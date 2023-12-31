// $Id: Geant4Data.h 513 2013-04-05 14:31:53Z gaede $
//====================================================================
//  AIDA Detector description implementation
//--------------------------------------------------------------------
//
//  Run Geant4 using DDG4 from root prompt with test objects for
//  Run/Event/Sensitive actions.
//
//  The Geant4 setup is programmed as a root script.
//
//  Usage:
//  $> root.exe
//  root[0] .x <installation-directory>/examples/LHeD/scripts/initACLick.C
//  root[1] .L <installation-directory>/examples/LHeD/scripts/initACLick.C+
//  root[2] LHeDACLick()
//
//
//  Author     : M.Frank
//
//====================================================================

#include "DDG4/Geant4Config.h"
#include "DDG4/Geant4TestActions.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "TSystem.h"
#include <iostream>

using namespace std;
using namespace dd4hep;
using namespace dd4hep::sim;
using namespace dd4hep::sim::Test;
using namespace dd4hep::sim::Setup;

Geant4SensDetActionSequence* setupDetector(Geant4Kernel& kernel, const std::string& name)   {
  SensitiveSeq sd = SensitiveSeq(kernel,"Geant4SensDetActionSequence/"+name);
  Sensitive  sens = Sensitive(kernel,"Geant4TestSensitive/"+name+"Handler",name);
  sens["OutputLevel"] = 2;
  sd->adopt(sens);
  sens = Sensitive(kernel,"Geant4TestSensitive/"+name+"Monitor",name);
  sd->adopt(sens);
  return sd;
}

int setupG4_CINT(bool interactive)  {
  Geant4Kernel& kernel = Geant4Kernel::instance(Detector::getInstance());
  string install_dir = getenv("DD4hepExamplesINSTALL");
  Phase p;

  kernel.loadGeometry(("file:"+install_dir+"/examples/LHeD/compact/compact.xml").c_str());
  kernel.loadXML(("file:"+install_dir+"/examples/LHeD/sim/field.xml").c_str());

  if ( interactive )   {
    kernel.property("UI") = "UI";
    setPrintLevel(DEBUG);

    Action ui(kernel,"Geant4UIManager/UI");
    ui["HaveVIS"]     = true;
    ui["HaveUI"]      = true;
    ui["SessionType"] = "csh";
    kernel.registerGlobalAction(ui);
  }
  else   {
    kernel.property("NumEvents") = 3;
  }
  GenAction gun(kernel,"Geant4ParticleGun/Gun");
  gun["energy"]       = 10*CLHEP::GeV;
  gun["particle"]     = "e-";
  gun["multiplicity"] = 1;
  gun["OutputLevel"]  = 3;
  kernel.generatorAction().adopt(gun);

  RunAction run_init(kernel,"Geant4TestRunAction/RunInit");
  run_init["Property_int"] = 12345;
  kernel.runAction().adopt(run_init);
  kernel.eventAction().callAtBegin(run_init.get(),&Geant4TestRunAction::beginEvent);
  kernel.eventAction().callAtEnd  (run_init.get(),&Geant4TestRunAction::endEvent);

  EventAction evt_1(kernel,"Geant4TestEventAction/UserEvent_1");
  evt_1["Property_int"] = 12345;
  evt_1["Property_string"] = "Events";
  evt_1["OutputLevel"] = 3;
  kernel.eventAction().adopt(evt_1);

  p = kernel.addPhase<const G4Run*>("BeginRun");
  p->add(evt_1.get(),&Geant4TestEventAction::beginRun);
  kernel.runAction().callAtBegin(p.get(),&Geant4ActionPhase::call<const G4Run*>);

  p = kernel.addPhase<const G4Run*>("EndRun");
  p->add(evt_1.get(),&Geant4TestEventAction::endRun);
  kernel.runAction().callAtEnd(p.get(),&Geant4ActionPhase::call<const G4Run*>);

  EventAction evt_2(kernel,"Geant4TestEventAction/UserEvent_2");
  kernel.eventAction().adopt(evt_2);
 
  setupDetector(kernel,"SiVertexBarrel");
  setupDetector(kernel,"SiTrackerBarrel");
  setupDetector(kernel,"SiTrackerBackward");
  setupDetector(kernel,"SiTrackerForward");
  setupDetector(kernel,"EcalBarrel");
  setupDetector(kernel,"EcalEndcap_fwd");
  setupDetector(kernel,"EcalEndcap_bwd");
  setupDetector(kernel,"HcalBarrel");
  setupDetector(kernel,"HcalEndcap_fwd");
  setupDetector(kernel,"HcalEndcap_bwd");
  setupDetector(kernel,"HcalPlug_fwd");
  setupDetector(kernel,"HcalPlug_bwd");
  setupDetector(kernel,"MuonBarrel");
  setupDetector(kernel,"MuonEndcap_fwd1");
  setupDetector(kernel,"MuonEndcap_fwd2");
  setupDetector(kernel,"MuonEndcap_bwd1");
  setupDetector(kernel,"MuonEndcap_bwd2");

  kernel.configure();
  kernel.initialize();
  kernel.run();
  std::cout << "LHeD, Successfully executed application .... " << std::endl;
  kernel.terminate();
  std::cout << "TEST_PASSED" << std::endl;
  return 0;
}

#if defined(G__DICTIONARY) || defined(__CLING__) || defined(__CINT__) || defined(__MAKECINT__) // CINT script
int LHeDACLick()
#else
int main(int, char**)                              // Main program if linked standalone
#endif
{
  return setupG4_CINT(false);
}

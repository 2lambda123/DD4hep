//==========================================================================
//  AIDA Detector description implementation
//--------------------------------------------------------------------------
// Copyright (C) Organisation europeenne pour la Recherche nucleaire (CERN)
// All rights reserved.
//
// For the licensing terms see $DD4hepINSTALL/LICENSE.
// For the list of contributors see $DD4hepINSTALL/doc/CREDITS.
//
//--------------------------------------------------------------------------
//
//  Run Geant4 using DDG4 from root prompt with test objects for
//  Run/Event/Sensitive actions.
//
//  The Geant4 setup is programmed in the xml files to be parsed. Only
//  the commands to parse these xml files is executed by root.
//
//  Usage:
//  $> root.exe
//  root[0] .x <installation-directory>/examples/DDG4/examples/initAClick.C
//  root[1] .L <installation-directory>/examples/DDG4/examples/CLICSidXML.C+
//  root[2] CLICSidAClick()
//
//
//  Author     : M.Frank
//
//=====================================================------===============
#include <DDG4/Geant4Config.h>
#include <iostream>
#include <ctime>

using namespace std;
using namespace dd4hep::sim::Setup;

int setupG4_XML(bool interactive)  {
  string install_dir = getenv("DD4hepExamplesINSTALL");
  string det_dir     = getenv("DD4hepINSTALL");
  string prefix = "file:"+install_dir+"/examples/";
  Kernel& kernel = Kernel::instance(dd4hep::Detector::getInstance());
  kernel.loadGeometry((det_dir+"/DDDetectors/compact/SiD.xml").c_str());
  kernel.loadXML((prefix+"CLICSiD/sim/field.xml").c_str());
  kernel.loadXML((prefix+"CLICSiD/sim/sequences.xml").c_str());
  kernel.loadXML((prefix+"CLICSiD/sim/physics.xml").c_str());
  if ( interactive )  {
    kernel.property("UI") = "UI";
  }
  else   {
    kernel.property("NumEvents") = 4;
  }
  Action rndm(kernel, "Geant4Random/Random");
  rndm["Seed"] = ::time(0);
  kernel.registerGlobalAction(rndm);

  EventAction out(kernel,"Geant4Output2ROOT/RootOutput");
  out["Output"] = is_aclick() ? "CLICSiD.xml_aclick.root" : "CLICSiD.xml_exe.root";
  kernel.eventAction().adopt(out);

  kernel.configure();
  kernel.initialize();
  kernel.run();
  cout << "Successfully executed application .... " << endl;
  kernel.terminate();
  cout << "TEST_PASSED" << endl;
  return 0;
}

int CLICSiDXML()   {
  return setupG4_XML(false);
}

#if not(defined(G__DICTIONARY) || defined(__CLING__) || defined(__CINT__) || defined(__MAKECINT__))
int main(int, char**)                              // Main program if linked standalone
{
  std::cout << "Running CLICSiDXML as standalone executable...." << std::endl;
  return CLICSiDXML();
}
#endif



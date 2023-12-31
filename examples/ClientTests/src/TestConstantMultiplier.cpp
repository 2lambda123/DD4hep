//==========================================================================
//  AIDA Detector description implementation 
//--------------------------------------------------------------------------
// Copyright (C) Organisation europeenne pour la Recherche nucleaire (CERN)
// All rights reserved.
//
// For the licensing terms see $DD4hepINSTALL/LICENSE.
// For the list of contributors see $DD4hepINSTALL/doc/CREDITS.
//
// Author     : M.Frank
//
//==========================================================================
/* 
 Plugin invocation:
 ==================
 This plugin behaves like a main program.
 Invoke the plugin with something like this:

 geoPluginRun -destroy -plugin DD4hep_TestConstantsMultiplier -opt [-opt]

*/
// Framework include files
#include "DD4hep/Printout.h"
#include "DD4hep/Factories.h"
#include "DD4hep/Detector.h"
#include "DD4hep/detail/ObjectsInterna.h"
#include <fstream>
#include <cerrno>

using namespace dd4hep;

/// Plugin function: Test in memory XML parsing of a simple sub detector
/**
 *  Factory: DD4hep_XML-In-Memory
 *
 *  Though there is a file name given, it is read FIRST and then parsed.
 *  Similar to a in memory XML string.
 *
 *  \author  M.Frank
 *  \version 1.0
 *  \date    20/01/2018
 */
static int multiply_constants (Detector& detector, int argc, char** argv)  {
  bool help = false;
  std::string name = "TestConstantsMultiplier";
  for(int i=0; i<argc && argv[i]; ++i)  {
    if ( 0 == ::strncmp("-name",argv[i],4) )
      name = argv[++i];
    else if ( 0 == ::strncmp("-help",argv[i],4) )
      help = true;
    else
      help = true;
  }
  if ( help )   {
    /// Help printout describing the basic command line interface
    std::cout <<
      "Usage: -plugin <name> -arg [-arg]                              \n"
      "     name:   factory name     DD4hep_TestConstantsMultiplier   \n"
      "\tArguments given: " << arguments(argc,argv) << std::endl << std::flush;
    ::exit(EINVAL);
  }
  int num_test = 0;
  const auto& constants = detector.constants();
  for(const auto& e : constants)  {
    Constant c = e.second;
    if ( c.dataType() == "number" )   {
      try {
        double res = _multiply(c.name(),1.0);
        printout(INFO,name,"+++ Constant: %-16s = %-16s [%s]  -> %-16s = %9.3g",
                 c.name(), c->GetTitle(), c.dataType().c_str(), c.name(), res);
        ++num_test;
      }
      catch(...)   {
      }
    }
  }
  printout(ALWAYS,name,"+++ Tested %d numeric constants for expression evaluation.",num_test);
  return 1;
}
DECLARE_APPLY(DD4hep_TestConstantsMultiplier,multiply_constants)

static int  print_line(Detector& , int, char** )  {
  printout(ALWAYS,"Line","+++ ------------------------------------------------------------------");
  return 1;
}
DECLARE_APPLY(DD4hep_TestPrintLine,print_line)

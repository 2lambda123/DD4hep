#==========================================================================
#  AIDA Detector description implementation 
#--------------------------------------------------------------------------
# Copyright (C) Organisation europeenne pour la Recherche nucleaire (CERN)
# All rights reserved.
#
# For the licensing terms see $DD4hepINSTALL/LICENSE.
# For the list of contributors see $DD4hepINSTALL/doc/CREDITS.
#
#==========================================================================
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
include ( ${DD4hep_DIR}/cmake/DD4hep.cmake )

#--------------------------------------------------------------------------
dd4hep_configure_output ()
dd4hep_package ( Persistency MAJOR 0 MINOR 0 PATCH 1
  USES         [ROOT   REQUIRED COMPONENTS Geom GenVector]
               [DD4hep REQUIRED COMPONENTS DDCore]
  OPTIONAL     XERCESC
)
#-----------------------------------------------------------------------------------
dd4hep_add_plugin(PersistencyExample SOURCES src/*.cpp)
dd4hep_configure_scripts (Persistency DEFAULT_SETUP WITH_TESTS )
#--------------------------------------------------------------------------
#
#  Test saving conditions to ROOT file
dd4hep_add_test_reg( Persist_Conditions_Save
  COMMAND    "${CMAKE_INSTALL_PREFIX}/bin/run_test_ClientTests.sh"
  EXEC_ARGS  geoPluginRun
  -plugin DD4hep_PersistencyExample_write_cond -output Conditions.root
  REGEX_PASS "\\+\\+\\+ Wrote 1360 bytes to file Conditions.root"
  REGEX_FAIL " ERROR ;EXCEPTION;Exception;FAILED"
  )
#
#  Test restoring geometry from ROOT file: Volume Manager
dd4hep_add_test_reg( Persist_Conditions_Restore
  COMMAND    "${CMAKE_INSTALL_PREFIX}/bin/run_test_ClientTests.sh"
  EXEC_ARGS  geoPluginRun
  -plugin DD4hep_PersistencyExample_read_cond -input Conditions.root
  REGEX_PASS "\\+\\+\\+ Read successfully 14 conditions. Result=1637"
  REGEX_FAIL " ERROR ;EXCEPTION;Exception;FAILED"
  )
#
#  Test saving geometry to ROOT file
dd4hep_add_test_reg( Persist_CLICSiD_Save_LONGTEST
  COMMAND    "${CMAKE_INSTALL_PREFIX}/bin/run_test_ClientTests.sh"
  EXEC_ARGS  geoPluginRun
  -volmgr -destroy -input file:${CMAKE_CURRENT_SOURCE_DIR}/../CLICSiD/compact/compact.xml
  -plugin DD4hepGeometry2ROOT -output CLICSiD_geometry.root
  REGEX_PASS "\\+\\+\\+ Successfully saved geometry data to file."
  REGEX_FAIL " ERROR ;EXCEPTION;Exception;FAILED"
  )
#
#  Test restoring geometry from ROOT file: Volume Manager
dd4hep_add_test_reg( Persist_CLICSiD_Restore_LONGTEST
  COMMAND    "${CMAKE_INSTALL_PREFIX}/bin/run_test_ClientTests.sh"
  EXEC_ARGS  geoPluginRun -print WARNING
  -plugin DD4hepRootLoader CLICSiD_geometry.root
  REGEX_PASS "\\+\\+\\+ Successfully loaded detector description from file"
  REGEX_FAIL " ERROR ;EXCEPTION;Exception;FAILED"
  )
#
#  Test restoring geometry from ROOT file: Volume Manager loading+nominals
dd4hep_add_test_reg( Persist_CLICSiD_Restore_VolMgr1_LONGTEST
  COMMAND    "${CMAKE_INSTALL_PREFIX}/bin/run_test_ClientTests.sh"
  EXEC_ARGS  geoPluginRun -print WARNING
  -plugin DD4hepRootLoader CLICSiD_geometry.root
  -plugin DD4hepCheckVolumeManager
  REGEX_PASS "\\+\\+\\+ PASSED Checked 29270 VolumeManager contexts. Num.Errors: 0"
  REGEX_FAIL " ERROR ;EXCEPTION;Exception;FAILED"
  )
#
#  Test restoring geometry from ROOT file: Test Volume Manager results
dd4hep_add_test_reg( Persist_CLICSiD_Restore_VolMgr2_LONGTEST
  COMMAND    "${CMAKE_INSTALL_PREFIX}/bin/run_test_ClientTests.sh"
  EXEC_ARGS  geoPluginRun -print WARNING
  -plugin DD4hepRootLoader CLICSiD_geometry.root
  -plugin DD4hepVolumeMgrTest SiTrackerBarrel
  REGEX_PASS "\\+\\+\\+ PASSED: Checked 81306 objects. Num.Errors:0"
  REGEX_FAIL " ERROR ;EXCEPTION;Exception;FAILED"
  )
#
#  Test restoring geometry from ROOT file: DetElement nominal alignments
#  Note: BeamCal has a problem. Need to be taken into account
dd4hep_add_test_reg( Persist_CLICSiD_Restore_Nominal_LONGTEST
  COMMAND    "${CMAKE_INSTALL_PREFIX}/bin/run_test_ClientTests.sh"
  EXEC_ARGS  geoPluginRun -print WARNING
  -plugin DD4hepRootLoader CLICSiD_geometry.root
  -plugin DD4hepCheckNominals
  REGEX_PASS "\\+\\+\\+ FAILED Checked 15946 DetElements. Num.Errors: 50"
  )
#
#  Test restoring geometry from ROOT file: Sensitive detectors
dd4hep_add_test_reg( Persist_CLICSiD_Restore_Sensitives_LONGTEST
  COMMAND    "${CMAKE_INSTALL_PREFIX}/bin/run_test_ClientTests.sh"
  EXEC_ARGS  geoPluginRun -print WARNING
  -plugin DD4hepRootLoader CLICSiD_geometry.root
  -plugin DD4hepCheckSensitives
  REGEX_PASS "\\+\\+\\+ PASSED Checked 14 SensitiveDetector objects. Num.Errors: 0"
  REGEX_FAIL " ERROR ;EXCEPTION;Exception;FAILED"
  )
#
#  Test restoring geometry from ROOT file: Readout segmentations
dd4hep_add_test_reg( Persist_CLICSiD_Restore_Segmentations_LONGTEST
  COMMAND    "${CMAKE_INSTALL_PREFIX}/bin/run_test_ClientTests.sh"
  EXEC_ARGS  geoPluginRun -print WARNING
  -plugin DD4hepRootLoader CLICSiD_geometry.root
  -plugin DD4hepCheckSegmentations
  REGEX_PASS "\\+\\+\\+ PASSED Checked 9 readout segmentations. Num.Errors: 0"
  REGEX_FAIL " ERROR ;EXCEPTION;Exception;FAILED"
  )
#
#  Test restoring geometry from ROOT file: Readout structures
dd4hep_add_test_reg( Persist_CLICSiD_Restore_Readouts_LONGTEST
  COMMAND    "${CMAKE_INSTALL_PREFIX}/bin/run_test_ClientTests.sh"
  EXEC_ARGS  geoPluginRun -print WARNING
  -plugin DD4hepRootLoader CLICSiD_geometry.root
  -plugin DD4hepCheckReadouts
  REGEX_PASS "\\+\\+\\+ PASSED Checked 14 readout objects. Num.Errors: 0"
  REGEX_FAIL " ERROR ;EXCEPTION;Exception;FAILED"
  )
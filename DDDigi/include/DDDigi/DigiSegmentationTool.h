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
#ifndef DDDIGI_DIGISEGMENTATIONTOOL_H
#define DDDIGI_DIGISEGMENTATIONTOOL_H

// Framework include files
#include <DDDigi/DigiData.h>
#include <DD4hep/Detector.h>
#include <DD4hep/DetElement.h>

/// Namespace for the AIDA detector description toolkit
namespace dd4hep {

  /// Namespace for the Digitization part of the AIDA detector description toolkit
  namespace digi {

    /// Forward declarations
    class DigiSegmentContext;
    class DigiSegmentationTool;

    /// Segmentation split context
    /**
     *
     *  \author  M.Frank
     *  \version 1.0
     *  \ingroup DD4HEP_DIGITIZATION
     */
    class DigiSegmentContext  {
    public:
      using field_t = const BitFieldElement;
      DetElement   detector   { };
      IDDescriptor idspec     { };
      field_t*     field      { nullptr };
      uint64_t     cell_mask  { ~0x0UL };
      uint64_t     det_mask   { 0UL };
      uint64_t     split_mask { 0UL };
      int32_t      offset     { 0 };
      int32_t      width      { 0 };
      int32_t      max_split  { 0 };

    public:
      /// Default constructor
      DigiSegmentContext() = default;
      /// Default move constructor
      DigiSegmentContext(DigiSegmentContext&& copy) = default;
      /// Default copy constructor
      DigiSegmentContext(const DigiSegmentContext& copy) = default;
      /// Default destructor
      virtual ~DigiSegmentContext() = default;
      /// Default move assignment
      DigiSegmentContext& operator=(DigiSegmentContext&& copy) = default;
      /// Default copy assignment
      DigiSegmentContext& operator=(const DigiSegmentContext& copy) = default;

      /// Split field name
      const std::string& name()  const;
      /// Split field name
      const char* cname()  const;
      /// Full identifier (field + id)
      std::string identifier(uint32_t id)  const;
      
      /// Get the identifier of the cell to be split
      uint32_t split_id(uint64_t cell)  const  {
	return uint32_t( (cell & this->split_mask) >> this->offset );
      }
      /// The CELL ID part of the identifier
      uint64_t cell_id(uint64_t cell)  const  {
	return uint64_t( uint64_t(cell & this->cell_mask) >> (this->offset + width) );
      }
      /// The identifier of the parent detector
      uint64_t detector_id(uint64_t cell)  const  {
	return uint64_t(cell & this->det_mask);
      }
    };

    /// Tool to handle segmentation manipulations
    /**
     *  
     *  
     *
     *  \author  M.Frank
     *  \version 1.0
     *  \ingroup DD4HEP_DIGITIZATION
     */
    class DigiSegmentationTool  {
    public:
      Detector&         description;
      DetElement        detector;
      SensitiveDetector sensitive;
      IDDescriptor      iddescriptor;

    public:
      /// Initializing constructor
      DigiSegmentationTool(Detector& desc);
      /// Default destructor
      virtual ~DigiSegmentationTool() = default;

      /// Setup tool to handle a given detector of the geometry
      void set_detector(const std::string& det_name);

      /// Access the readout collection keys
      std::vector<std::string> collection_names()   const;
      /// Access the readout collection keys (mask is empty!)
      std::vector<Key> collection_keys()   const;
      /// Access the readout collection keys with predefined mask
      std::vector<Key> collection_keys(Key::mask_type mask)   const;
      /// Access the collection keys from readout structures of multiple subdetectors
      std::vector<Key> collection_keys(const std::vector<std::string>& detectors)   const;
      /// Access the collection keys from readout structures of multiple subdetectors
      std::vector<Key> collection_keys(const std::vector<std::string>& detectors, Key::mask_type mask)   const;

      /// Create a split context depending on the segmentation field
      DigiSegmentContext split_context(const std::string& split_by)  const;

      /// Create full set of detector segments which can be split according to the context
      std::set<uint32_t> split_segmentation(const std::string& split_by)  const;
    };
  }    // End namespace digi
}      // End namespace dd4hep
#endif // DDDIGI_DIGISEGMENTATIONTOOL_H

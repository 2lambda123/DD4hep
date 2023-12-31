//==========================================================================
//  AIDA Detector description implementation 
//--------------------------------------------------------------------------
// Copyright (C) Organisation europeenne pour la Recherche nucleaire (CERN)
// All rights reserved.
//
// For the licensing terms see $DD4hepINSTALL/LICENSE.
// For the list of contributors see $DD4hepINSTALL/doc/CREDITS.
//
//==========================================================================
#include "Parsers/spirit/ParsersStandardMiscCommon.h"

PARSERS_DEF_FOR_PAIR(bool,bool)
PARSERS_DEF_FOR_PAIR(float,float)
PARSERS_DEF_FOR_PAIR(double,double)
PARSERS_DEF_FOR_PAIR(double,int)
PARSERS_DEF_FOR_PAIR(double,long)
PARSERS_DEF_FOR_PAIR(double,size_t)

/// Namespace for the AIDA detector description toolkit
namespace dd4hep {

  /// Namespace for the AIDA detector for utilities using boost::spirit parsers
  namespace Parsers {

    template <> int parse(std::vector<std::pair<double, double> >& result, const std::string& input) {
      return parse_(result, input);
    }

    template <> int parse(std::vector<std::pair<int, int> >& result, const std::string& input) {
      return parse_(result, input);
    }

    template <> int parse(std::vector<std::vector<std::string> >& result, const std::string& input) {
      return parse_(result, input);
    }
  }
}

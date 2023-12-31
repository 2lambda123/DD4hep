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

#include "Parsers/config.h"

// Framework include files
#if defined(DD4HEP_PARSER_HEADER)

#define DD4HEP_NEED_EVALUATOR
// This is the case, if the parsers are externalized
// and the dd4hep namespace is renamed!
#include DD4HEP_PARSER_HEADER

#else

// Standard dd4hep parser handling
#include "Parsers/spirit/ToStream.h"

#endif
#include "Evaluator/Evaluator.h"

// C/C++ include files
#include <sstream>
#include <iostream>
#include <stdexcept>

namespace dd4hep {
  const dd4hep::tools::Evaluator& g4Evaluator();
}
namespace {
  const dd4hep::tools::Evaluator& eval(dd4hep::g4Evaluator());
}

//==============================================================================
namespace dd4hep {  namespace Parsers {
    template <typename T> T evaluate_string(const std::string& /* value */)   {
      throw "Bad undefined call";
    }

    template <> double evaluate_string<double>(const std::string& value)   {
      std::stringstream err;
      auto result = eval.evaluate(value, err);
      if (result.first != tools::Evaluator::OK) {
        throw std::runtime_error("dd4hep::Properties: Severe error during expression evaluation of " + 
				 value + " : " + err.str());
      }
      return result.second;
    }
    template <> float evaluate_string<float>(const std::string& value)   {
      std::stringstream err;
      auto result = eval.evaluate(value, err);
      if (result.first != tools::Evaluator::OK) {
        throw std::runtime_error("dd4hep::Properties: Severe error during expression evaluation of " +
				 value + " : " + err.str());
      }
      return (float) result.second;
    }
  }
}

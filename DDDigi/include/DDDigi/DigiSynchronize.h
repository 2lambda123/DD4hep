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
#ifndef DDDIGI_DIGISYNCHRONIZE_H
#define DDDIGI_DIGISYNCHRONIZE_H

/// Framework incloude files
#include <DDDigi/DigiEventAction.h>
#include <DDDigi/DigiParallelWorker.h>

/// Namespace for the AIDA detector description toolkit
namespace dd4hep {

  // Forward declarations

  /// Namespace for the Digitization part of the AIDA detector description toolkit
  namespace digi {

    /// 
    /**
     *
     *  \author  M.Frank
     *  \version 1.0
     *  \ingroup DD4HEP_DIGITIZATION
     */
    class DigiSynchronize : public DigiEventAction {
    protected:
      using work_t    = context_t;
      using self_t    = DigiSynchronize;
      using worker_t  = DigiParallelWorker<DigiEventAction, work_t, std::size_t, self_t&>;
      using workers_t = DigiParallelWorkers<worker_t>;
      friend class DigiParallelWorker<DigiEventAction, work_t, std::size_t, self_t&>;

      /// The list of action objects to be called
      workers_t m_actors;

    protected:
      /// Define standard assignments and constructors
      DDDIGI_DEFINE_ACTION_CONSTRUCTORS(DigiSynchronize);

    public:
      /// Standard constructor
      DigiSynchronize(const kernel_t& kernel, const std::string& nam);
      /// Default destructor
      virtual ~DigiSynchronize();
      /// Adopt a new action as part of the sequence. Sequence takes ownership.
      virtual void adopt(DigiEventAction* action);
      /// Begin-of-event callback
      virtual void execute(context_t& context)  const override;
    };
  }    // End namespace digi
}      // End namespace dd4hep
#endif // DDDIGI_DIGISYNCHRONIZE_H

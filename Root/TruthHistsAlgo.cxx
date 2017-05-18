#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include "AthContainers/ConstDataVector.h"
#include "xAODAnaHelpers/HelperFunctions.h"

#include <SUSY_EWK_Truth/TruthHistsAlgo.h>

#include <xAODAnaHelpers/tools/ReturnCheck.h>

// this is needed to distribute the algorithm to the workers
ClassImp(TruthHistsAlgo)

TruthHistsAlgo :: TruthHistsAlgo ( std::string className ) :
    Algorithm(className),
    m_plots_default_cuts(nullptr)
{
  m_truthContainerName      = "";
  m_jetContainerName        = "";
  m_detailStr               = "";
  m_debug                   = false;

}

EL::StatusCode TruthHistsAlgo :: setupJob (EL::Job& job)
{
  job.useXAOD();

  // let's initialize the algorithm to use the xAODRootAccess package
  xAOD::Init("TruthHistsAlgo").ignore(); // call before opening first file

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode TruthHistsAlgo :: histInitialize ()
{

  Info("histInitialize()", "%s", m_name.c_str() );
  RETURN_CHECK("xAH::Algorithm::algInitialize()", xAH::Algorithm::algInitialize(), "");
  // needed here and not in initalize since this is called first
  if( m_truthContainerName.empty() || m_jetContainerName.empty() || m_detailStr.empty() ){
    Error("histInitialize()", "One or more required configuration values are empty");
    return EL::StatusCode::FAILURE;
  }


  // declare class and add histograms to output
  m_plots_default_cuts = new TruthHists(m_name, m_detailStr, m_truth_ptMinCut, m_truth_etaAbsMaxCut, m_jet_ptMinCut, m_bJet_etaAbsMaxCut, m_min_n_jetsCut, m_min_n_bJetsCut);
  RETURN_CHECK("TruthHistsAlgo::histInitialize()", m_plots_default_cuts -> initialize(), "");
  m_plots_default_cuts -> record( wk() );

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode TruthHistsAlgo :: fileExecute () { return EL::StatusCode::SUCCESS; }
EL::StatusCode TruthHistsAlgo :: changeInput (bool firstFile) { return EL::StatusCode::SUCCESS; }

EL::StatusCode TruthHistsAlgo :: initialize ()
{
  Info("initialize()", "TruthHistsAlgo");
  m_event = wk()->xaodEvent();
  m_store = wk()->xaodStore();
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode TruthHistsAlgo :: execute ()
{
  float eventWeight = 1.0;

  const xAOD::TruthParticleContainer* truths(nullptr);
  if (m_truthContainerName != "")
    RETURN_CHECK("TruthHistsAlgo::execute()", HelperFunctions::retrieve(truths, m_truthContainerName, m_event, m_store, m_verbose) ,"");
 
  const xAOD::JetContainer* jets(nullptr);
  if (m_jetContainerName != "")
    RETURN_CHECK("TruthHistsAlgo::execute()", HelperFunctions::retrieve(jets, m_jetContainerName, m_event, m_store, m_verbose) ,"");

  RETURN_CHECK("TruthHistsAlgo::execute()", m_plots_default_cuts->execute( truths, jets, eventWeight), "");

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode TruthHistsAlgo :: postExecute () { return EL::StatusCode::SUCCESS; }

EL::StatusCode TruthHistsAlgo :: finalize () { return EL::StatusCode::SUCCESS; }

EL::StatusCode TruthHistsAlgo :: histFinalize ()
{
  // clean up memory
  if(m_plots_default_cuts) delete m_plots_default_cuts;
  RETURN_CHECK("xAH::Algorithm::algFinalize()", xAH::Algorithm::algFinalize(), "");
  return EL::StatusCode::SUCCESS;
}

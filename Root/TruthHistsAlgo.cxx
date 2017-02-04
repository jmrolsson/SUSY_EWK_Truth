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
  m_inContainerName         = "";
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
  if( m_inContainerName.empty() || m_detailStr.empty() ){
    Error("histInitialize()", "One or more required configuration values are empty");
    return EL::StatusCode::FAILURE;
  }


  // declare class and add histograms to output
  m_plots_default_cuts = new TruthHists(m_name, m_detailStr);
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
  const xAOD::TruthParticleContainer* truths(nullptr);
  RETURN_CHECK("TruthHistsAlgo::execute()", HelperFunctions::retrieve(truths, m_inContainerName, m_event, m_store, m_verbose) ,"");

  float eventWeight = 1.0;
 
  // // Implement cuts here:
  // if (jet_pt < m_jet_ptMinCut) continue;
  //
  RETURN_CHECK("TruthHistsAlgo::execute()", m_plots_default_cuts->execute( truths, eventWeight ), "");

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

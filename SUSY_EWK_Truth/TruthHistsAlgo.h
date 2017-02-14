#ifndef SUSY_EWK_Truth_TruthHistsAlgo_H
#define SUSY_EWK_Truth_TruthHistsAlgo_H

// Histograms
#include <SUSY_EWK_Truth/TruthHists.h>

// algorithm wrapper
#include "xAODAnaHelpers/Algorithm.h"

class TruthHistsAlgo : public xAH::Algorithm
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
public:
  std::string m_truthContainerName;
  std::string m_jetContainerName;

  // configuration variables
  std::string m_detailStr;

  // truth parton cuts
  float m_truth_ptMinCut = 0.;
  float m_truth_etaAbsMaxCut = 1e8;
  
  // truth jet cuts
  float m_jet_ptMinCut = 0.;
  float m_bJet_etaAbsMaxCut = 1e8;
  float m_min_n_bJets = 1e8;


private:
  TruthHists* m_plots_default_cuts; //!

  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)
public:

  // this is a standard constructor
  TruthHistsAlgo (std::string className = "TruthHistsAlgo");

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

  // this is needed to distribute the algorithm to the workers
  ClassDef(TruthHistsAlgo, 1);
};

#endif

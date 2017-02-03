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
  std::string m_inContainerName;

  // configuration variables
  std::string m_detailStr;

private:
  TruthHists* m_plots; //!

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

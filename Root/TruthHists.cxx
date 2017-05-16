#include "SUSY_EWK_Truth/TruthHists.h"
#include <math.h>

#include "xAODAnaHelpers/tools/ReturnCheck.h"
#include "xAODAnaHelpers/HelperFunctions.h"

TruthHists :: TruthHists (std::string name, std::string detailStr,
    float truth_ptMinCut, float truth_etaAbsMaxCut,
    float jet_ptMinCut, float bJet_etaAbsMaxCut, float min_n_bJets) :
  HistogramManager(name, detailStr),
  m_C1({}),
  m_N2({}),
  m_N1_from_C1({}),
  m_W_from_C1({}),
  m_N1_from_N2({}),
  m_Zh_from_N2({}),
  m_C1_W_decays({}),
  m_N2_Zh_decays({})
{
  m_truth_ptMinCut = truth_ptMinCut;
  m_truth_etaAbsMaxCut = truth_etaAbsMaxCut;
  m_jet_ptMinCut = jet_ptMinCut;
  m_bJet_etaAbsMaxCut = bJet_etaAbsMaxCut;
  m_min_n_bJets = min_n_bJets;
}

TruthHists :: ~TruthHists () {}

StatusCode TruthHists::initialize() {

  unsigned int nBinsN = 10; float minBinN = -0.5; float maxBinN = 9.5;
  unsigned int nBinsN_m = 50; float minBinN_m = -0.5; float maxBinN_m = 49.5;
  unsigned int nBinsN_l = 350; float minBinN_l = -0.5; float maxBinN_l = 699.5;
  unsigned int nBinsPt = 250; float minBinPt = 0.0; float maxBinPt_s = 200.; float maxBinPt = 1000.; float maxBinPt_l = 2000.;
  unsigned int nBinsEta = 80; float minBinEta = -4.0; float maxBinEta = 4.0;
  unsigned int nBinsPhi = 64; float minBinPhi = -TMath::Pi(); float maxBinPhi = TMath::Pi();
  unsigned int nBinsDR = 40; float minBinDR = 0.0; float maxBinDR = 4.0;

  m_truth_n_nocut       = book(m_name, "truth_n_nocut",      "N_{truth}", nBinsN_l, minBinN_l, maxBinN_l);
  m_truth_n             = book(m_name, "truth_n",             "N_{truth}", nBinsN_l, minBinN_l, maxBinN_l);
  m_truth_pt            = book(m_name, "truth_pt",            "truth p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
  m_truth_pt_s          = book(m_name, "truth_pt_s",          "truth p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
  m_truth_pt_l          = book(m_name, "truth_pt_l",          "truth p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
  m_truth_eta           = book(m_name, "truth_eta",           "truth #eta", nBinsEta, minBinEta, maxBinEta);
  m_truth_phi           = book(m_name, "truth_phi",           "truth #phi",nBinsPhi, minBinPhi, maxBinPhi);
  m_truth_m             = book(m_name, "truth_m",             "truth m [GeV]", 150, 0, 150);
  m_truth_m_l           = book(m_name, "truth_m_l",           "truth m [GeV]", 100, 0, 1000);
  m_truth_pdgId         = book(m_name, "truth_pdgId",         "truth pdgId", 100, -50, 50);
  m_truth_pdgId_susy    = book(m_name, "truth_pdgId_susy",    "truth pdgId", 50, 1000000, 1000050);
  m_truth_pdgId_susy_p  = book(m_name, "truth_pdgId_susy_p",  "truth pdgId_p", 50, 1000000, 1000050);
  m_truth_pdgId_susy_n  = book(m_name, "truth_pdgId_susy_n",  "truth pdgId_n", 50,-1000050,-1000000);

  //
  //  Lepton plots
  //
  m_fillLeptons = false;
  if (m_detailStr.find("leptons") != std::string::npos) {
    m_fillLeptons = true;

    m_e_n              = book(m_name, "truth_e_n",              "N_{e}", nBinsN, minBinN, maxBinN);
    m_e_pt             = book(m_name, "truth_e_pt",             "e p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_e_pt_s           = book(m_name, "truth_e_pt_s",           "e p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_e_pt_l           = book(m_name, "truth_e_pt_l",           "e p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
    m_e_eta            = book(m_name, "truth_e_eta",            "e #eta", nBinsEta, minBinEta, maxBinEta);
    m_e_phi            = book(m_name, "truth_e_phi",            "e #phi",nBinsPhi, minBinPhi, maxBinPhi);
    m_e_m              = book(m_name, "truth_e_m",              "e m [GeV]", 150, 0, 150);
    m_mu_n             = book(m_name, "truth_mu_n",             "N_{#mu}", nBinsN, minBinN, maxBinN);
    m_mu_pt            = book(m_name, "truth_mu_pt",            "#mu p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_mu_pt_s          = book(m_name, "truth_mu_pt_s",          "#mu p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_mu_pt_l          = book(m_name, "truth_mu_pt_l",          "#mu p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
    m_mu_eta           = book(m_name, "truth_mu_eta",           "#mu #eta", nBinsEta, minBinEta, maxBinEta);
    m_mu_phi           = book(m_name, "truth_mu_phi",           "#mu #phi",nBinsPhi, minBinPhi, maxBinPhi);
    m_mu_m             = book(m_name, "truth_mu_m",             "#mu m [GeV]", 150, 0, 150);
    m_tau_n            = book(m_name, "truth_tau_n",            "N_{#tau}", nBinsN, minBinN, maxBinN);
    m_tau_pt           = book(m_name, "truth_tau_pt",           "#tau p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_tau_pt_s         = book(m_name, "truth_tau_pt_s",         "#tau p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_tau_pt_l         = book(m_name, "truth_tau_pt_l",         "#tau p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
    m_tau_eta          = book(m_name, "truth_tau_eta",          "#tau #eta", nBinsEta, minBinEta, maxBinEta);
    m_tau_phi          = book(m_name, "truth_tau_phi",          "#tau #phi",nBinsPhi, minBinPhi, maxBinPhi);
    m_tau_m            = book(m_name, "truth_tau_m",            "#tau m [GeV]", 150, 0, 150);
    m_lepton_n         = book(m_name, "truth_lepton_n",         "N_{lepton}", nBinsN, minBinN, maxBinN);
    m_lepton_pt        = book(m_name, "truth_lepton_pt",        "lepton p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_lepton_pt_s      = book(m_name, "truth_lepton_pt_s",      "lepton p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_lepton_pt_l      = book(m_name, "truth_lepton_pt_l",      "lepton p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
    m_lepton_eta       = book(m_name, "truth_lepton_eta",       "lepton #eta", nBinsEta, minBinEta, maxBinEta);
    m_lepton_phi       = book(m_name, "truth_lepton_phi",       "lepton #phi",nBinsPhi, minBinPhi, maxBinPhi);
    m_lepton_m         = book(m_name, "truth_lepton_m",         "lepton m [GeV]", 150, 0, 150);
  }

  //
  //  Quark plots
  //
  m_fillQuarks = false;
  if (m_detailStr.find("quarks") != std::string::npos) {
    m_fillQuarks = true;

    m_t_n             = book(m_name, "truth_t_n",             "N_{t}", nBinsN, minBinN, maxBinN);
    m_t_pt            = book(m_name, "truth_t_pt",            "t p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_t_pt_s          = book(m_name, "truth_t_pt_s",          "t p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_t_pt_l          = book(m_name, "truth_t_pt_l",          "t p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
    m_t_eta           = book(m_name, "truth_t_eta",           "t #eta", nBinsEta, minBinEta, maxBinEta);
    m_t_phi           = book(m_name, "truth_t_phi",           "t #phi",nBinsPhi, minBinPhi, maxBinPhi);
    m_t_m             = book(m_name, "truth_t_m",             "t m [GeV]", 150, 0, 150);
    m_b_n             = book(m_name, "truth_b_n",             "N_{b}", nBinsN_m, minBinN_m, maxBinN_m);
    m_b_pt            = book(m_name, "truth_b_pt",            "b p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_b_pt_s          = book(m_name, "truth_b_pt_s",          "b p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_b_pt_l          = book(m_name, "truth_b_pt_l",          "b p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
    m_b_eta           = book(m_name, "truth_b_eta",           "b #eta", nBinsEta, minBinEta, maxBinEta);
    m_b_phi           = book(m_name, "truth_b_phi",           "b #phi",nBinsPhi, minBinPhi, maxBinPhi);
    m_b_m             = book(m_name, "truth_b_m",             "b m [GeV]", 150, 0, 150);
    m_quark_n         = book(m_name, "truth_quark_n",         "N_{quark}", nBinsN_l, minBinN_l, maxBinN_l);
    m_quark_pt        = book(m_name, "truth_quark_pt",        "quark p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_quark_pt_s      = book(m_name, "truth_quark_pt_s",      "quark p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_quark_pt_l      = book(m_name, "truth_quark_pt_l",      "quark p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
    m_quark_eta       = book(m_name, "truth_quark_eta",       "quark #eta", nBinsEta, minBinEta, maxBinEta);
    m_quark_phi       = book(m_name, "truth_quark_phi",       "quark #phi",nBinsPhi, minBinPhi, maxBinPhi);
    m_quark_m         = book(m_name, "truth_quark_m",         "quark m [GeV]", 150, 0, 150);
  }

  //
  //  Boson plots
  //
  m_fillBosons = false;
  if (m_detailStr.find("bosons") != std::string::npos) {
    m_fillBosons = true;

    m_Z_n             = book(m_name, "truth_Z_n",             "N_{Z}", nBinsN, minBinN, maxBinN);
    m_Z_pt            = book(m_name, "truth_Z_pt",            "Z p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_Z_pt_s          = book(m_name, "truth_Z_pt_s",          "Z p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_Z_pt_l          = book(m_name, "truth_Z_pt_l",          "Z p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
    m_Z_eta           = book(m_name, "truth_Z_eta",           "Z #eta", nBinsEta, minBinEta, maxBinEta);
    m_Z_phi           = book(m_name, "truth_Z_phi",           "Z #phi",nBinsPhi, minBinPhi, maxBinPhi);
    m_Z_m             = book(m_name, "truth_Z_m",             "Z m [GeV]", 150, 0, 150);
    m_Z_child_n       = book(m_name, "truth_Z_child_n",       "Z N_{child}", nBinsN, minBinN, maxBinN);
    m_Z_child_pdgId   = book(m_name, "truth_Z_child_pdgId",   "Z child pdgId", 100, -50, 50);
    m_W_n             = book(m_name, "truth_W_n",             "N_{W}", nBinsN, minBinN, maxBinN);
    m_W_pt            = book(m_name, "truth_W_pt",            "W p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_W_pt_s          = book(m_name, "truth_W_pt_s",          "W p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_W_pt_l          = book(m_name, "truth_W_pt_l",          "W p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
    m_W_eta           = book(m_name, "truth_W_eta",           "W #eta", nBinsEta, minBinEta, maxBinEta);
    m_W_phi           = book(m_name, "truth_W_phi",           "W #phi",nBinsPhi, minBinPhi, maxBinPhi);
    m_W_m             = book(m_name, "truth_W_m",             "W m [GeV]", 150, 0, 150);
    m_W_child_n       = book(m_name, "truth_W_child_n",       "W N_{child}", nBinsN, minBinN, maxBinN);
    m_W_child_pdgId   = book(m_name, "truth_W_child_pdgId",   "W child pdgId", 100, -50, 50);
    m_h_n             = book(m_name, "truth_h_n",             "N_{h}", nBinsN, minBinN, maxBinN);
    m_h_pt            = book(m_name, "truth_h_pt",            "h p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_h_pt_s          = book(m_name, "truth_h_pt_s",          "h p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_h_pt_l          = book(m_name, "truth_h_pt_l",          "h p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
    m_h_eta           = book(m_name, "truth_h_eta",           "h #eta", nBinsEta, minBinEta, maxBinEta);
    m_h_phi           = book(m_name, "truth_h_phi",           "h #phi",nBinsPhi, minBinPhi, maxBinPhi);
    m_h_m             = book(m_name, "truth_h_m",             "h m [GeV]", 150, 0, 150);
    m_h_child_n       = book(m_name, "truth_h_child_n",       "h N_{child}", nBinsN, minBinN, maxBinN);
    m_h_child_pdgId   = book(m_name, "truth_h_child_pdgId",   "h child pdgId", 100, -50, 50);
  }

  //
  //  SUSY plots
  //
  m_fillSUSY = false;
  if (m_detailStr.find("substructure") != std::string::npos)
    m_fillSUSY = true;
  if (m_fillSUSY || (m_detailStr.find("susy") != std::string::npos)) {
    m_fillSUSY = true;

    m_C1_n             = book(m_name, "truth_C1_n",             "N_{C1}", nBinsN, minBinN, maxBinN);
    m_C1_pt            = book(m_name, "truth_C1_pt",            "C1 p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_C1_pt_s          = book(m_name, "truth_C1_pt_s",          "C1 p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_C1_pt_l          = book(m_name, "truth_C1_pt_l",          "C1 p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
    m_C1_eta           = book(m_name, "truth_C1_eta",           "C1 #eta", nBinsEta, minBinEta, maxBinEta);
    m_C1_phi           = book(m_name, "truth_C1_phi",           "C1 #phi",nBinsPhi, minBinPhi, maxBinPhi);
    m_C1_m             = book(m_name, "truth_C1_m",             "C1 m [GeV]", 150, 0, 600);
    m_C1_child_n       = book(m_name, "truth_C1_child_n",       "C1 N_{child}", nBinsN, minBinN, maxBinN);
    m_C1_child_pdgId   = book(m_name, "truth_C1_child_pdgId",   "C1 child pdgId", 100,-50, 50);
    m_C1_child_pdgId_susy = book(m_name, "truth_C1_child_pdgId_susy",   "C1 child pdgId", 50, 1000000, 1000050);
    m_N2_n             = book(m_name, "truth_N2_n",             "N_{N2}", nBinsN, minBinN, maxBinN);
    m_N2_pt            = book(m_name, "truth_N2_pt",            "N2 p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_N2_pt_s          = book(m_name, "truth_N2_pt_s",          "N2 p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_N2_pt_l          = book(m_name, "truth_N2_pt_l",          "N2 p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
    m_N2_eta           = book(m_name, "truth_N2_eta",           "N2 #eta", nBinsEta, minBinEta, maxBinEta);
    m_N2_phi           = book(m_name, "truth_N2_phi",           "N2 #phi",nBinsPhi, minBinPhi, maxBinPhi);
    m_N2_m             = book(m_name, "truth_N2_m",             "N2 m [GeV]", 150, 0, 600);
    m_N2_child_n       = book(m_name, "truth_N2_child_n",       "N2 N_{child}", nBinsN, minBinN, maxBinN);
    m_N2_child_pdgId   = book(m_name, "truth_N2_child_pdgId",   "N2 child pdgId", 100, -50, 50);
    m_N2_child_pdgId_susy = book(m_name, "truth_N2_child_pdgId_susy",   "N2 child pdgId", 50, 1000000, 1000050);
    m_N1_n             = book(m_name, "truth_N1_n",             "N_{N1}", nBinsN, minBinN, maxBinN);
    m_N1_pt            = book(m_name, "truth_N1_pt",            "N1 p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_N1_pt_s          = book(m_name, "truth_N1_pt_s",          "N1 p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_N1_pt_l          = book(m_name, "truth_N1_pt_l",          "N1 p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
    m_N1_eta           = book(m_name, "truth_N1_eta",           "N1 #eta", nBinsEta, minBinEta, maxBinEta);
    m_N1_phi           = book(m_name, "truth_N1_phi",           "N1 #phi",nBinsPhi, minBinPhi, maxBinPhi);
    m_N1_m             = book(m_name, "truth_N1_m",             "N1 m [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_N1_child_n       = book(m_name, "truth_N1_child_n",       "N1 N_{child}", nBinsN, minBinN, maxBinN);
    m_N1_child_pdgId   = book(m_name, "truth_N1_child_pdgId",   "N1 child pdgId", 100, -50, 50);
  }

  //
  //  Substructure validation plots
  //
  m_fillSubstructure = false;
  if (m_detailStr.find("substructure") != std::string::npos) {
    m_fillSubstructure = true;

    m_good_C1_N2_dPhi            = book(m_name, "truth_good_C1_N2_dPhi",       "#Delta#phi(C1, N2)", nBinsDR, minBinDR, maxBinDR);
    m_good_C1_N2_dEta            = book(m_name, "truth_good_C1_N2_dEta",       "#Delta#eta(C1, N2)", nBinsDR, minBinDR, maxBinDR);
    m_good_C1_N2_dR              = book(m_name, "truth_good_C1_N2_dR",         "#DeltaR(C1, N2)", nBinsDR, minBinDR, maxBinDR);
    m_good_C1_n                  = book(m_name, "truth_good_C1_n",    "N_{C1}", nBinsN, minBinN, maxBinN);
    m_good_C1_pt                 = book(m_name, "truth_good_C1_pt",   "C1 p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_good_C1_pt_s               = book(m_name, "truth_good_C1_pt_s", "C1 p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_good_C1_pt_l               = book(m_name, "truth_good_C1_pt_l", "C1 p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
    m_good_C1_eta                = book(m_name, "truth_good_C1_eta",  "C1 #eta", nBinsEta, minBinEta, maxBinEta);
    m_good_C1_phi                = book(m_name, "truth_good_C1_phi",  "C1 #phi",nBinsPhi, minBinPhi, maxBinPhi);
    m_good_C1_m                  = book(m_name, "truth_good_C1_m",    "C1 m [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_good_N2_n                  = book(m_name, "truth_good_N2_n",    "N_{N2}", nBinsN, minBinN, maxBinN);
    m_good_N2_pt                 = book(m_name, "truth_good_N2_pt",   "N2 p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_good_N2_pt_s               = book(m_name, "truth_good_N2_pt_s", "N2 p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_good_N2_pt_l               = book(m_name, "truth_good_N2_pt_l", "N2 p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
    m_good_N2_eta                = book(m_name, "truth_good_N2_eta",  "N2 #eta", nBinsEta, minBinEta, maxBinEta);
    m_good_N2_phi                = book(m_name, "truth_good_N2_phi",  "N2 #phi",nBinsPhi, minBinPhi, maxBinPhi);
    m_good_N2_m                  = book(m_name, "truth_good_N2_m",    "N2 m [GeV]", nBinsPt, minBinPt, maxBinPt);

    m_good_N1_W_dEta             = book(m_name, "truth_good_N1_W_dEta",       "|#Delta#eta(N1, W)|", nBinsDR, minBinDR, maxBinDR);
    m_good_N1_W_dPhi             = book(m_name, "truth_good_N1_W_dPhi",       "|#Delta#phi(N1, W)|", nBinsDR, minBinDR, maxBinDR);
    m_good_N1_W_dR               = book(m_name, "truth_good_N1_W_dR",         "#DeltaR(N1, W)", nBinsDR, minBinDR, maxBinDR);
    m_good_N1_from_C1_n          = book(m_name, "truth_good_N1_from_C1_n",    "N_{N1}", nBinsN, minBinN, maxBinN);
    m_good_N1_from_C1_pt         = book(m_name, "truth_good_N1_from_C1_pt",   "N1 p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_good_N1_from_C1_pt_s       = book(m_name, "truth_good_N1_from_C1_pt_s", "N1 p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_good_N1_from_C1_pt_l       = book(m_name, "truth_good_N1_from_C1_pt_l", "N1 p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
    m_good_N1_from_C1_eta        = book(m_name, "truth_good_N1_from_C1_eta",  "N1 #eta", nBinsEta, minBinEta, maxBinEta);
    m_good_N1_from_C1_phi        = book(m_name, "truth_good_N1_from_C1_phi",  "N1 #phi",nBinsPhi, minBinPhi, maxBinPhi);
    m_good_N1_from_C1_m          = book(m_name, "truth_good_N1_from_C1_m",    "N1 m [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_good_W_from_C1_n           = book(m_name, "truth_good_W_from_C1_n",     "N_{W}", nBinsN, minBinN, maxBinN);
    m_good_W_from_C1_pt          = book(m_name, "truth_good_W_from_C1_pt",    "W p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_good_W_from_C1_pt_s        = book(m_name, "truth_good_W_from_C1_pt_s",  "W p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_good_W_from_C1_pt_l        = book(m_name, "truth_good_W_from_C1_pt_l",  "W p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
    m_good_W_from_C1_eta         = book(m_name, "truth_good_W_from_C1_eta",   "W #eta", nBinsEta, minBinEta, maxBinEta);
    m_good_W_from_C1_phi         = book(m_name, "truth_good_W_from_C1_phi",   "W #phi",nBinsPhi, minBinPhi, maxBinPhi);
    m_good_W_from_C1_m           = book(m_name, "truth_good_W_from_C1_m",     "W m [GeV]", nBinsPt, minBinPt, maxBinPt_s);

    m_good_N1_Zh_dEta            = book(m_name, "truth_good_N1_Zh_dEta",      "|#Delta#eta(N1, Z/h)|", nBinsDR, minBinDR, maxBinDR);
    m_good_N1_Zh_dPhi            = book(m_name, "truth_good_N1_Zh_dPhi",      "|#Delta#phi(N1, Z/h)|", nBinsDR, minBinDR, maxBinDR);
    m_good_N1_Zh_dR              = book(m_name, "truth_good_N1_Zh_dR",        "#DeltaR(N1, Z/h)", nBinsDR, minBinDR, maxBinDR);
    m_good_N1_from_N2_n          = book(m_name, "truth_good_N1_from_N2_n",    "N_{N1}", nBinsN, minBinN, maxBinN);
    m_good_N1_from_N2_pt         = book(m_name, "truth_good_N1_from_N2_pt",   "N1 p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_good_N1_from_N2_pt_s       = book(m_name, "truth_good_N1_from_N2_pt_s", "N1 p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_good_N1_from_N2_pt_l       = book(m_name, "truth_good_N1_from_N2_pt_l", "N1 p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
    m_good_N1_from_N2_eta        = book(m_name, "truth_good_N1_from_N2_eta",  "N1 #eta", nBinsEta, minBinEta, maxBinEta);
    m_good_N1_from_N2_phi        = book(m_name, "truth_good_N1_from_N2_phi",  "N1 #phi",nBinsPhi, minBinPhi, maxBinPhi);
    m_good_N1_from_N2_m          = book(m_name, "truth_good_N1_from_N2_m",    "N1 m [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_good_Zh_from_N2_n          = book(m_name, "truth_good_Zh_from_N2_n",    "N_{W}", nBinsN, minBinN, maxBinN);
    m_good_Zh_from_N2_pt         = book(m_name, "truth_good_Zh_from_N2_pt",   "Z/h p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_good_Zh_from_N2_pt_s       = book(m_name, "truth_good_Zh_from_N2_pt_s", "Z/h p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_good_Zh_from_N2_pt_l       = book(m_name, "truth_good_Zh_from_N2_pt_l", "Z/h p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
    m_good_Zh_from_N2_eta        = book(m_name, "truth_good_Zh_from_N2_eta",  "Z/h #eta", nBinsEta, minBinEta, maxBinEta);
    m_good_Zh_from_N2_phi        = book(m_name, "truth_good_Zh_from_N2_phi",  "Z/h #phi",nBinsPhi, minBinPhi, maxBinPhi);
    m_good_Zh_from_N2_m          = book(m_name, "truth_good_Zh_from_N2_m",    "Z/h m [GeV]", nBinsPt, minBinPt, maxBinPt_s);

    m_good_W_Zh_dEta             = book(m_name, "truth_good_W_Zh_dEta",       "|#Delta#eta(W, Z/h)|", nBinsDR, minBinDR, maxBinDR);
    m_good_W_Zh_dPhi             = book(m_name, "truth_good_W_Zh_dPhi",       "|#Delta#phi(W, Z/h)|", nBinsDR, minBinDR, maxBinDR);
    m_good_W_Zh_dR               = book(m_name, "truth_good_W_Zh_dR",         "#DeltaR(W, Z/h)", nBinsDR, minBinDR, maxBinDR);
    m_good_W_decays_pt           = book(m_name, "truth_good_W_decays_pt",     "b/#bar{b} p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_good_W_decays_pt1          = book(m_name, "truth_good_W_decays_pt1",    "Leading b/#bar{b} p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_good_W_decays_pt2          = book(m_name, "truth_good_W_decays_pt2",    "Subleading b/#bar{b} p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_good_W_decays_dEta         = book(m_name, "truth_good_W_decays_dEta",   "|#Delta#eta| q#bar{q}", nBinsDR, minBinDR, maxBinDR);
    m_good_W_decays_dPhi         = book(m_name, "truth_good_W_decays_dPhi",   "|#Delta#phi| q#bar{q}", nBinsDR, minBinDR, maxBinDR);
    m_good_W_decays_dR           = book(m_name, "truth_good_W_decays_dR",     "#DeltaR q#bar{q}", nBinsDR, minBinDR, maxBinDR);
    m_good_Zh_decays_pt          = book(m_name, "truth_good_Zh_decays_pt",    "q/#bar{q} p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_good_Zh_decays_pt1         = book(m_name, "truth_good_Zh_decays_pt1",   "Leading q/#bar{q} p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_good_Zh_decays_pt2         = book(m_name, "truth_good_Zh_decays_pt2",   "Subleading q/#bar{q} p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_good_Zh_decays_dEta        = book(m_name, "truth_good_Zh_decays_dEta",  "|#Delta#eta| b#bar{b}", nBinsDR, minBinDR, maxBinDR);
    m_good_Zh_decays_dPhi        = book(m_name, "truth_good_Zh_decays_dPhi",  "|#Delta#phi| b#bar{b}", nBinsDR, minBinDR, maxBinDR);
    m_good_Zh_decays_dR          = book(m_name, "truth_good_Zh_decays_dR",    "#DeltaR b#bar{b}", nBinsDR, minBinDR, maxBinDR);

    m_good_W_decays_dR_vs_W_pt   = book(m_name, "truth_good_W_decays_dR_vs_W_pt", "W p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt, "#DeltaR q#bar{q}", nBinsDR, minBinDR, maxBinDR);
    m_good_Zh_decays_dR_vs_Zh_pt = book(m_name, "truth_good_Zh_decays_dR_vs_Zh_pt", "Z/h p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt, "#DeltaR b#bar{b}", nBinsDR, minBinDR, maxBinDR);

    m_good_W_decays_invmass      = book(m_name, "truth_good_W_decays_invmass", "M^{2}_{W} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_good_W_decays_invmass_s    = book(m_name, "truth_good_W_decays_invmass_s", "M^{2}_{W} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_good_Zh_decays_invmass     = book(m_name, "truth_good_Zh_decays_invmass", "M^{2}_{Z/h} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_good_Zh_decays_invmass_s   = book(m_name, "truth_good_Zh_decays_invmass_s", "M^{2}_{Z/h} [GeV]", nBinsPt, minBinPt, maxBinPt_s);

    m_good_MET                   = book(m_name, "truth_good_MET", "MET [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_good_MET_s                 = book(m_name, "truth_good_MET_s", "MET [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_good_MET_l                 = book(m_name, "truth_good_MET_l", "MET [GeV]", nBinsPt, minBinPt, maxBinPt_l);

    m_good_diboson_pt            = book(m_name, "truth_good_diboson_pt", "di-boson p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_good_diboson_pt_s          = book(m_name, "truth_good_diboson_pt_s", "di-boson p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_good_diboson_pt_l          = book(m_name, "truth_good_diboson_pt_l", "di-boson p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
    m_good_diboson_mt            = book(m_name, "truth_good_diboson_mt", "di-boson m_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_good_diboson_mt_s          = book(m_name, "truth_good_diboson_mt_s", "di-boson m_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_good_diboson_mt_l          = book(m_name, "truth_good_diboson_mt_l", "di-boson m_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
    m_good_diboson_invmass       = book(m_name, "truth_good_diboson_invmass", "M^{2} m_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
    m_good_diboson_invmass_s     = book(m_name, "truth_good_diboson_invmass_s", "M^{2} m_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
    m_good_diboson_invmass_l     = book(m_name, "truth_good_diboson_invmass_l", "M^{2} m_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);

    m_good_diboson_MET_dEta      = book(m_name, "truth_good_diboson_MET_dEta", "#Delta#eta(di-boson, MET)", nBinsDR, minBinDR, maxBinDR);
    m_good_diboson_MET_dPhi      = book(m_name, "truth_good_diboson_MET_dPhi", "#Delta#phi(di-boson, MET)", nBinsDR, minBinDR, maxBinDR);
    m_good_diboson_MET_dR        = book(m_name, "truth_good_diboson_MET_dR", "#DeltaR(di-boson, MET)", nBinsDR, minBinDR, maxBinDR);

    m_good_W_MET_dEta            = book(m_name, "truth_good_W_MET_dEta", "#Delta#eta(W, MET)", nBinsDR, minBinDR, maxBinDR);
    m_good_W_MET_dPhi            = book(m_name, "truth_good_W_MET_dPhi", "#Delta#phi(W, MET)", nBinsDR, minBinDR, maxBinDR);
    m_good_W_MET_dR              = book(m_name, "truth_good_W_MET_dR", "#DeltaR(W, MET)", nBinsDR, minBinDR, maxBinDR);

    m_good_Zh_MET_dEta           = book(m_name, "truth_good_Zh_MET_dEta", "#Delta#eta(Z/h, MET)", nBinsDR, minBinDR, maxBinDR);
    m_good_Zh_MET_dPhi           = book(m_name, "truth_good_Zh_MET_dPhi", "#Delta#phi(Z/h, MET)", nBinsDR, minBinDR, maxBinDR);
    m_good_Zh_MET_dR             = book(m_name, "truth_good_Zh_MET_dR", "#DeltaR(Z/h, MET)", nBinsDR, minBinDR, maxBinDR);

  }

  m_jet_n_nocut       = book(m_name, "jet_n_nocut",       "N_{jet}", nBinsN_l, minBinN_l, maxBinN_l);
  m_jet_n             = book(m_name, "jet_n",             "N_{jet}", nBinsN_l, minBinN_l, maxBinN_l);
  m_jet_pt            = book(m_name, "jet_pt",            "jet p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt);
  m_jet_pt_s          = book(m_name, "jet_pt_s",          "jet p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_s);
  m_jet_pt_l          = book(m_name, "jet_pt_l",          "jet p_{T} [GeV]", nBinsPt, minBinPt, maxBinPt_l);
  m_jet_eta           = book(m_name, "jet_eta",           "jet #eta", nBinsEta, minBinEta, maxBinEta);
  m_jet_phi           = book(m_name, "jet_phi",           "jet #phi",nBinsPhi, minBinPhi, maxBinPhi);
  m_jet_m             = book(m_name, "jet_m",             "jet m [GeV]", 150, 0, 150);
  m_jet_m_l           = book(m_name, "jet_m_l",           "jet m [GeV]", 100, 0, 1000);

  return StatusCode::SUCCESS;
}

StatusCode TruthHists::execute( const xAOD::TruthParticleContainer* truths, const xAOD::JetContainer* jets, float eventWeight) {

  if (truths != nullptr) {

    // Number of truth particle types per event (filled in the loop over truth partons below)
    m_truth_n_nocut -> Fill(truths->size());
    m_ntruth = 0;
    m_ne = 0;
    m_nmu = 0;
    m_ntau = 0;
    m_nlepton = 0;
    m_nt = 0;
    m_nb = 0;
    m_nquark = 0;
    m_nZ = 0;
    m_nW = 0;
    m_nh = 0;
    m_nC1 = 0;
    m_nN1 = 0;
    m_nN2 = 0;

    // Loop over all truth particles and save information that we want
    // (filling the number of event variables above and vectors with relevant particles) 
    xAOD::TruthParticleContainer::const_iterator truth_itr = truths->begin();
    xAOD::TruthParticleContainer::const_iterator truth_end = truths->end();
    for( ; truth_itr != truth_end; ++truth_itr) {
      RETURN_CHECK("TruthHists::execute()", this->execute( (*truth_itr), eventWeight), "");
    }

    // number of different particle species (filled in the loop above)
    m_truth_n      -> Fill(m_ntruth);
    if (m_fillLeptons) {
      m_e_n       -> Fill(m_ne);
      m_mu_n      -> Fill(m_nmu);
      m_tau_n     -> Fill(m_ntau);
      m_lepton_n  -> Fill(m_nlepton);
    }
    if (m_fillQuarks) {
      m_t_n       -> Fill(m_nt);
      m_b_n       -> Fill(m_nb);
      m_quark_n   -> Fill(m_nquark);
    }
    if (m_fillBosons) {
      m_Z_n       -> Fill(m_nZ);
      m_W_n       -> Fill(m_nW);
      m_h_n       -> Fill(m_nh);
    }
    if (m_fillSUSY) {
      m_C1_n      -> Fill(m_nC1);
      m_N1_n      -> Fill(m_nN1);
      m_N2_n      -> Fill(m_nN2);
    }
  }
  
  if (jets != nullptr) {

    m_jet_n_nocut -> Fill(jets->size());
    m_njet = 0;

    // Loop over truth jets
    xAOD::JetContainer::const_iterator jet_itr = jets->begin();
    xAOD::JetContainer::const_iterator jet_end = jets->end();
    for( ; jet_itr != jet_end; ++jet_itr) {
      RETURN_CHECK("TruthHists::execute()", this->execute( (*jet_itr), eventWeight), "");
    }

    m_truth_n -> Fill(m_njet);
  }

  // kinematic plots for SUSY and di-boson decay products
  if (truths != nullptr && m_fillSubstructure) {

    if (m_C1.size() > 0 && m_N2.size() > 0) {

      float C1_N2_dPhi = fabs(m_C1[0]->phi() - m_N2[0]->phi());
      if (C1_N2_dPhi > TMath::Pi()) C1_N2_dPhi = 2*TMath::Pi() - C1_N2_dPhi;
      float C1_N2_dEta = fabs(m_C1[0]->eta() - m_N2[0]->eta());
      float C1_N2_dR = m_C1[0]->p4().DeltaR( m_N2[0]->p4());
      m_good_C1_N2_dPhi -> Fill(C1_N2_dPhi, eventWeight);
      m_good_C1_N2_dEta -> Fill(C1_N2_dEta, eventWeight);
      m_good_C1_N2_dR   -> Fill(C1_N2_dR, eventWeight);

      m_good_C1_n -> Fill(m_C1.size(), 1.0);
      m_good_C1_pt_s -> Fill(m_C1[0]->pt()/1e3, eventWeight);
      m_good_C1_pt -> Fill(m_C1[0]->pt()/1e3, eventWeight);
      m_good_C1_pt_l -> Fill(m_C1[0]->pt()/1e3, eventWeight);
      m_good_C1_eta -> Fill(m_C1[0]->eta(), eventWeight);
      m_good_C1_phi -> Fill(m_C1[0]->phi(), eventWeight);
      m_good_C1_m -> Fill(m_C1[0]->m()/1e3, eventWeight);
      m_good_N2_n -> Fill(m_N2.size(), 1.0);
      m_good_N2_pt_s -> Fill(m_N2[0]->pt()/1e3, eventWeight);
      m_good_N2_pt -> Fill(m_N2[0]->pt()/1e3, eventWeight);
      m_good_N2_pt_l -> Fill(m_N2[0]->pt()/1e3, eventWeight);
      m_good_N2_eta -> Fill(m_N2[0]->eta(), eventWeight);
      m_good_N2_phi -> Fill(m_N2[0]->phi(), eventWeight);
      m_good_N2_m -> Fill(m_N2[0]->m()/1e3, eventWeight);
    }

    if (m_N1_from_C1.size() > 0 && m_W_from_C1.size() > 0) {

      float dEta_N1_W = fabs(m_N1_from_C1[0]->eta() - m_W_from_C1[0]->eta());
      m_good_N1_W_dEta -> Fill(dEta_N1_W, eventWeight);
      float dPhi_N1_W = fabs(m_N1_from_C1[0]->phi() - m_W_from_C1[0]->phi());
      if (dPhi_N1_W > TMath::Pi()) dPhi_N1_W = fabs(2*TMath::Pi() - dPhi_N1_W);
      m_good_N1_W_dPhi -> Fill(dPhi_N1_W, eventWeight);
      m_good_N1_W_dR -> Fill(m_N1_from_C1[0]->p4().DeltaR(m_W_from_C1[0]->p4()), eventWeight);

      m_good_N1_from_C1_n -> Fill(m_N1_from_C1.size(), 1.0);
      m_good_N1_from_C1_pt_s -> Fill(m_N1_from_C1[0]->pt()/1e3);
      m_good_N1_from_C1_pt -> Fill(m_N1_from_C1[0]->pt()/1e3);
      m_good_N1_from_C1_pt_l -> Fill(m_N1_from_C1[0]->pt()/1e3);
      m_good_N1_from_C1_eta -> Fill(m_N1_from_C1[0]->eta(), eventWeight);
      m_good_N1_from_C1_phi -> Fill(m_N1_from_C1[0]->phi(), eventWeight);
      m_good_N1_from_C1_m -> Fill(m_N1_from_C1[0]->m()/1e3, eventWeight);
      m_good_W_from_C1_n -> Fill(m_W_from_C1.size(), 1.0);
      m_good_W_from_C1_pt_s -> Fill(m_W_from_C1[0]->pt()/1e3);
      m_good_W_from_C1_pt -> Fill(m_W_from_C1[0]->pt()/1e3);
      m_good_W_from_C1_pt_l -> Fill(m_W_from_C1[0]->pt()/1e3);
      m_good_W_from_C1_eta -> Fill(m_W_from_C1[0]->eta(), eventWeight);
      m_good_W_from_C1_phi -> Fill(m_W_from_C1[0]->phi(), eventWeight);
      m_good_W_from_C1_m -> Fill(m_W_from_C1[0]->m()/1e3, eventWeight);
    }

    if (m_N1_from_N2.size() > 0 && m_Zh_from_N2.size() > 0) {

      float dEta_N1_Zh = fabs(m_N1_from_N2[0]->eta() - m_Zh_from_N2[0]->eta());
      m_good_N1_Zh_dEta -> Fill(dEta_N1_Zh, eventWeight);
      float dPhi_N1_Zh = fabs(m_N1_from_N2[0]->phi() - m_Zh_from_N2[0]->phi());
      if (dPhi_N1_Zh > TMath::Pi()) dPhi_N1_Zh = fabs(2*TMath::Pi() - dPhi_N1_Zh);
      m_good_N1_Zh_dPhi -> Fill(dPhi_N1_Zh, eventWeight);
      m_good_N1_Zh_dR -> Fill(m_N1_from_N2[0]->p4().DeltaR(m_Zh_from_N2[0]->p4()), eventWeight);

      m_good_N1_from_N2_n -> Fill(m_N1_from_N2.size(), 1.0);
      m_good_N1_from_N2_pt_s -> Fill(m_N1_from_N2[0]->pt()/1e3);
      m_good_N1_from_N2_pt -> Fill(m_N1_from_N2[0]->pt()/1e3);
      m_good_N1_from_N2_pt_l -> Fill(m_N1_from_N2[0]->pt()/1e3);
      m_good_N1_from_N2_eta -> Fill(m_N1_from_N2[0]->eta(), eventWeight);
      m_good_N1_from_N2_phi -> Fill(m_N1_from_N2[0]->phi(), eventWeight);
      m_good_N1_from_N2_m -> Fill(m_N1_from_N2[0]->m()/1e3, eventWeight);
      m_good_Zh_from_N2_n -> Fill(m_Zh_from_N2.size(), 1.0);
      m_good_Zh_from_N2_pt_s -> Fill(m_Zh_from_N2[0]->pt()/1e3);
      m_good_Zh_from_N2_pt -> Fill(m_Zh_from_N2[0]->pt()/1e3);
      m_good_Zh_from_N2_pt_l -> Fill(m_Zh_from_N2[0]->pt()/1e3);
      m_good_Zh_from_N2_eta -> Fill(m_Zh_from_N2[0]->eta(), eventWeight);
      m_good_Zh_from_N2_phi -> Fill(m_Zh_from_N2[0]->phi(), eventWeight);
      m_good_Zh_from_N2_m -> Fill(m_Zh_from_N2[0]->m()/1e3, eventWeight);
    }

    if (m_W_from_C1.size() > 0 && m_Zh_from_N2.size() > 0) {
      m_good_W_Zh_dR -> Fill(m_W_from_C1[0]->p4().DeltaR(m_Zh_from_N2[0]->p4()), eventWeight);
    }

    if (m_C1_W_decays.size() > 1){
      if (m_C1_W_decays[0]->pt() > m_C1_W_decays[1]->pt()) {
        m_good_W_decays_pt1 -> Fill(m_C1_W_decays[0]->pt()/1e3, eventWeight);
        m_good_W_decays_pt2 -> Fill(m_C1_W_decays[1]->pt()/1e3, eventWeight);
      } else {
        m_good_W_decays_pt1 -> Fill(m_C1_W_decays[1]->pt()/1e3, eventWeight);
        m_good_W_decays_pt2 -> Fill(m_C1_W_decays[0]->pt()/1e3, eventWeight);
      }
      m_good_W_decays_pt -> Fill(m_C1_W_decays[0]->pt()/1e3, eventWeight);
      m_good_W_decays_pt -> Fill(m_C1_W_decays[1]->pt()/1e3, eventWeight);

      float dEta_W_decays = fabs(m_C1_W_decays[0]->eta() - m_C1_W_decays[1]->eta());
      m_good_W_decays_dEta -> Fill(dEta_W_decays, eventWeight);
      float dPhi_W_MET = fabs(m_C1_W_decays[0]->phi() - m_C1_W_decays[1]->phi());
      if (dPhi_W_MET > TMath::Pi()) dPhi_W_MET = fabs(2*TMath::Pi() - dPhi_W_MET);
      m_good_W_MET_dPhi -> Fill(dPhi_W_MET, eventWeight);
      m_good_W_decays_dR -> Fill(m_C1_W_decays[0]->p4().DeltaR(m_C1_W_decays[1]->p4()), eventWeight);
      if ( m_W_from_C1.size() > 0){
        m_good_W_decays_dR_vs_W_pt -> Fill(m_W_from_C1[0]->pt()/1e3, m_C1_W_decays[0]->p4().DeltaR(m_C1_W_decays[1]->p4()), eventWeight);
      }

      // invariant mass of W decay products
      float W_invmass = (m_C1_W_decays[0]->p4()+m_C1_W_decays[1]->p4()).M()/1e3;
      m_good_W_decays_invmass -> Fill(W_invmass, eventWeight);
      m_good_W_decays_invmass_s -> Fill(W_invmass, eventWeight);
    }

    if (m_N2_Zh_decays.size() > 1) {
      if (m_N2_Zh_decays[0]->pt() > m_N2_Zh_decays[1]->pt()) {
        m_good_Zh_decays_pt1 -> Fill(m_N2_Zh_decays[0]->pt()/1e3, eventWeight);
        m_good_Zh_decays_pt2 -> Fill(m_N2_Zh_decays[1]->pt()/1e3, eventWeight);
      } else {
        m_good_Zh_decays_pt1 -> Fill(m_N2_Zh_decays[1]->pt()/1e3, eventWeight);
        m_good_Zh_decays_pt2 -> Fill(m_N2_Zh_decays[0]->pt()/1e3, eventWeight);
      }
      m_good_Zh_decays_pt -> Fill(m_N2_Zh_decays[0]->pt()/1e3, eventWeight);
      m_good_Zh_decays_pt -> Fill(m_N2_Zh_decays[1]->pt()/1e3, eventWeight);

      float dEta_Zh_decays = fabs(m_N2_Zh_decays[0]->eta() - m_N2_Zh_decays[1]->eta());
      m_good_Zh_decays_dEta -> Fill(dEta_Zh_decays, eventWeight);
      float dPhi_Zh_MET = fabs(m_N2_Zh_decays[0]->phi() - m_N2_Zh_decays[1]->phi());
      if (dPhi_Zh_MET > TMath::Pi()) dPhi_Zh_MET = fabs(2*TMath::Pi() - dPhi_Zh_MET);
      m_good_Zh_MET_dPhi -> Fill(dPhi_Zh_MET, eventWeight);
      m_good_Zh_decays_dR -> Fill(m_N2_Zh_decays[0]->p4().DeltaR(m_N2_Zh_decays[1]->p4()), eventWeight);
      if ( m_Zh_from_N2.size() > 0){
        m_good_Zh_decays_dR_vs_Zh_pt -> Fill(m_Zh_from_N2[0]->pt()/1e3, m_N2_Zh_decays[0]->p4().DeltaR(m_N2_Zh_decays[1]->p4()), eventWeight);
      }

      // invariant mass of Zh decay products
      float Zh_invmass = (m_N2_Zh_decays[0]->p4()+m_N2_Zh_decays[1]->p4()).M()/1e3;
      m_good_Zh_decays_invmass -> Fill(Zh_invmass, eventWeight);
      m_good_Zh_decays_invmass_s -> Fill(Zh_invmass, eventWeight);
    }

    // MET (combining the N1 four vectors
    if (m_N1_from_C1.size() > 0 && m_N1_from_N2.size() > 0) {
      TLorentzVector MET = m_N1_from_C1[0]->p4()+m_N1_from_N2[0]->p4();
      m_good_MET -> Fill(MET.Pt()/1e3, eventWeight);
      m_good_MET_s -> Fill(MET.Pt()/1e3, eventWeight);
      m_good_MET_l -> Fill(MET.Pt()/1e3, eventWeight);

      if (m_W_from_C1.size() > 0 && m_Zh_from_N2.size() > 0) {
        TLorentzVector diboson = m_W_from_C1[0]->p4()+m_Zh_from_N2[0]->p4();
        m_good_diboson_pt -> Fill(diboson.Pt()/1e3, eventWeight);
        m_good_diboson_pt_s -> Fill(diboson.Pt()/1e3, eventWeight);
        m_good_diboson_pt_l -> Fill(diboson.Pt()/1e3, eventWeight);
        m_good_diboson_mt -> Fill(diboson.Mt()/1e3, eventWeight);
        m_good_diboson_mt_s -> Fill(diboson.Mt()/1e3, eventWeight);
        m_good_diboson_mt_l -> Fill(diboson.Mt()/1e3, eventWeight);
        m_good_diboson_invmass -> Fill(diboson.M()/1e3, eventWeight);
        m_good_diboson_invmass_s -> Fill(diboson.M()/1e3, eventWeight);
        m_good_diboson_invmass_l -> Fill(diboson.M()/1e3, eventWeight);

        float dEta_diboson_MET = fabs(diboson.Eta() - MET.Eta());
        m_good_diboson_MET_dEta -> Fill(dEta_diboson_MET, eventWeight);
        float dPhi_diboson_MET = fabs(diboson.Phi() - MET.Phi());
        if (dPhi_diboson_MET > TMath::Pi()) dPhi_diboson_MET = fabs(2*TMath::Pi() - dPhi_diboson_MET);
        m_good_diboson_MET_dPhi -> Fill(dPhi_diboson_MET, eventWeight);
        m_good_diboson_MET_dR -> Fill(diboson.DeltaR(MET), eventWeight);

        float dEta_W_MET = fabs(m_W_from_C1[0]->eta() - MET.Eta());
        m_good_W_MET_dEta -> Fill(dEta_W_MET, eventWeight);
        float dPhi_W_MET = fabs(m_W_from_C1[0]->phi() - MET.Phi());
        if (dPhi_W_MET > TMath::Pi()) dPhi_W_MET = fabs(2*TMath::Pi() - dPhi_W_MET);
        m_good_W_MET_dPhi -> Fill(dPhi_W_MET, eventWeight);
        m_good_W_MET_dR -> Fill(m_W_from_C1[0]->p4().DeltaR(MET), eventWeight);

        float dEta_Zh_MET = fabs(m_Zh_from_N2[0]->eta() - MET.Eta());
        m_good_Zh_MET_dEta -> Fill(dEta_Zh_MET, eventWeight);
        float dPhi_Zh_MET = fabs(m_Zh_from_N2[0]->phi() - MET.Phi());
        if (dPhi_Zh_MET > TMath::Pi()) dPhi_Zh_MET = fabs(2*TMath::Pi() - dPhi_Zh_MET);
        m_good_Zh_MET_dPhi -> Fill(dPhi_Zh_MET, eventWeight);
        m_good_Zh_MET_dR -> Fill(m_Zh_from_N2[0]->p4().DeltaR(MET), eventWeight);
      }
    }
  }

  // clean up temporary event particle containers
  // if (m_C1.size() > 0) for (auto v : m_C1) delete v;
  // if (m_N2.size() > 0) for (auto v : m_N2) delete v;
  // if (m_N1_from_C1.size() > 0) for (auto v : m_N1_from_C1) delete v;
  // if (m_W_from_C1.size() > 0) for (auto v : m_W_from_C1) delete v;
  // if (m_N1_from_N2.size() > 0) for (auto v : m_N1_from_N2) delete v;
  // if (m_Zh_from_N2.size() > 0) for (auto v : m_Zh_from_N2) delete v;
  // if (m_C1_W_decays.size() > 0) for (auto v : m_C1_W_decays) delete v;
  // if (m_N2_Zh_decays.size() > 0) for (auto v : m_C1_W_decays) delete v;

  m_C1.clear();
  m_N2.clear();
  m_N1_from_C1.clear();
  m_W_from_C1.clear();
  m_N1_from_N2.clear();
  m_Zh_from_N2.clear();
  m_C1_W_decays.clear();
  m_N2_Zh_decays.clear();

  return StatusCode::SUCCESS;
}

StatusCode TruthHists::execute( const xAOD::TruthParticle* truth, float eventWeight) {

  float pt  = truth->pt()/1e3;
  float eta = truth->eta();
  float phi = truth->phi();
  float m   = truth->m()/1e3;
  int pdgId = truth->pdgId();

  // truth cuts
  if (pt < m_truth_ptMinCut) return StatusCode::SUCCESS;
  if (fabs(eta) > m_truth_etaAbsMaxCut) return StatusCode::SUCCESS;

  m_ntruth++;
  m_truth_pt_s          -> Fill(pt,    eventWeight);
  m_truth_pt            -> Fill(pt,    eventWeight);
  m_truth_pt_l          -> Fill(pt,    eventWeight);
  m_truth_eta           -> Fill(eta,   eventWeight);
  m_truth_phi           -> Fill(phi,   eventWeight);
  m_truth_m             -> Fill(m,     eventWeight);
  m_truth_m_l           -> Fill(m,     eventWeight);
  m_truth_pdgId         -> Fill(pdgId, eventWeight);
  m_truth_pdgId_susy    -> Fill(fabs(pdgId), eventWeight);
  m_truth_pdgId_susy_p  -> Fill(pdgId, eventWeight);
  m_truth_pdgId_susy_n  -> Fill(pdgId, eventWeight);

  if (m_fillLeptons) {
    if (fabs(pdgId) == 11) {
      m_ne++;
      m_e_pt_s          -> Fill(pt,    eventWeight);
      m_e_pt            -> Fill(pt,    eventWeight);
      m_e_pt_l          -> Fill(pt,    eventWeight);
      m_e_eta           -> Fill(eta,   eventWeight);
      m_e_phi           -> Fill(phi,   eventWeight);
      m_e_m             -> Fill(m,     eventWeight);
    } else if (fabs(pdgId) == 13) {
      m_nmu++;
      m_mu_pt_s         -> Fill(pt,    eventWeight);
      m_mu_pt           -> Fill(pt,    eventWeight);
      m_mu_pt_l         -> Fill(pt,    eventWeight);
      m_mu_eta          -> Fill(eta,   eventWeight);
      m_mu_phi          -> Fill(phi,   eventWeight);
      m_mu_m            -> Fill(m,     eventWeight);
    } else if (fabs(pdgId) == 16) {
      m_ntau++;
      m_tau_pt_s        -> Fill(pt,    eventWeight);
      m_tau_pt          -> Fill(pt,    eventWeight);
      m_tau_pt_l        -> Fill(pt,    eventWeight);
      m_tau_eta         -> Fill(eta,   eventWeight);
      m_tau_phi         -> Fill(phi,   eventWeight);
      m_tau_m           -> Fill(m,     eventWeight);
    } else if (fabs(pdgId) >= 11 && fabs(pdgId) <= 16) {
      m_nlepton++;
      m_lepton_pt_s     -> Fill(pt,    eventWeight);
      m_lepton_pt       -> Fill(pt,    eventWeight);
      m_lepton_pt_l     -> Fill(pt,    eventWeight);
      m_lepton_eta      -> Fill(eta,   eventWeight);
      m_lepton_phi      -> Fill(phi,   eventWeight);
      m_lepton_m        -> Fill(m,     eventWeight);
    }
  }

  if (m_fillQuarks) {
    if (fabs(pdgId) == 6) {
      m_nt++;
      m_t_pt_s          -> Fill(pt,    eventWeight);
      m_t_pt            -> Fill(pt,    eventWeight);
      m_t_pt_l          -> Fill(pt,    eventWeight);
      m_t_eta           -> Fill(eta,   eventWeight);
      m_t_phi           -> Fill(phi,   eventWeight);
      m_t_m             -> Fill(m,     eventWeight);
    } else if (fabs(pdgId) == 5) {
      m_nb++;
      m_b_pt_s          -> Fill(pt,    eventWeight);
      m_b_pt            -> Fill(pt,    eventWeight);
      m_b_pt_l          -> Fill(pt,    eventWeight);
      m_b_eta           -> Fill(eta,   eventWeight);
      m_b_phi           -> Fill(phi,   eventWeight);
      m_b_m             -> Fill(m,     eventWeight);
    } else if (fabs(pdgId) <= 5) {
      m_nquark++;
      m_quark_pt_s      -> Fill(pt,    eventWeight);
      m_quark_pt        -> Fill(pt,    eventWeight);
      m_quark_pt_l      -> Fill(pt,    eventWeight);
      m_quark_eta       -> Fill(eta,   eventWeight);
      m_quark_phi       -> Fill(phi,   eventWeight);
      m_quark_m         -> Fill(m,     eventWeight);
    }
  }

  if (m_fillBosons) {
    if (fabs(pdgId) == 23) {
      m_nZ++;
      m_Z_pt_s          -> Fill(pt,    eventWeight);
      m_Z_pt            -> Fill(pt,    eventWeight);
      m_Z_pt_l          -> Fill(pt,    eventWeight);
      m_Z_eta           -> Fill(eta,   eventWeight);
      m_Z_phi           -> Fill(phi,   eventWeight);
      m_Z_m             -> Fill(m,     eventWeight);
      m_Z_child_n   -> Fill(truth->nChildren(), eventWeight);
      for( unsigned int i=0; i < truth->nChildren(); i++) {
        m_Z_child_pdgId  -> Fill(truth->child(i)->pdgId(), eventWeight);
      }
    } else if (fabs(pdgId) == 24) {
      m_nW++;
      m_W_pt_s          -> Fill(pt,    eventWeight);
      m_W_pt            -> Fill(pt,    eventWeight);
      m_W_pt_l          -> Fill(pt,    eventWeight);
      m_W_eta           -> Fill(eta,   eventWeight);
      m_W_phi           -> Fill(phi,   eventWeight);
      m_W_m             -> Fill(m,     eventWeight);
      m_W_child_n   -> Fill(truth->nChildren(), eventWeight);
      for( unsigned int i=0; i < truth->nChildren(); i++) {
        m_W_child_pdgId -> Fill(truth->child(i)->pdgId(), eventWeight);
      }
    } else if (fabs(pdgId) == 25) {
      m_nh++;
      m_h_pt_s          -> Fill(pt,    eventWeight);
      m_h_pt            -> Fill(pt,    eventWeight);
      m_h_pt_l          -> Fill(pt,    eventWeight);
      m_h_eta           -> Fill(eta,   eventWeight);
      m_h_phi           -> Fill(phi,   eventWeight);
      m_h_m             -> Fill(m,     eventWeight);
      m_h_child_n   -> Fill(truth->nChildren(), eventWeight);
      for( unsigned int i=0; i < truth->nChildren(); i++) {
        m_h_child_pdgId  -> Fill(truth->child(i)->pdgId(), eventWeight);
      }
    }
  }

  if (m_fillSUSY) {
    if (fabs(pdgId) == 1000024) {
      m_nC1++;
      m_C1_pt_s         -> Fill(pt,    eventWeight);
      m_C1_pt           -> Fill(pt,    eventWeight);
      m_C1_pt_l         -> Fill(pt,    eventWeight);
      m_C1_eta          -> Fill(eta,   eventWeight);
      m_C1_phi          -> Fill(phi,   eventWeight);
      m_C1_m            -> Fill(m,     eventWeight);
      m_C1_child_n      -> Fill(truth->nChildren(), eventWeight);
      if (truth->nChildren() == 2){ 
        if (((truth->child(0)->absPdgId() == 1000022) && (truth->child(1)->absPdgId() == 24)) || 
            ((truth->child(1)->absPdgId() == 1000022) && (truth->child(0)->absPdgId() == 24))){
          m_C1.push_back(truth);
          for( unsigned int i=0; i < truth->nChildren(); i++) {
            const xAOD::TruthParticle* child = truth->child(i);
            int child_pdgId = child->pdgId();
            m_C1_child_pdgId -> Fill(child_pdgId, eventWeight);
            m_C1_child_pdgId_susy -> Fill(child_pdgId, eventWeight);
            if (fabs(child_pdgId) == 1000022) {
              m_N1_from_C1.push_back(child);
            } else if (fabs(child_pdgId) == 24) {
              m_W_from_C1.push_back(child);
              for( unsigned int j=0; j < child->nChildren(); j++) {
                m_C1_W_decays.push_back(child->child(j));
              }
            } 
          }
        }
      }
    } else if (fabs(pdgId) == 1000023) {
      m_nN2++;
      m_N2_pt_s         -> Fill(pt,    eventWeight);
      m_N2_pt           -> Fill(pt,    eventWeight);
      m_N2_pt_l         -> Fill(pt,    eventWeight);
      m_N2_eta          -> Fill(eta,   eventWeight);
      m_N2_phi          -> Fill(phi,   eventWeight);
      m_N2_m            -> Fill(m,     eventWeight);
      m_N2_child_n      -> Fill(truth->nChildren(), eventWeight);
      if (truth->nChildren() == 2){ 
        if (((truth->child(0)->absPdgId() == 1000022) && ((truth->child(1)->absPdgId() == 23) || (truth->child(1)->absPdgId() == 25))) ||
            ((truth->child(1)->absPdgId() == 1000022) && ((truth->child(0)->absPdgId() == 23) || (truth->child(0)->absPdgId() == 25)))){
          m_N2.push_back(truth);
          for( unsigned int i=0; i < truth->nChildren(); i++) {
            const xAOD::TruthParticle* child = truth->child(i);
            int child_pdgId = child->pdgId();
            m_N2_child_pdgId -> Fill(child_pdgId, eventWeight);
            m_N2_child_pdgId_susy -> Fill(child_pdgId, eventWeight);
            if (fabs(child_pdgId) == 1000022) {
              m_N1_from_N2.push_back(child);
            } else if (fabs(child_pdgId) == 23 || fabs(child_pdgId) == 25) {
              m_Zh_from_N2.push_back(child);
              for( unsigned int j=0; j < child->nChildren(); j++) {
                m_N2_Zh_decays.push_back(child->child(j));
              }
            }
          }
        }
      }
    } else if (fabs(pdgId) == 1000022) {
      m_nN1++;
      m_N1_pt_s         -> Fill(pt,    eventWeight);
      m_N1_pt           -> Fill(pt,    eventWeight);
      m_N1_pt_l         -> Fill(pt,    eventWeight);
      m_N1_eta          -> Fill(eta,   eventWeight);
      m_N1_phi          -> Fill(phi,   eventWeight);
      m_N1_m            -> Fill(m,     eventWeight);
      m_N1_child_n      -> Fill(truth->nChildren(), eventWeight);
      // just a sanity check, since N1 should not decay (it's stable and invisible)
      for( unsigned int i=0; i < truth->nChildren(); i++) {
        m_N1_child_pdgId -> Fill(truth->child(i)->pdgId(), eventWeight);
      }
    }
  }

  return StatusCode::SUCCESS;
}

StatusCode TruthHists::execute( const xAOD::Jet* jet, float eventWeight) {

  float pt  = jet->pt()/1e3;
  float eta = jet->eta();
  float phi = jet->phi();
  float m   = jet->m()/1e3;

  // jet cuts
  if (pt < m_jet_ptMinCut) return StatusCode::SUCCESS;
  if (fabs(eta) > m_bJet_etaAbsMaxCut) return StatusCode::SUCCESS; // TODO Make this cut only on b-tagged jets

  m_njet++;
  m_jet_pt_s          -> Fill(pt,    eventWeight);
  m_jet_pt            -> Fill(pt,    eventWeight);
  m_jet_pt_l          -> Fill(pt,    eventWeight);
  m_jet_eta           -> Fill(eta,   eventWeight);
  m_jet_phi           -> Fill(phi,   eventWeight);
  m_jet_m             -> Fill(m,     eventWeight);
  m_jet_m_l           -> Fill(m,     eventWeight);

}

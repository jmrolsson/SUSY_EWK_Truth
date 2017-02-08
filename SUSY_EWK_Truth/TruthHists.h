#ifndef SUSY_EWK_Truth_TruthHists_H
#define SUSY_EWK_Truth_TruthHists_H

#include "xAODAnaHelpers/HistogramManager.h"
#include <xAODTruth/TruthParticleContainer.h>

class TruthHists : public HistogramManager
{
  public:
    TruthHists(std::string name, std::string detailStr );
    ~TruthHists();

    StatusCode initialize();
    StatusCode execute( const xAOD::TruthParticleContainer* truths, float eventWeight );
    StatusCode execute( const xAOD::TruthParticle* truth, float eventWeight);
    using HistogramManager::book; // make other overloaded versions of book() to show up in subclass
    using HistogramManager::execute; // overload

  protected:
    // bools to control which histograms are filled
    bool m_fillLeptons; //!
    bool m_fillQuarks; //!
    bool m_fillBosons; //!
    bool m_fillSUSY; //!
    bool m_fillSubstructure; //!

  private:

    int m_ntruth; //!
    int m_ne; //!
    int m_nmu; //!
    int m_ntau; //!
    int m_nlepton; //!
    int m_nt; //!
    int m_nb; //!
    int m_nquark; //!
    int m_nZ; //!
    int m_nW; //!
    int m_nh; //!
    int m_nC1; //!
    int m_nN1; //!
    int m_nN2; //!

    std::vector<const xAOD::TruthParticle*> m_C1;
    std::vector<const xAOD::TruthParticle*> m_N2;
    std::vector<const xAOD::TruthParticle*> m_N1_from_C1;
    std::vector<const xAOD::TruthParticle*> m_W_from_C1;
    std::vector<const xAOD::TruthParticle*> m_N1_from_N2;
    std::vector<const xAOD::TruthParticle*> m_Zh_from_N2;

    std::vector<const xAOD::TruthParticle*> m_C1_W_decays;
    std::vector<const xAOD::TruthParticle*> m_N2_Zh_decays;

    TH1F* m_truth_n; //!
    TH1F* m_truth_pt; //!
    TH1F* m_truth_pt_s; //!
    TH1F* m_truth_pt_l; //!
    TH1F* m_truth_eta; //!
    TH1F* m_truth_phi; //!
    TH1F* m_truth_m; //!
    TH1F* m_truth_m_l; //!
    TH1F* m_truth_pdgId; //!
    TH1F* m_truth_pdgId_susy; //!
    TH1F* m_truth_pdgId_susy_p; //!
    TH1F* m_truth_pdgId_susy_n; //!

    TH1F* m_e_n; //!
    TH1F* m_e_pt; //!
    TH1F* m_e_pt_s; //!
    TH1F* m_e_pt_l; //!
    TH1F* m_e_eta; //!
    TH1F* m_e_phi; //!
    TH1F* m_e_m; //!
    TH1F* m_mu_n; //!
    TH1F* m_mu_pt; //!
    TH1F* m_mu_pt_s; //!
    TH1F* m_mu_pt_l; //!
    TH1F* m_mu_eta; //!
    TH1F* m_mu_phi; //!
    TH1F* m_mu_m; //!
    TH1F* m_tau_n; //!
    TH1F* m_tau_pt; //!
    TH1F* m_tau_pt_s; //!
    TH1F* m_tau_pt_l; //!
    TH1F* m_tau_eta; //!
    TH1F* m_tau_phi; //!
    TH1F* m_tau_m; //!
    TH1F* m_lepton_n; //!
    TH1F* m_lepton_pt; //!
    TH1F* m_lepton_pt_s; //!
    TH1F* m_lepton_pt_l; //!
    TH1F* m_lepton_eta; //!
    TH1F* m_lepton_phi; //!
    TH1F* m_lepton_m; //!

    TH1F* m_t_n; //!
    TH1F* m_t_pt; //!
    TH1F* m_t_pt_s; //!
    TH1F* m_t_pt_l; //!
    TH1F* m_t_eta; //!
    TH1F* m_t_phi; //!
    TH1F* m_t_m; //!
    TH1F* m_b_n; //!
    TH1F* m_b_pt; //!
    TH1F* m_b_pt_s; //!
    TH1F* m_b_pt_l; //!
    TH1F* m_b_eta; //!
    TH1F* m_b_phi; //!
    TH1F* m_b_m; //!
    TH1F* m_quark_n; //!
    TH1F* m_quark_pt; //!
    TH1F* m_quark_pt_s; //!
    TH1F* m_quark_pt_l; //!
    TH1F* m_quark_eta; //!
    TH1F* m_quark_phi; //!
    TH1F* m_quark_m; //!

    TH1F* m_Z_n; //!
    TH1F* m_Z_pt; //!
    TH1F* m_Z_pt_s; //!
    TH1F* m_Z_pt_l; //!
    TH1F* m_Z_eta; //!
    TH1F* m_Z_phi; //!
    TH1F* m_Z_m; //!
    TH1F* m_Z_child_n; //!
    TH1F* m_Z_child_pdgId; //!
    TH1F* m_W_n; //!
    TH1F* m_W_pt; //!
    TH1F* m_W_pt_s; //!
    TH1F* m_W_pt_l; //!
    TH1F* m_W_eta; //!
    TH1F* m_W_phi; //!
    TH1F* m_W_m; //!
    TH1F* m_W_child_n; //!
    TH1F* m_W_child_pdgId; //!
    TH1F* m_h_n; //!
    TH1F* m_h_pt; //!
    TH1F* m_h_pt_s; //!
    TH1F* m_h_pt_l; //!
    TH1F* m_h_eta; //!
    TH1F* m_h_phi; //!
    TH1F* m_h_m; //!
    TH1F* m_h_child_n; //!
    TH1F* m_h_child_pdgId; //!

    TH1F* m_C1_n; //!
    TH1F* m_C1_pt; //!
    TH1F* m_C1_pt_s; //!
    TH1F* m_C1_pt_l; //!
    TH1F* m_C1_eta; //!
    TH1F* m_C1_phi; //!
    TH1F* m_C1_m; //!
    TH1F* m_C1_child_n; //!
    TH1F* m_C1_child_pdgId; //!
    TH1F* m_C1_child_pdgId_susy; //!
    TH1F* m_N2_n; //!
    TH1F* m_N2_pt; //!
    TH1F* m_N2_pt_s; //!
    TH1F* m_N2_pt_l; //!
    TH1F* m_N2_eta; //!
    TH1F* m_N2_phi; //!
    TH1F* m_N2_m; //!
    TH1F* m_N2_child_n; //!
    TH1F* m_N2_child_pdgId; //!
    TH1F* m_N2_child_pdgId_susy; //!
    TH1F* m_N1_n; //!
    TH1F* m_N1_pt; //!
    TH1F* m_N1_pt_s; //!
    TH1F* m_N1_pt_l; //!
    TH1F* m_N1_eta; //!
    TH1F* m_N1_phi; //!
    TH1F* m_N1_m; //!
    TH1F* m_N1_child_n; //!
    TH1F* m_N1_child_pdgId; //!

    // Identified C1, N2 and their decay products
    TH1F* m_good_C1_N2_dPhi; //!
    TH1F* m_good_C1_N2_dEta; //!
    TH1F* m_good_C1_N2_dR; //!
    TH1F* m_good_C1_n; //!
    TH1F* m_good_C1_pt; //!
    TH1F* m_good_C1_pt_s; //!
    TH1F* m_good_C1_pt_l; //!
    TH1F* m_good_C1_eta; //!
    TH1F* m_good_C1_phi; //!
    TH1F* m_good_C1_m; //!
    TH1F* m_good_N2_n; //!
    TH1F* m_good_N2_pt; //!
    TH1F* m_good_N2_pt_s; //!
    TH1F* m_good_N2_pt_l; //!
    TH1F* m_good_N2_eta; //!
    TH1F* m_good_N2_phi; //!
    TH1F* m_good_N2_m; //!
    TH1F* m_good_N1_W_dR; //!
    TH1F* m_good_N1_from_C1_n; //!
    TH1F* m_good_N1_from_C1_pt; //!
    TH1F* m_good_N1_from_C1_pt_s; //!
    TH1F* m_good_N1_from_C1_pt_l; //!
    TH1F* m_good_N1_from_C1_eta; //!
    TH1F* m_good_N1_from_C1_phi; //!
    TH1F* m_good_N1_from_C1_m; //!
    TH1F* m_good_W_from_C1_n; //!
    TH1F* m_good_W_from_C1_pt; //!
    TH1F* m_good_W_from_C1_pt_s; //!
    TH1F* m_good_W_from_C1_pt_l; //!
    TH1F* m_good_W_from_C1_eta; //!
    TH1F* m_good_W_from_C1_phi; //!
    TH1F* m_good_W_from_C1_m; //!
    TH1F* m_good_N1_Zh_dR; //!
    TH1F* m_good_N1_from_N2_n; //!
    TH1F* m_good_N1_from_N2_pt; //!
    TH1F* m_good_N1_from_N2_pt_s; //!
    TH1F* m_good_N1_from_N2_pt_l; //!
    TH1F* m_good_N1_from_N2_eta; //!
    TH1F* m_good_N1_from_N2_phi; //!
    TH1F* m_good_N1_from_N2_m; //!
    TH1F* m_good_Zh_from_N2_n; //!
    TH1F* m_good_Zh_from_N2_pt; //!
    TH1F* m_good_Zh_from_N2_pt_s; //!
    TH1F* m_good_Zh_from_N2_pt_l; //!
    TH1F* m_good_Zh_from_N2_eta; //!
    TH1F* m_good_Zh_from_N2_phi; //!
    TH1F* m_good_Zh_from_N2_m; //!
    TH1F* m_good_W_Zh_dR; //!
    TH1F* m_good_W_decays_pt; //!
    TH1F* m_good_W_decays_pt1; //!
    TH1F* m_good_W_decays_pt2; //!
    TH1F* m_good_W_decays_dR; //!
    TH2F* m_good_W_decays_dR_vs_W_pt; //!
    TH1F* m_good_Zh_decays_pt; //!
    TH1F* m_good_Zh_decays_pt1; //!
    TH1F* m_good_Zh_decays_pt2; //!
    TH1F* m_good_Zh_decays_dR; //!
    TH2F* m_good_Zh_decays_dR_vs_Zh_pt; //!
};

#endif

# Truth studies for RunII SUSY EWK
# Joakim Olsson <joakim.olsson@cern.ch>
# 2017-02-07

# Baseline cuts
truth_ptMinCut = 20
truth_etaAbsMaxCut = 4.0
jet_ptMinCut = 30
bJet_etaAbsMaxCut = 2.8
min_n_jetsCut = 4;
min_n_bJetsCut = 1

from xAH_config import xAH_config
c = xAH_config()

''' Truth validation studies, no cuts '''
c.setalg("TruthHistsAlgo", {"m_name": "Truth_noCuts",
                            "m_truthContainerName": "TruthParticles",
                            "m_jetContainerName": "AntiKt4TruthJets",
                            "m_detailStr": "leptons quarks bosons susy substructure jets",
                            "m_debug": False})

''' Truth validation studies, baseline cuts '''
c.setalg("TruthHistsAlgo", {"m_name": "Truth_baselineCuts",
                            "m_truthContainerName": "TruthParticles",
                            "m_jetContainerName": "AntiKt4TruthJets",
                            "m_detailStr": "leptons quarks bosons susy substructure jets",
                            "m_truth_ptMinCut": truth_ptMinCut,
                            "m_truth_etaAbsMaxCut": truth_etaAbsMaxCut,
                            "m_jet_ptMinCut": jet_ptMinCut,
                            "m_bJet_etaAbsMaxCut": bJet_etaAbsMaxCut,
                            "m_min_n_jetsCut": min_n_jetsCut,
                            "m_min_n_bJetsCut": min_n_bJetsCut,
                            "m_debug": False})

''' Truth jets '''
c.setalg("JetHistsAlgo", {"m_name": "Jets",
                          "m_inContainerName": "AntiKt4TruthJets",
                          "m_detailStr": "truth NLeading6",
                          "m_debug": False})

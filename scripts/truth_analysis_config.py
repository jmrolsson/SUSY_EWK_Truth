# Truth studies for RunII SUSY EWK
# Joakim Olsson <joakim.olsson@cern.ch>
# 2017-02-07

# Baseline cuts
truth_ptMinCut = 25
truth_etaAbsMaxCut = 2.5
jet_ptMinCut = 20
bJet_etaAbsMaxCut = 2.5
min_n_bJets = 2

from xAH_config import xAH_config
c = xAH_config()

''' Truth validation studies, no cuts '''
c.setalg("TruthHistsAlgo", {"m_name": "Truth_noCuts",
                            "m_truthContainerName": "TruthParticles",
                            "m_jetContainerName": "AntiKt4TruthJets",
                            "m_detailStr": "leptons quarks bosons susy substructure",
                            "m_debug": False})

''' Truth validation studies, baseline cuts '''
c.setalg("TruthHistsAlgo", {"m_name": "Truth_baselineCuts",
                            "m_truthContainerName": "TruthParticles",
                            "m_jetContainerName": "AntiKt4TruthJets",
                            "m_detailStr": "leptons quarks bosons susy substructure",
                            "m_truth_ptMinCut": truth_ptMinCut,
                            "m_truth_etaAbsMaxCut": truth_etaAbsMaxCut,
                            "m_jet_ptMinCut": jet_ptMinCut,
                            "m_bJet_etaAbsMaxCut": bJet_etaAbsMaxCut,
                            "m_min_n_bJets": min_n_bJets,
                            "m_debug": False})

''' Truth jets '''
c.setalg("JetHistsAlgo", {"m_name": "Jets",
                          "m_inContainerName": "AntiKt4TruthJets",
                          "m_detailStr": "truth NLeading6",
                          "m_debug": False})

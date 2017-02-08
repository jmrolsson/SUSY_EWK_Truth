# Truth studies for RunII SUSY EWK
# Joakim Olsson <joakim.olsson@cern.ch>
# 2017-02-07

# Baseline cuts
jet_ptMinCut = 25
bJet_etaMaxCut = 2.5
min_n_bJets = 2

from xAH_config import xAH_config
c = xAH_config()

''' Truth validation studies, no cuts '''
c.setalg("TruthHistsAlgo", {"m_name": "Truth_noCuts",
                            "m_inContainerName": "TruthParticles",
                            "m_detailStr": "leptons quarks bosons susy substructure",
                            "m_jet_ptMinCut": 0.,
                            "m_bJet_etaMaxCut": 1e8,
                            "m_min_n_bJets": 1e8,
                            "m_debug": False})

# ''' Truth validation studies, baseline cuts '''
# c.setalg("TruthHistsAlgo", {"m_name": "Truth_baselineCuts",
#                             "m_inContainerName": "TruthParticles",
#                             "m_detailStr": "leptons quarks bosons susy substructure",
#                             "m_jet_ptMinCut": jet_ptMinCut,
#                             "m_bJet_etaMaxCut": bJet_etaMaxCut,
#                             "m_n_bJets": b_n_bJets,
#                             "m_debug": False})
#
# ''' Truth jets '''
# c.setalg("JetHistsAlgo", {"m_name": "Jets",
#                           "m_inContainerName": "AntiKt4TruthJets",
#                           "m_detailStr": "truth",
#                           "m_debug": False})

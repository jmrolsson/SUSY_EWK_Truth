# Truth studies for RunII SUSY EWK
# Joakim Olsson <joakim.olsson@cern.ch>

from xAH_config import xAH_config
c = xAH_config()

''' Truth jets '''
c.setalg("JetHistsAlgo", {"m_name": "Jets",
                          "m_inContainerName": "AntiKt4TruthJets",
                          "m_detailStr": "truth",
                          "m_debug": False})

''' Truth validation '''
c.setalg("TruthHistsAlgo", {"m_name": "Truth",
                            "m_inContainerName": "TruthParticles",
                            "m_detailStr": "leptons quarks bosons susy substructure",
                            # "m_detailStr": "leptons quarks bosons susy",
                            "m_debug": False})

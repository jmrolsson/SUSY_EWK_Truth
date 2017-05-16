# SUSY_EWK_Truth
A set of scripts (built on top of [xAODAnaHelpers](https://github.com/UCATLAS/xAODAnaHelpers)) to making quick truth studies for electroweak SUSY searches. Specifically, we focus on the "C1N2 -> WZ (or Wh) + N1N1 -> qqbb + Etmiss" all-hadronic decays, but it should hopefully be straightforward to adapt the code to other decay channels.

NB: For the full analysis we are using the MultibjetsAnalysis (MBJ) framework (ATLAS internal only): https://gitlab.cern.ch/MultiBJets/MultibjetsAnalysis

## Setup
```
mkdir myAnalysis; cd myAnalysis
git clone http://github.com/UCATLAS/xAODAnaHelpers xAODAnaHelpers
git clone http://github.com/jmrolsson/SUSY_EWK_Truth
lsetup 'rcsetup Base,2.4.22' # or later version of (Ath)AnalysisBase
rc clean && rc find_packages && rc compile && rc make_par
```

## Running
The code takes ATLAS ["TRUTH" xAODs](https://twiki.cern.ch/twiki/bin/view/AtlasProtected/TruthDAODTutorial) as inputs. 

Example:
```
xAH_run.py --files TRUTH1.root --config SUSY_EWK_Truth/scripts/truth_analysis_test.py --submitDir results/truth_test --verbose --force direct
```

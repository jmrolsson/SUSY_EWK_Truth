# SUSY_EWK_Truth

## Setup
```
mkdir myAnalysis; cd myAnalysis
git clone http://github.com/UCATLAS/xAODAnaHelpers xAODAnaHelpers
git clone http://github.com/jmrolsson/SUSY_EWK_Truth
lsetup 'rcsetup Base,2.4.22' # or later version of (Ath)AnalysisBase
rc clean && rc find_packages && rc compile && rc make_par
```

## Running
Example:
```
xAH_run.py --files TRUTH1.root --config SUSY_EWK_Truth/scripts/truth_analysis_test.py --submitDir results/truth_test --verbose --force direct
```

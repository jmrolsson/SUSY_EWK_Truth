# Truth studies for RunII SUSY EWK
# Joakim Olsson <joakim.olsson@cern.ch>
# 2017-02-07

if [ -z "$ROOTCOREBIN" ]; then
  echo "RootCore is not setup, please run:"
  echo "lsetup 'rcsetup Base,2.4.22'"

else

  cd $ROOTCOREBIN/.. 
  mkdir -p ewk_truth_hists

  for sample in $(ls $ROOTCOREBIN/../SUSY_EWK_Truth/filelists/); do
    echo $sample
    sample_tag=$(echo $sample | sed -r "s/.txt//g")
    echo "Running: "xAH_run.py --files SUSY_EWK_Truth/filelists/${sample} --inputList --config SUSY_EWK_Truth/scripts/truth_analysis_config.py --submitDir ewk_truth_hists/${sample_tag} --verbose --force direct
    xAH_run.py --files SUSY_EWK_Truth/filelists/${sample} --inputList --config SUSY_EWK_Truth/scripts/truth_analysis_config.py --submitDir ewk_truth_hists/${sample_tag} --verbose --force direct 2>&1 >/dev/null &
  done;

fi

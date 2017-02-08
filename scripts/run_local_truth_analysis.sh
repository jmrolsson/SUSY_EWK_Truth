# Truth studies for RunII SUSY EWK
# Joakim Olsson <joakim.olsson@cern.ch>
# 2017-02-07

if [ -z "$ROOTCOREBIN" ]; then
  echo "RootCore is not setup, please run:"
  echo "lsetup 'rcsetup Base,2.4.22'"

else

  cd $ROOTCOREBIN/.. 
  mkdir -p results

  for sample in; $(cat $ROOTCOREBIN/../SUSY_EWK_Truth/filelists/sample_list.txt) do
    process_command="xAH_run.py --files ${sample}.txt --inputList --config SUSY_EWK_Truth/scripts/truth_analysis_config.py --submitDir results/${sample_tag} --verbose --force direct > /dev/null 2>&1 &"
    # echo "Running: "$process_command
    eval $process_command
  done;

fi

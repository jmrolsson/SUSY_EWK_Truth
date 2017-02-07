# Truth studies for RunII SUSY EWK
# Joakim Olsson <joakim.olsson@cern.ch>

if [ -z "$ROOTCOREBIN" ]; then
  echo "RootCore is not setup, please run:"
  echo "lsetup \'rcsetup Base,2.4.22\'"

else

  cd $ROOTCOREBIN/.. 
  mkdir -p results

  # for sample in WZ_500p0_200p0 WZ_500p0_0p5 WZ_300p0_0p5 WZ_200p0_0p5 WZ_150p0_0p5 Wh_500p0_200p0 Wh_500p0_0p5 Wh_300p0_0p5 Wh_200p0_0p5 Wh_150p0_0p5;
  for sample in Wh_500p0_200p0; do
    process_command="xAH_run.py --files SUSY_EWK_Truth/filelists/mc15_13TeV_C1N2_${sample}_bbqq_J10.txt --inputList --config SUSY_EWK_Truth/scripts/truth_analysis_config.py --submitDir results/C1N2_${sample}_bbqq_J10 --verbose --force direct"
    echo "Running: "$process_command
    eval $process_command
  done;

fi

# Truth studies for RunII SUSY EWK
# Script for creating separate file lists for each sample 
# Joakim Olsson <joakim.olsson@cern.ch>
# 2017-02-07

pattern=/share/t3data2/jolsson/ewk_truth_xaod/*TRUTH1.20170506_2.1*/*.root
for path in $(ls ${pattern}) 
do 
  dir=$(dirname "${path}")
  file=$(basename "${path}")
  if [ -d $dir ]; then
    sample_tag=$(echo ${dir} | sed -r "s/^.*user.*A14N23LO_//g" | sed -r "s/\.TRUTH.*//g")
    echo $path >> $ROOTCOREBIN/../SUSY_EWK_Truth/filelists/mc15_13TeV_${sample_tag}.txt;
  fi
done;

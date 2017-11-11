# Truth studies for RunII SUSY EWK
# Script for creating separate file lists for each sample 
# Joakim Olsson <joakim.olsson@cern.ch>
# 2017-02-07

## February truth samples
#jo_version=feb2017
#tag=20170204_30k_1

## New truth samples, same generator settings as the "February samples" just different mass points, in order to validate the job options (JOs) for the official request
#jo_version=march2017
#tag=20170506
#tag=20170514
#tag=20170516

## Testing official Wh JOs (https://its.cern.ch/jira/browse/ATLMCPROD-4979)
jo_version=aug2017
tag=20170814

pattern=/share/t3data2/jolsson/EWK/ewk_truth_xaod/*TRUTH1.${tag}*/*.root
for path in $(ls ${pattern}) 
do 
  dir=$(dirname "${path}")
  file=$(basename "${path}")
  if [ -d $dir ]; then
    sample_tag=$(echo ${dir} | sed -r "s/^.*user.*A14N23LO_//g" | sed -r "s/\.TRUTH.*//g")
    echo $path >> $ROOTCOREBIN/../SUSY_EWK_Truth/filelists/mc15_13TeV_${sample_tag}_${jo_version}.txt;
  fi
done;

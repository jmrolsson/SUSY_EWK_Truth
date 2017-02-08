# Script for creating separate file lists for each sample 
# Joakim Olsson <joakim.olsson@cern.ch>
# 2017-02-07

path=/share/t3data2/jolsson/run2_truth_validation/
> $ROOTCOREBIN/../SUSY_EWK_Truth/filelists/sample_list.txt
for sample in $(ls $path) 
do 
  if [ -d $path/$sample ]; then
    sample_tag=$(echo $sample | sed -r "s/user.*A14N23LO_//g" | sed -r "s/\.TRUTH.*//g")
    find /share/t3data2/jolsson/run2_truth_validation/${sample}/ -name *root > $ROOTCOREBIN/../SUSY_EWK_Truth/filelists/mc15_13TeV_${sample_tag}.txt;
    echo mc15_13TeV_$sample_tag >> $ROOTCOREBIN/../SUSY_EWK_Truth/filelists/sample_list.txt;
  fi
done;

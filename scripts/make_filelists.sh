for sample in WZ_500p0_200p0 WZ_500p0_0p5 WZ_400p0_100p0 WZ_400p0_0p5 WZ_300p0_100p0 WZ_300p0_0p5 WZ_200p0_50p0 WZ_200p0_0p5 WZ_500p0_200p0 WZ_500p0_0p5 WZ_400p0_100p0 WZ_400p0_0p5 WZ_300p0_100p0 WZ_300p0_0p5 WZ_200p0_50p0 WZ_200p0_0p5
do 
  find /share/t3data2/jolsson/run2_truth_validation/user.jolsson.mc15_13TeV.*.MGPy8EG_A14N23LO_C1N2_${sample}_bbqq_J10.TRUTH1.20170204_30k_1_EXT0/ -name *root > $ROOTCOREBIN/../SUSY_EWK_Truth/filelists/mc15_13TeV_C1N2_${sample}_bbqq_J10.txt;
done;

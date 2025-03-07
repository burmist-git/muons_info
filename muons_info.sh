#!/usr/bin/bash

muonfileinfo="DL1_mouns_file.info"

printHelp () { 
    echo " --> ERROR in input arguments "
    echo " -d           : default" 
    echo " -m           : get DL1 mouns file information" 
    echo " --m_addition : get DL1 mouns file information (addition)"
}

if [ $# -eq 0 ] 
then
    printHelp
else
    if [ "$1" = "-d" ]; then
	echo "year : nnight nnight_v9 nnight_v10"
	for year in  2019 2020 2021 2022 2023 2024 2025 ; do
	    #echo $year
	    nnight=$(ls /fefs/aswg/data/real/DL1/$year*/ | grep DL1 | wc -l)
	    # dvr v0.10V v0.9G v0.10_tests interleaved v0.10.12 v0.10G v0.10.8_test
	    nnight_v9=$(ls /fefs/aswg/data/real/DL1/$year*/ | grep v0.9 | grep -v dvr | grep -v v0.10V | grep -v v0.9G | grep -v v0.10_tests | grep -v interleaved | grep -v v0.10.12 | grep -v v0.10G | grep -v v0.10.8_test | wc -l)
	    nnight_v10=$(ls /fefs/aswg/data/real/DL1/$year*/ | grep v0.10 | grep -v dvr | grep -v v0.10V | grep -v v0.9G | grep -v v0.10_tests | grep -v interleaved | grep -v v0.10.12 | grep -v v0.10G | grep -v v0.10.8_test | wc -l)
	    echo "$year : $nnight $nnight_v9 $nnight_v10"
	done
    elif [ "$1" = "-m" ]; then
	#rm -rf $muonfileinfo
	#echo "dirnamedate v09yes v10yes v09subruns v10subruns" | tee $muonfileinfo -a
	for year in  2019 2020 2021 2022 2023 2024 2025 ; do
	    for m in 1 2 3 4 5 6 7 8 9 10 11 12; do
		#date -d "$m/1 + 1 month - 1 day" "+%b - %d days";
		month=$(printf "%02d" $m)
		nnight_per_month=$(cal $m $year | awk 'NF {DAYS = $NF}; END {print DAYS}')
		#echo "$year $month $nnight_per_month"
		for d in $(seq 1 $nnight_per_month); do
		    days=$(printf "%02d" $d)
		    #echo "$year$month$days"
		    dirnamedate=$year$month$days
		    dirname_v9="/fefs/aswg/data/real/DL1/$dirnamedate/v0.9/"
		    dirname_v10="/fefs/aswg/data/real/DL1/$dirnamedate/v0.10/"
		    #ls -lrt /fefs/aswg/data/real/DL1/20230117/v0.10/muons/muons_LST-1.Run*.*.fits | wc -l
		    #ls -lrt /fefs/aswg/data/real/DL1/20230117/v0.9/muons_LST-1.Run*.*.fits | wc -l
		    #/fefs/aswg/data/real/DL1/20220222/v0.9/
		    #/fefs/aswg/data/real/DL1/20220222/v0.10/
		    #/fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz
		    if [ -d "$dirname_v9" ]; then
			v09yes="1"
			#v09subruns=$(ls -lrt /fefs/aswg/data/real/DL1/$dirnamedate/v0.9/muons_LST-1.Run*.*.fits | wc -l)
			#echo "$v09subruns"
			tar -czvf '/fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/'$dirnamedate'_v0.9_muons.tar.gz'  /fefs/aswg/data/real/DL1/$dirnamedate/v0.9/muons_LST-1.Run*.fits
			du -hs '/fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/'$dirnamedate'_v0.9_muons.tar.gz'
		    else
			v09yes="0"
			v09subruns="0"
		    fi
		    #
		    if [ -d "$dirname_v10" ]; then
			v10yes="1"
			#v10subruns=$(ls -lrt /fefs/aswg/data/real/DL1/$dirnamedate/v0.10/muons/muons_LST-1.Run*.*.fits | wc -l)
			tar -czvf '/fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/'$dirnamedate'_v0.10_muons.tar.gz'  /fefs/aswg/data/real/DL1/$dirnamedate/v0.10/muons/muons_LST-1.Run*.fits
			du -hs '/fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/'$dirnamedate'_v0.10_muons.tar.gz'
		    else
			v10yes="0"
			v10subruns="0"
		    fi
		    #echo "$dirnamedate $v09yes $v10yes $v09subruns $v10subruns" | tee $muonfileinfo -a
		done
	    done
	done
    elif [ "$1" = "--m_addition" ]; then
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20220628_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20220628/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20220629_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20220629/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20221010_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20221010/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20221012_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20221012/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230516_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230516/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230518_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230518/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230523_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230523/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230616_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230616/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230619_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230619/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230622_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230622/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230625_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230625/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230706_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230706/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230708_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230708/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230709_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230709/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230712_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230712/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230713_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230713/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230714_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230714/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230717_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230717/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230721_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230721/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230722_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230722/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230723_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230723/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230724_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230724/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230725_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230725/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230807_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230807/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230808_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230808/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230809_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230809/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230810_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230810/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230811_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230811/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230812_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230812/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230815_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230815/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230816_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230816/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230817_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230817/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230818_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230818/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230819_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230819/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230820_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230820/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230821_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230821/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230822_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230822/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230824_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230824/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230908_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230908/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230911_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230911/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230912_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230912/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230916_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230916/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230917_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230917/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230918_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230918/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230919_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230919/v0.10/muons_LST-1.Run*.*.fits
	tar -czvf /fefs/aswg/workspace/leonid.burmistrov/muons_DL1_tar_gz/20230920_v0.10_muons.tar.gz /fefs/aswg/data/real/DL1/20230920/v0.10/muons_LST-1.Run*.*.fits
    else
        printHelp
    fi
fi

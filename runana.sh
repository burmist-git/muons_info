#!/bin/bash

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d : single root file"
    echo " [0] -l : list of root files"
    echo " [0] -c : compile"
    echo " [0] -h : print help"
}

if [ $# -eq 0 ] 
then    
    printHelp
else
    if [ "$1" = "-d" ]; then
	inRootFiles="./muon_file.root"
	outHistSingleF="./histSingle.root"
	./runana 1 $inRootFiles $outHistSingleF
    elif [ "$1" = "-l" ]; then
	rootFilesList="./rootFileList.dat"
	outHistF="./hist.root"
	./runana 0 $rootFilesList $outHistF
    elif [ "$1" = "-c" ]; then
	make clean; make
    elif [ "$1" = "-h" ]; then
        printHelp
    else
        printHelp
    fi
fi

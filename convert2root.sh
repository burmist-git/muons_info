#!/bin/bash

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d                  : default"
    echo " [0] -c                  : re - compile"
    echo " [0] --inc_reduce_stack  : increase reduce stack memory"
    echo " [0] --set_unlimited_mem : set unlimited memory"
    echo " [0] -h                  : print help"
}
    
if [ $# -eq 0 ] 
then    
    printHelp
else
    if [ "$1" = "-d" ]; then
	./convert2root 0 muon_file.list muon_file.root
    elif [ "$1" = "-c" ]; then
	make clean; make;
    elif [ "$1" = "--inc_reduce_stack" ]; then	
	echo " ulimit -s           : current limit"
	echo " ulimit -s unlimited : set stack unlimited"
	echo " sudo swapoff -a; sudo swapon -a : clean swap"
    elif [ "$1" = "--set_unlimited_mem" ]; then	
	ulimit -s unlimited
    elif [ "$1" = "-h" ]; then
        printHelp
    else
        printHelp
    fi
fi

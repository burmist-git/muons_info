#!/home/burmist/miniconda/envs/mamba/envs/lstchain-v0.10.18/bin/python
# -*- coding: utf-8 -*-

import pandas as pd
import numpy as np
import glob
import gc
import matplotlib.pyplot as plt
from matplotlib import colors
from astropy.coordinates import SkyCoord, AltAz, angular_separation
import astropy.units as u
from scipy.stats import binned_statistic
from scipy.signal import lombscargle
import h5py
from astropy.io import fits
from astropy.table import Table

def parse_the_file_name_string(str_in, iloc_to_return = 0,if_test = False):
    date_str=str_in.split("/")[7]
    year_str=date_str[:4]
    month_str=date_str[4:6]
    day_str=date_str[6:]   
    #
    date_int=int(date_str)
    year_int=int(date_str[:4])
    month_int=int(date_str[4:6])
    day_int=int(date_str[6:])   
    #
    v_str=str_in.split("/")[8]
    name_str=str_in.split("/")[9]
    run_ID_str=name_str.split(".")[1].replace("Run","")
    subRun_ID_str=name_str.split(".")[2]
    #
    run_ID_int=int(run_ID_str)
    subRun_ID_int=int(subRun_ID_str)
    #         0         1         2          3        4      5         6           7              8         9         10         11       12          13
    list_out=[date_str, year_str, month_str, day_str, v_str, name_str, run_ID_str, subRun_ID_str, date_int, year_int, month_int, day_int, run_ID_int, subRun_ID_int]
    if(if_test):
        print("date_str      = ", list_out[0])
        print("year_str      = ", list_out[1])
        print("month_str     = ", list_out[2])
        print("day_str       = ", list_out[3])
        print("v_str         = ", list_out[4])
        print("name_str      = ", list_out[5])
        print("run_ID_str    = ", list_out[6])
        print("subRun_ID_str = ", list_out[7])
        print("date_int      = ", list_out[8])
        print("year_int      = ", list_out[9])
        print("month_int     = ", list_out[10])
        print("day_int       = ", list_out[11])
        print("run_ID_int    = ", list_out[12])
        print("subRun_ID_int = ", list_out[13])

    return list_out[iloc_to_return]
    
def main():
    pass

if __name__ == "__main__":
    #main()
    df_list=pd.read_csv("../muons_DL1_tar_gz/subRun.info")
    #
    parse_the_file_name_string(df_list['subRunlist'][0], 0, True)
    parse_the_file_name_string(df_list['subRunlist'][len(df_list)-1], 0, True)
    #
    df_list['date']=df_list['subRunlist'].map(lambda x: parse_the_file_name_string(x,0))
    df_list['year']=df_list['subRunlist'].map(lambda x: parse_the_file_name_string(x,1))
    df_list['month']=df_list['subRunlist'].map(lambda x: parse_the_file_name_string(x,2))
    df_list['day']=df_list['subRunlist'].map(lambda x: parse_the_file_name_string(x,3))
    df_list['ver']=df_list['subRunlist'].map(lambda x: parse_the_file_name_string(x,4))
    df_list['name']=df_list['subRunlist'].map(lambda x: parse_the_file_name_string(x,5))
    df_list['runID']=df_list['subRunlist'].map(lambda x: parse_the_file_name_string(x,6))
    df_list['subRunID']=df_list['subRunlist'].map(lambda x: parse_the_file_name_string(x,7))
    df_list['date_int']=df_list['subRunlist'].map(lambda x: parse_the_file_name_string(x,8))
    df_list['year_int']=df_list['subRunlist'].map(lambda x: parse_the_file_name_string(x,9))
    df_list['month_int']=df_list['subRunlist'].map(lambda x: parse_the_file_name_string(x,10))
    df_list['day_int']=df_list['subRunlist'].map(lambda x: parse_the_file_name_string(x,11))
    df_list['runID_int']=df_list['subRunlist'].map(lambda x: parse_the_file_name_string(x,12))
    df_list['subRunID_int']=df_list['subRunlist'].map(lambda x: parse_the_file_name_string(x,13))
    #
    df_list.to_csv('subRunlist.csv')
    df_list.to_csv('subRunlist_for_root.csv',sep=" ")

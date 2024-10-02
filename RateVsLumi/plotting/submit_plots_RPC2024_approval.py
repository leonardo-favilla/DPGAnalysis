import os
import argparse
# fill = 9573 # 8754-9573

usage       = 'python3 submit_plots_RPC2024_approval -f <fill_number>'
parser      = argparse.ArgumentParser(usage)
parser.add_argument('-f', '--fill',       dest = 'fill',      required = True,                                type = int,                             help = 'specify the fill number')
args        = parser.parse_args()
fill        = args.fill

if fill==8754:
    RPC_fit_file = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_8754/RPC_fit_F8754.root"
    out_dir      = "/eos/user/l/lfavilla/RPC/plots/RPC2024_approval/Fill_F8754"
elif fill==9573:
    # RPC_fit_file = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_9573_noblacklist_REp43_sector4/RPC_fit_F9573.root"
    # out_dir      = "/eos/user/l/lfavilla/RPC/plots/RPC2024_approval/RPC_fit_F9573_noblacklist_REp43_sector4"
    # RPC_fit_file = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_9573_singleJob/RPC_fit_F9573.root"
    # out_dir      = "/eos/user/l/lfavilla/RPC/plots/RPC2024_approval/Fill_9573_singleJob"
    RPC_fit_file = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_9573_dead_and_noisy_noSectorRollSubdvision/RPC_fit_F9573.root"
    out_dir      = "/eos/user/l/lfavilla/RPC/plots/RPC2024_approval/Fill_9573_dead_and_noisy_noSectorRollSubdvision"

barrel_chambers = [
    "Wm2_RB1in","Wm2_RB1out","Wm2_RB2in","Wm2_RB2out","Wm2_RB3","Wm2_RB4",
    "Wm1_RB1in","Wm1_RB1out","Wm1_RB2in","Wm1_RB2out","Wm1_RB3","Wm1_RB4",
    "W0_RB1in","W0_RB1out","W0_RB2in","W0_RB2out","W0_RB3","W0_RB4",
    "Wp1_RB1in","Wp1_RB1out","Wp1_RB2in","Wp1_RB2out","Wp1_RB3","Wp1_RB4",
    "Wp2_RB1in","Wp2_RB1out","Wp2_RB2in","Wp2_RB2out","Wp2_RB3","Wp2_RB4"
    ]
endcap_chambers = [
    "REm43","REm42","REm33","REm32","REm23","REm22","REm13","REm12",
    "REp43","REp42","REp33","REp32","REp23","REp22","REp13","REp12"
    ]

# barrel_chambers = ["Wp1_RB1in"]
# endcap_chambers = ["REm42"]
sectors         = ["S01","S02","S03","S04","S05","S06","S07","S08","S09","S10","S11","S12"]



# print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp42_S10,REm42_S10,REp32_S10,REm32_S10 -d {out_dir} -p")
# os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp42_S10,REm42_S10,REp32_S10,REm32_S10 -d {out_dir} -p")

# print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp42,REm42,REp32,REm32 -d {out_dir} -p")
# os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp42,REm42,REp32,REm32 -d {out_dir} -p")

# print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp43,REm43,REp33,REm33 -d {out_dir} -p")
# os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp43,REm43,REp33,REm33 -d {out_dir} -p")

# print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp43,REm43,REp42,REm42 -d {out_dir} -p")
# os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp43,REm43,REp42,REm42 -d {out_dir} -p")

# for sec in sectors:
#     print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp42_{sec},REm42_{sec},REp32_{sec},REm32_{sec} -d {out_dir} -p")
#     os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp42_{sec},REm42_{sec},REp32_{sec},REm32_{sec} -d {out_dir} -p")

#     os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp43_{sec},REm43_{sec},REp33_{sec},REm33_{sec} -d {out_dir} -p")
#     print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp43_{sec},REm43_{sec},REp33_{sec},REm33_{sec} -d {out_dir} -p")

#     os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp43_{sec},REm43_{sec},REp42_{sec},REm42_{sec} -d {out_dir} -p")
#     print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp43_{sec},REm43_{sec},REp42_{sec},REm42_{sec} -d {out_dir} -p")





# print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp42_S04,REm42_S04,REp32_S04,REm32_S04 -d {out_dir} -p")
# os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp42_S04,REm42_S04,REp32_S04,REm32_S04 -d {out_dir} -p")
# print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp42,REm42,Wp2_RB1in,Wm2_RB1in -d {out_dir} -p")
# os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp42,REm42,Wp2_RB1in,Wm2_RB1in -d {out_dir} -p")



##############
# LUMI PLOTS #
##############
# barrel_chambers = ["Wm2_RB1in"]
barrel_chambers = []
# endcap_chambers = ["REm42"]
endcap_chambers = []
# BARREL #
for ch in barrel_chambers:
    print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c {ch} -d {out_dir} -p")
    os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c {ch} -d {out_dir} -p")
    print("\n")
# ENDCAP #
for ch in endcap_chambers:
    print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c {ch} -d {out_dir} -p")
    os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c {ch} -d {out_dir} -p")
    print("\n")
    
    
    
#############
# ETA PLOTS #
#############
barrel_stations = ["RB1in","RB1out","RB2in","RB2out","RB3","RB4"]
# barrel_stations = ["RB1in"]
# barrel_stations = []
endcap_disks    = ["RE1","RE2","RE3","RE4"]
# endcap_disks    = ["RE4"]
# endcap_disks    = []
for station in barrel_stations:
    print(f"python3 HitRate_eta.py -i {RPC_fit_file} -f {fill} -c {station} -d {out_dir} -p")
    os.system(f"python3 HitRate_eta.py -i {RPC_fit_file} -f {fill} -c {station} -d {out_dir} -p")
    print("\n")
for disk in endcap_disks:
    print(f"python3 HitRate_eta.py -i {RPC_fit_file} -f {fill} -c {disk} -d {out_dir} -p")
    os.system(f"python3 HitRate_eta.py -i {RPC_fit_file} -f {fill} -c {disk} -d {out_dir} -p")
    print("\n")



#############
# +/- PLOTS #
#############
# print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp43,REm43 -d {out_dir} -p")
# os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp43,REm43 -d {out_dir} -p")
# print("\n")
# print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp42,REm42 -d {out_dir} -p")
# os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp42,REm42 -d {out_dir} -p")
# print("\n")
# print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp33,REm33 -d {out_dir} -p")
# os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp33,REm33 -d {out_dir} -p")
# print("\n")
# print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp32,REm32 -d {out_dir} -p")
# os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp32,REm32 -d {out_dir} -p")
# print("\n")
# print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp23,REm23 -d {out_dir} -p")
# os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp23,REm23 -d {out_dir} -p")
# print("\n")
# print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp22,REm22 -d {out_dir} -p")
# os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp22,REm22 -d {out_dir} -p")
# print("\n")
# print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp13,REm13 -d {out_dir} -p")
# os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp13,REm13 -d {out_dir} -p")
# print("\n")
# print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp12,REm12 -d {out_dir} -p")
# os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp12,REm12 -d {out_dir} -p")
# print("\n")

print("DONE!")
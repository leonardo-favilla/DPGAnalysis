import os
endcap_chambers = ["REp43","REp42","REp33","REp32","REp23","REp22","REp13","REp12","REm43","REm42","REm33","REm32","REm23","REm22","REm13","REm12"]

fill = 9573 # 8754-9573


if fill==8754:
    RPC_fit_file = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_8754/RPC_fit_F8754.root"
    out_dir      = "/eos/user/l/lfavilla/RPC/plots/RPC_fit_F8754"
elif fill==9573:
    RPC_fit_file = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_9573_noblacklist_REp43_sector4/RPC_fit_F9573.root"
    out_dir      = "/eos/user/l/lfavilla/RPC/plots/RPC_fit_F9573_noblacklist_REp43_sector4"

##########
# BARREL #
##########
print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c Wp2_RB1in -d {out_dir} -p")
os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c Wp2_RB1in -d {out_dir} -p")
print("\n")
print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c Wm2_RB1in -d {out_dir} -p")
os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c Wm2_RB1in -d {out_dir} -p")
print("\n")
print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c Wp2_RB1out -d {out_dir} -p")
os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c Wp2_RB1out -d {out_dir} -p")
print("\n")
print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c Wm2_RB1out -d {out_dir} -p")
os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c Wm2_RB1out -d {out_dir} -p")
print("\n")
print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c Wp2_RB4 -d {out_dir} -p")
os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c Wp2_RB4 -d {out_dir} -p")
print("\n")
print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c Wm2_RB4 -d {out_dir} -p")
os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c Wm2_RB4 -d {out_dir} -p")
print("\n")


print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c Wp2_RB1in,Wm2_RB1in -d {out_dir} -p")
os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c Wp2_RB1in,Wm2_RB1in -d {out_dir} -p")
print("\n")
print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c Wp2_RB4,Wm2_RB4 -d {out_dir} -p")
os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c Wp2_RB4,Wm2_RB4 -d {out_dir} -p")
print("\n")

##########
# ENDCAP #
##########
for ch in endcap_chambers:
    print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c {ch} -d {out_dir} -p")
    os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c {ch} -d {out_dir} -p")
    print("\n")


print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp43,REm43 -d {out_dir} -p")
os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp43,REm43 -d {out_dir} -p")
print("\n")
print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp42,REm42 -d {out_dir} -p")
os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp42,REm42 -d {out_dir} -p")
print("\n")
print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp33,REm33 -d {out_dir} -p")
os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp33,REm33 -d {out_dir} -p")
print("\n")
print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp32,REm32 -d {out_dir} -p")
os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp32,REm32 -d {out_dir} -p")
print("\n")
print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp23,REm23 -d {out_dir} -p")
os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp23,REm23 -d {out_dir} -p")
print("\n")
print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp22,REm22 -d {out_dir} -p")
os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp22,REm22 -d {out_dir} -p")
print("\n")
print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp13,REm13 -d {out_dir} -p")
os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp13,REm13 -d {out_dir} -p")
print("\n")
print(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp12,REm12 -d {out_dir} -p")
os.system(f"python3 HitRate_Lumi.py -i {RPC_fit_file} -f {fill} -c REp12,REm12 -d {out_dir} -p")
print("\n")

print("Done!")
import os
import optparse
import sys
import time
import json
import numpy as np

usage = "python3 RPCAnalyzer_submitter.py"
parser = optparse.OptionParser(usage)
# parser.add_option('-d', '--dryrun', dest='dryrun', default=True, action='store_false', help='Default do not run')
parser.add_option('-d', '--dryrun',
                  dest='dryrun',
                  default=False, 
                  action='store_true',
                  help='Default do not run')
#parser.add_option('-u', '--user', dest='us', type='string', default = 'ade', help="")
(opt, args) = parser.parse_args()
#Insert here your uid... you can see it typing echo $uid

dryrun = opt.dryrun

username = str(os.environ.get('USER'))
inituser = str(os.environ.get('USER')[0])
if username == 'adeiorio':
    uid = 103214
elif username == 'acagnott':
    uid = 140541
elif username == 'lfavilla':
    uid = 159320


def sub_writer(macro_to_run, fill):
    f = open("condor.sub", "w")
    f.write("Proxy_filename          = x509up\n")
    f.write("Proxy_path              = /afs/cern.ch/user/" + inituser + "/" + username + "/private/$(Proxy_filename)\n")
    f.write("universe                = vanilla\n")
    f.write("x509userproxy           = $(Proxy_path)\n")
    f.write("use_x509userproxy       = true\n")
    f.write("should_transfer_files   = YES\n")
    f.write("when_to_transfer_output = ON_EXIT\n")
    f.write("transfer_input_files    = $(Proxy_path)\n")
    #f.write("transfer_output_remaps  = \""+outname+"_Skim.root=root://eosuser.cern.ch///eos/user/"+inituser + "/" + username+"/DarkMatter/topcandidate_file/"+dat_name+"_Skim.root\"\n")
    f.write('requirements            = (TARGET.OpSysAndVer =?= "CentOS7")\n')
    f.write("+JobFlavour             = \"testmatch\"\n") # options are espresso = 20 minutes, microcentury = 1 hour, longlunch = 2 hours, workday = 8 hours, tomorrow = 1 day, testmatch = 3 days, nextweek     = 1 week
    f.write("executable              = runner_"+macro_to_run+"_F"+fill+".sh\n")
    f.write("arguments               = \n")
    #f.write("input                   = input.txt\n")
    f.write("output                  = condor/output/"+ macro_to_run+".out\n")
    f.write("error                   = condor/error/"+ macro_to_run+".err\n")
    f.write("log                     = condor/log/"+ macro_to_run+".log\n")
    f.write("queue\n")


def sh_writer(macro_to_run, fill, txt_files, colliding_scheme, outFolder):
    f = open("runner_"+macro_to_run+"_F"+fill+".sh", "w")
    f.write("#!/usr/bin/bash\n")
    f.write("cd /afs/cern.ch/user/l/lfavilla/CMSSW_14_0_5_patch1/src/DPGAnalysis/RateVsLumi/analyzer\n")
    f.write("eval 'scramv1 runtime -sh'\n")
    f.write("cmsenv\n")
    for i,txt_list in enumerate(txt_files):
        f.write("python3 "+macro_to_run+".py "+str(i)+" ["+",".join(txt_list)+"] "+colliding_scheme+" "+ outFolder+"\n")
    # f.write("export XRD_NETWORKSTACK=IPv4\n")


if not os.path.exists("condor/output"):
    os.makedirs("condor/output")
if not os.path.exists("condor/error"):
    os.makedirs("condor/error")
if not os.path.exists("condor/log"):
    os.makedirs("condor/log")
if(uid == 0):
    print("Please insert your uid")
    exit()
if not os.path.exists("/tmp/x509up_u" + str(uid)):
    os.system('voms-proxy-init --rfc --voms cms -valid 192:00')
os.popen("cp /tmp/x509up_u" + str(uid) + " /afs/cern.ch/user/" + inituser + "/" + username + "/private/x509up")

######## LAUNCH CONDOR ########
abs_path             = "/afs/cern.ch/user/l/lfavilla/CMSSW_14_0_5_patch1/src/DPGAnalysis/RateVsLumi"
fill                 = 8754 # 8754-9573
if fill==8754:
    RPCNtuples_txt   = f"{abs_path}/RPCNtuples/crab_ZB_RPCNtuplizer_F8754.txt"
    colliding_scheme = f"{abs_path}/fill_schemes/Fill_8754/colliding_8754.txt"
    outFolder        = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_8754_noSectorRollSubdvision"
elif fill==9573:
    # RPCNtuples_txt   = f"{abs_path}/RPCNtuples/crab_ZB_RPCNtuplizer_F9573_R380115.txt"
    # RPCNtuples_txt   = f"{abs_path}/RPCNtuples/crab_ZB_RPCNtuplizer_F9573.txt"
    RPCNtuples_txt   = f"{abs_path}/RPCNtuples/crab_ZB_RPCNtuplizer_F9573_dead_and_noisy.txt"
    colliding_scheme = f"{abs_path}/fill_schemes/Fill_9573/colliding_9573.txt"
    # outFolder        = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_9573"
    # outFolder        = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_9573_singleJob"
    # outFolder        = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_9573_dead_and_noisy"
    outFolder        = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_9573_dead_and_noisy_noSectorRollSubdvision"


txt_files = []
with open(RPCNtuples_txt, "r") as f:
    lines = f.readlines()

for line in lines:
    line = line.replace("\n", "")
    if ".root" in line:
        txt_files.append(line)

txt_lists = np.array_split(txt_files, 10)
txt_lists = [list(sublist) for sublist in txt_lists]


sh_writer(macro_to_run="RPCAnalyzer",
          fill=str(fill),
          txt_files=txt_lists,
          colliding_scheme=colliding_scheme,
          outFolder=outFolder
          )
sub_writer(macro_to_run="RPCAnalyzer",
           fill=str(fill)
           )
if not dryrun:
    os.popen("condor_submit condor.sub")
time.sleep(2)

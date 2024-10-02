import os
import argparse
import sys
import ROOT
from CMS_lumi import CMS_lumi
from loadHists import loadHists
from graphicsOptions import graphicsOptions
import copy
from geometry.geometry import geometry_dict
import array
from math import sqrt
import json
from statistics import mean, stdev
ROOT.gStyle.SetOptStat(0)
ROOT.gROOT.SetBatch(1)

usage       = 'python3 HitRate_eta.py -i <input root file>'
example     = 'python3 HitRate_eta.py -i /eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_9573/RPC_fit_F9573.root -c RB1in -d /eos/user/l/lfavilla/RPC/plots/RPC_fit_F9573 -p'
parser      = argparse.ArgumentParser(usage)
parser.add_argument('-i', '--inFile',     dest = 'inFile',    required = True,                                type = str,                             help = 'input root file (should be the output of RPCFitter.py)')
parser.add_argument('-f', '--fill',       dest = 'fill',      required = True,                                type = int,                             help = 'specify the fill number')
parser.add_argument('-c', '--chambers',   dest = 'chambers',  required = False,   default = 'Wm2_RB1in',      type = str,                             help = 'specify the chambers to be plotted - default Wm2_RB1in')
parser.add_argument('-d', '--outDir',     dest = 'outDir',    required = False,   default = './',             type = str,                             help = 'output directory for the plots - default is the current directory')
parser.add_argument('-p', '--print',      dest = 'print',     required = False,   default = False,                            action = 'store_true',  help = 'save the plots in png/pdf format')

args        = parser.parse_args()
inFile      = args.inFile
fill        = args.fill
chambers    = args.chambers.split(',')
outDir      = args.outDir
printPlots  = args.print
regions     = ["high", "low", "prebeam", "abort"]
superimpose_2018 = True

if fill==8754:
    year                    = 2023
    lumi                    = 440.273 + 175.600 + 27.104                        # pb-1, Runs: 367413 + 367406 + 367415 
    colliding_scheme_txt    = "../fill_schemes/Fill_8754/colliding_8754.txt"    # Fill=8754
elif fill==9573:
    year                    = 2024
    lumi                    = 635.347                                           # pb-1, Runs: 380115
    colliding_scheme_txt    = "../fill_schemes/Fill_9573/colliding_9573.txt"    # Fill=9573
    
# fit results #
fitResults_file             = {}
fitResults                  = {}
fitResults_file["9573"]     = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_9573_dead_and_noisy_noSectorRollSubdvision/RPC_fit_F9573_fitResults.json"
fitResults_file["8754"]     = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_8754/RPC_fit_F8754_fitResults.json"
with open(fitResults_file["9573"], "r") as f:
    fitResults["9573"]      = json.load(f)
with open(fitResults_file["8754"], "r") as f:
    fitResults["8754"]      = json.load(f)

HitRate_eta_2018            = {}
for station in ["RB1in","RB1out","RB2in","RB2out","RB3","RB4"]:
    HitRate_eta_2018[station]                           = {}
    for wheel in ["Wm2","Wm1","W0","Wp1","Wp2"]:
        HitRate_eta_2018[station][wheel]                = {}
        for bkg in ["inclusive", "delayed", "prompt"]:
            HitRate_eta_2018[station][wheel][bkg]       = 0

for disk in ["RE1","RE2","RE3","RE4"]:
    disk_number                                         = int(disk[-1])
    disk_chambers                                       = [f"REm{disk_number}{ring}_{part}" for ring in [2,3] for part in ["F","M","B"]] # negative endcap
    disk_chambers                                      += [f"REp{disk_number}{ring}_{part}" for ring in [3,2] for part in ["B","M","F"]] # positive endcap
    for chamber in disk_chambers:
        HitRate_eta_2018[chamber]                       = {}
        for bkg in ["inclusive", "delayed", "prompt"]:
            HitRate_eta_2018[chamber][bkg]              = 0


sectors         = ["S01","S02","S03","S04","S05","S06","S07","S08","S09","S10","S11","S12"]
############################
# Hit Rate values for 2018 #
############################
# BARREL #
HitRate_eta_2018["RB1in"]["Wm2"]["inclusive"]           = 5.36165
HitRate_eta_2018["RB1in"]["Wm1"]["inclusive"]           = 2.580828
HitRate_eta_2018["RB1in"]["W0"]["inclusive"]            = 0.9355827
HitRate_eta_2018["RB1in"]["Wp1"]["inclusive"]           = 2.529127
HitRate_eta_2018["RB1in"]["Wp2"]["inclusive"]           = 6.167103
HitRate_eta_2018["RB1in"]["Wm2"]["inclusive_mean"]      = 5.4
HitRate_eta_2018["RB1in"]["Wm1"]["inclusive_mean"]      = 2.6
HitRate_eta_2018["RB1in"]["W0"]["inclusive_mean"]       = 0.9
HitRate_eta_2018["RB1in"]["Wp1"]["inclusive_mean"]      = 3.6
HitRate_eta_2018["RB1in"]["Wp2"]["inclusive_mean"]      = 6.1
HitRate_eta_2018["RB1in"]["Wm2"]["inclusive_error"]     = 0.9
HitRate_eta_2018["RB1in"]["Wm1"]["inclusive_error"]     = 0.2
HitRate_eta_2018["RB1in"]["W0"]["inclusive_error"]      = 0.4
HitRate_eta_2018["RB1in"]["Wp1"]["inclusive_error"]     = 0.7
HitRate_eta_2018["RB1in"]["Wp2"]["inclusive_error"]     = 0.7

HitRate_eta_2018["RB1in"]["Wm2"]["delayed"]             = 3.491011
HitRate_eta_2018["RB1in"]["Wm1"]["delayed"]             = 1.923975
HitRate_eta_2018["RB1in"]["W0"]["delayed"]              = 0.593374
HitRate_eta_2018["RB1in"]["Wp1"]["delayed"]             = 1.867728
HitRate_eta_2018["RB1in"]["Wp2"]["delayed"]             = 4.00074
HitRate_eta_2018["RB1in"]["Wm2"]["delayed_mean"]        = 5.4
HitRate_eta_2018["RB1in"]["Wm1"]["delayed_mean"]        = 2.6
HitRate_eta_2018["RB1in"]["W0"]["delayed_mean"]         = 0.9
HitRate_eta_2018["RB1in"]["Wp1"]["delayed_mean"]        = 3.6
HitRate_eta_2018["RB1in"]["Wp2"]["delayed_mean"]        = 6.1
HitRate_eta_2018["RB1in"]["Wm2"]["delayed_error"]       = 0.9
HitRate_eta_2018["RB1in"]["Wm1"]["delayed_error"]       = 0.2
HitRate_eta_2018["RB1in"]["W0"]["delayed_error"]        = 0.4
HitRate_eta_2018["RB1in"]["Wp1"]["delayed_error"]       = 0.7
HitRate_eta_2018["RB1in"]["Wp2"]["delayed_error"]       = 0.7

HitRate_eta_2018["RB1in"]["Wm2"]["prompt"]              = 2.62066
HitRate_eta_2018["RB1in"]["Wm1"]["prompt"]              = 0.9202141
HitRate_eta_2018["RB1in"]["W0"]["prompt"]               = 0.4794151
HitRate_eta_2018["RB1in"]["Wp1"]["prompt"]              = 0.926582
HitRate_eta_2018["RB1in"]["Wp2"]["prompt"]              = 3.034952
HitRate_eta_2018["RB1in"]["Wm2"]["prompt_mean"]         = 5.4
HitRate_eta_2018["RB1in"]["Wm1"]["prompt_mean"]         = 2.6
HitRate_eta_2018["RB1in"]["W0"]["prompt_mean"]          = 0.9
HitRate_eta_2018["RB1in"]["Wp1"]["prompt_mean"]         = 3.6
HitRate_eta_2018["RB1in"]["Wp2"]["prompt_mean"]         = 6.1
HitRate_eta_2018["RB1in"]["Wm2"]["prompt_error"]        = 0.9
HitRate_eta_2018["RB1in"]["Wm1"]["prompt_error"]        = 0.2
HitRate_eta_2018["RB1in"]["W0"]["prompt_error"]         = 0.4
HitRate_eta_2018["RB1in"]["Wp1"]["prompt_error"]        = 0.7
HitRate_eta_2018["RB1in"]["Wp2"]["prompt_error"]        = 0.7


HitRate_eta_2018["RB1out"]["Wm2"]["inclusive"]          = 3.769397
HitRate_eta_2018["RB1out"]["Wm1"]["inclusive"]          = 2.003875
HitRate_eta_2018["RB1out"]["W0"]["inclusive"]           = 0.7811214
HitRate_eta_2018["RB1out"]["Wp1"]["inclusive"]          = 2.04832
HitRate_eta_2018["RB1out"]["Wp2"]["inclusive"]          = 3.882072
HitRate_eta_2018["RB1out"]["Wm2"]["inclusive_mean"]     = 4.4
HitRate_eta_2018["RB1out"]["Wm1"]["inclusive_mean"]     = 2.0
HitRate_eta_2018["RB1out"]["W0"]["inclusive_mean"]      = 0.8
HitRate_eta_2018["RB1out"]["Wp1"]["inclusive_mean"]     = 2.1
HitRate_eta_2018["RB1out"]["Wp2"]["inclusive_mean"]     = 4.5
HitRate_eta_2018["RB1out"]["Wm2"]["inclusive_error"]    = 0.7
HitRate_eta_2018["RB1out"]["Wm1"]["inclusive_error"]    = 0.4
HitRate_eta_2018["RB1out"]["W0"]["inclusive_error"]     = 0.2
HitRate_eta_2018["RB1out"]["Wp1"]["inclusive_error"]    = 0.6
HitRate_eta_2018["RB1out"]["Wp2"]["inclusive_error"]    = 0.9

HitRate_eta_2018["RB1out"]["Wm2"]["delayed"]            = 2.393656
HitRate_eta_2018["RB1out"]["Wm1"]["delayed"]            = 1.454743
HitRate_eta_2018["RB1out"]["W0"]["delayed"]             = 0.4790209
HitRate_eta_2018["RB1out"]["Wp1"]["delayed"]            = 1.526771
HitRate_eta_2018["RB1out"]["Wp2"]["delayed"]            = 2.443797
HitRate_eta_2018["RB1out"]["Wm2"]["delayed_mean"]        = 4.4
HitRate_eta_2018["RB1out"]["Wm1"]["delayed_mean"]        = 2.0
HitRate_eta_2018["RB1out"]["W0"]["delayed_mean"]         = 0.8
HitRate_eta_2018["RB1out"]["Wp1"]["delayed_mean"]        = 2.1
HitRate_eta_2018["RB1out"]["Wp2"]["delayed_mean"]        = 4.5
HitRate_eta_2018["RB1out"]["Wm2"]["delayed_error"]      = 0.7
HitRate_eta_2018["RB1out"]["Wm1"]["delayed_error"]      = 0.4
HitRate_eta_2018["RB1out"]["W0"]["delayed_error"]       = 0.2
HitRate_eta_2018["RB1out"]["Wp1"]["delayed_error"]      = 0.6
HitRate_eta_2018["RB1out"]["Wp2"]["delayed_error"]      = 0.9

HitRate_eta_2018["RB1out"]["Wm2"]["prompt"]             = 1.927336
HitRate_eta_2018["RB1out"]["Wm1"]["prompt"]             = 0.7693025
HitRate_eta_2018["RB1out"]["W0"]["prompt"]              = 0.4232257
HitRate_eta_2018["RB1out"]["Wp1"]["prompt"]             = 0.7306607
HitRate_eta_2018["RB1out"]["Wp2"]["prompt"]             = 2.014943
HitRate_eta_2018["RB1out"]["Wm2"]["prompt_mean"]         = 4.4
HitRate_eta_2018["RB1out"]["Wm1"]["prompt_mean"]         = 2.0
HitRate_eta_2018["RB1out"]["W0"]["prompt_mean"]          = 0.8
HitRate_eta_2018["RB1out"]["Wp1"]["prompt_mean"]         = 2.1
HitRate_eta_2018["RB1out"]["Wp2"]["prompt_mean"]         = 4.5
HitRate_eta_2018["RB1out"]["Wm2"]["prompt_error"]       = 0.7
HitRate_eta_2018["RB1out"]["Wm1"]["prompt_error"]       = 0.4
HitRate_eta_2018["RB1out"]["W0"]["prompt_error"]        = 0.2
HitRate_eta_2018["RB1out"]["Wp1"]["prompt_error"]       = 0.6
HitRate_eta_2018["RB1out"]["Wp2"]["prompt_error"]       = 0.9


HitRate_eta_2018["RB2in"]["Wm2"]["inclusive"]           = 1.160811
HitRate_eta_2018["RB2in"]["Wm1"]["inclusive"]           = 0.5172624
HitRate_eta_2018["RB2in"]["W0"]["inclusive"]            = 0.3267708
HitRate_eta_2018["RB2in"]["Wp1"]["inclusive"]           = 0.5353142
HitRate_eta_2018["RB2in"]["Wp2"]["inclusive"]           = 1.101844
HitRate_eta_2018["RB2in"]["Wm2"]["inclusive_mean"]      = 1.2
HitRate_eta_2018["RB2in"]["Wm1"]["inclusive_mean"]      = 0.5
HitRate_eta_2018["RB2in"]["W0"]["inclusive_mean"]       = 0.5
HitRate_eta_2018["RB2in"]["Wp1"]["inclusive_mean"]      = 0.9
HitRate_eta_2018["RB2in"]["Wp2"]["inclusive_mean"]      = 1.1
HitRate_eta_2018["RB2in"]["Wm2"]["inclusive_error"]     = 0.8
HitRate_eta_2018["RB2in"]["Wm1"]["inclusive_error"]     = 0.1
HitRate_eta_2018["RB2in"]["W0"]["inclusive_error"]      = 0.1
HitRate_eta_2018["RB2in"]["Wp1"]["inclusive_error"]     = 0.2
HitRate_eta_2018["RB2in"]["Wp2"]["inclusive_error"]     = 0.3

HitRate_eta_2018["RB2in"]["Wm2"]["delayed"]             = 0.8429186
HitRate_eta_2018["RB2in"]["Wm1"]["delayed"]             = 0.3524153
HitRate_eta_2018["RB2in"]["W0"]["delayed"]              = 0.1998048
HitRate_eta_2018["RB2in"]["Wp1"]["delayed"]             = 0.3691587
HitRate_eta_2018["RB2in"]["Wp2"]["delayed"]             = 0.80101
HitRate_eta_2018["RB2in"]["Wm2"]["delayed_mean"]        = 1.2
HitRate_eta_2018["RB2in"]["Wm1"]["delayed_mean"]        = 0.5
HitRate_eta_2018["RB2in"]["W0"]["delayed_mean"]         = 0.5
HitRate_eta_2018["RB2in"]["Wp1"]["delayed_mean"]        = 0.9
HitRate_eta_2018["RB2in"]["Wp2"]["delayed_mean"]        = 1.1
HitRate_eta_2018["RB2in"]["Wm2"]["delayed_error"]       = 0.8
HitRate_eta_2018["RB2in"]["Wm1"]["delayed_error"]       = 0.1
HitRate_eta_2018["RB2in"]["W0"]["delayed_error"]        = 0.1
HitRate_eta_2018["RB2in"]["Wp1"]["delayed_error"]       = 0.2
HitRate_eta_2018["RB2in"]["Wp2"]["delayed_error"]       = 0.3

HitRate_eta_2018["RB2in"]["Wm2"]["prompt"]              = 0.4453495
HitRate_eta_2018["RB2in"]["Wm1"]["prompt"]              = 0.2309414
HitRate_eta_2018["RB2in"]["W0"]["prompt"]               = 0.1778722
HitRate_eta_2018["RB2in"]["Wp1"]["prompt"]              = 0.2327744
HitRate_eta_2018["RB2in"]["Wp2"]["prompt"]              = 0.4214508
HitRate_eta_2018["RB2in"]["Wm2"]["prompt_mean"]         = 1.2
HitRate_eta_2018["RB2in"]["Wm1"]["prompt_mean"]         = 0.5
HitRate_eta_2018["RB2in"]["W0"]["prompt_mean"]          = 0.5
HitRate_eta_2018["RB2in"]["Wp1"]["prompt_mean"]         = 0.9
HitRate_eta_2018["RB2in"]["Wp2"]["prompt_mean"]         = 1.1
HitRate_eta_2018["RB2in"]["Wm2"]["prompt_error"]        = 0.8
HitRate_eta_2018["RB2in"]["Wm1"]["prompt_error"]        = 0.1
HitRate_eta_2018["RB2in"]["W0"]["prompt_error"]         = 0.1
HitRate_eta_2018["RB2in"]["Wp1"]["prompt_error"]        = 0.2
HitRate_eta_2018["RB2in"]["Wp2"]["prompt_error"]        = 0.3


HitRate_eta_2018["RB2out"]["Wm2"]["inclusive"]          = 1.165005
HitRate_eta_2018["RB2out"]["Wm1"]["inclusive"]          = 0.4718886
HitRate_eta_2018["RB2out"]["W0"]["inclusive"]           = 0.3315379
HitRate_eta_2018["RB2out"]["Wp1"]["inclusive"]          = 0.4293282
HitRate_eta_2018["RB2out"]["Wp2"]["inclusive"]          = 1.093243
HitRate_eta_2018["RB2out"]["Wm2"]["inclusive_mean"]     = 1.2
HitRate_eta_2018["RB2out"]["Wm1"]["inclusive_mean"]     = 0.5
HitRate_eta_2018["RB2out"]["W0"]["inclusive_mean"]      = 0.4
HitRate_eta_2018["RB2out"]["Wp1"]["inclusive_mean"]     = 0.5
HitRate_eta_2018["RB2out"]["Wp2"]["inclusive_mean"]     = 1.1
HitRate_eta_2018["RB2out"]["Wm2"]["inclusive_error"]    = 0.2
HitRate_eta_2018["RB2out"]["Wm1"]["inclusive_error"]    = 0.2
HitRate_eta_2018["RB2out"]["W0"]["inclusive_error"]     = 0.2
HitRate_eta_2018["RB2out"]["Wp1"]["inclusive_error"]    = 0.1
HitRate_eta_2018["RB2out"]["Wp2"]["inclusive_error"]    = 0.3

HitRate_eta_2018["RB2out"]["Wm2"]["delayed"]            = 0.8859977
HitRate_eta_2018["RB2out"]["Wm1"]["delayed"]            = 0.336582
HitRate_eta_2018["RB2out"]["W0"]["delayed"]             = 0.22917
HitRate_eta_2018["RB2out"]["Wp1"]["delayed"]            = 0.2996905
HitRate_eta_2018["RB2out"]["Wp2"]["delayed"]            = 0.826861
HitRate_eta_2018["RB2out"]["Wm2"]["delayed_mean"]       = 1.2
HitRate_eta_2018["RB2out"]["Wm1"]["delayed_mean"]       = 0.5
HitRate_eta_2018["RB2out"]["W0"]["delayed_mean"]        = 0.4
HitRate_eta_2018["RB2out"]["Wp1"]["delayed_mean"]       = 0.5
HitRate_eta_2018["RB2out"]["Wp2"]["delayed_mean"]       = 1.1
HitRate_eta_2018["RB2out"]["Wm2"]["delayed_error"]      = 0.2
HitRate_eta_2018["RB2out"]["Wm1"]["delayed_error"]      = 0.2
HitRate_eta_2018["RB2out"]["W0"]["delayed_error"]       = 0.2
HitRate_eta_2018["RB2out"]["Wp1"]["delayed_error"]      = 0.1
HitRate_eta_2018["RB2out"]["Wp2"]["delayed_error"]      = 0.3

HitRate_eta_2018["RB2out"]["Wm2"]["prompt"]             = 0.390873
HitRate_eta_2018["RB2out"]["Wm1"]["prompt"]             = 0.1895569
HitRate_eta_2018["RB2out"]["W0"]["prompt"]              = 0.1434117
HitRate_eta_2018["RB2out"]["Wp1"]["prompt"]             = 0.1816151
HitRate_eta_2018["RB2out"]["Wp2"]["prompt"]             = 0.373186
HitRate_eta_2018["RB2out"]["Wm2"]["prompt_mean"]        = 1.2
HitRate_eta_2018["RB2out"]["Wm1"]["prompt_mean"]        = 0.5
HitRate_eta_2018["RB2out"]["W0"]["prompt_mean"]         = 0.4
HitRate_eta_2018["RB2out"]["Wp1"]["prompt_mean"]        = 0.5
HitRate_eta_2018["RB2out"]["Wp2"]["prompt_mean"]        = 1.1
HitRate_eta_2018["RB2out"]["Wm2"]["prompt_error"]       = 0.2
HitRate_eta_2018["RB2out"]["Wm1"]["prompt_error"]       = 0.2
HitRate_eta_2018["RB2out"]["W0"]["prompt_error"]        = 0.2
HitRate_eta_2018["RB2out"]["Wp1"]["prompt_error"]       = 0.1
HitRate_eta_2018["RB2out"]["Wp2"]["prompt_error"]       = 0.3


HitRate_eta_2018["RB3"]["Wm2"]["inclusive"]             = 0.2623352
HitRate_eta_2018["RB3"]["Wm1"]["inclusive"]             = 0.1827559
HitRate_eta_2018["RB3"]["W0"]["inclusive"]              = 0.1875751
HitRate_eta_2018["RB3"]["Wp1"]["inclusive"]             = 0.2521998
HitRate_eta_2018["RB3"]["Wp2"]["inclusive"]             = 0.4336728
HitRate_eta_2018["RB3"]["Wm2"]["inclusive_mean"]        = 0.3
HitRate_eta_2018["RB3"]["Wm1"]["inclusive_mean"]        = 0.1
HitRate_eta_2018["RB3"]["W0"]["inclusive_mean"]         = 0.3
HitRate_eta_2018["RB3"]["Wp1"]["inclusive_mean"]        = 0.3
HitRate_eta_2018["RB3"]["Wp2"]["inclusive_mean"]        = 0.4
HitRate_eta_2018["RB3"]["Wm2"]["inclusive_error"]       = 0.1
HitRate_eta_2018["RB3"]["Wm1"]["inclusive_error"]       = 0.1
HitRate_eta_2018["RB3"]["W0"]["inclusive_error"]        = 0.1
HitRate_eta_2018["RB3"]["Wp1"]["inclusive_error"]       = 0.4
HitRate_eta_2018["RB3"]["Wp2"]["inclusive_error"]       = 0.4

HitRate_eta_2018["RB3"]["Wm2"]["delayed"]               = 0.2330214
HitRate_eta_2018["RB3"]["Wm1"]["delayed"]               = 0.148823
HitRate_eta_2018["RB3"]["W0"]["delayed"]                = 0.1613727
HitRate_eta_2018["RB3"]["Wp1"]["delayed"]               = 0.2170564
HitRate_eta_2018["RB3"]["Wp2"]["delayed"]               = 0.4030725
HitRate_eta_2018["RB3"]["Wm2"]["delayed_mean"]          = 0.3
HitRate_eta_2018["RB3"]["Wm1"]["delayed_mean"]          = 0.1
HitRate_eta_2018["RB3"]["W0"]["delayed_mean"]           = 0.3
HitRate_eta_2018["RB3"]["Wp1"]["delayed_mean"]          = 0.3
HitRate_eta_2018["RB3"]["Wp2"]["delayed_mean"]          = 0.4
HitRate_eta_2018["RB3"]["Wm2"]["delayed_error"]         = 0.1
HitRate_eta_2018["RB3"]["Wm1"]["delayed_error"]         = 0.1
HitRate_eta_2018["RB3"]["W0"]["delayed_error"]          = 0.1
HitRate_eta_2018["RB3"]["Wp1"]["delayed_error"]         = 0.4
HitRate_eta_2018["RB3"]["Wp2"]["delayed_error"]         = 0.4

HitRate_eta_2018["RB3"]["Wm2"]["prompt"]                = 0.04106692
HitRate_eta_2018["RB3"]["Wm1"]["prompt"]                = 0.04753815
HitRate_eta_2018["RB3"]["W0"]["prompt"]                 = 0.03670805
HitRate_eta_2018["RB3"]["Wp1"]["prompt"]                = 0.04923401
HitRate_eta_2018["RB3"]["Wp2"]["prompt"]                = 0.04286926
HitRate_eta_2018["RB3"]["Wm2"]["prompt_mean"]           = 0.3
HitRate_eta_2018["RB3"]["Wm1"]["prompt_mean"]           = 0.1
HitRate_eta_2018["RB3"]["W0"]["prompt_mean"]            = 0.3
HitRate_eta_2018["RB3"]["Wp1"]["prompt_mean"]           = 0.3
HitRate_eta_2018["RB3"]["Wp2"]["prompt_mean"]           = 0.4
HitRate_eta_2018["RB3"]["Wm2"]["prompt_error"]          = 0.1
HitRate_eta_2018["RB3"]["Wm1"]["prompt_error"]          = 0.1
HitRate_eta_2018["RB3"]["W0"]["prompt_error"]           = 0.1
HitRate_eta_2018["RB3"]["Wp1"]["prompt_error"]          = 0.4
HitRate_eta_2018["RB3"]["Wp2"]["prompt_error"]          = 0.4


HitRate_eta_2018["RB4"]["Wm2"]["inclusive"]             = 2.765997 
HitRate_eta_2018["RB4"]["Wm1"]["inclusive"]             = 2.617135 
HitRate_eta_2018["RB4"]["W0"]["inclusive"]              = 2.67305 
HitRate_eta_2018["RB4"]["Wp1"]["inclusive"]             = 3.191337 
HitRate_eta_2018["RB4"]["Wp2"]["inclusive"]             = 4.141577
HitRate_eta_2018["RB4"]["Wm2"]["inclusive_mean"]        = 3
HitRate_eta_2018["RB4"]["Wm1"]["inclusive_mean"]        = 3
HitRate_eta_2018["RB4"]["W0"]["inclusive_mean"]         = 3
HitRate_eta_2018["RB4"]["Wp1"]["inclusive_mean"]        = 3
HitRate_eta_2018["RB4"]["Wp2"]["inclusive_mean"]        = 4
HitRate_eta_2018["RB4"]["Wm2"]["inclusive_error"]       = 2
HitRate_eta_2018["RB4"]["Wm1"]["inclusive_error"]       = 2
HitRate_eta_2018["RB4"]["W0"]["inclusive_error"]        = 2
HitRate_eta_2018["RB4"]["Wp1"]["inclusive_error"]       = 2
HitRate_eta_2018["RB4"]["Wp2"]["inclusive_error"]       = 3

HitRate_eta_2018["RB4"]["Wm2"]["delayed"]               = 2.735156 
HitRate_eta_2018["RB4"]["Wm1"]["delayed"]               = 2.594586 
HitRate_eta_2018["RB4"]["W0"]["delayed"]                = 2.65658 
HitRate_eta_2018["RB4"]["Wp1"]["delayed"]               = 3.165386 
HitRate_eta_2018["RB4"]["Wp2"]["delayed"]               = 4.097827
HitRate_eta_2018["RB4"]["Wm2"]["delayed_mean"]          = 3
HitRate_eta_2018["RB4"]["Wm1"]["delayed_mean"]          = 3
HitRate_eta_2018["RB4"]["W0"]["delayed_mean"]           = 3
HitRate_eta_2018["RB4"]["Wp1"]["delayed_mean"]          = 3
HitRate_eta_2018["RB4"]["Wp2"]["delayed_mean"]          = 4
HitRate_eta_2018["RB4"]["Wm2"]["delayed_error"]         = 2
HitRate_eta_2018["RB4"]["Wm1"]["delayed_error"]         = 2
HitRate_eta_2018["RB4"]["W0"]["delayed_error"]          = 2
HitRate_eta_2018["RB4"]["Wp1"]["delayed_error"]         = 2
HitRate_eta_2018["RB4"]["Wp2"]["delayed_error"]         = 3

HitRate_eta_2018["RB4"]["Wm2"]["prompt"]                = 0.04320676 
HitRate_eta_2018["RB4"]["Wm1"]["prompt"]                = 0.03159024 
HitRate_eta_2018["RB4"]["W0"]["prompt"]                 = 0.02307343 
HitRate_eta_2018["RB4"]["Wp1"]["prompt"]                = 0.03635602 
HitRate_eta_2018["RB4"]["Wp2"]["prompt"]                = 0.06129187
HitRate_eta_2018["RB4"]["Wm2"]["prompt_mean"]           = 3
HitRate_eta_2018["RB4"]["Wm1"]["prompt_mean"]           = 3
HitRate_eta_2018["RB4"]["W0"]["prompt_mean"]            = 3
HitRate_eta_2018["RB4"]["Wp1"]["prompt_mean"]           = 3
HitRate_eta_2018["RB4"]["Wp2"]["prompt_mean"]           = 4
HitRate_eta_2018["RB4"]["Wm2"]["prompt_error"]          = 2
HitRate_eta_2018["RB4"]["Wm1"]["prompt_error"]          = 2
HitRate_eta_2018["RB4"]["W0"]["prompt_error"]           = 2
HitRate_eta_2018["RB4"]["Wp1"]["prompt_error"]          = 2
HitRate_eta_2018["RB4"]["Wp2"]["prompt_error"]          = 3

# ENDCAP #
HitRate_eta_2018["REm12_F"]["inclusive"]        = 5.236387
HitRate_eta_2018["REm12_M"]["inclusive"]        = 2.879595
HitRate_eta_2018["REm12_B"]["inclusive"]        = 1.936665
HitRate_eta_2018["REm13_F"]["inclusive"]        = 0.8585267
HitRate_eta_2018["REm13_M"]["inclusive"]        = 0.725612
HitRate_eta_2018["REm13_B"]["inclusive"]        = 2.37269
HitRate_eta_2018["REp13_B"]["inclusive"]        = 2.37269
HitRate_eta_2018["REp13_M"]["inclusive"]        = 0.725612
HitRate_eta_2018["REp13_F"]["inclusive"]        = 0.8585267
HitRate_eta_2018["REp12_B"]["inclusive"]        = 1.936665
HitRate_eta_2018["REp12_M"]["inclusive"]        = 2.879595
HitRate_eta_2018["REp12_F"]["inclusive"]        = 5.236387
HitRate_eta_2018["REm12_F"]["inclusive_mean"]   = 3.5
HitRate_eta_2018["REm12_M"]["inclusive_mean"]   = 3.5
HitRate_eta_2018["REm12_B"]["inclusive_mean"]   = 3.5
HitRate_eta_2018["REm13_F"]["inclusive_mean"]   = 1.3
HitRate_eta_2018["REm13_M"]["inclusive_mean"]   = 1.3
HitRate_eta_2018["REm13_B"]["inclusive_mean"]   = 1.3
HitRate_eta_2018["REp13_B"]["inclusive_mean"]   = 1.1
HitRate_eta_2018["REp13_M"]["inclusive_mean"]   = 1.1
HitRate_eta_2018["REp13_F"]["inclusive_mean"]   = 1.1
HitRate_eta_2018["REp12_B"]["inclusive_mean"]   = 3.4
HitRate_eta_2018["REp12_M"]["inclusive_mean"]   = 3.4
HitRate_eta_2018["REp12_F"]["inclusive_mean"]   = 3.4
HitRate_eta_2018["REm12_F"]["inclusive_error"]  = 0.2
HitRate_eta_2018["REm12_M"]["inclusive_error"]  = 0.2
HitRate_eta_2018["REm12_B"]["inclusive_error"]  = 0.2
HitRate_eta_2018["REm13_F"]["inclusive_error"]  = 0.5
HitRate_eta_2018["REm13_M"]["inclusive_error"]  = 0.5
HitRate_eta_2018["REm13_B"]["inclusive_error"]  = 0.5
HitRate_eta_2018["REp13_B"]["inclusive_error"]  = 0.3
HitRate_eta_2018["REp13_M"]["inclusive_error"]  = 0.3
HitRate_eta_2018["REp13_F"]["inclusive_error"]  = 0.3
HitRate_eta_2018["REp12_B"]["inclusive_error"]  = 0.4
HitRate_eta_2018["REp12_M"]["inclusive_error"]  = 0.4
HitRate_eta_2018["REp12_F"]["inclusive_error"]  = 0.4

HitRate_eta_2018["REm12_F"]["delayed"]          = 3.081103
HitRate_eta_2018["REm12_M"]["delayed"]          = 1.96303
HitRate_eta_2018["REm12_B"]["delayed"]          = 1.279001
HitRate_eta_2018["REm13_F"]["delayed"]          = 0.6011889
HitRate_eta_2018["REm13_M"]["delayed"]          = 0.6071028
HitRate_eta_2018["REm13_B"]["delayed"]          = 2.327107
HitRate_eta_2018["REp13_B"]["delayed"]          = 2.327107
HitRate_eta_2018["REp13_M"]["delayed"]          = 0.6071028
HitRate_eta_2018["REp13_F"]["delayed"]          = 0.6011889
HitRate_eta_2018["REp12_B"]["delayed"]          = 1.279001
HitRate_eta_2018["REp12_M"]["delayed"]          = 1.96303
HitRate_eta_2018["REp12_F"]["delayed"]          = 3.081103
HitRate_eta_2018["REm12_F"]["delayed_mean"]     = 3.5
HitRate_eta_2018["REm12_M"]["delayed_mean"]     = 3.5
HitRate_eta_2018["REm12_B"]["delayed_mean"]     = 3.5
HitRate_eta_2018["REm13_F"]["delayed_mean"]     = 1.3
HitRate_eta_2018["REm13_M"]["delayed_mean"]     = 1.3
HitRate_eta_2018["REm13_B"]["delayed_mean"]     = 1.3
HitRate_eta_2018["REp13_B"]["delayed_mean"]     = 1.1
HitRate_eta_2018["REp13_M"]["delayed_mean"]     = 1.1
HitRate_eta_2018["REp13_F"]["delayed_mean"]     = 1.1
HitRate_eta_2018["REp12_B"]["delayed_mean"]     = 3.4
HitRate_eta_2018["REp12_M"]["delayed_mean"]     = 3.4
HitRate_eta_2018["REp12_F"]["delayed_mean"]     = 3.4
HitRate_eta_2018["REm12_F"]["delayed_error"]    = 0.2
HitRate_eta_2018["REm12_M"]["delayed_error"]    = 0.2
HitRate_eta_2018["REm12_B"]["delayed_error"]    = 0.2
HitRate_eta_2018["REm13_F"]["delayed_error"]    = 0.5
HitRate_eta_2018["REm13_M"]["delayed_error"]    = 0.5
HitRate_eta_2018["REm13_B"]["delayed_error"]    = 0.5
HitRate_eta_2018["REp13_B"]["delayed_error"]    = 0.3
HitRate_eta_2018["REp13_M"]["delayed_error"]    = 0.3
HitRate_eta_2018["REp13_F"]["delayed_error"]    = 0.3
HitRate_eta_2018["REp12_B"]["delayed_error"]    = 0.4
HitRate_eta_2018["REp12_M"]["delayed_error"]    = 0.4
HitRate_eta_2018["REp12_F"]["delayed_error"]    = 0.4

HitRate_eta_2018["REm12_F"]["prompt"]           = 3.019432
HitRate_eta_2018["REm12_M"]["prompt"]           = 1.284056
HitRate_eta_2018["REm12_B"]["prompt"]           = 0.9213513
HitRate_eta_2018["REm13_F"]["prompt"]           = 0.3605157
HitRate_eta_2018["REm13_M"]["prompt"]           = 0.1660246
HitRate_eta_2018["REm13_B"]["prompt"]           = 0.06385903
HitRate_eta_2018["REp13_B"]["prompt"]           = 0.06385903
HitRate_eta_2018["REp13_M"]["prompt"]           = 0.1660246
HitRate_eta_2018["REp13_F"]["prompt"]           = 0.3605157
HitRate_eta_2018["REp12_B"]["prompt"]           = 0.9213513
HitRate_eta_2018["REp12_M"]["prompt"]           = 1.284056
HitRate_eta_2018["REp12_F"]["prompt"]           = 3.019432
HitRate_eta_2018["REm12_F"]["prompt_mean"]      = 3.5
HitRate_eta_2018["REm12_M"]["prompt_mean"]      = 3.5
HitRate_eta_2018["REm12_B"]["prompt_mean"]      = 3.5
HitRate_eta_2018["REm13_F"]["prompt_mean"]      = 1.3
HitRate_eta_2018["REm13_M"]["prompt_mean"]      = 1.3
HitRate_eta_2018["REm13_B"]["prompt_mean"]      = 1.3
HitRate_eta_2018["REp13_B"]["prompt_mean"]      = 1.1
HitRate_eta_2018["REp13_M"]["prompt_mean"]      = 1.1
HitRate_eta_2018["REp13_F"]["prompt_mean"]      = 1.1
HitRate_eta_2018["REp12_B"]["prompt_mean"]      = 3.4
HitRate_eta_2018["REp12_M"]["prompt_mean"]      = 3.4
HitRate_eta_2018["REp12_F"]["prompt_mean"]      = 3.4
HitRate_eta_2018["REm12_F"]["prompt_error"]     = 0.2
HitRate_eta_2018["REm12_M"]["prompt_error"]     = 0.2
HitRate_eta_2018["REm12_B"]["prompt_error"]     = 0.2
HitRate_eta_2018["REm13_F"]["prompt_error"]     = 0.5
HitRate_eta_2018["REm13_M"]["prompt_error"]     = 0.5
HitRate_eta_2018["REm13_B"]["prompt_error"]     = 0.5
HitRate_eta_2018["REp13_B"]["prompt_error"]     = 0.3
HitRate_eta_2018["REp13_M"]["prompt_error"]     = 0.3
HitRate_eta_2018["REp13_F"]["prompt_error"]     = 0.3
HitRate_eta_2018["REp12_B"]["prompt_error"]     = 0.4
HitRate_eta_2018["REp12_M"]["prompt_error"]     = 0.4
HitRate_eta_2018["REp12_F"]["prompt_error"]     = 0.4



HitRate_eta_2018["REm22_F"]["inclusive"]        = 10.91619
HitRate_eta_2018["REm22_M"]["inclusive"]        = 5.852738
HitRate_eta_2018["REm22_B"]["inclusive"]        = 2.909909
HitRate_eta_2018["REm23_F"]["inclusive"]        = 1.769396
HitRate_eta_2018["REm23_M"]["inclusive"]        = 1.659876
HitRate_eta_2018["REm23_B"]["inclusive"]        = 2.127818
HitRate_eta_2018["REp23_B"]["inclusive"]        = 2.127818
HitRate_eta_2018["REp23_M"]["inclusive"]        = 1.659876
HitRate_eta_2018["REp23_F"]["inclusive"]        = 1.769396
HitRate_eta_2018["REp22_B"]["inclusive"]        = 2.909909
HitRate_eta_2018["REp22_M"]["inclusive"]        = 5.852738
HitRate_eta_2018["REp22_F"]["inclusive"]        = 10.91619
HitRate_eta_2018["REm22_F"]["inclusive_mean"]   = 6.0
HitRate_eta_2018["REm22_M"]["inclusive_mean"]   = 6.0
HitRate_eta_2018["REm22_B"]["inclusive_mean"]   = 6.0
HitRate_eta_2018["REm23_F"]["inclusive_mean"]   = 1.8
HitRate_eta_2018["REm23_M"]["inclusive_mean"]   = 1.8
HitRate_eta_2018["REm23_B"]["inclusive_mean"]   = 1.8
HitRate_eta_2018["REp23_B"]["inclusive_mean"]   = 1.8
HitRate_eta_2018["REp23_M"]["inclusive_mean"]   = 1.8
HitRate_eta_2018["REp23_F"]["inclusive_mean"]   = 1.8
HitRate_eta_2018["REp22_B"]["inclusive_mean"]   = 5.8
HitRate_eta_2018["REp22_M"]["inclusive_mean"]   = 5.8
HitRate_eta_2018["REp22_F"]["inclusive_mean"]   = 5.8
HitRate_eta_2018["REm22_F"]["inclusive_error"]  = 0.2
HitRate_eta_2018["REm22_M"]["inclusive_error"]  = 0.2
HitRate_eta_2018["REm22_B"]["inclusive_error"]  = 0.2
HitRate_eta_2018["REm23_F"]["inclusive_error"]  = 0.4
HitRate_eta_2018["REm23_M"]["inclusive_error"]  = 0.4
HitRate_eta_2018["REm23_B"]["inclusive_error"]  = 0.4
HitRate_eta_2018["REp23_B"]["inclusive_error"]  = 0.2
HitRate_eta_2018["REp23_M"]["inclusive_error"]  = 0.2
HitRate_eta_2018["REp23_F"]["inclusive_error"]  = 0.2
HitRate_eta_2018["REp22_B"]["inclusive_error"]  = 0.4
HitRate_eta_2018["REp22_M"]["inclusive_error"]  = 0.4
HitRate_eta_2018["REp22_F"]["inclusive_error"]  = 0.4

HitRate_eta_2018["REm22_F"]["delayed"]          = 8.245262
HitRate_eta_2018["REm22_M"]["delayed"]          = 4.49321
HitRate_eta_2018["REm22_B"]["delayed"]          = 2.232501
HitRate_eta_2018["REm23_F"]["delayed"]          = 1.40012
HitRate_eta_2018["REm23_M"]["delayed"]          = 1.426659
HitRate_eta_2018["REm23_B"]["delayed"]          = 1.97441
HitRate_eta_2018["REp23_B"]["delayed"]          = 1.97441
HitRate_eta_2018["REp23_M"]["delayed"]          = 1.426659
HitRate_eta_2018["REp23_F"]["delayed"]          = 1.40012
HitRate_eta_2018["REp22_B"]["delayed"]          = 2.232501
HitRate_eta_2018["REp22_M"]["delayed"]          = 4.49321
HitRate_eta_2018["REp22_F"]["delayed"]          = 8.245262
HitRate_eta_2018["REm22_F"]["delayed_mean"]     = 6.0
HitRate_eta_2018["REm22_M"]["delayed_mean"]     = 6.0
HitRate_eta_2018["REm22_B"]["delayed_mean"]     = 6.0
HitRate_eta_2018["REm23_F"]["delayed_mean"]     = 1.8
HitRate_eta_2018["REm23_M"]["delayed_mean"]     = 1.8
HitRate_eta_2018["REm23_B"]["delayed_mean"]     = 1.8
HitRate_eta_2018["REp23_B"]["delayed_mean"]     = 1.8
HitRate_eta_2018["REp23_M"]["delayed_mean"]     = 1.8
HitRate_eta_2018["REp23_F"]["delayed_mean"]     = 1.8
HitRate_eta_2018["REp22_B"]["delayed_mean"]     = 5.8
HitRate_eta_2018["REp22_M"]["delayed_mean"]     = 5.8
HitRate_eta_2018["REp22_F"]["delayed_mean"]     = 5.8
HitRate_eta_2018["REm22_F"]["delayed_error"]    = 0.2
HitRate_eta_2018["REm22_M"]["delayed_error"]    = 0.2
HitRate_eta_2018["REm22_B"]["delayed_error"]    = 0.2
HitRate_eta_2018["REm23_F"]["delayed_error"]    = 0.4
HitRate_eta_2018["REm23_M"]["delayed_error"]    = 0.4
HitRate_eta_2018["REm23_B"]["delayed_error"]    = 0.4
HitRate_eta_2018["REp23_B"]["delayed_error"]    = 0.2
HitRate_eta_2018["REp23_M"]["delayed_error"]    = 0.2
HitRate_eta_2018["REp23_F"]["delayed_error"]    = 0.2
HitRate_eta_2018["REp22_B"]["delayed_error"]    = 0.4
HitRate_eta_2018["REp22_M"]["delayed_error"]    = 0.4
HitRate_eta_2018["REp22_F"]["delayed_error"]    = 0.4

HitRate_eta_2018["REm22_F"]["prompt"]           = 3.741817
HitRate_eta_2018["REm22_M"]["prompt"]           = 1.904622
HitRate_eta_2018["REm22_B"]["prompt"]           = 0.94901
HitRate_eta_2018["REm23_F"]["prompt"]           = 0.5173358
HitRate_eta_2018["REm23_M"]["prompt"]           = 0.3267228
HitRate_eta_2018["REm23_B"]["prompt"]           = 0.2149157
HitRate_eta_2018["REp23_B"]["prompt"]           = 0.2149157
HitRate_eta_2018["REp23_M"]["prompt"]           = 0.3267228
HitRate_eta_2018["REp23_F"]["prompt"]           = 0.5173358
HitRate_eta_2018["REp22_B"]["prompt"]           = 0.94901
HitRate_eta_2018["REp22_M"]["prompt"]           = 1.904622
HitRate_eta_2018["REp22_F"]["prompt"]           = 3.741817
HitRate_eta_2018["REm22_F"]["prompt_mean"]      = 6.0
HitRate_eta_2018["REm22_M"]["prompt_mean"]      = 6.0
HitRate_eta_2018["REm22_B"]["prompt_mean"]      = 6.0
HitRate_eta_2018["REm23_F"]["prompt_mean"]      = 1.8
HitRate_eta_2018["REm23_M"]["prompt_mean"]      = 1.8
HitRate_eta_2018["REm23_B"]["prompt_mean"]      = 1.8
HitRate_eta_2018["REp23_B"]["prompt_mean"]      = 1.8
HitRate_eta_2018["REp23_M"]["prompt_mean"]      = 1.8
HitRate_eta_2018["REp23_F"]["prompt_mean"]      = 1.8
HitRate_eta_2018["REp22_B"]["prompt_mean"]      = 5.8
HitRate_eta_2018["REp22_M"]["prompt_mean"]      = 5.8
HitRate_eta_2018["REp22_F"]["prompt_mean"]      = 5.8
HitRate_eta_2018["REm22_F"]["prompt_error"]     = 0.2
HitRate_eta_2018["REm22_M"]["prompt_error"]     = 0.2
HitRate_eta_2018["REm22_B"]["prompt_error"]     = 0.2
HitRate_eta_2018["REm23_F"]["prompt_error"]     = 0.4
HitRate_eta_2018["REm23_M"]["prompt_error"]     = 0.4
HitRate_eta_2018["REm23_B"]["prompt_error"]     = 0.4
HitRate_eta_2018["REp23_B"]["prompt_error"]     = 0.2
HitRate_eta_2018["REp23_M"]["prompt_error"]     = 0.2
HitRate_eta_2018["REp23_F"]["prompt_error"]     = 0.2
HitRate_eta_2018["REp22_B"]["prompt_error"]     = 0.4
HitRate_eta_2018["REp22_M"]["prompt_error"]     = 0.4
HitRate_eta_2018["REp22_F"]["prompt_error"]     = 0.4



HitRate_eta_2018["REm32_F"]["inclusive"]        = 9.750108
HitRate_eta_2018["REm32_M"]["inclusive"]        = 6.017883
HitRate_eta_2018["REm32_B"]["inclusive"]        = 3.328148
HitRate_eta_2018["REm33_F"]["inclusive"]        = 2.48076
HitRate_eta_2018["REm33_M"]["inclusive"]        = 2.566075
HitRate_eta_2018["REm33_B"]["inclusive"]        = 3.015256
HitRate_eta_2018["REp33_B"]["inclusive"]        = 3.015256
HitRate_eta_2018["REp33_M"]["inclusive"]        = 2.566075
HitRate_eta_2018["REp33_F"]["inclusive"]        = 2.48076
HitRate_eta_2018["REp32_B"]["inclusive"]        = 3.328148
HitRate_eta_2018["REp32_M"]["inclusive"]        = 6.017883
HitRate_eta_2018["REp32_F"]["inclusive"]        = 9.750108
HitRate_eta_2018["REm32_F"]["inclusive_mean"]   = 5.6
HitRate_eta_2018["REm32_M"]["inclusive_mean"]   = 5.6
HitRate_eta_2018["REm32_B"]["inclusive_mean"]   = 5.6
HitRate_eta_2018["REm33_F"]["inclusive_mean"]   = 2.6
HitRate_eta_2018["REm33_M"]["inclusive_mean"]   = 2.6
HitRate_eta_2018["REm33_B"]["inclusive_mean"]   = 2.6
HitRate_eta_2018["REp33_B"]["inclusive_mean"]   = 2.8
HitRate_eta_2018["REp33_M"]["inclusive_mean"]   = 2.8
HitRate_eta_2018["REp33_F"]["inclusive_mean"]   = 2.8
HitRate_eta_2018["REp32_B"]["inclusive_mean"]   = 6.0
HitRate_eta_2018["REp32_M"]["inclusive_mean"]   = 6.0
HitRate_eta_2018["REp32_F"]["inclusive_mean"]   = 6.0
HitRate_eta_2018["REm32_F"]["inclusive_error"]  = 1.6
HitRate_eta_2018["REm32_M"]["inclusive_error"]  = 1.6
HitRate_eta_2018["REm32_B"]["inclusive_error"]  = 1.6
HitRate_eta_2018["REm33_F"]["inclusive_error"]  = 0.6
HitRate_eta_2018["REm33_M"]["inclusive_error"]  = 0.6
HitRate_eta_2018["REm33_B"]["inclusive_error"]  = 0.6
HitRate_eta_2018["REp33_B"]["inclusive_error"]  = 0.9
HitRate_eta_2018["REp33_M"]["inclusive_error"]  = 0.9
HitRate_eta_2018["REp33_F"]["inclusive_error"]  = 0.9
HitRate_eta_2018["REp32_B"]["inclusive_error"]  = 0.6
HitRate_eta_2018["REp32_M"]["inclusive_error"]  = 0.6
HitRate_eta_2018["REp32_F"]["inclusive_error"]  = 0.6

HitRate_eta_2018["REm32_F"]["delayed"]          = 6.977562
HitRate_eta_2018["REm32_M"]["delayed"]          = 4.347988
HitRate_eta_2018["REm32_B"]["delayed"]          = 2.551935
HitRate_eta_2018["REm33_F"]["delayed"]          = 2.040158
HitRate_eta_2018["REm33_M"]["delayed"]          = 2.232643
HitRate_eta_2018["REm33_B"]["delayed"]          = 2.765121
HitRate_eta_2018["REp33_B"]["delayed"]          = 2.765121
HitRate_eta_2018["REp33_M"]["delayed"]          = 2.232643
HitRate_eta_2018["REp33_F"]["delayed"]          = 2.040158
HitRate_eta_2018["REp32_B"]["delayed"]          = 2.551935
HitRate_eta_2018["REp32_M"]["delayed"]          = 4.347988
HitRate_eta_2018["REp32_F"]["delayed"]          = 6.977562
HitRate_eta_2018["REm32_F"]["delayed_mean"]     = 5.6
HitRate_eta_2018["REm32_M"]["delayed_mean"]     = 5.6
HitRate_eta_2018["REm32_B"]["delayed_mean"]     = 5.6
HitRate_eta_2018["REm33_F"]["delayed_mean"]     = 2.6
HitRate_eta_2018["REm33_M"]["delayed_mean"]     = 2.6
HitRate_eta_2018["REm33_B"]["delayed_mean"]     = 2.6
HitRate_eta_2018["REp33_B"]["delayed_mean"]     = 2.8
HitRate_eta_2018["REp33_M"]["delayed_mean"]     = 2.8
HitRate_eta_2018["REp33_F"]["delayed_mean"]     = 2.8
HitRate_eta_2018["REp32_B"]["delayed_mean"]     = 6.0
HitRate_eta_2018["REp32_M"]["delayed_mean"]     = 6.0
HitRate_eta_2018["REp32_F"]["delayed_mean"]     = 6.0
HitRate_eta_2018["REm32_F"]["delayed_error"]    = 1.6
HitRate_eta_2018["REm32_M"]["delayed_error"]    = 1.6
HitRate_eta_2018["REm32_B"]["delayed_error"]    = 1.6
HitRate_eta_2018["REm33_F"]["delayed_error"]    = 0.6
HitRate_eta_2018["REm33_M"]["delayed_error"]    = 0.6
HitRate_eta_2018["REm33_B"]["delayed_error"]    = 0.6
HitRate_eta_2018["REp33_B"]["delayed_error"]    = 0.9
HitRate_eta_2018["REp33_M"]["delayed_error"]    = 0.9
HitRate_eta_2018["REp33_F"]["delayed_error"]    = 0.9
HitRate_eta_2018["REp32_B"]["delayed_error"]    = 0.6
HitRate_eta_2018["REp32_M"]["delayed_error"]    = 0.6
HitRate_eta_2018["REp32_F"]["delayed_error"]    = 0.6

HitRate_eta_2018["REm32_F"]["prompt"]           = 3.884181
HitRate_eta_2018["REm32_M"]["prompt"]           = 2.339429
HitRate_eta_2018["REm32_B"]["prompt"]           = 1.08743
HitRate_eta_2018["REm33_F"]["prompt"]           = 0.6172574
HitRate_eta_2018["REm33_M"]["prompt"]           = 0.4671183
HitRate_eta_2018["REm33_B"]["prompt"]           = 0.3504244
HitRate_eta_2018["REp33_B"]["prompt"]           = 0.3504244
HitRate_eta_2018["REp33_M"]["prompt"]           = 0.4671183
HitRate_eta_2018["REp33_F"]["prompt"]           = 0.6172574
HitRate_eta_2018["REp32_B"]["prompt"]           = 1.08743
HitRate_eta_2018["REp32_M"]["prompt"]           = 2.339429
HitRate_eta_2018["REp32_F"]["prompt"]           = 3.884181
HitRate_eta_2018["REm32_F"]["prompt_mean"]      = 5.6
HitRate_eta_2018["REm32_M"]["prompt_mean"]      = 5.6
HitRate_eta_2018["REm32_B"]["prompt_mean"]      = 5.6
HitRate_eta_2018["REm33_F"]["prompt_mean"]      = 2.6
HitRate_eta_2018["REm33_M"]["prompt_mean"]      = 2.6
HitRate_eta_2018["REm33_B"]["prompt_mean"]      = 2.6
HitRate_eta_2018["REp33_B"]["prompt_mean"]      = 2.8
HitRate_eta_2018["REp33_M"]["prompt_mean"]      = 2.8
HitRate_eta_2018["REp33_F"]["prompt_mean"]      = 2.8
HitRate_eta_2018["REp32_B"]["prompt_mean"]      = 6.0
HitRate_eta_2018["REp32_M"]["prompt_mean"]      = 6.0
HitRate_eta_2018["REp32_F"]["prompt_mean"]      = 6.0
HitRate_eta_2018["REm32_F"]["prompt_error"]     = 1.6
HitRate_eta_2018["REm32_M"]["prompt_error"]     = 1.6
HitRate_eta_2018["REm32_B"]["prompt_error"]     = 1.6
HitRate_eta_2018["REm33_F"]["prompt_error"]     = 0.6
HitRate_eta_2018["REm33_M"]["prompt_error"]     = 0.6
HitRate_eta_2018["REm33_B"]["prompt_error"]     = 0.6
HitRate_eta_2018["REp33_B"]["prompt_error"]     = 0.9
HitRate_eta_2018["REp33_M"]["prompt_error"]     = 0.9
HitRate_eta_2018["REp33_F"]["prompt_error"]     = 0.9
HitRate_eta_2018["REp32_B"]["prompt_error"]     = 0.6
HitRate_eta_2018["REp32_M"]["prompt_error"]     = 0.6
HitRate_eta_2018["REp32_F"]["prompt_error"]     = 0.6



HitRate_eta_2018["REm42_F"]["inclusive"]        = 15.24692
HitRate_eta_2018["REm42_M"]["inclusive"]        = 12.49818
HitRate_eta_2018["REm42_B"]["inclusive"]        = 10.18318
HitRate_eta_2018["REm43_F"]["inclusive"]        = 9.229289
HitRate_eta_2018["REm43_M"]["inclusive"]        = 9.371453
HitRate_eta_2018["REm43_B"]["inclusive"]        = 10.68044
HitRate_eta_2018["REp43_B"]["inclusive"]        = 10.68044
HitRate_eta_2018["REp43_M"]["inclusive"]        = 9.371453
HitRate_eta_2018["REp43_F"]["inclusive"]        = 9.229289
HitRate_eta_2018["REp42_B"]["inclusive"]        = 10.18318
HitRate_eta_2018["REp42_M"]["inclusive"]        = 12.49818
HitRate_eta_2018["REp42_F"]["inclusive"]        = 15.24692
HitRate_eta_2018["REm42_F"]["inclusive_mean"]   = 11.8
HitRate_eta_2018["REm42_M"]["inclusive_mean"]   = 11.8
HitRate_eta_2018["REm42_B"]["inclusive_mean"]   = 11.8
HitRate_eta_2018["REm43_F"]["inclusive_mean"]   = 15.2
HitRate_eta_2018["REm43_M"]["inclusive_mean"]   = 15.2
HitRate_eta_2018["REm43_B"]["inclusive_mean"]   = 15.2
HitRate_eta_2018["REp43_B"]["inclusive_mean"]   = 9.7
HitRate_eta_2018["REp43_M"]["inclusive_mean"]   = 9.7
HitRate_eta_2018["REp43_F"]["inclusive_mean"]   = 9.7
HitRate_eta_2018["REp42_B"]["inclusive_mean"]   = 12.6
HitRate_eta_2018["REp42_M"]["inclusive_mean"]   = 12.6
HitRate_eta_2018["REp42_F"]["inclusive_mean"]   = 12.6
HitRate_eta_2018["REm42_F"]["inclusive_error"]  = 2.4
HitRate_eta_2018["REm42_M"]["inclusive_error"]  = 2.4
HitRate_eta_2018["REm42_B"]["inclusive_error"]  = 2.4
HitRate_eta_2018["REm43_F"]["inclusive_error"]  = 3.2
HitRate_eta_2018["REm43_M"]["inclusive_error"]  = 3.2
HitRate_eta_2018["REm43_B"]["inclusive_error"]  = 3.2
HitRate_eta_2018["REp43_B"]["inclusive_error"]  = 3.1
HitRate_eta_2018["REp43_M"]["inclusive_error"]  = 3.1
HitRate_eta_2018["REp43_F"]["inclusive_error"]  = 3.1
HitRate_eta_2018["REp42_B"]["inclusive_error"]  = 2.8
HitRate_eta_2018["REp42_M"]["inclusive_error"]  = 2.8
HitRate_eta_2018["REp42_F"]["inclusive_error"]  = 2.8

HitRate_eta_2018["REm42_F"]["delayed"]          = 10.00131
HitRate_eta_2018["REm42_M"]["delayed"]          = 8.538846
HitRate_eta_2018["REm42_B"]["delayed"]          = 7.488873
HitRate_eta_2018["REm43_F"]["delayed"]          = 7.020769
HitRate_eta_2018["REm43_M"]["delayed"]          = 7.4416
HitRate_eta_2018["REm43_B"]["delayed"]          = 8.895609
HitRate_eta_2018["REp43_B"]["delayed"]          = 8.895609
HitRate_eta_2018["REp43_M"]["delayed"]          = 7.4416
HitRate_eta_2018["REp43_F"]["delayed"]          = 7.020769
HitRate_eta_2018["REp42_B"]["delayed"]          = 7.488873
HitRate_eta_2018["REp42_M"]["delayed"]          = 8.538846
HitRate_eta_2018["REp42_F"]["delayed"]          = 10.00131
HitRate_eta_2018["REm42_F"]["delayed_mean"]     = 11.8
HitRate_eta_2018["REm42_M"]["delayed_mean"]     = 11.8
HitRate_eta_2018["REm42_B"]["delayed_mean"]     = 11.8
HitRate_eta_2018["REm43_F"]["delayed_mean"]     = 15.2
HitRate_eta_2018["REm43_M"]["delayed_mean"]     = 15.2
HitRate_eta_2018["REm43_B"]["delayed_mean"]     = 15.2
HitRate_eta_2018["REp43_B"]["delayed_mean"]     = 9.7
HitRate_eta_2018["REp43_M"]["delayed_mean"]     = 9.7
HitRate_eta_2018["REp43_F"]["delayed_mean"]     = 9.7
HitRate_eta_2018["REp42_B"]["delayed_mean"]     = 12.6
HitRate_eta_2018["REp42_M"]["delayed_mean"]     = 12.6
HitRate_eta_2018["REp42_F"]["delayed_mean"]     = 12.6
HitRate_eta_2018["REm42_F"]["delayed_error"]    = 2.4
HitRate_eta_2018["REm42_M"]["delayed_error"]    = 2.4
HitRate_eta_2018["REm42_B"]["delayed_error"]    = 2.4
HitRate_eta_2018["REm43_F"]["delayed_error"]    = 3.2
HitRate_eta_2018["REm43_M"]["delayed_error"]    = 3.2
HitRate_eta_2018["REm43_B"]["delayed_error"]    = 3.2
HitRate_eta_2018["REp43_B"]["delayed_error"]    = 3.1
HitRate_eta_2018["REp43_M"]["delayed_error"]    = 3.1
HitRate_eta_2018["REp43_F"]["delayed_error"]    = 3.1
HitRate_eta_2018["REp42_B"]["delayed_error"]    = 2.8
HitRate_eta_2018["REp42_M"]["delayed_error"]    = 2.8
HitRate_eta_2018["REp42_F"]["delayed_error"]    = 2.8

HitRate_eta_2018["REm42_F"]["prompt"]           = 7.348796
HitRate_eta_2018["REm42_M"]["prompt"]           = 5.546808
HitRate_eta_2018["REm42_B"]["prompt"]           = 3.774569
HitRate_eta_2018["REm43_F"]["prompt"]           = 3.094012
HitRate_eta_2018["REm43_M"]["prompt"]           = 2.703615
HitRate_eta_2018["REm43_B"]["prompt"]           = 2.500445
HitRate_eta_2018["REp43_B"]["prompt"]           = 2.500445
HitRate_eta_2018["REp43_M"]["prompt"]           = 2.703615
HitRate_eta_2018["REp43_F"]["prompt"]           = 3.094012
HitRate_eta_2018["REp42_B"]["prompt"]           = 3.774569
HitRate_eta_2018["REp42_M"]["prompt"]           = 5.546808
HitRate_eta_2018["REp42_F"]["prompt"]           = 7.348796
HitRate_eta_2018["REm42_F"]["prompt_mean"]      = 11.8
HitRate_eta_2018["REm42_M"]["prompt_mean"]      = 11.8
HitRate_eta_2018["REm42_B"]["prompt_mean"]      = 11.8
HitRate_eta_2018["REm43_F"]["prompt_mean"]      = 15.2
HitRate_eta_2018["REm43_M"]["prompt_mean"]      = 15.2
HitRate_eta_2018["REm43_B"]["prompt_mean"]      = 15.2
HitRate_eta_2018["REp43_B"]["prompt_mean"]      = 9.7
HitRate_eta_2018["REp43_M"]["prompt_mean"]      = 9.7
HitRate_eta_2018["REp43_F"]["prompt_mean"]      = 9.7
HitRate_eta_2018["REp42_B"]["prompt_mean"]      = 12.6
HitRate_eta_2018["REp42_M"]["prompt_mean"]      = 12.6
HitRate_eta_2018["REp42_F"]["prompt_mean"]      = 12.6
HitRate_eta_2018["REm42_F"]["prompt_error"]     = 2.4
HitRate_eta_2018["REm42_M"]["prompt_error"]     = 2.4
HitRate_eta_2018["REm42_B"]["prompt_error"]     = 2.4
HitRate_eta_2018["REm43_F"]["prompt_error"]     = 3.2
HitRate_eta_2018["REm43_M"]["prompt_error"]     = 3.2
HitRate_eta_2018["REm43_B"]["prompt_error"]     = 3.2
HitRate_eta_2018["REp43_B"]["prompt_error"]     = 3.1
HitRate_eta_2018["REp43_M"]["prompt_error"]     = 3.1
HitRate_eta_2018["REp43_F"]["prompt_error"]     = 3.1
HitRate_eta_2018["REp42_B"]["prompt_error"]     = 2.8
HitRate_eta_2018["REp42_M"]["prompt_error"]     = 2.8
HitRate_eta_2018["REp42_F"]["prompt_error"]     = 2.8

######### Bunches scheme #########
def bunches_scheme(colliding_scheme, ntot):
    '''
    this function reads the colliding scheme from a .txt file and returns the list of bunches divided into:
    - all bunches
    - colliding bunches
    - prebeam bunches
    - abort bunches
    - non-colliding bunches
    '''
    with open(colliding_scheme, "r") as f:
        lines = f.readlines()

    bxIDs          = list(range(ntot)) # bunches go from 0 to 3563
    bxID_coll      = [int(bx.replace("\n","")) for bx in lines]
    bxID_prebeam   = list(range(bxID_coll[0]))
    bxID_abort     = list(range(bxID_coll[-1]+1, ntot))
    bxID_noncoll   = list(set(bxIDs) - set(bxID_coll) - set(bxID_prebeam) - set(bxID_abort))

    nbx_prebeam    = len(bxID_prebeam)
    nbx_coll       = len(bxID_coll)
    nbx_noncoll    = len(bxID_noncoll)
    nbx_abort      = len(bxID_abort)

    return bxIDs, bxID_coll, bxID_prebeam, bxID_abort, bxID_noncoll


ntot                 = 3564
bxIDs, bxID_coll, bxID_prebeam, bxID_abort, bxID_noncoll = bunches_scheme(colliding_scheme_txt, 3564)
nbx_prebeam          = len(bxID_prebeam)
nbx_coll             = len(bxID_coll)
nbx_noncoll          = len(bxID_noncoll)
nbx_abort            = len(bxID_abort)

print("Total bunches:           ", ntot)
print("Prebeam bunches:         ", nbx_prebeam)
print("Colliding bunches:       ", nbx_coll)
print("Non-colliding bunches:   ", nbx_noncoll)
print("Abort bunches:           ", nbx_abort)
   
# Get the list of histograms
histos = loadHists(inFile)

####################
wheels          = ["Wm2","Wm1","W0","Wp1","Wp2"]
disks           = ["RE1","RE2","RE3","RE4"]
    
# Output directories
outDir_png  = outDir + "/png"
outDir_pdf  = outDir + "/pdf"
outDir_C    = outDir + "/C"
if not os.path.exists(outDir):
    os.makedirs(outDir)
if not os.path.exists(outDir_png):
    os.makedirs(outDir_png)
if not os.path.exists(outDir_pdf):
    os.makedirs(outDir_pdf)
if not os.path.exists(outDir_C):
    os.makedirs(outDir_C)
    





def HitRateVsEta_Barrel_bkgs(inFile, ch, outDir, lumi=1, printPlots=False, legPos="ur"):
    ### Hit Rate vs Eta - [Barrel] ###
    draw_error   = True
    onlystat_err = False
    # types of bkg = ["inclusive", "delayed", "prompt"] #
    chambers    = [f"{w}_{ch}" for w in wheels]
    
    outDir_png  = outDir + "/png"
    outDir_pdf  = outDir + "/pdf"
    outDir_C    = outDir + "/C"


    # Create the canvas
    c = ROOT.TCanvas("c", "c", 900, 700)
    c.SetLeftMargin(0.05)
    c.SetRightMargin(0.05)
    c.SetTopMargin(0.1)
    c.SetBottomMargin(0.05)
    c.Draw()
    c.SetGrid()
    c.cd()

    if superimpose_2018:
        pad1 = ROOT.TPad("pad1", "pad1", 0, 0.31, 1, 1)
        pad1.SetTopMargin(0.1)
        pad1.SetBottomMargin(0.017) # 0.015
        pad1.SetLeftMargin(0.12)
        pad1.SetRightMargin(0.05)
        pad1.SetBorderMode(0)
        pad1.SetTickx(1)
        pad1.SetTicky(1)
    else:
        pad1 = ROOT.TPad("pad1", "pad1", 0.01, 0.01, 0.99, 0.99)
    pad1.Draw()
    pad1.SetLogy()
    pad1.SetGrid()

    pad1.cd()
    # Create the legend
    if legPos=="ur":
        leg = ROOT.TLegend(0.7, 0.7, 0.89, 0.89) # up-right corner
    elif legPos=="ul":
        leg = ROOT.TLegend(0.11, 0.7, 0.30, 0.89) # up-left corner
        if superimpose_2018:
            leg = ROOT.TLegend(0.13, 0.7, 0.5, 0.89) # with ratio
    elif legPos=="dr":
        leg = ROOT.TLegend(0.7, 0.11, 0.89, 0.3) # down-right corner
    elif legPos=="dl":
        leg = ROOT.TLegend(0.11, 0.11, 0.30, 0.3) # down-left corner
        if superimpose_2018:
            leg = ROOT.TLegend(0.13, 0.03, 0.5, 0.2) # with ratio
    leg.SetTextFont(42)
    leg.SetTextSize(0.04)
    leg.AddEntry("None", ch, "")
    leg.AddEntry("None", "", "")
    leg.AddEntry("None", "", "")

    # definition of the types of background
    bkgs        = ["inclusive", "delayed", "prompt"]
    if draw_error:
        graphs  = {bkg: ROOT.TGraphErrors() for bkg in bkgs}
    else:
        graphs  = {bkg: ROOT.TGraph() for bkg in bkgs}
        
    if superimpose_2018:
        if draw_error:
            graphs_2018 = {bkg: ROOT.TGraphErrors() for bkg in bkgs}
        else:
            graphs_2018 = {bkg: ROOT.TGraph() for bkg in bkgs}

    funcs       = {}
    funcs_error = {}
    
    # for w in wheels:
        # chamber = f"{w}_{ch}"
    for chamber in chambers:
        print(f"Processing ---> {chamber}")
        minX    = histos[chamber+"_prebeam_fit"].GetMinimumX()
        maxX    = histos[chamber+"_prebeam_fit"].GetMaximumX()
        funcs[chamber+"_inclusive_fit"] = ROOT.TF1(chamber+"_inclusive_fit", "pol1", minX, maxX)
        funcs[chamber+"_delayed_fit"]   = ROOT.TF1(chamber+"_delayed_fit", "pol1", minX, maxX)
        funcs[chamber+"_prompt_fit"]    = ROOT.TF1(chamber+"_prompt_fit", "pol1", minX, maxX)

        funcs[chamber+"_inclusive_fit"].SetParameter(0,(nbx_prebeam*histos[chamber+"_prebeam_fit"].GetParameter(0) + nbx_coll*histos[chamber+"_high_fit"].GetParameter(0) + nbx_noncoll*histos[chamber+"_low_fit"].GetParameter(0) + nbx_abort*histos[chamber+"_abort_fit"].GetParameter(0))/ntot)
        funcs[chamber+"_inclusive_fit"].SetParameter(1,(nbx_prebeam*histos[chamber+"_prebeam_fit"].GetParameter(1) + nbx_coll*histos[chamber+"_high_fit"].GetParameter(1) + nbx_noncoll*histos[chamber+"_low_fit"].GetParameter(1) + nbx_abort*histos[chamber+"_abort_fit"].GetParameter(1))/ntot)

        funcs[chamber+"_delayed_fit"].SetParameter(0,(nbx_prebeam*histos[chamber+"_prebeam_fit"].GetParameter(0) + nbx_noncoll*histos[chamber+"_low_fit"].GetParameter(0) + nbx_abort*histos[chamber+"_abort_fit"].GetParameter(0))/(ntot-nbx_coll))
        funcs[chamber+"_delayed_fit"].SetParameter(1,(nbx_prebeam*histos[chamber+"_prebeam_fit"].GetParameter(1) + nbx_noncoll*histos[chamber+"_low_fit"].GetParameter(1) + nbx_abort*histos[chamber+"_abort_fit"].GetParameter(1))/(ntot-nbx_coll))

        funcs[chamber+"_prompt_fit"].SetParameter(0,histos[chamber+"_high_fit"].GetParameter(0) - funcs[chamber+"_delayed_fit"].GetParameter(0))    
        funcs[chamber+"_prompt_fit"].SetParameter(1,histos[chamber+"_high_fit"].GetParameter(1) - funcs[chamber+"_delayed_fit"].GetParameter(1))    

        
  
        ####################
        # calculate errors #
        ####################
        funcs_error[chamber+"_inclusive_fit"] = {}
        funcs_error[chamber+"_delayed_fit"]   = {}
        funcs_error[chamber+"_prompt_fit"]    = {}

        if chamber in fitResults[str(fill)]:
            print(f"Getting the errors for {chamber}")
            print(fitResults[str(fill)][chamber+"_prebeam"])

        # inclusive bkg #
        if onlystat_err:
            funcs_error[chamber+"_inclusive_fit"]["p0_error"]  = sqrt(((nbx_prebeam**2)*fitResults[str(fill)][chamber+"_prebeam"]["p0_error"]**2 + (nbx_coll**2)*fitResults[str(fill)][chamber+"_high"]["p0_error"]**2 + (nbx_noncoll**2)*fitResults[str(fill)][chamber+"_low"]["p0_error"]**2 + (nbx_abort**2)*fitResults[str(fill)][chamber+"_abort"]["p0_error"]**2)/(ntot**2))
            funcs_error[chamber+"_inclusive_fit"]["p1_error"]  = sqrt(((nbx_prebeam**2)*fitResults[str(fill)][chamber+"_prebeam"]["p1_error"]**2 + (nbx_coll**2)*fitResults[str(fill)][chamber+"_high"]["p1_error"]**2 + (nbx_noncoll**2)*fitResults[str(fill)][chamber+"_low"]["p1_error"]**2 + (nbx_abort**2)*fitResults[str(fill)][chamber+"_abort"]["p1_error"]**2)/(ntot**2))
        else:
            funcs_error[chamber+"_inclusive_fit"]["p0_error"]  = sqrt(((nbx_prebeam**2)*(fitResults[str(fill)][chamber+"_prebeam"]["chi2"]/fitResults[str(fill)][chamber+"_prebeam"]["ndf"])*fitResults[str(fill)][chamber+"_prebeam"]["p0_error"]**2 + (nbx_coll**2)*(fitResults[str(fill)][chamber+"_high"]["chi2"]/fitResults[str(fill)][chamber+"_high"]["ndf"])*fitResults[str(fill)][chamber+"_high"]["p0_error"]**2 + (nbx_noncoll**2)*(fitResults[str(fill)][chamber+"_low"]["chi2"]/fitResults[str(fill)][chamber+"_low"]["ndf"])*fitResults[str(fill)][chamber+"_low"]["p0_error"]**2 + (nbx_abort**2)*(fitResults[str(fill)][chamber+"_abort"]["chi2"]/fitResults[str(fill)][chamber+"_abort"]["ndf"])*fitResults[str(fill)][chamber+"_abort"]["p0_error"]**2)/(ntot**2))
            funcs_error[chamber+"_inclusive_fit"]["p1_error"]  = sqrt(((nbx_prebeam**2)*(fitResults[str(fill)][chamber+"_prebeam"]["chi2"]/fitResults[str(fill)][chamber+"_prebeam"]["ndf"])*fitResults[str(fill)][chamber+"_prebeam"]["p1_error"]**2 + (nbx_coll**2)*(fitResults[str(fill)][chamber+"_high"]["chi2"]/fitResults[str(fill)][chamber+"_high"]["ndf"])*fitResults[str(fill)][chamber+"_high"]["p1_error"]**2 + (nbx_noncoll**2)*(fitResults[str(fill)][chamber+"_low"]["chi2"]/fitResults[str(fill)][chamber+"_low"]["ndf"])*fitResults[str(fill)][chamber+"_low"]["p1_error"]**2 + (nbx_abort**2)*(fitResults[str(fill)][chamber+"_abort"]["chi2"]/fitResults[str(fill)][chamber+"_abort"]["ndf"])*fitResults[str(fill)][chamber+"_abort"]["p1_error"]**2)/(ntot**2))
        funcs_error[chamber+"_inclusive_fit"]["cov_p0p1"]  = ((nbx_prebeam**2)*fitResults[str(fill)][chamber+"_prebeam"]["covMatrix"][0][1] + (nbx_coll**2)*fitResults[str(fill)][chamber+"_high"]["covMatrix"][0][1] + (nbx_noncoll**2)*fitResults[str(fill)][chamber+"_low"]["covMatrix"][0][1] + (nbx_abort**2)*fitResults[str(fill)][chamber+"_abort"]["covMatrix"][0][1])/(ntot**2)
        funcs_error[chamber+"_inclusive_fit"]["covMatrix"] = [
                                                                            [funcs_error[chamber+"_inclusive_fit"]["p0_error"]**2, funcs_error[chamber+"_inclusive_fit"]["cov_p0p1"]],
                                                                            [funcs_error[chamber+"_inclusive_fit"]["cov_p0p1"], funcs_error[chamber+"_inclusive_fit"]["p1_error"]**2]
                                                                        ]
        # delayed bkg #
        if onlystat_err:
            funcs_error[chamber+"_delayed_fit"]["p0_error"]    = sqrt(((nbx_prebeam**2)*fitResults[str(fill)][chamber+"_prebeam"]["p0_error"]**2 + (nbx_noncoll**2)*fitResults[str(fill)][chamber+"_low"]["p0_error"]**2 + (nbx_abort**2)*fitResults[str(fill)][chamber+"_abort"]["p0_error"]**2)/(ntot**2))
            funcs_error[chamber+"_delayed_fit"]["p1_error"]    = sqrt(((nbx_prebeam**2)*fitResults[str(fill)][chamber+"_prebeam"]["p1_error"]**2 + (nbx_noncoll**2)*fitResults[str(fill)][chamber+"_low"]["p1_error"]**2 + (nbx_abort**2)*fitResults[str(fill)][chamber+"_abort"]["p1_error"]**2)/(ntot**2))
        else:
            funcs_error[chamber+"_delayed_fit"]["p0_error"]    = sqrt(((nbx_prebeam**2)*(fitResults[str(fill)][chamber+"_prebeam"]["chi2"]/fitResults[str(fill)][chamber+"_prebeam"]["ndf"])*fitResults[str(fill)][chamber+"_prebeam"]["p0_error"]**2 + (nbx_noncoll**2)*(fitResults[str(fill)][chamber+"_low"]["chi2"]/fitResults[str(fill)][chamber+"_low"]["ndf"])*fitResults[str(fill)][chamber+"_low"]["p0_error"]**2 + (nbx_abort**2)*(fitResults[str(fill)][chamber+"_abort"]["chi2"]/fitResults[str(fill)][chamber+"_abort"]["ndf"])*fitResults[str(fill)][chamber+"_abort"]["p0_error"]**2)/(ntot**2))
            funcs_error[chamber+"_delayed_fit"]["p1_error"]    = sqrt(((nbx_prebeam**2)*(fitResults[str(fill)][chamber+"_prebeam"]["chi2"]/fitResults[str(fill)][chamber+"_prebeam"]["ndf"])*fitResults[str(fill)][chamber+"_prebeam"]["p1_error"]**2 + (nbx_noncoll**2)*(fitResults[str(fill)][chamber+"_low"]["chi2"]/fitResults[str(fill)][chamber+"_low"]["ndf"])*fitResults[str(fill)][chamber+"_low"]["p1_error"]**2 + (nbx_abort**2)*(fitResults[str(fill)][chamber+"_abort"]["chi2"]/fitResults[str(fill)][chamber+"_abort"]["ndf"])*fitResults[str(fill)][chamber+"_abort"]["p1_error"]**2)/(ntot**2))
        funcs_error[chamber+"_delayed_fit"]["cov_p0p1"]    = ((nbx_prebeam**2)*fitResults[str(fill)][chamber+"_prebeam"]["covMatrix"][0][1] + (nbx_noncoll**2)*fitResults[str(fill)][chamber+"_low"]["covMatrix"][0][1] + (nbx_abort**2)*fitResults[str(fill)][chamber+"_abort"]["covMatrix"][0][1])/(ntot**2)
        funcs_error[chamber+"_delayed_fit"]["covMatrix"]   = [
                                                                            [funcs_error[chamber+"_delayed_fit"]["p0_error"]**2, funcs_error[chamber+"_delayed_fit"]["cov_p0p1"]],
                                                                            [funcs_error[chamber+"_delayed_fit"]["cov_p0p1"], funcs_error[chamber+"_delayed_fit"]["p1_error"]**2]
                                                                        ]
        # prompt bkg #
        if onlystat_err:
            funcs_error[chamber+"_prompt_fit"]["p0_error"]     = sqrt(fitResults[str(fill)][chamber+"_high"]["p0_error"]**2 + funcs_error[chamber+"_delayed_fit"]["p0_error"]**2)
            funcs_error[chamber+"_prompt_fit"]["p1_error"]     = sqrt(fitResults[str(fill)][chamber+"_high"]["p1_error"]**2 + funcs_error[chamber+"_delayed_fit"]["p1_error"]**2)
        else:
            funcs_error[chamber+"_prompt_fit"]["p0_error"]     = sqrt((fitResults[str(fill)][chamber+"_high"]["chi2"]/fitResults[str(fill)][chamber+"_high"]["ndf"])*(fitResults[str(fill)][chamber+"_high"]["p0_error"]**2) + funcs_error[chamber+"_delayed_fit"]["p0_error"]**2)
            funcs_error[chamber+"_prompt_fit"]["p1_error"]     = sqrt((fitResults[str(fill)][chamber+"_high"]["chi2"]/fitResults[str(fill)][chamber+"_high"]["ndf"])*(fitResults[str(fill)][chamber+"_high"]["p1_error"]**2) + funcs_error[chamber+"_delayed_fit"]["p1_error"]**2)
        funcs_error[chamber+"_prompt_fit"]["cov_p0p1"]     = fitResults[str(fill)][chamber+"_high"]["covMatrix"][0][1] + funcs_error[chamber+"_delayed_fit"]["cov_p0p1"]
        funcs_error[chamber+"_prompt_fit"]["covMatrix"]    = [
                                                                            [funcs_error[chamber+"_prompt_fit"]["p0_error"]**2, funcs_error[chamber+"_prompt_fit"]["cov_p0p1"]],
                                                                            [funcs_error[chamber+"_prompt_fit"]["cov_p0p1"], funcs_error[chamber+"_prompt_fit"]["p1_error"]**2]
                                                                        ]
        
        
        
        
        # for bkg in bkgs:
        #     print(f"Processing ---> {w} {ch} for {bkg} background")
        #     func = funcs[chamber+"_"+bkg+"_fit"]
        #     graphs[bkg].AddPoint(geometry_dict[ch][w]["eta"], func.Eval(10)) # func.Eval(10) means we are going to fix the Inst.Lumi to 1e34cm^-2s^-1
            # calculate backgrounds functions also per phi-sector #
    
    for chamber in chambers:
        for sec in sectors:
            funcs[chamber+"_"+sec+"_inclusive_fit"] = ROOT.TF1(chamber+"_"+sec+"_inclusive_fit", "pol1", minX, maxX)
            funcs[chamber+"_"+sec+"_delayed_fit"]   = ROOT.TF1(chamber+"_"+sec+"_delayed_fit", "pol1", minX, maxX)
            funcs[chamber+"_"+sec+"_prompt_fit"]    = ROOT.TF1(chamber+"_"+sec+"_prompt_fit", "pol1", minX, maxX)
        
            funcs[chamber+"_"+sec+"_inclusive_fit"].SetParameter(0,(nbx_prebeam*histos[chamber+"_"+sec+"_prebeam_fit"].GetParameter(0) + nbx_coll*histos[chamber+"_"+sec+"_high_fit"].GetParameter(0) + nbx_noncoll*histos[chamber+"_"+sec+"_low_fit"].GetParameter(0) + nbx_abort*histos[chamber+"_"+sec+"_abort_fit"].GetParameter(0))/ntot)
            funcs[chamber+"_"+sec+"_inclusive_fit"].SetParameter(1,(nbx_prebeam*histos[chamber+"_"+sec+"_prebeam_fit"].GetParameter(1) + nbx_coll*histos[chamber+"_"+sec+"_high_fit"].GetParameter(1) + nbx_noncoll*histos[chamber+"_"+sec+"_low_fit"].GetParameter(1) + nbx_abort*histos[chamber+"_"+sec+"_abort_fit"].GetParameter(1))/ntot)

            funcs[chamber+"_"+sec+"_delayed_fit"].SetParameter(0,(nbx_prebeam*histos[chamber+"_"+sec+"_prebeam_fit"].GetParameter(0) + nbx_noncoll*histos[chamber+"_"+sec+"_low_fit"].GetParameter(0) + nbx_abort*histos[chamber+"_"+sec+"_abort_fit"].GetParameter(0))/(ntot-nbx_coll))
            funcs[chamber+"_"+sec+"_delayed_fit"].SetParameter(1,(nbx_prebeam*histos[chamber+"_"+sec+"_prebeam_fit"].GetParameter(1) + nbx_noncoll*histos[chamber+"_"+sec+"_low_fit"].GetParameter(1) + nbx_abort*histos[chamber+"_"+sec+"_abort_fit"].GetParameter(1))/(ntot-nbx_coll))

            funcs[chamber+"_"+sec+"_prompt_fit"].SetParameter(0,histos[chamber+"_"+sec+"_high_fit"].GetParameter(0) - funcs[chamber+"_"+sec+"_prompt_fit"].GetParameter(0))    
            funcs[chamber+"_"+sec+"_prompt_fit"].SetParameter(1,histos[chamber+"_"+sec+"_high_fit"].GetParameter(1) - funcs[chamber+"_"+sec+"_delayed_fit"].GetParameter(1))  
    # print(funcs.keys())
    data                = {}
    for bkg in bkgs:
        data[bkg]       = {}
        data[bkg]["X"]  = []
        data[bkg]["Y"]  = []
        data[bkg]["EX"] = []
        data[bkg]["EY"] = []
        for w in wheels:
            chamber = f"{w}_{ch}"
            # ch,part = chamber.split("_")
            print(f"Processing ---> {w} {ch} for {bkg} background")
            func        = funcs[chamber+"_"+bkg+"_fit"]
            x           = 10
            if draw_error:
                data[bkg]["X"].append(geometry_dict[ch][w]["eta"]) 
                data[bkg]["Y"].append(func.Eval(x)) # func.Eval(10) means we are going to fix the Inst.Lumi to 1e34cm^-2s^-1
                data[bkg]["EX"].append(0.0)
                # data[bkg]["EY"].append(sqrt(abs((x**2)*funcs_error[chamber+f"_{bkg}_fit"]["p1_error"]**2 + funcs_error[chamber+f"_{bkg}_fit"]["p0_error"]**2 + 2*x*funcs_error[chamber+f"_{bkg}_fit"]["cov_p0p1"])))
                mean_on_sectors     = mean([funcs[chamber+"_"+sec+f"_{bkg}_fit"].Eval(x) for sec in sectors if funcs[chamber+"_"+sec+f"_{bkg}_fit"].Eval(x)>0])
                stdev_on_sectors    = stdev([funcs[chamber+"_"+sec+f"_{bkg}_fit"].Eval(x) for sec in sectors if funcs[chamber+"_"+sec+f"_{bkg}_fit"].Eval(x)>0])
                y_err               = stdev_on_sectors*func.Eval(x)/mean_on_sectors
                data[bkg]["EY"].append(y_err)
                
                print([funcs[chamber+"_"+sec+f"_{bkg}_fit"].Eval(x) for sec in sectors if funcs[chamber+"_"+sec+f"_{bkg}_fit"].Eval(x)>0])
                print("stdev:               ", stdev_on_sectors)
                print("mean:                ", mean_on_sectors)
                print("y_err:               ", y_err)
                print("y value:             ", func.Eval(x))    
            else:
                data[bkg]["X"].append(geometry_dict[ch][w]["eta"]) 
                data[bkg]["Y"].append(func.Eval(x)) # func.Eval(10) means we are going to fix the Inst.Lumi to 1e34cm^-2s^-1
                data[bkg]["EX"].append(0.0)
                data[bkg]["EY"].append(0.0)
            print("\n")

    if draw_error:
        graphs  = {bkg: ROOT.TGraphErrors(len(data[bkg]["X"]), array.array("d", data[bkg]["X"]), array.array("d", data[bkg]["Y"]), array.array("d", data[bkg]["EX"]), array.array("d", data[bkg]["EY"])) for bkg in bkgs}
    else:
        graphs  = {bkg: ROOT.TGraph(len(data[bkg]["X"]), array.array("d", data[bkg]["X"]), array.array("d", data[bkg]["Y"])) for bkg in bkgs}
    
    print("Drawing the graphs")
    for i,bkg in enumerate(bkgs):
        # axis options
        # graphs[bkg].SetTitle(ch)
        graphs[bkg].SetTitle("")
        graphs[bkg].GetXaxis().SetTitle("#eta")
        graphs[bkg].GetXaxis().SetLabelSize(0) # 0.04
        graphs[bkg].GetXaxis().SetTitleSize(0.045)

        graphs[bkg].GetYaxis().SetTitle("Hit Rate (Hz/cm^{2})")
        graphs[bkg].GetYaxis().SetLabelSize(0.04)
        graphs[bkg].GetYaxis().SetTitleSize(0.045)
        graphs[bkg].GetYaxis().SetTitleOffset(0.9)
        if ch in ["RB1in","RB1out","RB2in","RB2out"]:
            graphs[bkg].SetMinimum(1e-1)
            graphs[bkg].SetMaximum(1e1)
        elif ch in ["RB3"]:
            graphs[bkg].SetMinimum(1e-2)
            graphs[bkg].SetMaximum(1e1)
        elif ch in ["RB4"]:
            graphs[bkg].SetMinimum(1e-2)
            graphs[bkg].SetMaximum(1e2)
        # graphs[bkg].SetMaximum(25)
        # graphs[bkg].SetMaximum(1e2)
        
        # graphics options
        graphs[bkg].SetLineColor(graphicsOptions[bkg]["color"])
        graphs[bkg].SetMarkerColor(graphicsOptions[bkg]["color"])
        graphs[bkg].SetMarkerStyle(graphicsOptions[bkg]["marker"])
        graphs[bkg].SetMarkerSize(1.0)
        if i==0:
            if (ch=="RB4") and (bkg=="prompt"):
                pass
            else:
                graphs[bkg].Draw("ap")
        else:
            if (ch=="RB4") and (bkg=="prompt"):
                pass
            else:
                graphs[bkg].Draw("p")

        
        if superimpose_2018:
            leg.SetNColumns(3)
            leg.AddEntry("None", bkg.replace("inclusive","Inclusive").replace("delayed","Delayed").replace("prompt","Prompt"), "")
            leg.AddEntry(graphs[bkg], bkg.replace("inclusive",f"{year}").replace("delayed",f"{year}").replace("prompt",f"{year}"), "p")
        else:
            leg.AddEntry(graphs[bkg], bkg.replace("inclusive","Inclusive").replace("delayed","Delayed").replace("prompt","Prompt"), "p")

        ###### Add 2018 data ######
        if superimpose_2018:
            # print("\n")
            # print("SUPERIMPOSING 2018 DATA")

            # graphs_2018[bkg].AddPoint(geometry_dict[ch]["Wm2"]["eta"],   HitRate_eta_2018[ch]["Wm2"][bkg])
            # graphs_2018[bkg].AddPoint(geometry_dict[ch]["Wm1"]["eta"],   HitRate_eta_2018[ch]["Wm1"][bkg])
            # graphs_2018[bkg].AddPoint(geometry_dict[ch]["W0"]["eta"],    HitRate_eta_2018[ch]["W0"][bkg])
            # graphs_2018[bkg].AddPoint(geometry_dict[ch]["Wp1"]["eta"],   HitRate_eta_2018[ch]["Wp1"][bkg])
            # graphs_2018[bkg].AddPoint(geometry_dict[ch]["Wp2"]["eta"],   HitRate_eta_2018[ch]["Wp2"][bkg])


            X       = []
            X_err   = []
            Y       = []
            Y_err   = []
            for w in wheels:
                # print(f"Processing ---> {disk} {chamber} for {bkg} background")
                X.append(geometry_dict[ch][w]["eta"])
                X_err.append(0.0)
                Y.append(HitRate_eta_2018[ch][w][bkg])
                Y_err.append(HitRate_eta_2018[ch][w][bkg+"_error"]/HitRate_eta_2018[ch][w][bkg+"_mean"] * HitRate_eta_2018[ch][w][bkg])
            
            # print(f'X:              {X}')
            # print(f'Y:              {Y}')
            # print(f'X_err:          {X_err}')
            # print(f'Perc. error:    {[HitRate_eta_2018[ch][w][bkg+"_error"]/HitRate_eta_2018[ch][w][bkg+"_mean"] for w in wheels]}')
            # print(f'Y_err:          {Y_err}')

            graphs_2018[bkg] = ROOT.TGraphErrors(len(X), array.array('d', X), array.array('d', Y), array.array('d', X_err), array.array('d', Y_err))
            # graphics options
            graphs_2018[bkg].SetLineColor(graphicsOptions[bkg]["color"])
            graphs_2018[bkg].SetMarkerColor(graphicsOptions[bkg]["color"])
            graphs_2018[bkg].SetMarkerStyle(graphicsOptions[bkg]["marker"])
            graphs_2018[bkg].SetLineStyle(ROOT.kDashed)
            graphs_2018[bkg].SetLineWidth(1)
            graphs_2018[bkg].SetFillColorAlpha(graphicsOptions[bkg]["color"], 0.1)
            graphs_2018[bkg].Draw("le3 SAME")


            leg.AddEntry(graphs_2018[bkg], bkg.replace("inclusive","2018").replace("delayed","2018").replace("prompt","2018"), "lf")

        
    
    leg.Draw("SAME")


    # pad1.cd()
    writeExtraText          = 1
    # extraText               = "Work in progress"
    extraText               = "Preliminary"
    lepText                 = ""
    # lumi_sqrtS              = ch + ", " + "%s fb^{-1}  (13.6 TeV)"%(round(lumi,3))
    if not superimpose_2018:
        lumi_sqrtS          = "Run 3 (13.6 TeV)"
    else:
        lumi_sqrtS          = "Run 2 (13 TeV), Run 3 (13.6 TeV)"
    iPeriod                 = 0
    iPos                    = 0
    CMS_lumi(pad1, lumi_sqrtS, iPos, writeExtraText, extraText, lepText) # CMS_lumi(pad, lumi_sqrtS, iPosX, writeExtraText, extraText, lepText), lepText is usually a region
    # pad1.Draw()
    pad1.Update()

    c.cd()

    if superimpose_2018:
        pad2 = ROOT.TPad("pad2", "pad2", 0, 0, 1, 0.30)
        pad2.SetTopMargin(0.05)
        pad2.SetBottomMargin(0.25)
        pad2.SetLeftMargin(0.12)
        pad2.SetRightMargin(0.05)
        pad2.SetGrid()
        ROOT.gStyle.SetHatchesSpacing(2)
        ROOT.gStyle.SetHatchesLineWidth(2)
        c.cd()
        pad2.Draw()
        pad2.cd()

        # Create the ratio histogram
        hist_ratio  = {}
        for i,bkg in enumerate(bkgs):
            if (ch=="RB4") and (bkg=="prompt"):
                continue
            X           = data[bkg]["X"]

            Y_2024      = data[bkg]["Y"]
            Y_2018      = [HitRate_eta_2018[ch][w][bkg] for w in wheels]
            Y           = [y_2024/y_2018 for y_2024,y_2018 in zip(Y_2024,Y_2018)]

            X_err       = [0 for x in X]

            print(chambers)
            print(Y_2024)

            # Y_err_2024  = [((10**2)*funcs_error[chamber+f"_{bkg}_fit"]["p1_error"]**2 + funcs_error[chamber+f"_{bkg}_fit"]["p0_error"]**2 + 2*10*funcs_error[chamber+f"_{bkg}_fit"]["cov_p0p1"])/(y_2024**2) for chamber,y_2024 in zip(chambers,Y_2024)]
            Y_err_2024  = [(y_err_2024/y_2024)**2 for y_2024,y_err_2024 in zip(Y_2024,data[bkg]["EY"])]
            Y_err_2018  = [(y_err_2018/y_2018)**2 for y_2018,y_err_2018 in zip(Y_2018,[HitRate_eta_2018[ch][w][bkg+"_error"]/HitRate_eta_2018[ch][w][bkg+"_mean"] * HitRate_eta_2018[ch][w][bkg] for w in wheels])]
            Y_err       = [y*sqrt(abs(y_err_2024 + y_err_2018)) for x,y,y_err_2024,y_err_2018 in zip(X,Y,Y_err_2024,Y_err_2018)]



            print(f"X:      {X}")
            print(f"Y:      {Y}")
            print(f"X_err:  {X_err}")
            print(f"Y_err:  {Y_err}")
            hist_ratio[bkg] = ROOT.TGraphErrors(len(X), array.array('d', X), array.array('d', Y), array.array('d', X_err), array.array('d', Y_err))

            # hist_ratio[bkg].SetMinimum(0)
            # hist_ratio[bkg].SetMaximum(2)
            hist_ratio[bkg].SetMinimum(hist_ratio[bkg].GetHistogram().GetMinimum()*0.9)
            hist_ratio[bkg].SetMaximum(hist_ratio[bkg].GetHistogram().GetMaximum()*1.1)

            hist_ratio[bkg].SetTitle("")

            hist_ratio[bkg].GetXaxis().SetTitle("#eta")
            hist_ratio[bkg].GetXaxis().SetTitleSize(0.1)
            hist_ratio[bkg].GetXaxis().SetLabelSize(0.1)

            hist_ratio[bkg].GetYaxis().SetTitle(f"{year} Data / 2018 Data") # "2024 / 2018"
            hist_ratio[bkg].GetYaxis().SetTitleOffset(0.3)
            hist_ratio[bkg].GetYaxis().CenterTitle(True)
            hist_ratio[bkg].GetYaxis().SetLabelSize(0.05)
            hist_ratio[bkg].GetYaxis().SetTitleSize(0.075)
            # hist_ratio[bkg].SetNdivisions(503, "Y")  # Reduce number of ticks on y-axis
            hist_ratio[bkg].SetLineColor(graphicsOptions[bkg]["color"])
            hist_ratio[bkg].SetMarkerColor(graphicsOptions[bkg]["color"])
            hist_ratio[bkg].SetMarkerStyle(ROOT.kFullCircle)
            hist_ratio[bkg].SetMarkerSize(1.0)
            # hist_ratio[bkg].SetFillColorAlpha(graphicsOptions[bkg]["color"], 0.3)
            # hist_ratio[bkg].SetFillStyle(3002)

        for i,bkg in enumerate(hist_ratio):
            h_ratio = hist_ratio[bkg]
            if (ch=="RB4") and (bkg=="prompt"):
                continue
            if i==0:
                h_ratio.Draw("AP")
                # line1 = ROOT.TLine(min(data[bkg]["X"]), 1, max(data[bkg]["X"]), 1)  # (x1, y1, x2, y2)
                line1 = ROOT.TLine(h_ratio.GetXaxis().GetXmin(), 1, h_ratio.GetXaxis().GetXmax(), 1)  # (x1, y1, x2, y2)
                line1.SetLineColor(ROOT.kBlack)
                line1.SetLineWidth(1)
                line1.SetLineStyle(ROOT.kSolid)
                line1.Draw("SAME")
            else:
                h_ratio.Draw("PSAME")

        pad2.Update()

        c.cd()
        c.RedrawAxis()
        pad2.RedrawAxis()
    
    c.cd()

    # Save the plot
    if printPlots:
        if superimpose_2018:
            c.SaveAs(outDir_png+"/HitRateVsEta_"+ch+"_bkgs_w2018_Ratio_syst_"+str(year)+"_APPROVED.png")
            c.SaveAs(outDir_pdf+"/HitRateVsEta_"+ch+"_bkgs_w2018_Ratio_syst_"+str(year)+"_APPROVED.pdf")
            c.SaveAs(outDir_C+"/HitRateVsEta_"+ch+"_bkgs_w2018_Ratio_syst_"+str(year)+"_APPROVED.C")
        else:
            c.SaveAs(outDir_png+"/HitRateVsEta_"+ch+"_bkgs_"+str(year)+"_APPROVED.png")
            c.SaveAs(outDir_pdf+"/HitRateVsEta_"+ch+"_bkgs_"+str(year)+"_APPROVED.pdf")
            c.SaveAs(outDir_C+"/HitRateVsEta_"+ch+"_bkgs_"+str(year)+"_APPROVED.C")
        
    
def HitRateVsEta_Endcap_bkgs(inFile, disk, outDir, lumi=1, printPlots=False, legPos="ur"):
    ### Hit Rate vs Eta - [Endcap] ###
    # types of bkg = ["inclusive", "delayed", "prompt"] #
    draw_error      = True
    onlystat_err    = False
    disk_number     = int(disk[-1])
    chambers        = [f"REm{disk_number}{ring}_{part}" for ring in [2,3] for part in ["F","M","B"]] # negative endcap
    chambers       += [f"REp{disk_number}{ring}_{part}" for ring in [3,2] for part in ["B","M","F"]] # positive endcap
    # print(chambers)
    
    outDir_png  = outDir + "/png"
    outDir_pdf  = outDir + "/pdf"
    outDir_C    = outDir + "/C"

    # Create the canvas
    c = ROOT.TCanvas("c", "c", 900, 700)
    c.SetLeftMargin(0.05)
    c.SetRightMargin(0.05)
    c.SetTopMargin(0.1)
    c.SetBottomMargin(0.05)
    c.Draw()
    c.SetGrid()
    c.cd()

    if superimpose_2018:
        pad1 = ROOT.TPad("pad1", "pad1", 0, 0.31, 1, 1)
        pad1.SetTopMargin(0.1)
        pad1.SetBottomMargin(0.017) # 0.015
        pad1.SetLeftMargin(0.12)
        pad1.SetRightMargin(0.05)
        pad1.SetBorderMode(0)
        pad1.SetTickx(1)
        pad1.SetTicky(1)
    else:
        pad1 = ROOT.TPad("pad1", "pad1", 0.01, 0.01, 0.99, 0.99)
    pad1.Draw()
    pad1.SetLogy()
    pad1.SetGrid()

    pad1.cd()
    # Create the legend
    if legPos=="ur":
        leg = ROOT.TLegend(0.7, 0.7, 0.89, 0.89) # up-right corner
    elif legPos=="ul":
        leg = ROOT.TLegend(0.11, 0.7, 0.30, 0.89) # up-left corner
        if superimpose_2018:
            leg = ROOT.TLegend(0.13, 0.7, 0.5, 0.89) # whithout ratio
            # leg = ROOT.TLegend(0.11, 0.8, 0.6, 0.95) # with ratio
    elif legPos=="dr":
        leg = ROOT.TLegend(0.7, 0.11, 0.89, 0.3) # down-right corner
    elif legPos=="dl":
        leg = ROOT.TLegend(0.11, 0.11, 0.30, 0.3) # down-left corner
        if superimpose_2018:
            # leg = ROOT.TLegend(0.11, 0.11, 0.6, 0.25) # whithout ratio
            leg = ROOT.TLegend(0.13, 0.01, 0.55, 0.2) # with ratio
    leg.SetTextFont(42)
    leg.SetTextSize(0.04)
    leg.AddEntry("None", disk, "")
    leg.AddEntry("None", "", "")
    leg.AddEntry("None", "", "")

    # definition of the types of background
    bkgs        = ["inclusive", "delayed", "prompt"]
    if draw_error:
        graphs  = {bkg: ROOT.TGraphErrors() for bkg in bkgs}
    else:
        graphs  = {bkg: ROOT.TGraph() for bkg in bkgs}
        
    if superimpose_2018:
        if draw_error:
            graphs_2018 = {bkg: {"m": ROOT.TGraphErrors(), "p": ROOT.TGraphErrors()} for bkg in bkgs}
        else:
            graphs_2018 = {bkg: {"m": ROOT.TGraph(), "p": ROOT.TGraph()} for bkg in bkgs}

    funcs       = {}
    funcs_error = {}
    for chamber in chambers:
        print(f"Processing ---> {chamber}")
        ch,part = chamber.split("_")
        minX    = histos[chamber+"_prebeam_fit"].GetMinimumX()
        maxX    = histos[chamber+"_prebeam_fit"].GetMaximumX()
        
        funcs[chamber+"_inclusive_fit"] = ROOT.TF1(chamber+"_inclusive_fit", "pol1", minX, maxX)
        funcs[chamber+"_delayed_fit"]   = ROOT.TF1(chamber+"_delayed_fit", "pol1", minX, maxX)
        funcs[chamber+"_prompt_fit"]    = ROOT.TF1(chamber+"_prompt_fit", "pol1", minX, maxX)

        funcs[chamber+"_inclusive_fit"].SetParameter(0,(nbx_prebeam*histos[chamber+"_prebeam_fit"].GetParameter(0) + nbx_coll*histos[chamber+"_high_fit"].GetParameter(0) + nbx_noncoll*histos[chamber+"_low_fit"].GetParameter(0) + nbx_abort*histos[chamber+"_abort_fit"].GetParameter(0))/ntot)
        funcs[chamber+"_inclusive_fit"].SetParameter(1,(nbx_prebeam*histos[chamber+"_prebeam_fit"].GetParameter(1) + nbx_coll*histos[chamber+"_high_fit"].GetParameter(1) + nbx_noncoll*histos[chamber+"_low_fit"].GetParameter(1) + nbx_abort*histos[chamber+"_abort_fit"].GetParameter(1))/ntot)

        funcs[chamber+"_delayed_fit"].SetParameter(0,(nbx_prebeam*histos[chamber+"_prebeam_fit"].GetParameter(0) + nbx_noncoll*histos[chamber+"_low_fit"].GetParameter(0) + nbx_abort*histos[chamber+"_abort_fit"].GetParameter(0))/(ntot-nbx_coll))
        funcs[chamber+"_delayed_fit"].SetParameter(1,(nbx_prebeam*histos[chamber+"_prebeam_fit"].GetParameter(1) + nbx_noncoll*histos[chamber+"_low_fit"].GetParameter(1) + nbx_abort*histos[chamber+"_abort_fit"].GetParameter(1))/(ntot-nbx_coll))

        funcs[chamber+"_prompt_fit"].SetParameter(0,histos[chamber+"_high_fit"].GetParameter(0) - funcs[chamber+"_delayed_fit"].GetParameter(0))    
        funcs[chamber+"_prompt_fit"].SetParameter(1,histos[chamber+"_high_fit"].GetParameter(1) - funcs[chamber+"_delayed_fit"].GetParameter(1))    

 

        ####################
        # calculate errors #
        ####################
        funcs_error[chamber+"_inclusive_fit"] = {}
        funcs_error[chamber+"_delayed_fit"]   = {}
        funcs_error[chamber+"_prompt_fit"]    = {}

        if chamber in fitResults[str(fill)]:
            print(f"Getting the errors for {chamber}")
            # print(fitResults[str(fill)][chamber+"_prebeam"])

        # inclusive bkg #
        if onlystat_err:
            funcs_error[chamber+"_inclusive_fit"]["p0_error"]  = sqrt(((nbx_prebeam**2)*fitResults[str(fill)][chamber+"_prebeam"]["p0_error"]**2 + (nbx_coll**2)*fitResults[str(fill)][chamber+"_high"]["p0_error"]**2 + (nbx_noncoll**2)*fitResults[str(fill)][chamber+"_low"]["p0_error"]**2 + (nbx_abort**2)*fitResults[str(fill)][chamber+"_abort"]["p0_error"]**2)/(ntot**2))
            funcs_error[chamber+"_inclusive_fit"]["p1_error"]  = sqrt(((nbx_prebeam**2)*fitResults[str(fill)][chamber+"_prebeam"]["p1_error"]**2 + (nbx_coll**2)*fitResults[str(fill)][chamber+"_high"]["p1_error"]**2 + (nbx_noncoll**2)*fitResults[str(fill)][chamber+"_low"]["p1_error"]**2 + (nbx_abort**2)*fitResults[str(fill)][chamber+"_abort"]["p1_error"]**2)/(ntot**2))
        else:
            funcs_error[chamber+"_inclusive_fit"]["p0_error"]  = sqrt(((nbx_prebeam**2)*(fitResults[str(fill)][chamber+"_prebeam"]["chi2"]/fitResults[str(fill)][chamber+"_prebeam"]["ndf"])*fitResults[str(fill)][chamber+"_prebeam"]["p0_error"]**2 + (nbx_coll**2)*(fitResults[str(fill)][chamber+"_high"]["chi2"]/fitResults[str(fill)][chamber+"_high"]["ndf"])*fitResults[str(fill)][chamber+"_high"]["p0_error"]**2 + (nbx_noncoll**2)*(fitResults[str(fill)][chamber+"_low"]["chi2"]/fitResults[str(fill)][chamber+"_low"]["ndf"])*fitResults[str(fill)][chamber+"_low"]["p0_error"]**2 + (nbx_abort**2)*(fitResults[str(fill)][chamber+"_abort"]["chi2"]/fitResults[str(fill)][chamber+"_abort"]["ndf"])*fitResults[str(fill)][chamber+"_abort"]["p0_error"]**2)/(ntot**2))
            funcs_error[chamber+"_inclusive_fit"]["p1_error"]  = sqrt(((nbx_prebeam**2)*(fitResults[str(fill)][chamber+"_prebeam"]["chi2"]/fitResults[str(fill)][chamber+"_prebeam"]["ndf"])*fitResults[str(fill)][chamber+"_prebeam"]["p1_error"]**2 + (nbx_coll**2)*(fitResults[str(fill)][chamber+"_high"]["chi2"]/fitResults[str(fill)][chamber+"_high"]["ndf"])*fitResults[str(fill)][chamber+"_high"]["p1_error"]**2 + (nbx_noncoll**2)*(fitResults[str(fill)][chamber+"_low"]["chi2"]/fitResults[str(fill)][chamber+"_low"]["ndf"])*fitResults[str(fill)][chamber+"_low"]["p1_error"]**2 + (nbx_abort**2)*(fitResults[str(fill)][chamber+"_abort"]["chi2"]/fitResults[str(fill)][chamber+"_abort"]["ndf"])*fitResults[str(fill)][chamber+"_abort"]["p1_error"]**2)/(ntot**2))
        funcs_error[chamber+"_inclusive_fit"]["cov_p0p1"]  = ((nbx_prebeam**2)*fitResults[str(fill)][chamber+"_prebeam"]["covMatrix"][0][1] + (nbx_coll**2)*fitResults[str(fill)][chamber+"_high"]["covMatrix"][0][1] + (nbx_noncoll**2)*fitResults[str(fill)][chamber+"_low"]["covMatrix"][0][1] + (nbx_abort**2)*fitResults[str(fill)][chamber+"_abort"]["covMatrix"][0][1])/(ntot**2)
        funcs_error[chamber+"_inclusive_fit"]["covMatrix"] = [
                                                                            [funcs_error[chamber+"_inclusive_fit"]["p0_error"]**2, funcs_error[chamber+"_inclusive_fit"]["cov_p0p1"]],
                                                                            [funcs_error[chamber+"_inclusive_fit"]["cov_p0p1"], funcs_error[chamber+"_inclusive_fit"]["p1_error"]**2]
                                                                        ]
        # delayed bkg #
        if onlystat_err:
            funcs_error[chamber+"_delayed_fit"]["p0_error"]    = sqrt(((nbx_prebeam**2)*fitResults[str(fill)][chamber+"_prebeam"]["p0_error"]**2 + (nbx_noncoll**2)*fitResults[str(fill)][chamber+"_low"]["p0_error"]**2 + (nbx_abort**2)*fitResults[str(fill)][chamber+"_abort"]["p0_error"]**2)/(ntot**2))
            funcs_error[chamber+"_delayed_fit"]["p1_error"]    = sqrt(((nbx_prebeam**2)*fitResults[str(fill)][chamber+"_prebeam"]["p1_error"]**2 + (nbx_noncoll**2)*fitResults[str(fill)][chamber+"_low"]["p1_error"]**2 + (nbx_abort**2)*fitResults[str(fill)][chamber+"_abort"]["p1_error"]**2)/(ntot**2))
        else:
            funcs_error[chamber+"_delayed_fit"]["p0_error"]    = sqrt(((nbx_prebeam**2)*(fitResults[str(fill)][chamber+"_prebeam"]["chi2"]/fitResults[str(fill)][chamber+"_prebeam"]["ndf"])*fitResults[str(fill)][chamber+"_prebeam"]["p0_error"]**2 + (nbx_noncoll**2)*(fitResults[str(fill)][chamber+"_low"]["chi2"]/fitResults[str(fill)][chamber+"_low"]["ndf"])*fitResults[str(fill)][chamber+"_low"]["p0_error"]**2 + (nbx_abort**2)*(fitResults[str(fill)][chamber+"_abort"]["chi2"]/fitResults[str(fill)][chamber+"_abort"]["ndf"])*fitResults[str(fill)][chamber+"_abort"]["p0_error"]**2)/(ntot**2))
            funcs_error[chamber+"_delayed_fit"]["p1_error"]    = sqrt(((nbx_prebeam**2)*(fitResults[str(fill)][chamber+"_prebeam"]["chi2"]/fitResults[str(fill)][chamber+"_prebeam"]["ndf"])*fitResults[str(fill)][chamber+"_prebeam"]["p1_error"]**2 + (nbx_noncoll**2)*(fitResults[str(fill)][chamber+"_low"]["chi2"]/fitResults[str(fill)][chamber+"_low"]["ndf"])*fitResults[str(fill)][chamber+"_low"]["p1_error"]**2 + (nbx_abort**2)*(fitResults[str(fill)][chamber+"_abort"]["chi2"]/fitResults[str(fill)][chamber+"_abort"]["ndf"])*fitResults[str(fill)][chamber+"_abort"]["p1_error"]**2)/(ntot**2))
        funcs_error[chamber+"_delayed_fit"]["cov_p0p1"]    = ((nbx_prebeam**2)*fitResults[str(fill)][chamber+"_prebeam"]["covMatrix"][0][1] + (nbx_noncoll**2)*fitResults[str(fill)][chamber+"_low"]["covMatrix"][0][1] + (nbx_abort**2)*fitResults[str(fill)][chamber+"_abort"]["covMatrix"][0][1])/(ntot**2)
        funcs_error[chamber+"_delayed_fit"]["covMatrix"]   = [
                                                                            [funcs_error[chamber+"_delayed_fit"]["p0_error"]**2, funcs_error[chamber+"_delayed_fit"]["cov_p0p1"]],
                                                                            [funcs_error[chamber+"_delayed_fit"]["cov_p0p1"], funcs_error[chamber+"_delayed_fit"]["p1_error"]**2]
                                                                        ]
        # prompt bkg #
        if onlystat_err:
            funcs_error[chamber+"_prompt_fit"]["p0_error"]     = sqrt(fitResults[str(fill)][chamber+"_high"]["p0_error"]**2 + funcs_error[chamber+"_delayed_fit"]["p0_error"]**2)
            funcs_error[chamber+"_prompt_fit"]["p1_error"]     = sqrt(fitResults[str(fill)][chamber+"_high"]["p1_error"]**2 + funcs_error[chamber+"_delayed_fit"]["p1_error"]**2)
        else:
            funcs_error[chamber+"_prompt_fit"]["p0_error"]     = sqrt((fitResults[str(fill)][chamber+"_high"]["chi2"]/fitResults[str(fill)][chamber+"_high"]["ndf"])*(fitResults[str(fill)][chamber+"_high"]["p0_error"]**2) + funcs_error[chamber+"_delayed_fit"]["p0_error"]**2)
            funcs_error[chamber+"_prompt_fit"]["p1_error"]     = sqrt((fitResults[str(fill)][chamber+"_high"]["chi2"]/fitResults[str(fill)][chamber+"_high"]["ndf"])*(fitResults[str(fill)][chamber+"_high"]["p1_error"]**2) + funcs_error[chamber+"_delayed_fit"]["p1_error"]**2)
        funcs_error[chamber+"_prompt_fit"]["cov_p0p1"]     = fitResults[str(fill)][chamber+"_high"]["covMatrix"][0][1] + funcs_error[chamber+"_delayed_fit"]["cov_p0p1"]
        funcs_error[chamber+"_prompt_fit"]["covMatrix"]    = [
                                                                            [funcs_error[chamber+"_prompt_fit"]["p0_error"]**2, funcs_error[chamber+"_prompt_fit"]["cov_p0p1"]],
                                                                            [funcs_error[chamber+"_prompt_fit"]["cov_p0p1"], funcs_error[chamber+"_prompt_fit"]["p1_error"]**2]
                                                                        ]

        

        # for bkg in bkgs:
        #     print(f"Processing ---> {disk} {chamber} for {bkg} background")
        #     func        = funcs[chamber+"_"+bkg+"_fit"]
        #     print(type(graphs[bkg]))
        #     if draw_error:
        #         x       = 10
        #         graphs[bkg].AddPointError(geometry_dict[ch][part]["eta"], func.Eval(x), 0.0, sqrt((x**2)*funcs_error[chamber+f"_{bkg}_fit"]["p1_error"]**2 + funcs_error[chamber+f"_{bkg}_fit"]["p0_error"]**2 + 2*x*funcs_error[chamber+f"_{bkg}_fit"]["cov_p0p1"])) # func.Eval(10) means we are going to fix the Inst.Lumi to 1e34cm^-2s^-1
        #     else:
        #         graphs[bkg].AddPoint(geometry_dict[ch][part]["eta"], func.Eval(x)) # func.Eval(10) means we are going to fix the Inst.Lumi to 1e34cm^-2s^-1
                # calculate backgrounds functions also per phi-sector #
    for ch in [f"REm{disk_number}2",f"REm{disk_number}3",f"REp{disk_number}3",f"REp{disk_number}2"]:
        for sec in sectors:
            funcs[ch+"_"+sec+"_inclusive_fit"] = ROOT.TF1(ch+"_"+sec+"_inclusive_fit", "pol1", minX, maxX)
            funcs[ch+"_"+sec+"_delayed_fit"]   = ROOT.TF1(ch+"_"+sec+"_delayed_fit", "pol1", minX, maxX)
            funcs[ch+"_"+sec+"_prompt_fit"]    = ROOT.TF1(ch+"_"+sec+"_prompt_fit", "pol1", minX, maxX)
        
            funcs[ch+"_"+sec+"_inclusive_fit"].SetParameter(0,(nbx_prebeam*histos[ch+"_"+sec+"_prebeam_fit"].GetParameter(0) + nbx_coll*histos[ch+"_"+sec+"_high_fit"].GetParameter(0) + nbx_noncoll*histos[ch+"_"+sec+"_low_fit"].GetParameter(0) + nbx_abort*histos[ch+"_"+sec+"_abort_fit"].GetParameter(0))/ntot)
            funcs[ch+"_"+sec+"_inclusive_fit"].SetParameter(1,(nbx_prebeam*histos[ch+"_"+sec+"_prebeam_fit"].GetParameter(1) + nbx_coll*histos[ch+"_"+sec+"_high_fit"].GetParameter(1) + nbx_noncoll*histos[ch+"_"+sec+"_low_fit"].GetParameter(1) + nbx_abort*histos[ch+"_"+sec+"_abort_fit"].GetParameter(1))/ntot)

            funcs[ch+"_"+sec+"_delayed_fit"].SetParameter(0,(nbx_prebeam*histos[ch+"_"+sec+"_prebeam_fit"].GetParameter(0) + nbx_noncoll*histos[ch+"_"+sec+"_low_fit"].GetParameter(0) + nbx_abort*histos[ch+"_"+sec+"_abort_fit"].GetParameter(0))/(ntot-nbx_coll))
            funcs[ch+"_"+sec+"_delayed_fit"].SetParameter(1,(nbx_prebeam*histos[ch+"_"+sec+"_prebeam_fit"].GetParameter(1) + nbx_noncoll*histos[ch+"_"+sec+"_low_fit"].GetParameter(1) + nbx_abort*histos[ch+"_"+sec+"_abort_fit"].GetParameter(1))/(ntot-nbx_coll))

            funcs[ch+"_"+sec+"_prompt_fit"].SetParameter(0,histos[ch+"_"+sec+"_high_fit"].GetParameter(0) - funcs[ch+"_"+sec+"_prompt_fit"].GetParameter(0))    
            funcs[ch+"_"+sec+"_prompt_fit"].SetParameter(1,histos[ch+"_"+sec+"_high_fit"].GetParameter(1) - funcs[ch+"_"+sec+"_delayed_fit"].GetParameter(1))   
    # print(funcs.keys())
    data                = {}
    for bkg in bkgs:
        data[bkg]       = {}
        data[bkg]["X"]  = []
        data[bkg]["Y"]  = []
        data[bkg]["EX"] = []
        data[bkg]["EY"] = []
        for chamber in chambers:
            ch,part = chamber.split("_")
            print(f"Processing ---> {disk} {chamber} for {bkg} background")
            func        = funcs[chamber+"_"+bkg+"_fit"]
            x           = 10
            if draw_error:
                data[bkg]["X"].append(geometry_dict[ch][part]["eta"]) 
                data[bkg]["Y"].append(func.Eval(x)) # func.Eval(10) means we are going to fix the Inst.Lumi to 1e34cm^-2s^-1
                data[bkg]["EX"].append(0.0)
                # data[bkg]["EY"].append(sqrt(abs((x**2)*funcs_error[chamber+f"_{bkg}_fit"]["p1_error"]**2 + funcs_error[chamber+f"_{bkg}_fit"]["p0_error"]**2 + 2*x*funcs_error[chamber+f"_{bkg}_fit"]["cov_p0p1"])))
                mean_on_sectors     = mean([funcs[ch+"_"+sec+f"_{bkg}_fit"].Eval(x) for sec in sectors if funcs[ch+"_"+sec+f"_{bkg}_fit"].Eval(x)>0])
                stdev_on_sectors    = stdev([funcs[ch+"_"+sec+f"_{bkg}_fit"].Eval(x) for sec in sectors if funcs[ch+"_"+sec+f"_{bkg}_fit"].Eval(x)>0])
                y_err               = stdev_on_sectors*func.Eval(x)/mean_on_sectors
                data[bkg]["EY"].append(y_err)
                
                print([funcs[ch+"_"+sec+f"_{bkg}_fit"].Eval(x) for sec in sectors if funcs[ch+"_"+sec+f"_{bkg}_fit"].Eval(x)>0])
                print("stdev:               ", stdev_on_sectors)
                print("mean:                ", mean_on_sectors)
                print("y_err:               ", y_err)
                print("y value:             ", func.Eval(x))
            else:
                data[bkg]["X"].append(geometry_dict[ch][part]["eta"]) 
                data[bkg]["Y"].append(func.Eval(x)) # func.Eval(10) means we are going to fix the Inst.Lumi to 1e34cm^-2s^-1
                data[bkg]["EX"].append(0.0)
                data[bkg]["EY"].append(0.0)

    if draw_error:
        graphs  = {bkg: ROOT.TGraphErrors(len(data[bkg]["X"]), array.array("d", data[bkg]["X"]), array.array("d", data[bkg]["Y"]), array.array("d", data[bkg]["EX"]), array.array("d", data[bkg]["EY"])) for bkg in bkgs}
    else:
        graphs  = {bkg: ROOT.TGraph(len(data[bkg]["X"]), array.array("d", data[bkg]["X"]), array.array("d", data[bkg]["Y"])) for bkg in bkgs}


    print("Drawing the graphs")
    for i,bkg in enumerate(bkgs):
        # axis options
        # graphs[bkg].SetTitle(disk)
        graphs[bkg].SetTitle("")
        graphs[bkg].GetXaxis().SetTitle("#eta")
        graphs[bkg].GetXaxis().SetLabelSize(0) # 0.04
        graphs[bkg].GetXaxis().SetTitleSize(0.045)
        graphs[bkg].GetYaxis().SetTitle("Hit Rate (Hz/cm^{2})")
        graphs[bkg].GetYaxis().SetLabelSize(0.04)
        graphs[bkg].GetYaxis().SetTitleSize(0.045)
        graphs[bkg].GetYaxis().SetTitleOffset(0.9)
        graphs[bkg].SetMinimum(1e-1)
        # graphs[bkg].SetMaximum(25)
        graphs[bkg].SetMaximum(1e2)
        
        # graphics options
        graphs[bkg].SetLineColor(graphicsOptions[bkg]["color"])
        graphs[bkg].SetMarkerColor(graphicsOptions[bkg]["color"])
        graphs[bkg].SetMarkerStyle(graphicsOptions[bkg]["marker"])
        graphs[bkg].SetMarkerSize(1.0)
        # graphs[bkg].SetFillColorAlpha(graphicsOptions[bkg]["color"], 0.3)
        # graphs[bkg].SetFillStyle(3001)
        if i==0:
            graphs[bkg].Draw("ap")
        else:
            graphs[bkg].Draw("p")
        

        if superimpose_2018:
            leg.SetNColumns(3)
            leg.AddEntry("None", bkg.replace("inclusive","Inclusive").replace("delayed","Delayed").replace("prompt","Prompt"), "")
            leg.AddEntry(graphs[bkg], bkg.replace("inclusive",f"{year}").replace("delayed",f"{year}").replace("prompt",f"{year}"), "p")
        else:
            leg.AddEntry(graphs[bkg], bkg.replace("inclusive","Inclusive").replace("delayed","Delayed").replace("prompt","Prompt"), "p")

        ###### Add 2018 data ######
        if superimpose_2018:
            print("\n")
            print("SUPERIMPOSING 2018 DATA")

            X       = []
            X_err   = []
            Y       = []
            Y_err   = []
            for chamber in [chamber for chamber in chambers if (("m" in chamber) and ("m".islower()))]:
                # print("Negative ENDCAP")
                # print(f"Processing ---> {disk} {chamber} for {bkg} background")
                ch,part = chamber.split("_")
                # print(f"Adding point for {ch} {part}")
                X.append(geometry_dict[ch][part]["eta"])
                X_err.append(0.0)
                Y.append(HitRate_eta_2018[chamber][bkg])
                Y_err.append(HitRate_eta_2018[chamber][bkg+"_error"]/HitRate_eta_2018[chamber][bkg+"_mean"] * HitRate_eta_2018[chamber][bkg])
                # graphs_2018[bkg]["m"].AddPoint(geometry_dict[ch][part]["eta"], HitRate_eta_2018[chamber][bkg])

                # print(f'X:              {X}')
                # print(f'Y:              {Y}')
                # print(f'X_err:          {X_err}')
                # print(f'Perc. Error:    {HitRate_eta_2018[chamber][bkg+"_error"]/HitRate_eta_2018[chamber][bkg+"_mean"]}')
                # print(f'Y_err:          {Y_err}')
            
            graphs_2018[bkg]["m"] = ROOT.TGraphErrors(len(X), array.array('d', X), array.array('d', Y), array.array('d', X_err), array.array('d', Y_err))
            # graphics options
            graphs_2018[bkg]["m"].SetLineColor(graphicsOptions[bkg]["color"])
            graphs_2018[bkg]["m"].SetMarkerColor(graphicsOptions[bkg]["color"])
            graphs_2018[bkg]["m"].SetMarkerStyle(graphicsOptions[bkg]["marker"])
            graphs_2018[bkg]["m"].SetLineStyle(ROOT.kDashed)
            graphs_2018[bkg]["m"].SetLineWidth(1)
            # graphs_2018[bkg]["m"].SetFillColorAlpha(graphicsOptions[bkg]["color"], 0.3)
            graphs_2018[bkg]["m"].SetFillColorAlpha(graphicsOptions[bkg]["color"], 0.1)
            graphs_2018[bkg]["m"].Draw("le3 SAME")

            X      = []
            X_err  = []
            Y      = []
            Y_err  = []
            for chamber in [chamber for chamber in chambers if (("p" in chamber) and ("p".islower()))]:
                # print("Positive ENDCAP")
                # print(f"Processing ---> {disk} {chamber} for {bkg} background")
                ch,part = chamber.split("_")
                # print(f"Adding point for {ch} {part}")
                X.append(geometry_dict[ch][part]["eta"])
                X_err.append(0.0)
                Y.append(HitRate_eta_2018[chamber][bkg])
                Y_err.append(HitRate_eta_2018[chamber][bkg+"_error"]/HitRate_eta_2018[chamber][bkg+"_mean"] * HitRate_eta_2018[chamber][bkg])
                # graphs_2018[bkg]["p"].AddPoint(geometry_dict[ch][part]["eta"], HitRate_eta_2018[chamber][bkg])
            
            graphs_2018[bkg]["p"] = ROOT.TGraphErrors(len(X), array.array('d', X), array.array('d', Y), array.array('d', X_err), array.array('d', Y_err))
            # graphics options
            graphs_2018[bkg]["p"].SetLineColor(graphicsOptions[bkg]["color"])
            graphs_2018[bkg]["p"].SetMarkerColor(graphicsOptions[bkg]["color"])
            graphs_2018[bkg]["p"].SetMarkerStyle(graphicsOptions[bkg]["marker"])
            graphs_2018[bkg]["p"].SetLineStyle(ROOT.kDashed)
            graphs_2018[bkg]["p"].SetLineWidth(1)
            # graphs_2018[bkg]["p"].SetFillColorAlpha(graphicsOptions[bkg]["color"], 0.3)
            graphs_2018[bkg]["p"].SetFillColorAlpha(graphicsOptions[bkg]["color"], 0.1)
            graphs_2018[bkg]["p"].Draw("le3 SAME")

            leg.AddEntry(graphs_2018[bkg]["p"], bkg.replace("inclusive","2018").replace("delayed","2018").replace("prompt","2018"), "lf")


    leg.Draw("SAME")


    # pad1.cd()
    writeExtraText          = 1
    # extraText               = "Work in progress"
    extraText               = "Preliminary"
    lepText                 = ""
    # lumi_sqrtS              = disk + ", " + "%s fb^{-1}  (13.6 TeV)"%(round(lumi,3))
    # lumi_sqrtS              = disk + ", " + "(13.6 TeV)"
    if not superimpose_2018:
        lumi_sqrtS          = "Run 3 (13.6 TeV)"
    else:
        lumi_sqrtS          = "Run 2 (13 TeV), Run 3 (13.6 TeV)"
    iPeriod                 = 0
    iPos                    = 0
    CMS_lumi(pad1, lumi_sqrtS, iPos, writeExtraText, extraText, lepText) # CMS_lumi(pad, lumi_sqrtS, iPosX, writeExtraText, extraText, lepText), lepText is usually a region
    # pad1.Draw()
    pad1.Update()

    c.cd()

    if superimpose_2018:
        pad2 = ROOT.TPad("pad2", "pad2", 0, 0, 1, 0.30)
        pad2.SetTopMargin(0.05)
        pad2.SetBottomMargin(0.25)
        pad2.SetLeftMargin(0.12)
        pad2.SetRightMargin(0.05)
        pad2.SetGrid()
        ROOT.gStyle.SetHatchesSpacing(2)
        ROOT.gStyle.SetHatchesLineWidth(2)
        c.cd()
        pad2.Draw()
        pad2.cd()

        # Create the ratio histogram
        hist_ratio  = {}
        for i,bkg in enumerate(bkgs):
            X           = data[bkg]["X"]

            Y_2024      = data[bkg]["Y"]
            Y_2018      = [HitRate_eta_2018[chamber][bkg] for chamber in chambers]
            Y           = [y_2024/y_2018 for y_2024,y_2018 in zip(Y_2024,Y_2018)]

            X_err       = [0 for x in X]

            print(chambers)
            print(Y_2024)

            # Y_err_2024  = [((10**2)*funcs_error[chamber+f"_{bkg}_fit"]["p1_error"]**2 + funcs_error[chamber+f"_{bkg}_fit"]["p0_error"]**2 + 2*10*funcs_error[chamber+f"_{bkg}_fit"]["cov_p0p1"])/(y_2024**2) for chamber,y_2024 in zip(chambers,Y_2024)]
            Y_err_2024  = [(y_err_2024/y_2024)**2 for y_2024,y_err_2024 in zip(Y_2024,data[bkg]["EY"])]
            Y_err_2018  = [(y_err_2018/y_2018)**2 for y_2018,y_err_2018 in zip(Y_2018,[HitRate_eta_2018[chamber][bkg+"_error"]/HitRate_eta_2018[chamber][bkg+"_mean"] * HitRate_eta_2018[chamber][bkg] for chamber in chambers])]
            Y_err       = [y*sqrt(abs(y_err_2024 + y_err_2018)) for x,y,y_err_2024,y_err_2018 in zip(X,Y,Y_err_2024,Y_err_2018)]



            print(f"X:      {X}")
            print(f"Y:      {Y}")
            print(f"X_err:  {X_err}")
            print(f"Y_err:  {Y_err}")
            hist_ratio[bkg] = ROOT.TGraphErrors(len(X), array.array('d', X), array.array('d', Y), array.array('d', X_err), array.array('d', Y_err))

            # hist_ratio[bkg].SetMinimum(0)
            # hist_ratio[bkg].SetMaximum(2)
            hist_ratio[bkg].SetMinimum(hist_ratio[bkg].GetHistogram().GetMinimum()*0.9)
            hist_ratio[bkg].SetMaximum(hist_ratio[bkg].GetHistogram().GetMaximum()*1.1)

            hist_ratio[bkg].SetTitle("")

            hist_ratio[bkg].GetXaxis().SetTitle("#eta")
            hist_ratio[bkg].GetXaxis().SetTitleSize(0.1)
            hist_ratio[bkg].GetXaxis().SetLabelSize(0.1)

            hist_ratio[bkg].GetYaxis().SetTitle(f"{year} Data / 2018 Data") # "2024 / 2018"
            hist_ratio[bkg].GetYaxis().SetTitleOffset(0.3)
            hist_ratio[bkg].GetYaxis().CenterTitle(True)
            hist_ratio[bkg].GetYaxis().SetLabelSize(0.05)
            hist_ratio[bkg].GetYaxis().SetTitleSize(0.075)
            # hist_ratio[bkg].SetNdivisions(503, "Y")  # Reduce number of ticks on y-axis
            hist_ratio[bkg].SetLineColor(graphicsOptions[bkg]["color"])
            hist_ratio[bkg].SetMarkerColor(graphicsOptions[bkg]["color"])
            hist_ratio[bkg].SetMarkerStyle(ROOT.kFullCircle)
            hist_ratio[bkg].SetMarkerSize(1.0)
            # hist_ratio[bkg].SetFillColorAlpha(graphicsOptions[bkg]["color"], 0.3)
            # hist_ratio[bkg].SetFillStyle(3002)

        for i,bkg in enumerate(hist_ratio):
            h_ratio = hist_ratio[bkg]
            if i==0:
                h_ratio.Draw("Ap")
                line1 = ROOT.TLine(min(data[bkg]["X"]), 1, max(data[bkg]["X"]), 1)  # (x1, y1, x2, y2)
                line1 = ROOT.TLine(h_ratio.GetXaxis().GetXmin(), 1, h_ratio.GetXaxis().GetXmax(), 1)  # (x1, y1, x2, y2)
                line1.SetLineColor(ROOT.kBlack)
                line1.SetLineWidth(1)
                line1.SetLineStyle(ROOT.kSolid)
                line1.Draw("SAME")
            else:
                h_ratio.Draw("pSAME")

        pad2.Update()

        c.cd()
        c.RedrawAxis()
        pad2.RedrawAxis()
    c.cd()
    # Save the plot
    if printPlots:
        if superimpose_2018:
            c.SaveAs(outDir_png+"/HitRateVsEta_"+disk+"_bkgs_w2018_Ratio_syst_"+str(year)+"_APPROVED.png")
            c.SaveAs(outDir_pdf+"/HitRateVsEta_"+disk+"_bkgs_w2018_Ratio_syst_"+str(year)+"_APPROVED.pdf")
            c.SaveAs(outDir_C+"/HitRateVsEta_"+disk+"_bkgs_w2018_Ratio_syst_"+str(year)+"_APPROVED.C")
        else:
            c.SaveAs(outDir_png+"/HitRateVsEta_"+disk+"_bkgs_"+str(year)+"_APPROVED.png")
            c.SaveAs(outDir_pdf+"/HitRateVsEta_"+disk+"_bkgs_"+str(year)+"_APPROVED.pdf")
            c.SaveAs(outDir_C+"/HitRateVsEta_"+disk+"_bkgs_"+str(year)+"_APPROVED.C")


if chambers[0].startswith("RB"):
    if chambers[0] in ["RB1in","RB1out"]:
        HitRateVsEta_Barrel_bkgs(inFile, chambers[0], outDir, lumi*1e-3, printPlots, legPos="dl")
    elif chambers[0] in ["RB2in","RB2out","RB3","RB4"]:
        HitRateVsEta_Barrel_bkgs(inFile, chambers[0], outDir, lumi*1e-3, printPlots, legPos="ul")

elif chambers[0].startswith("RE"):
    HitRateVsEta_Endcap_bkgs(inFile, chambers[0], outDir, lumi*1e-3, printPlots, legPos="ul")
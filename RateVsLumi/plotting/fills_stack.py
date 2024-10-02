import os
import argparse
import sys
import ROOT
from CMS_lumi import CMS_lumi
from loadHists import loadHists
from graphicsOptions import graphicsOptions
import copy
from math import sqrt
import array
import numpy as np
import json
ROOT.gStyle.SetOptStat(0)
ROOT.gROOT.SetBatch(1)


printPlots                  = True
# histo files #
RPC_fit_file                = {}
RPC_fit_file["9573"]        = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_9573_dead_and_noisy_noSectorRollSubdvision/RPC_fit_F9573.root"
RPC_fit_file["8754"]        = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_8754/RPC_fit_F8754.root"
# fit results #
fitResults_file             = {}
fitResults                  = {}
fitResults_file["9573"]     = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_9573_dead_and_noisy_noSectorRollSubdvision/RPC_fit_F9573_fitResults.json"
fitResults_file["8754"]     = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_8754/RPC_fit_F8754_fitResults.json"
with open(fitResults_file["9573"], "r") as f:
    fitResults["9573"]      = json.load(f)
with open(fitResults_file["8754"], "r") as f:
    fitResults["8754"]      = json.load(f)

# plots output directory #
outDir                      = "/eos/user/l/lfavilla/RPC/plots/RPC2024_approval/Additional_Plots"
# output json file for backgrounds parameters #
outJson                     = f"{outDir}/RPC_fit_F9573_F8754_backgrounds_parameters.json"




bkg                  = "prompt" # inclusive, delayed, prompt
legPos               = "ul"
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

# chambers             = ["REp42","REm42"]
chambers             = ["REp42_S06","REm42_S06"]
# chambers             = ["Wm2_RB4_S06","Wp2_RB4_S06"]
endcap_disks         = ["RE1","RE2","RE3","RE4"]
fills                = [8754,9573]
draw_error           = True

###### Retrieve histograms saved into a .root file ######
def loadHists(histFile):
    f           = ROOT.TFile(histFile, "READ")
    histList    = {}
    keyList     = f.GetListOfKeys()
    for key in keyList:
        hist    = f.Get(key.GetName())
        if (type(hist) == ROOT.TH1F) or (type(hist) == ROOT.TH2F):
            hist.SetDirectory(ROOT.gROOT)
        # hist.SetName(key.GetName())
        histList[key.GetName()]=hist
    if len(histList)==0: 
        raise Exception("ERROR: histList is empty!")
    f.Close()
    return histList

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


# Get the list of histograms
histos = {}
for fill in fills:
    histos[str(fill)] = loadHists(RPC_fit_file[str(fill)])
print(histos.keys())
print(len(histos["9573"].keys()))
print(len(histos["8754"].keys()))
# histos      = loadHists(inFile)

### Hit Rate vs Luminosity - [Double Chamber] ###
print(f"chambers selected: {chambers} ---> background: {bkg}")
outDir_png  = outDir + "/png"
outDir_pdf  = outDir + "/pdf"
outDir_C    = outDir + "/C"


if False:
    # Create the canvas
    ROOT.gStyle.SetOptStat(0)
    c = ROOT.TCanvas("c","c",900,700)
    c.SetFillColor(0)
    c.SetBorderMode(0)
    c.SetFrameFillStyle(0)
    c.SetFrameBorderMode(0)
    c.SetLeftMargin(0.12)
    c.SetRightMargin(0.9)
    c.SetTopMargin(1)
    c.SetBottomMargin(-1)
    c.SetTickx(1)
    c.SetTicky(1)
    c.Draw()


    pad1= ROOT.TPad("pad1", "pad1", 0, 0.31 , 1, 1)
    pad1.SetTopMargin(0.1)
    pad1.SetBottomMargin(0.02)
    pad1.SetLeftMargin(0.12)
    pad1.SetRightMargin(0.05)
    pad1.SetBorderMode(0)
    pad1.SetTickx(1)
    pad1.SetTicky(1)
    pad1.SetGrid()
    pad1.Draw()
    pad1.cd()



    # Create the legend
    if legPos=="ur":
        leg = ROOT.TLegend(0.7, 0.7, 0.89, 0.89) # up-right corner
    elif legPos=="ul":
        leg = ROOT.TLegend(0.15, 0.7, 0.4, 0.89) # up-left corner
    elif legPos=="dr":
        leg = ROOT.TLegend(0.7, 0.11, 0.89, 0.3) # down-right corner
    elif legPos=="dl":
        leg = ROOT.TLegend(0.11, 0.11, 0.45, 0.35) # down-left corner
    leg.SetTextFont(42)
    leg.SetTextSize(0.035)



    hist = ROOT.TH1F(bkg+"_fit", bkg.replace("inclusive","Inclusive Bkg").replace("delayed","Delayed Bkg").replace("prompt","Prompt Bkg"), 100, 0, 25)
    # hist.SetTitle("") # for RPC2024_approval
    hist.SetTitleSize(1)
    # axis options
    # hist.GetXaxis().SetTitle("Instantaneous Luminosity (10^{33} cm^{-2} s^{-1})")
    hist.GetXaxis().SetTitle("")
    hist.GetXaxis().SetLabelSize(0) # 0.03
    hist.GetXaxis().SetTitleSize(0.045)
    hist.GetYaxis().SetTitle("Hit Rate (Hz/cm^{2})")
    hist.GetYaxis().SetLabelSize(0.03)
    hist.GetYaxis().SetTitleSize(0.045)
    hist.SetMinimum(0)
    hist.SetMaximum(25)
    # hist.SetMaximum(funcs[ch+"_inclusive_fit"].GetMaximum()*2.0)
    hist.Draw()

    funcs = {}
    funcs_error = {}
    Band  = {} # dictionary error bands for backgrounds
    for fill in fills:
        if fill==8754:
            lumi                    = 440.273 + 175.600 + 27.104                        # pb-1, Runs: 367413 + 367406 + 367415 
            colliding_scheme_txt    = "../fill_schemes/Fill_8754/colliding_8754.txt"    # Fill=8754
        elif fill==9573:
            lumi                    = 635.347                                           # pb-1, Runs: 380115
            colliding_scheme_txt    = "../fill_schemes/Fill_9573/colliding_9573.txt"    # Fill=9573

        ntot                 = 3564
        bxIDs, bxID_coll, bxID_prebeam, bxID_abort, bxID_noncoll = bunches_scheme(colliding_scheme_txt, 3564)
        nbx_prebeam          = len(bxID_prebeam)
        nbx_coll             = len(bxID_coll)
        nbx_noncoll          = len(bxID_noncoll)
        nbx_abort            = len(bxID_abort)
        funcs[str(fill)]     = {}
        funcs_error[str(fill)] = {}
        # for i,ch in enumerate(sorted(chambers, key=lambda x: histos[str(fill)][x+"_high"].GetMaximum(), reverse=True)):
        for i,ch in enumerate(chambers):        
            # definition of the types of background
            minX    = histos[str(fill)][ch+"_prebeam_fit"].GetMinimumX()
            maxX    = histos[str(fill)][ch+"_prebeam_fit"].GetMaximumX()
            
            funcs[str(fill)][ch+"_inclusive_fit"] = ROOT.TF1(ch+"_inclusive_fit", "pol1", minX, maxX)
            funcs[str(fill)][ch+"_delayed_fit"]   = ROOT.TF1(ch+"_delayed_fit", "pol1", minX, maxX)
            funcs[str(fill)][ch+"_prompt_fit"]    = ROOT.TF1(ch+"_prompt_fit", "pol1", minX, maxX)

            # inclusive bkg #
            funcs[str(fill)][ch+"_inclusive_fit"].SetParameter(0,(nbx_prebeam*histos[str(fill)][ch+"_prebeam_fit"].GetParameter(0) + nbx_coll*histos[str(fill)][ch+"_high_fit"].GetParameter(0) + nbx_noncoll*histos[str(fill)][ch+"_low_fit"].GetParameter(0) + nbx_abort*histos[str(fill)][ch+"_abort_fit"].GetParameter(0))/ntot)
            funcs[str(fill)][ch+"_inclusive_fit"].SetParameter(1,(nbx_prebeam*histos[str(fill)][ch+"_prebeam_fit"].GetParameter(1) + nbx_coll*histos[str(fill)][ch+"_high_fit"].GetParameter(1) + nbx_noncoll*histos[str(fill)][ch+"_low_fit"].GetParameter(1) + nbx_abort*histos[str(fill)][ch+"_abort_fit"].GetParameter(1))/ntot)
            # funcs[str(fill)][ch+"_inclusive_fit"].SetParError(0,(nbx_prebeam*histos[str(fill)][ch+"_prebeam_fit"].GetParError(0) + nbx_coll*histos[str(fill)][ch+"_high_fit"].GetParError(0) + nbx_noncoll*histos[str(fill)][ch+"_low_fit"].GetParError(0) + nbx_abort*histos[str(fill)][ch+"_abort_fit"].GetParError(0))/ntot)
            # funcs[str(fill)][ch+"_inclusive_fit"].SetParError(1,(nbx_prebeam*histos[str(fill)][ch+"_prebeam_fit"].GetParError(1) + nbx_coll*histos[str(fill)][ch+"_high_fit"].GetParError(1) + nbx_noncoll*histos[str(fill)][ch+"_low_fit"].GetParError(1) + nbx_abort*histos[str(fill)][ch+"_abort_fit"].GetParError(1))/ntot)
            
            # delayed bkg #
            funcs[str(fill)][ch+"_delayed_fit"].SetParameter(0,(nbx_prebeam*histos[str(fill)][ch+"_prebeam_fit"].GetParameter(0) + nbx_noncoll*histos[str(fill)][ch+"_low_fit"].GetParameter(0) + nbx_abort*histos[str(fill)][ch+"_abort_fit"].GetParameter(0))/(ntot-nbx_coll))
            funcs[str(fill)][ch+"_delayed_fit"].SetParameter(1,(nbx_prebeam*histos[str(fill)][ch+"_prebeam_fit"].GetParameter(1) + nbx_noncoll*histos[str(fill)][ch+"_low_fit"].GetParameter(1) + nbx_abort*histos[str(fill)][ch+"_abort_fit"].GetParameter(1))/(ntot-nbx_coll))
            # funcs[str(fill)][ch+"_delayed_fit"].SetParError(0,(nbx_prebeam*histos[str(fill)][ch+"_prebeam_fit"].GetParError(0) + nbx_noncoll*histos[str(fill)][ch+"_low_fit"].GetParError(0) + nbx_abort*histos[str(fill)][ch+"_abort_fit"].GetParError(0))/(ntot-nbx_coll))
            # funcs[str(fill)][ch+"_delayed_fit"].SetParError(1,(nbx_prebeam*histos[str(fill)][ch+"_prebeam_fit"].GetParError(1) + nbx_noncoll*histos[str(fill)][ch+"_low_fit"].GetParError(1) + nbx_abort*histos[str(fill)][ch+"_abort_fit"].GetParError(1))/(ntot-nbx_coll))
            
            # prompt bkg #
            funcs[str(fill)][ch+"_prompt_fit"].SetParameter(0,histos[str(fill)][ch+"_high_fit"].GetParameter(0) - funcs[str(fill)][ch+"_delayed_fit"].GetParameter(0))    
            funcs[str(fill)][ch+"_prompt_fit"].SetParameter(1,histos[str(fill)][ch+"_high_fit"].GetParameter(1) - funcs[str(fill)][ch+"_delayed_fit"].GetParameter(1))
            # funcs[str(fill)][ch+"_prompt_fit"].SetParError(0,histos[str(fill)][ch+"_high_fit"].GetParError(0) - funcs[str(fill)][ch+"_delayed_fit"].GetParError(0))
            # funcs[str(fill)][ch+"_prompt_fit"].SetParError(1,histos[str(fill)][ch+"_high_fit"].GetParError(1) - funcs[str(fill)][ch+"_delayed_fit"].GetParError(1))


            ####################
            # calculate errors #
            ####################
            funcs_error[str(fill)][ch+"_inclusive_fit"] = {}
            funcs_error[str(fill)][ch+"_delayed_fit"]   = {}
            funcs_error[str(fill)][ch+"_prompt_fit"]    = {}

            # inclusive bkg #
            # funcs_error[str(fill)][ch+"_inclusive_fit"]["p0_error"]  = sqrt(((nbx_prebeam**2)*fitResults[str(fill)][ch+"_prebeam"]["p0_error"]**2 + (nbx_coll**2)*fitResults[str(fill)][ch+"_high"]["p0_error"]**2 + (nbx_noncoll**2)*fitResults[str(fill)][ch+"_low"]["p0_error"]**2 + (nbx_abort**2)*fitResults[str(fill)][ch+"_abort"]["p0_error"]**2)/(ntot**2))
            # funcs_error[str(fill)][ch+"_inclusive_fit"]["p1_error"]  = sqrt(((nbx_prebeam**2)*fitResults[str(fill)][ch+"_prebeam"]["p1_error"]**2 + (nbx_coll**2)*fitResults[str(fill)][ch+"_high"]["p1_error"]**2 + (nbx_noncoll**2)*fitResults[str(fill)][ch+"_low"]["p1_error"]**2 + (nbx_abort**2)*fitResults[str(fill)][ch+"_abort"]["p1_error"]**2)/(ntot**2))
            funcs_error[str(fill)][ch+"_inclusive_fit"]["p0_error"]  = sqrt(((nbx_prebeam**2)*(fitResults[str(fill)][ch+"_prebeam"]["chi2"]/fitResults[str(fill)][ch+"_prebeam"]["ndf"])*fitResults[str(fill)][ch+"_prebeam"]["p0_error"]**2 + (nbx_coll**2)*(fitResults[str(fill)][ch+"_high"]["chi2"]/fitResults[str(fill)][ch+"_high"]["ndf"])*fitResults[str(fill)][ch+"_high"]["p0_error"]**2 + (nbx_noncoll**2)*(fitResults[str(fill)][ch+"_low"]["chi2"]/fitResults[str(fill)][ch+"_low"]["ndf"])*fitResults[str(fill)][ch+"_low"]["p0_error"]**2 + (nbx_abort**2)*(fitResults[str(fill)][ch+"_abort"]["chi2"]/fitResults[str(fill)][ch+"_abort"]["ndf"])*fitResults[str(fill)][ch+"_abort"]["p0_error"]**2)/(ntot**2))
            funcs_error[str(fill)][ch+"_inclusive_fit"]["p1_error"]  = sqrt(((nbx_prebeam**2)*(fitResults[str(fill)][ch+"_prebeam"]["chi2"]/fitResults[str(fill)][ch+"_prebeam"]["ndf"])*fitResults[str(fill)][ch+"_prebeam"]["p1_error"]**2 + (nbx_coll**2)*(fitResults[str(fill)][ch+"_high"]["chi2"]/fitResults[str(fill)][ch+"_high"]["ndf"])*fitResults[str(fill)][ch+"_high"]["p1_error"]**2 + (nbx_noncoll**2)*(fitResults[str(fill)][ch+"_low"]["chi2"]/fitResults[str(fill)][ch+"_low"]["ndf"])*fitResults[str(fill)][ch+"_low"]["p1_error"]**2 + (nbx_abort**2)*(fitResults[str(fill)][ch+"_abort"]["chi2"]/fitResults[str(fill)][ch+"_abort"]["ndf"])*fitResults[str(fill)][ch+"_abort"]["p1_error"]**2)/(ntot**2))
            funcs_error[str(fill)][ch+"_inclusive_fit"]["cov_p0p1"]  = ((nbx_prebeam**2)*fitResults[str(fill)][ch+"_prebeam"]["covMatrix"][0][1] + (nbx_coll**2)*fitResults[str(fill)][ch+"_high"]["covMatrix"][0][1] + (nbx_noncoll**2)*fitResults[str(fill)][ch+"_low"]["covMatrix"][0][1] + (nbx_abort**2)*fitResults[str(fill)][ch+"_abort"]["covMatrix"][0][1])/(ntot**2)
            funcs_error[str(fill)][ch+"_inclusive_fit"]["covMatrix"] = [
                                                                                [funcs_error[str(fill)][ch+"_inclusive_fit"]["p0_error"]**2, funcs_error[str(fill)][ch+"_inclusive_fit"]["cov_p0p1"]],
                                                                                [funcs_error[str(fill)][ch+"_inclusive_fit"]["cov_p0p1"], funcs_error[str(fill)][ch+"_inclusive_fit"]["p1_error"]**2]
                                                                            ]
            # delayed bkg #
            # funcs_error[str(fill)][ch+"_delayed_fit"]["p0_error"]    = sqrt(((nbx_prebeam**2)*fitResults[str(fill)][ch+"_prebeam"]["p0_error"]**2 + (nbx_noncoll**2)*fitResults[str(fill)][ch+"_low"]["p0_error"]**2 + (nbx_abort**2)*fitResults[str(fill)][ch+"_abort"]["p0_error"]**2)/(ntot**2))
            # funcs_error[str(fill)][ch+"_delayed_fit"]["p1_error"]    = sqrt(((nbx_prebeam**2)*fitResults[str(fill)][ch+"_prebeam"]["p1_error"]**2 + (nbx_noncoll**2)*fitResults[str(fill)][ch+"_low"]["p1_error"]**2 + (nbx_abort**2)*fitResults[str(fill)][ch+"_abort"]["p1_error"]**2)/(ntot**2))
            funcs_error[str(fill)][ch+"_delayed_fit"]["p0_error"]    = sqrt(((nbx_prebeam**2)*(fitResults[str(fill)][ch+"_prebeam"]["chi2"]/fitResults[str(fill)][ch+"_prebeam"]["ndf"])*fitResults[str(fill)][ch+"_prebeam"]["p0_error"]**2 + (nbx_noncoll**2)*(fitResults[str(fill)][ch+"_low"]["chi2"]/fitResults[str(fill)][ch+"_low"]["ndf"])*fitResults[str(fill)][ch+"_low"]["p0_error"]**2 + (nbx_abort**2)*(fitResults[str(fill)][ch+"_abort"]["chi2"]/fitResults[str(fill)][ch+"_abort"]["ndf"])*fitResults[str(fill)][ch+"_abort"]["p0_error"]**2)/(ntot**2))
            funcs_error[str(fill)][ch+"_delayed_fit"]["p1_error"]    = sqrt(((nbx_prebeam**2)*(fitResults[str(fill)][ch+"_prebeam"]["chi2"]/fitResults[str(fill)][ch+"_prebeam"]["ndf"])*fitResults[str(fill)][ch+"_prebeam"]["p1_error"]**2 + (nbx_noncoll**2)*(fitResults[str(fill)][ch+"_low"]["chi2"]/fitResults[str(fill)][ch+"_low"]["ndf"])*fitResults[str(fill)][ch+"_low"]["p1_error"]**2 + (nbx_abort**2)*(fitResults[str(fill)][ch+"_abort"]["chi2"]/fitResults[str(fill)][ch+"_abort"]["ndf"])*fitResults[str(fill)][ch+"_abort"]["p1_error"]**2)/(ntot**2))
            funcs_error[str(fill)][ch+"_delayed_fit"]["cov_p0p1"]    = ((nbx_prebeam**2)*fitResults[str(fill)][ch+"_prebeam"]["covMatrix"][0][1] + (nbx_noncoll**2)*fitResults[str(fill)][ch+"_low"]["covMatrix"][0][1] + (nbx_abort**2)*fitResults[str(fill)][ch+"_abort"]["covMatrix"][0][1])/(ntot**2)
            funcs_error[str(fill)][ch+"_delayed_fit"]["covMatrix"]   = [
                                                                                [funcs_error[str(fill)][ch+"_delayed_fit"]["p0_error"]**2, funcs_error[str(fill)][ch+"_delayed_fit"]["cov_p0p1"]],
                                                                                [funcs_error[str(fill)][ch+"_delayed_fit"]["cov_p0p1"], funcs_error[str(fill)][ch+"_delayed_fit"]["p1_error"]**2]
                                                                            ]
            # prompt bkg #
            # funcs_error[str(fill)][ch+"_prompt_fit"]["p0_error"]     = sqrt(fitResults[str(fill)][ch+"_high"]["p0_error"]**2 + funcs_error[str(fill)][ch+"_delayed_fit"]["p0_error"]**2)
            # funcs_error[str(fill)][ch+"_prompt_fit"]["p1_error"]     = sqrt(fitResults[str(fill)][ch+"_high"]["p1_error"]**2 + funcs_error[str(fill)][ch+"_delayed_fit"]["p1_error"]**2)
            funcs_error[str(fill)][ch+"_prompt_fit"]["p0_error"]     = sqrt((fitResults[str(fill)][ch+"_high"]["chi2"]/fitResults[str(fill)][ch+"_high"]["ndf"])*(fitResults[str(fill)][ch+"_high"]["p0_error"]**2) + funcs_error[str(fill)][ch+"_delayed_fit"]["p0_error"]**2)
            funcs_error[str(fill)][ch+"_prompt_fit"]["p1_error"]     = sqrt((fitResults[str(fill)][ch+"_high"]["chi2"]/fitResults[str(fill)][ch+"_high"]["ndf"])*(fitResults[str(fill)][ch+"_high"]["p1_error"]**2) + funcs_error[str(fill)][ch+"_delayed_fit"]["p1_error"]**2)
            funcs_error[str(fill)][ch+"_prompt_fit"]["cov_p0p1"]     = fitResults[str(fill)][ch+"_high"]["covMatrix"][0][1] + funcs_error[str(fill)][ch+"_delayed_fit"]["cov_p0p1"]
            funcs_error[str(fill)][ch+"_prompt_fit"]["covMatrix"]    = [
                                                                                [funcs_error[str(fill)][ch+"_prompt_fit"]["p0_error"]**2, funcs_error[str(fill)][ch+"_prompt_fit"]["cov_p0p1"]],
                                                                                [funcs_error[str(fill)][ch+"_prompt_fit"]["cov_p0p1"], funcs_error[str(fill)][ch+"_prompt_fit"]["p1_error"]**2]
                                                                            ]


        for i,ch in enumerate(chambers):
            func = funcs[str(fill)][ch+"_"+bkg+"_fit"]
            # graphics options
            if fill==8754:
                func.SetLineStyle(ROOT.kDashed)
                # when = "Before NFS"
                when = "2023"
            elif fill==9573:
                # when = "After NFS"
                when = "2024"
                func.SetLineStyle(ROOT.kSolid)
            else:
                when = fill
                func.SetLineStyle(ROOT.kDotted)
            func.SetLineWidth(1)
            func.SetLineColor(2*(i+1))
            if i==0:
                func.Draw("SAME")
            else:
                func.Draw("SAME")
            # leg.AddEntry(func, f'{ch.replace("_"," ").replace("p","+").replace("m","-")}: y={round(func.GetParameter(1),2)}x+{round(func.GetParameter(0),2)}', "l")
            # leg.AddEntry(func, f'{ch.replace("_"," ").replace("p","+").replace("m","-")} fill={fill}', "l") # for RPC2024_approval
            # leg.AddEntry(func, ch.replace("_"," ").replace("p","+").replace("m","-")+" "+bkg, "l")
            leg.AddEntry(func, f'{ch.replace("_"," ").replace("p","+").replace("m","-")} {when}', "l")


            Band[str(fill)]             = {}
            func                        = funcs[str(fill)][ch+"_"+bkg+"_fit"]
            # ERROR BANDS for background and per each ch #
            XCenters = range(9, 21)
            YCenters = [funcs[str(fill)][ch+f"_{bkg}_fit"].Eval(x) for x in XCenters]
            XErrors  = [0 for x in XCenters]
            YErrors  = [sqrt(abs((x**2)*funcs_error[str(fill)][ch+f"_{bkg}_fit"]["p1_error"]**2 + funcs_error[str(fill)][ch+f"_{bkg}_fit"]["p0_error"]**2 + 2*x*funcs_error[str(fill)][ch+f"_{bkg}_fit"]["cov_p0p1"])) for x in XCenters]
            
            Band[str(fill)][ch+f"{bkg}_fit"] = ROOT.TGraphErrors(len(XCenters), array.array('f', XCenters), array.array('f', YCenters), array.array('f', XErrors), array.array('f', YErrors))
            Band[str(fill)][ch+f"{bkg}_fit"].SetFillColor(graphicsOptions[bkg]["color"])
            Band[str(fill)][ch+f"{bkg}_fit"].SetFillStyle(3001)
            # Band[str(fill)][ch+f"{bkg}_fit"].SetLineColorAlpha(graphicsOptions[bkg]["color"], 0.3)
            # Band[str(fill)][ch+f"{bkg}_fit"].SetMarkerColorAlpha(graphicsOptions[bkg]["color"], 0.3)
            Band[str(fill)][ch+f"{bkg}_fit"].SetTitle("")
            Band[str(fill)][ch+f"{bkg}_fit"].GetXaxis().SetTitle("")
            Band[str(fill)][ch+f"{bkg}_fit"].GetYaxis().SetTitle("")
            # Band[str(fill)][ch+f"{bkg}_fit"].GetYaxis().SetRangeUser(0,350)
            # Band[str(fill)][ch+f"{bkg}_fit"].SetMinimum(0.)
            # Band[str(fill)][ch+f"{bkg}_fit"].SetMaximum(2*a)
            # Band[str(fill)][ch+f"{bkg}_fit"].Draw("A3 SAME")
            Band[str(fill)][ch+f"{bkg}_fit"].Draw("P3 SAME")

    leg.Draw("SAME")
    # pad1.cd()
    writeExtraText          = 1
    # extraText               = "Work in progress"
    extraText               = "Preliminary"
    lepText                 = ""
    # lumi_sqrtS              = "%s fb^{-1}  (13.6 TeV)"%(round(lumi,3))
    lumi_sqrtS              = "(13.6 TeV)"
    iPeriod                 = 0
    iPos                    = 0
    CMS_lumi(pad1, lumi_sqrtS, iPos, writeExtraText, extraText, lepText) # CMS_lumi(pad, lumi_sqrtS, iPosX, writeExtraText, extraText, lepText), lepText is usually a region
    # pad1.Draw()
    pad1.Update()


    c.cd()
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
    for i,ch in enumerate(chambers):
        X           = []
        Y           = []
        X_err       = []
        Y_err       = []
        for x in range(9, 21):
            X.append(x)
            y_9573  = funcs["9573"][ch+f"_{bkg}_fit"].Eval(x)
            y_8754  = funcs["8754"][ch+f"_{bkg}_fit"].Eval(x)
            y       = y_9573/y_8754
            Y.append(y)
            X_err.append(0)
            y_err_9573 = ((x**2)*funcs_error["9573"][ch+f"_{bkg}_fit"]["p1_error"]**2 + funcs_error["9573"][ch+f"_{bkg}_fit"]["p0_error"]**2 + 2*x*funcs_error["9573"][ch+f"_{bkg}_fit"]["cov_p0p1"])/(y_9573**2)
            y_err_8754 = ((x**2)*funcs_error["8754"][ch+f"_{bkg}_fit"]["p1_error"]**2 + funcs_error["8754"][ch+f"_{bkg}_fit"]["p0_error"]**2 + 2*x*funcs_error["8754"][ch+f"_{bkg}_fit"]["cov_p0p1"])/(y_8754**2)
            y_err   = y*sqrt(y_err_9573 + y_err_8754)
            # y_err   = 0
            Y_err.append(y_err)



        print(f"X:      {X}")
        print(f"Y:      {Y}")
        print(f"X_err:  {X_err}")
        print(f"Y_err:  {Y_err}")
        hist_ratio[ch] = ROOT.TGraphErrors(len(X), array.array('d', X), array.array('d', Y), array.array('d', X_err), array.array('d', Y_err))

        hist_ratio[ch].SetMinimum(0.7)
        hist_ratio[ch].SetMaximum(1.3)
        hist_ratio[ch].GetXaxis().SetLimits(0, 25)

        hist_ratio[ch].SetTitle("")

        hist_ratio[ch].GetXaxis().SetTitle("Instantaneous Luminosity (10^{33} cm^{-2} s^{-1})")
        hist_ratio[ch].GetXaxis().SetTitleSize(0.1)
        hist_ratio[ch].GetXaxis().SetLabelSize(0.1)

        hist_ratio[ch].GetYaxis().SetTitle("After NFS / Before NFS") # "9573 / 8754"
        hist_ratio[ch].GetYaxis().SetTitleOffset(0.3)
        hist_ratio[ch].GetYaxis().CenterTitle(True)
        hist_ratio[ch].GetYaxis().SetLabelSize(0.05)
        hist_ratio[ch].GetYaxis().SetTitleSize(0.075)
        # hist_ratio[ch].SetNdivisions(503, "Y")  # Reduce number of ticks on y-axis
        hist_ratio[ch].SetLineColor(funcs["9573"][ch+f"_{bkg}_fit"].GetLineColor())
        hist_ratio[ch].SetMarkerColor(funcs["9573"][ch+f"_{bkg}_fit"].GetLineColor())
        hist_ratio[ch].SetMarkerStyle(ROOT.kFullCircle)
        hist_ratio[ch].SetMarkerSize(0.5)

    for i,ch in enumerate(hist_ratio):
        h_ratio = hist_ratio[ch]
        if i==0:
            h_ratio.Draw("AP")
            line1 = ROOT.TLine(0, 1, 25, 1)  # (x1, y1, x2, y2)
            line1.SetLineColor(ROOT.kGray)
            line1.SetLineWidth(1)
            line1.SetLineStyle(ROOT.kDashed)
            line1.Draw("SAME")
        else:
            h_ratio.Draw("PSAME")

    pad2.Update()

    c.cd()
    c.RedrawAxis()
    pad2.RedrawAxis()
    # Save the plot
    if printPlots:
        c.SaveAs(outDir_png+"/HitRateVsLumi_["+','.join(chambers)+"]_"+bkg+".png")
        c.SaveAs(outDir_pdf+"/HitRateVsLumi_["+','.join(chambers)+"]_"+bkg+".pdf")
        c.SaveAs(outDir_C+"/HitRateVsLumi_["+','.join(chambers)+"]_"+bkg+".C")








if False:
    ##### ETA PLOTS #####
    # for disk in endcap_disks:
    disk        = "RE4"
    disk_number = int(disk[-1])
    chambers    = [f"REm{disk_number}{ring}_{part}" for ring in [2,3] for part in ["F","M","B"]] # negative endcap
    chambers   += [f"REp{disk_number}{ring}_{part}" for ring in [3,2] for part in ["B","M","F"]] # positive endcap
    print(chambers)

    # Create the canvas
    ROOT.gStyle.SetOptStat(0)
    c = ROOT.TCanvas("c","c",900,700)
    c.SetFillColor(0)
    c.SetBorderMode(0)
    c.SetFrameFillStyle(0)
    c.SetFrameBorderMode(0)
    c.SetLeftMargin(0.12)
    c.SetRightMargin(0.9)
    c.SetTopMargin(1)
    c.SetBottomMargin(-1)
    c.SetTickx(1)
    c.SetTicky(1)
    c.Draw()


    pad1= ROOT.TPad("pad1", "pad1", 0, 0.31 , 1, 1)
    pad1.SetTopMargin(0.1)
    pad1.SetBottomMargin(0.02)
    pad1.SetLeftMargin(0.12)
    pad1.SetRightMargin(0.05)
    pad1.SetBorderMode(0)
    pad1.SetTickx(1)
    pad1.SetTicky(1)
    pad1.SetGrid()
    pad1.Draw()
    pad1.cd()



    # Create the legend
    if legPos=="ur":
        leg = ROOT.TLegend(0.7, 0.7, 0.89, 0.89) # up-right corner
    elif legPos=="ul":
        leg = ROOT.TLegend(0.15, 0.7, 0.4, 0.89) # up-left corner
    elif legPos=="dr":
        leg = ROOT.TLegend(0.7, 0.11, 0.89, 0.3) # down-right corner
    elif legPos=="dl":
        leg = ROOT.TLegend(0.11, 0.11, 0.45, 0.35) # down-left corner
    leg.SetTextFont(42)
    leg.SetTextSize(0.035)


    # definition of the types of background
    bkgs    = ["inclusive", "delayed", "prompt"]
    graphs  = {}
    for fill in fills:
        print(f"Processing fill {fill}\n")
        graphs[str(fill)]  = {bkg: ROOT.TGraph() for bkg in bkgs}
        for chamber in chambers:
            ch,part = chamber.split("_")
            minX    = histos[str(fill)][ch+"_prebeam_fit"].GetMinimumX()
            maxX    = histos[str(fill)][ch+"_prebeam_fit"].GetMaximumX()
            
            funcs[str(fill)][ch+"_inclusive_fit"] = ROOT.TF1(ch+"_inclusive_fit", "pol1", minX, maxX)
            funcs[str(fill)][ch+"_delayed_fit"]   = ROOT.TF1(ch+"_delayed_fit", "pol1", minX, maxX)
            funcs[str(fill)][ch+"_prompt_fit"]    = ROOT.TF1(ch+"_prompt_fit", "pol1", minX, maxX)
            
            funcs[str(fill)][ch+"_inclusive_fit"].SetParameter(0,(nbx_prebeam*histos[str(fill)][ch+"_prebeam_fit"].GetParameter(0) + nbx_coll*histos[str(fill)][ch+"_high_fit"].GetParameter(0) + nbx_noncoll*histos[str(fill)][ch+"_low_fit"].GetParameter(0) + nbx_abort*histos[str(fill)][ch+"_abort_fit"].GetParameter(0))/ntot)
            funcs[str(fill)][ch+"_inclusive_fit"].SetParameter(1,(nbx_prebeam*histos[str(fill)][ch+"_prebeam_fit"].GetParameter(1) + nbx_coll*histos[str(fill)][ch+"_high_fit"].GetParameter(1) + nbx_noncoll*histos[str(fill)][ch+"_low_fit"].GetParameter(1) + nbx_abort*histos[str(fill)][ch+"_abort_fit"].GetParameter(1))/ntot)
            
            funcs[str(fill)][ch+"_delayed_fit"].SetParameter(0,(nbx_prebeam*histos[str(fill)][ch+"_prebeam_fit"].GetParameter(0) + nbx_noncoll*histos[str(fill)][ch+"_low_fit"].GetParameter(0) + nbx_abort*histos[str(fill)][ch+"_abort_fit"].GetParameter(0))/(ntot-nbx_coll))
            funcs[str(fill)][ch+"_delayed_fit"].SetParameter(1,(nbx_prebeam*histos[str(fill)][ch+"_prebeam_fit"].GetParameter(1) + nbx_noncoll*histos[str(fill)][ch+"_low_fit"].GetParameter(1) + nbx_abort*histos[str(fill)][ch+"_abort_fit"].GetParameter(1))/(ntot-nbx_coll))
            
            funcs[str(fill)][ch+"_prompt_fit"].SetParameter(0,histos[str(fill)][ch+"_high_fit"].GetParameter(0) - funcs[str(fill)][ch+"_delayed_fit"].GetParameter(0))    
            funcs[str(fill)][ch+"_prompt_fit"].SetParameter(1,histos[str(fill)][ch+"_high_fit"].GetParameter(1) - funcs[str(fill)][ch+"_delayed_fit"].GetParameter(1))
            
            for bkg in bkgs:
                print(f"Processing ---> {disk} {chamber} for {bkg} background")
                func = funcs[str(fill)][chamber+"_"+bkg+"_fit"]
                graphs[str(fill)][bkg].AddPoint(geometry_dict[ch][part]["eta"], func.Eval(10)) # func.Eval(10) means we are going to fix the Inst.Lumi to 1e34cm^-2s^-1

        
        


        print("Drawing the graphs")
        for i,bkg in enumerate(bkgs):
            # axis options
            graphs[str(fill)][bkg].SetTitle(disk)
            graphs[str(fill)][bkg].GetXaxis().SetTitle("#eta")
            graphs[str(fill)][bkg].GetXaxis().SetLabelSize(0.03)
            graphs[str(fill)][bkg].GetXaxis().SetTitleSize(0.045)
            graphs[str(fill)][bkg].GetYaxis().SetTitle("Hit Rate (Hz/cm^{2})")
            graphs[str(fill)][bkg].GetYaxis().SetLabelSize(0.03)
            graphs[str(fill)][bkg].GetYaxis().SetTitleSize(0.045)
            graphs[str(fill)][bkg].SetMinimum(1e-2)
            # graphs[str(fill)][bkg].SetMaximum(25)
            graphs[str(fill)][bkg].SetMaximum(1e2)
            
            # graphics options
            graphs[str(fill)][bkg].SetLineColor(graphicsOptions[bkg]["color"])
            graphs[str(fill)][bkg].SetMarkerColor(graphicsOptions[bkg]["color"])
            graphs[str(fill)][bkg].SetMarkerStyle(graphicsOptions[bkg]["marker"])
            graphs[str(fill)][bkg].SetMarkerSize(1.25)
            if i==0:
                graphs[str(fill)][bkg].Draw("ap")
            else:
                graphs[str(fill)][bkg].Draw("p")
            leg.AddEntry(graphs[str(fill)][bkg], bkg.replace("inclusive","Inclusive Bkg").replace("delayed","Delayed Bkg").replace("prompt","Prompt Bkg"), "p")

    leg.Draw("SAME")
    # pad1.cd()
    writeExtraText          = 1
    # extraText               = "Work in progress"
    extraText               = "Preliminary"
    lepText                 = ""
    # lumi_sqrtS              = "%s fb^{-1}  (13.6 TeV)"%(round(lumi,3))
    lumi_sqrtS              = "(13.6 TeV)"
    iPeriod                 = 0
    iPos                    = 0
    CMS_lumi(pad1, lumi_sqrtS, iPos, writeExtraText, extraText, lepText) # CMS_lumi(pad, lumi_sqrtS, iPosX, writeExtraText, extraText, lepText), lepText is usually a region
    # pad1.Draw()
    pad1.Update()


    c.cd()
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


    c.cd()
    # Save the plot
    if printPlots:
        c.SaveAs(outDir_png+"/HitRateVsEta_"+disk+"_bkgs.png")
        c.SaveAs(outDir_pdf+"/HitRateVsEta_"+disk+"_bkgs.pdf")
        c.SaveAs(outDir_C+"/HitRateVsEta_"+disk+"_bkgs.C")






#########################################
#### single chamber, 2 fills, 3 bkgs ####
#########################################
onlystat_err                    = False # True if only statistical errors are considered, False if statistical+systematic errors are considered
fitParameters                   = {} # dictionary to store the fit parameters
for fill in fills:
    fitParameters[str(fill)]    = {}

for chamber in chambers:
    # Create the canvas
    ROOT.gStyle.SetOptStat(0)
    c = ROOT.TCanvas("c","c",900,700)
    c.SetFillColor(0)
    c.SetBorderMode(0)
    c.SetFrameFillStyle(0)
    c.SetFrameBorderMode(0)
    c.SetLeftMargin(0.12)
    c.SetRightMargin(0.9)
    c.SetTopMargin(1)
    c.SetBottomMargin(-1)
    c.SetTickx(1)
    c.SetTicky(1)
    c.Draw()


    pad1= ROOT.TPad("pad1", "pad1", 0, 0.31, 1, 1)
    pad1.SetTopMargin(0.1)
    pad1.SetBottomMargin(0.015) # 0.02
    pad1.SetLeftMargin(0.12)
    pad1.SetRightMargin(0.05)
    pad1.SetBorderMode(0)
    pad1.SetTickx(1)
    pad1.SetTicky(1)
    pad1.SetGrid()
    pad1.Draw()
    pad1.cd()



    # Create the legend
    if legPos=="ur":
        leg = ROOT.TLegend(0.7, 0.7, 0.89, 0.89) # up-right corner
    elif legPos=="ul":
        # leg = ROOT.TLegend(0.15, 0.6, 0.4, 0.89) # up-left corner
        leg = ROOT.TLegend(0.15, 0.6, 0.35, 0.89) # up-left corner
    elif legPos=="dr":
        leg = ROOT.TLegend(0.7, 0.11, 0.89, 0.3) # down-right corner
    elif legPos=="dl":
        leg = ROOT.TLegend(0.11, 0.11, 0.45, 0.35) # down-left corner
    leg.SetTextFont(42)
    leg.SetTextSize(0.035)
    leg.AddEntry("None", chamber.replace("_"," ").replace("p","+").replace("m","-")[:4]+"/"+chamber.replace("_"," ").replace("p","+").replace("m","-")[4:], "")



    # definition of the types of background
    bkgs        = ["inclusive", "delayed", "prompt"]
    funcs       = {}
    funcs_error = {}
    for fill in fills:
        if fill==8754:
            lumi                    = 440.273 + 175.600 + 27.104                        # pb-1, Runs: 367413 + 367406 + 367415 
            colliding_scheme_txt    = "../fill_schemes/Fill_8754/colliding_8754.txt"    # Fill=8754
        elif fill==9573:
            lumi                    = 635.347                                           # pb-1, Runs: 380115
            colliding_scheme_txt    = "../fill_schemes/Fill_9573/colliding_9573.txt"    # Fill=9573

        ntot                 = 3564
        bxIDs, bxID_coll, bxID_prebeam, bxID_abort, bxID_noncoll = bunches_scheme(colliding_scheme_txt, ntot)
        nbx_prebeam          = len(bxID_prebeam)
        nbx_coll             = len(bxID_coll)
        nbx_noncoll          = len(bxID_noncoll)
        nbx_abort            = len(bxID_abort)



        funcs[str(fill)]    = {}
        print(f"Processing fill {fill}\n")
        minX    = histos[str(fill)][chamber+"_prebeam_fit"].GetMinimumX()
        maxX    = histos[str(fill)][chamber+"_prebeam_fit"].GetMaximumX()
        
        funcs[str(fill)][chamber+"_inclusive_fit"] = ROOT.TF1(chamber+"_inclusive_fit", "pol1", minX, maxX)
        funcs[str(fill)][chamber+"_delayed_fit"]   = ROOT.TF1(chamber+"_delayed_fit", "pol1", minX, maxX)
        funcs[str(fill)][chamber+"_prompt_fit"]    = ROOT.TF1(chamber+"_prompt_fit", "pol1", minX, maxX)

        # inclusive bkg #
        funcs[str(fill)][chamber+"_inclusive_fit"].SetParameter(0,(nbx_prebeam*histos[str(fill)][chamber+"_prebeam_fit"].GetParameter(0) + nbx_coll*histos[str(fill)][chamber+"_high_fit"].GetParameter(0) + nbx_noncoll*histos[str(fill)][chamber+"_low_fit"].GetParameter(0) + nbx_abort*histos[str(fill)][chamber+"_abort_fit"].GetParameter(0))/ntot)
        funcs[str(fill)][chamber+"_inclusive_fit"].SetParameter(1,(nbx_prebeam*histos[str(fill)][chamber+"_prebeam_fit"].GetParameter(1) + nbx_coll*histos[str(fill)][chamber+"_high_fit"].GetParameter(1) + nbx_noncoll*histos[str(fill)][chamber+"_low_fit"].GetParameter(1) + nbx_abort*histos[str(fill)][chamber+"_abort_fit"].GetParameter(1))/ntot)
        # funcs[str(fill)][chamber+"_inclusive_fit"].SetParError(0,(nbx_prebeam*histos[str(fill)][chamber+"_prebeam_fit"].GetParError(0) + nbx_coll*histos[str(fill)][chamber+"_high_fit"].GetParError(0) + nbx_noncoll*histos[str(fill)][chamber+"_low_fit"].GetParError(0) + nbx_abort*histos[str(fill)][chamber+"_abort_fit"].GetParError(0))/ntot)
        # funcs[str(fill)][chamber+"_inclusive_fit"].SetParError(1,(nbx_prebeam*histos[str(fill)][chamber+"_prebeam_fit"].GetParError(1) + nbx_coll*histos[str(fill)][chamber+"_high_fit"].GetParError(1) + nbx_noncoll*histos[str(fill)][chamber+"_low_fit"].GetParError(1) + nbx_abort*histos[str(fill)][chamber+"_abort_fit"].GetParError(1))/ntot)
        
        # delayed bkg #
        funcs[str(fill)][chamber+"_delayed_fit"].SetParameter(0,(nbx_prebeam*histos[str(fill)][chamber+"_prebeam_fit"].GetParameter(0) + nbx_noncoll*histos[str(fill)][chamber+"_low_fit"].GetParameter(0) + nbx_abort*histos[str(fill)][chamber+"_abort_fit"].GetParameter(0))/(ntot-nbx_coll))
        funcs[str(fill)][chamber+"_delayed_fit"].SetParameter(1,(nbx_prebeam*histos[str(fill)][chamber+"_prebeam_fit"].GetParameter(1) + nbx_noncoll*histos[str(fill)][chamber+"_low_fit"].GetParameter(1) + nbx_abort*histos[str(fill)][chamber+"_abort_fit"].GetParameter(1))/(ntot-nbx_coll))
        # funcs[str(fill)][chamber+"_delayed_fit"].SetParError(0,(nbx_prebeam*histos[str(fill)][chamber+"_prebeam_fit"].GetParError(0) + nbx_noncoll*histos[str(fill)][chamber+"_low_fit"].GetParError(0) + nbx_abort*histos[str(fill)][chamber+"_abort_fit"].GetParError(0))/(ntot-nbx_coll))
        # funcs[str(fill)][chamber+"_delayed_fit"].SetParError(1,(nbx_prebeam*histos[str(fill)][chamber+"_prebeam_fit"].GetParError(1) + nbx_noncoll*histos[str(fill)][chamber+"_low_fit"].GetParError(1) + nbx_abort*histos[str(fill)][chamber+"_abort_fit"].GetParError(1))/(ntot-nbx_coll))
        
        # prompt bkg #
        funcs[str(fill)][chamber+"_prompt_fit"].SetParameter(0,histos[str(fill)][chamber+"_high_fit"].GetParameter(0) - funcs[str(fill)][chamber+"_delayed_fit"].GetParameter(0))    
        funcs[str(fill)][chamber+"_prompt_fit"].SetParameter(1,histos[str(fill)][chamber+"_high_fit"].GetParameter(1) - funcs[str(fill)][chamber+"_delayed_fit"].GetParameter(1))
        # funcs[str(fill)][chamber+"_prompt_fit"].SetParError(0,histos[str(fill)][chamber+"_high_fit"].GetParError(0) - funcs[str(fill)][chamber+"_delayed_fit"].GetParError(0))
        # funcs[str(fill)][chamber+"_prompt_fit"].SetParError(1,histos[str(fill)][chamber+"_high_fit"].GetParError(1) - funcs[str(fill)][chamber+"_delayed_fit"].GetParError(1))
            

        ####################
        # calculate errors #
        ####################
        funcs_error[str(fill)] = {}
        funcs_error[str(fill)][chamber+"_inclusive_fit"] = {}
        funcs_error[str(fill)][chamber+"_delayed_fit"]   = {}
        funcs_error[str(fill)][chamber+"_prompt_fit"]    = {}

        # inclusive bkg #
        if onlystat_err:
            funcs_error[str(fill)][chamber+"_inclusive_fit"]["p0_error"]  = sqrt(((nbx_prebeam**2)*fitResults[str(fill)][chamber+"_prebeam"]["p0_error"]**2 + (nbx_coll**2)*fitResults[str(fill)][chamber+"_high"]["p0_error"]**2 + (nbx_noncoll**2)*fitResults[str(fill)][chamber+"_low"]["p0_error"]**2 + (nbx_abort**2)*fitResults[str(fill)][chamber+"_abort"]["p0_error"]**2)/(ntot**2))
            funcs_error[str(fill)][chamber+"_inclusive_fit"]["p1_error"]  = sqrt(((nbx_prebeam**2)*fitResults[str(fill)][chamber+"_prebeam"]["p1_error"]**2 + (nbx_coll**2)*fitResults[str(fill)][chamber+"_high"]["p1_error"]**2 + (nbx_noncoll**2)*fitResults[str(fill)][chamber+"_low"]["p1_error"]**2 + (nbx_abort**2)*fitResults[str(fill)][chamber+"_abort"]["p1_error"]**2)/(ntot**2))
        else:
            funcs_error[str(fill)][chamber+"_inclusive_fit"]["p0_error"]  = sqrt(((nbx_prebeam**2)*(fitResults[str(fill)][chamber+"_prebeam"]["chi2"]/fitResults[str(fill)][chamber+"_prebeam"]["ndf"])*fitResults[str(fill)][chamber+"_prebeam"]["p0_error"]**2 + (nbx_coll**2)*(fitResults[str(fill)][chamber+"_high"]["chi2"]/fitResults[str(fill)][chamber+"_high"]["ndf"])*fitResults[str(fill)][chamber+"_high"]["p0_error"]**2 + (nbx_noncoll**2)*(fitResults[str(fill)][chamber+"_low"]["chi2"]/fitResults[str(fill)][chamber+"_low"]["ndf"])*fitResults[str(fill)][chamber+"_low"]["p0_error"]**2 + (nbx_abort**2)*(fitResults[str(fill)][chamber+"_abort"]["chi2"]/fitResults[str(fill)][chamber+"_abort"]["ndf"])*fitResults[str(fill)][chamber+"_abort"]["p0_error"]**2)/(ntot**2))
            funcs_error[str(fill)][chamber+"_inclusive_fit"]["p1_error"]  = sqrt(((nbx_prebeam**2)*(fitResults[str(fill)][chamber+"_prebeam"]["chi2"]/fitResults[str(fill)][chamber+"_prebeam"]["ndf"])*fitResults[str(fill)][chamber+"_prebeam"]["p1_error"]**2 + (nbx_coll**2)*(fitResults[str(fill)][chamber+"_high"]["chi2"]/fitResults[str(fill)][chamber+"_high"]["ndf"])*fitResults[str(fill)][chamber+"_high"]["p1_error"]**2 + (nbx_noncoll**2)*(fitResults[str(fill)][chamber+"_low"]["chi2"]/fitResults[str(fill)][chamber+"_low"]["ndf"])*fitResults[str(fill)][chamber+"_low"]["p1_error"]**2 + (nbx_abort**2)*(fitResults[str(fill)][chamber+"_abort"]["chi2"]/fitResults[str(fill)][chamber+"_abort"]["ndf"])*fitResults[str(fill)][chamber+"_abort"]["p1_error"]**2)/(ntot**2))
        funcs_error[str(fill)][chamber+"_inclusive_fit"]["cov_p0p1"]  = ((nbx_prebeam**2)*fitResults[str(fill)][chamber+"_prebeam"]["covMatrix"][0][1] + (nbx_coll**2)*fitResults[str(fill)][chamber+"_high"]["covMatrix"][0][1] + (nbx_noncoll**2)*fitResults[str(fill)][chamber+"_low"]["covMatrix"][0][1] + (nbx_abort**2)*fitResults[str(fill)][chamber+"_abort"]["covMatrix"][0][1])/(ntot**2)
        funcs_error[str(fill)][chamber+"_inclusive_fit"]["covMatrix"] = [
                                                                            [funcs_error[str(fill)][chamber+"_inclusive_fit"]["p0_error"]**2, funcs_error[str(fill)][chamber+"_inclusive_fit"]["cov_p0p1"]],
                                                                            [funcs_error[str(fill)][chamber+"_inclusive_fit"]["cov_p0p1"], funcs_error[str(fill)][chamber+"_inclusive_fit"]["p1_error"]**2]
                                                                        ]
        # delayed bkg #
        if onlystat_err:
            funcs_error[str(fill)][chamber+"_delayed_fit"]["p0_error"]    = sqrt(((nbx_prebeam**2)*fitResults[str(fill)][chamber+"_prebeam"]["p0_error"]**2 + (nbx_noncoll**2)*fitResults[str(fill)][chamber+"_low"]["p0_error"]**2 + (nbx_abort**2)*fitResults[str(fill)][chamber+"_abort"]["p0_error"]**2)/(ntot**2))
            funcs_error[str(fill)][chamber+"_delayed_fit"]["p1_error"]    = sqrt(((nbx_prebeam**2)*fitResults[str(fill)][chamber+"_prebeam"]["p1_error"]**2 + (nbx_noncoll**2)*fitResults[str(fill)][chamber+"_low"]["p1_error"]**2 + (nbx_abort**2)*fitResults[str(fill)][chamber+"_abort"]["p1_error"]**2)/(ntot**2))
        else:
            funcs_error[str(fill)][chamber+"_delayed_fit"]["p0_error"]    = sqrt(((nbx_prebeam**2)*(fitResults[str(fill)][chamber+"_prebeam"]["chi2"]/fitResults[str(fill)][chamber+"_prebeam"]["ndf"])*fitResults[str(fill)][chamber+"_prebeam"]["p0_error"]**2 + (nbx_noncoll**2)*(fitResults[str(fill)][chamber+"_low"]["chi2"]/fitResults[str(fill)][chamber+"_low"]["ndf"])*fitResults[str(fill)][chamber+"_low"]["p0_error"]**2 + (nbx_abort**2)*(fitResults[str(fill)][chamber+"_abort"]["chi2"]/fitResults[str(fill)][chamber+"_abort"]["ndf"])*fitResults[str(fill)][chamber+"_abort"]["p0_error"]**2)/(ntot**2))
            funcs_error[str(fill)][chamber+"_delayed_fit"]["p1_error"]    = sqrt(((nbx_prebeam**2)*(fitResults[str(fill)][chamber+"_prebeam"]["chi2"]/fitResults[str(fill)][chamber+"_prebeam"]["ndf"])*fitResults[str(fill)][chamber+"_prebeam"]["p1_error"]**2 + (nbx_noncoll**2)*(fitResults[str(fill)][chamber+"_low"]["chi2"]/fitResults[str(fill)][chamber+"_low"]["ndf"])*fitResults[str(fill)][chamber+"_low"]["p1_error"]**2 + (nbx_abort**2)*(fitResults[str(fill)][chamber+"_abort"]["chi2"]/fitResults[str(fill)][chamber+"_abort"]["ndf"])*fitResults[str(fill)][chamber+"_abort"]["p1_error"]**2)/(ntot**2))
        funcs_error[str(fill)][chamber+"_delayed_fit"]["cov_p0p1"]    = ((nbx_prebeam**2)*fitResults[str(fill)][chamber+"_prebeam"]["covMatrix"][0][1] + (nbx_noncoll**2)*fitResults[str(fill)][chamber+"_low"]["covMatrix"][0][1] + (nbx_abort**2)*fitResults[str(fill)][chamber+"_abort"]["covMatrix"][0][1])/(ntot**2)
        funcs_error[str(fill)][chamber+"_delayed_fit"]["covMatrix"]   = [
                                                                            [funcs_error[str(fill)][chamber+"_delayed_fit"]["p0_error"]**2, funcs_error[str(fill)][chamber+"_delayed_fit"]["cov_p0p1"]],
                                                                            [funcs_error[str(fill)][chamber+"_delayed_fit"]["cov_p0p1"], funcs_error[str(fill)][chamber+"_delayed_fit"]["p1_error"]**2]
                                                                        ]
        # prompt bkg #
        if onlystat_err:
            funcs_error[str(fill)][chamber+"_prompt_fit"]["p0_error"]     = sqrt(fitResults[str(fill)][chamber+"_high"]["p0_error"]**2 + funcs_error[str(fill)][chamber+"_delayed_fit"]["p0_error"]**2)
            funcs_error[str(fill)][chamber+"_prompt_fit"]["p1_error"]     = sqrt(fitResults[str(fill)][chamber+"_high"]["p1_error"]**2 + funcs_error[str(fill)][chamber+"_delayed_fit"]["p1_error"]**2)
        else:
            funcs_error[str(fill)][chamber+"_prompt_fit"]["p0_error"]     = sqrt((fitResults[str(fill)][chamber+"_high"]["chi2"]/fitResults[str(fill)][chamber+"_high"]["ndf"])*(fitResults[str(fill)][chamber+"_high"]["p0_error"]**2) + funcs_error[str(fill)][chamber+"_delayed_fit"]["p0_error"]**2)
            funcs_error[str(fill)][chamber+"_prompt_fit"]["p1_error"]     = sqrt((fitResults[str(fill)][chamber+"_high"]["chi2"]/fitResults[str(fill)][chamber+"_high"]["ndf"])*(fitResults[str(fill)][chamber+"_high"]["p1_error"]**2) + funcs_error[str(fill)][chamber+"_delayed_fit"]["p1_error"]**2)
        funcs_error[str(fill)][chamber+"_prompt_fit"]["cov_p0p1"]     = fitResults[str(fill)][chamber+"_high"]["covMatrix"][0][1] + funcs_error[str(fill)][chamber+"_delayed_fit"]["cov_p0p1"]
        funcs_error[str(fill)][chamber+"_prompt_fit"]["covMatrix"]    = [
                                                                            [funcs_error[str(fill)][chamber+"_prompt_fit"]["p0_error"]**2, funcs_error[str(fill)][chamber+"_prompt_fit"]["cov_p0p1"]],
                                                                            [funcs_error[str(fill)][chamber+"_prompt_fit"]["cov_p0p1"], funcs_error[str(fill)][chamber+"_prompt_fit"]["p1_error"]**2]
                                                                        ]

        



    hist = ROOT.TH1F(chamber+"_bkgs_fit", chamber.replace("_"," ").replace("p","+").replace("m","-"), 100, 0, 25)
    hist.SetTitleSize(1)
    # axis options
    hist.GetXaxis().SetTitle("Instantaneous Luminosity (10^{33} cm^{-2} s^{-1})")
    hist.GetXaxis().SetLabelSize(0) # 0.04
    hist.GetXaxis().SetTitleSize(0.045)
    hist.GetYaxis().SetTitle("Hit Rate (Hz/cm^{2})")
    hist.GetYaxis().SetLabelSize(0.04)
    hist.GetYaxis().SetTitleSize(0.045)
    hist.SetTitle("") # for RPC2024_approval
    # hist.SetMinimum(0)
    # hist.SetMinimum(-1) #todelete
    if "RE" in chamber:
        hist.SetMaximum(25)
        # hist.SetTitle(hist.GetTitle()[:4]+"/"+hist.GetTitle()[4:])
    elif "W" in chamber:
        hist.SetMaximum(15)
    # hist.SetMaximum(funcs[chamber+"_inclusive_fit"].GetMaximum()*2.0)
    hist.Draw()

    Band                            = {} # dictionary error bands for backgrounds
    for fill in fills:
        Band[str(fill)]             = {}
        for i,bkg in enumerate(bkgs):
            func                    = funcs[str(fill)][chamber+"_"+bkg+"_fit"]
            # update output json with the fit parameters #
            fitParameters[str(fill)][chamber+"_"+bkg+"_fit"]                = {}
            fitParameters[str(fill)][chamber+"_"+bkg+"_fit"]["p0"]          = func.GetParameter(0)
            fitParameters[str(fill)][chamber+"_"+bkg+"_fit"]["p1"]          = func.GetParameter(1)
            fitParameters[str(fill)][chamber+"_"+bkg+"_fit"]["p0_error"]    = funcs_error[str(fill)][chamber+"_"+bkg+"_fit"]["p0_error"]
            fitParameters[str(fill)][chamber+"_"+bkg+"_fit"]["p1_error"]    = funcs_error[str(fill)][chamber+"_"+bkg+"_fit"]["p1_error"]
            fitParameters[str(fill)][chamber+"_"+bkg+"_fit"]["cov_p0p1"]    = funcs_error[str(fill)][chamber+"_"+bkg+"_fit"]["cov_p0p1"]
            fitParameters[str(fill)][chamber+"_"+bkg+"_fit"]["covMatrix"]   = funcs_error[str(fill)][chamber+"_"+bkg+"_fit"]["covMatrix"]

            # graphics options
            if fill==8754:
                func.SetLineStyle(ROOT.kDashed)
                # when = "Before NFS"
                when = "2023"
            elif fill==9573:
                # when = "After NFS"
                when = "2024"
                func.SetLineStyle(ROOT.kSolid)
            else:
                when = fill
                func.SetLineStyle(ROOT.kDotted)
            func.SetLineColor(graphicsOptions[bkg]["color"])
            func.SetLineWidth(1)

            if i==0:
                func.Draw("SAME")
            else:
                func.Draw("SAME")
            # leg.AddEntry(func, chamber.replace("_"," ").replace("p","+").replace("m","-")+" "+bkg, "l")
            leg.AddEntry(func, bkg.replace("inclusive",f"Inclusive {when}").replace("delayed",f"Delayed {when}").replace("prompt",f"Prompt {when}"), "l")


            # ERROR BANDS for backgrounds #
            XCenters = range(9, 21)
            YCenters = [funcs[str(fill)][chamber+f"_{bkg}_fit"].Eval(x) for x in XCenters]
            XErrors  = [0 for x in XCenters]
            YErrors  = [sqrt(abs((x**2)*funcs_error[str(fill)][chamber+f"_{bkg}_fit"]["p1_error"]**2 + funcs_error[str(fill)][chamber+f"_{bkg}_fit"]["p0_error"]**2 + 2*x*funcs_error[str(fill)][chamber+f"_{bkg}_fit"]["cov_p0p1"])) for x in XCenters]
            
            Band[str(fill)][chamber+f"{bkg}_fit"] = ROOT.TGraphErrors(len(XCenters), array.array('f', XCenters), array.array('f', YCenters), array.array('f', XErrors), array.array('f', YErrors))
            if fill==8754:
                Band[str(fill)][chamber+f"{bkg}_fit"].SetFillStyle(3003)
                Band[str(fill)][chamber+f"{bkg}_fit"].SetFillColorAlpha(graphicsOptions[bkg]["color"], 1)
            elif fill==9573:
                Band[str(fill)][chamber+f"{bkg}_fit"].SetFillStyle(1001)
                Band[str(fill)][chamber+f"{bkg}_fit"].SetFillColorAlpha(graphicsOptions[bkg]["color"], 0.1)
            # Band[str(fill)][chamber+f"{bkg}_fit"].SetLineColorAlpha(graphicsOptions[bkg]["color"], 0.3)
            # Band[str(fill)][chamber+f"{bkg}_fit"].SetMarkerColorAlpha(graphicsOptions[bkg]["color"], 0.3)
            Band[str(fill)][chamber+f"{bkg}_fit"].SetTitle("")
            Band[str(fill)][chamber+f"{bkg}_fit"].GetXaxis().SetTitle("")
            Band[str(fill)][chamber+f"{bkg}_fit"].GetYaxis().SetTitle("")
            # Band[str(fill)][chamber+f"{bkg}_fit"].GetYaxis().SetRangeUser(0,350)
            # Band[str(fill)][chamber+f"{bkg}_fit"].SetMinimum(0.)
            # Band[str(fill)][chamber+f"{bkg}_fit"].SetMaximum(2*a)
            # Band[str(fill)][chamber+f"{bkg}_fit"].Draw("A3 SAME")
            Band[str(fill)][chamber+f"{bkg}_fit"].Draw("e3 SAME")

        
    leg.Draw("SAME")
    # pad1.cd()
    writeExtraText          = 1
    # extraText               = "Work in progress"
    extraText               = "Preliminary"
    lepText                 = ""
    # lumi_sqrtS              = "%s fb^{-1}  (13.6 TeV)"%(round(lumi,3))
    # lumi_sqrtS              = chamber.replace("_"," ").replace("p","+").replace("m","-")[:4]+"/"+chamber.replace("_"," ").replace("p","+").replace("m","-")[4:] + ", " + "(13.6 TeV)"
    lumi_sqrtS              = "Run 3 (13.6 TeV)"
    iPeriod                 = 0
    iPos                    = 0
    CMS_lumi(pad1, lumi_sqrtS, iPos, writeExtraText, extraText, lepText) # CMS_lumi(pad, lumi_sqrtS, iPosX, writeExtraText, extraText, lepText), lepText is usually a region
    # pad1.Draw()
    pad1.Update()


    c.cd()
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
        X           = []
        Y           = []
        X_err       = []
        Y_err       = []
        for x in range(9, 21):
            X.append(x)
            y_9573  = funcs["9573"][chamber+f"_{bkg}_fit"].Eval(x)
            y_8754  = funcs["8754"][chamber+f"_{bkg}_fit"].Eval(x)
            y       = y_9573/y_8754
            Y.append(y)
            X_err.append(0)
            y_err_9573 = ((x**2)*funcs_error["9573"][chamber+f"_{bkg}_fit"]["p1_error"]**2 + funcs_error["9573"][chamber+f"_{bkg}_fit"]["p0_error"]**2 + 2*x*funcs_error["9573"][chamber+f"_{bkg}_fit"]["cov_p0p1"])/(y_9573**2)
            y_err_8754 = ((x**2)*funcs_error["8754"][chamber+f"_{bkg}_fit"]["p1_error"]**2 + funcs_error["8754"][chamber+f"_{bkg}_fit"]["p0_error"]**2 + 2*x*funcs_error["8754"][chamber+f"_{bkg}_fit"]["cov_p0p1"])/(y_8754**2)
            y_err      = y*sqrt(abs(y_err_9573 + y_err_8754))
            # y_err   = 0
            Y_err.append(y_err)



        print(f"X:      {X}")
        print(f"Y:      {Y}")
        print(f"X_err:  {X_err}")
        print(f"Y_err:  {Y_err}")
        hist_ratio[bkg] = ROOT.TGraphErrors(len(X), array.array('d', X), array.array('d', Y), array.array('d', X_err), array.array('d', Y_err))

        hist_ratio[bkg].SetMinimum(0.7)
        hist_ratio[bkg].SetMaximum(1.3)
        # hist_ratio[bkg].SetMinimum(hist_ratio[bkg].GetHistogram().GetMinimum()*0.9)
        # hist_ratio[bkg].SetMaximum(hist_ratio[bkg].GetHistogram().GetMaximum()*1.1)
        hist_ratio[bkg].GetXaxis().SetLimits(0, 25)

        hist_ratio[bkg].SetTitle("")

        hist_ratio[bkg].GetXaxis().SetTitle("Instantaneous Luminosity (10^{33} cm^{-2} s^{-1})")
        hist_ratio[bkg].GetXaxis().SetTitleSize(0.1)
        hist_ratio[bkg].GetXaxis().SetLabelSize(0.1)

        # hist_ratio[bkg].GetYaxis().SetTitle("After NFS / Before NFS") # "9573 / 8754"
        hist_ratio[bkg].GetYaxis().SetTitle("2024 Data / 2023 Data")
        hist_ratio[bkg].GetYaxis().SetTitleOffset(0.3)
        hist_ratio[bkg].GetYaxis().CenterTitle(True)
        hist_ratio[bkg].GetYaxis().SetLabelSize(0.05)
        hist_ratio[bkg].GetYaxis().SetTitleSize(0.075)
        # hist_ratio[bkg].SetNdivisions(503, "Y")  # Reduce number of ticks on y-axis
        hist_ratio[bkg].SetLineColor(funcs["9573"][chamber+f"_{bkg}_fit"].GetLineColor())
        hist_ratio[bkg].SetMarkerColor(funcs["9573"][chamber+f"_{bkg}_fit"].GetLineColor())
        hist_ratio[bkg].SetMarkerStyle(ROOT.kFullCircle)
        hist_ratio[bkg].SetMarkerSize(0.5)
        hist_ratio[bkg].SetFillColorAlpha(funcs["9573"][chamber+f"_{bkg}_fit"].GetLineColor(), 0.3)

    for i,bkg in enumerate(hist_ratio):
        h_ratio = hist_ratio[bkg]
        if i==0:
            h_ratio.Draw("Al3")
            line1 = ROOT.TLine(0, 1, 25, 1)  # (x1, y1, x2, y2)
            line1.SetLineColor(ROOT.kBlack)
            line1.SetLineWidth(1)
            line1.SetLineStyle(ROOT.kSolid)
            line1.Draw("SAME")
        else:
            h_ratio.Draw("le3SAME")

    pad2.Update()

    c.cd()
    c.RedrawAxis()
    pad2.RedrawAxis()
    # Save the plot
    if printPlots:
        c.SaveAs(outDir_png+"/HitRateVsLumi_"+chamber+"_bkgs_Ratio_syst_APPROVED.png")
        c.SaveAs(outDir_pdf+"/HitRateVsLumi_"+chamber+"_bkgs_Ratio_syst_APPROVED.pdf")
        c.SaveAs(outDir_C+"/HitRateVsLumi_"+chamber+"_bkgs_Ratio_syst_APPROVED.C")


print(fitParameters.keys())
print(fitParameters["9573"].keys())

with open(outJson, 'w') as f:
    json.dump(fitParameters, f, indent=4)
    print(f"Fit parameters saved in {outJson}")
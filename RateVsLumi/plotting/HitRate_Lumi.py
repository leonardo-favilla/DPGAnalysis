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

usage       = 'python3 HitRate_Lumi.py -i <input root file>'
example     = 'python3 HitRate_Lumi.py -i /eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_9573/RPC_fit_F9573.root -c Wm2_RB1in -d /eos/user/l/lfavilla/RPC/plots/RPC_fit_F9573 -p'
parser      = argparse.ArgumentParser(usage)
parser.add_argument('-i', '--inFile',     dest = 'inFile',    required = True,                                type = str,                             help = 'input root file (should be the output of RPCFitter.py)')
parser.add_argument('-f', '--fill',       dest = 'fill',      required = True,                                type = int,                             help = 'specify the fill number')
parser.add_argument('-c', '--chambers',   dest = 'chambers',  required = False,   default = 'Wm2_RB1in',      type = str,                             help = 'specify the chambers to be plotted - default Wm2_RB1in')
parser.add_argument('-d', '--outDir',     dest = 'outDir',    required = False,   default = './',             type = str,                             help = 'output directory for the plots - default is the current directory')
parser.add_argument('-p', '--print',      dest = 'print',     required = False,   default = False,                            action = 'store_true',  help = 'save the plots in png/pdf format')

args                = parser.parse_args()
inFile              = args.inFile
fill                = args.fill
chambers            = args.chambers.split(',')
outDir              = args.outDir
# outFile             = ROOT.TFile(f"{outDir}/HitRateVsLumi.root", "RECREATE")
printPlots          = args.print
regions             = ["high", "low", "prebeam", "abort"]

mean_cluster_size          = {}
if fill==8754:
    mean_cluster_size["REp42"] = 1.5 # 1.6 for Fill 9573, 1.5 for Fill 8754
    mean_cluster_size["REp43"] = 1.5 # 1.6 for Fill 9573, 1.5 for Fill 8754
    mean_cluster_size["REm42"] = 1.5 # 1.6 for Fill 9573, 1.5 for Fill 8754
    mean_cluster_size["REm43"] = 1.5 # 1.6 for Fill 9573, 1.5 for Fill 8754
    mean_cluster_size["REp32"] = 1.8 # 1.8 for Fill 9573, 1.8 for Fill 8754
    mean_cluster_size["REp33"] = 1.8 # 1.8 for Fill 9573, 1.8 for Fill 8754
    mean_cluster_size["REm32"] = 1.6 # 1.6 for Fill 9573, 1.6 for Fill 8754
    mean_cluster_size["REm33"] = 1.6 # 1.6 for Fill 9573, 1.6 for Fill 8754
elif fill==9573:
    mean_cluster_size["REp42"] = 1.6
    mean_cluster_size["REp43"] = 1.6
    mean_cluster_size["REm42"] = 1.6
    mean_cluster_size["REm43"] = 1.6
    mean_cluster_size["REp32"] = 1.8
    mean_cluster_size["REp33"] = 1.8
    mean_cluster_size["REm32"] = 1.6
    mean_cluster_size["REm33"] = 1.6



if fill==8754:
    year                    = 2023
    lumi                    = 440.273 + 175.600 + 27.104                        # pb-1, Runs: 367413 + 367406 + 367415 
    colliding_scheme_txt    = "../fill_schemes/Fill_8754/colliding_8754.txt"    # Fill=8754
    fitResults_file         = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_8754/RPC_fit_F8754_fitResults.json"
elif fill==9573:
    year                    = 2024
    lumi                    = 635.347                                           # pb-1, Runs: 380115
    colliding_scheme_txt    = "../fill_schemes/Fill_9573/colliding_9573.txt"    # Fill=9573
    fitResults_file         = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_9573_dead_and_noisy_noSectorRollSubdvision/RPC_fit_F9573_fitResults.json"

# fit results #
fitResults                  = {}
with open(fitResults_file, "r") as f:
    fitResults              = json.load(f)   

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
histos      = loadHists(inFile)

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



def HitRateVsLumi_SingleChamber_regions(inFile, chamber, outDir, lumi=1, printPlots=False, legPos="ur", fit=False):
    ### Hit Rate vs Luminosity - [Single Chamber] ###
    # regions = ["high", "low", "prebeam", "abort"]
    outDir_png  = outDir + "/png"
    outDir_pdf  = outDir + "/pdf"
    outDir_C    = outDir + "/C"

    draw_error  = True

    # Create the canvas
    c = ROOT.TCanvas("c", "c", 900, 700)
    c.SetLeftMargin(0.05)
    c.SetRightMargin(0.05)
    c.SetTopMargin(0.1)
    c.SetBottomMargin(0.05)
    c.Draw()
    c.SetGrid()
    c.cd()

    pad1 = ROOT.TPad("pad1", "pad1", 0.01, 0.01, 0.99, 0.99)
    # pad1.SetTopMargin(0.07)
    # pad1.SetBottomMargin(0.02)
    # pad1.SetLeftMargin(0.1)
    # pad1.SetRightMargin(0.05)
    # pad1.SetBorderMode(0)
    # pad1.SetBorderSize(1)
    # pad1.SetTickx(1)
    # pad1.SetTicky(1)
    pad1.Draw()
    pad1.SetGrid()
    
    pad1.cd()
    # Create the legend
    if legPos=="ur":
        leg = ROOT.TLegend(0.7, 0.7, 0.89, 0.89) # up-right corner
    elif legPos=="ul":
        leg = ROOT.TLegend(0.11, 0.7, 0.47, 0.89) # up-left corner
        # leg = ROOT.TLegend(0.11, 0.7, 0.35, 0.89) # up-left corner
    elif legPos=="dr":
        leg = ROOT.TLegend(0.7, 0.11, 0.89, 0.3) # down-right corner
    elif legPos=="dl":
        leg = ROOT.TLegend(0.11, 0.11, 0.45, 0.35) # down-left corner
    leg.SetTextFont(42)
    leg.SetTextSize(0.035)
    leg.AddEntry("None", f"{year} Data + Fit", "")

    stop        = False
    funcs_error = {}
    for i,r in enumerate(regions):
        hist        = histos[chamber+"_"+r]
        # hist_error  = histos[chamber+"_"+r+"_error"]
        if r=="prebeam" or r=="abort":
            histos[chamber+"_prebeam"].Scale(nbx_prebeam/(nbx_prebeam+nbx_abort))
            histos[chamber+"_abort"].Scale(nbx_abort/(nbx_prebeam+nbx_abort))
            # histos[chamber+"_prebeam_error"].Scale(nbx_prebeam/(nbx_prebeam+nbx_abort))
            # histos[chamber+"_abort_error"].Scale(nbx_abort/(nbx_prebeam+nbx_abort))
            hist        = histos[chamber+"_prebeam"] + histos[chamber+"_abort"]
            # hist_error  = histos[chamber+"_prebeam_error"] + histos[chamber+"_abort_error"]
            stop        = True
        else:
            hist        = histos[chamber+"_"+r]  

        for k in range(hist.GetNbinsX()):
            # print(f"bin {k+1} ---> {hist.GetBinCenter(k+1)} ---> {hist.GetBinContent(k+1)}")
            if hist.GetBinLowEdge(k+1)<9:
                hist.SetBinContent(k+1, -2.0)             
                hist.SetBinError(k+1, 0.0)
            else:
                pass
        # hist.SetTitle(chamber.replace("_"," ").replace("p","+").replace("m","-"))
        hist.SetTitle("") # for RPC2024_approval
        hist.SetTitleSize(1)
        # axis options
        hist.GetXaxis().SetTitle("Instantaneous Luminosity (10^{33} cm^{-2} s^{-1})")
        hist.GetXaxis().SetLabelSize(0.04)
        hist.GetXaxis().SetTitleSize(0.045)
        hist.GetXaxis().SetRangeUser(0, 25)
        hist.SetMinimum(0)
        # hist.SetMinimum(-1) #todelete
        if "RE" in chamber:
            hist.SetMaximum(25)
        elif "W" in chamber:
            hist.SetMaximum(15)

        # hist.SetMaximum(hist.GetMaximum()*2)
        hist.GetYaxis().SetTitle("Hit Rate (Hz/cm^{2})")
        hist.GetYaxis().SetLabelSize(0.04)
        hist.GetYaxis().SetTitleSize(0.045)


        # graphics options
        hist.SetMarkerStyle(graphicsOptions[r]["marker"])
        hist.SetMarkerSize(1)
        hist.SetMarkerColor(graphicsOptions[r]["color"])
        hist.SetLineColor(graphicsOptions[r]["color"])

        if i==0:
            hist.Draw("PE hist")
        else:
            hist.Draw("PE SAME hist")

        if fit:
            # fitFunc = histos[chamber+"_"+r+"_fit"]
            if r=="prebeam" or r=="abort":
                fitFunc                                                     = ROOT.TF1(chamber+"_prebeam_abort_fit", "pol1", 9, 20)
                fitFunc.SetParameter(0,histos[chamber+"_prebeam_fit"].GetParameter(0)*(nbx_prebeam/(nbx_prebeam+nbx_abort)) + histos[chamber+"_abort_fit"].GetParameter(0)*(nbx_abort/(nbx_prebeam+nbx_abort)))
                fitFunc.SetParameter(1,histos[chamber+"_prebeam_fit"].GetParameter(1)*(nbx_prebeam/(nbx_prebeam+nbx_abort)) + histos[chamber+"_abort_fit"].GetParameter(1)*(nbx_abort/(nbx_prebeam+nbx_abort)))
                funcs_error[chamber+"_"+"prebeam_abort"+"_fit"]             = {}
                funcs_error[chamber+"_"+"prebeam_abort"+"_fit"]["p0_error"] = sqrt((nbx_prebeam/(nbx_prebeam+nbx_abort))**2 * fitResults[chamber+"_prebeam"]["p0_error"]**2 + (nbx_abort/(nbx_prebeam+nbx_abort))**2 * fitResults[chamber+"_abort"]["p0_error"]**2)
                funcs_error[chamber+"_"+"prebeam_abort"+"_fit"]["p1_error"] = sqrt((nbx_prebeam/(nbx_prebeam+nbx_abort))**2 * fitResults[chamber+"_prebeam"]["p1_error"]**2 + (nbx_abort/(nbx_prebeam+nbx_abort))**2 * fitResults[chamber+"_abort"]["p1_error"]**2)
                funcs_error[chamber+"_"+"prebeam_abort"+"_fit"]["cov_p0p1"] = (nbx_prebeam/(nbx_prebeam+nbx_abort))**2 * fitResults[chamber+"_prebeam"]["covMatrix"][0][1] + (nbx_abort/(nbx_prebeam+nbx_abort))**2 * fitResults[chamber+"_low"]["covMatrix"][0][1]
            else:
                fitFunc                                       = histos[chamber+"_"+r+"_fit"]
                funcs_error[chamber+"_"+r+"_fit"]             = {}
                funcs_error[chamber+"_"+r+"_fit"]["p0_error"] = fitResults[chamber+"_"+r]["p0_error"]
                funcs_error[chamber+"_"+r+"_fit"]["p1_error"] = fitResults[chamber+"_"+r]["p1_error"]
                funcs_error[chamber+"_"+r+"_fit"]["cov_p0p1"] = fitResults[chamber+"_"+r]["covMatrix"][0][1]
            fitFunc.SetLineColor(graphicsOptions[r]["color"])
            fitFunc.Draw("SAME")

            # Draw fit error
            if draw_error:
                # ERROR BANDS for regions #
                XCenters = range(9, 21)
                YCenters = [fitFunc.Eval(x) for x in XCenters]
                XErrors  = [0 for x in XCenters]
                if r=="prebeam" or r=="abort":
                    YErrors  = [sqrt((x**2)*funcs_error[chamber+"_"+"prebeam_abort"+"_fit"]["p1_error"]**2 + funcs_error[chamber+"_"+"prebeam_abort"+"_fit"]["p0_error"]**2 + 2*x*funcs_error[chamber+"_"+"prebeam_abort"+"_fit"]["cov_p0p1"]) for x in XCenters]
                else:
                    YErrors  = [sqrt((x**2)*funcs_error[chamber+"_"+r+"_fit"]["p1_error"]**2 + funcs_error[chamber+"_"+r+"_fit"]["p0_error"]**2 + 2*x*funcs_error[chamber+"_"+r+"_fit"]["cov_p0p1"]) for x in XCenters]

                hist_error = ROOT.TGraphErrors(len(XCenters), array.array('f', XCenters), array.array('f', YCenters), array.array('f', XErrors), array.array('f', YErrors))
                hist_error.GetXaxis().SetRangeUser(9, 20)  
                hist_error.SetMarkerSize(0)
                hist_error.GetYaxis().SetLabelOffset(999)
                hist_error.GetXaxis().SetLabelSize(0)
                hist_error.GetXaxis().SetTitleSize(0)
                hist_error.SetFillColorAlpha(hist.GetMarkerColor(), 0.6)
                hist_error.SetFillStyle(3013)
                hist_error.Draw("e3 SAME")

        if r=="prebeam" or r=="abort":
            leg.AddEntry(hist, "Pre-beam + Beam-abort", "PL")
        else:
            # leg.AddEntry(hist, chamber.replace("_"," ").replace("p","+").replace("m","-")+" "+r.replace("high","colliding").replace("low","non colliding"), "P")
            leg.AddEntry(hist, r.replace("high","Colliding").replace("low","Non Colliding").replace("prebeam","Pre-beam").replace("abort","Beam-abort"), "PL")
        # leg.AddEntry(hist, r.replace("high","Colliding").replace("low","Non Colliding").replace("prebeam","Pre-beam").replace("abort","Beam-abort"), "P")
        
        if stop:
            break
    leg.Draw("SAME")


    # pad1.cd()
    writeExtraText          = 1
    # extraText               = "Work in progress"
    extraText               = "Preliminary"
    lepText                 = ""
    lumi_sqrtS              = chamber.replace('_',' ').replace('p','+').replace('m','-')+", " + "%s fb^{-1}  (13.6 TeV)"%(round(lumi,3))
    iPeriod                 = 0
    iPos                    = 0
    CMS_lumi(pad1, lumi_sqrtS, iPos, writeExtraText, extraText, lepText) # CMS_lumi(pad, lumi_sqrtS, iPosX, writeExtraText, extraText, lepText), lepText is usually a region
    # pad1.Draw()
    pad1.Update()

    c.cd()
    # Save the plot
    if printPlots:
        c.SaveAs(outDir_png+"/HitRateVsLumi_"+chamber+"_regions.png")
        c.SaveAs(outDir_pdf+"/HitRateVsLumi_"+chamber+"_regions.pdf")
        c.SaveAs(outDir_C+"/HitRateVsLumi_"+chamber+"_regions.C")

def HitRateVsLumi_SingleChamber_bkgs(inFile, chamber, outDir, lumi=1, printPlots=False, legPos="ur"):
    ### Hit Rate vs Luminosity - [Single Chamber] ###
    # types of bkg = ["inclusive", "delayed", "prompt"] #
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

    pad1 = ROOT.TPad("pad1", "pad1", 0.01, 0.01, 0.99, 0.99)
    # pad1.SetTopMargin(0.07)
    # pad1.SetBottomMargin(0.02)
    # pad1.SetLeftMargin(0.1)
    # pad1.SetRightMargin(0.05)
    # pad1.SetBorderMode(0)
    # pad1.SetBorderSize(1)
    # pad1.SetTickx(1)
    # pad1.SetTicky(1)
    pad1.Draw()
    pad1.SetGrid()
    
    pad1.cd()
    # Create the legend
    if legPos=="ur":
        leg = ROOT.TLegend(0.7, 0.7, 0.89, 0.89) # up-right corner
    elif legPos=="ul":
        leg = ROOT.TLegend(0.11, 0.7, 0.4, 0.89) # up-left corner
    elif legPos=="dr":
        leg = ROOT.TLegend(0.7, 0.11, 0.89, 0.3) # down-right corner
    elif legPos=="dl":
        leg = ROOT.TLegend(0.11, 0.11, 0.45, 0.35) # down-left corner
    leg.SetTextFont(42)
    leg.SetTextSize(0.035)

    # definition of the types of background
    bkgs    = ["inclusive", "delayed", "prompt"]
    minX    = histos[chamber+"_prebeam_fit"].GetMinimumX()
    maxX    = histos[chamber+"_prebeam_fit"].GetMaximumX()
    funcs   = {}
    funcs[chamber+"_inclusive_fit"] = ROOT.TF1(chamber+"_inclusive_fit", "pol1", minX, maxX)
    funcs[chamber+"_delayed_fit"]   = ROOT.TF1(chamber+"_delayed_fit", "pol1", minX, maxX)
    funcs[chamber+"_prompt_fit"]    = ROOT.TF1(chamber+"_prompt_fit", "pol1", minX, maxX)

    funcs[chamber+"_inclusive_fit"].SetParameter(0,(nbx_prebeam*histos[chamber+"_prebeam_fit"].GetParameter(0) + nbx_coll*histos[chamber+"_high_fit"].GetParameter(0) + nbx_noncoll*histos[chamber+"_low_fit"].GetParameter(0) + nbx_abort*histos[chamber+"_abort_fit"].GetParameter(0))/ntot)
    funcs[chamber+"_inclusive_fit"].SetParameter(1,(nbx_prebeam*histos[chamber+"_prebeam_fit"].GetParameter(1) + nbx_coll*histos[chamber+"_high_fit"].GetParameter(1) + nbx_noncoll*histos[chamber+"_low_fit"].GetParameter(1) + nbx_abort*histos[chamber+"_abort_fit"].GetParameter(1))/ntot)
    
    funcs[chamber+"_delayed_fit"].SetParameter(0,(nbx_prebeam*histos[chamber+"_prebeam_fit"].GetParameter(0) + nbx_noncoll*histos[chamber+"_low_fit"].GetParameter(0) + nbx_abort*histos[chamber+"_abort_fit"].GetParameter(0))/(ntot-nbx_coll))
    funcs[chamber+"_delayed_fit"].SetParameter(1,(nbx_prebeam*histos[chamber+"_prebeam_fit"].GetParameter(1) + nbx_noncoll*histos[chamber+"_low_fit"].GetParameter(1) + nbx_abort*histos[chamber+"_abort_fit"].GetParameter(1))/(ntot-nbx_coll))
    
    funcs[chamber+"_prompt_fit"].SetParameter(0,histos[chamber+"_high_fit"].GetParameter(0) - funcs[chamber+"_delayed_fit"].GetParameter(0))    
    funcs[chamber+"_prompt_fit"].SetParameter(1,histos[chamber+"_high_fit"].GetParameter(1) - funcs[chamber+"_delayed_fit"].GetParameter(1))    


    hist = ROOT.TH1F(chamber+"_bkgs_fit", chamber.replace("_"," ").replace("p","+").replace("m","-"), 100, 0, 25)
    hist.SetTitleSize(1)
    # axis options
    hist.GetXaxis().SetTitle("Instantaneous Luminosity (10^{33} cm^{-2} s^{-1})")
    hist.GetXaxis().SetLabelSize(0.04)
    hist.GetXaxis().SetTitleSize(0.045)
    hist.GetYaxis().SetTitle("Hit Rate (Hz/cm^{2})")
    hist.GetYaxis().SetLabelSize(0.04)
    hist.GetYaxis().SetTitleSize(0.045)
    # hist.SetTitle("") # for RPC2024_approval
    # hist.SetMinimum(0)
    # hist.SetMinimum(-1) #todelete
    if "RE" in chamber:
        hist.SetMaximum(25)
    elif "W" in chamber:
        hist.SetMaximum(15)
    # hist.SetMaximum(funcs[chamber+"_inclusive_fit"].GetMaximum()*2.0)
    hist.Draw()
    for i,bkg in enumerate(bkgs):
        func = funcs[chamber+"_"+bkg+"_fit"]

        # graphics options
        func.SetLineColor(graphicsOptions[bkg]["color"])

        if i==0:
            func.Draw("SAME")
        else:
            func.Draw("SAME")
        # leg.AddEntry(func, chamber.replace("_"," ").replace("p","+").replace("m","-")+" "+bkg, "l")
        leg.AddEntry(func, bkg.replace("inclusive","Inclusive Bkg").replace("delayed","Delayed Bkg").replace("prompt","Prompt Bkg"), "l")
    leg.Draw("SAME")


    # pad1.cd()
    writeExtraText          = 1
    # extraText               = "Work in progress"
    extraText               = "Preliminary"
    lepText                 = ""
    lumi_sqrtS              = "%s fb^{-1}  (13.6 TeV)"%(round(lumi,3))
    iPeriod                 = 0
    iPos                    = 0
    CMS_lumi(pad1, lumi_sqrtS, iPos, writeExtraText, extraText, lepText) # CMS_lumi(pad, lumi_sqrtS, iPosX, writeExtraText, extraText, lepText), lepText is usually a region
    # pad1.Draw()
    pad1.Update()

    c.cd()
    # Save the plot
    if printPlots:
        c.SaveAs(outDir_png+"/HitRateVsLumi_"+chamber+"_bkgs.png")
        c.SaveAs(outDir_pdf+"/HitRateVsLumi_"+chamber+"_bkgs.pdf")
        c.SaveAs(outDir_C+"/HitRateVsLumi_"+chamber+"_bkgs.C")

def HitRateVsLumi_DoubleChamber_single_region(inFile, chambers, reg, outDir, fit=False, lumi=1, printPlots=False, colored=False, legPos="ur"):
    print(f"chambers selected: {chambers} ---> region: {reg}")
    ### Hit Rate vs Luminosity - [Double Chamber] ###
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

    pad1 = ROOT.TPad("pad1", "pad1", 0.01, 0.01, 0.99, 0.99)
    # pad1.SetTopMargin(0.07)
    # pad1.SetBottomMargin(0.02)
    # pad1.SetLeftMargin(0.1)
    # pad1.SetRightMargin(0.05)
    # pad1.SetBorderMode(0)
    # pad1.SetBorderSize(1)
    # pad1.SetTickx(1)
    # pad1.SetTicky(1)
    pad1.Draw()
    pad1.SetGrid()

    pad1.cd()
    # Create the legend
    if legPos=="ur":
        leg = ROOT.TLegend(0.7, 0.7, 0.89, 0.89) # up-right corner
    elif legPos=="ul":
        leg = ROOT.TLegend(0.11, 0.7, 0.35, 0.89) # up-left corner
    elif legPos=="dr":
        leg = ROOT.TLegend(0.7, 0.11, 0.89, 0.3) # down-right corner
    elif legPos=="dl":
        leg = ROOT.TLegend(0.11, 0.11, 0.45, 0.35) # down-left corner
    leg.SetTextFont(42)
    leg.SetTextSize(0.035)

    for i,ch in enumerate(chambers):
        # hist = histos[ch].Clone("")
        # hist = copy.deepcopy(histos[ch])
        hist = histos[ch+"_"+reg]
        for k in range(hist.GetNbinsX()):
            # print(f"bin {k+1} ---> {hist.GetBinCenter(k+1)} ---> {hist.GetBinContent(k+1)}")
            if hist.GetBinCenter(k+1)<9:
                hist.SetBinContent(k+1, -2.0)             
                hist.SetBinError(k+1, 0.0)
            else:
                pass
                

        # hist.SetTitle("Hit Rate vs Luminosity")
        # hist.SetTitle("") # for RPC2024_approval
        hist.SetTitle(reg.replace("all","Total").replace("high","Colliding").replace("low","Non Colliding").replace("prebeam","Pre-beam").replace("abort","Beam-abort"))
        hist.SetTitleSize(1)

        # axis options
        hist.GetXaxis().SetTitle("Instantaneous Luminosity (10^{33} cm^{-2} s^{-1})")
        hist.GetXaxis().SetLabelSize(0.04)
        hist.GetXaxis().SetTitleSize(0.045)
        hist.GetXaxis().SetRangeUser(0, 25)
        hist.SetMinimum(0)
        hist.SetMaximum(25)
        # hist.SetMaximum(hist.GetMaximum()*2.0)
        hist.GetYaxis().SetTitle("Hit Rate (Hz/cm^{2})")
        hist.GetYaxis().SetLabelSize(0.04)
        hist.GetYaxis().SetTitleSize(0.045)
        # graphics options
        hist.SetMarkerStyle(graphicsOptions[reg]["marker"])
        hist.SetMarkerSize(1)
        if colored:
            hist.SetMarkerColor(2*(i+1))
            hist.SetLineColor(2*(i+1))
            # hist.SetMarkerColor(graphicsOptions[reg]["color"])
            # hist.SetLineColor(graphicsOptions[reg]["color"])
        else:
            hist.SetMarkerColor(ROOT.kBlack)
            hist.SetLineColor(ROOT.kBlack)

        if i==0:
            hist.Draw("PE hist")
        else:
            hist.Draw("PE SAME hist")

        # leg.AddEntry(hist, ch.replace("_"," ").replace("p","+").replace("m","-")+" "+reg.replace("all","Total").replace("high","colliding").replace("low","non colliding"), "P")
        leg.AddEntry(hist, ch.replace("_"," ").replace("p","+").replace("m","-"), "P")

        if fit:
            fitFunc = histos[ch+"_"+reg+"_fit"]
            fitFunc.SetLineColor(2*(i+1))
            if "m" in ch:
                fitFunc.SetLineStyle(1) # solid line
            elif "p" in ch:
                fitFunc.SetLineStyle(7) # dashed line
            fitFunc.Draw("SAME")

            # leg.AddEntry(fitFunc, ch.replace("_"," ").replace("p","+").replace("m","-")+" "+reg.replace("all","Total").replace("high","colliding").replace("low","non colliding")+" fit", "l")
            leg.AddEntry(fitFunc, ch.replace("_"," ").replace("p","+").replace("m","-")+" fit", "l")

    leg.Draw("SAME")


    # pad1.cd()
    writeExtraText          = 1
    # extraText               = "Work in progress"
    extraText               = "Preliminary"
    lepText                 = ""
    lumi_sqrtS              = "%s fb^{-1}  (13.6 TeV)"%(round(lumi,3))
    iPeriod                 = 0
    iPos                    = 0
    CMS_lumi(pad1, lumi_sqrtS, iPos, writeExtraText, extraText, lepText) # CMS_lumi(pad, lumi_sqrtS, iPosX, writeExtraText, extraText, lepText), lepText is usually a region
    # pad1.Draw()
    pad1.Update()

    c.cd()
    # Save the plot
    if printPlots:
        c.SaveAs(outDir_png+"/HitRateVsLumi_["+','.join(chambers)+"]_"+reg+".png")
        c.SaveAs(outDir_pdf+"/HitRateVsLumi_["+','.join(chambers)+"]_"+reg+".pdf")
        c.SaveAs(outDir_C+"/HitRateVsLumi_["+','.join(chambers)+"]_"+reg+".C")

def HitRateVsLumi_DoubleChamber_single_bkg(inFile, chambers, bkg, outDir, lumi=1, printPlots=False, colored=False, legPos="ur"):
    print(f"chambers selected: {chambers} ---> background: {bkg}")
    ### Hit Rate vs Luminosity - [Double Chamber] ###
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

    pad1 = ROOT.TPad("pad1", "pad1", 0.01, 0.01, 0.99, 0.99)
    # pad1.SetTopMargin(0.07)
    # pad1.SetBottomMargin(0.02)
    # pad1.SetLeftMargin(0.1)
    # pad1.SetRightMargin(0.05)
    # pad1.SetBorderMode(0)
    # pad1.SetBorderSize(1)
    # pad1.SetTickx(1)
    # pad1.SetTicky(1)
    pad1.Draw()
    pad1.SetGrid()


    pad1.cd()
    # Create the legend
    if legPos=="ur":
        leg = ROOT.TLegend(0.7, 0.7, 0.89, 0.89) # up-right corner
    elif legPos=="ul":
        leg = ROOT.TLegend(0.11, 0.7, 0.42, 0.89) # up-left corner
    elif legPos=="dr":
        leg = ROOT.TLegend(0.7, 0.11, 0.89, 0.3) # down-right corner
    elif legPos=="dl":
        leg = ROOT.TLegend(0.11, 0.11, 0.45, 0.35) # down-left corner
    leg.SetTextFont(42)
    leg.SetTextSize(0.035)



    funcs   = {}
    # for i,ch in enumerate(sorted(chambers, key=lambda x: histos[x+"_high"].GetMaximum(), reverse=True)):
    for i,ch in enumerate(chambers):
        
        # definition of the types of background
        minX    = histos[ch+"_prebeam_fit"].GetMinimumX()
        maxX    = histos[ch+"_prebeam_fit"].GetMaximumX()
        
        funcs[ch+"_inclusive_fit"] = ROOT.TF1(ch+"_inclusive_fit", "pol1", minX, maxX)
        funcs[ch+"_delayed_fit"]   = ROOT.TF1(ch+"_delayed_fit", "pol1", minX, maxX)
        funcs[ch+"_prompt_fit"]    = ROOT.TF1(ch+"_prompt_fit", "pol1", minX, maxX)

        funcs[ch+"_inclusive_fit"].SetParameter(0,(nbx_prebeam*histos[ch+"_prebeam_fit"].GetParameter(0) + nbx_coll*histos[ch+"_high_fit"].GetParameter(0) + nbx_noncoll*histos[ch+"_low_fit"].GetParameter(0) + nbx_abort*histos[ch+"_abort_fit"].GetParameter(0))/ntot)
        funcs[ch+"_inclusive_fit"].SetParameter(1,(nbx_prebeam*histos[ch+"_prebeam_fit"].GetParameter(1) + nbx_coll*histos[ch+"_high_fit"].GetParameter(1) + nbx_noncoll*histos[ch+"_low_fit"].GetParameter(1) + nbx_abort*histos[ch+"_abort_fit"].GetParameter(1))/ntot)
        
        funcs[ch+"_delayed_fit"].SetParameter(0,(nbx_prebeam*histos[ch+"_prebeam_fit"].GetParameter(0) + nbx_noncoll*histos[ch+"_low_fit"].GetParameter(0) + nbx_abort*histos[ch+"_abort_fit"].GetParameter(0))/(ntot-nbx_coll))
        funcs[ch+"_delayed_fit"].SetParameter(1,(nbx_prebeam*histos[ch+"_prebeam_fit"].GetParameter(1) + nbx_noncoll*histos[ch+"_low_fit"].GetParameter(1) + nbx_abort*histos[ch+"_abort_fit"].GetParameter(1))/(ntot-nbx_coll))
        
        funcs[ch+"_prompt_fit"].SetParameter(0,histos[ch+"_high_fit"].GetParameter(0) - funcs[ch+"_delayed_fit"].GetParameter(0))    
        funcs[ch+"_prompt_fit"].SetParameter(1,histos[ch+"_high_fit"].GetParameter(1) - funcs[ch+"_delayed_fit"].GetParameter(1))

    hist = ROOT.TH1F(bkg+"_fit", bkg.replace("inclusive","Inclusive Bkg").replace("delayed","Delayed Bkg").replace("prompt","Prompt Bkg"), 100, 0, 25)
    # hist.SetTitle("") # for RPC2024_approval
    hist.SetTitleSize(1)
    # axis options
    hist.GetXaxis().SetTitle("Instantaneous Luminosity (10^{33} cm^{-2} s^{-1})")
    hist.GetXaxis().SetLabelSize(0.04)
    hist.GetXaxis().SetTitleSize(0.045)
    hist.GetYaxis().SetTitle("Hit Rate (Hz/cm^{2})")
    hist.GetYaxis().SetLabelSize(0.04)
    hist.GetYaxis().SetTitleSize(0.045)
    hist.SetMinimum(0)
    hist.SetMaximum(25)
    # hist.SetMaximum(funcs[ch+"_inclusive_fit"].GetMaximum()*2.0)
    hist.Draw()

    for i,ch in enumerate(chambers):
        func = funcs[ch+"_"+bkg+"_fit"]
        # graphics options
        # funcs.SetLineColor(graphicsOptions[bkg]["color"])
        func.SetLineColor(2*(i+1))
        if i==0:
            func.Draw("SAME")
        else:
            func.Draw("SAME")
        leg.AddEntry(func, f'{ch.replace("_"," ").replace("p","+").replace("m","-")}: y={round(func.GetParameter(1),2)}x+{round(func.GetParameter(0),2)}', "l")
        # leg.AddEntry(func, f'{ch.replace("_"," ").replace("p","+").replace("m","-")}', "l") # for RPC2024_approval


    
    # ratio between m & q for the 2 chambers #
    if len(chambers)==2:
        ratio_m = funcs[chambers[1]+"_"+bkg+"_fit"].GetParameter(1)/funcs[chambers[0]+"_"+bkg+"_fit"].GetParameter(1)
        ratio_q = funcs[chambers[1]+"_"+bkg+"_fit"].GetParameter(0)/funcs[chambers[0]+"_"+bkg+"_fit"].GetParameter(0)
        # print(f"m_{{{chambers[1]}}}/m_{{{chambers[0]}}} = {ratio_m} ---> q_{{{chambers[1]}}}/q_{{{chambers[0]}}}= {ratio_q}")

        
        # text = ROOT.TLatex(0.5, 0.3, f"#splitline{{m_{{{chambers[1]}}}/m_{{{chambers[0]}}} = {ratio_m}}}{{q_{{{chambers[1]}}}/q_{{{chambers[0]}}} = {ratio_q}}}")
        # text.SetTextSize(0.025)
        # text.SetTextAlign(11)
        # text.Draw("SAME")

    
    leg.Draw("SAME")


    # pad1.cd()
    writeExtraText          = 1
    # extraText               = "Work in progress"
    extraText               = "Preliminary"
    lepText                 = ""
    lumi_sqrtS              = "%s fb^{-1}  (13.6 TeV)"%(round(lumi,3))
    iPeriod                 = 0
    iPos                    = 0
    CMS_lumi(pad1, lumi_sqrtS, iPos, writeExtraText, extraText, lepText) # CMS_lumi(pad, lumi_sqrtS, iPosX, writeExtraText, extraText, lepText), lepText is usually a region
    # pad1.Draw()
    pad1.Update()

    c.cd()
    # Save the plot
    if printPlots:
        c.SaveAs(outDir_png+"/HitRateVsLumi_["+','.join(chambers)+"]_"+bkg+".png")
        c.SaveAs(outDir_pdf+"/HitRateVsLumi_["+','.join(chambers)+"]_"+bkg+".pdf")
        c.SaveAs(outDir_C+"/HitRateVsLumi_["+','.join(chambers)+"]_"+bkg+".C")

def HitRateVsLumi_FourChamber_single_region(inFile, chambers, reg, outDir, fit=False, lumi=1, printPlots=False, colored=False, legPos="ur", hl_projection=False):
    print(f"chambers selected: {chambers} ---> region: {reg}")
    ### Hit Rate vs Luminosity - [Four Chamber] ###
    outDir_png  = outDir + "/png"
    outDir_pdf  = outDir + "/pdf"
    outDir_C    = outDir + "/C"

    draw_error  = True

    # Create the canvas
    c = ROOT.TCanvas("c", "c", 900, 700)
    c.SetLeftMargin(0.05)
    c.SetRightMargin(0.05)
    c.SetTopMargin(0.1)
    c.SetBottomMargin(0.05)
    c.Draw()
    c.SetGrid()
    c.cd()

    pad1 = ROOT.TPad("pad1", "pad1", 0.01, 0.01, 0.99, 0.99)
    # pad1.SetTopMargin(0.07)
    # pad1.SetBottomMargin(0.02)
    # pad1.SetLeftMargin(0.1)
    # pad1.SetRightMargin(0.05)
    # pad1.SetBorderMode(0)
    # pad1.SetBorderSize(1)
    # pad1.SetTickx(1)
    # pad1.SetTicky(1)
    pad1.Draw()
    pad1.SetGrid()

    pad1.cd()
    # Create the legend
    if legPos=="ur":
        leg = ROOT.TLegend(0.7, 0.7, 0.89, 0.89) # up-right corner
    elif legPos=="ul":
        # leg = ROOT.TLegend(0.11, 0.7, 0.4, 0.89) # up-left corner
        leg = ROOT.TLegend(0.11, 0.42, 0.45, 0.89) # up-left corner
    elif legPos=="dr":
        leg = ROOT.TLegend(0.7, 0.11, 0.89, 0.3) # down-right corner
    elif legPos=="dl":
        leg = ROOT.TLegend(0.11, 0.11, 0.45, 0.35) # down-left corner
    leg.SetTextFont(42)
    leg.SetTextSize(0.035)

    if hl_projection:
        leg.AddEntry("None", "2024 Data + Fit", "")

        h = ROOT.TH1F("h", "", 100, 0, 100) # scale the offline-HitRate by a factor mean_cluster_size when comparing to online-HitRate
        h.Draw()
        h.GetXaxis().SetRangeUser(0, 80)
        h.SetMinimum(0)
        h.SetMaximum(250)
        # h.GetXaxis().SetTitle("Instantaneous Luminosity (10^{33} cm^{-2} s^{-1})")
        h.GetXaxis().SetTitle("")
        h.GetXaxis().SetLabelSize(0) # 0.03
        h.GetXaxis().SetTitleSize(0) # 0.045
        h.GetYaxis().SetTitle("Rate (Hz/cm^{2})")

        # Create the secondary axis on the right side
        axis2 = ROOT.TGaxis(80, h.GetMinimum(), 80, h.GetMaximum(), h.GetMinimum(), h.GetMaximum(), 510, "+L")
        axis2.SetTitle("Hit Rate (Hz/cm^{2})")
        axis2.SetLineColor(ROOT.kGray)
        axis2.SetLabelColor(ROOT.kGray)
        axis2.SetTitleColor(ROOT.kGray)
        # axis2.Draw()


    for i,ch in enumerate(chambers):
        # hist = histos[ch].Clone("")
        # hist = copy.deepcopy(histos[ch])
        hist        = histos[ch+"_"+reg]
        hist_error  = histos[ch+"_"+reg+"_error"]
        hist.Scale(mean_cluster_size[ch.split("_")[0]]) # scale the offline-HitRate by a factor mean_cluster_size when comparing to online-HitRate
        for k in range(hist.GetNbinsX()):
            # print(f"bin {k+1} ---> {hist.GetBinCenter(k+1)} ---> {hist.GetBinContent(k+1)}")
            if hist.GetBinCenter(k+1)<9:
                hist.SetBinContent(k+1, -2.0)             
                hist.SetBinError(k+1, 0.0)
            else:
                pass
                
        

        # draw a new x-axis with the luminosity in 10^34 cm^-2 s^-1
        axis1 = ROOT.TGaxis(0, 0, 80, 0, 0, 80000, 510, "")
        axis1.SetTitle("Instantaneous Luminosity (10^{30} cm^{-2} s^{-1})")
        # axis1 = ROOT.TGaxis(0, 0, 80, 0, 0, 8, 510, "")
        # axis1.SetTitle("Instantaneous Luminosity (10^{34} cm^{-2} s^{-1})")
        axis1.SetLineColor(ROOT.kBlack)
        axis1.SetLabelColor(ROOT.kBlack)
        axis1.SetTitleColor(ROOT.kBlack)
        axis1.SetLabelFont(42)
        axis1.SetTitleFont(42)
        axis1.SetLabelSize(0.035)
        axis1.SetTitleSize(0.035)
        axis1.Draw()

        # hist.SetTitle("Hit Rate vs Luminosity")
        # hist.SetTitle("") # for RPC2024_approval
        hist.SetTitle(reg.replace("high","Colliding").replace("low","Non Colliding").replace("prebeam","Pre-beam").replace("abort","Beam-abort"))
        hist.SetTitleSize(1)
        # axis options
        hist.GetXaxis().SetTitle("Instantaneous Luminosity (10^{33} cm^{-2} s^{-1})")
        hist.GetXaxis().SetLabelSize(0) # 0.03
        hist.GetXaxis().SetTitleSize(0) # 0.045
        # hist.GetYaxis().SetLabelOffset(999)
        hist.GetXaxis().SetRangeUser(0, 25)
        hist.SetMinimum(0)
        hist.SetMaximum(25)

        if hl_projection:
            hist.GetXaxis().SetRangeUser(0, 80)
            hist.SetMinimum(0)
            hist.SetMaximum(250) # scale the offline-HitRate by a factor mean_cluster_size when comparing to online-HitRate

        # hist.SetMaximum(hist.GetMaximum()*2.0)
        hist.GetYaxis().SetTitle("Hit Rate (Hz/cm^{2})")
        hist.GetYaxis().SetLabelSize(0.04)
        hist.GetYaxis().SetTitleSize(0.045)


        # graphics options
        if "m" in ch:
            hist.SetMarkerStyle(ROOT.kFullCircle)
            hist.SetLineStyle(1) # solid line
        elif "p" in ch:
            hist.SetMarkerStyle(ROOT.kOpenCircle)
            hist.SetLineStyle(2) # dashed line
        hist.SetMarkerSize(0.75)
        if colored:
            if i==0 or i==1:
                hist.SetMarkerColor(ROOT.kRed)
                hist.SetLineColor(ROOT.kRed)
            elif i==2 or i==3:
                hist.SetMarkerColor(ROOT.kBlue)
                hist.SetLineColor(ROOT.kBlue)
        else:
            hist.SetMarkerColor(ROOT.kBlack)
            hist.SetLineColor(ROOT.kBlack)

        # Draw the histogram
        if i==0:
            if hl_projection:
                hist.Draw("p0 SAME")
            else:
                hist.Draw("p0")
        else:
            hist.Draw("p0 SAME")



        # leg.AddEntry(hist, ch.replace("_"," ").replace("p","+").replace("m","-")+" "+reg.replace("all","Total").replace("high","colliding").replace("low","non colliding"), "P")
        leg.AddEntry(hist, ch.replace("_"," ").replace("p","+").replace("m","-")+" "+reg.replace("all","").replace("high","colliding").replace("low","non colliding"), "pl")


        if fit:
            fitFunc     = histos[ch+"_"+reg+"_fit"]
            old_params  = fitFunc.GetParameter(0), fitFunc.GetParameter(1)
            print(f"old params for {ch} in {reg} ---> {old_params}")
            new_params  = [old_params[0]*mean_cluster_size[ch.split("_")[0]],old_params[1]*mean_cluster_size[ch.split("_")[0]]] # scale the offline-HitRate by a factor mean_cluster_size when comparing to online-HitRate
            print(f"new params for {ch} in {reg} ---> {new_params}")
            fitFunc.SetParameter(0, new_params[0])
            fitFunc.SetParameter(1, new_params[1])
            fitFunc.SetLineWidth(1)
            fitFunc.SetLineColor(hist.GetMarkerColor())
            
            if "m" in ch:
                fitFunc.SetLineStyle(1) # solid line
                projection_marker_style = ROOT.kFullDoubleDiamond
            elif "p" in ch:
                fitFunc.SetLineStyle(2) # dashed line
                projection_marker_style = ROOT.kOpenDoubleDiamond
        
            if hl_projection:
                fitFunc.SetRange(0, 80) # (0, 50)

                # Projection to lumi = 5x10^34 cm^-2 s^-1
                hl_lumi1   = 50 # 10^33 cm^-2 s^-1
                hl_hitrate = fitFunc.Eval(hl_lumi1)
                print(f"Projection for {ch} in {reg} ---> lumi: {hl_lumi1} 10^{33} cm^{-2} s^{-1} ---> hitrate: {hl_hitrate} Hz/cm^2")
                hl1_marker = ROOT.TMarker()
                hl1_marker.SetMarkerStyle(projection_marker_style)
                hl1_marker.SetMarkerSize(3)
                hl1_marker.SetMarkerColor(hist.GetMarkerColor())
                # hl1_marker.DrawMarker(hl_lumi1, hl_hitrate)
                # add vertical line for "hl_lumi1"
                line1      = ROOT.TLine(hl_lumi1, 0, hl_lumi1, hist.GetMaximum())
                line1.SetLineColor(ROOT.kGreen)
                line1.Draw("SAME")


                # Projection to lumi = 7.5x10^34 cm^-2 s^-1
                hl_lumi2   = 75 # 10^33 cm^-2 s^-1
                hl_hitrate = fitFunc.Eval(hl_lumi2)
                print(f"Projection for {ch} in {reg} ---> lumi: {hl_lumi2} 10^{33} cm^{-2} s^{-1} ---> hitrate: {hl_hitrate} Hz/cm^2")
                hl2_marker = ROOT.TMarker()
                hl2_marker.SetMarkerStyle(projection_marker_style)
                hl2_marker.SetMarkerSize(3)
                hl2_marker.SetMarkerColor(hist.GetMarkerColor())
                # hl2_marker.DrawMarker(hl_lumi2, hl_hitrate)
                line2      = ROOT.TLine(hl_lumi2, 0, hl_lumi2, hist.GetMaximum())
                line2.SetLineColor(ROOT.kGreen)
                line2.Draw("SAME")

            # Draw fit error
            if draw_error:
                hist_error.GetXaxis().SetRangeUser(0, 80)  
                hist_error.Scale(mean_cluster_size[ch.split("_")[0]]) # scale the offline-HitRate by a factor mean_cluster_size when comparing to online-HitRate
                hist_error.SetMarkerSize(0)
                hist_error.GetYaxis().SetLabelOffset(999)
                hist_error.GetXaxis().SetLabelSize(0)
                hist_error.GetXaxis().SetTitleSize(0)
                if "m" in ch:
                    hist_error.SetFillColorAlpha(hist.GetMarkerColor(), 0.6)
                elif "p" in ch:
                    hist_error.SetFillColorAlpha(hist.GetMarkerColor(), 0.3)                
                hist_error.SetFillStyle(1001)
                hist_error.Draw("e3 SAME")

            # Draw the fit function
            fitFunc.Draw("SAME")
            # leg.AddEntry(fitFunc, ch.replace("_"," ").replace("p","+").replace("m","-")+" "+reg.replace("all","Total").replace("high","colliding").replace("low","non colliding")+" fit", "l")
            # leg.AddEntry(fitFunc, ch.replace("_"," ").replace("p","+").replace("m","-")+" "+reg.replace("all","").replace("high","colliding").replace("low","non colliding")+" fit", "l")
        c.Update()



    if hl_projection and ("REm42_S10" in chambers):
        # draw CMS-TDR-016 expectations as 4 markers
        leg.AddEntry("None", "", "")
        leg.AddEntry("None", "CMS-TDR-016 Exp.", "")

        hl_tdr_marker_2 = ROOT.TMarker()
        hl_tdr_marker_2.SetMarkerStyle(ROOT.kOpenSquare)
        hl_tdr_marker_2.SetMarkerSize(1.5)
        hl_tdr_marker_2.SetMarkerColor(ROOT.kRed)
        hl_tdr_marker_2.DrawMarker(hl_lumi1, 180)
        leg.AddEntry(hl_tdr_marker_2, "RE+4/2 S10", "P")

        hl_tdr_marker_1 = ROOT.TMarker()
        hl_tdr_marker_1.SetMarkerStyle(ROOT.kFullSquare)
        hl_tdr_marker_1.SetMarkerSize(1.5)
        hl_tdr_marker_1.SetMarkerColor(ROOT.kRed)
        hl_tdr_marker_1.DrawMarker(hl_lumi1, 195)
        leg.AddEntry(hl_tdr_marker_1, "RE-4/2 S10", "P")

        hl_tdr_marker_4 = ROOT.TMarker()
        hl_tdr_marker_4.SetMarkerStyle(ROOT.kOpenTriangleUp)
        hl_tdr_marker_4.SetMarkerSize(1.5)
        hl_tdr_marker_4.SetMarkerColor(ROOT.kBlue)
        hl_tdr_marker_4.DrawMarker(hl_lumi1, 121)
        leg.AddEntry(hl_tdr_marker_4, "RE+3/2 S10", "P")

        hl_tdr_marker_3 = ROOT.TMarker()
        hl_tdr_marker_3.SetMarkerStyle(ROOT.kFullTriangleUp)
        hl_tdr_marker_3.SetMarkerSize(1.5)
        hl_tdr_marker_3.SetMarkerColor(ROOT.kBlue)
        hl_tdr_marker_3.DrawMarker(hl_lumi1, 103)
        leg.AddEntry(hl_tdr_marker_3, "RE-3/2 S10", "P")

    leg.Draw("SAME")





    # pad1.cd()
    writeExtraText          = 1
    # extraText               = "Work in progress"
    extraText               = "Preliminary"
    lepText                 = ""
    lumi_sqrtS              = "%s fb^{-1}  (13.6 TeV)"%(round(lumi,3))
    iPeriod                 = 0
    iPos                    = 0
    CMS_lumi(pad1, lumi_sqrtS, iPos, writeExtraText, extraText, lepText) # CMS_lumi(pad, lumi_sqrtS, iPosX, writeExtraText, extraText, lepText), lepText is usually a region
    # pad1.Draw()
    pad1.Update()

    c.cd()
    # Save the plot
    if printPlots:
        c.SaveAs(outDir_png+"/HitRateVsLumi_["+','.join(chambers)+"]_"+reg+".png")
        c.SaveAs(outDir_pdf+"/HitRateVsLumi_["+','.join(chambers)+"]_"+reg+".pdf")
        c.SaveAs(outDir_C+"/HitRateVsLumi_["+','.join(chambers)+"]_"+reg+".C")





if len(chambers)==1:
    HitRateVsLumi_SingleChamber_regions(inFile, chambers[0], outDir, lumi*1e-3, printPlots, legPos="ul", fit=True)
    HitRateVsLumi_SingleChamber_bkgs(inFile,    chambers[0], outDir, lumi*1e-3, printPlots, legPos="ul")
elif len(chambers)==2:
    print("Preparing the plots for the double chamber...")
    HitRateVsLumi_DoubleChamber_single_region(inFile,   chambers, "all",        outDir, True ,  lumi*1e-3, printPlots, colored=True,    legPos="ul")
    HitRateVsLumi_DoubleChamber_single_region(inFile,   chambers, "high",       outDir, True ,  lumi*1e-3, printPlots, colored=True,    legPos="ul")
    HitRateVsLumi_DoubleChamber_single_region(inFile,   chambers, "low",        outDir, True ,  lumi*1e-3, printPlots, colored=True,    legPos="ul")
    HitRateVsLumi_DoubleChamber_single_region(inFile,   chambers, "prebeam",    outDir, True ,  lumi*1e-3, printPlots, colored=True,    legPos="ul")
    HitRateVsLumi_DoubleChamber_single_region(inFile,   chambers, "abort",      outDir, True ,  lumi*1e-3, printPlots, colored=True,    legPos="ul")
    HitRateVsLumi_DoubleChamber_single_bkg(inFile,      chambers, "inclusive",  outDir,         lumi*1e-3, printPlots,                  legPos="ul")
    HitRateVsLumi_DoubleChamber_single_bkg(inFile,      chambers, "prompt",     outDir,         lumi*1e-3, printPlots,                  legPos="ul")
    HitRateVsLumi_DoubleChamber_single_bkg(inFile,      chambers, "delayed",    outDir,         lumi*1e-3, printPlots,                  legPos="ul")
elif len(chambers)>2:
    print("More than 2 chambers selected")
    if len(chambers)==4:
        HitRateVsLumi_FourChamber_single_region(inFile,   chambers, "all",        outDir, True ,lumi*1e-3, printPlots, colored=True,    legPos="ul", hl_projection=True)


# outFile.Close()
print("Done!")
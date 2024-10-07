import os
import argparse
import sys
import ROOT
import cmsstyle as CMS
from loadHists import loadHists
from graphicsOptions import graphicsOptions
import copy
from math import sqrt
import array
import numpy as np
import json
ROOT.gStyle.SetOptStat(0)
ROOT.gROOT.SetBatch(1)    


inFile      = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_9573_dead_and_noisy_noSectorRollSubdvision/RPC_fit_F9573.root"
outDir      = "/eos/user/l/lfavilla/RPC/plots/background_Run3toHL/"
webDir      = "/eos/user/l/lfavilla/www/RPC/plots/background_Run3toHL/"
year        = 2024
lumi        = round(635.347/1000., 3) # fb-1, Runs: 380115
energy      = 13.6 # TeV
canv_name   = "trial_plot"
addInfo     = "addInfo"

# Output directory
outDir_png  = outDir + "png/"
outDir_pdf  = outDir + "pdf/"
outDir_C    = outDir + "C/"
if not os.path.exists(outDir):
    os.makedirs(outDir)
if not os.path.exists(outDir_png):
    os.makedirs(outDir_png)
if not os.path.exists(outDir_pdf):
    os.makedirs(outDir_pdf)
if not os.path.exists(outDir_C):
    os.makedirs(outDir_C)
# Web directory
if not os.path.exists(webDir):
    os.makedirs(webDir)
    os.system("cp /eos/user/l/lfavilla/index.php " + webDir)


# Get the list of histograms
histos  = loadHists(inFile)


# Canvas creation and histogram plotting
x_min       = 0
x_max       = 25
y_min       = 0
y_max       = 100
xtitle      = "Instantaneous Luminosity (10^{33} cm^{-2} s^{-1})"
ytitle      = "Hit Rate (Hz/cm^{2})"

iPos        = 0
CMS.SetLumi(lumi)
CMS.SetEnergy(energy)
CMS.ResetAdditionalInfo()
CMS.AppendAdditionalInfo(addInfo)
CMS.SetExtraText("Work in progress")
CMS.setCMSStyle()
canv = CMS.cmsCanvas(canv_name, x_min, x_max, y_min, y_max, xtitle, ytitle, square=CMS.kRectangular, iPos=iPos)
# hdf  = CMS.GetcmsCanvasHist(canv)
# # hdf.GetYaxis().SetMaxDigits(2)
# hdf.GetYaxis().SetLabelOffset(0.001)
# hdf.GetYaxis().SetLabelSize(0.045)
# hdf.GetYaxis().SetTitleOffset(1.1)
# hdf.GetYaxis().SetTitleSize(0.045)
# hdf.GetXaxis().SetLabelOffset(0.001)
# hdf.GetXaxis().SetLabelSize(0.045)
# hdf.GetXaxis().SetTitleOffset(1.1)
# hdf.GetXaxis().SetTitleSize(0.045)

latex = ROOT.TLatex()
latex.SetTextFont(42)
latex.SetTextSize(0.04)
latex.SetTextAlign(22)
latex.DrawLatexNDC(0.27, 0.77, "SOME TEXT")

h1          = copy.deepcopy(histos["REp42_high"])
h1_fit      = copy.deepcopy(histos["REp42_high_fit"])
marker_1    = ROOT.kFullCircle
mcolor_1    = ROOT.kRed
h2          = copy.deepcopy(histos["REp42_low"])
h2_fit      = copy.deepcopy(histos["REp42_low_fit"])
marker_2    = ROOT.kFullSquare
mcolor_2    = ROOT.kBlue

CMS.cmsDraw(h=h1, style="", marker=marker_1, mcolor=mcolor_1)
CMS.cmsDraw(h=h2, style="", marker=marker_2, mcolor=mcolor_2)
# CMS.cmsDraw(h=h1_fit, style="e3 SAME", msize=0, fcolor=mcolor_1, fstyle=3001, lcolor=mcolor_1, lwidth=2)
# CMS.cmsDraw(h=h2_fit, style="e3 SAME", msize=0, fcolor=mcolor_2, fstyle=3001, lcolor=mcolor_2, lwidth=2)
# h1_fit.Draw("SAME")
h2_fit.Draw("SAME")


# Save the canvas
CMS.SaveCanvas(canv, outDir_png+canv_name+".png", close=False)
CMS.SaveCanvas(canv, outDir_pdf+canv_name+".pdf", close=False)
CMS.SaveCanvas(canv, outDir_C+canv_name+".C",   close=False)

CMS.SaveCanvas(canv, webDir+canv_name+".png", close=False)
CMS.SaveCanvas(canv, webDir+canv_name+".pdf", close=True)
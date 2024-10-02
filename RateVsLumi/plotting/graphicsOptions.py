import ROOT
import numpy as np
ROOT.gStyle.SetOptStat(0)

graphicsOptions             = {}

graphicsOptions["W0"]       = {"color": ROOT.kGreen,     "marker": ROOT.kFullDiamond}
graphicsOptions["Wp1"]      = {"color": ROOT.kBlue,      "marker": ROOT.kFullCircle}
graphicsOptions["Wp2"]      = {"color": ROOT.kRed,       "marker": ROOT.kFullSquare}
graphicsOptions["Wm1"]      = {"color": ROOT.kBlue,      "marker": ROOT.kOpenCircle}
graphicsOptions["Wm2"]      = {"color": ROOT.kRed,       "marker": ROOT.kOpenSquare}

graphicsOptions["REp12"]    = {"color": ROOT.kRed,       "marker": ROOT.kFullCircle}
graphicsOptions["REp13"]    = {"color": ROOT.kRed-7,     "marker": ROOT.kFullCircle}
graphicsOptions["REp22"]    = {"color": ROOT.kBlue,      "marker": ROOT.kFullSquare}
graphicsOptions["REp23"]    = {"color": ROOT.kBlue-7,    "marker": ROOT.kFullSquare}
graphicsOptions["REp32"]    = {"color": ROOT.kGreen,     "marker": ROOT.kFullDiamond}
graphicsOptions["REp33"]    = {"color": ROOT.kGreen-7,   "marker": ROOT.kFullDiamond}
graphicsOptions["REp42"]    = {"color": ROOT.kMagenta,   "marker": ROOT.kFullCross}
graphicsOptions["REp43"]    = {"color": ROOT.kMagenta-7, "marker": ROOT.kFullCross}

graphicsOptions["REm12"]    = {"color": ROOT.kRed,       "marker": ROOT.kOpenCircle}
graphicsOptions["REm13"]    = {"color": ROOT.kRed-7,     "marker": ROOT.kOpenCircle}
graphicsOptions["REm22"]    = {"color": ROOT.kBlue,      "marker": ROOT.kOpenSquare}
graphicsOptions["REm23"]    = {"color": ROOT.kBlue-7,    "marker": ROOT.kOpenSquare}
graphicsOptions["REm32"]    = {"color": ROOT.kGreen,     "marker": ROOT.kOpenDiamond}
graphicsOptions["REm33"]    = {"color": ROOT.kGreen-7,   "marker": ROOT.kOpenDiamond}
graphicsOptions["REm42"]    = {"color": ROOT.kMagenta,   "marker": ROOT.kOpenCross}
graphicsOptions["REm43"]    = {"color": ROOT.kMagenta-7, "marker": ROOT.kOpenCross}


graphicsOptions["all"]      = {"color": ROOT.kBlack,     "marker": ROOT.kFullCircle}
graphicsOptions["high"]     = {"color": ROOT.kGreen+1,   "marker": ROOT.kOpenCircle}
graphicsOptions["low"]      = {"color": ROOT.kRed,       "marker": ROOT.kOpenSquare}
graphicsOptions["prebeam"]  = {"color": ROOT.kAzure,     "marker": ROOT.kOpenTriangleUp}
graphicsOptions["abort"]    = {"color": ROOT.kMagenta+2, "marker": ROOT.kOpenTriangleDown}

graphicsOptions["inclusive"] = {"color": ROOT.kBlack,    "marker": ROOT.kFullCircle}
graphicsOptions["delayed"]   = {"color": ROOT.kRed,      "marker": ROOT.kOpenSquare}
graphicsOptions["prompt"]    = {"color": ROOT.kBlue,     "marker": ROOT.kFullSquare}
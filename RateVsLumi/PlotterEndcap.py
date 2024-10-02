import ROOT
from hist_settings import *

ROOT.gROOT.SetBatch()
f = ROOT.TFile.Open("RPC_fit.root")
fout = ROOT.TFile.Open("EndcapPlots.root", "RECREATE")


def plotter_endcap(name, region= "all",min = 10, maxim = 19):
        hit_hist_p = ROOT.TH1F(f.Get(name+"_"+region))
        hit_hist_m = ROOT.TH1F(f.Get(name.replace("Ep","Em")+"_"+region))
        fit_p = ROOT.TF1(f.Get(name+"_"+region+"_fit"))
        fit_m = ROOT.TF1(f.Get(name.replace("Ep","Em")+"_"+region+"_fit"))
        c = ROOT.TCanvas()
        ROOT.gStyle.SetOptStat(00000000)
        hit_hist_p.SetMarkerColor(ROOT.kBlue)                 
        hit_hist_m.SetMarkerColor(ROOT.kRed)
        hit_hist_p.SetLineColor(ROOT.kBlue)
        hit_hist_m.SetLineColor(ROOT.kRed)
        fit_p.SetLineColor(ROOT.kBlue)
        fit_m.SetLineColor(ROOT.kRed)
        hit_hist_p.GetYaxis().SetTitle("Hit Rate (Hz/cm^{2})")
        hit_hist_p.GetXaxis().SetTitle("Inst. Lumi")
        hit_hist_p.SetTitle("")
        hit_hist_p.Draw()
        hit_hist_p.GetXaxis().SetRangeUser(min,maxim)
        hit_hist_p.GetYaxis().SetRangeUser(0,max(hit_hist_p.GetMaximum(),hit_hist_m.GetMaximum())*1.5)
        hit_hist_m.Draw("same")
        fit_p.Draw("same")
        fit_m.Draw("same")
        l = ROOT.TLegend(0.16,0.63,0.38,0.87)
        l.AddEntry(fit_p,name)
        l.AddEntry(fit_m,name.replace("Ep","Em"))
        l.Draw()
        fout.cd()
        c.SetName(name.replace("Ep","E")+"_"+region)
        c.Write()
        c.SaveAs("/eos/home-f/fcarneva/ZB_2022_Scheme8148/"+name.replace("Ep","E")+"_"+region+".png")

regions = ["all","high","low","prebeam","abort"]
endcaps = ["REp12","REp13","REp22","REp23","REp32","REp33","REp42","REp43"]
for i in endcaps:
        for j in regions:
                plotter_endcap(i,j)


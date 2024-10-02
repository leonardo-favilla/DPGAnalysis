import ROOT
from hist_settings import *

ROOT.gROOT.SetBatch()

f2022 = ROOT.TFile.Open("RPC_fit.root")
f2023 = ROOT.TFile.Open("RPC_fit2023.root")


def compare(name, region="all", min=9, max=19):
        c = ROOT.TCanvas(name,name)
        hit_hist1 = ROOT.TH1F(f2022.Get(name+"_"+region))
        hit_hist1.SetName(name+"_"+region+"_2022")
        hit_hist2 = ROOT.TH1F(f2023.Get(name+"_"+region))
        hit_hist2.SetName(name+"_"+region+"_2023")
        fit_hist1 = ROOT.TF1(f2022.Get(name+"_"+region+"_fit"))                   
        fit_hist2 = ROOT.TF1(f2023.Get(name+"_"+region+"_fit"))
        hit_hist1.SetMarkerColor(ROOT.kRed)
        hit_hist1.SetLineColor(ROOT.kRed)
        fit_hist1.SetLineColor(ROOT.kRed)
        hit_hist1.SetMarkerStyle(8)

        hit_hist2.SetMarkerColor(ROOT.kBlue)
        hit_hist2.SetLineColor(ROOT.kBlue)
        fit_hist2.SetLineColor(ROOT.kBlue)
        hit_hist2.SetMarkerStyle(25)
        
        hit_hist1.Draw()
        fit_hist1.Draw("same")
        hit_hist2.Draw("same")
        fit_hist2.Draw("same")
        
        hit_hist1.GetXaxis().SetRangeUser(min,max)
        hit_hist1.GetYaxis().SetRangeUser(0,(hit_hist1.GetMaximum())*1.3)

        l = ROOT.TLegend(0.16,0.63,0.38,0.87)
        l.AddEntry(hit_hist1,"2022")
        l.AddEntry(hit_hist2,"2023")
        l.Draw()

        hit_hist1.GetXaxis().SetTitle("Inst. Lumi")
        hit_hist1.GetYaxis().SetTitle("Hit Rate (Hz/cm^{2})")
        hit_hist1.SetTitle(name+"_"+region)
        
        ROOT.gStyle.SetOptStat(00000000)

        c.SaveAs("/eos/home-f/fcarneva/ZB_2023_Scheme8754/plots/"+name+"_"+region+".png")
        c.SaveAs("/eos/home-f/fcarneva/ZB_2023_Scheme8754/plots/"+name+"_"+region+".C")


def compare2D(names, region="all"):
        c = ROOT.TCanvas()
        hist2D = ROOT.TH2D("hist2D","Barrel "+region,5,0.5,5.5,6,0.5,6.5)
        i=0.
        j=0
        for name in names:
                #i += 1
                j += 1
                if j==6: j = 1
                fit_hist1 = ROOT.TF1(f2022.Get(name+"_"+region+"_fit"))
                fit_hist2 = ROOT.TF1(f2023.Get(name+"_"+region+"_fit"))
                
                slope_22 = fit_hist1.GetParameter(1)
                slope_23 = fit_hist2.GetParameter(1)
                
                if fit_hist1.GetParameter(1)!=0: delta = (fit_hist1.GetParameter(1)-fit_hist2.GetParameter(1))/fit_hist1.GetParameter(1)*100
                else: delta = 0.
                print(j,i)
                hist2D.SetBinContent(j,int(i/5)+1,delta)
                i = i + 1
                

        ROOT.gStyle.SetOptStat(00000000)
        #hist2D.GetYaxis().SetLabelOffset(999)
        Ylabel = ["RB1in","RB1out","RB2in","RB2out","RB3","RB4"]
        for i in range(1,7):
                hist2D.GetYaxis().SetBinLabel(i,Ylabel[i-1])


        Xlabel = ["Wheel -2","Wheel -1","Wheel 0","Wheel +1","Wheel +2"]
        for i in range(1,6):
                hist2D.GetXaxis().SetBinLabel(i,Xlabel[i-1])
        hist2D.GetZaxis().SetRangeUser(-40,40)
        hist2D.Draw("COLZTEXT")
        c.SaveAs("/eos/home-f/fcarneva/ZB_2023_Scheme8754/plots/2DBarrel_"+region+".png")
        c.SaveAs("/eos/home-f/fcarneva/ZB_2023_Scheme8754/plots/2DBarrel_"+region+".C")        


def compare2D_Endcap(names, region="all"):
        c = ROOT.TCanvas()
        hist2D = ROOT.TH2D("hist2D","Endcap "+region,4,0.5,4.5,4,0.5,4.5)
        i=0.
        j=0
        for name in names:
                #i += 1
                j += 1
                if j==5: j = 1
                fit_hist1 = ROOT.TF1(f2022.Get(name+"_"+region+"_fit"))
                fit_hist2 = ROOT.TF1(f2023.Get(name+"_"+region+"_fit"))

                slope_22 = fit_hist1.GetParameter(1)
                slope_23 = fit_hist2.GetParameter(1)

                if fit_hist1.GetParameter(1)!=0: delta = (fit_hist1.GetParameter(1)-fit_hist2.GetParameter(1))/fit_hist1.GetParameter(1)*100
                else: delta = 0.
                print(j,i)
                hist2D.SetBinContent(j,int(i/4)+1,delta)
                i = i + 1


        ROOT.gStyle.SetOptStat(00000000)
        #hist2D.GetYaxis().SetLabelOffset(999)
        Ylabel = ["RE 1","RE 2","RE 3","RE 4"]
        for i in range(1,5):
                hist2D.GetYaxis().SetBinLabel(i,Ylabel[i-1])


        Xlabel = ["Ring 2 (Positive)","Ring 3 (Positive)","Ring 2 (Negative)","Ring 3 (Negative)",]
        for i in range(1,5):
                hist2D.GetXaxis().SetBinLabel(i,Xlabel[i-1])

        hist2D.GetZaxis().SetRangeUser(-40,40)
        hist2D.Draw("COLZTEXT")
        c.SaveAs("/eos/home-f/fcarneva/ZB_2023_Scheme8754/plots/2DEndcap_"+region+".png")
        c.SaveAs("/eos/home-f/fcarneva/ZB_2023_Scheme8754/plots/2DEndcap_"+region+".C")



regions = ["all","high","low","prebeam","abort"]
#for i in hist_dict.keys():
#        for j in regions:
#                compare(i,j)
 
for i in regions:
        compare2D(["Wm2_RB1in","Wm1_RB1in","W0_RB1in","Wp1_RB1in","Wp2_RB1in",
           "Wm2_RB1out","Wm1_RB1out","W0_RB1out","Wp1_RB1out","Wp2_RB1out",
           "Wm2_RB2in","Wm1_RB2in","W0_RB2in","Wp1_RB2in","Wp2_RB2in",
           "Wm2_RB2out","Wm1_RB2out","W0_RB2out","Wp1_RB2out","Wp2_RB2out",
           "Wm2_RB3","Wm1_RB3","W0_RB3","Wp1_RB3","Wp2_RB3",
                   "Wm2_RB4","Wm1_RB4","W0_RB4","Wp1_RB4","Wp2_RB4"], region= i)               

        compare2D_Endcap(["REp12","REp13","REm12","REm13",
                   "REp22","REp23","REm22","REm23",
                   "REp32","REp33","REm32","REm33",
                   "REp42","REp43","REm42","REm43"], region= i)


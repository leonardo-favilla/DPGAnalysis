import ROOT
import json
from hist_settings import *

ROOT.gROOT.SetBatch()
fill = 8754
if fill == 8754:
        f       = ROOT.TFile.Open("/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_8754/fileout.root")
        fout    = ROOT.TFile.Open("/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_8754/RPC_fit_F8754.root", "RECREATE")
        outJson = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_8754/RPC_fit_F8754_fitResults.json"
elif fill == 9573:
        f       = ROOT.TFile.Open("/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_9573_dead_and_noisy_noSectorRollSubdvision/fileout.root")
        fout    = ROOT.TFile.Open("/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_9573_dead_and_noisy_noSectorRollSubdvision/RPC_fit_F9573.root", "RECREATE")
        outJson = "/eos/user/l/lfavilla/RPC/post_RPC_Analyzer/Fill_9573_dead_and_noisy_noSectorRollSubdvision/RPC_fit_F9573_fitResults.json"
fitresults_json = {}

def fitter(name, region= "all", min = 9, max = 20):
        print(name+"_"+region)
        hit_hist = ROOT.TH1F(f.Get(name+"_"+region))
        nBX = 5
        if ("REp13" in name) or ("REm13" in name) or ("REp23" in name) or ("REm23" in name): nBX = 8
        string_name = "event_"+str(nBX)+"bx_"+ region
        print(string_name)
        event_hist = ROOT.TH1F(f.Get(string_name))
        event_hist.Sumw2()
        hit_hist.Sumw2()
        hit_hist.Divide(event_hist)
        if event_hist.GetEntries()>3:
                fout.cd()

                fit       = ROOT.TF1(name+"_"+region+"_fit","pol1", min, max) # pol1: y = p0 + p1*x
                fitResult = hit_hist.Fit(fit, "S0")
                hit_hist.SetName(name+"_"+region)

                fit.Write()
                hit_hist.SetOption()
                hit_hist.Write()

                
                # Confidence intervals #
                if int(fitResult) != 0:
                        print("Fit failed ---> Confidence intervals not calculated")
                else:
                        # save fit results in json #
                        fitresults_json[name+"_"+region]                = {}
                        fitresults_json[name+"_"+region]["p0"]          = fit.GetParameter(0)
                        fitresults_json[name+"_"+region]["p1"]          = fit.GetParameter(1)
                        fitresults_json[name+"_"+region]["p0_error"]    = fit.GetParError(0)
                        fitresults_json[name+"_"+region]["p1_error"]    = fit.GetParError(1)
                        fitresults_json[name+"_"+region]["chi2"]        = fitResult.Chi2()
                        fitresults_json[name+"_"+region]["ndf"]         = fitResult.Ndf()
                        covMatrix = fitResult.GetCovarianceMatrix()
                        fitresults_json[name+"_"+region]["covMatrix"]   = [
                                [covMatrix(0,0), covMatrix(0,1)],
                                [covMatrix(1,0), covMatrix(1,1)]
                        ]
                        # calculate confidence intervals #
                        tv = ROOT.TVirtualFitter.GetFitter()
                        if tv:
                                hit_hist_error = hit_hist.Clone(hit_hist.GetName()+"_error")
                                print(type(hit_hist_error))
                                hit_hist_error.SetName(hit_hist.GetName()+"_error")
                                hit_hist_error.SetTitle(hit_hist.GetTitle()+"_error")
                                tv.GetConfidenceIntervals(hit_hist_error,0.95)
                                hit_hist_error.SetStats(0)
                                # hit_hist_error.SetFillColorAlpha(ROOT.kGray, 0.5)
                                # hit_hist_error.SetFillStyle(3013)
                                hit_hist_error.SetOption("E3")
                                hit_hist_error.Write()



regions = ["all","high","low","prebeam","abort"]
for i in hist_dict.keys():
        for j in regions:
                fitter(i,j)
                print("\n")
                

fout.Close()


# Save fit results in json file #
with open(outJson, "w") as f:
        json.dump(fitresults_json, f, indent=4)
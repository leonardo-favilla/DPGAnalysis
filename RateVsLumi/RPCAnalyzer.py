import ROOT
import numpy as np
import pandas as pd
import uproot
#from  my_dict import *
import datetime
import sys

startTime = datetime.datetime.now()
print("Starting running at " + str(startTime))

ROOT.gROOT.SetBatch()

file_list = list(map(str, sys.argv[2].strip('[]').split(',')))
part = sys.argv[1]
fout = ROOT.TFile.Open("fileout" + part + ".root", "RECREATE")
df = uproot.concatenate([infile + ":demo/hit_tree" for infile in file_list], library="pd")#, cut = que)

if sys.argv[3] != "": list_from_txt = np.array(open(sys.argv[3],"r").read().split("\n")[:-1],dtype="float64")
else: 
        print("Missing Filling Scheme")
        list_from_txt = [None]

def add_fill_info(bx):
        if list_from_txt[0]==None: return -1
        else:
                if bx in list_from_txt: return 1 #Colliding region
                elif bx < list_from_txt[0]: return 3 # PreBeam
                elif bx > list_from_txt[-1]: return 4 #BeamAbort
                else: return 2 #NonColliding
df["coll_region"] = df.apply(lambda x: add_fill_info(x["bunchNum"]+x["RPCbx"]),axis = 1 )


def hit_hist(part, que =""):
        #df = uproot.concatenate([infile + ":demo/hit_tree" for infile in file_list], library="pd", cut = que) # filter_name=keys,
        #df["coll_region"] = df.apply(lambda x: add_fill_info(x["bunchNum"]+x["RPCbx"]),axis = 1 )
        #print(df.head(2882))
        nbin = 50
        rate = ROOT.TH1F("rate","rate", nbin, -0.5, nbin-0.5)
        #evt = ROOT.TH1F("evt","evt", nbin, -0.5, nbin-0.5)
        fout = ROOT.TFile.Open("fileout" + part + ".root", "RECREATE")
        for i in pd.unique(df['lumi']):
                #print("Filling bin " + str(i))
                df_lumi = df.loc[df["lumi"] == i ]
                #group_data = df_lumi.groupby(['runNum','eventNum'])
                rate.SetBinContent(int(i),len(df_lumi["lumi"].values))
                #evt.SetBinContent(int(i),len(group_data))
                
        area_tot = df.drop_duplicates(subset=['region','sector','layer','station','roll','subsector'])['area'].sum() #da valutare 
        #Attenzione MaNca Region!?
        #print(area_tot)
        rate.Sumw2()
        rate.Scale(1./(25e-9*area_tot))
        fout.cd()
        #evt.Write()
        rate.Write()

#rate_hist(df,"hist",que ="region==0 and ring==-2 and station ==1 and layer ==1 and sector!=10")
keys = "/(region|ring|station|layer|lumi|runNum|eventNum|roll|sector|subsector)/"
hit_hist(part, que ="(region==0) & (ring==-2) & (station ==1) & (layer ==1) & (sector!=10)")

endTime = datetime.datetime.now()
print("Ending running at " + str(endTime))


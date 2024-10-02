import ROOT
import numpy as np
import pandas as pd
import uproot
#from  my_dict import *
import datetime
import sys
from hist_settings import *
import json


startTime = datetime.datetime.now()
print("Starting running at " + str(startTime))

ROOT.gROOT.SetBatch()

file_list = list(map(str, sys.argv[2].strip('[]').split(',')))
part = sys.argv[1]
fout = ROOT.TFile.Open("fileout" + part + ".root", "RECREATE")


with open('All_Noisy_strips_ID.json', 'r') as file:
    ids = json.load(file)


lists = []
# Check if each key has a list with length greater than zero
for key, value in ids.items():
    if isinstance(value, list) and len(value) > 0: lists.append(key)

blacklist = np.array(lists)
que_ =""
for i in blacklist: que_=que_ + "(RPC_Id!="+i+") & "


df = uproot.concatenate([infile + ":demo/hit_tree" for infile in file_list], library="pd", cut = que_[:-2])
df_evt = uproot.concatenate([infile + ":demo/event_tree" for infile in file_list], library="pd")

print(que_)
print(df.columns)
print(df_evt.columns)



if sys.argv[3] != "": list_from_txt = np.array(open(sys.argv[3],"r").read().split("\n")[:-1],dtype="float64")
else: 
        print("Missing Filling Scheme")
        list_from_txt = [None]

def add_fill_info(bx):
        if list_from_txt[0]==None: return 0
        else:
                if bx in list_from_txt: return 1 #Colliding region
                elif bx < list_from_txt[0]: return 3 # PreBeam
                elif bx > list_from_txt[-1]: return 4 #BeamAbort
                else: return 2 #NonColliding
df["coll_region"] = df.apply(lambda x: add_fill_info(x["bunchNum"]+x["RPCbx"]),axis = 1 )
df_evt["coll_region"] = df_evt.apply(lambda x: add_fill_info(x["real_bunchNum"]),axis = 1 )

def hit_hist(name, que ="", coll_region=0):
        if coll_region!=0:df_ =df.query(que+" & coll_region=="+str(coll_region))
        else: df_=df.query(que)
        nbin = 50
        rate = ROOT.TH1F("rate","rate", nbin, -0.5, nbin-0.5)
        for i in pd.unique(df_evt['lumi']):
                df_lumi = df_.loc[df_["lumi"] == i]
                rate.SetBinContent(int(i),len(df_lumi["lumi"].values))
                
        area_tot = df_.drop_duplicates(subset=['region','sector','layer','station','roll','subsector'])['area'].sum() #da valutare 
        #Attenzione MaNca Region!?
        rate.Sumw2()
        if area_tot !=0 :
                rate.Scale(1./(25e-9*area_tot))
        rate.SetName(name)
        fout.cd()
        rate.Write()

def evt_hist(name, que=""):
        df_ =df_evt.query(que)
        nbin = 50
        evt = ROOT.TH1F("evt","evt", nbin, -0.5, nbin-0.5)
        for i in pd.unique(df_evt['lumi']):
                df_lumi = df_.loc[df_["lumi"] == i]
                evt.SetBinContent(int(i),len(df_lumi["lumi"].values))
        evt.SetName(name)
        fout.cd()
        evt.Write()

name_list = ["_all","_high","_low","_prebeam","_abort"]
keys = "/(region|ring|station|layer|lumi|runNum|eventNum|roll|sector|subsector)/"
#hit_hist(part, que ="(region==0) & (ring==-2) & (station ==1) & (layer ==1) & (sector!=10)")

event_queries = {"event_5bx_all":"RPCbx>=-2 & RPCbx<=2",
                 "event_8bx_all":"RPCbx>-5",
                 "event_5bx_high":"RPCbx>=-2 & RPCbx<=2 & coll_region==1",
                 "event_8bx_high":"RPCbx>-5 & coll_region==1",
                 "event_5bx_low":"RPCbx>=-2 & RPCbx<=2 & coll_region==2",
                 "event_8bx_low":"RPCbx>-5 & coll_region==2",
                 "event_5bx_prebeam":"RPCbx>=-2 & RPCbx<=2 & coll_region==3",
                 "event_8bx_prebeam":"RPCbx>-5 & coll_region==3",
                 "event_5bx_abort":"RPCbx>=-2 & RPCbx<=2 & coll_region==4",
                 "event_8bx_abort":"RPCbx>-5 & coll_region==4",
}

for h in range(0,5):
        print(h)
        for i in hist_dict.keys():
                print(i)
                hit_hist(i+name_list[h],que=hist_dict[i][0],coll_region=h)

for j in event_queries.keys():
        print(j)
        evt_hist(j,que=event_queries[j])

endTime = datetime.datetime.now()
print("Ending running at " + str(endTime))


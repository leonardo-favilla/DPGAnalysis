import json

fill              = 9573 # 8754-9573
inFilename_dead   = f"./crab/noisy_files/Fill_{fill}/All_Dead_strips_ID.json"
inFilename_noisy  = f"./crab/noisy_files/Fill_{fill}/All_Noisy_strips_ID.json"

outFilename       = f"./crab/noisy_files/Fill_{fill}/All_Dead_and_Noisy_strips_ID.txt"

if inFilename_dead!="":
    with open(inFilename_dead, "r") as f:
        inDict_dead   = json.load(f)

if inFilename_noisy!="":
    with open(inFilename_noisy, "r") as f:
        inDict_noisy  = json.load(f)



inDict = {}
if inFilename_dead!="" and inFilename_noisy!="":
    inDict.update(inDict_dead)
    for rpcId,strips in inDict_noisy.items():
        inDict[rpcId].extend(strips)
elif inFilename_dead!="" and inFilename_noisy=="":
    inDict.update(inDict_dead)
elif inFilename_dead=="" and inFilename_noisy!="":
    inDict.update(inDict_noisy)



lines_to_write = []
for rpcId,strips in inDict.items():
    if len(strips):
        strips = list(sorted([int(s.replace("strip_","")) for s in strips]))
        line   = str(rpcId) + "," + ",".join([str(s) for s in strips])
        lines_to_write.append("{}\n".format(line))

with open(outFilename, "w") as f:
    f.writelines(lines_to_write)
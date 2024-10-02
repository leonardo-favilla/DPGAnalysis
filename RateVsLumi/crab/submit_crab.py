import os
import optparse
import sys

usage = 'python3 submit_crab.py -d <jobname>'
parser = optparse.OptionParser(usage)
parser.add_option('-d', '--dat',    dest = 'dat',       type=str,   default = '',                           help = 'Please enter a dataset name')
parser.add_option('-s', '--sub',    dest = 'sub',                   default = False, action = 'store_true', help = 'Default do not submit')
parser.add_option('--status',       dest = 'status',                default = False, action = 'store_true', help = 'Default do not check the status')
parser.add_option('-k', '--kill',   dest = 'kill',                  default = False, action = 'store_true', help = 'Default do not kill')
parser.add_option('-r', '--resub',  dest = 'resub',                 default = False, action = 'store_true', help = 'Default do not resubmit')
parser.add_option('-g', '--gout',   dest = 'gout',                  default = False, action = 'store_true', help = 'Default do not do getoutput')
(opt, args) = parser.parse_args()

submit      = opt.sub
status      = opt.status
kill        = opt.kill
resubmit    = opt.resub
getout      = opt.gout


if submit:
    print("Submitting crab jobs...")
    print("crab submit -c CrabConf_RPCNtuplizer.py")
    os.system("crab submit -c CrabConf_RPCNtuplizer.py")

elif kill:
    print("Killing crab jobs...")
    os.system("crab kill -d crab_" + opt.dat)
    os.system("rm -rf crab_" + opt.dat)

elif resubmit:
    print("Resubmitting crab jobs...")
    os.system("crab resubmit -d crab_" + opt.dat)

elif status:
    print("Checking crab jobs status...")
    os.system("crab status -d crab_" + opt.dat)

elif getout:
    print("crab getoutput --xrootd -d crab_" + opt.dat + " > ../RPCNtuples/crab_" + opt.dat + ".txt")
    os.system("crab getoutput --xrootd -d crab_" + opt.dat + " > ../RPCNtuples/crab_" + opt.dat + ".txt")
    # print("crab getoutput --xrootd -d crab_" + opt.dat + " --jobids=1-500 > ./crab_" + opt.dat + ".txt")
    # os.system("crab getoutput --xrootd -d crab_" + opt.dat + " --jobids=1-500 > ./crab_" + opt.dat + ".txt")

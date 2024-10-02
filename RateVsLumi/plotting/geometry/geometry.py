############################
# infos about CMS geometry #
############################

##########
# BARREL #
##########
wheels                  = ["Wm2","Wm1","W0","Wp1","Wp2"]
RB1in                   = {}
RB1out                  = {}
RB2in                   = {}
RB2out                  = {}
RB3                     = {}
RB4                     = {}

for w in wheels:
    RB1in[w]            = {}               
    RB1out[w]           = {}              
    RB2in[w]            = {}               
    RB2out[w]           = {}              
    RB3[w]              = {}             
    RB4[w]              = {}
                 

RB1in["Wm2"]["eta"]     = -1.062382
RB1in["Wm1"]["eta"]     = -0.598404
RB1in["W0"]["eta"]      = 0.0069675
RB1in["Wp1"]["eta"]     = 0.598404
RB1in["Wp2"]["eta"]     = 1.062382

RB1out["Wm2"]["eta"]    = -1.000767
RB1out["Wm1"]["eta"]    = -0.55726
RB1out["W0"]["eta"]     = 0.006443001
RB1out["Wp1"]["eta"]    = 0.55726
RB1out["Wp2"]["eta"]    = 1.000767

RB2in["Wm2"]["eta"]     = -0.9292475
RB2in["Wm1"]["eta"]     = -0.5090627
RB2in["W0"]["eta"]      = 0.007250567
RB2in["Wp1"]["eta"]     = 0.5090627
RB2in["Wp2"]["eta"]     = 0.9292475

RB2out["Wm2"]["eta"]    = -0.8790133
RB2out["Wm1"]["eta"]    = -0.4797505
RB2out["W0"]["eta"]     = 0.0054795
RB2out["Wp1"]["eta"]    = 0.4797505
RB2out["Wp2"]["eta"]    = 0.8790133

RB3["Wm2"]["eta"]       = -0.790862
RB3["Wm1"]["eta"]       = -0.4245525
RB3["W0"]["eta"]        = 0.004812103
RB3["Wp1"]["eta"]       = 0.4245525
RB3["Wp2"]["eta"]       = 0.790862

RB4["Wm2"]["eta"]       = -0.68395
RB4["Wm1"]["eta"]       = -0.36125
RB4["W0"]["eta"]        = 0.000400003
RB4["Wp1"]["eta"]       = 0.36125
RB4["Wp2"]["eta"]       = 0.68395







##########
# ENDCAP #
##########
rolls                   = ["B","M","F"] # [A, B, C]
# negative side #
REm12                   = {}
REm13                   = {}
REm22                   = {}
REm23                   = {}
REm32                   = {}
REm33                   = {}
REm42                   = {}
REm43                   = {}
# positive side #
REp12                   = {}
REp13                   = {}
REp22                   = {}
REp23                   = {}
REp32                   = {}
REp33                   = {}
REp42                   = {}
REp43                   = {}


for r in rolls:
    REm12[r] = {}       
    REm13[r] = {}   
    REm22[r] = {}   
    REm23[r] = {}       
    REm32[r] = {}   
    REm33[r] = {}   
    REm42[r] = {}   
    REm43[r] = {}
       
    REp12[r] = {}
    REp13[r] = {}
    REp22[r] = {}
    REp23[r] = {}
    REp32[r] = {}
    REp33[r] = {}
    REp42[r] = {}
    REp43[r] = {}



##########
# disk 1 #
##########
# ring 3 #
REp13["B"]["eta"] = 0.9430065
REp13["M"]["eta"] = 1.015039
REp13["F"]["eta"] = 1.106885
# ring 2 #
REp12["B"]["eta"] = 1.288165
REp12["M"]["eta"] = 1.40005
REp12["F"]["eta"] = 1.57486


##########
# disk 2 #
##########
# ring 3 #
REp23["B"]["eta"] = 1.009115
REp23["M"]["eta"] = 1.09031
REp23["F"]["eta"] = 1.189005
# ring 2 #
REp22["B"]["eta"] = 1.303265
REp22["M"]["eta"] = 1.42126
REp22["F"]["eta"] = 1.544025


##########
# disk 3 #
##########
# ring 3 #
REp33["B"]["eta"] = 1.173555
REp33["M"]["eta"] = 1.260595
REp33["F"]["eta"] = 1.36549
# ring 2 #
REp32["B"]["eta"] = 1.48562
REp32["M"]["eta"] = 1.608545
REp32["F"]["eta"] = 1.7354


##########
# disk 4 #
##########
# ring 3 #
REp43["B"]["eta"] = 1.24778
REp43["M"]["eta"] = 1.33697
REp43["F"]["eta"] = 1.444095
# ring 2 #
REp42["B"]["eta"] = 1.56629
REp42["M"]["eta"] = 1.69092
REp42["F"]["eta"] = 1.819165



for r in rolls:
    REm12[r]["eta"] = -REp12[r]["eta"]
    REm13[r]["eta"] = -REp13[r]["eta"]
    REm22[r]["eta"] = -REp22[r]["eta"]
    REm23[r]["eta"] = -REp23[r]["eta"]
    REm32[r]["eta"] = -REp32[r]["eta"]
    REm33[r]["eta"] = -REp33[r]["eta"]
    REm42[r]["eta"] = -REp42[r]["eta"]
    REm43[r]["eta"] = -REp43[r]["eta"]




geometry_dict     = {
                        "RB1in"     : RB1in,
                        "RB1out"    : RB1out,
                        "RB2in"     : RB2in,
                        "RB2out"    : RB2out,
                        "RB3"       : RB3,
                        "RB4"       : RB4,
                        
                        "REp12"     : REp12,
                        "REp13"     : REp13,
                        "REp22"     : REp22,
                        "REp23"     : REp23,
                        "REp32"     : REp32,
                        "REp33"     : REp33,
                        "REp42"     : REp42,
                        "REp43"     : REp43,
                        
                        "REm12"     : REm12,
                        "REm13"     : REm13,
                        "REm22"     : REm22,
                        "REm23"     : REm23,
                        "REm32"     : REm32,
                        "REm33"     : REm33,
                        "REm42"     : REm42,
                        "REm43"     : REm43,
}
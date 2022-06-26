from sys import setdlopenflags
from ctypes import RTLD_GLOBAL
setdlopenflags (RTLD_GLOBAL | 2)

from members_component import Leg
from animal_component import Pet
p=Pet("medor chien")
l=Leg("front left")
l2=Leg("avant droite")
p.addLeg(l)
p.addLeg(l2)
p.to_json()

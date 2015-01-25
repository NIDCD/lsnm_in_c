# -*- coding: utf-8 -*-
"""
Fusion of LSNM and TVB

By: Antonio Ulloa, PhD

Adapted from TVB Tutorial 'Tutorial_Region_Stimuli'

Last modified: January 25, 2015
"""

# DO THE SETUP FIRST
from tvb.simulator import simulator
import tvb.simulator.models as models
import tvb.simulator.coupling as coupling
import tvb.simulator.integrators as integrators
import tvb.simulator.monitors as monitors
import tvb.datatypes.connectivity as connectivity

from tvb.simulator.plot.tools import *

import numpy as np
import matplotlib.pyplot as plt

import os

#Initialize model
oscillator = models.Generic2dOscillator()

#Initialize connectivity (brain with 74 regions)
white_matter = connectivity.Connectivity(load_default=True)
white_matter.speed = np.array([4.0])

#Initialize coupling
white_matter_coupling = coupling.Linear(a=0.0154)

#Initialise an Integrator
heunint = integrators.HeunDeterministic(dt=2**-6) 

#Initialise some Monitors with period in physical time
mon_raw = monitors.Raw()
mon_tavg = monitors.TemporalAverage(period=2**-2)
what_to_watch = (mon_raw, mon_tavg)

#Initialize a Simulator using the Model, Connectivity, Integrator, and Monitor defined above
sim = simulator.Simulator(model = oscillator, 
                          connectivity = white_matter,
                          coupling = white_matter_coupling, 
                          integrator = heunint, 
                          monitors = what_to_watch)

sim.configure()

#Run the simulation
raw_data = []
raw_time = []
tavg_data = []
tavg_time = []

for raw, tavg in sim(simulation_length=2**10):
    if not raw is None:
        raw_time.append(raw[0])
        raw_data.append(raw[1])
        
    if not tavg is None:
        tavg_time.append(tavg[0])    # TODO:The first [0] is a hack for single monitor
        tavg_data.append(tavg[1])    # TODO:The first [0] is a hack for single monitor


#Make the lists numpy.arrays for easier use.
RAW = np.array(raw_data)
TAVG = np.array(tavg_data)

print RAW.shape
print TAVG.shape

#Plot raw time series
plt.figure(1)
plt.plot(raw_time, RAW[:, 0, :, 0])
plt.title("Raw -- State variable 0")

plt.figure(2)
plt.plot(raw_time, RAW[:, 1, :, 0])
plt.title("Raw -- State variable 1")

#Plot temporally averaged time series
plt.figure(3)
plt.plot(tavg_time, TAVG[:, 0, :, 0])
plt.title("Temporal average")

#Plot connectivity
plot_connectivity(white_matter)

#Show them
plt.show()


###EoF###
                                            

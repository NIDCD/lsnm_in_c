# ============================================================================
#
#                            PUBLIC DOMAIN NOTICE
#
#       National Institute on Deafness and Other Communication Disorders
#
# This software/database is a "United States Government Work" under the 
# terms of the United States Copyright Act. It was written as part of 
# the author's official duties as a United States Government employee and 
# thus cannot be copyrighted. This software/database is freely available 
# to the public for use. The NIDCD and the U.S. Government have not placed 
# any restriction on its use or reproduction. 
#
# Although all reasonable efforts have been taken to ensure the accuracy 
# and reliability of the software and data, the NIDCD and the U.S. Government 
# do not and cannot warrant the performance or results that may be obtained 
# by using this software or data. The NIDCD and the U.S. Government disclaim 
# all warranties, express or implied, including warranties of performance, 
# merchantability or fitness for any particular purpose.
#
# Please cite the author in any work or product based on this material.
# 
# ==========================================================================



# ***************************************************************************
#
#   Large-Scale Neural Modeling software (LSNM)
#
#   Section on Brain Imaging and Modeling
#   Voice, Speech and Language Branch
#   National Institute on Deafness and Other Communication Disorders
#   National Institutes of Health
#
#   This file (simulate_Wilson_Cowan_Brain_74_nodes.py) was created on 01/29/15,
#   based on 'generate_region_demo_data.py' by Stuart A. Knock and
#            'region_deterministic_bnm_wc.py' by Paula Sanz-Leon
#
#   This program makes use of The Virtual Brain library toolbox, downloaded
#   from the TVB GitHub page.
#
#   Author: Antonio Ulloa. Last updated by Antonio Ulloa on January 31 2015  
# **************************************************************************/
#
# simulate_Wilson_Cowan_Brain_74_nodes.py
#
# Simulates resting brain activity using Wilson Cowan model and 74 nodes.
# The activation of state variable E and I are collected at each time step
# of the simulation and are written out to a data file that can be accessed
# later.
#

from tvb.simulator.lab import *

# white matter transmission speed in mm/ms
speed = 4.0

# define length of simulation in ms
simulation_length = 6500

# define global coupling strength as in Sanz-Leon (2015) Neuroimage paper
# figure 17 3rd column 3rd row
global_coupling_strength = 0.0042

# Define the population model to be used and state variables to be collected
# the parameters are same as those used by Sanz-Leon (2015) Neuroimage article,
# as shown in table 11 case 'c'
WC = models.WilsonCowan(variables_of_interest=['E','I'],
                        c_ee=16, c_ei=12, c_ie=15, c_ii=3,
                        tau_e=8, tau_i=8, a_e=1.3, a_i=2,
                        b_e=4, b_i=3.7, P=1.25)

# Define connectivity to be used (74 ROI matrix from TVB demo set)
white_matter = connectivity.Connectivity(load_default=True)

# Define the transmission speed of white matter tracts (4 mm/ms)
white_matter.speed = numpy.array([speed])

# Define the coupling function between white matter tracts and brain regions
white_matter_coupling = coupling.Linear(a=global_coupling_strength)

# Define noise and integrator to be used
heunint = integrators.HeunDeterministic(dt=2**-4)

# Define a monitor to be used (i.e., simulated data to be collected)
#what_to_watch = monitors.Raw(variables_of_interest=['E','I'])
what_to_watch = monitors.SubSample(period=5.0)

# Initialise a Simulator -- Model, Connectivity, Integrator, and Monitors.
sim = simulator.Simulator(model=WC, connectivity=white_matter,
                          coupling=white_matter_coupling,
                          integrator=heunint, monitors=what_to_watch)

sim.configure()

# Run the simulation
raw_data = []
raw_time = []
for raw in sim(simulation_length=simulation_length):
    if raw is not None:
        raw_time.append(raw[0][0]) 
        raw_data.append(raw[0][1])
        print numpy.array(raw[0][1]).shape

# Convert data list to a numpy array
RawData = numpy.array(raw_data)

# write output dimension to the console
print RawData.shape

# Save the array to a file for future use
FILE_NAME = "wilson_cowan_brain_74_nodes.npy"
numpy.save(FILE_NAME, RawData)

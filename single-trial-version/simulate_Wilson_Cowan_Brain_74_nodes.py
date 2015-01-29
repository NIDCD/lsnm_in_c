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
#   based on 'generate_region_demo_data by Stuart A. Knock (part of the
#   The Virtual Brain team).
#
#   This program makes use of The Virtual Brain library toolbox, downloaded
#   from the TVB GitHub page.
#
#   Author: Antonio Ulloa. Last updated by Antonio Ulloa on January 29 2015  
# **************************************************************************/
#
# simulate_Wilson_Cowan_Brain.74_nodes.py
#
# Simulates resting brain activity using Wilson Cowan units and 74 nodes.

from tvb.simulator.lab import *


WC = models.WilsonCowan()

white_matter = connectivity.Connectivity(load_default=True)
white_matter.speed = numpy.array([4.0])
white_matter_coupling = coupling.Linear(a=0.033)

#Initialize Integrator
hiss = noise.Additive(nsig=numpy.array([2 ** -10, ]))
heunint = integrators.HeunStochastic(dt=0.06103515625, noise=hiss) 

#Initialise a Monitor with period in physical time
what_to_watch = monitors.Raw()

#Initialise a Simulator -- Model, Connectivity, Integrator, and Monitors.
sim = simulator.Simulator(model=WC, connectivity=white_matter,
                          coupling=white_matter_coupling,
                          integrator=heunint, monitors=what_to_watch)

sim.configure()

#Perform the simulation
raw_data = []
raw_time = []
LOG.info("Starting simulation...")
for raw in sim(simulation_length=5500):
    if raw is not None:
        raw_time.append(raw[0][0])    # TODO:The first [0] is a hack for single monitor
        raw_data.append(raw[0][1])    # TODO:The first [0] is a hack for single monitor


#Make the list a numpy.array.
RAW = numpy.array(raw_data)

#Save it
FILE_NAME = "wilson_cowan_brain_74_nodes.npy"
LOG.info("Saving array to %s..." % FILE_NAME)
numpy.save(FILE_NAME, RAW)

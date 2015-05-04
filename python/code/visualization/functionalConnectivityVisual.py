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
#   This file (functionalConnectivityVisual.py) was created on May 4, 2015.
#
#
#   Author: Antonio Ulloa
#
#   Last updated by Antonio Ulloa on May 4 2015  
# **************************************************************************/

# functionalConnectivityVisual.py
#
# Calculate and plot functional connectivity (within-task time series correlation)
# of IT with all other simulated brain areas, using the output 
# from visual DMS task (synaptic activity and BOLD activity time series)

import numpy as np
import matplotlib.pyplot as plt

import math as m

# Load V1 synaptic activity data files into a numpy array
ev1h = np.loadtxt('../../output/ev1h_synaptic.out')
ev1v = np.loadtxt('../../output/ev1v_synaptic.out')
iv1h = np.loadtxt('../../output/iv1h_synaptic.out')
iv1v = np.loadtxt('../../output/iv1v_synaptic.out')

# Load V4 synaptic activity data files into a numpy array
ev4h = np.loadtxt('../../output/ev4h_synaptic.out')
ev4v = np.loadtxt('../../output/ev4v_synaptic.out')
ev4c = np.loadtxt('../../output/ev4c_synaptic.out')
iv4h = np.loadtxt('../../output/iv4h_synaptic.out')
iv4v = np.loadtxt('../../output/iv4v_synaptic.out')
iv4c = np.loadtxt('../../output/iv4c_synaptic.out')

# Load IT synaptic activity data files into a numpy array
exss = np.loadtxt('../../output/exss_synaptic.out')
inss = np.loadtxt('../../output/inss_synaptic.out')

# Load D1 synaptic activity data files into a numpy array
efd1 = np.loadtxt('../../output/efd1_synaptic.out')
ifd1 = np.loadtxt('../../output/ifd1_synaptic.out')

# Load D2 synaptic activity data files into a numpy array
efd2 = np.loadtxt('../../output/efd2_synaptic.out')
ifd2 = np.loadtxt('../../output/ifd2_synaptic.out')

# Load FS synaptic activity data files into a numpy array
exfs = np.loadtxt('../../output/exfs_synaptic.out')
infs = np.loadtxt('../../output/infs_synaptic.out')

# Load FR synaptic activity data files into a numpy array
exfr = np.loadtxt('../../output/exfr_synaptic.out')
infr = np.loadtxt('../../output/infr_synaptic.out')

# add all units within each region (V1, IT, and D1) together across space to calculate
# synaptic activity in each brain region
v1 = np.sum(ev1h + ev1v + iv1h + iv1v, axis = 1)
v4 = np.sum(ev4h + ev4v + ev4c + iv4h + iv4v + iv4c, axis = 1)
it = np.sum(exss + inss, axis = 1)
d1 = np.sum(efd1 + ifd1, axis = 1)
d2 = np.sum(efd2 + ifd2, axis = 1)
fs = np.sum(exfs + infs, axis = 1)
fr  = np.sum(exfr + infr, axis = 1)

# Gets rid of the control trials in the synaptic activity arrays,
# by separating the task-related trials and concatenating them
# together. Remember that each trial is 440 synaptic timesteps
# long
print v1.shape

# Set up figure to plot synaptic activity
plt.figure(1)

plt.suptitle('FUNCTIONAL CONNECTIVITY OF IT WITH ALL OTHER BRAIN REGIONS')

# Plot V1 module
plt.plot(v1)
plt.plot(v4)
plt.plot(it)
plt.plot(d1)
plt.plot(d2)
plt.plot(fs)
plt.plot(fr)

# Show the plot on the screen
plt.show()

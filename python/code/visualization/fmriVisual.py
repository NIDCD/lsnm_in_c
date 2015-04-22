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
#   This file (fmriVisual.py) was created on April 17, 2015.
#
#
#   Author: Antonio Ulloa. Last updated by Antonio Ulloa on April 17 2015  
# **************************************************************************/

# fmriVisual.py
#
# Calculate and plot fMRI BOLD signal based on data from visual
# delay-match-to-sample simulation

import numpy as np
import matplotlib.pyplot as plt

import math as m

from scipy.stats import poisson

# define constants needed for hemodynamic function
lambda_ = 4.0

# given the number of total timesteps, calculate total time of scanning
# experiment in seconds
T = 22

# Time for one complete trial
Ttrial = 5.5

# define neural synaptic time interval and total time of scanning
# experiment (units are seconds)
Ti = .004 * 10

# the scanning happened every Tr interval below (in seconds). This
# is the time needed to sample hemodynamic activity to produce
# each fMRI image.
Tr = 2

# Load V1 synaptic activity data files into a numpy array
ev1h = np.loadtxt('../../output/ev1h_synaptic.out')
ev1v = np.loadtxt('../../output/ev1v_synaptic.out')
iv1h = np.loadtxt('../../output/iv1h_synaptic.out')
iv1v = np.loadtxt('../../output/iv1v_synaptic.out')

# Load IT synaptic activity data files into a numpy array
exss = np.loadtxt('../../output/exss_synaptic.out')
inss = np.loadtxt('../../output/inss_synaptic.out')

# Load D1 synaptic activity data files into a numpy array
efd1 = np.loadtxt('../../output/efd1_synaptic.out')
ifd1 = np.loadtxt('../../output/ifd1_synaptic.out')


# Extract number of timesteps from one of the matrices
timesteps = ev1h.shape[0]


# Given neural synaptic time interval and total time of scanning experiment,
# construct a numpy array of time points (data points provided in data files)
t = np.arange(0, T, Tr)

# the following calculates a Poisson distribution (that will represent a hemodynamic
# function, given lambda (the Poisson time constant characterizing width and height
# of hemodynamic function), and tau (the time step)
#h = Lambda ** tau * m.exp(-Lambda) / m.factorial(tau)
h = poisson.pmf(t, lambda_)

# the following calculates the impulse response (convolution kernel) of the gamma
# function, approximating the BOLD response (Boynton model).

#a = (t - 2.5) / 1.25

#a = a.clip(min=0)

#h = [(x ** (3-1) * m.exp(-x)) / (1.25 * m.factorial(3-1)) for x in a]

#h = np.asarray(h)

plt.figure(1)
plt.plot(h)

# add all units within each region (V1, IT, and D1) together across space to calculate
# synaptic activity in each brain region
v1 = np.sum(ev1h + ev1v + iv1h + iv1v, axis = 1)
it = np.sum(exss + inss, axis = 1)
d1 = np.sum(efd1 + ifd1, axis = 1)

# now, we need to convolve the synaptic activity with a hemodynamic delay
# function and sample the array at Tr regular intervals

BOLD_interval = np.arange(0, T, Tr)

v1_BOLD = np.convolve(v1, h, mode='valid')[BOLD_interval]
it_BOLD = np.convolve(it, h, mode='valid')[BOLD_interval]
d1_BOLD = np.convolve(d1, h, mode='valid')[BOLD_interval]

print v1_BOLD.size

# Set up figure to plot synaptic activity
plt.figure(2)

plt.suptitle('SIMULATED SYNAPTIC ACTIVITY')

# Plot V1 module
plt.plot(v1)
plt.plot(it)
plt.plot(d1)

# Set up second figure to plot fMRI BOLD signal
plt.figure(3)

plt.suptitle('SIMULATED fMRI BOLD SIGNAL')

plt.plot(v1_BOLD)
plt.plot(it_BOLD)
plt.plot(d1_BOLD)

# Show the plot on the screen
plt.show()
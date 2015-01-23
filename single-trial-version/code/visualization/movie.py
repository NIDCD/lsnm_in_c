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
#   This file (movie.py) was created on December January 22, 2015.
#
#
#   Author: Antonio Ulloa. Last updated by Antonio Ulloa on January 22 2015  
# **************************************************************************/

# movie.py
#
# Plays a movie using output data files of visual delay-match-to-sample simulation

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button, RadioButtons

# Load data files
lgns = np.loadtxt('../../output/lgns.out')
efd1 = np.loadtxt('../../output/efd1.out')
efd2 = np.loadtxt('../../output/efd2.out')
ev1h = np.loadtxt('../../output/ev1h.out')
ev1v = np.loadtxt('../../output/ev1v.out')
ev4c = np.loadtxt('../../output/ev4c.out')
ev4h = np.loadtxt('../../output/ev4h.out')
ev4v = np.loadtxt('../../output/ev4v.out')
exfr = np.loadtxt('../../output/exfr.out')
exfs = np.loadtxt('../../output/exfs.out')
exss = np.loadtxt('../../output/exss.out')

# extract number of timesteps from one of the matrices
timesteps = lgns.shape[0]

# This is the dimension of each module i.e., dxd = 9x9
d=9

lgn = lgns.reshape(timesteps,d,d)
v1h = ev1h.reshape(timesteps,d,d)
v1v = ev1v.reshape(timesteps,d,d)
v4h = ev4h.reshape(timesteps,d,d)
v4c = ev4c.reshape(timesteps,d,d)
v4v = ev4v.reshape(timesteps,d,d)
ss  = exss.reshape(timesteps,d,d)
fd1 = efd1.reshape(timesteps,d,d)
fd2 = efd2.reshape(timesteps,d,d)
fs  = exfs.reshape(timesteps,d,d)
fr  = exfr.reshape(timesteps,d,d)

fig = plt.figure(1)

# Render LGN array in a colormap
plt.subplot(3,6,7)
plt.imshow(lgn[0,:,:])

# Render EV1h array in a colormap
plt.subplot(3,6,14)
plt.imshow(v1h[0,:,:])

# Render EV1v array in a colormap
plt.subplot(3,6,2)
plt.imshow(v1v[0,:,:])

# Render array in a colormap
plt.subplot(3,6,3)
plt.imshow(v4h[0,:,:])

# Render array in a colormap
plt.subplot(3,6,9)
plt.imshow(v4c[0,:,:])

# Render array in a colormap
plt.subplot(3,6,15)
plt.imshow(v4v[0,:,:])

# Render array in a colormap
plt.subplot(3,6,10)
plt.imshow(ss[0,:,:])

# Render array in a colormap
plt.subplot(3,6,5)
plt.imshow(fs[0,:,:])

# Render array in a colormap
plt.subplot(3,6,11)
plt.imshow(fd1[0,:,:])

# Render array in a colormap
plt.subplot(3,6,17)
plt.imshow(fd2[0,:,:])

# Render array in a colormap
plt.subplot(3,6,12)
plt.imshow(fr[0,:,:])

# now draw interactive slider
axtimesteps = plt.axes([0.25, 0.1, 0.65, 0.03])

stimesteps = Slider(axtimesteps, 'TimeSteps', 0, 219, valinit=0)

# now define the function that updates plots as slider is moved
def update(val):
    timesteps = stimesteps.val

    plt.subplot(3,6,7)
    plt.imshow(lgn[timesteps,:,:])
    
    plt.subplot(3,6,14)
    plt.imshow(v1h[timesteps,:,:])
    
    plt.subplot(3,6,2)
    plt.imshow(v1v[timesteps,:,:])
    
    plt.subplot(3,6,3)
    plt.imshow(v4h[timesteps,:,:])
    
    plt.subplot(3,6,9)
    plt.imshow(v4c[timesteps,:,:])
    
    plt.subplot(3,6,15)
    plt.imshow(v4v[timesteps,:,:])
    
    plt.subplot(3,6,10)
    plt.imshow(ss[timesteps,:,:])
    
    plt.subplot(3,6,5)
    plt.imshow(fs[timesteps,:,:])
    
    plt.subplot(3,6,11)
    plt.imshow(fd1[timesteps,:,:])
    
    plt.subplot(3,6,17)
    plt.imshow(fd2[timesteps,:,:])
    
    plt.subplot(3,6,12)
    plt.imshow(fr[timesteps,:,:])
    
stimesteps.on_changed(update)

# Show the plot on the screen
plt.show()

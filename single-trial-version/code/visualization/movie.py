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

plt.figure(1)

print lgns.shape

# Render LGN array in a colormap
ax = plt.subplot(3,6,7)
lgn = lgns[0]
img = plt.imshow(lgn.reshape(9,9))
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render EV1h array in a colormap
ax=plt.subplot(3,6,14)
ev1h = ev1h[0]
ev1h = ev1h.reshape(9, 9)
img = plt.imshow(ev1h)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render EV1v array in a colormap
ax=plt.subplot(3,6,2)
ev1v = ev1v[0]
ev1v = ev1v.reshape(9, 9)
img = plt.imshow(ev1v)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(3,6,3)
ev4h = ev4h[0]
ev4h = ev4h.reshape(9, 9)
img = plt.imshow(ev4h)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(3,6,9)
ev4c = ev4c[0]
ev4c = ev4c.reshape(9, 9)
img = plt.imshow(ev4c)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(3,6,15)
ev4v = ev4v[0]
ev4v = ev4v.reshape(9, 9)
img = plt.imshow(ev4v)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(3,6,10)
exss = exss[0]
exss = exss.reshape(9, 9)
img = plt.imshow(exss)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(3,6,5)
exfs = exfs[0]
exfs = exfs.reshape(9, 9)
img = plt.imshow(exfs)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(3,6,11)
efd1 = efd1[0]
efd1 = efd1.reshape(9, 9)
img = plt.imshow(efd1)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(3,6,17)
efd2 = efd2[0]
efd2 = efd2.reshape(9, 9)
img = plt.imshow(efd2)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(3,6,12)
exfr = exfr[0]
exfr = exfr.reshape(9, 9)
img = plt.imshow(exfr)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# now draw interactive slider
axtimesteps = plt.axes([0.25, 0.1, 0.65, 0.03])

stimesteps = Slider(axtimesteps, 'TimeSteps', 0, 219, valinit=0)

def update(val):
    timesteps = stimesteps.val

    ax = plt.subplot(3,6,7)
    lgn = lgns[timesteps]
    img = plt.imshow(lgn.reshape(9,9))
    img.set_cmap('hot')
    ax.set_xticks([])
    ax.set_yticks([])

    ax=plt.subplot(3,6,14)
    v1h = ev1h[timesteps]
    img = plt.imshow(v1h.reshape(9,9))
    img.set_cmap('hot')
    ax.set_xticks([])
    ax.set_yticks([])

    ax=plt.subplot(3,6,2)
    v1v = ev1v[timesteps]
    img = plt.imshow(ev1v)
    img.set_cmap('hot')
    ax.set_xticks([])
    ax.set_yticks([])

    ax=plt.subplot(3,6,3)
    v4h = ev4h[timesteps]
    img = plt.imshow(ev4h)
    img.set_cmap('hot')
    ax.set_xticks([])
    ax.set_yticks([])

    ax=plt.subplot(3,6,9)
    v4c = ev4c[timesteps]
    img = plt.imshow(v4c.reshape(9,9))
    img.set_cmap('hot')
    ax.set_xticks([])
    ax.set_yticks([])

    ax=plt.subplot(3,6,15)
    v4v = ev4v[timesteps]
    img = plt.imshow(v4v.reshape(9,9))
    img.set_cmap('hot')
    ax.set_xticks([])
    ax.set_yticks([])

    ax=plt.subplot(3,6,10)
    ss = exss[timesteps]
    img = plt.imshow(ss.reshape(9,9))
    img.set_cmap('hot')
    ax.set_xticks([])
    ax.set_yticks([])

    ax=plt.subplot(3,6,5)
    fs = exfs[timesteps]
    img = plt.imshow(fs.reshape(9,9))
    img.set_cmap('hot')
    ax.set_xticks([])
    ax.set_yticks([])

    ax=plt.subplot(3,6,11)
    fd1 = efd1[timesteps]
    img = plt.imshow(fd1.reshape(9,9))
    img.set_cmap('hot')
    ax.set_xticks([])
    ax.set_yticks([])

    ax=plt.subplot(3,6,17)
    fd2 = efd2[timesteps]
    img = plt.imshow(fd2.reshape(9,9))
    img.set_cmap('hot')
    ax.set_xticks([])
    ax.set_yticks([])

    ax=plt.subplot(3,6,12)
    fr = exfr[timesteps]
    img = plt.imshow(fr.reshape(9,9))
    img.set_cmap('hot')
    ax.set_xticks([])
    ax.set_yticks([])

stimesteps.on_changed(update)

# Show the plot on the screen
plt.show()

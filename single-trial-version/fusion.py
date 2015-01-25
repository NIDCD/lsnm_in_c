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
#   This file (fusion.py) was created on January 24 2015.
#   
#   Author: Antonio Ulloa
#
#   Last updated by Antonio Ulloa on January 24 2015  
# **************************************************************************/

# fusion.py
#
# loads a TVB network and uses it to provide inputs to an LSNM network

from tvb.simulator.lab import *

import tvb.datatypes.time_series

from tvb.simulator.plot.tools import *

import tvb.simulator.plot.timeseries_interactive as ts_int

from matplotlib.widgets import Slider

import numpy as np

import os

########## THE FOLLOWING SIMULATES TVB NETWORK'S #######################
RAW = np.load("demo_raw_data_region_5.5s_2048Hz.npy")

print RAW.shape

# sample TVB RAW activity file to extract 220 data points
RAW = RAW[::410]    # round(90112 / 220) = 410 

print RAW.shape

print RAW

white_matter = connectivity.Connectivity(load_default=True)

print white_matter.weights[73]

print white_matter.region_labels

white_matter.configure()

######### THE FOLLOWING SIMULATES LSNM NETWORK ########################
# Define input file (i.e., network creation parameters)
network = 'pethi1'

# Define simulation command
cmd = 'bin/sim1' + ' ' + network

# Execute simulation
os.system(cmd)

# Now move output files to the output directory
os.rename('spec_pet.m', 'output/spec_pet.m')

for file in os.listdir('.'):
    if file.endswith('.out'):
        os.rename(file, 'output/'+file)

########## NOW DISPLAY LSNM SIMULATED NEURAL ACTIVITY ##################
#import matplotlib as plt

# Load data files
lgns = np.loadtxt('output/lgns.out')
efd1 = np.loadtxt('output/efd1.out')
efd2 = np.loadtxt('output/efd2.out')
ev1h = np.loadtxt('output/ev1h.out')
ev1v = np.loadtxt('output/ev1v.out')
ev4c = np.loadtxt('output/ev4c.out')
ev4h = np.loadtxt('output/ev4h.out')
ev4v = np.loadtxt('output/ev4v.out')
exfr = np.loadtxt('output/exfr.out')
exfs = np.loadtxt('output/exfs.out')
exss = np.loadtxt('output/exss.out')

# Extract number of timesteps from one of the matrices
timesteps = lgns.shape[0]

# Contruct a numpy array of timesteps (data points provided in data file)
t = np.arange(0, timesteps, 1)

# Set up plot
figure('LARGE SCALE NEURAL MODEL (LSNM)')

suptitle('SIMULATED NEURAL ACTIVITY')

# Plot LGN module
ax = subplot(11,1,1)
ax.plot(t, lgns)
ax.set_xticks([])
ax.set_yticks([])
ax.set_xlim(0,timesteps)
ylabel('LGN', rotation='horizontal', horizontalalignment='right')

# Plot V1 module
ax = subplot(11,1,2)
ax.plot(t, ev1h)
ax.set_xticks([])
ax.set_yticks([])
ax.set_xlim(0,timesteps)
ylabel('V1h', rotation='horizontal', horizontalalignment='right')

ax = subplot(11,1,3)
ax.plot(t, ev1v)
ax.set_xticks([])
ax.set_yticks([])
ax.set_xlim(0,timesteps)
ylabel('V1v', rotation='horizontal', horizontalalignment='right')

# Plot V4 module
ax = subplot(11,1,4)
ax.plot(t, ev4h)
ax.set_xticks([])
ax.set_yticks([])
ax.set_xlim(0,timesteps)
ylabel('V4h', rotation='horizontal', horizontalalignment='right')

ax = subplot(11,1,5)
ax.plot(t, ev4c)
ax.set_xticks([])
ax.set_yticks([])
ax.set_xlim(0,timesteps)
ylabel('V4c', rotation='horizontal', horizontalalignment='right')

ax = subplot(11,1,6)
ax.plot(t, ev4v)
ax.set_xticks([])
ax.set_yticks([])
ax.set_xlim(0,timesteps)
ylabel('V4v', rotation='horizontal', horizontalalignment='right')

# Plot IT module
ax = subplot(11,1,7)
ax.plot(t, exss)
ax.set_xticks([])
ax.set_yticks([])
ax.set_xlim(0,timesteps)
ylabel('IT', rotation='horizontal', horizontalalignment='right')

# Plot PFC modules FS, FD1, and FD2
ax = subplot(11,1,8)
ax.plot(t, exfs)
ax.set_xticks([])
ax.set_yticks([])
ax.set_xlim(0,timesteps)
ylabel('FS', rotation='horizontal', horizontalalignment='right')

ax = subplot(11,1,9)
ax.plot(t, efd1)
ax.set_xticks([])
ax.set_yticks([])
ax.set_xlim(0,timesteps)
ylabel('D1', rotation='horizontal', horizontalalignment='right')

ax = subplot(11,1,10)
ax.plot(t, efd2)
ax.set_xticks([])
ax.set_yticks([])
ax.set_xlim(0,timesteps)
ylabel('D2', rotation='horizontal', horizontalalignment='right')

# Plot FR (Response module)
ax = subplot(11,1,11)
ax.plot(t, exfr)
ax.set_yticks([])
ax.set_xlim(0,timesteps)
ylabel('R', rotation='horizontal', horizontalalignment='right')
xlabel('Timesteps (i.e., Data points)')

# Extract number of timesteps from one of the matrices
timesteps = lgns.shape[0]

# Initialize the dimension of each module i.e., dxd = 9x9
d=9

# Reshape all matrices to reflect dimensionality of visual modules
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

fig = figure('LARGE-SCALE NEURAL MODEL (LSNM)')

suptitle('SIMULATED NEURAL ACTIVITY')

# Render LGN array in a colormap
subplot(3,4,1)
imshow(lgn[0,:,:], vmin=0, vmax=1, cmap='hot')
title('LGN')
axis('off')

# Render EV1h array in a colormap
subplot(3,4,5)
imshow(v1h[0,:,:], vmin=0, vmax=1, cmap='hot')
title('V1h')
axis('off')

# Render EV1v array in a colormap
subplot(3,4,9)
imshow(v1v[0,:,:], vmin=0, vmax=1, cmap='hot')
title('V1v')
axis('off')

# Render array in a colormap
subplot(3,4,2)
imshow(v4h[0,:,:], vmin=0, vmax=1, cmap='hot')
title('V4h')
axis('off')

# Render array in a colormap
subplot(3,4,6)
imshow(v4c[0,:,:], vmin=0, vmax=1, cmap='hot')
title('V4c')
axis('off')

# Render array in a colormap
subplot(3,4,10)
imshow(v4v[0,:,:], vmin=0, vmax=1, cmap='hot')
title('V4v')
axis('off')

# Render array in a colormap
subplot(3,4,3)
imshow(ss[0,:,:], vmin=0, vmax=1, cmap='hot')
title('IT')
axis('off')

# Render array in a colormap
subplot(3,4,7)
imshow(fs[0,:,:], vmin=0, vmax=1, cmap='hot')
title('FS')
axis('off')

# Render array in a colormap
subplot(3,4,11)
imshow(fd1[0,:,:], vmin=0, vmax=1, cmap='hot')
title('FD1')
axis('off')

# Render array in a colormap
subplot(3,4,4)
imshow(fd2[0,:,:], vmin=0, vmax=1, cmap='hot')
title('FD2')
axis('off')

# Render array in a colormap
subplot(3,4,8)
imshow(fr[0,:,:], vmin=0, vmax=1, cmap='hot')
title('FR')
axis('off')

# Display reference colorbar [left, bottom, width, height]
cbaxes = fig.add_axes([0.92, 0.1, 0.03, 0.8])
cb = colorbar(cax=cbaxes)

# now draw interactive slider at [x, y, length, width]   
axtimesteps = axes([0.1, 0, 0.8, 0.03])

stimesteps = Slider(axtimesteps, 'Slider', 0, timesteps-1, valinit=0)

# now define the function that updates plots as slider is moved
def update(val):
    timesteps = stimesteps.val

    subplot(3,4,1)
    imshow(lgn[timesteps,:,:], vmin=0, vmax=1, cmap='hot')
    
    subplot(3,4,5)
    imshow(v1h[timesteps,:,:], vmin=0, vmax=1, cmap='hot')
    
    subplot(3,4,9)
    imshow(v1v[timesteps,:,:], vmin=0, vmax=1, cmap='hot')
    
    subplot(3,4,2)
    imshow(v4h[timesteps,:,:], vmin=0, vmax=1, cmap='hot')
    
    subplot(3,4,6)
    imshow(v4c[timesteps,:,:], vmin=0, vmax=1, cmap='hot')
    
    subplot(3,4,10)
    imshow(v4v[timesteps,:,:], vmin=0, vmax=1, cmap='hot')
    
    subplot(3,4,3)
    imshow(ss[timesteps,:,:], vmin=0, vmax=1, cmap='hot')
    
    subplot(3,4,7)
    imshow(fs[timesteps,:,:], vmin=0, vmax=1, cmap='hot')
    
    subplot(3,4,11)
    imshow(fd1[timesteps,:,:], vmin=0, vmax=1, cmap='hot')
    
    subplot(3,4,4)
    imshow(fd2[timesteps,:,:], vmin=0, vmax=1, cmap='hot')
    
    subplot(3,4,8)
    imshow(fr[timesteps,:,:], vmin=0, vmax=1, cmap='hot')
    
stimesteps.on_changed(update)


########## NOW DISPLAY TVB SIMULATED NEURAL ACTIVITY ##################
plot_connectivity(white_matter)

white_matter.display_name = 'default'
tsr = tvb.datatypes.time_series.TimeSeriesRegion(data = RAW,
                                                 connectivity=white_matter)
tsr.configure()

tsi = ts_int.TimeSeriesInteractive(time_series=tsr)

tsi.configure()

tsi.show()

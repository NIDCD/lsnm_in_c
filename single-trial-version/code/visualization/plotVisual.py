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
#   This file (plotVisual.py) was created on December 1, 2014.
#
#
#   Author: Antonio Ulloa. Last updated by Antonio Ulloa on January 18 2015  
# **************************************************************************/

# plotVisual.py
#
# Plot output data files of visual delay-match-to-sample simulation

import numpy as np
import pylab as pl

# Load data files
efd1 = np.loadtxt('../../output/efd1.out')
#efd2 = np.loadtxt('../../output/efd2.out')
#ev1h = np.loadtxt('../../output/ev1h.out')
#ev1v = np.loadtxt('../../output/ev1v.out')
#ev4c = np.loadtxt('../../output/ev4c.out')
#ev4h = np.loadtxt('../../output/ev4h.out')
#ev4v = np.loadtxt('../../output/ev4v.out')
#exfr = np.loadtxt('../../output/exfr.out')
#exfs = np.loadtxt('../../output/exfs.out')
#exss = np.loadtxt('../../output/exss.out')

# Plot values
fig1 = pl.figure()
fig1.suptitle('EFD1')
pl.plot(efd1) 

#fig2 = pl.figure()
#fig2.suptitle('EFD2')
#pl.plot(efd2)

#fig3 = pl.figure()
#fig3.suptitle('EV1H')
#pl.plot(ev1h)

#fig4 = pl.figure()
#fig4.suptitle('EV1V')
#pl.plot(ev1v)

#print ev1v.shape

#grid = ev1v[1].reshape(9,9)

#print grid.shape

#fig5 = pl.figure()
#fig5.suptitle('EV4C')
#pl.plot(ev4c)

#print grid.shape

#fig6 = pl.figure()
#fig6.suptitle('EV4H')
#pl.plot(ev4h)

#fig7 = pl.figure()
#fig7.suptitle('EV4V')
#pl.plot(ev4v)

#fig8 = pl.figure()
#fig8.suptitle('EXFR')
#pl.plot(exfr)

#fig9 = pl.figure()
#fig9.suptitle('EXFS')
#pl.plot(exfs)

#fig0 = pl.figure()
#fig0.suptitle('EXSS')
#pl.plot(exss)

# Show the plot on the screen
pl.show() 

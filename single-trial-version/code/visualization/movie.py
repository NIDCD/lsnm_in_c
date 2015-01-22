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

plt.figure(1)

#t,n = lgns.shape
#lgns = lgns.reshape(t, 9, 9)
#print lgns.shape

# Render LGN array in a colormap
ax = plt.subplot(3,6,7)
lgns = lgns[75]
lgns = lgns.reshape(9, 9)
img = plt.imshow(lgns)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render EV1h array in a colormap
ax=plt.subplot(3,6,14)
ev1h = ev1h[75]
ev1h = ev1h.reshape(9, 9)
img = plt.imshow(ev1h)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render EV1v array in a colormap
ax=plt.subplot(3,6,2)
ev1v = ev1v[75]
ev1v = ev1v.reshape(9, 9)
img = plt.imshow(ev1v)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(3,6,3)
ev4h = ev4h[75]
ev4h = ev4h.reshape(9, 9)
img = plt.imshow(ev4h)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(3,6,9)
ev4c = ev4c[75]
ev4c = ev4c.reshape(9, 9)
img = plt.imshow(ev4c)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(3,6,15)
ev4v = ev4v[75]
ev4v = ev4v.reshape(9, 9)
img = plt.imshow(ev4v)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(3,6,10)
exss = exss[75]
exss = exss.reshape(9, 9)
img = plt.imshow(exss)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(3,6,5)
exfs = exfs[75]
exfs = exfs.reshape(9, 9)
img = plt.imshow(exfs)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(3,6,11)
efd1 = efd1[75]
efd1 = efd1.reshape(9, 9)
img = plt.imshow(efd1)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(3,6,17)
efd2 = efd2[75]
efd2 = efd2.reshape(9, 9)
img = plt.imshow(efd2)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(3,6,12)
exfr = exfr[75]
exfr = exfr.reshape(9, 9)
img = plt.imshow(exfr)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# anim = animation.FuncAnimation(fig, plt.plot(lgns[9,9]))

# Show the plot on the screen
plt.show()

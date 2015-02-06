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
#   This file (sim.py) was created on February 5, 2015.
#
#
#   Author: Antonio Ulloa. Last updated by Antonio Ulloa on February 5 2015  
# **************************************************************************/

# sim.py
#
# Simulates delayed match-to-sample experiment using Wilson-Cowan neuronal
# population model.

# First, assign the name of the input file
input_file = 'model.txt'

# create a list with labels to be used as indexes
index = ['module_name', 'num_units', 'act_rule', 'threshold', 'delta', 'decay', 'K', 'noise', 'init_value']

# initialize an empty list to keep ALL of the modules of the neural network
modules = []

# open the file with module declarations
f = open(input_file, 'r')

# load the file into a python list of lists
modules = [line.split() for line in f.readlines()]

# add a list of nodes belongig to each module in the list, using the number of nodes specified
# in the input file (num_units) and initializing those nodes to 'init_value'
for module in modules:
    module.append([float(module[8])] * int(module[1]))

print modules

# close our input file
f.close()




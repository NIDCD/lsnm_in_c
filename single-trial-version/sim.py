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

# create labels to be used as indexes, thus avoiding the use of a
# python dictionary
module_name = 0
x_dim = 1
y_dim = 2
activation_rule = 3
threshold = 4
delta = 5
decay = 6
K = 7
noise = 8
initial_value = 9

# initialize an empty list to keep ALL of the modules of the neural network
modules = []

# open the file containing module declarations
f = open(input_file, 'r')

# load the file into a python list of lists
modules = [line.split() for line in f.readlines()]

# convert ALL module dimensions into integers
for module in modules:
    module[x_dim] = int(module[x_dim])
    module[y_dim] = int(module[y_dim])

# convert ALL parameters in the list of lists into float
for module in modules:
    module[threshold] = float(module[threshold])
    module[delta] = float(module[delta])
    module[decay] = float(module[decay])
    module[K] = float(module[K])
    module[noise] = float(module[noise])
    module[initial_value] = float(module[initial_value])

# add a list of nodes belonging to each module in the list, using the module dimensions specified
# in the input file (x_dim * y_dim) and initializing those nodes to 'initial_value'
for module in modules:
    module.append([[[float(module[initial_value])] * int(module[x_dim])] * int(module[y_dim])])

print modules

# close our input file
f.close()




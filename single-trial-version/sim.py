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
#   Author: Antonio Ulloa. Last updated by Antonio Ulloa on February 6 2015  
# **************************************************************************/

# sim.py
#
# Simulates delayed match-to-sample experiment using Wilson-Cowan neuronal
# population model.

import re

# First, assign the name of the input file
model = 'model.txt'
weights_list = 'weights/weightslist.txt'

# create labels to be used as indexes to information about each module, thus
# avoiding the use of a python dictionary
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
unit_matrix = 10

# initialize an empty list to store ALL of the modules of the neural network
modules = []

# open the input file containing module declarations (i.e., the 'model'), then
# load the file into a python list of lists and close file safely
f = open(model, 'r')
try: 
    modules = [line.split() for line in f]
finally:
    f.close()
    
# convert ALL module dimensions to integers since we will need those numbers
# later
for module in modules:
    module[x_dim] = int(module[x_dim])
    module[y_dim] = int(module[y_dim])
    
# convert ALL parameters in the modules to float since we will need to use those
# to solve Wilson-Cowan equations
for module in modules:
    module[threshold] = float(module[threshold])
    module[delta] = float(module[delta])
    module[decay] = float(module[decay])
    module[K] = float(module[K])
    module[noise] = float(module[noise])
    module[initial_value] = float(module[initial_value])

# add a list of units to each module, using the module dimensions specified
# in the input file (x_dim * y_dim) and initialize all units in each module to 'initial_value'
# It also adds two extra elements per each unit to store sum of inbititory and sum
# of excitatory activity at the current time step.
for module in modules:
    module.append([[[[module[initial_value]] + [0, 0]] * module[x_dim]] * module[y_dim]])

# now turn the list modules into a dictionary so we can access each module using the
# module name as key
modules = {m[0]: m[1:] for m in modules}

# read file that contains list of weight files, store the list of files in a python list,
# and close the file safely
f = open(weights_list, 'r')
try:
    weight_files = [line.strip() for line in f]
finally:
    f.close()

# build a dictionary of replacements for parsing the weight files
replacements = {'Connect': '',
                'From:': '',
                '(':'[',
                ')':']',
                '{':'[',
                '}':']',
                '|':''}

# open each weight file in the list of weight files, one by one, and transfer weights
# from those files to each unit in the module list
# Note: file f is closed automatically at the end of 'with' since block 'with' is a
# context manager for file I/O
for file in weight_files:
    with open(file) as f:
        # read the whole file and store it in a string
        whole_thing = f.read()
        
        # find which module is connected to which module
        module_connection = re.search(r'Connect\((.+?),(.+?)\)', whole_thing)

        # get rid of white spaces from origin and destination modules
        origin_module = module_connection.group(1).strip()
        destination_module = module_connection.group(2).strip()

        # gets rid of C-style comments at the beginning of weight files
        whole_thing = re.sub(re.compile('%.*?\n'), '', whole_thing)

        # removes all white spaces (space, tab, newline, etc) from weight files
        whole_thing = ''.join(whole_thing.split())
        
        # replaces Malle-style language with python lists characters
        for i, j in replacements.iteritems():
            whole_thing = whole_thing.replace(i, j)

        # now add commas between pairs of brackets
        whole_thing = whole_thing.replace('][', '],[')

        # now insert commas between right brackets and numbers (temporary hack!)
        whole_thing = whole_thing.replace(']0', '],0')
        whole_thing = whole_thing.replace(']1', '],1')
        whole_thing = whole_thing.replace(']-', '],-')

        # add extra string delimiters to origin_module and destination_module so
        # that they can be recognized as python "strings" when the list or lists
        # is formed
        whole_thing = whole_thing.replace(origin_module+','+destination_module,
                                          "'"+origin_module+"','"+destination_module+"'", 1)

        # now convert the whole thing into a python list of lists, using Python's
        # own interpreter 
        whole_thing = eval(whole_thing)

        # remove [origin_module, destination_module] from list of connections
        whole_thing = whole_thing[1]
        
        # now groups items in the form: [(origin_unit), [[[destination_unit], weight],
        # ..., [[destination_unit_2], weight_2]])]
        whole_thing = zip(whole_thing, whole_thing[1:])[::2]
        
        # insert [destination_module, x_dest, y_dest, weight] in the corresponding origin
        # unit location of the modules list while adjusting (x_dest, y_dest) coordinates
        # to a zero-based format (as used in Python)
        for connection in whole_thing:
            for destination in connection[1]:
                modules[origin_module][9][0][connection[0][0]-1][connection[0][1]-1].append (
                    [destination_module,        # insert name of destination module
                     destination[0][0],         # insert x coordinate of destination unit
                     destination[0][1],         # insert y coordinate of destination unit
                     destination[1]])           # insert connection weight

print modules['efd2']


# -*- coding: utf-8 -*-
#
#
#  TheVirtualBrain-Scientific Package. This package holds all simulators, and 
# analysers necessary to run brain-simulations. You can use it stand alone or
# in conjunction with TheVirtualBrain-Framework Package. See content of the
# documentation-folder for more details. See also http://www.thevirtualbrain.org
#
# (c) 2012-2013, Baycrest Centre for Geriatric Care ("Baycrest")
#
# This program is free software; you can redistribute it and/or modify it under 
# the terms of the GNU General Public License version 2 as published by the Free
# Software Foundation. This program is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
# License for more details. You should have received a copy of the GNU General 
# Public License along with this program; if not, you can download it here
# http://www.gnu.org/licenses/old-licenses/gpl-2.0
#
#
#   CITATION:
# When using The Virtual Brain for scientific publications, please cite it as follows:
#
#   Paula Sanz Leon, Stuart A. Knock, M. Marmaduke Woodman, Lia Domide,
#   Jochen Mersmann, Anthony R. McIntosh, Viktor Jirsa (2013)
#   The Virtual Brain: a simulator of primate brain network dynamics.
#   Frontiers in Neuroinformatics (7:10. doi: 10.3389/fninf.2013.00010)
#
#

"""
Generate 16 seconds of 2048Hz data at the region level, stochastic integration.

``Run time``: approximately 4 minutes (workstation circa 2010)

``Memory requirement``: < 1GB
``Storage requirement``: ~ 19MB

.. moduleauthor:: Stuart A. Knock <stuart.knock@gmail.com>

"""

from tvb.simulator.lab import *

##----------------------------------------------------------------------------##
##-                      Perform the simulation                              -##
##----------------------------------------------------------------------------##

LOG.info("Configuring...")

#Initialise a Model, Coupling, and Connectivity.
pars = {'a': 1.05,
        'b': -1.,
        'c': 0.0,
        'd': 0.1,
        'e': 0.0,
        'f': 1 / 3.,
        'g': 1.0,
        'alpha': 1.0,
        'beta': 0.2,
        'tau': 1.25,
        'gamma': -1.0}

oscillator = models.Generic2dOscillator(**pars)

white_matter = connectivity.Connectivity(load_default=True)
white_matter.speed = numpy.array([4.0])
white_matter_coupling = coupling.Linear(a=0.033)

#Initialise an Integrator
hiss = noise.Additive(nsig=numpy.array([2 ** -10, ]))
heunint = integrators.HeunStochastic(dt=0.06103515625, noise=hiss) 

#Initialise a Monitor with period in physical time
what_to_watch = monitors.Raw()

#Initialise a Simulator -- Model, Connectivity, Integrator, and Monitors.
sim = simulator.Simulator(model=oscillator, connectivity=white_matter,
                          coupling=white_matter_coupling,
                          integrator=heunint, monitors=what_to_watch)

sim.configure()

#Perform the simulation
raw_data = []
raw_time = []
LOG.info("Starting simulation...")
for raw in sim(simulation_length=5500):
    if raw is not None:
        raw_time.append(raw[0][0])    # TODO:The first [0] is a hack for single monitor
        raw_data.append(raw[0][1])    # TODO:The first [0] is a hack for single monitor

LOG.info("Finished simulation.")


##----------------------------------------------------------------------------##
##-                     Save the data to a file                              -##
##----------------------------------------------------------------------------##

#Make the list a numpy.array.
LOG.info("Converting result to array...")
RAW = numpy.array(raw_data)

#Save it
FILE_NAME = "demo_raw_data_region_5.5s_2048Hz.npy"
LOG.info("Saving array to %s..." % FILE_NAME)
numpy.save(FILE_NAME, RAW)

LOG.info("Done.")

###EoF###

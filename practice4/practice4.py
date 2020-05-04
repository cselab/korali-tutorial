#!/usr/bin/env python3

# In this example, we demonstrate how Korali samples the posterior
# distribution in a bayesian problem where the likelihood
# is provided directly by the computational model.
# In this case, we use the MCMC method.

# Importing computational model
import sys
sys.path.append('model')
from model import *

# Creating new experiment
import korali
e = korali.Experiment()

# Selecting problem and solver types.
e["Problem"]["Type"] = "Sampling"
e["Problem"]["Probability Function"] = 

# Configuring the MCMC sampler parameters
e["Solver"]["Type"]  = "MCMC"
e["Solver"]["Termination Criteria"]["Max Samples"] = 50000

# Defining problem's variables
e["Variables"][0]["Name"] = 
e["Variables"][0]["Initial Mean"] = 
e["Variables"][0]["Initial Standard Deviation"] = 

# Defining problem's variables
e["Variables"][1]["Name"] = 
e["Variables"][1]["Initial Mean"] =
e["Variables"][1]["Initial Standard Deviation"] = 

# Configuring output settings
e["File Output"]["Frequency"] = 5000
e["Console Output"]["Frequency"] = 5000
e["Console Output"]["Verbosity"] = "Detailed"

# Starting Korali's Engine and running experiment
k = korali.Engine()
k.run(e)

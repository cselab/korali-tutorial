#!/usr/bin/env python3

# In this example, we demonstrate how Korali find the variable values
# that maximize the posterior in a bayesian problem where the likelihood
# is calculated by providing reference data points and their objective values.

# Importing the computational model
import sys
sys.path.append('./model')
from model import *

# Creating new experiment
import korali
e = korali.Experiment()

# Get Reference Data and Points

# Setting up the reference likelihood for the Bayesian Problem
e["Problem"]["Type"] = 
e["Problem"]["Likelihood Model"] = 
e["Problem"]["Reference Data"] = 
e["Problem"]["Computational Model"] = 

# Configuring CMA-ES parameters
e["Solver"]["Type"] = "TMCMC"
e["Solver"]["Population Size"] = 2000

# Configuring the problem's random distributions
e["Distributions"][0]["Name"] = 
e["Distributions"][0]["Type"] = 
e["Distributions"][0]["Minimum"] =
e["Distributions"][0]["Maximum"] = 

e["Distributions"][1]["Name"] = 
e["Distributions"][1]["Type"] = 
e["Distributions"][1]["Minimum"] = 
e["Distributions"][1]["Maximum"] = 

e["Distributions"][2]["Name"] = 
e["Distributions"][2]["Type"] = 
e["Distributions"][2]["Mean"] = 
e["Distributions"][2]["Standard Deviation"] = 

# Configuring the problem's variables
e["Variables"][0]["Name"] = 
e["Variables"][0]["Prior Distribution"] = 

e["Variables"][1]["Name"] = 
e["Variables"][1]["Prior Distribution"] = 

e["Variables"][2]["Name"] = 
e["Variables"][2]["Prior Distribution"] = 

# Starting Korali's Engine and running experiment
k = korali.Engine()
k.run(e)

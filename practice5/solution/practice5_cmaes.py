#!/usr/bin/env python3

# In this example, we demonstrate how Korali find the variable values
# that maximize the posterior in a bayesian problem where the likelihood
# is calculated by providing reference data points and their objective values.

# Importing the computational model
import sys
sys.path.append('../model')
from model import *

# Creating new experiment
import korali
e = korali.Experiment()

# Getting Reference Data and Points
x = getReferencePoints()
y = getReferenceData()

# Setting up the reference likelihood for the Bayesian Problem
e["Problem"]["Type"] = "Bayesian/Reference" 
e["Problem"]["Likelihood Model"] = "Normal"
e["Problem"]["Reference Data"] = y
e["Problem"]["Computational Model"] = lambda sample : model(sample, x)

# Configuring CMA-ES parameters
e["Solver"]["Type"] = "Optimizer/CMAES"
e["Solver"]["Population Size"] = 12
e["Solver"]["Termination Criteria"]["Min Value Difference Threshold"] = 0.00001

# Configuring the problem's random distributions
e["Distributions"][0]["Name"] = "Prior 1"
e["Distributions"][0]["Type"] = "Univariate/Uniform"
e["Distributions"][0]["Minimum"] = -5.0
e["Distributions"][0]["Maximum"] = +5.0

e["Distributions"][1]["Name"] = "Prior 2"
e["Distributions"][1]["Type"] = "Univariate/Uniform"
e["Distributions"][1]["Minimum"] = -5.0
e["Distributions"][1]["Maximum"] = +5.0

e["Distributions"][2]["Name"] = "Error Distribution"
e["Distributions"][2]["Type"] = "Univariate/Normal"
e["Distributions"][2]["Mean"] = 0.0 
e["Distributions"][2]["Standard Deviation"] = 2.0

# Configuring the problem's variables
e["Variables"][0]["Name"] = "S0"
e["Variables"][0]["Prior Distribution"] = "Prior 1"
e["Variables"][0]["Lower Bound"] = -5.0
e["Variables"][0]["Upper Bound"] = +5.0

e["Variables"][1]["Name"] = "S1"
e["Variables"][1]["Prior Distribution"] = "Prior 2"
e["Variables"][1]["Lower Bound"] = -5.0
e["Variables"][1]["Upper Bound"] = +5.0

e["Variables"][2]["Name"] = "[Sigma]"
e["Variables"][2]["Prior Distribution"] = "Error Distribution"
e["Variables"][2]["Lower Bound"] = 0.0
e["Variables"][2]["Upper Bound"] = 1.0

# Starting Korali's Engine and running experiment
k = korali.Engine()
k.run(e)

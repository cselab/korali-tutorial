#!/usr/bin/env python3
import time

# Importing computational model
import sys
sys.path.append('../model')
from model import *

# Starting Korali's Engine
import korali
k = korali.Engine()

# Setting concurrent conduit
k["Conduit"]["Type"] = "Concurrent"
k["Conduit"]["Concurrent Jobs"] = 12

# Enabling profiling information
k["Profiling"]["Detail"] = "Full"
k["Profiling"]["Frequency"] = 0.5

# Taking Initial Time
start = time.time()

# Creating  experiment list
eList = []

# Running 8 (similar) experiments
for i in range(8):
  e = korali.Experiment()
  e["Problem"]["Type"] = "Bayesian/Reference"
  e["Problem"]["Likelihood Model"] = "Normal"
  e["Problem"]["Reference Data"] = getReferenceData()
  e["Problem"]["Computational Model"] = lambda sampleData: model(sampleData, getReferencePoints())
  
  # Configuring CMA-ES parameters
  e["Solver"]["Type"] = "Optimizer/CMAES"
  e["Solver"]["Population Size"] = 12 
  e["Solver"]["Termination Criteria"]["Max Generations"] = 100
  
  # Configuring the problem's random distributions
  e["Distributions"][0]["Name"] = "Uniform 0"
  e["Distributions"][0]["Type"] = "Univariate/Uniform"
  e["Distributions"][0]["Minimum"] = -5.0
  e["Distributions"][0]["Maximum"] = +5.0
  
  e["Distributions"][1]["Name"] = "Uniform 1"
  e["Distributions"][1]["Type"] = "Univariate/Uniform"
  e["Distributions"][1]["Minimum"] = -5.0
  e["Distributions"][1]["Maximum"] = +5.0
  
  e["Distributions"][2]["Name"] = "Uniform 2"
  e["Distributions"][2]["Type"] = "Univariate/Uniform"
  e["Distributions"][2]["Minimum"] = 0.0
  e["Distributions"][2]["Maximum"] = +5.0
  
  # Configuring the problem's variables
  e["Variables"][0]["Name"] = "a"
  e["Variables"][0]["Prior Distribution"] = "Uniform 0"
  e["Variables"][0]["Lower Bound"] = -5.0
  e["Variables"][0]["Upper Bound"] = +5.0
  e["Variables"][0]["Initial Mean"] = +0.0
  e["Variables"][0]["Initial Standard Deviation"] = +1.0
  
  e["Variables"][1]["Name"] = "b"
  e["Variables"][1]["Prior Distribution"] = "Uniform 1"
  e["Variables"][1]["Lower Bound"] = -5.0
  e["Variables"][1]["Upper Bound"] = +5.0
  e["Variables"][1]["Initial Mean"] = +0.0
  e["Variables"][1]["Initial Standard Deviation"] = +1.0
  
  e["Variables"][2]["Name"] = "[Sigma]"
  e["Variables"][2]["Prior Distribution"] = "Uniform 2"
  e["Variables"][2]["Lower Bound"] = 0.0
  e["Variables"][2]["Upper Bound"] = +5.0
  e["Variables"][2]["Initial Mean"] = +2.5
  e["Variables"][2]["Initial Standard Deviation"] = +0.5
 
  # Setting distinct experiment paths
  e["File Output"]["Path"] = '_korali_multiple/exp' + str(i)

  # Appending experiment to list  
  eList.append(e)

# Running experiments alltogether
k.run(eList)

# Taking final time
end = time.time()

print("Elapsed Time: " + str(end - start) + " seconds" )

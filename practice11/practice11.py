#!/usr/bin/env python3

# In this example, we demonstrate how a Korali experiment can
# be resumed from previous file-saved results. This is a useful feature
# for continuing jobs after an error, or to fragment big jobs into
# smaller ones that can better fit a supercomputer queue.

# First, we run a simple Korali experiment.

import sys
sys.path.append('model')
from model import *
import korali

k = korali.Engine()
e = korali.Experiment()

e["Problem"]["Type"] = "Optimization/Stochastic"

e["Solver"]["Type"] = "CMAES"
e["Solver"]["Population Size"] = 5
e["Solver"]["Termination Criteria"]["Max Generations"] = 10

e["Variables"][0]["Name"] = "X"
e["Variables"][0]["Lower Bound"] = -10.0
e["Variables"][0]["Upper Bound"] = +10.0

# Setting computational model
e["Problem"]["Objective Function"] = model

# Initially, we run all 10 generations at once
k.run(e)

# But here we will add the logic to see if there were previous results

# If they were not, we ran anew

# If they were there, then we just resume execution

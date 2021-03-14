#!/usr/bin/env python3

# Define Objective Function
def myObjectiveFunction(sample):
  x = sample["Parameters"][0]
  y = sample["Parameters"][1]

  f = -(x*x + y*y) + 5

  sample["F(x)"] = f

# Import and Start Korali's Engine
import korali
k = korali.Engine()

# Creating new experiment
e = korali.Experiment()

# Configuring Problem
e["Problem"]["Type"] = "Optimization"
e["Problem"]["Objective Function"] = myObjectiveFunction

# Defining the problem's variables.
e["Variables"][0]["Name"] = "X"
e["Variables"][0]["Lower Bound"] = -10.0
e["Variables"][0]["Upper Bound"] = +10.0

e["Variables"][1]["Name"] = "Y"
e["Variables"][1]["Lower Bound"] = -10.0
e["Variables"][1]["Upper Bound"] = +10.0

# Configure the CMAES solver
e["Solver"]["Type"] = "Optimizer/CMAES"
e["Solver"]["Population Size"] = 4 

# Add Termination Criteria
e["Solver"]["Termination Criteria"]["Max Generations"] = 100

# Prevent Console Output
e["Console Output"]["Verbosity"] = "Silent"

# Prevent File Output
e["File Output"]["Enabled"] = False

# Running Korali
k.run(e)

# Print Results Manually
maximum = e["Results"]["Best Sample"]["F(x)"]
x = e["Results"]["Best Sample"]["Parameters"][0]
y = e["Results"]["Best Sample"]["Parameters"][1]

print("Found Maximum: " + str(maximum) + " at (" + str(x) + ", " + str(x) + ")")


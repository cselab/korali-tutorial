#!/usr/bin/env python3
import korali
import sys
import subprocess

def runModel(sample):
  # Create the launch command, containing first the path of the model we want to run
  argString = ['../model/model.py']
  
  # Get the model parameters from Korali
  v = sample["Parameters"]

  # For each parameter, append it to the launch command
  for i in v: argString.append(str(i))

  # Gather return value form the console output
  retValue = subprocess.check_output(argString)

  # Convert string value to a number
  result = float(retValue.decode())

  # Save the return value as result in the sample
  sample["F(x)"] = result

k = korali.Engine()
e = korali.Experiment()

e["Problem"]["Type"] = "Optimization";
e["Problem"]["Objective Function"] = runModel

e["Solver"]["Type"] = "Optimizer/CMAES"
e["Solver"]["Population Size"] = 12
e["Solver"]["Termination Criteria"]["Max Generations"] = 10

e["Variables"][0]["Name"] = "X0"
e["Variables"][0]["Lower Bound"] = -32.0;
e["Variables"][0]["Upper Bound"] = +32.0;

e["Variables"][1]["Name"] = "X1"
e["Variables"][1]["Lower Bound"] = -32.0;
e["Variables"][1]["Upper Bound"] = +32.0;

e["Variables"][2]["Name"] = "X2"
e["Variables"][2]["Lower Bound"] = -32.0;
e["Variables"][2]["Upper Bound"] = +32.0;

e["Variables"][3]["Name"] = "X3"
e["Variables"][3]["Lower Bound"] = -32.0;
e["Variables"][3]["Upper Bound"] = +32.0;

k["Conduit"]["Type"] = "Concurrent"
k["Conduit"]["Concurrent Jobs"] = 12

k.run(e)

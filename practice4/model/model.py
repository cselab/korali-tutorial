#!/usr/bin/env python

# This model described a given unnormalized probability distribution
def model(s):
  v0 = s["Parameters"][0]
  v1 = s["Parameters"][1]

  s["P(x)"] = -0.5*v0*v0 -0.5*v1*v1


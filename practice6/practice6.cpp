#include "model/heat2d.h"
#include "korali.hpp"

int main(int argc, char* argv[])
{
 auto k = korali::Engine();
 auto e = korali::Experiment();
 auto p = heat2DInit("data_1source.in");

 e["Problem"]["Type"] = "Bayesian/Reference";
 e["Problem"]["Likelihood Model"] = "Additive Normal";
 e["Problem"]["Reference Data"] = p.refTemp;
 e["Problem"]["Computational Model"] = &heat2DSolver;

 e["Solver"]["Type"] = "CMAES";
 e["Solver"]["Population Size"] = 12;
 e["Solver"]["Termination Criteria"]["Max Generations"] = 100;

 e["Distributions"][0]["Name"] = "Uniform 0";
 e["Distributions"][0]["Type"] = "Univariate/Uniform";
 e["Distributions"][0]["Minimum"] = 10.0;
 e["Distributions"][0]["Maximum"] = 60.0;

 e["Distributions"][1]["Name"] = "Uniform 1";
 e["Distributions"][1]["Type"] = "Univariate/Uniform";
 e["Distributions"][1]["Minimum"] = 0.0;
 e["Distributions"][1]["Maximum"] = 1.0;

 e["Distributions"][2]["Name"] = "Uniform 2";
 e["Distributions"][2]["Type"] = "Univariate/Uniform";
 e["Distributions"][2]["Minimum"] = 0.0;
 e["Distributions"][2]["Maximum"] = 1.0;

 e["Distributions"][3]["Name"] = "Uniform 3";
 e["Distributions"][3]["Type"] = "Univariate/Uniform";
 e["Distributions"][3]["Minimum"] = 0.0;
 e["Distributions"][3]["Maximum"] = 20.0;

 e["Variables"][0]["Name"] = "Intensity";
 e["Variables"][0]["Prior Distribution"] = "Uniform 0";
 e["Variables"][0]["Lower Bound"] = 10.0;
 e["Variables"][0]["Upper Bound"] = 60.0;

 e["Variables"][1]["Name"] = "PosX";
 e["Variables"][1]["Prior Distribution"] = "Uniform 1";
 e["Variables"][1]["Lower Bound"] = 0.0;
 e["Variables"][1]["Upper Bound"] = 1.0;

 e["Variables"][2]["Name"] = "PosY";
 e["Variables"][2]["Prior Distribution"] = "Uniform 2";
 e["Variables"][2]["Lower Bound"] = 0.0;
 e["Variables"][2]["Upper Bound"] = 1.0;

 e["Variables"][3]["Name"] = "[Sigma]";
 e["Variables"][3]["Prior Distribution"] = "Uniform 3";
 e["Variables"][3]["Lower Bound"] = 0.0;
 e["Variables"][3]["Upper Bound"] = 10.0;

 k.run(e);

 return 0;
}

#include "model/heat2d.h"
#include "korali.hpp"

/* Example with three heat sources
Exact Solution:
X0: 0.13
Y0: 0.75

X1: 0.79
Y1: 0.91

X2: 0.58
Y2: 0.23
*/

int main(int argc, char* argv[])
{
 auto k = korali::Engine();
 auto e = korali::Experiment();
 auto p = heat2DInit("model/data.in");

 e["Problem"]["Type"] = "Bayesian/Reference";
 e["Problem"]["Likelihood Model"] = "Normal";
 e["Problem"]["Reference Data"] = p.refTemp;
 e["Problem"]["Computational Model"] = &heat2DSolver;

 e["Solver"]["Type"] = "Sampler/TMCMC";
 e["Solver"]["Population Size"] = 2000;

 // Heat Source 0

 e["Variables"][0]["Name"] = "Pos X0";
 e["Variables"][0]["Prior Distribution"] = "Prior 0";
 e["Distributions"][0]["Name"] = "Prior 0";
 e["Distributions"][0]["Type"] = "Univariate/Uniform";
 e["Distributions"][0]["Minimum"] = 0.0;
 e["Distributions"][0]["Maximum"] = 0.5;

 e["Variables"][1]["Name"] = "Pos Y0";
 e["Variables"][1]["Prior Distribution"] = "Prior 1";
 e["Distributions"][1]["Name"] = "Prior 1";
 e["Distributions"][1]["Type"] = "Univariate/Uniform";
 e["Distributions"][1]["Minimum"] = 0.5;
 e["Distributions"][1]["Maximum"] = 1.0;

 // Heat Source 1

 e["Variables"][2]["Name"] = "Pos X1";
 e["Variables"][2]["Prior Distribution"] = "Prior 2";
 e["Distributions"][2]["Name"] = "Prior 2";
 e["Distributions"][2]["Type"] = "Univariate/Uniform";
 e["Distributions"][2]["Minimum"] = 0.5;
 e["Distributions"][2]["Maximum"] = 1.0;

 e["Variables"][3]["Name"] = "Pos Y1";
 e["Variables"][3]["Prior Distribution"] = "Prior 3";
 e["Distributions"][3]["Name"] = "Prior 3";
 e["Distributions"][3]["Type"] = "Univariate/Uniform";
 e["Distributions"][3]["Minimum"] = 0.5;
 e["Distributions"][3]["Maximum"] = 1.0;

 // Heat Source 2

 e["Variables"][4]["Name"] = "Pos X2";
 e["Variables"][4]["Prior Distribution"] = "Prior 4";
 e["Distributions"][4]["Name"] = "Prior 4";
 e["Distributions"][4]["Type"] = "Univariate/Uniform";
 e["Distributions"][4]["Minimum"] = 0.5;
 e["Distributions"][4]["Maximum"] = 1.0;

 e["Variables"][5]["Name"] = "Pos Y2";
 e["Variables"][5]["Prior Distribution"] = "Prior 5";
 e["Distributions"][5]["Name"] = "Prior 5";
 e["Distributions"][5]["Type"] = "Univariate/Uniform";
 e["Distributions"][5]["Minimum"] = 0.0;
 e["Distributions"][5]["Maximum"] = 0.5;

 e["Variables"][6]["Name"] = "[Sigma]";
 e["Variables"][6]["Prior Distribution"] = "Prior 6";
 e["Distributions"][6]["Name"] = "Prior 6";
 e["Distributions"][6]["Type"] = "Univariate/Uniform";
 e["Distributions"][6]["Minimum"] = 0.0;
 e["Distributions"][6]["Maximum"] = 20.0;

 e["Store Sample Information"] = true;

 // Here you should add configuration for concurrent execution
 k["Conduit"]["Type"] = "Concurrent";
 k["Conduit"]["Concurrent Jobs"] = 12;

 k.run(e);

 // Now looking for the best sample among the sample population

 double maxPosterior = -korali::Inf;
 size_t bestSampleIdx = 0;

 printf("\n");
 printf("Best Parameters:\n");
 printf("----------------\n");

 for (size_t i = 0; i < e["Samples"].size(); i++)
 {
  double currPosterior = e["Samples"][i]["logPosterior"];
  if (currPosterior > maxPosterior)
  {
   maxPosterior = currPosterior;
   bestSampleIdx = i;
  }
 }

 std::vector<double> bestParameters = e["Samples"][bestSampleIdx]["Parameters"];

 printf("X0: %f\n", bestParameters[0]);
 printf("Y0: %f\n", bestParameters[1]);

 printf("X1: %f\n", bestParameters[2]);
 printf("Y1: %f\n", bestParameters[3]);

 printf("X2: %f\n", bestParameters[4]);
 printf("Y2: %f\n", bestParameters[5]);

 printf("Sigma: %f\n", bestParameters[6]);

 return 0;
}

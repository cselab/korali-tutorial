#include "model/heat2d.h"
#include "korali.hpp"

/* Example with a single heat source
Exact Solution:
X0: 0.3
Y0: 0.8
*/

int main(int argc, char* argv[])
{
 auto k = korali::Engine();
 auto e = korali::Experiment();

 auto p = heat2DInit("data_1source.in");

 e["Problem"]["Type"] = "Bayesian/Reference";
 e["Problem"]["Likelihood Model"] = "Additive Normal";
 e["Problem"]["Reference Data"] = p.refTemp;
 e["Problem"]["Computational Model"] = &heat2DSolver;

 e["Solver"]["Type"] = "TMCMC";
 e["Solver"]["Population Size"] = 500;

 e["Variables"][0]["Name"] = "Pos X";
 e["Variables"][0]["Prior Distribution"] = "Uniform 0";
 e["Distributions"][0]["Name"] = "Uniform 0";
 e["Distributions"][0]["Type"] = "Univariate/Uniform";
 e["Distributions"][0]["Minimum"] = 0.0;
 e["Distributions"][0]["Maximum"] = 1.0;

 e["Variables"][1]["Name"] = "Pos Y";
 e["Variables"][1]["Prior Distribution"] = "Uniform 1";
 e["Distributions"][1]["Name"] = "Uniform 1";
 e["Distributions"][1]["Type"] = "Univariate/Uniform";
 e["Distributions"][1]["Minimum"] = 0.0;
 e["Distributions"][1]["Maximum"] = 1.0;

 e["Variables"][2]["Name"] = "[Sigma]";
 e["Variables"][2]["Prior Distribution"] = "Uniform 2";
 e["Distributions"][2]["Name"] = "Uniform 2";
 e["Distributions"][2]["Type"] = "Univariate/Uniform";
 e["Distributions"][2]["Minimum"] = 0.0;
 e["Distributions"][2]["Maximum"] = 20.0;

 e["Store Sample Information"] = true;

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
 printf("X: %f\n", bestParameters[0]);
 printf("Y: %f\n", bestParameters[1]);
 printf("Sigma: %f\n", bestParameters[2]);

 return 0;
}

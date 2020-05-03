#include "korali.hpp"
#include "model/jacobi.h"
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
 auto e = korali::Experiment();

 e["Problem"]["Type"] = "Bayesian/Reference";
 e["Problem"]["Likelihood Model"] = "Additive Normal";
 e["Problem"]["Reference Data"] = getReferenceData();
 e["Problem"]["Computational Model"] = &jacobi;

 e["Distributions"][0]["Name"] = "Uniform 0";
 e["Distributions"][0]["Type"] = "Univariate/Uniform";
 e["Distributions"][0]["Minimum"] = -5.0;
 e["Distributions"][0]["Maximum"] = +5.0;

 e["Distributions"][1]["Name"] = "Uniform 1";
 e["Distributions"][1]["Type"] = "Univariate/Uniform";
 e["Distributions"][1]["Minimum"] = -5.0;
 e["Distributions"][1]["Maximum"] = +5.0;

 e["Distributions"][2]["Name"] = "Uniform 2";
 e["Distributions"][2]["Type"] = "Univariate/Uniform";
 e["Distributions"][2]["Minimum"] = -5.0;
 e["Distributions"][2]["Maximum"] = +5.0;

 e["Distributions"][3]["Name"] = "Uniform 3";
 e["Distributions"][3]["Type"] = "Univariate/Uniform";
 e["Distributions"][3]["Minimum"] = -5.0;
 e["Distributions"][3]["Maximum"] = +5.0;

 e["Distributions"][4]["Name"] = "Uniform 4";
 e["Distributions"][4]["Type"] = "Univariate/Uniform";
 e["Distributions"][4]["Minimum"] = -5.0;
 e["Distributions"][4]["Maximum"] = +5.0;

 e["Distributions"][5]["Name"] = "Uniform 5";
 e["Distributions"][5]["Type"] = "Univariate/Uniform";
 e["Distributions"][5]["Minimum"] = -5.0;
 e["Distributions"][5]["Maximum"] = +5.0;

 e["Distributions"][6]["Name"] = "Uniform 6";
 e["Distributions"][6]["Type"] = "Univariate/Normal";
 e["Distributions"][6]["Mean"] = 0.0;
 e["Distributions"][6]["Standard Deviation"] = +5.0;

 e["Variables"][0]["Name"] = "X0";
 e["Variables"][0]["Prior Distribution"] = "Uniform 0";

 e["Variables"][1]["Name"] = "Y0";
 e["Variables"][1]["Prior Distribution"] = "Uniform 1";

 e["Variables"][2]["Name"] = "X1";
 e["Variables"][2]["Prior Distribution"] = "Uniform 2";

 e["Variables"][3]["Name"] = "Y1";
 e["Variables"][3]["Prior Distribution"] = "Uniform 3";

 e["Variables"][4]["Name"] = "X2";
 e["Variables"][4]["Prior Distribution"] = "Uniform 4";

 e["Variables"][5]["Name"] = "Y2";
 e["Variables"][5]["Prior Distribution"] = "Uniform 5";

 e["Variables"][6]["Name"] = "[Sigma]";
 e["Variables"][6]["Prior Distribution"] = "Uniform 6";

 e["Solver"]["Type"] = "TMCMC";
 e["Solver"]["Covariance Scaling"] = 0.02;
 e["Solver"]["Population Size"] = 200;

 auto k = korali::Engine();
 k.run(e);

 return 0;
}

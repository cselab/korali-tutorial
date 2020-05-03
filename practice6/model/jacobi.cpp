/**********************************************************************/
// A generic stencil-based 3D Jacobi solver                           //
// Course Material for HPCSE-II, Spring 2019, ETH Zurich              //
// Authors: Sergio Martin                                             //
// License: Use if you like, but give us credit.                      //
/**********************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "jacobi.h"

struct Neighbor {
 int rankId;
 double* recvBuffer;
 double* sendBuffer;
};

void jacobi(korali::Sample& k)
{
 int myRank = 0;
 int rankCount = 1;

 int N = 64;
 int nIters = 100;
 int nx, ny, nz;
 int px, py, pz;
 Neighbor X1, X0, Y0, Y1, Z0, Z1;

 nx = N; // Internal grid size (without halo) on X Dimension
 ny = N; // Internal grid size (without halo) on Y Dimension
 nz = N; // Internal grid size (without halo) on Z Dimension
 px = 1;
 py = 1;
 pz = 1;

 if(N % px > 0) { if (myRank == 0) printf("Jacobi3D Model Error: N (%d) should be divisible by px (%d)\n", N, px); exit(-1); }
 if(N % py > 0) { if (myRank == 0) printf("Jacobi3D Model Error: N (%d) should be divisible by py (%d)\n", N, py); exit(-1); }
 if(N % pz > 0) { if (myRank == 0) printf("Jacobi3D Model Error: N (%d) should be divisible by pz (%d)\n", N, pz); exit(-1); }

 int fx = nx + 2; // Grid size (with halo) on X Dimension
 int fy = ny + 2; // Grid size (with halo) on Y Dimension
 int fz = nz + 2; // Grid size (with halo) on Z Dimension

 double *U, *Un;
 U  = (double*) calloc(sizeof(double), fx*fy*fz);
 Un = (double*) calloc(sizeof(double), fx*fy*fz);

 for (int k = 0; k < fz; k++)
 for (int j = 0; j < fy; j++)
 for (int i = 0; i < fx; i++)
   U[k*fy*fx + j*fx + i] = 1;

 for (int i = 0; i < fy; i++) for (int j = 0; j < fz; j++) U[j*fx*fy + i*fx  ] = k["Parameters"][0];
 for (int i = 0; i < fx; i++) for (int j = 0; j < fz; j++) U[j*fx*fy + fx + i] = k["Parameters"][2];
 for (int i = 0; i < fx; i++) for (int j = 0; j < fy; j++) U[fx*fy + j*fx + i] = k["Parameters"][4];

 for (int i = 0; i < fy; i++) for (int j = 0; j < fz; j++) U[j*fx*fy + i*fx + (nx+1)] = k["Parameters"][1];
 for (int i = 0; i < fx; i++) for (int j = 0; j < fz; j++) U[j*fx*fy + (ny+1)*fx + i] = k["Parameters"][3];
 for (int i = 0; i < fx; i++) for (int j = 0; j < fy; j++) U[(nz+1)*fx*fy + j*fx + i] = k["Parameters"][5];

 for (int iter=0; iter<nIters; iter++)
 {
  for (int k = 1; k <= nz; k++)
  for (int j = 1; j <= ny; j++)
  for (int i = 1; i <= nx; i++)
  {
   double sum = 0.0;
   sum += U[fx*fy*k + fx*j  + i + 0]; // Central
   sum += U[fx*fy*k + fx*j  + i - 1]; // Y0
   sum += U[fx*fy*k + fx*j  + i + 1]; // Y1
   sum += U[fx*fy*k + fx*(j-1)  + i]; // X0
   sum += U[fx*fy*k + fx*(j+1)  + i]; // X1
   sum += U[fx*fy*(k-1) + fx*j  + i]; // Z0
   sum += U[fx*fy*(k+1) + fx*j  + i]; // Z1
   Un[fx*fy*k + fx*j + i] = sum/7.0;
  }
  double *temp = U; U = Un; Un = temp;
 }

 double dx = 1.0;
 double dy = 1.0;
 double dz = 1.0;

 double startX = 0.0;
 double startY = 0.0;
 double startZ = 0.0;

 double endX = startX + dx;
 double endY = startY + dy;
 double endZ = startZ + dz;

 auto xdata = getPointData();

 std::vector<double> resultVector;
 for (size_t i = 0; i < xdata.size(); i += 3)
 {
  double result = 0.0;
  double xPos = xdata[i + 0];
  double yPos = xdata[i + 1];
  double zPos = xdata[i + 2];

  bool foundValue = false;

  if(xPos >= startX && xPos <= endX)
  if(yPos >= startY && yPos <= endY)
  if(zPos >= startZ && zPos <= endZ)
  {
   double h = 1.0/N;
   int ix = ceil((xPos-startX)/h);
   int iy = ceil((yPos-startY)/h);
   int iz = ceil((zPos-startZ)/h);

   foundValue = true;
   result = U[fx*fy*iz + fx*iy + ix];
  }

  resultVector.push_back(result);
 }

 k["Reference Evaluations"] = resultVector;

 free(U);
 free(Un);
}

std::vector<double> getPointData()
{
 std::vector<double> xdata;

 xdata.push_back(0.364); xdata.push_back(0.944); xdata.push_back(0.560);
 xdata.push_back(0.151); xdata.push_back(0.863); xdata.push_back(0.983);
 xdata.push_back(0.292); xdata.push_back(0.979); xdata.push_back(0.876);
 xdata.push_back(0.451); xdata.push_back(0.014); xdata.push_back(0.150);
 xdata.push_back(0.893); xdata.push_back(0.935); xdata.push_back(0.316);
 xdata.push_back(0.093); xdata.push_back(0.287); xdata.push_back(0.921);
 xdata.push_back(0.671); xdata.push_back(0.565); xdata.push_back(0.078);
 xdata.push_back(0.565); xdata.push_back(0.779); xdata.push_back(0.974);

 return xdata;
}

std::vector<double> getReferenceData()
{
 std::vector<double> ref;

 ref.push_back(0.978724);
 ref.push_back(0.960720);
 ref.push_back(0.738612);
 ref.push_back(0.713227);
 ref.push_back(0.988677);
 ref.push_back(1.001350);
 ref.push_back(1.001672);
 ref.push_back(0.974431);

 // Expected Solution:
  // X0 = +3.71
  // X1 = -2.34
  // Y0 = +1.32
  // Y1 = +0.78
  // Z0 = +2.25
  // Z1 = +1.81

 return ref;
}

#pragma once
#include <algorithm> 
#include "Model.h"



double LL2_012(int t1, int t2, int nn, double alpha, double beta1, double gamma1, double beta2, double gamma2, vector<double> data, double start0) {

	double temp = 0;
	double start1 = 0;
	for (int i = t1 + 1; i <= min(t2, nn);++i) {
        double mu1temp = mu1(i - t1, alpha, beta1, gamma1, start1);
		temp += mu1temp * data[i - 1] - (0.5) * mu1temp * mu1temp;
	}

	double start2 = mu1(t2 - t1, alpha, beta1, gamma1, start1);
	for (int i = t2 + 1; i <= nn; ++i) {
        double mu2temp = mu2(i - t2, alpha, beta1, gamma1, start2);
		temp += mu2temp * data[i - 1] - (0.5) * mu2temp * mu2temp;
	}

	return temp;
}


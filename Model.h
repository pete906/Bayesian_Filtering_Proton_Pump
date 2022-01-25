#pragma once


//  Created by Peter Johnson on 30/05/2014.
//  Copyright (c) 2014 Peter Johnson. All rights reserved.

using namespace std;



#include <vector>
#include <cmath>
#include <random>

// Range of parameter variables
double Alphahigh = 35, Alphalow = 20, dAlpha = 0.5;
//double bb = 0.21, aa = 0.01, dd = 0.001, Gammahigh = bb, Betahigh = bb, Gammalow = aa, Betalow = aa, dBeta = dd, dGamma = dd;
//nBeta = int(((Betahigh - Betalow + dBeta)) / dBeta), nGamma = int(((Gammahigh - Gammalow + dGamma)) / dGamma);
double gammaMin=0.01, betaMin=0.002;
int nGamma = 25, nBeta=25;
int nAlpha = int(((Alphahigh - Alphalow + dAlpha)) / dAlpha);




double int2gamma(int i){
    double output=0;
    if((1<=i)&&(i<=nGamma)){
        output= gammaMin*exp((pow(i,1.4)-1)/15);
    }
    else{
        cout << "Interger for Gamma out of range.";
    }
    return output;
}

double int2beta(int i){
    double output=0;
    if((1<=i)&&(i<=nBeta)){
        output= betaMin*exp((pow(i,1.4)-1)/15);
    }
    else{
        cout << "Interger for Beta out of range.";
    }
    return output;
}

vector<double > alphaVec(nAlpha,0.0),betaVec(nBeta,0.0), gammaVec(nGamma,0.0);

void GenerateABGVecs(){
    for(int i =1; i<=nAlpha; i++){
        alphaVec[i-1]=Alphalow + (i - 1) * dAlpha;
    }
    for(int i =1; i<=nBeta; i++){
        betaVec[i-1]=int2beta(i);
    }
    for(int i =1; i<=nGamma; i++){
        gammaVec[i-1]=int2gamma(i);
    }
}


// Distribution of Noise (must be normally distributed)
std::normal_distribution<double> Noise(0,1);

// Distribution of parameter variables
std::uniform_int_distribution<int> adist(1, nAlpha);
std::uniform_int_distribution<int> bdist(1, nBeta);
std::uniform_int_distribution<int> gdist(1, nGamma);
double AlphaDist(std::default_random_engine generator) { return Alphalow + (double(adist(generator)) - 1) * dAlpha; }
double BetaDist(std::default_random_engine generator) { return int2beta(bdist(generator)); }
double GammaDist(std::default_random_engine generator) { return int2gamma(gdist(generator)); }
vector< double> AlphaPriorVec(1 / nAlpha, int(nAlpha));
vector< double> BetaPriorVec(1 / nBeta, int(nBeta));
vector< double> GammaPriorVec(1 / nGamma, int(nGamma));




// Distribution of change-points
double p = 0.05;
std::geometric_distribution<int> CPDist(p);

double f1(int n, double p) {
	return p * pow(1 - p, n-1);
}
double f2(int n, double p) {
	return p * pow(1 - p, n-1);
}
double f3(int n, double p) {
	return p * pow(1 - p, n-1);
}
double f4(int n, double p) {
	return p * pow(1 - p, n-1);
}

double barF1(int n, double p) {
	return pow(1 - p, n);
}
double barF2(int n, double p) {
	return pow(1 - p, n);
}
double barF3(int n, double p) {
	return pow(1 - p, n);
}
double barF4(int n, double p) {
	return pow(1 - p, n);
}


// Functions of used in signal
double mu0( int t, double alpha, double  beta, double gamma, double start) {
	return 0;
}

double mu1(int t, double alpha, double  beta, double gamma, double start) {

    return sqrt(((start*start - alpha*alpha) * exp(-beta * (t))) + alpha*alpha);
}

double mu2(int t, double alpha, double  beta, double gamma, double start) {
    
	return start * (exp(-0.5*gamma * t));
}


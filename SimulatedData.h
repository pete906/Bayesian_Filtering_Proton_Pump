#pragma once
#include <random>
#include <vector>
#include <algorithm>
#include <chrono>
#include "Model.h"


vector<double> SimulatedDataRnd(int nCP, int nn, vector<double>& outputs) {
    // Define 'sig' to be returned.
	vector<double> sig(nn,0),temp(4,0.0);
    
    outputs=temp;
    // Define vectors for change points, betas, and gammas
	vector<int> CPs(1,0);
	vector<double> Bs(1, 0.0), Gs(1, 0.0);
    // Generate a random alpha
	unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // seed to generate random noise
	std::default_random_engine generator(seed);
	double alpha = AlphaDist(generator);
    
    // Generate nCP change-points, storing all less than or equal to nn
	for (int i = 1; i <= nCP;i++) {
		unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // seed to generate random noise
		std::default_random_engine generator(seed);
		int aa = CPs[i-1]+ max(20,CPDist(generator));
		// cout << aa << "\n";
		if ( aa <= nn) {
			CPs.push_back(aa);
		}
		else { i = nCP; }
	}

	// nCP redefined as the actual number of change-points in the data
	nCP = CPs.size();
	for (int i =2; i <= nCP;i++) {

		if ((i) % 2 == 0) {
            unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // seed to generate random noise
            std::default_random_engine generator(seed);
			Bs.push_back( BetaDist(generator));
			Gs.push_back(0);
		}
		else {
            unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // seed to generate random noise
            std::default_random_engine generator(seed);
			Bs.push_back(0);
			Gs.push_back(GammaDist(generator));
		}

	}
   

	for (int i = 2;i <= nCP;i++) {
		outputs.push_back(CPs[i-1]);
		outputs.push_back(alpha);
		outputs.push_back(Bs[i - 1]);
		outputs.push_back(Gs[i - 1]);
	}
    
	CPs.push_back(nn);
	for (int t =  CPs[0]+1; t <= min(CPs[1],nn); t++) {
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine generator(seed);
		sig[t-1] = mu0(t, alpha, Bs[0], Gs[0], 0);
	}
	double start = sig[CPs[1]];
	for (int i = 2; i < CPs.size(); i++) {
		for (int t = CPs[i - 1] + 1; t <= min(CPs[i],nn); t++) {
			unsigned seed = chrono::system_clock::now().time_since_epoch().count();
			std::default_random_engine generator(seed);
			if (i % 2 == 0) {
				sig[t-1] = mu1(t- CPs[i -1], alpha, Bs[i-1], Gs[i-1], start);
			}
			else {
				sig[t-1] = mu2(t- CPs[i - 1], alpha, Bs[i - 1], Gs[i - 1], start) ;
			}
		}
		start = sig[CPs[i]-1];

	}
    std::random_device rd;
    std::default_random_engine generatorn;
    generatorn.seed( rd() );
    for(int i = 1; i < sig.size(); i++) {
        
  
        sig[i-1]+= Noise(generatorn);
    }

	return sig;
}


vector<double> SimulatedSigInputs(vector<double> Inputs, int nn, int vars, int Lversion,double start) {
	vector<double> sig(nn, 0);
	int nCP = (Inputs.size() / (vars + 1));
	vector<int> CPs(nCP, 0.0);
	vector<double> As(nCP, 0.0), Bs(nCP, 0.0), Gs(nCP, 0.0);
	int a = 0,di=0;

	for (int i = 1; i <= nCP;i++) {
		CPs[i - 1] = int(Inputs[(i - 1) * (vars + 1)]);
		As[i - 1] = Inputs[(i - 1) * (vars + 1) + 1];
		Bs[i - 1] = Inputs[(i - 1) * (vars + 1) + 2];
		Gs[i - 1] = Inputs[(i - 1) * (vars + 1) + 3];
	}

	CPs.push_back(nn);
	if (Lversion == 0) {
		for (int t = CPs[0] + 1; t <= min(CPs[1], nn); t++) {
			sig[t - 1] = mu0(t, As[0], Bs[0], Gs[0], start);
		}
		start = sig[CPs[1]];
	}
	if (Lversion == 1) {
		di = 1;
		a = 1;
	}
	if (Lversion == 2) {
		di = 1;

	}
	//cout << "nCP=" << nCP << "   "<<CPs[nCP] <<   "\n";
	for (int i = 2-di; i <= nCP; i++) {
		for (int t = CPs[i - 1] + 1; t <= min(CPs[i], nn); t++) {
			if ((i +a)% 2 == 0) {
				sig[t - 1] = mu1(t - CPs[i - 1], As[i - 1], Bs[i - 1], Gs[i - 1], start);
			}
			else {
				sig[t - 1] = mu2(t - CPs[i - 1], As[i - 1], Bs[i - 1], Gs[i - 1], start);
			}
		}
		start = sig[CPs[i] - 1];
	}

	return sig;
}






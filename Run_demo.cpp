#include <fstream>
#include <iostream>
#include <random>

#include "Model.h"
#include "Likelihoods.h"
#include "SimulatedData.h"
#include "RunRoutinesOnData.h"



int main() {
    
    GenerateABGVecs();

    vector < double > Data, Sig, EstSig, outputs, estoutputs;

    int n=100;
    int nCP=2;
    double pi1, pi2;
    
    Data=SimulatedDataRnd(nCP, n, outputs);
    
    ofstream T1_File("Output.csv");


    estoutputs=RunMLE_2_prob(0, Data, n,0, pi1, pi2);

    
    EstSig = SimulatedSigInputs(estoutputs, n, 3, 0, 0);
    Sig = SimulatedSigInputs(outputs, n, 3, 0, 0);
    
    
    for (int i=1;i<=Data.size();i++){
        T1_File << Sig[i-1] << "," << Data[i-1] <<  "," <<  EstSig[i-1] << "\n";
    }
    
    return 0;
}


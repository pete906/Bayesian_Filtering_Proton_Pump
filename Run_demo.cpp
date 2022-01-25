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


    cout << Data.size() << "\n";
    
    estoutputs=RunMLE_2_prob(0, Data, n,0, pi1, pi2);
    cout  << "outputs1:  ";
    for (int i=1;i<=outputs.size();i++){
       cout  << outputs[i-1] << "," ;
    }
    cout  << "\n\n";
    
    cout  << "outputs2:  ";
    for (int i=1;i<=estoutputs.size();i++){
       cout  << estoutputs[i-1] << "," ;
    }
    cout  << "\n\n";
    
    cout << "pi1="<< pi1 << ",   pi2=" << pi2 << "\n";
    
    EstSig = SimulatedSigInputs(estoutputs, n, 3, 0, 0);
    Sig = SimulatedSigInputs(outputs, n, 3, 0, 0);
    
    
    cout << "Sig.size()=" << Sig.size() << ",    Data.size()=" << Data.size() << ",   EstSig.size()=" << EstSig.size() << "\n";
    
    
    for (int i=1;i<=Data.size();i++){
        T1_File << Sig[i-1] << "," << Data[i-1] <<  "," <<  EstSig[i-1] << "\n";
    }
    
   
    
    return 0;
}

// int main() {
//
//    vector < double > outputs, EstSig;
//    vector<  vector < double >> outputsMat;
//    outputsMat = readCSV("Final_Outputs.csv");
//    ofstream T2_File("FinalEstSig.csv");
//
//
//    for (int i=1; i<= outputsMat.size(); i++){
//        outputs=outputsMat[i-1];
//        EstSig = SimulatedSigInputs(outputs, 750, 3, 0,0);
//        cout << EstSig.size() << "\n";
//        for (int j=1; j<=EstSig.size();j++){
//            T2_File << EstSig[j-1] << ",";
//        }
//        T2_File << "\n";
//    }
//
//
//
//
//   GenerateABGVecs();
//
////    int CPs = 5, vars = 3, nn =200;
//    vector<    vector < double > > DataMat,DataMat_mu_sigma, SigMat;
//    vector < double > Data, Sig1, Sig2, outputs, outputs2;
//
//    string outputstring = "Outputs_ATP10_Pete.csv";
//    ofstream T2_File("Data_EstSig_ATP10_Pete.csv");
//    ofstream T_File("Data_EstSig.csv");
//    DataMat = readCSV("ATP10_Pete.csv");
//    cout << 1 << "\n";
//    DataMat_mu_sigma = readCSV("ATP10_Pete_mu_sigma.csv");
//        cout << 2 << "\n";
////    for (int i=1;i<=DataMat[0].size();i++){
////        cout << i << "  " <<  DataMat[0][i-1] << "\n";
////    }
//
//
//
//    for(int i=1;i<=DataMat_mu_sigma.size(); i++){
//        cout << DataMat_mu_sigma[i-1][0] << "  " << DataMat_mu_sigma[i-1][1] << "\n";
//    }
//    cout << 2.5 << "\n";
////    vector <int> testset={9};
//    vector <int> testset={3, 9, 11, 14, 16, 34, 37, 41, 48, 58, 69, 73, 96, 112, 131, 151};
//    vector < double > v(DataMat[0].size(),0.0), v2(2,0.0);
//    vector<    vector < double > >  DataMatTestSet(testset.size(), v), DataMatTestSet_mu_sigma(testset.size(), v2);
//
//    for(int i=1;i<=testset.size(); i++){
//        DataMatTestSet[i-1]=DataMat[testset[i-1]-1];
//        DataMatTestSet_mu_sigma[i-1]=DataMat_mu_sigma[testset[i-1]-1];
//    }
//        cout << 3 << "\n";
//
//
//
//    Data = DataMat[testset[0]-1];
//    cout << DataMat.size() << "   " << DataMat[0].size() << "\n";
//
////    vector<    vector < double > > DataMat2(1,DataMat[0]);
//
//
////    double Testset[1]={1};
////    for(int i=1; i<=1; i++){
////        DataMat2[i-1]=DataMat[Testset[i-1]-1];
////    }
//
//
//
//
////
////    DataMat[0].size()
////    DataMat.size()
////    Data=DataMat[2];
//
////    cout << Data.size() << "\n";
//
////    Data = SimulatedDataRnd_test(CPs, nn, outputs, 0,0);
//
////    cout <<  exp(std::numeric_limits<double>::lowest()) << "\n";
//
////    double snrEst=int(Data[max_element(Data.begin(), Data.end()) - Data.begin()]);
////    cout << snrEst << "\n";
////    if ((snrEst > 15) && (snrEst <100 )) {
////        dAlpha = 5.0,Alphahigh = snrEst + dAlpha*8, Alphalow = snrEst - dAlpha*3;
////    }
////    if ((snrEst >= 100)) {
////        dAlpha = 7.0, Alphahigh = snrEst + dAlpha * 8, Alphalow = snrEst - dAlpha * 3;
////    }
////    nAlpha = ((Alphahigh - Alphalow + dAlpha)) / dAlpha,
//
////
////    int Lversion = 1, start=2;
////    double Theta1MLE=100.0, Theta2MLE=175.0 , AlphaMLE=20.0, BetaMLE=0.5, GammaMLE=0.5, Beta2MLE=0.5,Gamma2MLE=0.5;
////    if (Lversion == 0) {
////        outputs = { 0, 0, 0, 0,Theta1MLE,AlphaMLE, BetaMLE, GammaMLE,Theta2MLE,AlphaMLE, Beta2MLE, Gamma2MLE };
////    }
////    if (Lversion == 1) {
////        outputs = { 0, AlphaMLE, BetaMLE, 0,Theta1MLE,AlphaMLE,0, GammaMLE,Theta2MLE,AlphaMLE, Beta2MLE, 0 };
////    }
////    if (Lversion == 2) {
////        outputs = { 0, AlphaMLE, 0,  GammaMLE ,Theta1MLE,AlphaMLE, BetaMLE,0,Theta2MLE,AlphaMLE, 0, Gamma2MLE };
////    }
//
//
////
////    double begint, endt;
//    vector < vector < double > > DistVecStor,ConIntVecStor;
//    double thresh =0.99, thresh2 = 0.99;
////    begint = omp_get_wtime();
//
////    for (int i=1;i<=nBeta;i++){
////        cout << int2beta(i) << "\n";
////    }
//
////    outputs2= RunMLE_2_reduced(2, Data,  nn,  10);
////    for (int i = 1; i<=outputs2.size(); i++){
////        cout << outputs2[i-1] << " , ";
////    }
////    cout << "\n";
//
////   Sig = SimulatedSigInputs(outputs2, nn, 3, 2,10);
////  Sig = SlidingMethod_1_dev(Data, thresh);
////  Sig = SlidingMethod_1_dist_conf(Data, thresh,DistVecStor,ConIntVecStor);
////    Sig = SlidingMethod_2_dist_reduced(Data, thresh,DistVecStor);
////    SigMat = Multi_SlidingMethod_1_2(DataMat, thresh);
////    Sig = SlidingMethod_1_2_alpha(Data, thresh,thresh2);
////    Sig1= SlidingMethod_1_2_alpha(Data, thresh, thresh2, outputs);
////    Sig2= SlidingMethod_1_2_alpha_off_off(Data, thresh, thresh2, outputs);
//
//
//        SigMat = Multi_SlidingMethod_1_2_alpha_sqrt(DataMatTestSet, DataMatTestSet_mu_sigma, thresh, thresh2, outputstring);
//
//
//    //    Sig = SimulatedSigInputs(outputs, nn, 3, Lversion, start);
////    Sig = SlidingMethod_1_2_dist(Data, thresh,DistVecStor);
//
////    endt = omp_get_wtime();
////    int elapsed_secs= int(endt - begint);
////
////    cout << "Computation time: " << elapsed_secs << ", or   " << int(elapsed_secs / (60 * 60)) << " hours, " << int((elapsed_secs / (60)) % 60) << " minutes, " << elapsed_secs % (60) << " seconds." << "\n";
//
//
//
////        cout << Data.size() << "\n";
////    cout << Sig.size() << "\n";
//
//
////    ofstream T3_File("LData.csv");
////    for (int i = 1; i <= DataMat2.size(); i++) {
////        for (int j = 1; j <= DataMat2[i-1].size(); j++) {
////            T3_File << DataMat2[i-1][j-1]<< "," ;
////        }
////        T3_File << "\n";
////    }
////    T3_File << "\n";
//
//
//
//    for (int i = 1; i <= SigMat.size(); i++) {
//        for (int j = 1; j <= SigMat[i-1].size(); j++) {
//            T_File <<  SigMat[i-1][j-1] << "," ;
//        }
//        T_File <<  "\n";
//    }
//
//
//
////    for (int i = 1; i <= SigMat.size(); i++) {
////        for (int j = 1; j <= SigMat[i-1].size(); j++) {
////            T2_File << SigMat[i-1][j-1]<< "," ;
////        }
////        T2_File << "\n";
////    }
////    T2_File << "\n";
//
//
//
////    ofstream T2_File("Data_EstSig.csv");
////    for (int j = 1; j <= DataMat.size(); j++) {
////        for (int i = 1; i <= DataMat[0].size(); i++) {
////            T2_File << SigMat[j-1][i - 1] << ",";
////        }
////        T2_File << "\n";
////    }
////    ofstream T1_File("DistVecStor.csv");
////    for (int i = 1; i <= DistVecStor.size(); i++) {
////            for (int j = 1; j <= nn; j++) {
////                T1_File << DistVecStor[i - 1][j-1] << ",";
////            }
////            T1_File << "\n";
////    }
////    ofstream T3_File("ConIntVecStor.csv");
////    for (int i = 1; i <= ConIntVecStor.size(); i++) {
////            for (int j = 1; j <= 3; j++) {
////                T3_File << ConIntVecStor[i - 1][j-1] << ",";
////            }
////            T3_File << "\n";
////    }
//    return 0;
//}


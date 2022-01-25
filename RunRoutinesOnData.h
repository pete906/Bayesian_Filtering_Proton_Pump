#pragma once



#include "Model.h"
#include "Likelihoods.h"


double(*pnt2func)(int, int, int, double, double, double, double, double, vector<double>, double);


vector < double> RunMLE_2_prob(int Lversion, vector<double> Data, int n,double start,double& pi1, double& pi2) {
	int bbstart, ggstart;
	double Theta1MLE, AlphaMLE, BetaMLE, GammaMLE, Theta2MLE, Beta2MLE, Gamma2MLE;
	vector < double> outputs;


    bbstart = nBeta;
    ggstart = nGamma;
    pnt2func = LL2_012;
	



    double Z0, Z1, Z2, Z;
    vector < double > z0v(n, 0);
	vector < double > z1v(n, 0);
	vector < double > z2v(n, 0);



	vector<double> L1(n, -INFINITY);
	vector<vector<double>> Storage(9, L1);
	Z0 = 0.0, Z1 = 0.0, Z2 = 0.0;
	pi1 = 0.0, pi2 = 0.0;


	for (int i = 1;i <= n;i++) {
        cout << i << "  \n";

		Storage[1][i - 1] = i;
		double temp = 0, maxx = -INFINITY;
        double prevAdj=0.0,Adj=0.0;
		for (int j = 1; j <= max(n - i, 1);j++) {
            double multi;
            if (Lversion == 0) {
                multi = log(bool(i == n) * (barF1(n, p)) + bool(j == n - i) * (f1(i, p) * barF2(j, p)) + bool(j < n - i) * (f1(i, p) * f2(j, p)));
            }
            if (Lversion == 1) {
                multi = log(bool(i == n) * (barF2(n, p)) + bool(j == n - i) * (f2(i, p) * barF1(j, p)) + bool(j < n - i) * (f1(i, p) * f2(j, p)));
            }
            if (Lversion == 2) {
                multi = log(bool(i == n) * (barF1(n, p)) + bool(j == n - i) * (f1(i, p) * barF2(j, p)) + bool(j < n - i) * (f1(i, p) * f2(j, p)));
            }

			for (int a = 1; a <= nAlpha;a++) {
				for (int b = 1; b <= nBeta;b++) {
					for (int g = 1; g <= nGamma;g++) {
						for (int bb = bbstart; bb <= nBeta;bb++) {
							for (int gg = ggstart; gg <= nGamma;gg++) {

								temp = multi + pnt2func(i, i + j, n, Alphalow + (a - 1) * dAlpha, int2beta(b), int2gamma(g), int2beta(bb), int2gamma(gg), Data, start);


								if (temp > maxx) {

                                    prevAdj=max(maxx,0.0);
                                    Adj=max(temp,0.0);
//                                    cout <<i << "  " <<  prevAdj << "  " << Adj << "\n";
                                    z0v[i - 1] = z0v[i - 1]*exp(prevAdj-Adj);
                                    z1v[i - 1] = z1v[i - 1]*exp(prevAdj-Adj);
                                    z2v[i - 1] = z2v[i - 1]*exp(prevAdj-Adj);

									maxx = temp;
									Storage[0][i - 1] = maxx;
									Storage[2][i - 1] = j;
									Storage[3][i - 1] = Alphalow + (a - 1) * dAlpha;
                                    Storage[4][i - 1] = int2beta(b);
                                    Storage[5][i - 1] = int2gamma(g);
                                    Storage[6][i - 1] = int2beta(bb);
                                    Storage[7][i - 1] = int2gamma(gg);
                                    Storage[8][i - 1] = Adj;
								}

                                if (i == n) {
                                    z0v[i - 1] +=  exp(temp-Adj);
                                }
                                if (j == n - i) {
                                    z1v[i - 1] +=  exp(temp-Adj);
                                }
                                if (j < n - i) {
                                    z2v[i - 1] +=  exp(temp-Adj);
                                }


//								if ((j == n-i-1)&& (g==nGamma)&& (a==nAlpha)&& (b==nBeta))  {
//                                    cout << "       " << Adj<< "\n";
//                                    cout << "       " << z0v<< "  " << z0v2* exp(static_cast<mpdouble>(Adj)) << "\n";
//                                    cout <<"       " <<z1v[i - 1] << "  " << z1v2[i - 1]* exp(static_cast<mpdouble>(Adj)) << "\n";
//                                    cout <<"       " <<z2v[i - 1] << "  " << z2v2[i - 1]* exp(static_cast<mpdouble>(Adj)) << "\n";
//								}


							}
						}
					}

				}
			}
		}

	}



	int MaxElementIndex = max_element(Storage[0].begin(), Storage[0].end()) - Storage[0].begin();
	Theta1MLE = Storage[1][MaxElementIndex];
	Theta2MLE = Theta1MLE + Storage[2][MaxElementIndex];
	AlphaMLE = Storage[3][MaxElementIndex];
	BetaMLE = Storage[4][MaxElementIndex];
	GammaMLE = Storage[5][MaxElementIndex];
	Beta2MLE = Storage[6][MaxElementIndex];
	Gamma2MLE = Storage[7][MaxElementIndex];
    double maxAdj= Storage[8][MaxElementIndex];




    for (int k = 1;k < n;k++) {
        Z1 += z1v[k - 1]*exp(Storage[8][k-1]-maxAdj);
        Z2 += z2v[k - 1]*exp(Storage[8][k-1]-maxAdj);
    }
    Z0 = z0v[n - 1]*exp(Storage[8][n-1]-maxAdj);

    Z = Z0 + Z1 + Z2;// barF1 needs to change with routine
	pi1 = (Z1 + Z2) / Z;
	pi2 = (Z2) / Z;


	if (Lversion == 0) {
		outputs = { 0, 0, 0, 0,Theta1MLE,AlphaMLE, BetaMLE,0,Theta2MLE,AlphaMLE, 0, GammaMLE };
	}
	if (Lversion == 1) {
		outputs = { 0, AlphaMLE, BetaMLE, 0,Theta1MLE,AlphaMLE,0, GammaMLE,Theta2MLE,AlphaMLE, Beta2MLE, 0 };
	}
	if (Lversion == 2) {
		outputs = { 0, AlphaMLE, 0,  GammaMLE ,Theta1MLE,AlphaMLE, BetaMLE,0,Theta2MLE,AlphaMLE, 0, Gamma2MLE };
	}

	return outputs;
}

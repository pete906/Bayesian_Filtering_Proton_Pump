# Bayesian_Filtering_Proton_Pump
This respository contains a demo of the application of Bayesian Stochastic Filtering for paper titled "Direct observation of regulation by mode-switching of the mammalian-brain V-ATPase".

The demo simulates some data from the described model and uses Bayesian Stochastic Filtering techniques to filter out the noise and estimate the most probable (Maximum a posteriori estimate) of the underlying signal. See sections on 'Stochastic model description', 'Stochastic Filtering' and 'Sliding method' in paper for more information.

The depostitory contains:
 Compiled source code.
 A simulated dataset to demo the code.

- [System Requirements](#system-requirements)
- [Installation guide](#installation-guide)
- [Demo](#demo)
- [Instructions for use](#instructions-for-use)

# System requirements
  
 ## Hardware requirements
  The code used in the Demo requires only a standard computer with enough RAM to support the in-memory operations.

  Does not require any non-standard hardware, however the code is parallelisable (via OpenMP) and so parallel processing will increase the speed with more CPU cores available. Results for paper were produced using KU server with 54 cores.
 
 ## Software requirements
  The code used in the Demo requires only a C++ and Python complier and an OS that can support. 
  
  Versions the software has been tested on:
  
  + macOS Monterey, Version 12.1
  + g++ (GCC) 12.0.5
  + Python 2.7.18

# Installation guide

  No installation required, other than suitable C++ complier, e.g. g++ (GCC), and python for plotting of results.
  
  See [Demo](#demo) section below for instructions on running the demo.

# Demo

  To run the demo of the Bayesian Stochastic Filtering algorithm on the simulated data, firstly download all files. 
  
  This can be done via the command:
  ```
  git clone https://github.com/pete906/Bayesian_Filtering_Proton_Pump.git
  ```
  Nativigate to the "Bayesian_Filtering_Proton_Pump" folder created; This can be achieved by moving the folder to the desktop and using the command 
  ```
  cd Desktop/Bayesian_Filtering_Proton_Pump
  ```
  The command 
  ```
  make
  ```
  will run demo, output the results and plot the results.
  

  The code should give you an approximate percentage of analysis which has been completed. Then will write the outputs to a csv file called "Output.csv".
  
  In the "Output.csv" file will be three columns of data, the first is the unobservable signal (available as we are simulating the data), the second is the observed data (the unobservable signal plus noise), and the third is the resulting most probable (MAP) estimate for the signal calculated via the Bayesian Stochastic Filtering algorithm. 
 
  The Makefile (run using the "make" command) also produces a plot of the results using a small python script "Plot_outputs.py", however a similar graph may be created and viewed using excel or similar program.

  Expected run time for demo on a "normal" desktop computer is approximately 30 seconds (possibly a few minutes on older computers).
  
  # Instructions for use
  
  This demo can be applied to real data rather than simulated data by changing the vector 'Data' in the 'Run_demo.cpp' to be equal to the real data. For example if the real data was contained in a file 'RealData.csv' we could change the lines 
 ```
 int nCP=2;
 int n=100;
 Data=SimulatedDataRnd(nCP, n, outputs);
 ```
 to 
 ```
 Data=readCSV('RealData.csv');
 int n=Data.size();
 ```
 where the 'readCSV()' function could be defined as 
 ```
 vector<double> readCSV(string filename){
    vector<double> vec={};
    ifstream in(filename);
    string line;
    while (getline(in, line))                   
    {   string datatemp;
        datatemp=line.substr(0, line.find(",,"));
        stringstream ss(datatemp);
        vector<double> row={};
        string data;
        int i=0;
        while (getline(ss, data, ',')){       
                row.push_back(stod(data));      
        }
        for(int i=1;row.size(); i++){
            cout << row[i-1] << "\n";
        }
        vec=row;
    }
    return vec;
}
 ```
 or similar.
  

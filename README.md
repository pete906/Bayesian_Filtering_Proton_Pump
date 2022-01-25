# Bayesian_Filtering_Proton_Pump
Demo of Bayesian Filtering application to proton-pumping, inactive and proton-leaky modes.

- [System Requirements](#system-requirements)
- [Installation guide](#installation_guide)
- [Demo](#demo)

 

A README file includes:
Compiled source code.
A simulated dataset to demo the code.

  
  # System requirements
  
  Versions the software has been tested on:
  
  g++ (GCC) 4.8.5 20150623 (Red Hat 4.8.5-44)
  Python 2.7.18

  Does not require any non-standard hardware, however the code is parallelisable and so parallel processing will increase the speed with more cpu available. Results  for produced using KU server with 54 cores.

# Installation guide

  No installation required, other than suitable C++ complier, e.g. g++ (GCC), and python for plotting of results.

# Demo


  To run the Bayesian Filtering agorithm on the simulated data, firstly download all files. 
  
  This can be done via the command:
  
   git clone https://github.com/pete906/Bayesian_Filtering_Proton_Pump.git
  
  Nativigate to the "Bayesian_Filtering_Proton_Pump" folder created; This can be achieved by moving the folder to the desktop and using the command 
  
   cd Desktop/Bayesian_Filtering_Proton_Pump
  
  Type "make" and press enter to run demo.

  The code should give you a approximate percentage of analysis which has been completed. Then will write the outputs to a csv file called "Output.csv".
  
  In the "Output.csv" file will be three columns of data, the first is the unobservable signal, the second is the observed data (signal plus noise), and the third is the resulting MAP estimate for the signal calculated via the Bayesian Stochastics Filtering algorithm. 
 
  The Makefile (run using the "make" command) also produces a plot of the results using a small python script "Plot_outputs.py", however a similar graph may be created and viewed using excel or similar program.

  Expected run time for demo on a "normal" desktop computer is approximately 30 seconds (possibly a few minutes on older computers).

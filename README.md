# Bayesian_Filtering_Proton_Pump
Demo of Bayesian Filtering application to proton-pumping, inactive and proton-leaky modes.

- [System Requirements](#system-requirements)

 
Compiled standalone software and/or source code
A small (simulated or real) dataset to demo the software/code
A README file that includes:

# System requirements
  
  Versions the software has been tested on:
  
  g++ (GCC) 4.8.5 20150623 (Red Hat 4.8.5-44)

  Does not require any non-standard hardware, however the parallel processing of the data will be increased with more cpu available. Results produced using KU server with 54 cores.

# Installation guide

  No installation required, other than suitable C++ complier, e.g. g++ (GCC).

# Demo

  To run the Bayesian Filtering agorithm on the example data "ExampleData.csv", firstly download all files. 

  Open the command line prompt and navigate to loction of downloaded files.
  Type "make" and press enter to run Demo.

  The resulting MAP estimate for the signal is given in the "Output.csv" file where the first column is the example data and the last column is its corresponding the MAP estimate. Can be viewed using excel or similar program.

  Expected run time for demo on a "normal" desktop computer is x days.

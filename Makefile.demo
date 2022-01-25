# Declare variables 
CPP = /usr/local/opt/llvm/bin/clang
CPPFLAGS = -I/usr/local/opt/llvm/include -fopenmp
LDFLAGS = -L/usr/local/opt/llvm/lib

# Makefile in command line will run first command
all: CreateCode RunNewCode PlotOutput
	

CreateCode: 
	g++ Run_demo.cpp -o RunCode -std=c++11 -Ofast 
	
RunNewCode: 
	./RunCode

PlotOutput: 
	python Plot_outputs.py






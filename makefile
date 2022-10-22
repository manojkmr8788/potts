CC = g++
CFLAGS = -w
OPFLAGS = -O3 -march=native
LDFLAGS = -lm -fpermissive
OUTPUT = rfpm.out

all:
	$(CXX) $(CFLAGS) $(OPFLAGS) GCoptimization.cpp LinkedBlockList.cpp RFPM_3D.cpp $(LDFLAGS) -o $(OUTPUT) 
	

CC = g++
CFLAGS = -w -DGCO_ENERGYTYPE=double
OPFLAGS = -O3 -march=native
LDFLAGS = -lm -fpermissive
OUTPUT = rfpm.out

all:
	$(CC) $(CFLAGS) $(OPFLAGS) GCoptimization.cpp LinkedBlockList.cpp RFPM_3D.cpp $(LDFLAGS) -o $(OUTPUT) 
	

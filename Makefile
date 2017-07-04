# Enviorment
SRCPATH := src/
gsvm := g++ -std=c++0x -Wall -I$(LINEARINC) -L$(LINEARLIB)

sample:
	$(gsvm) $(SRCPATH)libsvm_sample.cpp -lsvm -o $(SRCPATH)libsvm_sample.o

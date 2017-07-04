# Enviorment
SRCPATH := src/
LINEARINC :=/usr/include
LIB :=/usr/lib
SVMINC := /usr/include/libsvm
LIB :=/usr/lib

glinear := g++ -std=c++11 -Wall -I$(LINEARINC) -L$(LIB)
gsvm := g++ -std=c++0x -Wall -I$(SVMINC) -L$(LIB)

sample:
	$(glinear) $(SRCPATH)liblinear_sample.cpp -llinear -o $(SRCPATH)liblinear_sample.o
	$(gsvm) $(SRCPATH)libsvm_sample.cpp -lsvm -o $(SRCPATH)libsvm_sample.o

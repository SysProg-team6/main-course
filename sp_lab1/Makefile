#Makefile
all: policy
policy: main.o InsurancePolicy.o
        g++ main.o InsurancePolicy.o -o policy
main.o: main.cpp
        g++ -c main.cpp
InsurancePolicy.o: InsurancePolicy.cpp
        g++ -c InsurancePolicy.cpp
clean: 
        rm -rf *.o policy
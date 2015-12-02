#include <fstream>
#include <iostream>
#include <vector>

// supplied code:
template<typename T>
void writelst(std::ostream &os, std::vector<T> &l) {
	os << '{';
	if (!l.empty()) {
		for(auto i=l.begin();i!=l.end()-1;++i)
			os << *i << ',';
		os << l.back();
	}
	os << '}';
}

void start(int t) {
	std::cout << t << ": START" << std::endl;
}

void end(int t) {
	std::cout << t << ": END" << std::endl;
}

void consume(int t, int m, std::vector<int> inputs) {
	std::cout << t << ": ";
	writelst(std::cout,inputs);
	std::cout << " => [" << m << "]" << std::endl;
}

void produce(int t, int m, std::vector<int> outputs) {
	std::cout << t << ": [" << m << "] => ";
	writelst(std::cout,outputs);
	std::cout << std::endl;
}

template<typename T>
std::vector<T> readvector(std::istream &is) {
	int n;
	is >> n;
	std::vector<T> ret;
	for(int i=0;i<n;i++) {
		T temp;
		is >> temp;
		ret.emplace_back(std::move(temp));
	}
	return ret;
}

// add your code here (definition of data type "machine", function
// to do the simulation, main function, etc).


// below is not complete... it is just code that you should 
// use inside your own function to load in the machines...
//
//
	std::ifstream mfile(filename); // filename should be a char *
	if (!mfile.is_open()) {
		std::cerr << "bad input file name" << std::endl;
		exit(-1);
	}
	int endtime;
	mfile >> endtime; // endtime is now the last time (0 is the first time)
	int nmachines;
	mfile >> nmachines;
	for(int i=0;i<nmachines;i++) {
		int delay;
		mfile >> delay;
		std::vector<int> inputs = readvector<int>(mfile);
		std::vector<int> outputs = readvector<int>(mfile);
		// at this point you can create a machine
		// i is its id
		// delay is how long it takes to process
		// inputs are the products it consumes
		// outputs are the products it generates
	}

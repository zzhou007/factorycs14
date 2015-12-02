#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stdlib.h> 
#include <algorithm>


using namespace std;

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

void start(int t) {												//outputs start
	std::cout << t << ": START" << std::endl;
}

void end(int t) {										//outputs end
	std::cout << t << ": END" << std::endl;
}

void consume(int t, int m, std::vector<int> inputs) {				//outputs consumed
	std::cout << t << ": ";
	writelst(std::cout,inputs);
	std::cout << " => [" << m << "]" << std::endl;
}

void produce(int t, int m, std::vector<int> outputs) {				//outputs produced			
	std::cout << t << ": [" << m << "] => ";
	writelst(std::cout,outputs);
	std::cout << std::endl;
}

template<typename T>
std::vector<T> readvector(std::istream &is) {        //used in main
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
//class compare
//{
//public:
 //  bool operator()(pair<int,int> a,pair <int,int> b)
  // {
  //    return true;
  // }
//};

typedef pair<int, int> P;
std::priority_queue<P,vector<P>, greater<P>> event;

struct machine{
   std::vector<int> outputs;
   std::vector<int> inputs;
   int time = 0;
   int number = 0;
   bool working = false;
};

class factory{
   public:
   void makeevents()
	{
		for (unsigned i = 0; i < v.size(); i++)
		{
			//cout << v.at(i).number;
			event.push(make_pair(0, v.at(i).number));
		}
	}
	void eat()
	{
		for (unsigned i = 0; i < v.size(); i++)
		{
			if(v.at(i).inputs.size() == 0)
			{
				//cout << v.at(i).number << endl;
				//cout << "top second " << event.top().second << endl;
				if (event.top().second == v.at(i).number)
				{
					//cout << "m number :" << event.top().second << " working :" << v.at(event.top().second).working << endl;
					v.at(i).working = true;
					event.pop();
					consume(curtime,v.at(i).number,v.at(i).inputs);
					event.push(make_pair(curtime+v.at(i).time,v.at(i).number));
				}
			}
			else 
			{
				if (productnum.size() == 0)
				{
					v.at(i).working = false;
					//cout << event.top().first << " , " << event.top().second << endl; 
					event.pop();
					event.push(make_pair(curtime+1,v.at(i).number));
					//debug
					//cout << event.top().first << endl;
				}
				else 
				{
					if (event.top().second == v.at(i).number)
					{
						unsigned allreq = 0;
						for (unsigned j = 0; j < v.at(i).inputs.size(); j++) 
						{
							for (unsigned k = 0; k < productnum.size(); k++)
							{
								//debug
								//cout << event.top().first << endl;
								//cout << event.top().first << endl;
								if (v.at(i).inputs.at(j) == productnum.at(k).first
									&& productnum.at(k).second != 0)						//
								{
									allreq ++;
									//cout << event.top().first << endl;
								}
							}
						}
						if (allreq == v.at(i).inputs.size())
						{
							v.at(i).working = true;
							//cout << "start :" <<event.top().first << " , " << event.top().second << endl;
							event.pop();
							//cout << "start :" <<event.top().first << " , " << event.top().second << endl;
							consume(curtime,v.at(i).number,v.at(i).inputs);
							event.push(make_pair(curtime+v.at(i).time,v.at(i).number));
							for (unsigned r = 0; r < v.at(i).inputs.size(); r++)
							{
								for (unsigned p = 0; p < productnum.size(); p++)
								{
									if (v.at(i).inputs.at(r) == productnum.at(p).first)
										productnum.at(p).second--;
								}
							}
						}
						else
						{
								v.at(i).working = false;
								event.pop();
								event.push(make_pair(curtime+1,v.at(i).number));
								//debug
								//cout << event.top().first << endl;
								
						}				
					}
				}
			}
		}
	}
   void begin(int endtime)
   {
		start(curtime);
		makeevents();
		//for (unsigned i = 0; i < v.size(); i++)
		//{
		//	event.pop();
		//	cout << i << event.top().first << event.top().second << endl;
		//	event.pop();
		//}
		
		//debug
		//cout << event.top().first;
		
		while(curtime==event.top().first)
		{
			vector <pair<int,int>> store;
			store.clear();
			bool newproduct = true;
			while (event.top().first == curtime && !event.empty())
			{
				store.push_back(make_pair(event.top().first,event.top().second));
				//cout << "m number :" << event.top().second << " working :" << v.at(event.top().second).working << endl;
				if (v.at(event.top().second).working == true)
				{
					produce(curtime, event.top().second, v.at(event.top().second).outputs);
					for (unsigned i = 0; i < v.at(event.top().second).outputs.size(); i++)
					{
						for (unsigned j = 0; j < productnum.size(); j++)
						{
							if (v.at(event.top().second).outputs.at(i) == productnum.at(j).first)
							{
								productnum.at(j).second++;
								newproduct = false;
							}
						}
						if (newproduct)
						{
							productnum.push_back(make_pair(v.at(event.top().second).outputs.at(i),1));
							//sort(productnum.begin(),productnum.end());
						}
						newproduct = true;
					}
				}
				event.pop();
			}
			//cout << store.size() << endl;
			for (unsigned i = 0; i < store.size(); i ++)
			{
				event.push(store.at(i));
				//cout << store.at(i).first << " , " << store.at(i).second << endl;
			}

            eat();

			if (event.top().first > endtime)
				break;
			curtime = event.top().first;
		}
	end(endtime);
}
   void makemech(int id, int nmachines, std::vector<int> inputs, std::vector<int> outputs, int delay)
   {
      machine temp;
      temp.outputs = outputs;
      temp.inputs = inputs;
      temp.time = delay;
      temp.number = id;
      
      v.emplace_back(temp);
   }
   private:
   
	std::vector<pair<int,int>> productnum;
	std::vector <machine> v;
	
   
   int curtime=0;
};
//typedef pair<int, int> P;
//priority_queue< P, vector<P>, greater<P> > Q;



// below is not complete... it is just code that you should 
// use inside your own function to load in the machines...
//
//
int main(int argc, char **argv)
{
   factory a;
	std::ifstream mfile(argv[1]); // filename should be a char *
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
      a.makemech(i,nmachines, inputs,outputs,delay);
	}
   a.begin(endtime);
}

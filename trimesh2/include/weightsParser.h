#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <array>
#include <map>
#include <vector>



using namespace std;

// std::map<int, std::map<std::string, double>> parse(string argFile);
std::vector<std::vector<double>> getWeights();
std::vector<std::string> readJoints(ifstream& flux);
std::vector<double> readWeights(ifstream& flux, int &id);

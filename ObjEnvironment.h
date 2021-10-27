#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

/*! \file ObjEnvironment.h Contains only the Environment Class. Attention, this class is not the sofware rte, yet the real environment. */
/**
* For test cases, the real environment is simulated via an input file. 
* This file can contain many lines to detect many objects, but the thread structres are not configured for this! I would not recommend to do it. 
* The first three numbers are the coordinates of the object (not relative), the third one is the objectclass. 
*/

class Environment
{
public:
	vector<vector<double>> real_object_coordinates;
	vector<int> real_object_type;
	Environment(string filename);
	~Environment();
};


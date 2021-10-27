#include "ObjEnvironment.h"



Environment::Environment(string filename)
{
	string line;
	ifstream myfile(filename);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			stringstream stream(line);
			vector<double> current_real_object_coordinates(3);
			for (int i = 0; i < 3; i++) {
				stream>>current_real_object_coordinates[i];
				//cout << line[i]<<endl;
				//cout << current_real_object_coordinates[i] << endl;
			}
			real_object_coordinates.push_back(current_real_object_coordinates);
			int current_type;
			stream >> current_type;
			real_object_type.push_back(current_type);
		}
		myfile.close();
	}
}


Environment::~Environment()
{
}

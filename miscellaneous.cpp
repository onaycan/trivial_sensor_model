#include "miscellaneous.h"


string tabs(int i) {
	string staff(i, '\t');
	return staff;
}

int Ltwnorm(vector<type_scaled_obj_coords> c) {
	int ret = 0;
	for (unsigned int i = 0; i < c.size(); i++)
		ret += int(pow(c[i], 2));
	return ret;
}
#pragma once
#include <string>
#include <fstream>
using namespace std;
class Save
{
public:


	static void save(string namefile, const string& data, bool forceOverride = true)
	{
		ofstream file(string("save/").append(namefile));

		file.clear();

		file << data;

		file.close();

		
	}
};


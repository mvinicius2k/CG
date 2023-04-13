#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
using namespace std;
//Responsável pela parte de salvar e carregar
class Persistence
{
public:

	static string GetPath(string filename)
	{
		return string("save\\").append(filename);
	}

	static void Save(string namefile, const string& data, bool forceOverride = true)
	{
		auto path = GetPath(namefile);

		ofstream file(path);

		auto backup = Load(namefile);

		if (backup != nullptr && !forceOverride)
		{
			cout << "Já há um save em " << path << endl;
			return;
		}

		file.clear();

		file << data;

		file.close();

		
	}

	static vector<string>* Load(string namefile)
	{
		auto path = GetPath(namefile);
		ifstream file;
		file.open(path);

		auto input = new vector<string>();

		PrintCurrentSaveFiles();


		if (file.fail())
		{
			cout << "Deu ruim ao abrir o " << path << endl;
			return nullptr;
		}




		if (file.is_open())
		{
			string line;
			while (getline(file, line)) 
			{
				if(!line.empty())
					input->push_back(line);
			}
		}
		
		return input;

	}
	static void PrintCurrentSaveFiles()
	{
		for (const auto& entry : std::filesystem::directory_iterator(".\\save"))
			std::cout << entry.path() << std::endl;
	}
};


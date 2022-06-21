#pragma once
#include <string>
#include <regex> 
#include "../bib/Vetor3D.h"
#include <vector>
#include <sstream>
#include <iostream>
#include "../objects/model3d.h"
#include "../objects/camera3D.h"
#include <utils/strings.h>
#define NAMEOF(name) #name

enum ClassType
{
	None, EModel3D, ECamera3D
};
class Serialization
{
public:
	
	static ClassType GetType(string& line)
	{
		if (line == typeid(Model3D).name())
			return EModel3D;
		else if (line == typeid(Camera3D).name())
			return ECamera3D;
		else
			cout << "Linha " << line << " não é um objeto" << endl;
		return None;
	}

	static string Vectors3DToString(vector<Vetor3D>& vectors)
	{
		std::stringstream ss;
		ss << "[" << endl;
		for (auto vector : vectors)
			ss << Strings::Vector3DToString(vector) << endl;

		ss << "]";
		return ss.str();
	}

	

	static string MaterialsToString(vector<Material*>& materials)
	{
		std::stringstream ss;
		ss << "[" << endl;
		for (auto material : materials)
			ss << material->serialize();

		ss << "]";
		return ss.str();
	}


	template <class T>
	static bool LineIsObject(std::string& line, T& obj)
	{
		return line == typeid(T).name();

	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="line"></param>
	/// <param name="variable"></param>
	/// <returns>nullptr se  não for possível obter o valor</returns>
	static bool TryGetValue(std::string& line, std::string varname, std::string*& output)
	{

		if (varname == "") {
			output = new std::string(line);
			return true;
		}

		auto expression = std::string(varname).append("=.*");
		
		if (regex_match(line, std::regex(expression)))
		{
			std::smatch resultRight;
			regex_search(line, resultRight, std::regex("=.*"));
			auto right = resultRight.str();
			output = new string(std::string(right.substr(1)));
			return true;
		}


		return false;

	}

	

	static bool EndOfArray(string& line)
	{
		auto b = line.find(']') != std::string::npos;
		return b;
	}

	static bool GetBool(std::string& line, std::string varname, bool defaultValue = false)
	{
		std::string* valueStr = nullptr;
		if (TryGetValue(line, varname, valueStr))
		{
			return  *valueStr == "1";
		}

		return defaultValue;
	}

	static string GetString(std::string& line, std::string varname, string defaultValue = "")
	{
		std::string* valueStr = nullptr;
		if (TryGetValue(line, varname, valueStr))
			return *valueStr;
		return defaultValue;

	}

	static float GetFloat(std::string& line, std::string varname, float defaultValue = 0.f)
	{
		std::string* valueStr = nullptr;
		if (TryGetValue(line, varname, valueStr))
		{
			return std::stof(*valueStr);
		}

		return defaultValue;
	}

	static float GetInt(std::string& line, std::string varname, int defaultValue = 0.f)
	{
		std::string* valueStr = nullptr;
		if (TryGetValue(line, varname, valueStr))
		{
			return std::stoi(*valueStr);
		}

		return defaultValue;
	}

	static Vetor3D GetVetor3D(std::string& line, std::string varname = "", Vetor3D defaultValue = Vetor3D(0, 0, 0))
	{
		std::string* valueStr = nullptr;

		if (TryGetValue(line, varname, valueStr))
		{
			std::smatch matches;
			auto valuesStr = std::regex_search(*valueStr, matches, std::regex("([-]?[0-9]*[.]?[0-9]+)\\; ([-]?[0-9]*[.]?[0-9]+)\\; ([-]?[0-9]*[.]?[0-9]+)"));
			
			if (matches.size() == 4)
				return Vetor3D(std::stof(matches[1]), std::stof(matches[2]), std::stof(matches[3]));

			else
			{
				std::cout << "Vetor mal formado em " << line << std::endl;
			}
			
		}
		return defaultValue;
	}


	

};



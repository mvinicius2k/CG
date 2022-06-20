#pragma once
#include <string>
#include <regex> 
#include "../bib/Vetor3D.h"
#include <vector>
#include <sstream>
#include <iostream>
#include "../objects/model3d.h"
#define NAMEOF(name) #name

class Serialization
{
public:
	
	static string Vectors3DToString(vector<Vetor3D> vectors)
	{
		std::stringstream ss("[");
		for (auto vector : vectors)
			ss << Strings::Vector3DToString(vector) << endl;

		ss << "]";
		return ss.str();
	}


	static bool LineIsObject(std::string& line, std::string className)
	{
		auto regexExpression = std::string(className).append("{");

		return std::regex_match(line, std::regex(regexExpression));

	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="line"></param>
	/// <param name="variable"></param>
	/// <returns>nullptr se  não for possível obter o valor</returns>
	static bool TryGetValue(std::string& line, std::string varname, std::string *output)
	{

		auto expression = std::string(varname).append("=.*");
		
		if (regex_match(line, std::regex(expression)))
		{
			std::smatch resultRight;
			regex_search(line, resultRight, std::regex("=.*"));
			auto right = resultRight.str();
			output = new std::string(right.substr(1, right.length() - 1));
			return true;
		}

		return false;

	}

	

	static bool TryAssing(std::string& line, std::string varname, bool* output)
	{
		std::string* valueStr = nullptr;
		if (TryGetValue(line, varname, valueStr))
		{
			*output = *valueStr == "1";
			return true;
		}
		return false;
	}

	static bool TryAssing(std::string& line, std::string varname, std::string* output)
	{
		return TryGetValue(line, varname, output);
	}

	static bool TryAssing(std::string& line, std::string varname, Vetor3D* output)
	{
		std::string* valueStr = nullptr;

		if (TryGetValue(line, varname, valueStr))
		{
			std::smatch matches;
			auto valuesStr = std::regex_search(*valueStr, matches, std::regex("[+-]?([0-9]*[.])?[0-9]+"));
			
			if (matches.size() == 3)
				output = new Vetor3D(std::stof(matches[0]), std::stof(matches[1]), std::stof(matches[2]));
			else
			{
				std::cout << "Vetor mal formado em " << line << std::endl;
				return false;   
			}


			return true;
		}
		return false;
	}

	static bool TryAssing(std::string& line, std::string varname, vector<Object*> output)
	{
		std::string* valueStr = nullptr;

		if (!TryGetValue(line, varname, valueStr))
			return false;
		
		if (valueStr->substr(0, valueStr->length() - 2) == typeid(Model3D).name())
		{
			Model3D::deserialize();
		}
			

			std::smatch matches;
			auto valuesStr = std::regex_search(*valueStr, matches, std::regex("$.*$"));

			if (matches.size() == 3)
				output = new Vetor3D(std::stof(matches[0]), std::stof(matches[1]), std::stof(matches[2]));
			else
			{
				std::cout << "Vetor mal formado em " << line << std::endl;
				return false;
			}


			return true;
		}
		return false;
	}

	//static vector<std::string>& SpitString(std::string& line, char delimiter)
	//{
	//	auto chunk = std::stringstream();
	//	auto strings = std::vector<std::string>();
	//	for (auto l : line)
	//	{
	//		if (l == delimiter)
	//		{
	//			strings.push_back(chunk.str());
	//			chunk.clear();
	//			continue;
	//		}

	//		chunk << l;
	//	}
	//}

	

};



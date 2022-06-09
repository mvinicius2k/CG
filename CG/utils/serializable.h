#pragma once
#include <string>
#include <regex> 
#include "strings.h"
#include "../bib/Vetor3D.h"
#define NAMEOF(name) #name
using namespace std;
template<typename T>
class Serializable
{
public:
	virtual string serialize() = 0;

	virtual T* deserialize(string& str) = 0;
	
	static bool lineIsObject(string& line, string className)
	{
		auto regex = regex(string(className).append("{"));

		smatch founded;

		return regex_match(line, founded, regex);

		

	}

	static string* getValue(string& line, string variable)
	{

		auto regex = regex(string(variable).append("="));
		string value = nullptr;
		smatch founded;

		if (regex_match(line, founded, regex))
		{
			regex_search(line, founded, regex("=.");

			value = founded.str().replace("\n", "");

		}

		return value;

	}

	

	static bool TryAssing(string& line, string varname, bool* value)
	{
		auto valueStr = getValue(line, varname);
		try
		{
			value = valueStr == "1";
			return true;
		}
		catch (const std::exception& e)
		{
			e.what();
			return false;
		}
	}

	static bool TryAssing(string& line, string varname, string* value)
	{
		auto valueStr = getValue(line, varname);
		try
		{
			value = valueStr;
			return true
		}
		catch (const std::exception& e)
		{
			e.what();
			return false;
		}
	}

	static bool TryAssing(string& line, string varname, Vetor3D* value)
	{
		auto valueStr = getValue(line, varname);
		try
		{

			valueStr = regex_replace(*valueStr, regex("(|)"), "");

			return true;
		}
		catch (const std::exception& e)
		{
			e.what();
			return false;
		}
	}

	

};



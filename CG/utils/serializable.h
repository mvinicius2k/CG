#pragma once
#include <string>
#include <vector>

template <Serializable T>
class Serializable
{
public:
	virtual std::string serialize() = 0;
	
	static T* Deserialize(std::vector<std::string> &line)
	{
		auto obj = new T();
		
		
	}

	
	
protected:
	virtual T* deserialize(vector<std::string>& line) = 0;

private:

};

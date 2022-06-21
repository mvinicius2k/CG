#pragma once
#include <string>
#include <vector>


template <class T> class Serializable
{
public:
	virtual std::string serialize() = 0;
	virtual T* deserialize(std::vector<std::string>::iterator &lines) = 0;

private:

};


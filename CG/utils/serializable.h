#pragma once
#include <string>
#include <vector>

//Acho que isso deveria ter sido exclu�do, acho que nada usa isso

template <class T> class Serializable
{
	
public:
	virtual std::string serialize() = 0;
	virtual T* deserialize(std::vector<std::string>::iterator &lines) = 0;

private:

};


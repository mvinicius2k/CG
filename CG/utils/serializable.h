#pragma once
#include <string>


template <Serializable T>
class Serializable
{
public:
	virtual std::string serialize() = 0;
	static T* Deserialize();
	

private:

};

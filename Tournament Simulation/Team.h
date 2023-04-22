#pragma once

#include <string>

class Team
{
public:
	Team(const std::string& name, double rating);
	std::string name;
	double rating;
};

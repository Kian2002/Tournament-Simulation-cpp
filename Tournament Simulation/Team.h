#pragma once

#include <string>

class Team
{
public:
	Team(const std::string& name, int rating);
	std::string name;
	int rating;
};

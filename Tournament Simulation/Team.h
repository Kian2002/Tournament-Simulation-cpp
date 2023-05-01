#pragma once

#include <string>
#include "Record.h"

class Team
{
public:
	Team();
	Team(const std::string& name, double rating, double avgGoals);
	std::string name;
	Record record;
};

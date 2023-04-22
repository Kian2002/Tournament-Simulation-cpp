#pragma once
#include <vector>
#include <iostream>

#include "Team.h"

class Group
{
public:
	Group();
	std::vector<Team> teams;
	void playGroupMatch(std::vector<Team> teams);
};

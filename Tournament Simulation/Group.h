#pragma once
#include <vector>
#include <iostream>

#include "Team.h"

class Group
{
public:
	Group();
	Group(const std::vector<Team>& teams);
	std::vector<Team> teams;
	void playGroupMatch();
};

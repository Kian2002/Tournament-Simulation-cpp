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
	std::vector<Team> playGroupMatch();
	Team playKnockoutMatch();
	int simulateGoals(double avgGoals);
	void checkForTies();
	void simulateMatch();
	void penaltyShootout();
	int name;
};

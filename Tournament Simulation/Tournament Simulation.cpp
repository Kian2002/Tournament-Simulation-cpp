// Tournament Simulation.cpp : This file contains the 'main' function.

#include <iostream>

#include "Group.h"
#include "TeamData.h"

int main()
{
	std::sort(teams.begin(), teams.end(),
	          [](const Team& a, const Team& b) { return a.record.rating > b.record.rating; });

	Group group(teams);
	group.playGroupMatch();
}

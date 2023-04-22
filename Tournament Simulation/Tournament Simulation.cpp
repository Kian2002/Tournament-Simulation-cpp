// Tournament Simulation.cpp : This file contains the 'main' function.

#include <iostream>

#include "Group.h"

int main()
{
	const std::vector<Team> teams = {
		Team("Brazil", 1834.21), Team("Germany", 1647.42), Team("Italy", 1713.66), Team("Argentina", 1838.38)
	};
	Group group(teams);
	group.playGroupMatch();
}

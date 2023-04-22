// Tournament Simulation.cpp : This file contains the 'main' function.

#include <iostream>

#include "Group.h"

int main()
{
	Group group;
	const Team team1("Brazil", 50);
	const Team team2("Argentina", 100);
	const Team team3("Germany", 100);
	const Team team4("France", 1000);

	group.teams.push_back(team1);
	group.teams.push_back(team2);
	group.teams.push_back(team3);
	group.teams.push_back(team4);

	group.playGroupMatch(group.teams);
}

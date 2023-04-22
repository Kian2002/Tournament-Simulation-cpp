// Tournament Simulation.cpp : This file contains the 'main' function.

#include "Group.h"
#include "TeamData.h"

int main()
{
	std::vector<Team> seededTeams;

	for (int i = 0; i < 8; i++)
	{
		seededTeams.push_back(teams[i]);
	}

	teams.erase(teams.begin(), teams.begin() + 8);
	teams.shrink_to_fit();

	std::vector<Group> groups;
	int groupIndex = 0;

	for (int i = 0; i < 8; i++)
	{
		Group group;
		group.teams.push_back(seededTeams[groupIndex]);
		groups.push_back(group);
		groupIndex++;
	}

	constexpr int maxRandomOffset = 10;
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> dist(-maxRandomOffset, maxRandomOffset);
	std::shuffle(teams.begin(), teams.end(), rng);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			groups[i].teams.push_back(teams[i * 3 + j]);
		}
	}


	for (int i = 0; i < 8; i++)
	{
		groups[i].playGroupMatch();
	}
}

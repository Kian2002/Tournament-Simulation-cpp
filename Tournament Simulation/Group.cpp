#include "Group.h"
#include "Team.h"

#include <vector>
#include <iostream>
#include <random>

Group::Group() = default;

Group::Group(const std::vector<Team>& teams)
{
	this->teams = teams;
}

void Group::playGroupMatch()
{
	for (int i = 0; i < static_cast<int>(teams.size()); i++)
	{
		for (int j = i + 1; j < static_cast<int>(teams.size()); j++)
		{
			std::cout << teams[i].name << " vs " << teams[j].name << std::endl;

			constexpr int maxRandomOffset = 10;
			std::random_device rd;
			std::mt19937 rng(rd());
			std::uniform_int_distribution<int> dist(-maxRandomOffset, maxRandomOffset);

			const int matchResult = teams[i].rating - teams[j].rating + dist(rng);

			if (matchResult > 0)
			{
				std::cout << "Match result: " << teams[i].name << " wins" << std::endl;
				// TODO: Add 3 points to teams[i]
			}
			else if (matchResult < 0)
			{
				std::cout << "Match result: " << teams[j].name << " wins" << std::endl;
				// TODO: Add 3 points to teams[j]
			}
			else
			{
				std::cout << "Match result: Draw" << std::endl;
				// TODO: Add 1 point to teams[i] and teams[j]
			}
		}
	}
}

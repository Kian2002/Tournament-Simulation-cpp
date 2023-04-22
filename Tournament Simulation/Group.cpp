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

			constexpr int maxRandomOffset = 500;
			std::random_device rd;
			std::mt19937 rng(rd());
			std::uniform_int_distribution<int> dist(-maxRandomOffset, maxRandomOffset);

			const double matchResult = teams[i].record.rating - teams[j].record.rating + dist(rng);

			if (matchResult > 0)
			{
				std::cout << "Match result: " << teams[i].name << " wins" << std::endl;
				teams[i].record.wins++;
				teams[i].record.points += 3;
				teams[j].record.losses++;
			}
			else if (matchResult < 0)
			{
				std::cout << "Match result: " << teams[j].name << " wins" << std::endl;
				teams[j].record.wins++;
				teams[j].record.points += 3;
				teams[i].record.losses++;
			}
			else
			{
				std::cout << "Match result: Draw" << std::endl;
				teams[i].record.draws++;
				teams[i].record.points++;
				teams[j].record.draws++;
				teams[j].record.points++;
			}
		}
	}

	std::sort(teams.begin(), teams.end(),
	          [](const Team& a, const Team& b) { return a.record.points > b.record.points; });

	for (int i = 0; i < 2; i++)
	{
		std::cout << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;
		std::cout << "------------------Advancement------------------: " << teams[i].name << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;
		std::cout << std::endl;
	}
}

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

int Group::simulateGoals(const double avgGoals)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::poisson_distribution<int> dist(avgGoals);
	return dist(rng);
};

std::vector<Team> Group::playGroupMatch()
{
	std::cout << "-----------------------------------------------" << std::endl;
	std::cout << "--------------------Group " << name << "--------------------" << std::endl;
	std::cout << "-----------------------------------------------" << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < static_cast<int>(teams.size()); i++)
	{
		for (int j = i + 1; j < static_cast<int>(teams.size()); j++)
		{
			std::cout << teams[i].name << " vs " << teams[j].name << std::endl;

			constexpr double avgGoals = 2.69; // Average goals per game in the 2022 World Cup

			const int goalsI = simulateGoals(avgGoals);
			const int goalsJ = simulateGoals(avgGoals);

			std::cout << "Goals: " << goalsI << " - " << goalsJ << std::endl;

			// update team records
			teams[i].record.goalsFor += goalsI;
			teams[i].record.goalsAgainst += goalsJ;
			teams[i].record.goalDifference += goalsI - goalsJ;
			teams[j].record.goalsFor += goalsJ;
			teams[j].record.goalsAgainst += goalsI;
			teams[j].record.goalDifference += goalsJ - goalsI;

			const int matchResult = goalsI - goalsJ;

			if (matchResult > 0)
			{
				std::cout << "Match result: " << teams[i].name << " wins" << std::endl;
				std::cout << std::endl;

				// update team records
				teams[i].record.wins++;
				teams[i].record.points += 3;
				teams[j].record.losses++;
			}
			else if (matchResult < 0)
			{
				std::cout << "Match result: " << teams[j].name << " wins" << std::endl;
				std::cout << std::endl;

				// update team records
				teams[j].record.wins++;
				teams[j].record.points += 3;
				teams[i].record.losses++;
			}
			else
			{
				std::cout << "Match result: Draw" << std::endl;
				std::cout << std::endl;

				// update team records
				teams[i].record.draws++;
				teams[i].record.points++;
				teams[j].record.draws++;
				teams[j].record.points++;
			}
		}
	}

	// sort teams by points
	std::sort(teams.begin(), teams.end(),
	          [](const Team& a, const Team& b) { return a.record.points > b.record.points; });

	// tiebreakers
	// 1. goal difference

	for (int i = 0; i < static_cast<int>(teams.size()); i++)
	{
		for (int j = i + 1; j < static_cast<int>(teams.size()); j++)
		{
			// check if teams have the same number of points
			if (teams[i].record.points == teams[j].record.points)
			{
				if (teams[i].record.goalDifference < teams[j].record.goalDifference)
				{
					std::swap(teams[i], teams[j]);
				}
			}
		}
	}

	// TODO: implement other tiebreakers here for a more accurate simulation

	for (int i = 0; i < 2; i++)
	{
		std::cout << "-----------------------------------------------" << std::endl;
		std::cout << "------------------Advancement------------------: " << teams[i].name << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;
		std::cout << std::endl;
	}

	return teams;
}

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

void Group::header()
{
	std::cout << "-----------------------------------------------" << std::endl;
	std::cout << "--------------------Group " << name << "--------------------" << std::endl;
	std::cout << "-----------------------------------------------" << std::endl;
	std::cout << std::endl;
}

int Group::simulateGoals(const double avgGoals)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::poisson_distribution<int> dist(avgGoals);
	return dist(rng);
};

void Group::checkForTies()
{
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
}

void Group::simulateMatch()
{
	for (int i = 0; i < static_cast<int>(teams.size()); i++)
	{
		for (int j = i + 1; j < static_cast<int>(teams.size()); j++)
		{
			std::cout << teams[i].name << " vs " << teams[j].name << std::endl;

			constexpr double avgGoals = 2.69; // Average goals per game in the 2022 World Cup
			// TODO: use the teams actual average goals per game instead of the average goals per game in the 2022 World Cup

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
}

std::vector<Team> Group::playGroupMatch()
{
	header();
	simulateMatch();
	checkForTies();

	for (int i = 0; i < 2; i++)
	{
		std::cout << "-----------------------------------------------" << std::endl;
		std::cout << "------------------Advancement------------------: " << teams[i].name << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;
		std::cout << std::endl;
	}

	return teams;
}

void Group::penaltyShootout()
{
	std::cout << "-----------------Looks like were going to penalties-----------------" << std::endl;
	int penaltyKicks = 5;

	while (penaltyKicks > 0)
	{
		// 0.75 is the average chance of scoring a penalty kick
		constexpr double avgPenaltyKick = 0.75;

		const int penaltyKickI = simulateGoals(avgPenaltyKick);
		const int penaltyKickJ = simulateGoals(avgPenaltyKick);

		// update team records
		teams[0].record.goalsFor += penaltyKickI;
		teams[0].record.goalsAgainst += penaltyKickJ;
		teams[0].record.goalDifference += penaltyKickI - penaltyKickJ;
		teams[0].record.points += penaltyKickI;

		teams[1].record.goalsFor += penaltyKickJ;
		teams[1].record.goalsAgainst += penaltyKickI;
		teams[1].record.goalDifference += penaltyKickJ - penaltyKickI;
		teams[1].record.points += penaltyKickJ;

		// continue penalty kicks if teams are still tied
		if (penaltyKicks == 1 && teams[0].record.points == teams[1].record.points)
		{
			penaltyKicks++;
		}

		penaltyKicks--;
	}

	std::cout << "The final score is " << teams[0].name << " " << teams[0].record.points << " - " << teams[1].record.
		points << " " << teams[1].name << std::endl;
}

Team Group::playKnockoutMatch(const std::string& title)
{
	// reset team points from group stage
	teams[0].record.points = 0;
	teams[1].record.points = 0;

	header();
	simulateMatch();

	// tiebreaker
	if (teams[0].record.points == teams[1].record.points)
	{
		penaltyShootout();
	}

	// put winner at index 0
	for (int i = 0; i < static_cast<int>(teams.size()); i++)
	{
		for (int j = i + 1; j < static_cast<int>(teams.size()); j++)
		{
			if (teams[i].record.points < teams[j].record.points)
			{
				std::swap(teams[i], teams[j]);
			}
		}
	}

	std::cout << "-----------------------------------------------" << std::endl;
	std::cout << teams[0].name << title << std::endl;
	std::cout << "-----------------------------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	return teams[0];
}

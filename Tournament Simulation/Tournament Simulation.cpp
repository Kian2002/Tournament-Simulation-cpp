// Tournament Simulation.cpp : This file contains the 'main' function.

#include "Group.h"
#include "TeamData.h"

void welcome();

int main()
{
	welcome();

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
		group.name = i + 1;
		group.teams.push_back(seededTeams[groupIndex]);
		groups.push_back(group);
		groupIndex++;
	}

	// shuffle the teams so that the groups are more random
	constexpr int maxRandomOffset = 10;
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> dist(-maxRandomOffset, maxRandomOffset);
	std::shuffle(teams.begin(), teams.end(), rng);

	// add the remaining teams to the groups
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			groups[i].teams.push_back(teams[i * 3 + j]);
		}
	}

	std::vector<Team> teamsThatAdvanceGroupStage;

	for (int i = 0; i < 8; i++)
	{
		const std::vector<Team> teams = groups[i].playGroupMatch();
		teamsThatAdvanceGroupStage.push_back(teams[0]);
		teamsThatAdvanceGroupStage.push_back(teams[1]);
	}

	std::vector<Group> knockoutGroups;

	for (int i = 0; i < 8; i++)
	{
		Group group;
		group.name = i + 1;
		knockoutGroups.push_back(group);
	}

	// add the teams that advance to the knockout stage to the knockout groups
	// the teams are added in the following order by index:
	// (0,3) (4,7) (8,11) (12,15) (1,2) (5,6) (9,10) (13,14)
	int team_index = 0;
	for (int i = 0; i < 4; i++)
	{
		knockoutGroups[i].teams.push_back(teamsThatAdvanceGroupStage[team_index]);
		knockoutGroups[i].teams.push_back(teamsThatAdvanceGroupStage[team_index + 3]);
		knockoutGroups[i + 4].teams.push_back(teamsThatAdvanceGroupStage[team_index + 1]);
		knockoutGroups[i + 4].teams.push_back(teamsThatAdvanceGroupStage[team_index + 2]);
		team_index += 4;
	}

	// print the groups TODO: DELETE ME
	for (Group group : knockoutGroups)
	{
		std::cout << "Group " << group.name << std::endl;
		std::cout << "Team 1: " << group.teams[0].name << std::endl;
		std::cout << "Team 2: " << group.teams[1].name << std::endl;
	}
}

void welcome()
{
	std::cout << R"(
____    __    ____  _______  __        ______   ______   .___  ___.  _______  
\   \  /  \  /   / |   ____||  |      /      | /  __  \  |   \/   | |   ____|  
 \   \/    \/   /  |  |__   |  |     |  ,----'|  |  |  | |  \  /  | |  |__
  \            /   |   __|  |  |     |  |     |  |  |  | |  |\/|  | |   __|
   \    /\    /    |  |____ |  `----.|  `----.|  `--'  | |  |  |  | |  |____ 
    \__/  \__/     |_______||_______| \______| \______/  |__|  |__| |_______| 
                                                                                                        
)";
	std::cout << std::endl;
	std::cout << "                to the tournament simulator!" << std::endl;
	std::cout << "                This program will simulate a FIFA World Cup tournament" << std::endl;
	std::cout << "                Starting off with the group stage: " << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}

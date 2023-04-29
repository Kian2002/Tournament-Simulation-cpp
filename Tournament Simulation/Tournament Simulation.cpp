// Tournament Simulation.cpp : This file contains the 'main' function.

#include "Group.h"
#include "TeamData.h"

void welcome();
void roundOf16();

int main()
{
	welcome();

	// seed the top 8 teams into seperate groups
	std::vector<Team> seededTeams;
	for (int i = 0; i < 8; i++)
	{
		seededTeams.push_back(teams[i]);
	}

	teams.erase(teams.begin(), teams.begin() + 8);
	teams.shrink_to_fit();

	// create group stage groups
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

	// play the group stage
	// the teams that advance to the knockout stage are stored in a vector
	std::vector<Team> teamsThatAdvanceGroupStage;
	for (int i = 0; i < 8; i++)
	{
		const std::vector<Team> teams = groups[i].playGroupMatch();
		teamsThatAdvanceGroupStage.push_back(teams[0]);
		teamsThatAdvanceGroupStage.push_back(teams[1]);
	}

	// create the knockout groups using the teams that advanced from the group stage
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

	// Commence Round of 16
	roundOf16(); // print the round of 16 title
	std::vector<Team> teamsThatAdvanceRoundOf16;
	for (Group group : knockoutGroups)
	{
		Team team = group.playKnockoutMatch("Quarter Finals");
		teamsThatAdvanceRoundOf16.push_back(team);
	}

	// Quarter Finals Groups
	std::vector<Group> quarterFinalsGroups;
	for (int i = 0; i < static_cast<int>(teamsThatAdvanceRoundOf16.size() / 2); i++)
	{
		Group group;
		group.name = i + 1;
		quarterFinalsGroups.push_back(group);
	}

	// Add the teams that advance to the quarter finals to the quarter finals groups
	for (int i = 0; i < quarterFinalsGroups.size(); i++)
	{
		quarterFinalsGroups[i].teams.push_back(teamsThatAdvanceRoundOf16[i * 2]);
		quarterFinalsGroups[i].teams.push_back(teamsThatAdvanceRoundOf16[i * 2 + 1]);
	}

	//Commence Quarter Finals
	std::vector<Team> teamsThatAdvanceQuarterFinals;
	for (Group group : quarterFinalsGroups)
	{
		Team team = group.playKnockoutMatch("Semi Finals");
		teamsThatAdvanceQuarterFinals.push_back(team);
	}

	// Semi Finals Groups
	std::vector<Group> semiFinalsGroups;
	for (int i = 0; i < 2; i++)
	{
		Group group;
		group.name = i + 1;
		semiFinalsGroups.push_back(group);
	}

	// Add the teams that advance to the semi finals to the semi finals groups
	for (int i = 0; i < teamsThatAdvanceQuarterFinals.size() / 2; i++)
	{
		semiFinalsGroups[i].teams.push_back(teamsThatAdvanceQuarterFinals[i * 2]);
		semiFinalsGroups[i].teams.push_back(teamsThatAdvanceQuarterFinals[i * 2 + 1]);
	}

	// Commence Semi Finals
	std::vector<Team> teamsThatAdvanceSemiFinals;
	for (int i = 0; i < 2; i++)
	{
		Team team = semiFinalsGroups[i].playKnockoutMatch("Final");
		teamsThatAdvanceSemiFinals.push_back(team);
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

void roundOf16()
{
	std::cout << R"(
.______        ______    __    __  .__   __.  _______       ______    _______     __     __   
|   _  \      /  __  \  |  |  |  | |  \ |  | |       \     /  __  \  |   ____|   /_ |   / /   
|  |_)  |    |  |  |  | |  |  |  | |   \|  | |  .--.  |   |  |  |  | |  |__       | |  / /_   
|      /     |  |  |  | |  |  |  | |  . `  | |  |  |  |   |  |  |  | |   __|      | | | '_ \  
|  |\  \----.|  `--'  | |  `--'  | |  |\   | |  '--'  |   |  `--'  | |  |         | | | (_) | 
| _| `._____| \______/   \______/  |__| \__| |_______/     \______/  |__|         |_|  \___/  
                                                                                              
)";
}

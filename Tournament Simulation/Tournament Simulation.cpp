// Tournament Simulation.cpp : This file contains the 'main' function.

#include "Group.h"
#include "TeamData.h"

void welcome();
void roundOf16();
std::vector<Group> createGroup(int size);
void addTeams(const std::vector<Group>& group, const std::vector<Team>& teamsToAdd);


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
	for (int i = 0; i < static_cast<int>(groups.size()); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			groups[i].teams.push_back(teams[i * 3 + j]);
		}
	}

	// play the group stage
	// the teams that advance to the knockout stage are stored in a vector
	std::vector<Team> teamsThatAdvanceGroupStage;
	for (int i = 0; i < static_cast<int>(groups.size()); i++)
	{
		const std::vector<Team> returnedTeams = groups[i].playGroupMatch();
		teamsThatAdvanceGroupStage.push_back(returnedTeams[0]);
		teamsThatAdvanceGroupStage.push_back(returnedTeams[1]);
	}

	// create the knockout groups using the teams that advanced from the group stage
	std::vector<Group> knockoutGroups = createGroup(static_cast<int>(teamsThatAdvanceGroupStage.size() / 2));

	// add the teams that advance to the knockout stage to the knockout groups
	// the teams are added in the following order by index:
	// (0,3) (4,7) (8,11) (12,15) (1,2) (5,6) (9,10) (13,14)
	int team_index = 0;
	for (int i = 0; i < static_cast<int>(knockoutGroups.size()) / 2; i++)
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
	std::vector<Group> quarterFinalsGroups = createGroup(static_cast<int>(teamsThatAdvanceRoundOf16.size() / 2));
	addTeams(quarterFinalsGroups, teamsThatAdvanceRoundOf16);

	//Commence Quarter Finals
	std::vector<Team> teamsThatAdvanceQuarterFinals;
	for (Group group : quarterFinalsGroups)
	{
		Team team = group.playKnockoutMatch("Semi Finals");
		teamsThatAdvanceQuarterFinals.push_back(team);
	}

	// Semi Finals Groups
	std::vector<Group> semiFinalsGroups = createGroup(static_cast<int>(teamsThatAdvanceQuarterFinals.size() / 2));
	addTeams(semiFinalsGroups, teamsThatAdvanceQuarterFinals);

	// Commence Semi Finals
	std::vector<Team> teamsThatAdvanceSemiFinals;
	for (int i = 0; i < 2; i++)
	{
		Team team = semiFinalsGroups[i].playKnockoutMatch("Final");
		teamsThatAdvanceSemiFinals.push_back(team);
	}

	// Third Place Match
	Group thirdPlaceGroup;
	for (int i = 0; i < static_cast<int>(teamsThatAdvanceQuarterFinals.size()); i++)
	{
		if (teamsThatAdvanceQuarterFinals[i].name != teamsThatAdvanceSemiFinals[0].name && teamsThatAdvanceQuarterFinals
			[i].name != teamsThatAdvanceSemiFinals[1].name)
		{
			thirdPlaceGroup.teams.push_back(teamsThatAdvanceQuarterFinals[i]);
		}
	}

	thirdPlaceGroup.playThirdplaceMatch();
}

std::vector<Group> createGroup(int size)
{
	std::vector<Group> groups;

	for (int i = 0; i < size; i++)
	{
		Group group;
		group.name = i + 1;
		groups.push_back(group);
	}

	return groups;
}

void addTeams(const std::vector<Group>& group, const std::vector<Team>& teamsToAdd)
{
	for (int i = 0; i < static_cast<int>(group.size()); i++)
	{
		group[i].teams.push_back(teamsToAdd[i * 2]);
		group[i].teams.push_back(teamsToAdd[i * 2 + 1]);
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

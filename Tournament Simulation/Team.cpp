#include "Team.h"

Team::Team(const std::string& name, const double rating, const double avgGoals)
{
	this->name = name;
	this->record.rating = rating;
	this->record.avgGoals = avgGoals;
}

Team::Team() = default;

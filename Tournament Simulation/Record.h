#pragma once

struct Record
{
	int wins = 0;
	int draws = 0;
	int losses = 0;
	int goalsFor = 0;
	int goalsAgainst = 0;
	int goalDifference = goalsFor - goalsAgainst;
	int points = 0;
	double rating = 0;
};

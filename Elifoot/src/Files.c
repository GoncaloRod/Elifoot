#include "Files.h"

#include <stdio.h>

Team* ReadTeams(char* fileName, int* teamCount)
{
	FILE* fp;
	Team* teams;
	char teamFileName[32];

	// Open teams file
	if (!(fp = fopen(fileName, FM_READ)))
		return NULL;

	// Read amount of team inside file
	fscanf_s(fp, "%d", teamCount);

	// Allocate memory to house every team
	if (!(teams = (Team*)malloc(*teamCount * sizeof(Team))))
	{
		fclose(fp);
		return NULL;
	}


	// Read individual team
	for (int i = 0; i < *teamCount; i++)
	{
		if (feof(fp))
		{
			fclose(fp);
			return NULL;
		}

		fscanf_s(fp, "%s", teamFileName, 32);

		if (!ReadTeam(teamFileName, teams + i, *teamCount))
		{
			fclose(fp);
			return NULL;
		}
	}

	fclose(fp);

	return teams;
}

int ReadTeam(char* fileName, Team* team, int teamsCount)
{
	FILE* fp;
	Player* player;
	int playersCount;

	if (!(fp = fopen(fileName, FM_READ)))
		return 0;

	// Read team info
	fscanf_s(fp, " %[^\n]%*c", team->name, 64);
	fscanf_s(fp, " %[^\n]%*c", team->stadiumName, 64);
	fscanf_s(fp, " %d %d %f %f", &team->stadiumCapacity, &team->associates, &team->funds, &team->stadiumExpenses);

	// Initialize results table
	if (!(team->results.games = (Game*)malloc((teamsCount - 1) * 2 * sizeof(Game))))
	{
		fclose(fp);
		return 0;
	}
	
	team->results.gamesPlayedCount = 0;
	team->results.wins = team->results.draws = team->results.defeats = 0;
	team->results.goalsScored = team->results.goalsSuffered = 0;

	// Read squad
	fscanf_s(fp, " %[^\n]%*c", team->squad.coach.name, 64);

	// Read number of players
	fscanf_s(fp, " %d", &playersCount);

	team->squad.players = playersCount;
	team->squad.maxPlayers = playersCount + 10;

	// Allocate memory for all the players
	if (!(team->squad.players = (Player*)malloc(team->squad.maxPlayers * sizeof(Player))))
	{
		fclose(fp);
		return 0;
	}

	// Read all the players
	for (int i = 0; i < playersCount; i++)
	{
		if (feof(fp))
		{
			fclose(fp);
			return 0;
		}

		fscanf_s(fp, " %d %[^\n]%*c", &team->squad.players[i].number, team->squad.players[i].name, 64);
		fscanf_s(fp, "%f", &team->squad.players[i].salary);
		fscanf_s(fp, "%d %d %d %d", &team->squad.players[i].contractSignedDate.day, &team->squad.players[i].contractSignedDate.month, &team->squad.players[i].contractSignedDate.year, &team->squad.players[i].contractYears);
		fscanf_s(fp, "%d %d %d %d", &team->squad.players[i].stats.forwardPower, &team->squad.players[i].stats.midfilderPower, &team->squad.players[i].stats.defenderPower, &team->squad.players[i].stats.goalkeeperPower);
		team->squad.players[i].enable = 1;
	}

	fclose(fp);

	return 1;
}

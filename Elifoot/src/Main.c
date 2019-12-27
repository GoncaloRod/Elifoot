#include <stdio.h>
#include <stdlib.h>

#include "Structs.h"
#include "Files.h"

#include "ChooseTeam.h"

int main(int argc, char** argv)
{
	Team* teams;
	Team* playerTeam;
	int teamsCount;

	teams = ReadTeams("teams.elf", &teamsCount);

	// Choose team
	playerTeam = ChooseTeam(teams, teamsCount);

	// Draw game calendar

	// Transfermarket

	// Game loop
	for (int i = 0; i < (teamsCount - 1) * 2; i++)
	{
		// If i % 4 == 0 pay the bills
	}

	// Free dynamically allocated memory
	for (int i = 0; i < teamsCount; i++)
	{
		free(teams[i].squad.players);
	}

	free(teams);

	return 0;
}
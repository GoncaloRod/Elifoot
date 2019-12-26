#include <stdio.h>
#include <stdlib.h>

#include "Structs.h"
#include "Files.h"

int main(int argc, char** argv)
{
	Team* teams;
	int teamsCount;

	teams = ReadTeams("teams.elf", &teamsCount);

	// Choose team

	// Draw games

	// Game loop
	for (int i = 0; i < (teamsCount - 1) * 2; i++)
	{

	}

	// Free dynamically allocated memory
	for (int i = 0; i < teamsCount; i++)
	{
		free(teams[i].squad.players);
	}

	free(teams);

	return 0;
}
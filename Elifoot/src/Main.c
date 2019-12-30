#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Structs.h"
#include "Files.h"

#include "ChooseTeam.h"

int main(int argc, char** argv)
{
	Team* teams;
	Team* playerTeam;
	int teamsCount;

	srand(time(NULL));

	teams = ReadTeams("teams.elf", &teamsCount);

	if (!teams)
		return;

	playerTeam = ChooseTeam(teams, teamsCount);

	// TODO: Shuffle game calendar
	ShuffleCalendar(teams, teamsCount);

	// TODO: Transfermarket

	// TODO: Game loop
	for (int i = 0; i < (teamsCount - 1) * 2; i++)
	{
		// If i % 4 == 0 pay the bills

		printf("%s - %s\n", teams[playerTeam->results.games[i].hostsIndex].name, teams[playerTeam->results.games[i].visitorsIndex].name);
	}

	// Free dynamically allocated memory
	for (int i = 0; i < teamsCount; i++)
	{
		free(teams[i].results.games);
		free(teams[i].squad.players);
	}

	free(teams);

	return 0;
}
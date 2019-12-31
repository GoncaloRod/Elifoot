#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Structs.h"
#include "Utils.h"
#include "Files.h"

#include "ChooseTeam.h"
#include "Calendar.h"
#include "Transfermarket.h"
#include "Games.h"

int main(int argc, char** argv)
{
	Team* teams;
	Team* playerTeam;
	Game* nextGame;
	int teamsCount;

	srand(time(NULL));

	teams = ReadTeams("teams.elf", &teamsCount);

	if (!teams)
		return;

	playerTeam = ChooseTeam(teams, teamsCount);

	ShuffleCalendar(teams, teamsCount);
	PrintGameCalendar(teams, playerTeam, teamsCount);

	HandleTransfermarket(teams, teamsCount, playerTeam);

	nextGame = playerTeam->results.games;

	// TODO: Game loop
	for (int weekend = 0; weekend < (teamsCount - 1) * 2; weekend++, nextGame++)
	{
		ClrScr();

		if (weekend % 4 == 0)
		{
			// A month has passed
			// TODO: Pay the bills
		}

		printf("Next game: %s vs %s", teams[nextGame->hostsIndex].name, teams[nextGame->visitorsIndex].name);

		PlayGame(teams, nextGame, playerTeam);

		for (int teamIndex = 0; teamIndex < teamsCount; teamIndex++)
		{
			if (teams[teamIndex].results.gamesPlayedCount < weekend + 1)
			{
				SimulateGame(teams, teams[teamIndex].results.games + weekend);
			}
		}

		// TODO: Print results
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
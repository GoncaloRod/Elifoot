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
	Game* nextGame, *tmpGame;
	int teamsCount;
	float expenses;

	srand(time(NULL));

	teams = ReadTeams("teams.elf", &teamsCount);

	if (!teams)
		return;

	playerTeam = ChooseTeam(teams, teamsCount);

	ShuffleCalendar(teams, teamsCount);
	PrintGameCalendar(teams, playerTeam, teamsCount);

	HandleTransfermarket(teams, teamsCount, playerTeam);

	nextGame = playerTeam->results.games;

	for (int weekend = 0; weekend < (teamsCount - 1) * 2; weekend++, nextGame++)
	{
		ClrScr();

		if ((weekend + 1) % 4 == 0 && playerTeam->funds > 0.0f)
		{
			// A month has passed, pay the bills
			expenses = 0;

			expenses += playerTeam->stadiumExpenses;

			for (int i = 0; i < playerTeam->squad.playersCount; i++)
			{
				expenses += playerTeam->squad.players[i].salary;
			}

			playerTeam->funds -= expenses;

			if (playerTeam->funds <= 0)
			{
				printf("You went bankrupted! You will now lose every game until the end of the season!\n");

				printf("\n");
				WaitForKey();
			}
		}

		// Only play game if team is not bankrupted
		if (playerTeam->funds > 0)
		{
			printf("Next game: %s vs %s\n\n", teams[nextGame->hostsIndex].name, teams[nextGame->visitorsIndex].name);

			WaitForKey();

			PlayGame(teams, nextGame, playerTeam);
		}
		else
		{
			nextGame->hostsGoals = teams + nextGame->hostsIndex == playerTeam ? 0 : 1;
			nextGame->visitorsGoals = teams + nextGame->hostsIndex == playerTeam ? 1 : 0;
		}
		
		// Simulate other teams games
		ClrScr();

		printf("Other teams results:\n\n");

		for (int teamIndex = 0; teamIndex < teamsCount; teamIndex++)
		{
			if (teams[teamIndex].results.gamesPlayedCount < weekend + 1)
			{
				tmpGame = teams[teamIndex].results.games + weekend;

				//SimulateGame(teams, tmpGame);

				printf("%s %d - %d %s\n", teams[tmpGame->hostsIndex].name, tmpGame->hostsGoals, tmpGame->visitorsGoals, teams[tmpGame->visitorsIndex].name);
			}
		}

		printf("\n");
		WaitForKey();
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
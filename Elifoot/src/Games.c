#include "Games.h"
#include <stdio.h>
#include <stdlib.h>
#include "Simulation.h"
#include "Utils.h"

void PlayGame(Team* teams, Game* game, Team* playerTeam)
{
	int pChoice;
	int inUse;

	printf("Choose a tactic:\n");
	printf("[1] 5-3-2\n");
	printf("[2] 4-5-1\n");
	printf("[3] 4-4-2\n");
	printf("[4] 4-3-3\n");
	printf("\n");

	scanf_s("%d", &pChoice);


	switch (pChoice)
	{
	case 1:
		playerTeam->squad.tactic.forwardsCount = 2;
		playerTeam->squad.tactic.midfildersCount = 3;
		playerTeam->squad.tactic.defendersCount = 5;
		break;

	case 2:
		playerTeam->squad.tactic.forwardsCount = 1;
		playerTeam->squad.tactic.midfildersCount = 5;
		playerTeam->squad.tactic.defendersCount = 4;
		break;

	case 3:
		playerTeam->squad.tactic.forwardsCount = 2;
		playerTeam->squad.tactic.midfildersCount = 4;
		playerTeam->squad.tactic.defendersCount = 4;
		break;

	case 4:
		playerTeam->squad.tactic.forwardsCount = 3;
		playerTeam->squad.tactic.midfildersCount = 3;
		playerTeam->squad.tactic.defendersCount = 4;
		break;

	}

	playerTeam->squad.tactic.forwardsIndex = (int*)malloc(playerTeam->squad.tactic.forwardsCount * sizeof(int));
	playerTeam->squad.tactic.midfildersIndex = (int*)malloc(playerTeam->squad.tactic.midfildersCount * sizeof(int));
	playerTeam->squad.tactic.defendersIndex = (int*)malloc(playerTeam->squad.tactic.defendersCount * sizeof(int));

	for (int i = 0; i < playerTeam->squad.tactic.forwardsCount; i++)
	{
		ClrScr();
		printf("Choose a forward:\n\n");
		for (int j = 0; j < playerTeam->squad.playersCount; j++)
		{
			inUse = 0;

		}
	}



	SimulateFirstHalf(teams + game->hostsIndex, teams + game->visitorsIndex, game);

	// TODO: Change tactics and players


	SimulateSecondHalf(teams + game->hostsIndex, teams + game->visitorsIndex, game);

	free(playerTeam->squad.tactic.forwardsIndex);
	free(playerTeam->squad.tactic.midfildersIndex);
	free(playerTeam->squad.tactic.defendersIndex);
}

void SimulateGame(Team* teams, Game* game)
{
	SimulateFirstHalf(teams + game->hostsIndex, teams + game->visitorsIndex, game);

	SimulateSecondHalf(teams + game->hostsIndex, teams + game->visitorsIndex, game);
}

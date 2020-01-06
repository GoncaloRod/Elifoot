#include "Games.h"

#include <stdio.h>
#include <stdlib.h>

#include "Simulation.h"
#include "Utils.h"

void PlayGame(Team* teams, Game* game, Team* playerTeam)
{
	char userChoice = 0;

	ChangeTactic(playerTeam);

	if (teams + game->hostsIndex == playerTeam)
		PickRandomTactic(teams + game->visitorsIndex);
	else
		PickRandomTactic(teams + game->hostsIndex);

	SimulateFirstHalf(teams + game->hostsIndex, teams + game->visitorsIndex, game);

	ClrScr();

	printf("Half time!\n");
	printf("Current score: %d - %d\n\n", game->hostsGoals, game->visitorsGoals);

	do
	{
		printf("Do you want to change tactics? (y/n): ");
		scanf_s(" %c", &userChoice, 1);

		if (userChoice != 'y' && userChoice != 'Y' && userChoice != 'n' && userChoice != 'N')
			printf("Invalid option, please try again!\n\n");

	} while (userChoice != 'y' && userChoice != 'Y' && userChoice != 'n' && userChoice != 'N');

	if (userChoice == 'y' || userChoice == 'Y')
		ChangeTactic(playerTeam);
	

	SimulateSecondHalf(teams + game->hostsIndex, teams + game->visitorsIndex, game);

	printf("It's the end of the game!\n");
	printf("Final score: %d - %d\n\n", game->hostsGoals, game->visitorsGoals);

	// Update results table
	teams[game->hostsIndex].results.gamesPlayedCount++;
	teams[game->visitorsIndex].results.gamesPlayedCount++;

	if (game->hostsGoals > game->visitorsGoals)
	{
		teams[game->hostsIndex].results.wins++;
		teams[game->visitorsGoals].results.defeats++;
	}
	else if (game->hostsGoals < game->visitorsGoals)
	{
		teams[game->hostsIndex].results.defeats++;
		teams[game->visitorsGoals].results.wins++;
	}
	else
	{
		teams[game->hostsIndex].results.draws++;
		teams[game->visitorsGoals].results.draws++;
	}

	WaitForKey();
}

void SimulateGame(Team* teams, Game* game)
{
	PickRandomTactic(teams + game->hostsIndex);
	PickRandomTactic(teams + game->visitorsIndex);

	SimulateFirstHalf(teams + game->hostsIndex, teams + game->visitorsIndex, game);

	SimulateSecondHalf(teams + game->hostsIndex, teams + game->visitorsIndex, game);

	// Update results table
	(teams + game->hostsIndex)->results.gamesPlayedCount++;
	(teams + game->visitorsIndex)->results.gamesPlayedCount++;

	if (game->hostsGoals > game->visitorsGoals)
	{
		teams[game->hostsIndex].results.wins++;
		teams[game->visitorsGoals].results.defeats++;
	}
	else if (game->hostsGoals < game->visitorsGoals)
	{
		teams[game->hostsIndex].results.defeats++;
		teams[game->visitorsGoals].results.wins++;
	}
	else
	{
		teams[game->hostsIndex].results.draws++;
		teams[game->visitorsGoals].results.draws++;
	}
}

void ChangeTactic(Team* playerTeam)
{
	Player* playerTmp;
	int forwardsCount = 0, midfieldersCount = 0, defendersCount = 0;
	int userPick;
	int inUse;

	ClrScr();

	printf("[1] 5-3-2\n");
	printf("[2] 4-5-1\n");
	printf("[3] 4-4-2\n");
	printf("[4] 4-3-3\n\n");

	do
	{
		printf("Choose a tactic: ");
		scanf_s("%d", &userPick);

		if (userPick <= 0 || userPick > 4)
			printf("Invalid tactic, please try again!\n\n");

	} while (userPick <= 0 || userPick > 4);

	switch (userPick)
	{
		case 1:
			forwardsCount = 2;
			midfieldersCount = 3;
			defendersCount = 5;
			break;

		case 2:
			forwardsCount = 1;
			midfieldersCount = 5;
			defendersCount = 4;
			break;

		case 3:
			forwardsCount = 2;
			midfieldersCount = 4;
			defendersCount = 4;
			break;

		case 4:
			forwardsCount = 3;
			midfieldersCount = 3;
			defendersCount = 4;
			break;
	}

	playerTeam->squad.tactic.forwardsCount = forwardsCount;
	playerTeam->squad.tactic.midfieldersCount = midfieldersCount;
	playerTeam->squad.tactic.defendersCount = defendersCount;

	// Reset tactic
	for (int i = 0; i < 11; i++)
	{
		playerTeam->squad.tactic.players[i] = -1;
	}

	for (int i = 0; i < 11; i++)
	{
		ClrScr();

		// Print all available players
		for (int j = 0; j < playerTeam->squad.playersCount; j++)
		{
			inUse = 0;
			playerTmp = playerTeam->squad.players + j;

			// Check if player is already in use
			for (int k = 0; k < 11 && !inUse; k++)
				if (playerTeam->squad.tactic.players[k] == j)
					inUse = 1;

			if (!inUse)
				printf("[%d] %s | %d %d %d %d\n", j + 1, playerTmp->name, playerTmp->stats.forwardPower, playerTmp->stats.midfilderPower, playerTmp->stats.defenderPower, playerTmp->stats.goalkeeperPower);
		}

		printf("\n");

		do
		{
			if (i < forwardsCount)
				printf("Choose a forward: ");
			else if (i < midfieldersCount + forwardsCount)
				printf("Choose a midfielder: ");
			else if (i < defendersCount + midfieldersCount + forwardsCount)
				printf("Choose a defender: ");
			else
				printf("Choose a goalkeeper: ");

			scanf_s("%d", &userPick);

			// Check if player is already in use
			inUse = 0;

			for (int j = 0; j < 11 && !inUse; j++)
				if (playerTeam->squad.tactic.players[j] == userPick - 1)
					inUse = 1;

			if (userPick <= 0 || userPick > playerTeam->squad.playersCount || inUse)
			{
				printf("Invalid player, please try again!\n\n");
			}

		} while (userPick <= 0 || userPick > playerTeam->squad.playersCount || inUse);

		playerTeam->squad.tactic.players[i] = userPick - 1;
	}
}

void PickRandomTactic(Team* team)
{
	int tactic = RandomInRange(1, 4);
	int forwardsCount = 0, midfieldersCount = 0, defendersCount = 0;
	int inUse, position;

	switch (tactic)
	{
		case 1:
			forwardsCount = 2;
			midfieldersCount = 3;
			defendersCount = 5;
			break;

		case 2:
			forwardsCount = 1;
			midfieldersCount = 5;
			defendersCount = 4;
			break;

		case 3:
			forwardsCount = 2;
			midfieldersCount = 4;
			defendersCount = 4;
			break;

		case 4:
			forwardsCount = 3;
			midfieldersCount = 3;
			defendersCount = 4;
			break;
	}

	team->squad.tactic.forwardsCount = forwardsCount;
	team->squad.tactic.midfieldersCount = midfieldersCount;
	team->squad.tactic.defendersCount = defendersCount;

	for (int i = 0, position = 0; i < team->squad.playersCount && position < 11; i++)
	{
		if (position < forwardsCount)
		{
			if (team->squad.players[i].stats.forwardPower > 0)
			{
				team->squad.tactic.players[position] = i;
				position++;
			}
		}
		else if (position < midfieldersCount + forwardsCount)
		{
			if (team->squad.players[i].stats.midfilderPower > 0)
			{
				team->squad.tactic.players[position] = i;
				position++;
			}
		}
		else if (position < defendersCount + midfieldersCount + forwardsCount)
		{
			if (team->squad.players[i].stats.defenderPower > 0)
			{
				team->squad.tactic.players[position] = i;
				position++;
			}
		}
		else
		{
			if (team->squad.players[i].stats.goalkeeperPower > 0)
			{
				team->squad.tactic.players[position] = i;
				position++;
			}
		}
	}
}

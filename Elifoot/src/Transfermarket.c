#include "Transfermarket.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Utils.h"

void HandleTransfermarket(Team* teams, int teamsCount, Team* playerTeam)
{
	Player player;

	// Variable that calculates the value of the transfer & variable that counts the amount of funds required to transfer the player 
	float transferValue, fundsRequired;

	// Variables that receive the users picked team & picked player & count the amount of transfers done by the user
	int userTeamPick, userPlayerPick, transferCount;
	transferCount = 0;

	ClrScr();

	printf("Funds: %.2f\n\n", playerTeam->funds);

	// The user picks a team to transfer a player from (easier to print info on console when reduced from 20000 choices to 20.)
	printf("Pick from which team you want to transfer the player from:\n");

	// Cycle that goes through all the teams 
	for (int i = 0; i < teamsCount; i++)
	{
		//prints the name of the teams on position i aka from 0 all the way to the number of teams
		printf("[%d] %s\n", i + 1, teams[i].name);

	}

	scanf_s("%d", &userTeamPick);

	if (teams + userTeamPick - 1 == playerTeam)
	{
		ClrScr();
		printf("You can't transfer from your own team!");
		return;
	}
	else
	{
		ClrScr();
		// The user picks a player in order for the transfer value to be calculated
		printf("Pick the player you want to transfer to your team:\n");

		// Cycle that prints the players names filtering through the teams pick
		for (int i = 0; i < teams[userTeamPick - 1].squad.playersCount; i++)
		{
			printf("[%d] %s\n", i + 1, teams[userTeamPick - 1].squad.players[i].name);
		}

		scanf_s("%d", &userPlayerPick);

		ClrScr();

		transferValue = teams[userTeamPick - 1].squad.players[userPlayerPick - 1].salary * 5.0f * teams[userTeamPick - 1].squad.players[userPlayerPick - 1].contractYears;

		// The amount of funds required is the amount of funds the team has minus the value of the transfer
		fundsRequired = teams->funds - transferValue;

		if (playerTeam->funds < transferValue)
		{
			printf("Insufficient funds! You need more %f to buy this player.\n", playerTeam->funds);
		}
		else
		{
			if (transferCount <= 3 && teams->squad.playersCount < teams->squad.maxPlayers)
			{
				// Adding the new player to the team - inserts the player picked by the user on the users squad
				memcpy(playerTeam->squad.players + playerTeam->squad.playersCount, teams[userTeamPick - 1].squad.players + userPlayerPick - 1, sizeof(Player));

				// Disable old player
				teams[userTeamPick - 1].squad.players[userPlayerPick - 1].enable = 0;

				// Setting the new salary for the player
				playerTeam->squad.players[playerTeam->squad.playersCount].salary = teams[userTeamPick - 1].squad.players[userPlayerPick - 1].salary * 1.50f;

				// Keeps track of how many transfers the user has done and adds to the transfer count one transfer every time this conditions passes 
				transferCount++;
				playerTeam->squad.playersCount++;

				printf("Your transfer was accepted! %s\n", teams[userTeamPick - 1].squad.players[userPlayerPick - 1].name);
			}
			else
			{
				printf("You have reached the limit of transfers.\n");
				return;
			}
		}

		WaitForKey();
	}
}

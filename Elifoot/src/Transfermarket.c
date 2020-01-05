#include "Transfermarket.h"
#include <stdio.h>
#include <string.h>
#include "Utils.h"

void HandleTransfermarket(Team* teams, int teamsCount, Team* playerTeam)
{
	printf("Funds: %f", playerTeam->funds);
	Player player;

	//variable that calculates the value of the transfer & variable that counts the amount of funds required to transfer the player 
	float transferValue, fundsRequired;

	//variables that receive the users picked team & picked player & count the amout of transfers done by the user
	int userTeamPick, userPlayerPick, transferCount;
	char userPick;
	transferCount = 0;

	printf("Do you want to transfer a player to your team? (y/n)");
	scanf_s("%c", &userPick);

	if (userPick == 'y') 
	{
		HandleTransfermarket(teams, teamsCount, playerTeam);
	}
	else 
	{
		return;
	}

	ClrScr();
	//the user picks a team to transfer a player from (easier to print info on console when reduced from 20000 choices to 20.)
	printf("Pick from which team you want to transfer the player from:\n");

	//cycle that goes through all the teams 
	for (int i = 0; i < teamsCount; i++)
	{
		if (strcmp(teams[i].name, playerTeam) == 0) 
		{
			printf("You can't transfer from your own team!");
		}
		else 
		{
			//prints the name of the teams on position i aka from 0 all the way to the number of teams
			printf("[%d] %s\n", i + 1, teams[i].name);
		}
	}

	scanf_s("%d", &userTeamPick);
	ClrScr();

	//the user picks a player in order for the transfer value to be calculated
	printf("Pick the player you want to transfer to your team:\n");

	//cycle that prints the players names filtering through the teams pick
	for (int k = 0; k < teams[userTeamPick - 1].squad.playersCount; k++)
	{
		printf("[%d] %s\n", k+1, teams[userTeamPick - 1].squad.players[k].name);
	}

	scanf_s("%d", &userPlayerPick);

	transferValue = teams[userTeamPick - 1].squad.players[userPlayerPick - 1].salary * 5.0f * teams[userTeamPick - 1].squad.players[userPlayerPick - 1].contractYears;

	//the amount of funds required is the amount of funds the team has minus the value of the transfer
	fundsRequired = teams->funds - transferValue;

	if (teams->funds < transferValue)
	{
		printf("Insuficient funds");
		printf("Current funds: %f", fundsRequired);
	}
	else
	{
		if (transferCount <= 3 && teams->squad.playersCount <= teams->squad.maxPlayers)
		{
			for (int j = 0; j < teamsCount; j++)
			{
				if (strcmp(teams[userTeamPick - 1].squad.players[userPlayerPick - 1].name, teams[userTeamPick - 1].squad.players[j].name) == 0)
				{
					//adding the new player to the team
					playerTeam->squad.playersCount = playerTeam->squad.playersCount + teams[userTeamPick - 1].squad.players[userPlayerPick - 1].name;

					//setting the new salary for the player
					teams[userTeamPick - 1].squad.players[userPlayerPick - 1].salary = teams[userTeamPick - 1].squad.players[userPlayerPick - 1].salary * 1.50F;
					
					//keeps track of how many transfers the user has done and adds to the transfer count one transfer everytime this conditions passes 
					transferCount++;
					teamsCount++;

					printf("Jogador adicionado com sucesso: %s", teams[userTeamPick - 1].squad.players[userPlayerPick - 1].name);
				}
			}
		}
		else
		{
			printf("You have reached the limit of transfers.");
			return;
		}
		return teams[userTeamPick - 1].squad.players[userPlayerPick - 1].name;
	}
	WaitForKey();
}

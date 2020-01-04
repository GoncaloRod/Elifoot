#include "Transfermarket.h"

void HandleTransfermarket(Team* teams, int teamsCount, Team* playerTeam)
{
	Player player;

	//variable that calculates the value of the transfer & variable that counts the amount of funds required to transfer the player 
	float transferValue, fundsRequired;

	//variables that receive the users picked team & picked player & count the amout of transfers done by the user
	int userTeamPick, userPlayerPick, transferCount;

	//the user picks a team to transfer a player from (easier to print info on console when reduced from 20000 choices to 20.)
	printf("Pick from which team you want to transfer the player from:");

	//cycle that goes through all the teams 
	for (int i = 0; i < teamsCount; i++)
	{
		//prints the name of the teams on position i aka from 0 all the way to the number of teams
		printf("[i] %s", teams->name[i]);
	}

	scanf_s("%d", &userTeamPick);

	//the user picks a player in order for the transfer value to be calculated
	printf("Pick the player you want to transfer to your team:");

	//cycle that prints the players names filtering through the teams pick
	for (int k = 0; k < teams[userTeamPick-1].squad.playersCount; k++)
 	{
		printf("[k] %s", player.name[k]);
	}

	scanf_s("%d", &userPlayerPick);
	
	transferValue = teams[userTeamPick - 1].squad.players[userPlayerPick - 1].salary * 5.0f * teams[userTeamPick - 1].squad.players[userPlayerPick - 1].contractYears;

	//the amount of funds required is the amount of funds the team has minus the value of the transfer
	fundsRequired = teams->funds - transferValue;

	transferCount = 0;

	if (teams->funds < transferValue)
	{
		printf("Insuficient funds");
		printf("Current funds: %f", fundsRequired);
	}
	else
	{
		if (transferCount <= 3)
		{
			for (int j = 0; j < teamsCount; j++)
			{
				if (userTeamPick == player.name[userTeamPick-1])
				{	
					//adding the new player to the team
					teams[userTeamPick - 1].squad.players = teams[userTeamPick - 1].squad.players + player.name[userPlayerPick - 1];
					//setting the new salary for the player
					teams[userTeamPick - 1].squad.players[userPlayerPick - 1].salary = teams[userTeamPick - 1].squad.players[userPlayerPick - 1].salary * 1.50F;
					transferCount++;
					teamsCount++;
				}
			}
		}
		else
		{
			printf("You have reached the limit of transfers.");
			return;
		}

	}
}

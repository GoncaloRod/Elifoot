#include "ChooseTeam.h"

#include <stdio.h>

Team* ChooseTeam(Team* teams, int teamCount)
{
	int teamIndex;

	for (int i = 0; i < teamCount; i++)
	{
		printf("%-2d - %s\n", i + 1, teams[i].name);
	}

	do 
	{
		printf("\nChoose a team: ");
		scanf_s("%d", &teamIndex);

		if (teamIndex < 0 || teamIndex > teamCount)
			printf("Invalid team, please try again!\n");

	} while (teamIndex < 0 || teamIndex > teamCount);

	return teams + (teamIndex - 1);
}

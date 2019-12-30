#include "ShuffleCalendar.h"

#include "Utils.h"

void ShuffleCalendar(Team* teams, int teamsCount)
{
	Game game;
	int* shuffle = (int*)malloc(teamsCount * sizeof(int));
	int random;
	char unique;

	for (int i = 0; i < teamsCount; i++)
	{
		do 
		{
			random = RandomInRange(0, teamsCount - 1);

			unique = 1;

			for (int j = 0; j < i; j++)
				if (shuffle[j] == random)
					unique = 0;

			if (unique)
				shuffle[i] = random;

		} while (!unique);
	}

	// First half of the season
	for (int weekend = 0; weekend < teamsCount - 1; weekend++)
	{
		for (int team = 0; team < teamsCount; team += 2)
		{
			game.hostsIndex = shuffle[team];
			game.visitorsIndex = shuffle[team + 1];

			teams[shuffle[team]].results.games[weekend] = game;
			teams[shuffle[team + 1]].results.games[weekend] = game;
		}
	}

	// Second half of the season
	for (int weekend = teamsCount - 1; weekend < (teamsCount - 1) * 2; weekend++)
	{
		for (int team = 0; team < teamsCount; team += 2)
		{
			game.hostsIndex = shuffle[team + 1];
			game.visitorsIndex = shuffle[team];

			teams[shuffle[team]].results.games[weekend] = game;
			teams[shuffle[team + 1]].results.games[weekend] = game;
		}
	}

	free(shuffle);
}

#include "Games.h"

#include "Simulation.h"

void PlayGame(Team* teams, Game* game, Team* playerTeam)
{
	// TODO: Choose tactic and players

	SimulateFirstHalf(teams + game->hostsIndex, teams + game->visitorsIndex);

	// TODO: Change tactics and players

	SimulateSecondHalf(teams + game->hostsIndex, teams + game->visitorsIndex);
}

void SimulateGame(Team* teams, Game* game)
{
	SimulateFirstHalf(teams + game->hostsIndex, teams + game->visitorsIndex);

	SimulateSecondHalf(teams + game->hostsIndex, teams + game->visitorsIndex);
}

#include "Games.h"

#include "Simulation.h"

void PlayGame(Team* teams, Game* game, Team* playerTeam)
{
	// TODO: Choose tactic and players

	SimulateFirstHalf(teams + game->hostsIndex, teams + game->visitorsIndex, game);

	// TODO: Change tactics and players

	SimulateSecondHalf(teams + game->hostsIndex, teams + game->visitorsIndex, game);
}

void SimulateGame(Team* teams, Game* game)
{
	SimulateFirstHalf(teams + game->hostsIndex, teams + game->visitorsIndex, game);

	SimulateSecondHalf(teams + game->hostsIndex, teams + game->visitorsIndex, game);
}

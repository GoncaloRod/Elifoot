#ifndef GAMES_H_
#define GAMES_H_

#include "Structs.h"

// Play a game between player's team and other team
void PlayGame(Team* teams, Game* game, Team* playerTeam);

// Simulate game between two teams
void SimulateGame(Team* teams, Game* game);

// Change player's team tactic
void ChangeTactic(Team* playerTeam);

// Pick a random tactic for AI team
void PickRandomTactic(Team* team);

#endif // !GAMES_H_

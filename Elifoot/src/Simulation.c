#include "Simulation.h"

#include <stdio.h>

void SimulateFirstHalf(Team* hosts, Team* visitors, Game* game)
{
	// Set score to 0-0
	game->hostsGoals = game->visitorsGoals = 0;

	SimulateHalf(hosts, visitors, game);
}

void SimulateSecondHalf(Team* hosts, Team* visitors, Game* game)
{
	SimulateHalf(hosts, visitors, game);
}

void SimulateHalf(Team* hosts, Team* visitors, Game* game)
{
	int hostsPower[4] = { 0 }, hostsPerformace[4] = { 0 };
	float hostsStrikePower, hostsDefendPower;
	int visitorsPower[4] = { 0 }, visitorsPerformace[4] = { 0 };
	float visitorsStrikePower, visitorsDefendPower;

	// Calculate hosts power
	for (int i = 0; i < 11; i++)
	{
		if (i < hosts->squad.tactic.forwardsCount)
			hostsPower[0] += hosts->squad.players[hosts->squad.tactic.players[i]].stats.forwardPower;
		else if (i < hosts->squad.tactic.forwardsCount + hosts->squad.tactic.midfieldersCount)
			hostsPower[1] += hosts->squad.players[hosts->squad.tactic.players[i]].stats.midfilderPower;
		else if (i < hosts->squad.tactic.forwardsCount + hosts->squad.tactic.midfieldersCount + hosts->squad.tactic.defendersCount)
			hostsPower[2] += hosts->squad.players[hosts->squad.tactic.players[i]].stats.defenderPower;
		else
			hostsPower[3] += hosts->squad.players[hosts->squad.tactic.players[i]].stats.goalkeeperPower;
	}

	// Calculate visitors power
	for (int i = 0; i < 11; i++)
	{
		if (i < visitors->squad.tactic.forwardsCount)
			hostsPower[0] += visitors->squad.players[visitors->squad.tactic.players[i]].stats.forwardPower;
		else if (i < visitors->squad.tactic.forwardsCount + visitors->squad.tactic.midfieldersCount)
			hostsPower[1] += visitors->squad.players[visitors->squad.tactic.players[i]].stats.midfilderPower;
		else if (i < visitors->squad.tactic.forwardsCount + visitors->squad.tactic.midfieldersCount + visitors->squad.tactic.defendersCount)
			hostsPower[2] += visitors->squad.players[visitors->squad.tactic.players[i]].stats.defenderPower;
		else
			hostsPower[3] += visitors->squad.players[visitors->squad.tactic.players[i]].stats.goalkeeperPower;
	}

	// Calculate performances
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			hostsPerformace[i] += RandomInRange(1, 100);
			visitorsPerformace[i] += RandomInRange(1, 100);
		}

		hostsPerformace[i] /= 5;
		visitorsPerformace[i] /= 5;
	}

	// Calculate strike and defend powers
	hostsStrikePower = hostsPower[0] * (hostsPerformace[0] * 0.01f) + (hostsPower[1] * (hostsPerformace[1] * 0.01f)) * 0.5f;
	hostsDefendPower = hostsPower[3] * (hostsPerformace[3] * 0.01f) + (hostsPower[2] * (hostsPerformace[2] * 0.01f)) * 0.5f;

	visitorsStrikePower = visitorsPower[0] * (visitorsPerformace[0] * 0.01f) + (visitorsPower[1] * (visitorsPerformace[1] * 0.01f)) * 0.5f;
	visitorsDefendPower = visitorsPower[3] * (visitorsPerformace[3] * 0.01f) + (visitorsPower[2] * (visitorsPerformace[2] * 0.01f)) * 0.5f;

	// Calculate goals
	game->hostsGoals += hostsStrikePower - visitorsDefendPower * 0.1f;
	game->visitorsGoals += visitorsStrikePower - hostsDefendPower * 0.1f;
}

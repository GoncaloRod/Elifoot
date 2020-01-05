#include "Simulation.h"

#include <stdio.h>

void SimulateFirstHalf(Team* hosts, Team* visitors, Game* game)
{
	int hostsPower[4] = { 0 }, hostsPerformace[4] = { 0 };
	float hostsStrikePower, hostsDefendPower;
	int visitorsPower[4] = { 0 }, visitorsPerformace[4] = { 0 };
	float visitorsStrikePower, visitorsDefendPower;

	// Set score to 0-0
	game->hostsGoals = game->visitorsGoals = 0;

	// Calculate hosts power
	for (int i = 0; i < hosts->squad.tactic.forwardsCount; i++)
		hostsPower[0] += hosts->squad.players[hosts->squad.tactic.forwardsIndex[i]].stats.forwardPower;
	
	for (int i = 0; i < hosts->squad.tactic.midfildersCount; i++)
		hostsPower[1] += hosts->squad.players[hosts->squad.tactic.midfildersIndex[i]].stats.midfilderPower;
	
	for (int i = 0; i < hosts->squad.tactic.defendersCount; i++)
		hostsPower[2] += hosts->squad.players[hosts->squad.tactic.defendersIndex[i]].stats.defenderPower;
	
	hostsPower[3] += hosts->squad.players[hosts->squad.tactic.goalkeeperIndex].stats.goalkeeperPower;

	// Calculate visitors power
	for (int i = 0; i < visitors->squad.tactic.forwardsCount; i++)
		hostsPower[0] += visitors->squad.players[visitors->squad.tactic.forwardsIndex[i]].stats.forwardPower;

	for (int i = 0; i < visitors->squad.tactic.midfildersCount; i++)
		hostsPower[1] += visitors->squad.players[visitors->squad.tactic.midfildersIndex[i]].stats.midfilderPower;

	for (int i = 0; i < visitors->squad.tactic.defendersCount; i++)
		hostsPower[2] += visitors->squad.players[visitors->squad.tactic.defendersIndex[i]].stats.defenderPower;

	hostsPower[3] += visitors->squad.players[visitors->squad.tactic.goalkeeperIndex].stats.goalkeeperPower;

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
	game->hostsGoals += hostsStrikePower / visitorsDefendPower;
	game->visitorsGoals += visitorsStrikePower / hostsDefendPower;
}

void SimulateSecondHalf(Team* hosts, Team* visitors, Game* game)
{

}
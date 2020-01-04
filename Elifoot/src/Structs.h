#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct
{
	int year, month, day;
} Date;

typedef struct
{
	char name[64];
} Coach;

typedef struct 
{
	int forwardPower;
	int midfilderPower;
	int defenderPower;
	int goalkeeperPower;
} PlayerStats;

typedef struct
{
	char name[64];
	int number;
	float salary;
	Date contractSignedDate;
	int contractYears;
	PlayerStats stats;
	char enable;
} Player;

typedef struct
{
	int hostsIndex, visitorsIndex;
	int hostsGoals, visitorsGoals;
} Game;

typedef struct
{
	Game* games;
	int gamesPlayedCount;
	int wins, draws, defeats;
	int goalsScored, goalsSuffered;
} ResultsTable;

typedef struct
{
	int forwardsCount;
	int* forwardsIndex;
	int midfildersCount;
	int* midfildersIndex;
	int defendersCount;
	int* defendersIndex;
	int goalkeeperIndex;
} Tactic;

typedef struct
{
	Coach coach;
	Player* players;
	Tactic tactic;
	int playersCount;
	int maxPlayers;
} Squad;

typedef struct
{
	char name[64];
	char stadiumName[64];
	int stadiumCapacity;
	int associates;
	float funds;
	float stadiumExpenses;
	ResultsTable results;
	Squad squad;
} Team;

#endif // !STRUCTS_H_

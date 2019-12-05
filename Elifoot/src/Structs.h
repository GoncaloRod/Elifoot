#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct
{
	int year, month, day;
} Date;

typedef struct
{
	char name[32];
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
	char name[32];
	int number;
	float salary;
	Date contractSignedDate;
	int contractYears;
	PlayerStats stats;
	int enable;
} Player;

typedef struct
{
	int hostsIndex, visitorsIndex;
	int hostsGoals, visitorsGoals;
} Game;

typedef struct
{
	Game gamesPlayed[17 * 2];
	int gamesPlayed;
	int wins, draws, defeats;
	int goalsScored, goalsSuffered;
} ResultsTable;

typedef struct
{
	Coach coach;
	Player player[25];
} Squad;

typedef struct
{
	char name[32];
	char stadiumName[32];
	int stadiumCapacity;
	int associates;
	float funds;
	float stadiumExpenses;
	ResultsTable results;
	Squad squad;
} Team;

#endif // !STRUCTS_H_

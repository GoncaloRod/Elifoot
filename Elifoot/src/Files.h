#ifndef FILES_H_
#define FILES_H_

#include <stdio.h>

#include "Structs.h"

#define FM_READ			"r"
#define FM_WRITE		"w"
#define FM_APPEND		"a"

#define FM_READ_BIN		"rb"
#define FM_WRITE_BIN	"wb"
#define FM_APPEND_BIN	"ab"

Team* ReadTeams(char* fileName, int* teamCount);

int ReadTeam(char* fileName, Team* team, int teamsCount);

#endif // !FILES_H_

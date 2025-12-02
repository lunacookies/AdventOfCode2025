#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "Utils.h"
#include "Utils.c"

#include "Day 1 Part 1.c"
#include "Day 1 Part 2.c"
#include "Day 2 Part 1.c"

int
main(void)
{
	Arena *arena = ArenaAlloc();
	Day1Part1(arena);
	ArenaClear(arena);
	Day1Part2(arena);
	ArenaClear(arena);
	Day2Part1(arena);
	ArenaRelease(arena);
}

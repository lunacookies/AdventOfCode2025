#include <fcntl.h>
#include <stdalign.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "Utils.h"
#include "Utils.c"

#include "Day 1.c"
#include "Day 2.c"

int
main(void)
{
	Arena *arena = ArenaAlloc();
	Day1(arena);
	ArenaClear(arena);
	Day2(arena);
	ArenaRelease(arena);
}

#!/bin/dash

source_directory="Source"
build_directory="Build"

rm -rf "$build_directory"
mkdir -p "$build_directory"
clang-format -i "$source_directory/"*.c "$source_directory/"*.h
clang \
	-g \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Wconversion \
	-Wimplicit-fallthrough \
	-Wmissing-prototypes \
	-Wshadow \
	-Wstrict-prototypes \
	-fsanitize=undefined \
	-o "$build_directory/aoc" \
	"$source_directory/Entry Point.c"

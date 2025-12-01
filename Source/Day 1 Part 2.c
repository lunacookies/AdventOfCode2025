static void
Day1Part2(Arena *scratch)
{
	String string = ReadFile(scratch, scratch, S("Inputs/Day 1.txt"));
	StringList lines = StringSplit(scratch, string, '\n');
	smm dial = 50;
	umm count = 0;

	for (StringNode *node = lines.first; node; node = node->next)
	{
		String line = node->string;
		if (line.count >= 2)
		{
			String direction = StringPrefix(line, 1);
			String number_string = StringSuffix(line, 1);
			smm move = (smm)U64FromString(number_string);
			if (direction.data[0] == 'L') move = -move;

			umm full_rotations = (umm)Abs(move / 100);
			smm partial_rotation = move % 100;
			count += full_rotations;
			count += dial + partial_rotation < -1 || dial + partial_rotation >= 100;

			dial = Abs((dial + move) % 100);
			Assert(dial >= 0);
			Assert(dial <= 99);
		}
	}

	printf("%zu\n", count);
}

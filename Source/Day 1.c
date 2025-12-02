static void
Day1(Arena *scratch)
{
	String string = ReadFile(scratch, scratch, S("Inputs/Day 1.txt"));
	StringList lines = StringSplit(scratch, string, '\n');
	smm dial = 50;
	umm part_1_count = 0;
	umm part_2_count = 0;

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
			part_2_count += full_rotations;
			part_2_count += dial + partial_rotation < 0 || dial + partial_rotation >= 100;

			dial = (dial + move) % 100;
			if (dial < 0)
			{
				dial = 100 - Abs(dial);
			}
			Assert(dial >= 0);
			Assert(dial <= 99);

			if (!dial) part_1_count++;
		}
	}

	printf("Day 1 Part 1: %zu\n", part_1_count);
	printf("Day 1 Part 2: %zu\n", part_2_count);
}

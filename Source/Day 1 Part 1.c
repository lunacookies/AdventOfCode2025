static void
Day1Part1(Arena *scratch)
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
			umm number = (umm)U64FromString(number_string);
			switch (direction.data[0])
			{
				case 'L': dial += number; break;
				case 'R': dial -= number; break;
			}
		}

		dial %= 100;
		if (!dial) count++;
	}

	printf("%td\n", count);
}

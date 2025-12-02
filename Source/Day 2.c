static umm
DigitCount(umm number)
{
	umm result = 0;
	for (; number; number /= 10)
	{
		result++;
	}
	return result;
}

static bmm
IDIsInvalid(umm id)
{
	bmm result = 0;
	umm digit_count = DigitCount(id);
	if (!(digit_count % 2))
	{
		umm half_digit_mask = 1;
		for (umm i = 0; i < digit_count / 2; i++)
		{
			half_digit_mask *= 10;
		}

		umm digits_hi = id / half_digit_mask;
		umm digits_lo = id % half_digit_mask;
		result = digits_hi == digits_lo;
	}
	return result;
}

static void
Day2(Arena *scratch)
{
	String string = ReadFile(scratch, scratch, S("Inputs/Day 2.txt"));
	StringList ranges = StringSplit(scratch, string, ',');
	umm sum = 0;

	for (StringNode *range_node = ranges.first; range_node; range_node = range_node->next)
	{
		String start_string = {0};
		String end_string = {0};
		StringCut(range_node->string, '-', &start_string, &end_string);
		umm start = (umm)U64FromString(start_string);
		umm end = (umm)U64FromString(end_string);

		for (umm id = start; id <= end; id++)
		{
			if (IDIsInvalid(id))
			{
				sum += id;
			}
		}
	}

	printf("Day 2 Part 1: %zu\n", sum);
}

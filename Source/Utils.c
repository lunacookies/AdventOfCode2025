static smm
Abs(smm x)
{
	smm result = x > 0 ? x : -x;
	return result;
}

static void
MemoryCopy(void *dst, void *src, umm size)
{
	memmove(dst, src, size);
}

static void
MemorySet(void *dst, umm size, u8 byte)
{
	memset(dst, byte, size);
}

static void
MemoryZero(void *dst, umm size)
{
	MemorySet(dst, size, 0);
}

static Arena *
ArenaAlloc(void)
{
	umm mapping_size = 1024 * 1024;
	u8 *p = mmap(0, mapping_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	Assert(p != MAP_FAILED);
	Arena *result = (Arena *)p;
	result->capacity = mapping_size - sizeof(Arena);
	return result;
}

static void
ArenaRelease(Arena *arena)
{
	umm mapping_size = arena->capacity + sizeof(Arena);
	munmap(arena, mapping_size);
}

static void
ArenaClear(Arena *arena)
{
	u8 *buf = (u8 *)arena + sizeof(Arena);
	arena->used = 0;
	MemoryZero(buf, arena->capacity);
}

static void *
PushSize(Arena *arena, umm size)
{
	void *result = 0;
	if (size)
	{
		Assert(arena->used <= arena->capacity);
		umm remaining = arena->capacity - arena->used;
		Assert(size <= remaining);
		u8 *buf = (u8 *)arena + sizeof(Arena);
		result = buf + arena->used;
		arena->used += size;
	}
	return result;
}

static String
StringSlice(String string, umm start, umm end)
{
	Assert(start <= string.count);
	Assert(end <= string.count);
	Assert(start <= end);
	String result = {0};
	result.data = string.data + start;
	result.count = end - start;
	return result;
}

static String
StringPrefix(String string, umm end)
{
	String result = StringSlice(string, 0, end);
	return result;
}

static String
StringSuffix(String string, umm start)
{
	String result = StringSlice(string, start, string.count);
	return result;
}

static String
StringCopy(Arena *arena, String string)
{
	String result = {0};
	result.data = PushArray(arena, u8, string.count);
	result.count = string.count;
	MemoryCopy(result.data, string.data, string.count);
	return result;
}

static umm
StringFind(String haystack, u8 needle)
{
	umm result = haystack.count;
	u8 *p = memchr(haystack.data, needle, haystack.count);
	if (p)
	{
		result = (umm)(p - haystack.data);
	}
	return result;
}

static bmm
StringCut(String haystack, u8 needle, String *before, String *after)
{
	umm index = StringFind(haystack, needle);
	bmm result = index < haystack.count;

	if (result)
	{
		if (before) *before = StringPrefix(haystack, index);
		if (after) *after = StringSuffix(haystack, index + 1);
	}
	else
	{
		if (before) *before = haystack;
		if (after) MemoryZeroStruct(after);
	}

	return result;
}

static StringList
StringSplit(Arena *arena, String string, u8 delimiter)
{
	StringList result = {0};

	for (String remaining = string;;)
	{
		String before = {0};
		bmm more = StringCut(remaining, delimiter, &before, &remaining);

		StringNode *node = PushStruct(arena, StringNode);
		node->string = before;

		if (result.first)
		{
			result.last->next = node;
		}
		else
		{
			result.first = node;
		}
		result.last = node;
		result.count++;

		if (!more) break;
	}

	return result;
}

static char *
CStringFromString(Arena *arena, String string)
{
	char *result = PushArray(arena, char, string.count);
	MemoryCopy(result, string.data, string.count);
	return result;
}

static u64
U64FromString(String string)
{
	u64 result = 0;
	u8 *end = string.data + string.count;
	for (u8 *p = string.data; p != end; p++)
	{
		u8 c = *p;
		if (c >= '0' && c <= '9')
		{
			result *= 10;
			result += c - '0';
		}
		else
		{
			break;
		}
	}
	return result;
}

static String
ReadFile(Arena *arena, Arena *scratch, String path)
{
	char *path_c = CStringFromString(scratch, path);
	int fd = open(path_c, O_RDONLY);
	struct stat buf = {0};
	fstat(fd, &buf);

	String temp = {0};
	temp.count = (umm)buf.st_size;
	temp.data = PushArray(scratch, u8, temp.count);
	String result = {0};
	smm bytes_read = read(fd, temp.data, temp.count);
	if (bytes_read > 0)
	{
		result = StringCopy(arena, StringPrefix(temp, (umm)bytes_read));
	}

	close(fd);
	return result;
}

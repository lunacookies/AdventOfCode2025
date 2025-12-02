typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef size_t umm;
typedef ptrdiff_t smm;
typedef smm bmm;

#define DebugTrap() (__builtin_debugtrap())
#define Assert(condition) \
	if (!(condition)) DebugTrap();

static smm Abs(smm x);
static umm SetBitCount(umm x);
static umm AlignPadPow2(umm base, umm align);

static void MemoryCopy(void *dst, void *src, umm size);
static void MemorySet(void *dst, umm size, u8 byte);
static void MemoryZero(void *dst, umm size);
#define MemoryZeroStruct(dst) (MemoryZero((dst), sizeof(*(dst))))

typedef struct Arena Arena;
struct Arena
{
	umm used;
	umm capacity;
};

static Arena *ArenaAlloc(void);
static void ArenaRelease(Arena *arena);
static void ArenaClear(Arena *arena);
static void *PushSize(Arena *arena, umm size, umm align);
#define PushArray(arena, T, count) ((T *)PushSize((arena), sizeof(T) * (count), alignof(T)))
#define PushStruct(arena, T) (PushArray((arena), T, 1))

typedef struct String String;
struct String
{
	u8 *data;
	umm count;
};

#define S(string) ((String){(u8 *)(string), sizeof(string) - 1})

typedef struct StringNode StringNode;
struct StringNode
{
	StringNode *next;
	String string;
};

typedef struct StringList StringList;
struct StringList
{
	StringNode *first;
	StringNode *last;
	umm count;
};

static String StringSlice(String string, umm start, umm end);
static String StringPrefix(String string, umm end);
static String StringSuffix(String string, umm start);
static String StringCopy(Arena *arena, String string);
static umm StringFind(String haystack, u8 needle);
static bmm StringCut(String haystack, u8 needle, String *before, String *after);
static StringList StringSplit(Arena *arena, String string, u8 delimiter);
static char *CStringFromString(Arena *arena, String string);
static u64 U64FromString(String string);

static String ReadFile(Arena *arena, Arena *scratch, String path);

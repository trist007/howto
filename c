: structs

typedef struct Test
{
	int sick;
	float wow;
} Test;

need to put both Test just to get the alias Test to declare a struct

: zero initialize
// zero initialize the struct
Test test = {0};

: const with strings
char filename[256];

will decay to const char* when passed to a function expecting const char*, the compiler will actually add const so it becomes
const char* const

it will decay to a char* when passed to a regular function

const char* - pointer to a constant char, you can change the pointer but you can't change the data it pointer to
const char* const = contant pointer to a constant char, can't change pointer and can't change whta the ptr points to

: arrays
don't have to put 2 here can leave it blank
    VkDynamicState dynamicStates[2] = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR
    };


: assert vs static assert
assert - runtime
static assert - at compile time	

: dll vs .lib
dll has actual machine code of function implementations, exported symbols, resources like strings, icons, import and export tables and relocation info
shared between multiple programs

lib is either a static lib machine code of function impl like a dll or it's an import library for a dll with no code just symbols and hits telling linker how to find them in dll
basically a stuf or forwarding table

Summary Table

Feature                         .lib (Static)                     .lib (Import)                         .dll

Contains actual code            Yes                               No                                    Yes
Linked at build time            Yes (code copied in)              Yes (references only)                 No (loaded at runtime)
Distributed with app            No                                No (but DLL is needed)                Yes
Final .exe size                 Larger                            Small                                 Small
Can update without rebuild      No                                Yes (if DLL changes)                  Yes
Multiple programs share it      No                                Yes (via DLL)                         Yes
Used with                       #pragma comment(lib, "xx.lib")    Same as static                        Same + DLL present at runtime

: how to tell if .lib is a static lib or an import lib
lib /list YourLibrary.lib

static - shows many .obj files
import - shows no .obj files often shows .dll names or just a smaller number of entries __imp__

lib /list YourLibrary.lib | findstr /i ".obj" >nul && echo Static Library || echo Import Library

or

dumpbin /linkermember YourLibrary.lib

dumpbin /linkermember:2 YourLibrary.lib | more

: checking which libs the exe is dependent on
dumpbin /dependents arwin.exe

dumpbin /imports arwin.exe

: check if the binary has statically linked libs
dumpbin /all arwin.exe | findstr /i volk

: show symbols in .dll
dumpbin /EXPORTS vulkan-1.dll

: std version
__STDC_VERSION__ C17 is 201710L

: _Static_assert use macro static_assert for asserts during compile time
_Static_assert(condition, "Error message");

// Preferred on MSVC (works in both C and C++)
#include <assert.h>
static_assert(condition, "Error message");

: _Alignas use macro aligntas()
#include <stdalign.h>     // Best practice

// Preferred way
alignas(16) int buffer[1024];                    // 16-byte aligned array
alignas(64) struct Vec3 { float x, y, z; } v;    // 64-byte aligned struct

Common Use Cases in Handmade/Low-Level CCache-line alignment (usually 64 bytes)
SIMD vector alignment (16, 32, or 64 bytes)
Ensuring struct members are properly aligned for performance
Page alignment (4096 bytes) for memory-mapped stuff

: snprintf and strlen
this function does add a null byte terminator if the size of bytes to copy is 8 bytes and the string is also 8 bytes
then it will only copy 7 bytes of the string and use the last byte for the null terminator
strlen also gets number of bytes before 00 and like snprintf does not count the null terminator 00

: strncpy if you give it 8 bytes to write and the string is 8 bytes then it will write 8 bytes and not include null terminator, if 
string is 7 bytes then it will use the last byte for null terminator	

: __VA_ARGS__ only allowed in macros that use ...
#define Log(...) SDL_Log(__VA_ARGS__)

: u32 and when to use int or size_t
u64
Default for sizes, counts, indices, offsets, positions, memory amounts
String8.size, arena positions, loop counters, array lengths, file sizes, hashes

u32
When you're sure < 4 GB is enough and you want to save space (rare)
Small buffers, entity counts, bitfields

u8/u16
Bytes, small enums, packed data
Pixel values, flags, network packets

b32
Booleans (your style)
B32 is_valid;

int
Avoid in new code — only for APIs that demand it or small signed values
Return codes from some OS functions, loop variables when negative makes sense

size_t
Only when calling C standard library or platform APIs that expect it
malloc, fread, memset, some sizeof arithmetic

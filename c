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

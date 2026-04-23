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


#include "utils.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_PWD_SIZE 512

typedef enum {
    CMD_CD,
    CMD_EXIT,
    CMD_PWD,
    CMD_EXPORT,
    CMD_UNSET,
    CMD_ECHO,
    CMD_HELP,
    CMD_COUNT
} FUNCTION;

typedef struct {
	const char* name;
	FUNCTION    id;
} BuiltinEntry;

// функция управления встроенными командами
bool handle_builtins(char** args);

// команда cd
void cmd_cd(char* path);

// команда pwd
void cmd_pwd();

// команда export
void cmd_export(char* arg);

// команда unset
void cmd_unset(char* name);

// команда echo
void cmd_echo(char** args);

// команда help
void cmd_help();

#pragma once

#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>

#include "goydash.h"

// парсит строку command и записывает аргументы в args
void parse_args(char* command, ssize_t command_size, char** args);

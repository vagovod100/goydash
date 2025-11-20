#include "parser.h"

void parse_args(char* command, ssize_t command_size, char** args){
    if (command == NULL || args == NULL || command_size <= 0) {
        write(STDERR_FILENO, "parser error: invalid input\n", 29);
        return;
    }

  	// замена переноса строки на нулевой байт
	if(command[command_size - 1] == '\n'){
		command[command_size - 1] = '\0';
	}

	// парсинг введенной строки по пробелам
	uint8_t	arg_index = 0;
	char*	token = strtok(command, " ");
	while(token != NULL && arg_index < MAX_ARGS - 1){
		args[arg_index++] = token;
		token = strtok(NULL, " ");
	}
	args[arg_index] = NULL;
}

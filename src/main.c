#include "parser.h"
#include "executor.h"
#include "builtins.h"

#include <signal.h>

int main(){
	signal(SIGINT, SIG_IGN);	// игнорирование Ctrl + C

	char	command_buffer[MAX_COMMAND_SIZE];	// строка где хранится введенная команда
	char*	args[MAX_ARGS];						// введенные аргументы
	ssize_t command_size;						// длина введенной команды

	while(1){
		if(write(STDOUT_FILENO, "$ ", 2) == -1){
			write(STDERR_FILENO, "stdout error\n", 13);
			exit(EXIT_FAILURE);
		}

		command_size = read(STDIN_FILENO, command_buffer, MAX_COMMAND_SIZE);

		if (command_size == -1) {		// ошибка стандартного ввода
		    print_error("read error");
			continue;
		}
		else if (command_size == 0) {	// Ctrl + D (EOF)
			write(STDOUT_FILENO, "\nexit\n", 6);
			break;
		}
		else if (command_size == 1) {	// пустой ввод
			continue;
		}

		// парсим введенную команду по аргументам
		parse_args(command_buffer, command_size, args);

		// выполняем команду
		if(!handle_builtins(args)){
		    exec_command(args);
		}
	}

	return 0;
}

#include "executor.h"

void exec_command(char** args){
    if (args == NULL || args[0] == NULL) {
		write(STDERR_FILENO, "exec error: empty command\n", 27);
		return;
	}

  	// дочерний процесс для запуска команды
	pid_t pid = fork();

	if (pid == -1) {    // ошибка создания процесса
	    print_error("fork error");
		return;
	}

	if(pid == 0){		// дочерний процесс
		execvp(args[0], args);

		// ошибка выполнения команды
		print_error("execvp error");
		_exit(1);
	}
	else if (pid > 0) {	// родительский процесс
		wait(NULL);		// ожидаем завершения дочернего процесса
	}
}

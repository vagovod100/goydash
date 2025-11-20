#include "builtins.h"

static BuiltinEntry builtins[CMD_COUNT] = {
	{"cd",      CMD_CD},
	{"exit",    CMD_EXIT},
	{"pwd",     CMD_PWD},
	{"export",  CMD_EXPORT},
	{"unset",   CMD_UNSET},
	{"echo",    CMD_ECHO},
	{"help",    CMD_HELP}
};

bool handle_builtins(char** args){
    if (args == NULL || args[0] == NULL) return false;

    for(int i = 0; i < CMD_COUNT; i++){
        if(!strcmp(builtins[i].name, args[0])){ // 0 - строки равны
            switch (builtins[i].id) {
                case CMD_CD:
                    cmd_cd(args[1]);
                    return true;
                case CMD_EXIT:
                    _exit(0);
                    return true;
                case CMD_PWD:
                    cmd_pwd();
                    return true;
                case CMD_EXPORT:
                    cmd_export(args[1]);
                    return true;
                case CMD_UNSET:
                    cmd_unset(args[1]);
                    return true;
                case CMD_ECHO:
                    cmd_echo(args + 1);
                    return true;
                case CMD_HELP:
                    cmd_help();
                    return true;
                default:
                    break;
            }
        }
    }

    return false;
}

void cmd_cd(char* path){
    if(path == NULL){
        path = getenv("HOME");
		if (path == NULL) {
            print_error("cd error");
			return;
		}
    }

    if (chdir(path) != 0) {
        print_error("cd error");
	}
}

void cmd_pwd(){
    char path[MAX_PWD_SIZE];

    if (getcwd(path, MAX_PWD_SIZE) == NULL){
        print_error("pwd error");
        return;
    }

    write(STDOUT_FILENO, path, strlen(path));
    write(STDOUT_FILENO, "\n", 1);
}

void cmd_export(char* arg){
    if (arg == NULL || strchr(arg, '=') == NULL) {
        write(STDERR_FILENO, "export error: invalid input\n", 28);
        return;
    }

    char* key   = strtok(arg, "=");
    char* value = strtok(NULL, "");
    if (key == NULL || value == NULL) {
        write(STDERR_FILENO, "export error: missing key or value\n", 36);
        return;
    }

    if(setenv(key, value, 1) != 0){
        print_error("export error");
    }
}

void cmd_unset(char* name){
    if (name == NULL || strlen(name) == 0) {
        write(STDERR_FILENO, "unset error: invalid input\n", 27);
        return;
    }

    if (unsetenv(name) != 0){
        print_error("unset error");
    }
}

void cmd_echo(char** args){
    for (size_t i = 0; args[i] != NULL; i++){
        write(STDOUT_FILENO, args[i], strlen(args[i]));
        if (args[i + 1] != NULL) {
            write(STDOUT_FILENO, " ", 1);
        }
    }

    write(STDOUT_FILENO, "\n", 1);
}

void cmd_help(){
    int fd = open("help.txt", O_RDONLY);
    if (fd == -1) {
        print_error("help open error");
        return;
    }

    char buffer[256];
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    if (bytes_read == -1) {
        print_error("help read error");
    }

    close(fd);
}

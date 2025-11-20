#include "utils.h"

void print_error(const char* prefix) {
	if (prefix != NULL) {
		write(STDERR_FILENO, prefix, strlen(prefix));
		write(STDERR_FILENO, ": ", 2);
	}
	const char* msg = strerror(errno);
	write(STDERR_FILENO, msg, strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}

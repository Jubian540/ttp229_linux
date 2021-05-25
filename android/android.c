#include <stdlib.h>
#include <unistd.h>
#include "android.h"
#include <errno.h>
#include <sys/wait.h>

int android_cmd(char *cmd)
{
	pid_t pid;
	int status;

	if (cmd == NULL)
		return 1;

	if ((pid = fork()) < 0) status = -1;
	else if (pid == 0) {
		execl("/system/bin/sh", "sh", "-c", cmd, (char *)0);
		exit(127);
	} else {
		while (waitpid(pid, &status, 0) < 0) {
			if (errno != EINTR) {
				status = -1;
			}
		}
	}

	return status;
}

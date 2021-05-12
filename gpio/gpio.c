#include "gpio.h"
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>

int malloc_gpio(struct gpio* pgpio, int port, char *direction)
{
	char buf[128];	
	sprintf(buf, "/sys/class/gpio/gpio%d/value", port);

	strcpy(pgpio->direction, "err");
	pgpio->port = port;

	if (set_direction(pgpio, direction)) return -1;

	printf("open: %s\n", buf);
	if (!strcmp(direction, DIRECTION_OUT))
		pgpio->fd = open(buf, O_WRONLY);
	if (!strcmp(direction, DIRECTION_IN))
		pgpio->fd = open(buf, O_RDONLY);

	if (pgpio->fd == -1) perror("open failed!\n");
	return 0;
}

int set_direction(struct gpio* pgpio, char *direction)
{
	char buf[128];
	sprintf(buf, "/sys/class/gpio/gpio%d", pgpio->port);
	if (access(buf, R_OK|W_OK)) {
		sprintf(buf, "echo %d > /sys/class/gpio/export", pgpio->port);
		system(buf);
		sprintf(buf, "/sys/class/gpio/gpio%d", pgpio->port);
		if (access(buf, R_OK|W_OK)) {
			perror("set direction error: ");
			return -1;
		}	
	}

	if (!((!strcmp(direction, DIRECTION_IN)) || (!strcmp(direction, DIRECTION_OUT)))) {
		printf("direction is not in or out!\n");
		return -1;
	}

	sprintf(buf, "echo %s > /sys/class/gpio/gpio%d/direction", direction, pgpio->port);
	printf("%s\n", buf);
	system(buf);
	strcpy(pgpio->direction, direction);
	return 0;
}

int g_read(struct gpio* pgpio, int *res)
{
	char buf[3] = {0};
	int nread;

	lseek(pgpio->fd, 0, SEEK_SET);
	nread = read(pgpio->fd, buf, 1);
	
	if (nread == -1) {
		perror("GPIO Read failed!\n");
		return -1;
	}

	*res = atoi(buf);

	return 0;
}

int g_write(struct gpio* pgpio, int *state)
{
	int s = (*state == 0) ? 0:1;
	char buf[2];

	sprintf(buf,"%d", s);
	if (write(pgpio->fd, buf, 1) == -1) {
		perror("write gpio failed!\n");
		return -1;
	}
	return 0;
}

void g_close(struct gpio* pgpio)
{
	close(pgpio->fd);
	free(pgpio);
}

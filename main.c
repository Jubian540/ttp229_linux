#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include "gpio/gpio.h"

int main(int argc, char *argv[])
{
	struct gpio *scl, *sdo;
	int state, data;
	if (argc != 3) {
		printf("use: keyboard {pin_scl} {pin_sdo}!\n");
		return -1;
	}

	if ((scl = malloc(sizeof(struct gpio))) == NULL) {
		printf("out of memory!\n");
		return -1;
	}

	if ((sdo = malloc(sizeof(struct gpio))) == NULL) {
		printf("out of memory!\n");
		return -1;
	}

	if (malloc_gpio(scl, atoi(argv[1]), DIRECTION_OUT)) {
		printf("gpio init failed!\n");
		return -1;
	}

	if (malloc_gpio(sdo, atoi(argv[2]), DIRECTION_IN)) {
		printf("gpio init failed!\n");
		return -1;
	}
	
	printf("gpio init successed!\n");


	while (1) {
		state = 0;
		g_write(scl, &state);
		usleep(50);
		state = 1;
		g_write(scl, &state);
		usleep(50);
		g_read(sdo, &data);
		printf("data=%d\n", data);
	}

	g_close(scl);
	g_close(sdo);

	return 0;
}

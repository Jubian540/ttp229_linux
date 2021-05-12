#include <unistd.h>
#include "ttp229.h"
#include <string.h>
#include <fcntl.h>
#include "gpio/gpio.h"

int init_ttp229(struct ttp229* pttp229)
{
	struct gpio *scl, *sdo;
	if ((scl = malloc(sizeof(struct gpio))) == NULL) {
		printf("out of memory!\n");
		return -1;
	}

	if ((sdo = malloc(sizeof(struct gpio))) == NULL) {
		printf("out of memory!\n");
		return -1;
	}

	if (malloc_gpio(scl, pttp229->pin_scl, DIRECTION_OUT)) {
		printf("gpio init failed!\n");
		return -1;
	}

	if (malloc_gpio(sdo, pttp229->pin_sdo, DIRECTION_IN)) {
		printf("gpio init failed!\n");
		return -1;
	}

	pttp229->gp_scl = scl;
	pttp229->gp_sdo = sdo;

	return 0;
}

int ttp229_read(struct ttp229* pttp229, struct ttp229_state *pstate)
{
	int state = 0, data;
	pstate->is_press = 0;
	pstate->key = 0;
	g_write(pttp229->gp_scl, &state);

	for (int i = 0; i < 16; i++) {
		state = 0;
		g_write(pttp229->gp_scl, &state);
		usleep(50);
		state = 1;
		g_write(pttp229->gp_scl, &state);
		g_read(pttp229->gp_sdo, &data);
		if (data == 1) {
			pstate->is_press = 1;
			pstate->key++;
		}
		usleep(50);
	}
	return 0;
}

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include "gpio/gpio.h"
#include "ttp229.h"

int main(int argc, char *argv[])
{
	struct ttp229* pttp229;
	struct ttp229_state state;
	if (argc != 3) {
		printf("use: keyboard {pin_scl} {pin_sdo}!\n");
		return -1;
	}

	if ((pttp229 = malloc(sizeof(struct ttp229))) == NULL) {
		printf("out of memory!\n");
		return -1;
	}

	pttp229->pin_scl = atoi(argv[1]);
	pttp229->pin_sdo = atoi(argv[2]);

	if (init_ttp229(pttp229)) {
		printf("ttp229 init failed!\n");
		return -1;
	}

	while (1) {
		ttp229_read(pttp229, &state);
		if (state.is_press) {
			printf("on press, key=%d\n", state.key);
		}
	}

	return 0;
}

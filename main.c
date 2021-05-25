#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "gpio/gpio.h"
#include "ttp229/ttp229.h"
#include "android/android.h"

int main(int argc, char *argv[])
{
	int sum;
	int count;
	int prev_key;
	struct ttp229* pttp229;
	struct ttp229_state state;
	
	if ((pttp229 = (struct ttp229 *)malloc(sizeof(struct ttp229))) == NULL) {
		printf("out of memory!\n");
		return -1;
	}

	pttp229->pin_scl = 65;
	pttp229->pin_sdo = 64;

	if (init_ttp229(pttp229)) {
		printf("ttp229 init failed!\n");
		return -1;
	}

	while (1) {
		ttp229_read(pttp229, &state);
		if (state.is_press) {
			sum = 0;
			count = 0;
			prev_key = state.key;
			do {
				if (prev_key != state.key) {
					sum = prev_key - state.key;
					count++;
				}
				prev_key = state.key;
				ttp229_read(pttp229, &state);
			} while (state.is_press);
			if (count > 2 && sum > 0) {
				printf("up\n");
				ANDROID_CMD(ANDROID_VOLUME_UP);
			} else if (count > 2 && sum < 0) {
				printf("down\n");
				ANDROID_CMD(ANDROID_VOLUME_DOWN);
			} else {
				printf("press\n");
				ANDROID_CMD(ANDROID_POWER);
			}
		}
	}

	return 0;
}

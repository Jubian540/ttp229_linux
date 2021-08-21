#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "gpio.h"

#ifndef TTP229
#define TTP229
#define TTP229_KEY_ERROR -1

struct ttp229_state {
	int is_press;
	int key;
};

struct ttp229 {
	int pin_scl;
	int pin_sdo;
	struct gpio *gp_scl;
	struct gpio *gp_sdo;
};

int init_ttp229(struct ttp229* pttp229);
int ttp229_read(struct ttp229* pttp229, struct ttp229_state *pstate);

#endif

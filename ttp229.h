#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
	int (*read)(struct ttp229_state *pstate);
};

int init_ttp229(struct ttp229* pttp229);

#endif

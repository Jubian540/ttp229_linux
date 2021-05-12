#include <sys/types.h>
#include <unistd.h>

#ifndef GPIO
#define GPIO
#define DIRECTION_IN "in"
#define DIRECTION_OUT "out"

struct gpio {
	int port;
	int fd;
	char direction[4];
};

#endif

int g_read(struct gpio* pgpio, int *res);
int g_write(struct gpio* pgpio, int *state);
void g_close(struct gpio* pgpio);
int set_direction(struct gpio* pgpio, char *direction);
int malloc_gpio(struct gpio* pgpio, int port, char *direction);

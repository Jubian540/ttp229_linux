#include<stdlib.h>
#include<unistd.h>

#ifndef ANDROID_
#define ANDROID_

int android_cmd(char *);

#define ANDROID_CMD(cmd) android_cmd(cmd)
#define ANDROID_VOLUME_UP "input keyevent 24"
#define ANDROID_VOLUME_DOWN "input keyevent 25"
#define ANDROID_POWER "input keyevent 26"

#endif

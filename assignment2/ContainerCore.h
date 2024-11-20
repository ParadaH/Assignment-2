#ifndef __CONTAINER_CORE__
#define __CONTAINER_CORE__

#include "Arduino.h"

#define EMPTY 0
#define FULL 1
#define OPEN 2
#define CLOSE 3
#define ALARM 4
#define SLEEP 5
#define EMPTYING 6

extern int container_state;
extern int garbage_bin_level;

#endif

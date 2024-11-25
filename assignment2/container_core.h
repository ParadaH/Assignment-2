#ifndef __CONTAINER_CORE__
#define __CONTAINER_CORE__

#include "Arduino.h"

/* Finite states */
#define EMPTY 0 // Idle state of container
#define FULL 1
#define OPEN 2
#define CLOSE 3
#define ALARM 4
#define SLEEP 5
#define EMPTYING 6

#define ALARM_COMMAND 101

extern int container_state;
extern int garbage_bin_level;

#endif

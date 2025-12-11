#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 6

const int LOCK_STARTING_POSITION = 50;
const int LOCK_MIN_VALUE = 0;
const int LOCK_MAX_VALUE = 99;
const int LOCK_LIMITER = 100;

typedef enum LockDirection {
    LEFT,
    RIGHT
} LockDirection;

typedef struct LockRotation {
    LockDirection direction;
    int value;
} LockRotation;

int rotate_lock(int lock_position, LockRotation* rotation);
int rotate_lock_right(int lock_position, int value);
int rotate_lock_left(int lock_position, int value);

FILE* openInputFile(char* file_name);

void process_lock_rotations(FILE* file);
LockRotation* get_lock_rotation(char* line);

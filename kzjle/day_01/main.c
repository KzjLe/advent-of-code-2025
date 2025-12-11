#include "main.h"

int main(int argc, char* argv[]) {
    if (argc == 1 || argc > 2) {
        perror("Invalid argument. Use: main [file_name]");
        return 0;
    }
    char* file_name = argv[1];
    FILE* inputFile = openInputFile(file_name);
    process_lock_rotations(inputFile);
    fclose(inputFile);
    return 0;
}

FILE* openInputFile(char* file_name) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("error while opening %s\n", file_name);
        exit(0);
    }
	return file;
}

void process_lock_rotations(FILE* file) {
    char line[MAX_LINE_LENGTH];
    int lock_current_pos = LOCK_STARTING_POSITION;
    int zero_counter = 0;
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        LockRotation* lock_rotation = get_lock_rotation(line);
        lock_current_pos = rotate_lock(lock_current_pos, lock_rotation);
        if (lock_current_pos == 0) zero_counter++;
        free(lock_rotation);
    }
    printf("The password is: %d\n", zero_counter); 
}

LockRotation* get_lock_rotation(char* line) {
    LockRotation* lock_rotation = malloc(sizeof(LockRotation));
    char direction;
    int value;
    sscanf(line, " %c%d", &direction, &value);
    if (direction == 'L') lock_rotation->direction = LEFT;
    else lock_rotation->direction = RIGHT;
    lock_rotation->value = value;
    return lock_rotation;
}

int rotate_lock(int lock_position, LockRotation* rotation) {
    if (rotation->direction == RIGHT) {
        return rotate_lock_right(lock_position, rotation->value);
    }
    return rotate_lock_left(lock_position, rotation->value);
}

int rotate_lock_right(int lock_position, int value) {
    int target = lock_position + value;
    if (target <= LOCK_MAX_VALUE) {
        return target;
    }
    return (target - LOCK_LIMITER) % LOCK_LIMITER;
}

int rotate_lock_left(int lock_position, int value) {
    int target = lock_position - value;
    if (target >= LOCK_MIN_VALUE) {
        return target;
    }
    return (LOCK_LIMITER + target) % LOCK_LIMITER;
}

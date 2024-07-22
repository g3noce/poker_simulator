#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define RED "\033[7;31m"
#define RESET "\033[0m"

void* safe_malloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        printf("%sMemory allocation failed: %s\n%s", RED, strerror(errno), RESET);
        exit(EXIT_FAILURE);
    }
    return ptr;
}
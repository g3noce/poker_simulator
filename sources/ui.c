#include "ui.h"
#include <stdio.h>

int get_valid_choice(int min, int max) {
    int choice;
    if (min > max)
        return max;

    while (1) {
        printf("Enter your choice (%d-%d): ", min, max);
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Clear input buffer
            printf("Invalid input. Please enter a number.\n");
        } else if (choice < min || choice > max) {
            printf("Invalid choice. Please try again.\n");
        } else {
            break;
        }
    }
    return choice;
}
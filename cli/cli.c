#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"
#include "bubbleSort.h"

static void CLI_ShowMenu(void);
static int CLI_GetUserInput(void);
static void CLI_ExecuteMenuOption(int choice);

/**
 * @brief Displays the command line interface menu
 * 
 */
static void CLI_ShowMenu(void)
{
    int i = 1;
    printf("\n=== CLI Menu ===\n");
    printf("%d. Bubble Sort\n", i++);
    printf("%d. Print hello message\n", i++);
    printf("0. Exit\n");
    printf("Enter menu number: ");
}

/**
 * @brief Gets the menu input from the user
 * 
 * @return int The menu option chosen by the user, or -1 if input is invalid
 */
static int CLI_GetUserInput(void)
{
    char buffer[32];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    char *endptr = NULL;
    long choice = strtol(buffer, &endptr, 10);

    if (endptr == buffer || *endptr != '\n') {
        return -1;
    }

    return (int)choice;
}

/**
 * @brief Executes the selected menu option
 * 
 * @param menuOption The menu option chosen by the user
 */
static void CLI_ExecuteMenuOption(int menuOption)
{
    printf("\n"); // Add a newline for better formatting

    switch (menuOption) 
    {
        case 1:
            BubbleSort();
            break;

        case 2:
            printf("Hello from the CLI!\n");
            break;

        case 0:
            printf("Exiting CLI. Goodbye!\n");
            break;

        default:
            printf("Invalid selection. Please enter a menu number.\n");
            break;
    }
}

void CLI_Run(void)
{
    int menuOption = 0;

    do {
        CLI_ShowMenu();
        menuOption = CLI_GetUserInput();

        if (menuOption < 0) {
            printf("Invalid input. Please enter a number from the menu.\n");
            continue;
        }

        CLI_ExecuteMenuOption(menuOption);
    } while (menuOption != 0);
}

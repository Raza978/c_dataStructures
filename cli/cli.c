#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"
#include "sortingAlgorithms.h"
#include "searchingAlgorithms.h"
#include "linkedList.h"

static void CLI_ShowMenu(void);
static int CLI_GetUserInput(void);
static void CLI_ExecuteMenuOption(int choice);
static void CLI_ShowSortingMenu(void);
static void CLI_RunSortingMenu(void);
static void CLI_ShowSearchingMenu(void);
static void CLI_RunSearchingMenu(void);
static void CLI_ShowLinkedListMenu(void);
static void CLI_RunLinkedListMenu(void);

static void CLI_ShowSortingMenu(void)
{
    int i = 1;
    printf("\n=== Sorting Algorithms ===\n");
    printf("%d. Bubble Sort\n", i++);
    printf("%d. Selection Sort\n", i++);
    printf("%d. Insertion Sort\n", i++);
    printf("%d. Quick Sort\n", i++);
    printf("0. Back\n");
    printf("Enter menu number: ");
}

static void CLI_ShowSearchingMenu(void)
{
    int i = 1;
    printf("\n=== Searching Algorithms ===\n");
    printf("%d. Linear Search\n", i++);
    printf("%d. Binary Search\n", i++);
    printf("0. Back\n");
    printf("Enter menu number: ");
}

static void CLI_ShowLinkedListMenu(void)
{
    int i = 1;
    printf("\n=== Linked List Algorithms ===\n");
    printf("%d. Insert at Head\n", i++);
    printf("%d. Insert at Tail\n", i++);
    printf("%d. Insert at Position\n", i++);
    printf("%d. Delete Head\n", i++);
    printf("%d. Delete Tail\n", i++);
    printf("%d. Delete at Position\n", i++);
    printf("%d. Delete List\n", i++);
    printf("0. Back\n");
    printf("Enter menu number: ");
}

/**
 * @brief Displays the command line interface menu
 * 
 */
static void CLI_ShowMenu(void)
{
    int i = 1;
    printf("\n=== CLI Menu ===\n");
    printf("%d. Sorting Algorithms\n", i++);
    printf("%d. Searching Algorithms\n", i++);
    printf("%d. Linked Lists\n", i++);
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

static void CLI_RunSortingMenu(void)
{
    int menuOption;

    do {
        CLI_ShowSortingMenu();
        menuOption = CLI_GetUserInput();

        printf("\n"); // Add a newline for better formatting

        switch (menuOption) {
            case 1:
                BubbleSort();
                break;

            case 2:
                SelectionSort();
                break;

            case 3:
                InsertionSort();
                break;
            
            case 4:
                QuickSort();
                break;

            case 0:
                printf("\nReturning to main menu.\n");
                break;

            default:
                printf("\nInvalid selection. Please enter a menu number.\n");
                break;
        }
    } while (menuOption != 0);
}

static void CLI_RunSearchingMenu(void)
{
    int menuOption;

    do {
        CLI_ShowSearchingMenu();
        menuOption = CLI_GetUserInput();

        printf("\n"); // Add a newline for better formatting

        switch (menuOption) 
        {
            case 1:
                LinearSearch();
                break;

            case 2:
                BinarySearch();
                break;

            case 0:
                printf("\nReturning to main menu.\n");
                break;

            default:
                printf("\nInvalid selection. Please enter a menu number.\n");
                break;
        }
    } while (menuOption != 0);
}

static void CLI_RunLinkedListMenu(void)
{
    int menuOption;

    do {
        CLI_ShowLinkedListMenu();
        menuOption = CLI_GetUserInput();
        int data = 0;
        int position = 0;

        printf("\n"); // Add a newline for better formatting

        switch (menuOption) 
        {
            case 1:
                printf("Enter data (int) for new node: ");
                data = CLI_GetUserInput();
                LinkedList_InsertAtHead(data);
                break;
            
            case 2:
                printf("Enter data (int) for new node: ");
                data = CLI_GetUserInput();
                LinkedList_InsertAtTail(data);
                break;

            case 3:
                printf("Enter data (int) for new node: ");
                data = CLI_GetUserInput();
                printf("Enter position (int) for new node: ");
                position = CLI_GetUserInput();
                LinkedList_InsertAfterPosition(data, position);
                break;

            case 4:
                LinkedList_DeleteHead();
                break;
            
            case 5:
                LinkedList_DeleteTail();
                break;

            case 6:
                printf("Enter position (int) for node to delete: ");
                position = CLI_GetUserInput();
                LinkedList_DeleteAtPosition(position);
                break;
            
            case 7:
                LinkedList_DeleteList();
                break;

            case 0:
                printf("\nReturning to main menu.\n");
                break;

            default:
                printf("\nInvalid selection. Please enter a menu number.\n");
                break;
        }
    } while (menuOption != 0);
}

/**
 * @brief Executes the selected menu option
 * 
 * @param menuOption The menu option chosen by the user
 */
static void CLI_ExecuteMenuOption(int menuOption)
{
    switch (menuOption) 
    {
        case 1:
            CLI_RunSortingMenu();
            break;

        case 2:
            CLI_RunSearchingMenu();
            break;

        case 3:
            CLI_RunLinkedListMenu();
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

        CLI_ExecuteMenuOption(menuOption);
    } while (menuOption != 0);
}

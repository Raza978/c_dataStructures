#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"
#include "sortingAlgorithms.h"
#include "searchingAlgorithms.h"
#include "linkedList.h"

typedef enum {
    BASE_MENU = 0,
    SORTING_MENU,
    SEARCHING_MENU,
    LINKED_LIST_MENU
} MenuState;

typedef enum {
    // Base Menu Options
    EXIT = 0,
    SORTING,
    SEARCHING,
    LINKED_LIST,

    // Sorting Menu Options
    BUBBLE_SORT = 1,
    SELECTION_SORT,
    INSERTION_SORT,
    QUICK_SORT,

    // Searching Menu Options
    LINEAR_SEARCH = 1,
    BINARY_SEARCH,

    // Linked List Menu Options
    INSERT_AT_HEAD = 1,
    INSERT_AT_TAIL,
    INSERT_AT_POSITION,
    DELETE_HEAD,
    DELETE_TAIL,
    DELETE_AT_POSITION,
    DELETE_LIST
} MenuOption;

typedef void (*MenuAction)(void);

typedef struct {
    MenuState currentState;
    MenuOption menuOption;
    MenuState nextState;
    const char *label;
    MenuAction action;
} MenuTransition;

static int running = 1;

// Function prototypes
static int CLI_GetUserInput(void);
static int CLI_GetUserInputPrompt(const char *prompt);
static const MenuTransition *CLI_FindTransition(MenuState state, MenuOption option);
static void CLI_ShowMenu(MenuState state);
static void CLI_ExecuteTransition(const MenuTransition *transition);
static const char *CLI_GetMenuTitle(MenuState state);

// Action functions for menu options
static void CLI_ActionBubbleSort(void) { BubbleSort(); }
static void CLI_ActionSelectionSort(void) { SelectionSort(); }
static void CLI_ActionInsertionSort(void) { InsertionSort(); }
static void CLI_ActionQuickSort(void) { QuickSort(); }
static void CLI_ActionLinearSearch(void) { LinearSearch(); }
static void CLI_ActionBinarySearch(void) { BinarySearch(); }
static void CLI_ActionInsertAtHead(void) 
{
    int data = CLI_GetUserInputPrompt("Enter data (int) for new node: ");
    LinkedList_InsertAtHead(data);
}
static void CLI_ActionInsertAtTail(void) 
{
    int data = CLI_GetUserInputPrompt("Enter data (int) for new node: ");
    LinkedList_InsertAtTail(data);
}
static void CLI_ActionInsertAtPosition(void) 
{
    int data = CLI_GetUserInputPrompt("Enter data (int) for new node: ");
    int position = CLI_GetUserInputPrompt("Enter position (int) for new node: ");
    LinkedList_InsertAfterPosition(data, position);
}
static void CLI_ActionDeleteHead(void) { LinkedList_DeleteHead(); }
static void CLI_ActionDeleteTail(void) { LinkedList_DeleteTail(); }
static void CLI_ActionDeleteAtPosition(void) 
{
    int position = CLI_GetUserInputPrompt("Enter position (int) for node to delete: ");
    LinkedList_DeleteAtPosition(position);
}
static void CLI_ActionDeleteList(void) { LinkedList_DeleteList(); }

static const MenuTransition stateTransitionTable[] = {
    //currentState,     menuOption,         nextState,        label,                action
    { BASE_MENU,        EXIT,               BASE_MENU,        "Exit",               NULL },
    { BASE_MENU,        SORTING,            SORTING_MENU,     "Sorting Algorithms", NULL },
    { BASE_MENU,        SEARCHING,          SEARCHING_MENU,   "Searching Algorithms", NULL },
    { BASE_MENU,        LINKED_LIST,        LINKED_LIST_MENU, "Linked Lists",       NULL },

    { SORTING_MENU,     BUBBLE_SORT,        SORTING_MENU,     "Bubble Sort",        CLI_ActionBubbleSort },
    { SORTING_MENU,     SELECTION_SORT,     SORTING_MENU,     "Selection Sort",     CLI_ActionSelectionSort },
    { SORTING_MENU,     INSERTION_SORT,     SORTING_MENU,     "Insertion Sort",     CLI_ActionInsertionSort },
    { SORTING_MENU,     QUICK_SORT,         SORTING_MENU,     "Quick Sort",         CLI_ActionQuickSort },
    { SORTING_MENU,     EXIT,               BASE_MENU,        "Back",               NULL },

    { SEARCHING_MENU,   LINEAR_SEARCH,      SEARCHING_MENU,   "Linear Search",      CLI_ActionLinearSearch },
    { SEARCHING_MENU,   BINARY_SEARCH,      SEARCHING_MENU,   "Binary Search",      CLI_ActionBinarySearch },
    { SEARCHING_MENU,   EXIT,               BASE_MENU,        "Back",               NULL },

    { LINKED_LIST_MENU, INSERT_AT_HEAD,      LINKED_LIST_MENU, "Insert at Head",     CLI_ActionInsertAtHead },
    { LINKED_LIST_MENU, INSERT_AT_TAIL,      LINKED_LIST_MENU, "Insert at Tail",     CLI_ActionInsertAtTail },
    { LINKED_LIST_MENU, INSERT_AT_POSITION,  LINKED_LIST_MENU, "Insert at Position", CLI_ActionInsertAtPosition },
    { LINKED_LIST_MENU, DELETE_HEAD,         LINKED_LIST_MENU, "Delete Head",        CLI_ActionDeleteHead },
    { LINKED_LIST_MENU, DELETE_TAIL,         LINKED_LIST_MENU, "Delete Tail",        CLI_ActionDeleteTail },
    { LINKED_LIST_MENU, DELETE_AT_POSITION,  LINKED_LIST_MENU, "Delete at Position", CLI_ActionDeleteAtPosition },
    { LINKED_LIST_MENU, DELETE_LIST,         LINKED_LIST_MENU, "Delete List",        CLI_ActionDeleteList },
    { LINKED_LIST_MENU, EXIT,                BASE_MENU,        "Back",               NULL }
};

/**
 * @brief Gets the title for the given menu state.
 * 
 * @param state The menu state
 * @return const char* The title of the menu
 */
static const char *CLI_GetMenuTitle(MenuState state)
{
    switch (state) 
    {
        case BASE_MENU:
            return "CLI Menu";
        case SORTING_MENU:
            return "Sorting Algorithms";
        case SEARCHING_MENU:
            return "Searching Algorithms";
        case LINKED_LIST_MENU:
            return "Linked List Algorithms";
        default:
            return "Menu";
    }
}

/**
 * @brief Displays the menu options for the given menu state.
 * 
 * @param state The current menu state
 */
static void CLI_ShowMenu(MenuState state)
{
    printf("\n=== %s ===\n", CLI_GetMenuTitle(state));

    for (size_t i = 0; i < sizeof(stateTransitionTable) / sizeof(stateTransitionTable[0]); ++i) 
    {
        if (stateTransitionTable[i].currentState == state) 
        {
            printf("%d. %s\n", stateTransitionTable[i].menuOption, stateTransitionTable[i].label);
        }
    }

    printf("Enter menu number: ");
}

/**
 * @brief Gets user input from the console.
 * 
 * @return int The user's input.
 */
static int CLI_GetUserInput(void)
{
    char buffer[32];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) 
    {
        return -1;
    }

    char *endptr = NULL;
    long choice = strtol(buffer, &endptr, 10);

    if (endptr == buffer || *endptr != '\n') 
    {
        return -1;
    }

    return (int)choice;
}

/**
 * @brief Gets user input with a prompt.
 * 
 * @param prompt The prompt to display.
 * @return int The user's input.
 */
static int CLI_GetUserInputPrompt(const char *prompt)
{
    int value;

    while (1) 
    {
        printf("%s", prompt);
        value = CLI_GetUserInput();
        if (value != -1) 
        {
            return value;
        }
        printf("Invalid input. Please enter a valid integer.\n");
    }
}

/**
 * @brief Finds the menu transition for a given state and option.
 * 
 * @param state Current menu state
 * @param option Selected menu option
 * @return const MenuTransition* Pointer to the found menu transition, or NULL if not found
 */
static const MenuTransition *CLI_FindTransition(MenuState state, MenuOption option)
{
    for (size_t i = 0; i < sizeof(stateTransitionTable) / sizeof(stateTransitionTable[0]); ++i) 
    {
        if (stateTransitionTable[i].currentState == state && stateTransitionTable[i].menuOption == option) 
        {
            return &stateTransitionTable[i];
        }
    }
    return NULL;
}

/**
 * @brief Executes the action associated with the given menu transition and handles state changes.
 * 
 * @param transition Pointer to the MenuTransition to execute
 */
static void CLI_ExecuteTransition(const MenuTransition *transition)
{
    if (transition->action != NULL) 
    {
        transition->action();
    }

    if (transition->currentState == BASE_MENU && transition->menuOption == EXIT) 
    {
        printf("Exiting CLI. Goodbye!\n");
        running = 0;
    }
}

void CLI_Run(void)
{
    MenuState currentState = BASE_MENU;

    while (running) {
        CLI_ShowMenu(currentState);
        int menuOption = CLI_GetUserInput();
        printf("\n");

        if (menuOption == -1) 
        {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        const MenuTransition *transition = CLI_FindTransition(currentState, (MenuOption)menuOption);
        if (transition == NULL) 
        {
            printf("Invalid selection. Please enter a menu number.\n");
            continue;
        }

        CLI_ExecuteTransition(transition);
        currentState = transition->nextState;
    }
}

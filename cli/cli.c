#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"
#include "sortingAlgorithms.h"
#include "searchingAlgorithms.h"
#include "linkedList.h"
#include "doublyLinkedList.h"

typedef enum {
    BASE_MENU = 0,
    SORTING_MENU,
    SEARCHING_MENU,
    LINKED_LIST_MENU,
    DOUBLY_LINKED_LIST_MENU,
} MenuState;

typedef enum {
    // Base Menu Options
    EXIT = 0,
    SORTING,
    SEARCHING,
    LINKED_LIST,
    DOUBLY_LINKED_LIST,

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
    DELETE_LIST,

    // Doubly Linked List Menu Options
    DBL_INSERT_AT_HEAD = 1,
    DBL_INSERT_AT_TAIL,
    DBL_INSERT_AT_POSITION,
    DBL_DELETE_HEAD,
    DBL_DELETE_TAIL,
    DBL_DELETE_AT_POSITION,
    DBL_DELETE_LIST,
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
static int GetUserInput(void);
static int GetUserInputPrompt(const char *prompt);
static const MenuTransition *FindTransition(MenuState state, MenuOption option);
static void ShowMenu(MenuState state);
static void ExecuteTransition(const MenuTransition *transition);
static const char *GetMenuTitle(MenuState state);

// Action functions for menu options
static void ActionBubbleSort(void) { BubbleSort(); }
static void ActionSelectionSort(void) { SelectionSort(); }
static void ActionInsertionSort(void) { InsertionSort(); }
static void ActionQuickSort(void) { QuickSort(); }
static void ActionLinearSearch(void) { LinearSearch(); }
static void ActionBinarySearch(void) { BinarySearch(); }
static void ActionInsertAtHead(void) 
{
    int data = GetUserInputPrompt("Enter data (int) for new node: ");
    LinkedList_InsertAtHead(data);
}
static void ActionInsertAtTail(void) 
{
    int data = GetUserInputPrompt("Enter data (int) for new node: ");
    LinkedList_InsertAtTail(data);
}
static void ActionInsertAtPosition(void) 
{
    int data = GetUserInputPrompt("Enter data (int) for new node: ");
    int position = GetUserInputPrompt("Enter position (int) for new node: ");
    LinkedList_InsertAtPosition(data, position);
}
static void ActionDeleteHead(void) { LinkedList_DeleteHead(); }
static void ActionDeleteTail(void) { LinkedList_DeleteTail(); }
static void ActionDeleteAtPosition(void) 
{
    int position = GetUserInputPrompt("Enter position (int) for node to delete: ");
    LinkedList_DeleteAtPosition(position);
}
static void ActionDeleteList(void) { LinkedList_DeleteList(); }
static void ActionDBLInsertAtHead(void) 
{
    int data = GetUserInputPrompt("Enter data (int) for new node: ");
    DoublyLinkedList_InsertAtHead(data);
}
static void ActionDBLInsertAtTail(void) 
{
    int data = GetUserInputPrompt("Enter data (int) for new node: ");
    DoublyLinkedList_InsertAtTail(data);
}
static void ActionDBLInsertAtPosition(void) 
{
    int data = GetUserInputPrompt("Enter data (int) for new node: ");
    int position = GetUserInputPrompt("Enter position (int) for new node: ");
    DoublyLinkedList_InsertAtPosition(data, position);
}
static void ActionDBLDeleteHead(void) { DoublyLinkedList_DeleteHead(); }
static void ActionDBLDeleteTail(void) { DoublyLinkedList_DeleteTail(); }
static void ActionDBLDeleteAtPosition(void) 
{
    int position = GetUserInputPrompt("Enter position (int) for node to delete: ");
    DoublyLinkedList_DeleteAtPosition(position);
}
static void ActionDBLDeleteList(void) { DoublyLinkedList_DeleteList(); }

static const MenuTransition stateTransitionTable[] = {
    //currentState,     menuOption,         nextState,        label,                action
    // Base Menu Transitions
    { BASE_MENU,        EXIT,               BASE_MENU,        "Exit",               NULL },
    { BASE_MENU,        SORTING,            SORTING_MENU,     "Sorting Algorithms", NULL },
    { BASE_MENU,        SEARCHING,          SEARCHING_MENU,   "Searching Algorithms", NULL },
    { BASE_MENU,        LINKED_LIST,        LINKED_LIST_MENU, "Linked Lists",       NULL },
    { BASE_MENU,        DOUBLY_LINKED_LIST, DOUBLY_LINKED_LIST_MENU, "Doubly Linked Lists", NULL },

    // Sorting Menu Transitions
    { SORTING_MENU,     BUBBLE_SORT,        SORTING_MENU,     "Bubble Sort",        ActionBubbleSort },
    { SORTING_MENU,     SELECTION_SORT,     SORTING_MENU,     "Selection Sort",     ActionSelectionSort },
    { SORTING_MENU,     INSERTION_SORT,     SORTING_MENU,     "Insertion Sort",     ActionInsertionSort },
    { SORTING_MENU,     QUICK_SORT,         SORTING_MENU,     "Quick Sort",         ActionQuickSort },
    { SORTING_MENU,     EXIT,               BASE_MENU,        "Back",               NULL },

    // Searching Menu Transitions
    { SEARCHING_MENU,   LINEAR_SEARCH,      SEARCHING_MENU,   "Linear Search",      ActionLinearSearch },
    { SEARCHING_MENU,   BINARY_SEARCH,      SEARCHING_MENU,   "Binary Search",      ActionBinarySearch },
    { SEARCHING_MENU,   EXIT,               BASE_MENU,        "Back",               NULL },

    // Linked List Menu Transitions
    { LINKED_LIST_MENU, INSERT_AT_HEAD,      LINKED_LIST_MENU, "Insert at Head",     ActionInsertAtHead },
    { LINKED_LIST_MENU, INSERT_AT_TAIL,      LINKED_LIST_MENU, "Insert at Tail",     ActionInsertAtTail },
    { LINKED_LIST_MENU, INSERT_AT_POSITION,  LINKED_LIST_MENU, "Insert at Position", ActionInsertAtPosition },
    { LINKED_LIST_MENU, DELETE_HEAD,         LINKED_LIST_MENU, "Delete Head",        ActionDeleteHead },
    { LINKED_LIST_MENU, DELETE_TAIL,         LINKED_LIST_MENU, "Delete Tail",        ActionDeleteTail },
    { LINKED_LIST_MENU, DELETE_AT_POSITION,  LINKED_LIST_MENU, "Delete at Position", ActionDeleteAtPosition },
    { LINKED_LIST_MENU, DELETE_LIST,         LINKED_LIST_MENU, "Delete List",        ActionDeleteList },
    { LINKED_LIST_MENU, EXIT,                BASE_MENU,        "Back",               NULL },

    // Doubly Linked List Menu Transitions
    //state,                   option,                  nextState,               label,                action
    { DOUBLY_LINKED_LIST_MENU, DBL_INSERT_AT_HEAD,      DOUBLY_LINKED_LIST_MENU, "Insert at Head",     ActionDBLInsertAtHead },
    { DOUBLY_LINKED_LIST_MENU, DBL_INSERT_AT_TAIL,      DOUBLY_LINKED_LIST_MENU, "Insert at Tail",     ActionDBLInsertAtTail },
    { DOUBLY_LINKED_LIST_MENU, DBL_INSERT_AT_POSITION,  DOUBLY_LINKED_LIST_MENU, "Insert at Position", ActionDBLInsertAtPosition },
    { DOUBLY_LINKED_LIST_MENU, DBL_DELETE_HEAD,         DOUBLY_LINKED_LIST_MENU, "Delete Head",        ActionDBLDeleteHead },
    { DOUBLY_LINKED_LIST_MENU, DBL_DELETE_TAIL,         DOUBLY_LINKED_LIST_MENU, "Delete Tail",        ActionDBLDeleteTail },
    { DOUBLY_LINKED_LIST_MENU, DBL_DELETE_AT_POSITION,  DOUBLY_LINKED_LIST_MENU, "Delete at Position", ActionDBLDeleteAtPosition },
    { DOUBLY_LINKED_LIST_MENU, DBL_DELETE_LIST,         DOUBLY_LINKED_LIST_MENU, "Delete List",        ActionDBLDeleteList },
    { DOUBLY_LINKED_LIST_MENU, EXIT,                    BASE_MENU,               "Back",               NULL },
};

/**
 * @brief Gets the title for the given menu state.
 * 
 * @param state The menu state
 * @return const char* The title of the menu
 */
static const char *GetMenuTitle(MenuState state)
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
            return "Linked List";
        case DOUBLY_LINKED_LIST_MENU:
            return "Doubly Linked List";
        default:
            return "Menu";
    }
}

/**
 * @brief Displays the menu options for the given menu state.
 * 
 * @param state The current menu state
 */
static void ShowMenu(MenuState state)
{
    printf("\n=== %s ===\n", GetMenuTitle(state));

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
static int GetUserInput(void)
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
static int GetUserInputPrompt(const char *prompt)
{
    int value;

    while (1) 
    {
        printf("%s", prompt);
        value = GetUserInput();
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
static const MenuTransition *FindTransition(MenuState state, MenuOption option)
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
static void ExecuteTransition(const MenuTransition *transition)
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
        ShowMenu(currentState);
        int menuOption = GetUserInput();
        printf("\n");

        if (menuOption == -1) 
        {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        const MenuTransition *transition = FindTransition(currentState, (MenuOption)menuOption);
        if (transition == NULL) 
        {
            printf("Invalid selection. Please enter a menu number.\n");
            continue;
        }

        ExecuteTransition(transition);
        currentState = transition->nextState;
    }
}

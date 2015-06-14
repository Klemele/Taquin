#include "twod_array.h"

typedef struct state{
        /* Pointer to pointer to array of the taquin */
        int **arr;
        /* Dist from star */
        int g;
        /* Dist to end */
        int h;
        /* Evaluation value */
        int f;
        /* Parent */
        struct state *parent;
} state;

typedef struct states{
        /* Pointer to the dynamically allocated array of struct state */
        state **state_list;
        /* Size of the list */
        int list_size;
} states;

/* Initialize the starting and stoping state of the taquin */
void state_init_state(state *current_state, int rows, int cols);

/* Free memory allocation for the state */
void state_free_state(state *current_state, int rows);

/* Free memory allocation for the list of state */
void state_free_states(states *lstates, int rows);

/* Print all element of the state */
void state_print_state(state *current_state, int rows, int cols);

/* Copy state1 to state2 */
void state_copy_state(state *src_state, state *dest_state, int rows, int cols);

/* Compare two state and return 1 if this is the same array or 0 if not */
int state_compare_state(state *src_state, state *dest_state, int rows, int cols);

/* Compare the current state with the states arrays and return the state already in or NULL if not */
int state_compare_with_states(state *current_state, states *lstates, int rows, int cols);

/* Add state to the list of the states */
void state_add_state(state *current_state, states *lstates);

/* Remove a state to the list of the states */
void state_remove_state(state *current_state, states *lstates, int rows, int cols);



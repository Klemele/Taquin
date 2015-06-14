#include "state.h"
#include <stdio.h>
#include <stdlib.h>

/* Initialize the starting and stoping state of the taquin */
void state_init_state(state *current_state, int rows, int cols) {

    /* Initialize memory for the pointer of pointer */
    current_state->arr = malloc(rows * sizeof(int *));
    if(current_state->arr == NULL) {
        printf("\nout of memory\n");
        return;
    }

    /* Initialize values */
    current_state->f = 0;
    current_state->g = 0;
    current_state->h = 0;

    /* allocate memory for the pointer to pointer to array */
    twod_array_allocate_array(current_state->arr, rows, cols);

    /* Set the pointer to parent to NULL */
    current_state->parent = NULL;
}

/* Free memory allocation for the state */
void state_free_state(state *current_state, int rows) {
    /* Free memory for the array */
    twod_array_free_array(current_state->arr, rows);

    /* Free memory for the struc */
    free(current_state);
}

/* Free memory allocation for the list of state */
void state_free_states(states *lstates, int rows) {
    int i;

    for(i = 0; i < lstates->list_size; i++) {
        state_free_state(lstates->state_list[i], rows);
    }

    /* Free memory for the struc */
    free(lstates);
}

/* Print all element of the state */
void state_print_state(state *current_state, int rows, int cols) {
    twod_array_print_array(current_state->arr, rows, cols);
    printf("\n\tvalue of g : %d", current_state->g);
    printf("\n\tvalue of h : %d", current_state->h);
    printf("\n\tvalue of f : %d", current_state->f);
}

/* Copy state1 to state2 */
void state_copy_state(state *src_state, state *dest_state, int rows, int cols) {
    twod_array_copy_array(src_state->arr, dest_state->arr, rows, cols);
    dest_state->g = src_state->g;
    dest_state->h = src_state->h;
    dest_state->f = src_state->f;
    dest_state->parent = src_state->parent;
}

/* Compare two state and return 1 if this is the same state or 0 if not */
int state_compare_state(state *src_state, state *dest_state, int rows, int cols) {
    if (twod_array_is_same_array(src_state->arr, dest_state->arr, rows, cols) == 1) {
        return 1;
    }

    return 0;
}

/* Compare the current state with the states arrays and return the position of the state already in or -1 if not */
int state_compare_with_states(state *current_state, states *lstates, int rows, int cols) {
    int i;

    /* Compare with the states in the close */
    for(i = 0; i < lstates->list_size; i++) {
        if (state_compare_state(lstates->state_list[i], current_state, rows, cols) == 1) {
            //printf("\nState found at position : %d", i);
            //state_print_state(lstates->state_list[i]);
            return i;
        }
    }
    return -1;
}

/* Add state to the list of the states */
void state_add_state(state *current_state, states *lstates) {
    /* Increment the list size */
    lstates->list_size++;

    /* Realloc the array */
    lstates->state_list = realloc(lstates->state_list, lstates->list_size * sizeof(state**));
    if(lstates->state_list == NULL) {
        printf("\nout of memory\n");
    }

    /* Add the new state to the states */
    lstates->state_list[lstates->list_size - 1] = current_state;
}

/* Remove a state to the list of the states */
void state_remove_state(state *current_state, states *lstates, int rows, int cols) {
    int pos = state_compare_with_states(current_state, lstates, rows, cols);

    /* Set to null there is only one state */
    if(lstates->list_size == 1) {
        lstates->state_list[pos] = NULL;
    }
    else {
        /* Replace the state to remove by the last state in the list */
        lstates->state_list[pos] = lstates->state_list[lstates->list_size - 1];
    }

    /* Decrement size */
    lstates->list_size--;
}


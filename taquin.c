#include "taquin.h"
#include <stdio.h>
#include <stdlib.h>

/* Evaluate parameters h, g and f and the parent state */
void taquin_set_parameters(state *current_state, state *parent, state *stop, int rows, int cols) {
    /* Increment the dist from start */
    current_state->g += 1;

    if( HEURISTIC == 1) {
        /* Calcul the number of wrong places case */
        current_state->h = twod_array_count_differences(current_state->arr, stop->arr, rows, cols);
    }
    else if( HEURISTIC == 2) {
        /* Evaluate the distance of each cases */
        int r1, r2, c1, c2;
        current_state->h = 0;
        for (r1 = 0; r1 < rows; r1++) {
            for (c1 = 0; c1 < cols; c1++) {
                for (r2 = 0; r2 < rows; r2++) {
                    for (c2 = 0; c2 < cols; c2++) {
                        if(current_state->arr[r1][c1] == stop->arr[r2][c2]) {
                            /* Element found, we apply formula */
                            current_state->h +=abs(r1 - r2) + abs(c1 - c2);
                        }
                    }
                }
            }
        }
    }

    current_state->f = current_state->g + current_state->h;

    /* Set parent state */
    current_state->parent = parent;
}

/* Check the state with the list and add it to the corresponding list if necessary */
void taquin_check_states(state *current_state, states *open_states, states *close_states, int rows, int cols) {
    /* Test if the state is already in open_states */
    int pos_state_open = state_compare_with_states(current_state, open_states, rows, cols);

    /* Test if the state is already in close_states */
    int pos_state_close = state_compare_with_states(current_state, close_states, rows, cols);

    /* state not found, add it to the open_state */
    if((pos_state_open == -1) && (pos_state_close == -1)) {
        /* Add state to the open_state*/
        state_add_state(current_state, open_states);
    }
    /* state already in open state */
    else if (pos_state_open != -1) {
        if (open_states->state_list[pos_state_open]->f >= current_state->f) {
            /* Delete state founded in open_state */
            state_remove_state(open_states->state_list[pos_state_open], open_states, rows, cols);

            /* Add state to the open_state*/
            state_add_state(current_state, open_states);
        }
        else {
            /* Free allocation memory */
            state_free_state(current_state, rows);
        }
    }
    /* state already in close state */
    else if (pos_state_close != -1) {
        if (close_states->state_list[pos_state_close]->f >= current_state->f) {
            /* Delete state founded in close_states */
            state_remove_state(close_states->state_list[pos_state_close], close_states, rows, cols);

            /* Add state to the open_state*/
            state_add_state(current_state, open_states);
        }
        else {
            /* Free allocation memory */
            state_free_state(current_state, rows);
        }
    }
}

/* Iterate through list of state to find the lowest one and return it */
state *taquin_lower_state(states *lstates) {
    int pos = 0,i = 0;

    /* Secure condition */
    if (lstates->list_size > 0) {
        /* Iterate through open_states */
        for (i = 0; i < lstates->list_size; i++) {
            /* Test if the state is lowest than the one saved */
            if (lstates->state_list[i]->f < lstates->state_list[pos]->f) {
                /* Save new position */
                pos = i;
            }
        }
    }
    return lstates->state_list[pos];
}

/* Init and set a child state */
void taquin_create_child_state(state *parent_state, int r, int c, char movement_type, states *open_states, states *close_states, state *stop, state *solution, int rows, int cols) {
    /* Create a new state for operation purpose */
    state *new_state;
    /* Allocate memory */
    new_state = malloc(1* sizeof(state));
    if(new_state == NULL) {
        printf("\nout of memory\n");
    }

    /* Init state allocation */
    state_init_state(new_state, rows, cols);

    /* Duplicate current_state state */
    state_copy_state(parent_state, new_state, rows, cols);

    /* Move an element*/
    if(movement_type == 'S') {
        new_state->arr[r+1][c] = parent_state->arr[r][c];
        new_state->arr[r][c] = parent_state->arr[r+1][c];
    }
    else if(movement_type == 'N') {
        new_state->arr[r-1][c] = parent_state->arr[r][c];
        new_state->arr[r][c] = parent_state->arr[r-1][c];
    }
    else if(movement_type == 'W') {
        new_state->arr[r][c-1] = parent_state->arr[r][c];
        new_state->arr[r][c] = parent_state->arr[r][c-1];
    }
    else if(movement_type == 'E') {
        new_state->arr[r][c+1] = parent_state->arr[r][c];
        new_state->arr[r][c] = parent_state->arr[r][c+1];
    }

    /* Set f, g and h and set the parent*/
    taquin_set_parameters(new_state, parent_state, stop, rows, cols);

    /* Check if we find the solution */
    if(new_state->h == 0) {
        state_copy_state(new_state, solution, rows, cols);
        return;
    }

    /* Check and add the state to open or close states if necessary */
    taquin_check_states(new_state, open_states, close_states, rows, cols);
}

/* Find the next possibilities of the taquin set the pointer 'solution' to the solution state if it has been find */
void taquin_next_state(state *current_state, states *open_states, states *close_states, state *stop, state *solution, int rows, int cols) {
    int r, c, state_grid_element;
    r = 0;

    while(r < rows) {
        c = 0;
        while(c < cols) {
            /* find where the blank is */
            state_grid_element = current_state->arr[r][c];
            if(state_grid_element == 0) {
                if(r - 1 >= 0) {
                    taquin_create_child_state(current_state, r, c, 'N', open_states, close_states, stop, solution, rows, cols);
                }
                if(r + 1 < rows) {
                    taquin_create_child_state(current_state, r, c, 'S', open_states, close_states, stop, solution, rows, cols);
                }
                if(c - 1 >= 0) {
                    taquin_create_child_state(current_state, r, c, 'W', open_states, close_states, stop, solution, rows, cols);
                }
                if(c + 1 < cols) {
                    taquin_create_child_state(current_state, r, c, 'E', open_states, close_states, stop, solution, rows, cols);
                }

                /* Avoid to loop unnecessary */
                return;
            }
            c++;
        }
        r++;
    }
}

/* Find the solution of the taquin */
state *taquin_find_solution(states *open_states, states *close_states, state *start, state *stop, int rows, int cols) {
    /* Duplicate the start state */
    state *first_state;
    first_state = malloc(1 * sizeof(state));
    state_init_state(first_state, rows, cols);
    state_copy_state(start, first_state, rows, cols);

    /* Stock initial state in open */
    open_states->state_list[0] = first_state;

    /* Initialize the solution state to be returned */
    state *solution;
    solution = malloc(1 * sizeof(state));
    state_init_state(solution, rows, cols);

    while(open_states->list_size != 0 && solution->parent == NULL) {
        /* Find the lowest state */
        state *lower_state = taquin_lower_state(open_states);

        /* Add the lowest state to the closed state */
        state_add_state(lower_state, close_states);

        /* Remove the lowest state from the open state */
        state_remove_state(lower_state, open_states, rows, cols);

        /* Find the next possible movement */
        taquin_next_state(lower_state, open_states, close_states, stop, solution, rows, cols);
    }

    return solution;
}

/* Print the route to the solution */
void taquin_print_route(state *current_state, int rows, int cols) {
    int counter, counter2;

    /* Init counter */
    counter2 = 0;
    counter = current_state->g;

    /* Create a new state */
    state parent_state;
    /* Init state allocation */
    state_init_state(&parent_state, rows, cols);

    /* Copy init node */
    state_copy_state(current_state, &parent_state, rows, cols);

    while (counter >= 0) {
        if (counter2 != counter) {
            /* Copy current node */
            state_copy_state(parent_state.parent, &parent_state, rows, cols);

            counter2++;
        }
        else {
            printf("\nRoute %d", parent_state.g);
            state_print_state(&parent_state, rows, cols);

            /* Reinit value */
            counter--;
            counter2 = 0;
            state_copy_state(current_state, &parent_state, rows, cols);
        }
    }
}

/* Generate stop & start of a taquin */
void taquin_generate_taquin(state *start, state *stop, int rows, int cols) {
    int r, c, count;

    /* Init state allocation */
    state_init_state(stop, rows, cols);
    state_init_state(start, rows, cols);

    /* Generate the stop array */
    count = 1;
    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            if (r == rows - 1 && c == cols - 1) {
                stop->arr[r][c] = 0;
            }
            else {
                stop->arr[r][c] = count++;
            }
        }
    }

    /* Duplicate the stop to start */
    state_copy_state(stop, start, rows, cols);

    printf("\n\nClosing state is : ");
    state_print_state(stop, rows, cols);
}


/* Generate random movement on start of a taquin */
void taquin_random_start_movement(state *start, int movement_number, int rows, int cols) {
    int i, r, c, movement_type, temp, exit;

    /* Make random movement on the start */
    for (i = 0; i < movement_number; i++) {
        r = 0;
        exit = 0;
        while (r < rows && exit == 0) {
            c = 0;
            while (c < cols && exit == 0) {
                if (start->arr[r][c] == 0) {

                    /* 0 we move to another row, 1 we move to another column */
                    movement_type = rand() % 2;

                    /* Move an element*/
                    if (movement_type == 0) {
                        /* 0 we move up, 1 we move down */
                        movement_type = rand() % 2;
                        if (((movement_type == 0) && (r - 1 >= 0)) || ((movement_type == 1) && (r + 1 >= rows))) {
                            temp = start->arr[r - 1][c];
                            start->arr[r - 1][c] = start->arr[r][c];
                        }
                        else {
                            temp = start->arr[r + 1][c];
                            start->arr[r + 1][c] = start->arr[r][c];
                        }
                    }
                    else {
                        /* 0 we move left, 1 we move right */
                        movement_type = rand() % 2;
                        if (((movement_type == 0) && (c - 1 >= 0)) || ((movement_type == 1) && (c + 1 >= cols))) {
                            temp = start->arr[r][c - 1];
                            start->arr[r][c - 1] = start->arr[r][c];
                        }
                        else {
                            temp = start->arr[r][c + 1];
                            start->arr[r][c + 1] = start->arr[r][c];
                        }
                    }
                    start->arr[r][c] = temp;

                    /* Exit var to avoid unnecessary loop */
                    exit = 1;
                }
                c++;
            }
            r++;
        }
    }

    /*Information for user */
    printf("\nStarting state is : ");
    state_print_state(start, rows, cols);
}


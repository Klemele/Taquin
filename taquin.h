#include "state.h"

/* Define globally the euristic used */
/* 1 for number of misplaced cases, 2 for distance evaluation */
int HEURISTIC;

/* Evaluate parameters h, g and f and the parent state */
void taquin_set_parameters(state *current_state, state *parent, state *stop, int rows, int cols);

/* Check the state with the list and add it to the corresponding list if necessary */
void taquin_check_states(state *current_state, states *open_states, states *close_states, int rows, int cols);

/* Iterate through list of open state to find the fastest one and return it */
state *taquin_lower_state(states *lstates);

/* Init and set a child state */
void taquin_create_child_state(state *parent_state, int r, int c, char movement_type, states *open_states, states *close_states, state *stop, state *solution, int rows, int cols);

/* Find the next possibilities of the taquin set the pointer 'solution' to the solution state if it has been find */
void taquin_next_state(state *current_state, states *open_states, states *close_states, state *stop, state *solution, int rows, int cols);

/* Find the solution of the taquin */
state *taquin_find_solution(states *open_states, states *close_states, state *start, state *stop, int rows, int cols);

/* Print the route to the solution */
void taquin_print_route(state *current_state, int rows, int cols);

/* Generate stop & start of a taquin */
void taquin_generate_taquin(state *start, state *stop, int rows, int cols);

/* Generate random movement on start of a taquin */
void taquin_random_start_movement(state *start, int movement_number, int rows, int cols);
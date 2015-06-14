#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "taquin.h"

int main() {
    int i, j, rows, cols;

    /* Set the size of ROWS & COLS */
    rows =  3;
    cols =  3;

    /* Set the heuristic type */
    /* 1 for number of misplaced cases, 2 for distance evaluation */
    HEURISTIC = 1;

    /* Generate file */
    time_t now = time(NULL);
    struct tm *ltime = localtime(&now);
    char filename[255];
    if (HEURISTIC == 1) {
        strftime(filename, 255, "stats_WrongCases_%Y%m%d.csv", ltime);
    }
    else {
        strftime(filename, 255, "stats_Manhattan_%Y%m%d.csv", ltime);
    }

    /* Add the path */
    char filepath[] = "%s";
    char filepath_computed[sizeof(filepath) + sizeof(filename)];
    sprintf(filepath_computed, filepath, filename);

    printf(filepath_computed);

    /* Remove stats.csv */
    remove(filepath_computed);

    /* Create file with header */
    FILE *file = fopen(filepath_computed, "a+");
    fprintf(file, "Complexity;Distance from start;Number of state open;Number of state close;Elapsed time in seconds");
    fclose(file);

    for (j = 0; j <= 10; j++) {
        /* Stop is the solution taquin */
        state *stop;
        /* Start is the initial taquin */
        state *start;
        /* Allocate memory */
        stop = malloc(1 * sizeof(state));
        start = malloc(1 * sizeof(state));

        /* Generate the taquin */
        taquin_generate_taquin(start, stop, rows, cols);

        for (i = 0; i <= 10000; i+=50) {
            /* User information */
            printf("\n\nMovement complexity : %d", i);

            /* Set the timer */
            clock_t timer_end, timer_start = clock();

            /* At each loop add a random movement on the current start state */
            taquin_random_start_movement(start, i, rows, cols);

            /* Pointer to the dynamically allocated array of struct state, already treated */
            states *close_states;
            close_states = malloc(1 * sizeof(states));
            if(close_states == NULL) {
                printf("\nout of memory\n");
            }
            close_states->list_size = 0;
            close_states->state_list = malloc(0 * sizeof(state*));
            if(close_states->state_list == NULL) {
                printf("\nout of memory\n");
            }

            /* Pointer to the dynamically allocated array of struct state in waiting for treatment */
            states *open_states;
            open_states = malloc(1 * sizeof(states));
            if(open_states == NULL) {
                printf("\nout of memory\n");
            }
            open_states->list_size = 1;
            open_states->state_list = malloc(1 * sizeof(state*));
            if(open_states->state_list == NULL) {
                printf("\nout of memory\n");
            }

            /* Create solution state */
            state *solution;

            /* Search the solution */
            solution = taquin_find_solution(open_states, close_states, start, stop, rows, cols);

            /* Timer management */
            timer_end = clock();
            int time = ((timer_end - timer_start)) / CLOCKS_PER_SEC;

            int hours, minutes, seconds;
            hours = time / 36000;
            minutes = (time % 36000) / 60;
            seconds = ((time % 3600000) % 60);

            /* Print the route solution */
            printf("\n\nPrint the route : ");
            taquin_print_route(solution, rows, cols);

            printf("\n\nTime taken %d hours %d minutes %d seconds", hours, minutes, seconds);

            /* Write to stats.csv : complexity - i; time - seconds; steps - g */
            FILE *file = fopen(filepath_computed, "a+");
            fprintf(file, "\n%d;%d;%d;%d;%d", i, solution->g, open_states->list_size, close_states->list_size, time);
            fclose(file);

            /* Free allocation memory */
            state_free_state(solution, rows);
            state_free_states(open_states, rows);
            state_free_states(close_states, rows);
        }
        /* Free allocation memory */
        state_free_state(start, rows);
        state_free_state(stop, rows);
    }

    /* Wait user to close */
    printf("\nPress any key to end...\n");
    fflush ( stdout );
    getchar();

    return 0;
}

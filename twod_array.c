#include "twod_array.h"
#include <stdio.h>
#include <stdlib.h>

/* Allocate memory to a 2D array */
//TODO method FREE array
void twod_array_allocate_array(int **src_arr, int rmax, int cmax) {
    int i =0;
    for(i = 0; i < rmax; i++) {
        /* Allocate memory for each pointer */
        src_arr[i] = malloc(cmax * sizeof(int));
        if(src_arr[i] == NULL) {
            printf("\nout of memory\n");
        }
    }
}

/* Free memory for a 2D array */
void twod_array_free_array(int **src_arr, int rmax) {
    int i =0;
    for(i = 0; i < rmax; i++) {
        free(src_arr[i]);
    }

    free(src_arr);
}


/* Print a 2D array*/
void twod_array_print_array(int **src_arr, int rmax, int cmax) {
    printf("\n\tarray : \n\t");
    int r, c, k;
    k=0;
    for (r = 0; r < rmax; r++) {
        for (c = 0; c < cmax; c++) {
            if (k != r) {
                k=r;
                printf("\n\t\t%d", src_arr[r][c]);
            }
            else {
                printf("\t%d", src_arr[r][c]);
            }
        }
    }
}

/* Compare two 2d array of the same size arr and arr2 and return 1 if this is the same array or 0 if not */
int twod_array_is_same_array(int **src_arr, int **dest_arr, int rmax, int cmax) {
    int r, c;
    for (r = 0; r < rmax; r++) {
        for (c = 0; c < cmax; c++) {
            if(src_arr[r][c] != dest_arr[r][c]){
                return 0;
            }
        }
    }
    return 1;
}

/* Copy the source array to the dest array */
void twod_array_copy_array(int **src_arr, int **dest_arr, int rmax, int cmax) {
    int r, c;
    for (r = 0; r < rmax; r++) {
        for (c = 0; c < cmax; c++) {
            dest_arr[r][c] = src_arr[r][c];
        }
    }
}

/* Return the number of differences between a source and a dest array */
int twod_array_count_differences(int **src_arr, int **dest_arr, int rmax, int cmax) {
    int r, c, count;
    count = 0;
    for (r = 0; r < rmax; r++) {
        for (c = 0; c < cmax; c++) {
            if (src_arr[r][c] != dest_arr[r][c]) {
                count++;
            }
        }
    }
    return count;
}

/* Allocate memory to a 2D array */
void twod_array_allocate_array(int **arr, int rmax, int cmax);

/* Free memory for a 2D array */
void twod_array_free_array(int **src_arr, int rmax);

/* Print a 2D array*/
void twod_array_print_array(int **arr, int r, int c);

/* Compare two 2d array of the same size arr and arr2 and return 1 if this is the same array or 0 if not */
int twod_array_is_same_array(int **arr, int **arr2, int rmax, int cmax);

/* Copy the source array to the dest array */
void twod_array_copy_array(int **src_arr, int **dest_arr, int rmax, int cmax);

/* Return the number of differences between a source and a dest array */
int twod_array_count_differences(int **src_arr, int **dest_arr, int rmax, int cmax);

#include <stdio.h>

typedef struct row_segtree{
    int *row_seg;
    int col_size;
}row_segtree;

void row_seg_init( row_segtree* tree, int cols );

/*
*READ KUNAL*
This is just the row segtree. These 1D segtrees will be clustered into
a final 2D segtree. The idea is that we will use 2D arrays to store the 1D segtree
of size (2*col_size)x5. Here each of the 5 elements are min,max,avg,stddev&sum for the range.
The final 2D segtree will be 3 dimensional (ironically) ; 2*col_size*(2*col_size)*5(should be fine).
*/
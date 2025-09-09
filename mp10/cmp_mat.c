#include "cmp_mat.h"
#include <stdio.h>

void printt(sp_tuples * mat) {
    if (mat == NULL) {
        printf("ERROR: Matrix is NULL\n");
        return;
    }
    
    printf("\n===============================================================\n");
    printf("SPARSE MATRIX ANALYSIS\n");
    printf("===============================================================\n");
    printf("Matrix dimensions: %d rows x %d columns\n", mat->m, mat->n);
    printf("Total possible elements: %d\n", mat->m * mat->n);
    printf("Non-zero elements: %d\n", mat->nz);
    
    if (mat->m * mat->n > 0) {
        double sparsity = (double)(mat->m * mat->n - mat->nz) / (mat->m * mat->n) * 100.0;
        printf("Sparsity: %.2f%% (%.2f%% of matrix is zeros)\n", sparsity, sparsity);
        printf("Memory efficiency: Storing only %.2f%% of elements!\n", 
               (double)mat->nz / (mat->m * mat->n) * 100.0);
    }
    
    printf("\nNON-ZERO ELEMENTS (Row, Column): Value\n");
    printf("---------------------------------------------------------------\n");
    
    sp_tuples_node *current = mat->tuples_head;
    int count = 0;
    while (current != NULL && count < 15) {  // Show first 15 elements
        printf("   (%4d, %4d): %8.3f", current->row, current->col, current->value);
        if (current->value > 0) printf(" [+]");
        else printf(" [-]");
        printf("\n");
        current = current->next;
        count++;
    }
    
    if (current != NULL) {
        int remaining = 0;
        while (current != NULL) {
            remaining++;
            current = current->next;
        }
        printf("   ... and %d more elements\n", remaining);
    }
    
    if (mat->nz == 0) {
        printf("   No non-zero elements (this is a zero matrix!)\n");
    }
    
    printf("\nWhy sparse matrices?\n");
    printf("  * Regular matrix would need %d memory slots\n", mat->m * mat->n);
    printf("  * This sparse representation needs only %d slots\n", mat->nz);
    if (mat->m * mat->n > 0 && mat->nz > 0) {
        printf("  * Space savings: %dx less memory!\n", 
               (mat->m * mat->n) / mat->nz);
    }
    printf("===============================================================\n\n");
}

int matcmpt(sp_tuples * matA, sp_tuples * matB) {
    // Simple comparison - not implemented
    return 0;
}

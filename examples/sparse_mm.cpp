#include "sparse_mm.h"
void sparse_mm(csr_t a[A_HEIGHT*A_WIDTH], unsigned int a_y, unsigned int a_x, int b[B_HEIGHT*B_WIDTH], int b_y, int b_x, int c[C_HEIGHT*C_WIDTH]) {
	unsigned long long * a_csr = (unsigned long long *) a;
	for(int ibx = 0; ibx < b_x ; ibx++) {
		for(int a_i = 0, iay = 0, sum = 0; iay < a_y; a_i++) {
			bool end_row = a_csr[a_i] & 1;
			unsigned int column = (a_csr[a_i] >> 1) & 0x7FFFFFFF;
			int value = a_csr[a_i] >> 32;
			if(end_row){
				c[iay++ * b_x + ibx] = sum;
				sum = 0;
			} else {
				sum += value * b[column*b_x + ibx];
			}
		}
	}
}

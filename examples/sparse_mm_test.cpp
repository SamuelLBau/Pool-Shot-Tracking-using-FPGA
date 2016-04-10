#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <random>
#include <limits>
#include <string.h>
#include "sparse_mm.h"


typedef int fill_t;


void fill(int * matrix, unsigned int dim_y, unsigned int dim_x, unsigned char sparsity);
void print(int * matrix, unsigned int dim_y, unsigned int dim_x);
void multiply(int * a, int a_y, unsigned int a_x, int * b, int b_y, int b_x, int * c);
void smm(csr_t * a_csr, unsigned int a_y, unsigned int a_x, int * b, int b_y, int b_x, int * c);
void smmt(csr_t * a_csr, unsigned int a_y, unsigned int a_x, int * b, int b_y, int b_x, int * c);
void print_csr(csr_t * a, unsigned int length);
int to_csr(int * a, int a_y, int a_x, csr_t * a_csr);
void from_csr(int * a, int a_y, int a_x, csr_t * a_csr);
int equals(csr_t * a, csr_t *b, unsigned int len);
int equals(int * a, int * b, unsigned int a_y, unsigned int a_x);
void transpose(int * a, int a_y, unsigned int a_x, int * at);
using namespace std;
int main() {
	int * array_a = new int[A_HEIGHT*A_WIDTH]();
	int * array_ap = new int[A_HEIGHT*A_WIDTH]();
	int * array_b = new int[B_HEIGHT*B_WIDTH]();
	int * array_bt = new int[B_HEIGHT*B_WIDTH]();
	int * array_c = new int[C_HEIGHT*C_WIDTH]();
	int * array_cp = new int[C_HEIGHT*C_WIDTH]();
	int * array_cpp = new int[C_HEIGHT*C_WIDTH]();
	int i;
	printf("%lu\n",sizeof(csr_t));
	fill(array_a,A_HEIGHT,A_WIDTH,64);
	fill(array_b,B_HEIGHT,B_WIDTH,128);
	transpose(array_b,B_HEIGHT,B_WIDTH, array_bt);
	multiply(array_a, A_HEIGHT, A_WIDTH, array_b, B_HEIGHT, B_WIDTH, array_c);
	printf("\n");
	//print(array_a,A_HEIGHT,A_WIDTH);
	printf("\n");
	//print(array_b,B_HEIGHT,B_WIDTH);
	printf("\n");
	//print(array_c,C_HEIGHT,C_WIDTH);
	
	csr_t * array_csr_a = new csr_t[A_HEIGHT*A_WIDTH];
	int len_csr_a = to_csr(array_a, A_HEIGHT, A_WIDTH, array_csr_a);
	printf("Len CSR A: %d\n",len_csr_a);
	//print_csr(array_csr_a,len_csr_a);

	from_csr(array_ap, A_HEIGHT, A_WIDTH, array_csr_a);
	//print(array_ap, A_HEIGHT, A_WIDTH);
	printf("Equals returned %d\n",i = equals(array_ap, array_a, A_HEIGHT, A_WIDTH));
	sparse_mm(array_csr_a, A_HEIGHT, A_WIDTH, array_b, B_HEIGHT, B_WIDTH, array_cp);
	printf("Equals returned %d\n",i =equals(array_c, array_cp, C_HEIGHT, C_WIDTH));
	return !i;
	//print(array_cp, C_HEIGHT, C_WIDTH);
	//smmt(array_csr_a, A_HEIGHT, len_csr_a, array_bt, B_WIDTH, B_HEIGHT, array_cpp);
	//printf("Equals returned %d\n",equals(array_c, array_cpp, C_HEIGHT, C_WIDTH));
	//print(array_cpp,C_HEIGHT,C_WIDTH);

}

int equals(csr_t * a, csr_t *b, unsigned int len) {
	return !memcmp(a,b, sizeof(csr_t)*len);
}
int equals(int * a, int * b, unsigned int a_y, unsigned int a_x) {
	return !memcmp(a,b, sizeof(int)*a_y*a_x);
}

void print_csr(csr_t * a, unsigned int length){
	for(int ia = 0; ia < length; ia ++){
		printf("%d, %u, %d\n", a[ia].csr_s.end_row, a[ia].csr_s.column, a[ia].csr_s.value);
	}
}

int to_csr(int * a, int a_y, int a_x, csr_t * a_csr) { 
	int idx = 0;
	for(unsigned int iay = 0; iay < a_y ; iay++) {
		for(unsigned int iax = 0; iax < a_x ; iax++) {
			if(a[iay*a_x + iax] != 0) {
				a_csr[idx++].csr_s = {0,iax,a[iay*a_x + iax]};
			}
		}
		a_csr[idx++].csr_s = {1,0,0};
	}
	return idx;
}

void from_csr(int * a, int a_y, int a_x, csr_t * a_csr) { 
	for(int a_i = 0, iay = 0; iay < a_y; a_i++) {
		if(a_csr[a_i].csr_s.end_row){
			iay++;
		} else {
			a[iay*a_x + a_csr[a_i].csr_s.column] = a_csr[a_i].csr_s.value;
		}
	}
}

void multiply(int * a, int a_y, unsigned int a_x, int * b, int b_y, int b_x, int * c) {
	for(int ibx = 0; ibx < b_x ; ibx++) {
		for(int iay = 0; iay < a_y ; iay++) {
			int sum = 0;
			for(int iax = 0; iax < a_x ; iax++) {
				sum += a[iay*a_x + iax] * b[iax*b_x + ibx];
			}
			c[iay * b_x + ibx] = sum;
		}
	}
}


void smm(csr_t * a, unsigned int a_y, unsigned int a_x, int * b, int b_y, int b_x, int * c) {
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

void smmt(csr_t * a, unsigned int a_y, unsigned int nelem, int * b, int bt_y, int bt_x, int * c) {
	unsigned long long * a_csr = (unsigned long long *) a;
	for(int ibty = 0; ibty < bt_y ; ibty++) {
		for(int a_i = 0, iay = 0, sum = 0; a_i < nelem; a_i++) {
			unsigned long long temp = a_csr[a_i];
			bool end_row = temp & 1;
			unsigned int column = (temp >> 1) & 0x7FFFFFFF;
			int value = temp >> 32;
			if(end_row){
				c[iay++ * bt_y + ibty] = sum;
				sum = 0;
			} else {
				sum += value * b[ibty*bt_x + column];
			}
		}
	}
}

/*void smm(csr_t * a_csr, unsigned int a_y, unsigned int a_x, int * b, int b_y, int b_x, int * c) {
	for(int ibx = 0; ibx < b_x ; ibx++) {
		for(int a_i = 0, iay = 0, sum = 0; iay < a_y; a_i++) {
			if(a_csr[a_i].csr_s.end_row){
				c[iay++ * a_y + ibx] = sum;
				sum = 0;
			} else {
				sum += a_csr[a_i].csr_s.value * b[a_csr[a_i].csr_s.column*b_x + ibx];
			}
		}
	}
}
*/

void fill(int * matrix, unsigned int dim_y, unsigned int dim_x, unsigned char sparsity) {
	std::random_device rd;
	std::mt19937 gen(rd());
	uniform_int_distribution<int> distribution(RN_MIN,RN_MAX);
	uniform_int_distribution<unsigned char> sparsifier(0,255);
	for(unsigned int i = 0; i < dim_x * dim_y; i++) {
		if(sparsifier(gen) <= sparsity){
			matrix[i] = distribution(gen);
		}
	}
}

void print(int * matrix, unsigned int dim_y, unsigned int dim_x) {
	//printf("[\n");
	for(unsigned int iy = 0; iy < dim_y; iy++) {
		printf("[ ");
		for(unsigned int ix = 0; ix < dim_x; ix++) {
			printf("%8d ", matrix[dim_x * iy  + ix]);
		}
		printf(" ]%s",iy==dim_y-1? "": "\n");
	}
	printf("\n");

}
void transpose(int * a, int a_y, unsigned int a_x, int * at) {
	for(int iay = 0; iay < a_y ; iay++) {
		for(int iax = 0; iax < a_x ; iax++) {
			at[iax*a_y + iay] = a[iay*a_x + iax];
		}
	}
}

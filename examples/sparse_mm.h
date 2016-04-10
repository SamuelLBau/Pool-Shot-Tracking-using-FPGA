#ifndef SPARSE_MM_H
#define SPARSE_MM_H
#define ARRAY_LENGTH 256
#define RN_MIN -256
#define RN_MAX 255
#define A_HEIGHT 2048
#define A_WIDTH  2048
#define B_HEIGHT 2048
#define B_WIDTH  1
#define C_HEIGHT A_HEIGHT
#define C_WIDTH  B_WIDTH

typedef	struct csr_s_t { 
	bool end_row:1;
	unsigned int column:31;
	int value:32;
} csr_s_t;

typedef union csr
{
	csr_s_t csr_s;
	unsigned long long csr_v;
} csr_t;

void sparse_mm(csr_t * a, unsigned int a_y, unsigned int a_x, int * b, int b_y, int b_x, int * c);
#endif

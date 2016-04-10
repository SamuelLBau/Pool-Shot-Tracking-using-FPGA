int array_sum(int array[64], unsigned int length)
{
	int sum = 0;
	for(int i = 0; i < 64; i++){
#pragma HLS UNROLL
		sum += array[i];
	}
	return sum;
}

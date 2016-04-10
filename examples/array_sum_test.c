#include <stdio.h>
#include <stdlib.h>
#define C_LENGTH 64
int main(){
	int * array = malloc(64*sizeof(int));
	int sum;
	for(int i = 0; i < C_LENGTH; i++){
		array[i] = i;
	}
	sum = array_sum(array, C_LENGTH);
	printf("Sum returned: %d\n", sum);

	if(sum == (C_LENGTH-1)*(C_LENGTH)/2){
		return 0;
	} else {
		return 1;
	}
}

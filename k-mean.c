#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define N 600
#define D 2 
#define K 3 // n_clusters
#define EPOCH 1000

int main(){
	double x[N][D]; // examples
 	int i, j; 
	double u[K][D]; // cluster centroids
	int index;

	FILE * file_d;

	// 1. Read input data
	file_d = fopen("data.txt", "r");
	for(i=0; i<N; i++)
		for(j=0; j<D; j++){
			fscanf(file_d, "%lf", &x[i][j]);			
	}
	// for(i=0; i<N; i++){
	// 	for(j=0; j<D; j++){
	// 		printf("%lf  ", x[i][j] );	
	// 	}
	// 	printf("\n");
	// }
	
	//---------
	
	// 2. Randomly initialize K cluster centroids (= K examples)
	srand(time(NULL));
	for(int p = 0; p < K; p++){
		index = rand()%N;
		// printf("%d\n", index);
		// printf("x: %lf %lf\n", x[index][0], x[index][1]);
		u[p][0] = x[index][0];
		u[p][1] = x[index][1]; 
	}

	//-------
	for(int n = 0; n < EPOCH; n++){
		// Cluster assignment step
				

		// Move centroid
	}	

}





































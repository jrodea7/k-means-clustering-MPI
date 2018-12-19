#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define SERVER 0
#define N 600
#define D 2 
#define K 3 // n_clusters
#define EPOCH 100

double dist(double, double, double, double);

int main(int argc, char ** argv){
	int rank, size;

	double x[N][D]; // examples
	int c[N]; // clusters
 	int i, j; 
	double u[K][D]; // cluster centroids
	int index;
	double min_dist;

	int n_elem[K];
	double sum_t[K][D];
	int index_t;
	FILE * file_d;

	int n_exam = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank == SERVER){
		// 1. Read input data
		file_d = fopen("data_600.txt", "r");
		fscanf(file_d, "%d", &n_exam);
		for(i=0; i<N; i++)
			for(j=0; j<D; j++){
				fscanf(file_d, "%lf", &x[i][j]);			
		}

		// 2. Randomly initialize K cluster centroids (= K examples)
		srand(time(NULL));
		for(int p = 0; p < K; p++){
			index = rand()%N;
			// printf("%d\n", index);
			// printf("x: %lf %lf\n", x[index][0], x[index][1]);
			u[p][0] = x[index][0];
			u[p][1] = x[index][1]; 
		}
	}


	MPI_Bcast(&numValues, 1, MPI_INT, SERVER, MPI_COMM_WORLD);
	MPI_Bcast(&data_size, 1, MPI_INT, SERVER, MPI_COMM_WORLD);
	MPI_Bcast(allValues, numValues, MPI_INT, SERVER, MPI_COMM_WORLD);



	// 3. Iterate
	for(int e = 0; e < EPOCH; e++){
		for(int i = 0; i < K; i++){
			n_elem[i] = 0;
			sum_t[i][0] = 0;
			sum_t[i][1] = 0;
		}
		// Cluster assignment step
		for(int n = 0; n < N; n++){
			c[n] = 1;
			min_dist = dist(x[n][0], x[n][1], u[0][0], u[0][1]);
			for(int m = 1; m <= K; m++){
				// printf("u1 = %lf, u2 = %lf, d = %lf\n", u[m-1][0], u[m-1][1], dist(x[n][0], x[n][1], u[m][0], u[m][1]));
				if(dist(x[n][0], x[n][1], u[m-1][0], u[m-1][1]) < min_dist){
					min_dist = dist(x[n][0], x[n][1], u[m-1][0], u[m-1][1]);
					c[n] = m;
				}
 			}	
		}	
		// // Move centroids
		for(int n = 0; n < N; n++){
			index_t = c[n]-1;
			sum_t[index_t][0] += x[n][0];
			sum_t[index_t][1] += x[n][1];
			n_elem[index_t]++;
		}
		for(int k = 0; k < K; k++){
			u[k][0] = (double) sum_t[k][0]/n_elem[k];
			u[k][1] = (double) sum_t[k][1]/n_elem[k];
		}	
	}	


	// for(int n = 0; n < N; n++){
	// 	printf("%d\n", c[n]);
	// }

	// for(int k = 0; k < K; k++){
	// 	printf("%lf %lf\n", u[k][0], u[k][1]);
	// }
}

double dist(double x1, double y1, double x2, double y2){
	return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);	
}

































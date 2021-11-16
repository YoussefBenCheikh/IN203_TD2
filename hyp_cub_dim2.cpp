# include <chrono>
# include <random>
# include <cstdlib>
# include <sstream>
# include <string>
# include <fstream>
# include <iostream>
# include <iomanip>
# include <mpi.h>



int main( int nargs, char* argv[] )
{

int rank, nbp, prev, next, tag1=1;

	MPI_Request reqs[2]; // required variable for non-blocking calls
	MPI_Status stats[2]; // required variable for Waitall routine

	MPI_Init( &nargs, &argv );

	MPI_Comm globComm;
	MPI_Comm_dup(MPI_COMM_WORLD, &globComm);

	MPI_Comm_size(globComm, &nbp);

	MPI_Comm_rank(globComm, &rank);

if (rank==0) 
{
	int jeton = 7;
	MPI_Send(&jeton, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
	MPI_Send(&jeton, 1, MPI_INT, 2, 1, MPI_COMM_WORLD);
	std::cout<<"jeton: "<<jeton<<" affiché par tâche: "<<rank<<"\n";
} else if (rank==1) {
	int jeton;
	MPI_Recv(&jeton, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, stats);
	MPI_Send(&jeton, 1, MPI_INT, 3, 1, MPI_COMM_WORLD);
	std::cout<<"jeton: "<<jeton<<" affiché par tâche: "<<rank<<"\n";
} else if (rank==2){
	int jeton;
	MPI_Recv(&jeton, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, stats);
	std::cout<<"jeton: "<<jeton<<" affiché par tâche: "<<rank<<"\n";
} else {
	int jeton;
	MPI_Recv(&jeton, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, stats);
	std::cout<<"jeton: "<<jeton<<" affiché par tâche: "<<rank<<"\n";
}



MPI_Finalize();
return EXIT_SUCCESS;
}

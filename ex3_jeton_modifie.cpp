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

	prev = rank -1;
	next = rank +1;
	if (rank == 0) prev = nbp - 1;
	if (rank == (nbp - 1)) next = 0;

	int val=rank*rank;
	MPI_Isend(&val , 1, MPI_INT , next , tag1 , MPI_COMM_WORLD , &reqs[1]);
		
	int nval;
	MPI_Irecv(&nval, 1, MPI_INT , prev , tag1 , MPI_COMM_WORLD , &reqs[0]);
	MPI_Wait(&reqs[0] , &stats[0]);
	nval++;
	std::cout<<"task "<<rank<<" displays "<<nval<<"\n";




	MPI_Finalize();
	return EXIT_SUCCESS;
}

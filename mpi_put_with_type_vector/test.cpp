#include <mpi.h>

#include <iostream>
#include <vector>

int main() {
  MPI_Init(nullptr, nullptr);
  int rank, size;
  auto comm = MPI_COMM_WORLD;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &size);

  MPI_Win win;
  int *win_data;
  MPI_Win_allocate(3 * sizeof(int) * rank, sizeof(int), MPI_INFO_NULL, comm,
                   &win_data, &win);

  if (rank == 0) {
    std::vector<int> txt = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    MPI_Datatype vec_type;
    MPI_Type_vector(3, 1, 3, MPI_INT, &vec_type);
    MPI_Type_commit(&vec_type);

    MPI_Win_lock(MPI_LOCK_EXCLUSIVE, 1, 0, win);
    MPI_Put(&txt[0], 1, vec_type, 1, 0, 3, MPI_INT, win);
    MPI_Win_unlock(1, win);
    MPI_Barrier(comm);
  } else if (rank == 1) {
    MPI_Barrier(comm);
    int three[3];
    MPI_Win_lock(MPI_LOCK_EXCLUSIVE, 1, 0, win);
    MPI_Get(three, 3, MPI_INT, 1, 0, 3, MPI_INT, win);
    MPI_Win_unlock(1, win);
    std::cout << "Rank 1 read: " << three[0] << ", " << three[1] << ", "
              << three[2] << std::endl;
  } else {
    MPI_Barrier(comm);
  }

  MPI_Finalize();
  return 0;
}

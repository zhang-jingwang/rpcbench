#include <stdio.h>
#include <sys/time.h>
#include <mpi.h>
#include "bench-args.h"
#include <assert.h>
#include "rpc_method.h"

int main(int argc, char **argv)
{
	int res;
	int i;
	double start, end;
	int rank, rsize;
	struct bench_options opts;
	void *client;
	const struct rpc_method *method = &bmirpc;
	void *data;
	long data_len;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &rsize);

	bench_args(&opts, argc, argv);
	if (rank == 0) bench_args_dump(&opts);
	data_len = opts.message_len;
	data = malloc(data_len);
	client = method->create_client(opts.server_ip);
	MPI_Barrier(MPI_COMM_WORLD);
	start = MPI_Wtime();
	for (i = 0; i < opts.iteration; i++) {
		res = method->call_server(client, data, data_len);
//		res = *(rpcbench_call_1(&arg, cl));
		assert(res == 12345);
	}
	MPI_Barrier(MPI_COMM_WORLD);
	end = MPI_Wtime();
	if (rank == 0)
		printf("%f\n", (opts.iteration * rsize)/(end - start));
	free(data);
	method->destroy_client(client);
//	clnt_destroy(cl);
	MPI_Finalize();
	return 0;
}

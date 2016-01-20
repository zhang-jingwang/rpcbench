#include <rpc/rpc.h>
#include <./rpc/rpcbench.h>
#include "rpc_method.h"

void *sunrpc_create_client(const char *server_ip)
{
	return clnt_create(server_ip, RPCBENCHPROG, RPCBENCHVERS, "tcp");
}

int sunrpc_call_server(void *cl, void *data_val, long data_len)
{
	data arg;

	arg.data_val = data_val;
	arg.data_len = data_len;
	return *(rpcbench_call_1(&arg, cl));
}

void sunrpc_destroy_client(void *cl)
{
	clnt_destroy(((CLIENT *)cl));
}

const struct rpc_method sunrpc = {
	.name = "SUN RPC",
	.create_client = sunrpc_create_client,
	.call_server = sunrpc_call_server,
	.destroy_client = sunrpc_destroy_client
};


#include <./rpc/rpcbench.h>

int * rpcbench_call_1_svc(data *data, struct svc_req *req)
{
	static int ret = 12345;
	return &ret;
}

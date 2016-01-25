#ifndef _RPC_METHOD_H_
#define _RPC_METHOD_H_

struct rpc_method {
	const char *name;
	void *(*create_client)(const char *server_ip);
	int (*call_server)(void *cl, void *data, long data_len);
	void (*destroy_client)(void *cl);
};

const struct rpc_method sunrpc;
const struct rpc_method bmirpc;

#endif

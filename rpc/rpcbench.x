
typedef opaque data<>;

program RPCBENCHPROG {
	version RPCBENCHVERS {
		int RPCBENCH_CALL(data) = 1;
	} = 1;
} = 0x20000009;

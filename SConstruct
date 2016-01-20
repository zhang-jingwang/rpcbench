rpcgen = Builder(action = 'rpcgen $SOURCE')
env=Environment(CC='/usr/lib64/mpich/bin/mpicc',
	BUILDERS = {'RPC' : rpcgen})
env.RPC('rpc/rpcbench.h', './rpc/rpcbench.x')
env.Append( CPPPATH=['./'] )
env.Program('rpcbench_server', ['./src/rpcbench_server.c', './rpc/rpcbench_svc.c', './rpc/rpcbench_xdr.c'], CC='gcc')
env.Program('rpcbench_client', ['./rpc/rpcbench_clnt.c', './src/clnt_main.c', './rpc/rpcbench_xdr.o', './src/bench-args.c', './src/method_sunrpc.c'])
env.Depends('rpcbench_server', 'rpc/rpcbench.h')
env.Depends('rpcbench_client', 'rpc/rpcbench.h')
AddOption('--orangefs',
	dest='orangefs',
	type='string',
	nargs=1,
	action='store',
	metavar='DIR',
	help='orangefs build directory')
bmi=Environment(ORANGEFS=GetOption('orangefs'), CCFLAGS='-g -O0')
bmi.Append(CPPPATH=['$ORANGEFS/', '$ORANGEFS/src/io/bmi/',
				  '$ORANGEFS/src/common/misc'])
bmi.Append(LIBPATH='$ORANGEFS/lib/')
bmi.Program('bmi_server', ['./src/bmi_server.c'], LIBS='bmi')
bmi.Object('./src/method_bmi.o', './src/method_bmi.c')

rpcgen = Builder(action = 'rpcgen $SOURCE')
env=Environment(CC='/usr/lib64/mpich/bin/mpicc',
	BUILDERS = {'RPC' : rpcgen}, ORANGEFS=GetOption('orangefs'))
env.RPC('rpc/rpcbench.h', './rpc/rpcbench.x')
env.Append( CPPPATH=['./'] )
env.Program('rpcbench_server', ['./src/rpcbench_server.c', './rpc/rpcbench_svc.c', './rpc/rpcbench_xdr.c'], CC='gcc')
env.Program('rpcbench_client', ['./rpc/rpcbench_clnt.c', './src/clnt_main.c', './rpc/rpcbench_xdr.o', './src/bench-args.c', './src/method_sunrpc.c', './src/method_bmi.o'], LIBS='bmi', LIBPATH='$ORANGEFS/lib/')
env.Depends('rpcbench_server', 'rpc/rpcbench.h')
env.Depends('rpcbench_client', 'rpc/rpcbench.h')


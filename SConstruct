AddOption('--method',
	dest='method',
	type='string',
	nargs=1,
	action='store',
	help='RPC method: rpc, bmi or asio')
method=GetOption('method')
AddOption('--orangefs',
	dest='orangefs',
	type='string',
	nargs=1,
	action='store',
	metavar='DIR',
	help='orangefs build directory')
orangefs=GetOption('orangefs')
AddOption('--mpicc',
	dest='mpicc',
	type='string',
	nargs=1,
	action='store',
	metavar='FILE',
	default='mpicc',
	help='PATH to the mpicc command')
env=Environment(CC=GetOption('mpicc'))
clientobjs=[]
if method == 'rpc':
   rpcgen = Builder(action = 'rpcgen $SOURCE')
   rpc = Environment(BUILDERS = {'RPC' : rpcgen})
   rpc.Append( CPPPATH=['./'] )
   rpc.RPC(['./rpc/rpcbench_xdr.c', './rpc/rpcbench.h',
   	    'rpc/rpcbench_clnt.c', 'rpc/rpcbench_svc.c'], './rpc/rpcbench.x')
   xdrobj = rpc.Object('./rpc/rpcbench_xdr.o', './rpc/rpcbench_xdr.c')
   rpc.Program('rpc_server', ['./src/rpcbench_server.c', './rpc/rpcbench_svc.c', xdrobj])
   clientobjs = rpc.Object(['./rpc/rpcbench_clnt.c', './src/method_sunrpc.c']) + [xdrobj]
elif method == 'bmi':
   bmi=Environment(ORANGEFS=orangefs)
   bmi.Append(CPPPATH=['$ORANGEFS/', '$ORANGEFS/src/io/bmi/',
				       '$ORANGEFS/src/common/misc'])
   bmi.Append(LIBPATH='$ORANGEFS/lib/')
   bmi.Program('bmi_server', ['./src/bmi_server.c'], LIBS='bmi')
   clientobjs = bmi.Object('./src/method_bmi.o', './src/method_bmi.c')
   env.Append(LIBS='bmi', LIBPATH=orangefs+'/lib')
elif method == '':
   print "You must specify the test method [rpc, bmi or asio]!"

env.Program('rpcbench_client', ['./src/clnt_main.c', './src/bench-args.c'] + clientobjs)
env.Depends('rpcbench_client', 'rpc/rpcbench.h')
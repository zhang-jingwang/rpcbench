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
AddOption('--mpibin',
	dest='mpibin',
	type='string',
	nargs=1,
	action='store',
	metavar='DIR',
	default='',
	help='PATH to the mpicc command')
mpibin=GetOption('mpibin')
env=Environment(CC=mpibin+'/mpicc', CXX=mpibin+'mpicxx')
clientobjs=[]
if method == 'rpc':
   rpcgen = Builder(action = 'rpcgen $SOURCE')
   rpc = Environment(BUILDERS = {'RPC' : rpcgen})
   rpc.Append( CPPPATH=['./'] )
   rpc.RPC(['./rpc/rpcbench_xdr.c', './rpc/rpcbench.h',
   	    'rpc/rpcbench_clnt.c', 'rpc/rpcbench_svc.c'], './rpc/rpcbench.x')
   xdrobj = rpc.Object('./rpc/rpcbench_xdr.o', './rpc/rpcbench_xdr.c')
   rpc.Program('rpc_server', ['./src/rpcbench_server.c', './rpc/rpcbench_svc.c', xdrobj])
   clientobjs = rpc.Object(['./rpc/rpcbench_clnt.c', './src/method_rpc.c']) + [xdrobj]
elif method == 'bmi':
   bmi=Environment(ORANGEFS=orangefs)
   bmi.Append(CPPPATH=['$ORANGEFS/', '$ORANGEFS/src/io/bmi/',
				       '$ORANGEFS/src/common/misc'])
   bmi.Append(LIBPATH='$ORANGEFS/lib/')
   bmi.Program('bmi_server', ['./src/bmi_server.c'], LIBS='bmi')
   clientobjs = bmi.Object('./src/method_bmi.o', './src/method_bmi.c')
   env.Append(LIBS='bmi', LIBPATH=orangefs+'/lib')
elif method == 'asio':
   asio=Environment(CCFLAGS='--std=c++11')
   asio.Append(LIBS='boost_system')
   env.Append(LIBS='boost_system')
   asio.Program('asio_server', ['./src/asio_server.cpp'])
   clientobjs = asio.Object('./src/method_asio.o', './src/method_asio.cpp')
else:
   print "You must specify the test method [rpc, bmi or asio]!"

env.Append(CPPDEFINES=['METHOD_BY_SCONS=' + method])
env.Program('rpcbench_client', ['./src/clnt_main.c', './src/bench-args.c'] + clientobjs)

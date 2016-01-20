/*
 * (C) 2001 Clemson University and The University of Chicago
 *
 * See COPYING in top-level directory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <getopt.h>
#include <mpi.h>
#include "bench-args.h"

int bench_args(
    struct bench_options *user_opts,
    int argc,
    char **argv)
{
    char flags[] = "l:i:s:";
    int one_opt = ' ';

    int ret = -1;

    /* fill in defaults */
    user_opts->message_len = 128;
    user_opts->iteration = 1000;
    user_opts->flags = 0;

    /* look at command line arguments */
    while ((one_opt = getopt(argc, argv, flags)) != EOF)
    {
	switch (one_opt)
	{
	case ('s'):
	    ret = sscanf(optarg, "%s", (char *)&user_opts->server_ip);
	    break;
	case ('l'):
	    ret = sscanf(optarg, "%d", &user_opts->message_len);
	    break;
	case ('i'):
	    ret = sscanf(optarg, "%d", &user_opts->iteration);
	    break;
	default:
	    break;
	}
	if (ret < 1)
	{
	    return -1;
	}
    }
    return (0);
}

void bench_args_dump(
    struct bench_options *opts)
{
    printf("Options:\n");
    printf("server IP address: %s\n", opts->server_ip);
    printf("message length: %d\n", opts->message_len);
    printf("number of iteration: %d\n", opts->iteration);

    return;
}

/*
 * Local variables:
 *  c-indent-level: 4
 *  c-basic-offset: 4
 * End:
 *
 * vim: ts=8 sts=4 sw=4 expandtab
 */

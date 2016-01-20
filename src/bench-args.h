/*
 * (C) 2001 Clemson University and The University of Chicago
 *
 * See COPYING in top-level directory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <mpi.h>

#ifndef __BENCH_ARGS_H
#define __BENCH_ARGS_H

struct bench_options
{
    int flags;
    int message_len;
    int iteration;
    char server_ip[256];
};

int bench_args(
    struct bench_options *user_opts,
    int argc,
    char **argv);
void bench_args_dump(
    struct bench_options *opts);

#endif /* __BENCH_ARGS_H */

/*
 * Local variables:
 *  c-indent-level: 4
 *  c-basic-offset: 4
 * End:
 *
 * vim: ts=8 sts=4 sw=4 expandtab
 */

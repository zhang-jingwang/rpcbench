#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <getopt.h>
#include <bmi.h>
#include <assert.h>

struct server_args {
	char method[16];
	char ip_addr[64];
};

int parse_args(struct server_args *args,
	int argc,
	char **argv)
{
	char flags[] = "m:s:";
	int one_opt = ' ';
	int ret = -1;

	/* look at command line arguments */
	while ((one_opt = getopt(argc, argv, flags)) != EOF)
	{
		switch (one_opt)
		{
		case ('s'):
			ret = sscanf(optarg, "%s", (char *)args->ip_addr);
			break;
		case ('m'):
			ret = sscanf(optarg, "%s", args->method);
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

int main(int argc, char **argv)
{
	struct server_args args;
	bmi_context_id bmi_context;
	struct BMI_unexpected_info bmi_info;
	int ret;
	int outcount;

	parse_args(&args, argc, argv);
	ret = BMI_initialize(args.method, args.ip_addr, BMI_INIT_SERVER);
	assert(ret == 0);
	ret = BMI_open_context(&bmi_context);
	assert(ret == 0);
	while (1) {
		bmi_op_id_t opid;
		int response = 12345;
		bmi_error_code_t error_code;
		bmi_size_t actual_size;
		void *user_ptr;

		do {
			ret = BMI_testunexpected(1, &outcount, &bmi_info,
						5000);
		} while (ret == 0 && outcount == 0);
		if (ret < 0) printf("Failed to send response!\n");
		ret = BMI_post_send(&opid, bmi_info.addr, &response, 4,
				BMI_EXT_ALLOC, 0, NULL, bmi_context, NULL);
		if (ret == 1) continue; // Immediate success.
		do {
			ret = BMI_test(opid, &outcount, &error_code,
				&actual_size, &user_ptr, 5000, bmi_context);
		} while (ret == 0 && outcount == 0);
		if (ret < 0) printf("Failed to send response!\n");
	}
	BMI_close_context(bmi_context);
	BMI_finalize();
}

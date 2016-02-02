#include "rpc_method.h"
#include <bmi.h>
#include <assert.h>

bmi_context_id bmi_context;
BMI_addr_t bmi_addr;

void *bmi_create_client(const char *server_ip)
{
	int ret;

	ret = BMI_initialize(NULL, NULL, 0);
	assert(ret == 0);
	ret = BMI_open_context(&bmi_context);
	assert(ret == 0);
	ret = BMI_addr_lookup(&bmi_addr, server_ip);
	assert(ret == 0);
        return &bmi_addr;
}

int bmi_call_server(void *cl, void *data_val, long data_len)
{
	int ret;
	bmi_op_id_t opid;
	int outcount = 0;
	bmi_error_code_t error_code;
	bmi_size_t actual_size;
	void *user_ptr = NULL;
	int response = -1;

	ret = BMI_post_sendunexpected(&opid, bmi_addr,
				data_val, data_len,
				BMI_EXT_ALLOC, 0, NULL,
				bmi_context, NULL);
	assert(ret >= 0);
	while (ret == 0 && outcount == 0) {
		ret = BMI_test(opid, &outcount, &error_code,
			&actual_size, &user_ptr, 5000, bmi_context);
	}
	if (ret < 0) return ret;
	ret = BMI_post_recv(&opid, bmi_addr, &response, 4, &actual_size,
			BMI_EXT_ALLOC, 0, NULL, bmi_context, NULL);
	do {
		ret = BMI_test(opid, &outcount, &error_code,
			&actual_size, &user_ptr, 5000, bmi_context);
	} while (ret == 0 && outcount == 0);
	if (ret < 0) return ret;
	return response;
}

void bmi_destroy_client(void *cl)
{
	BMI_close_context(bmi_context);
	BMI_finalize();
}

const struct rpc_method bmi = {
	.name = "bmi",
	.create_client = bmi_create_client,
	.call_server = bmi_call_server,
	.destroy_client = bmi_destroy_client
};

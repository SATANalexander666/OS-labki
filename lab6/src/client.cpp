#include <unistd.h>
#include <zmq.hpp>

#include <string>
#include <iostream>

int main (int argc, char const *argv[]) 
{
	void* context = zmq_ctx_new();
	void* request = zmq_socket(context, ZMQ_REQ);
	zmq_connect(request, "tcp://localhost:4040");
	
	int count = 0;
    std::string str;
	
	while (getline(std::cin, str)) 
	{
		zmq_msg_t req;
		zmq_msg_init_size(&req, str.length());
		memcpy(zmq_msg_data(&req), str.data(), str.length());

		zmq_msg_send(&req, request, 0);
		zmq_msg_close(&req);

		zmq_msg_t reply;
		zmq_msg_init(&reply);

		zmq_msg_recv(&reply, request, 0);
		zmq_msg_close(&reply);
	}

	zmq_close(request);
	zmq_ctx_destroy(context);
	
	return 0;
}

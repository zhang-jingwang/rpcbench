//
// blocking_tcp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include "rpc_method.h"

using boost::asio::ip::tcp;

boost::asio::io_service io_service;

tcp::socket s(io_service);
tcp::resolver resolver(io_service);

void *asio_create_client(const char *server_ip)
{
    boost::asio::connect(s, resolver.resolve({server_ip, "3333"}));
    return &s;
}

int asio_call_server(void *cl, void *data_val, long data_len)
{
  try
  {
    boost::asio::write(s, boost::asio::buffer(data_val, data_len));
    size_t reply_length = boost::asio::read(s,
        boost::asio::buffer(data_val, data_len));
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  return 12345;
}

void asio_destroy_client(void *cl)
{
}

//extern "C" {
extern const struct rpc_method asio = {
	.name = "BOOST ASIO",
	.create_client = asio_create_client,
	.call_server = asio_call_server,
	.destroy_client = asio_destroy_client
};
//}

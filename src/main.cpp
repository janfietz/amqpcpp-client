#include <boost/asio/io_service.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/deadline_timer.hpp>

#include "amqpcpp.h"
#include "amqpcpp/libboostasio.h"

int main(int argc, char **argv)
{

  // access to the boost asio handler
  // note: we suggest use of 2 threads - normally one is fin (we are simply demonstrating thread safety).
  boost::asio::io_service service(4);

  // handler for libev
  AMQP::LibBoostAsioHandler handler(service);

  // make a connection
  AMQP::TcpConnection connection(&handler, AMQP::Address("amqp://guest:guest@localhost/"));

  // we need a channel too
  AMQP::TcpChannel channel(&connection);

  // create a temporary queue
  channel.declareQueue(AMQP::exclusive).onSuccess([&connection](const std::string &name, uint32_t messagecount, uint32_t consumercount) {
    // report the name of the temporary queue
    std::cout << "declared queue " << name << std::endl;

    // now we can close the connection
    connection.close();
  });

  // run the handler
  // a t the moment, one will need SIGINT to stop.  In time, should add signal handling through boost API.
  return service.run();
}

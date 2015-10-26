#pragma once
#ifndef MOBILE_SERVER_H
#define MOBILE_SERVER_H
#include <algorithm>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

namespace mobile
{
using boost::asio::ip::tcp;
typedef boost::function<void (char*)> ReadHandler;

class Session 
{
public:
  Session(boost::asio::io_service& io_service, ReadHandler handler)
    : socket_(io_service),
      handler_(handler)
  {
  }

  inline tcp::socket& socket() { return socket_; }
  void start()
  {
    receive();
  }

  void receive()
  {
    socket_.async_read_some(
        boost::asio::buffer(receive_buffer_, max_length),
        boost::bind(&Session::handle, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

private:
  void handle(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    if(!error)
    {
      handler_(receive_buffer_);
      std::fill(&receive_buffer_[0], &receive_buffer_[0]+max_length, '\0');
      receive();
    }
    else
    {
      delete this;
    }
  }

  tcp::socket socket_;
  enum { max_length = 1024*160 };
  char receive_buffer_[max_length];
  boost::function<void (char*)> handler_;
};


class Server
{
public:
  Server(boost::asio::io_service& io_service, short port, ReadHandler handler)
    : io_service_(io_service),
      acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
      handler_(handler)
  {
    start_accept();
  }

private:
  void start_accept()
  {
    Session* session = new Session(io_service_, handler_);
    acceptor_.async_accept(
        session->socket(),
        boost::bind(
          &Server::handle_accept,
          this,
          session,
          boost::asio::placeholders::error));
  }

  void handle_accept(
    Session* session,
    const boost::system::error_code& error)
  {
    if(!error)
    {
      session->start();
    }
    else
    {
      delete session;
    }

    start_accept();
  }
  
  boost::asio::io_service& io_service_;
  tcp::acceptor acceptor_;
  ReadHandler handler_;
};
}

#endif

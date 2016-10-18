#pragma once

#include "iac.h"
#include "queue.h"

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <array>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
 protected:
  tcp::socket socket_;
  enum { max_length = 1024 };
  std::array<char, max_length> data_;

  bool running_ = true;

  virtual void handle_connect() = 0;
  virtual void handle_line(const std::string& data) = 0;
  virtual void handle_iac(const std::array<char, max_length>& data, std::size_t bytes) = 0;

  void read() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
      [this, self](boost::system::error_code ec, std::size_t bytes) {
        if (!running_) {
          return;
        }
        if (!ec) {
          if (data_[0] == (char)iac::IAC) {
            handle_iac(data_, bytes);
          } else {
            handle_line(std::string(data_.data(), bytes));
          }
          read();
        }
      });
  }

  void write(const std::string& line) {
    boost::asio::write(socket_, boost::asio::buffer(line));
  }

 public:
  Session(tcp::socket socket) : socket_(std::move(socket)) {}

  void start() {
    handle_connect();
    read();
  }
};

template<typename T>
class BbsServer {
 private:
  boost::asio::io_service io_service_;
  short port_;
  tcp::acceptor acceptor_;
  tcp::socket socket_;

  void accept() {
    acceptor_.async_accept(socket_,
      [this](boost::system::error_code ec) {
        if (!ec) {
          std::make_shared<T>(std::move(socket_))->start();
        }
        accept();
      });
  }

 public:
  BbsServer(short port)
    : port_(port), acceptor_(io_service_, tcp::endpoint(tcp::v6(), port_)),
      socket_(io_service_) {}

  void run() {
    std::cout << "Starting server on port " << port_ << std::endl;
    accept();
    io_service_.run();
  }
};

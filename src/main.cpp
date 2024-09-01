#include <array>
#include <asio/io_context.hpp>
#include <iostream>
#include <asio.hpp>
#include <system_error>
#include <ctime>
#include<functional>

using asio::ip::tcp;

int client(int argc, char* argv[]);
int server(int argc, char* argv[]);
std::string make_dt_string();

auto run_server = std::bind(server, 0, std::placeholders::_1); 

int main(int argc, char* argv[]){ 
  if(argc < 2){
    std::cerr << "Usage: TcppNet `client | server` <host>" << std::endl;
  }
  else if(argc < 3){
    return run_server(argv);
  }
  else{
    return client(argc, argv);
  }
}

int client(int argc, char* argv[]){
  try {
    if(argc != 3) {
      std::cerr << "Usage: cnet client <host>" << std::endl;
      return 1;
    }

    asio::io_context ioc;
    tcp::resolver resolver(ioc);
    
    tcp::resolver::results_type endpoints = resolver.resolve(argv[2], "daytime");
    tcp::socket socket(ioc);
    asio::connect(socket, endpoints);
  
    for(;;) {
      std::array<char, 128> buff;
      std::error_code error;

      size_t len = socket.read_some(asio::buffer(buff), error);

      if(error == asio::error::eof)
        break;
      else if(error)
        throw std::system_error(error);
      
      std::cout.write(buff.data(), len);
    }
  }

  catch(std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}


int server(int argc, char* argv[]){
  try {
    asio::io_context ioc;
    tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 13));

    for(;;) {
      tcp::socket sock(ioc);
      acceptor.accept(sock);

      std::string message = make_dt_string();
      std::error_code ignored_error;

      asio::write(sock, asio::buffer(message), ignored_error);
    }
  }

  catch(std::exception& e){
    std::cerr << e.what() << std::endl;
  }

  return 0;
}

std::string make_dt_string(){
  using namespace std; //For time_t, time, and ctime
  time_t now = time(0);
  return ctime(&now);
}

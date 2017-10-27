set -o xtrace
g++ -o hey client_main.cc client.cc message.cc
g++ -o hi server_main.cc server.cc message.cc


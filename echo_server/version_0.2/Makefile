server_client_tcp: server_tcp.o client_tcp.o socket.o base.o
	g++ -Wall server_tcp.o socket.o base.o -o server_tcp
	g++ -Wall client_tcp.o socket.o base.o -o client_tcp

server_client_udp: server_udp.o client_udp.o socket.o base.o
	g++ -Wall server_udp.o socket.o base.o -o server_udp
	g++ -Wall client_udp.o socket.o base.o -o client_udp

server_tcp.o: server_tcp.cpp
	g++ -c -Wall server_tcp.cpp

client_tcp.o: client_tcp.cpp
	g++ -c -Wall client_tcp.cpp

server_udp.o: server_udp.cpp
	g++ -c -Wall server_udp.cpp

client_udp.o: client_udp.cpp
	g++ -c -Wall client_udp.cpp

socket.o: socket.cpp
	g++ -c -Wall socket.cpp

base.o: base.cpp
	g++ -c -Wall base.cpp

clean:
	rm -rf *.o server_tcp client_tcp server_udp client_udp


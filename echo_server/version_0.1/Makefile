server_client: server.o client.o socket.o base.o
	g++ -Wall server.o socket.o base.o -o server
	g++ -Wall client.o socket.o base.o -o client

server.o: server.cpp
	g++ -c -Wall server.cpp

client.o: client.cpp
	g++ -c -Wall client.cpp

socket.o: socket.cpp
	g++ -c -Wall socket.cpp

base.o: base.cpp
	g++ -c -Wall base.cpp

clean:
	rm -rf *.o server client


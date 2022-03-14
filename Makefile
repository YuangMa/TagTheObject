
#
# Makefile for miniGFS, ecs251 and ecs36b
#

CC = g++ -std=c++17

# CFLAGS = -g

# for most Linux environments, but might need to be changed to find json stuff
CFLAGS = -g -I/usr/include/jsoncpp

# CFLAGS = -g -Wall -Wstrict-prototypes
# CFLAGS = -O3

# the following, RPCG, are JSONRPC generated files
RPCG_INCS =	tagging_client.h tagging_server.h

CORE_INCS =	File.h Shadow_Directory.h $(RPCG_INCS)
CORE_OBJS =	File.o Shadow_Directory.o

# libraries needed for JSON and JSONRPC
LDFLAGS_SV = 	-ljsoncpp -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server
LDFLAGS_CL = 	-ljsoncpp -lcurl -ljsonrpccpp-common -ljsonrpccpp-client

# rules

all: 	client1 server

tagging_client.h:	tagging.json
	jsonrpcstub tagging.json --cpp-server=tagging_Server --cpp-client=tagging_Client
tagging_server.h:	tagging.json
	jsonrpcstub tagging.json --cpp-server=tagging_Server --cpp-client=tagging_Client
File.o:	File.cpp File.h
	$(CC) -c $(CFLAGS) File.cpp
Shadow_Directory.o:	Shadow_Directory.cpp Shadow_Directory.h File.h tagging_client.h
	$(CC) -c $(CFLAGS) Shadow_Directory.cpp
client1.o:	client1.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) client1.cpp
server.o:	server.cpp $(CORE_INCS) tagging_server.h
	$(CC) -c $(CFLAGS) server.cpp
client1:	$(CORE_OBJS) client1.o
	$(CC) -o client1 $(CORE_OBJS) client1.o $(LDFLAGS_CL)
server:	$(CORE_OBJS) server.o
	$(CC) -o server $(CORE_OBJS) server.o $(LDFLAGS_SV) $(LDFLAGS_CL)
clean:
	rm -f *.o *~ core $(EXE_FILES) $(RPCG_INCS)

# end of the Makefile
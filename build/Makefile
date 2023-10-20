CC = g++
CFLAGS = -Wall -O2 -std=c++17 -march=native
#CFLAGS = -Wall -O2 -std=c++17 -fsanitize=address -static-libasan -g -march=native
SRC = ../src
BUILD = ../build
HEADERS = $(SRC)/WYPB_Exception.hpp $(SRC)/WYPB_Player.hpp $(SRC)/WYPB_Event.hpp $(SRC)/WYPB_PlayerMgr.hpp $(SRC)/WYPB_EventMgr.hpp $(SRC)/WYPB_Logger.hpp $(SRC)/WYPB_IO.hpp $(SRC)/WYPB_Serialize.hpp
OBJS = WYPB_Player.o WYPB_Event.o WYPB_PlayerMgr.o WYPB_EventMgr.o WYPB_Logger.o WYPB_IO.o WYPB_Serialize.o
LIBS = -l"stdc++"
TARGET_LIB = WYPlayBox.a
TARGET = WYPlayBoxDemo $(TARGET_LIB)

all: $(TARGET)

WYPlayBoxDemo: $(SRC)/WYPlayBoxDemo.cpp $(HEADERS) $(TARGET_LIB)
	@echo Building WYPlayBoxDemo...
	$(CC) $(CFLAGS) $(SRC)/WYPlayBoxDemo.cpp $(TARGET_LIB) $(LIBS) -o WYPlayBoxDemo

$(TARGET_LIB): $(OBJS)
	@echo Building PlayBox static library...
	ar rcs WYPlayBox.a $(OBJS)

WYPB_Player.o: $(SRC)/WYPB_Player.cpp $(HEADERS) 
	$(CC) $(CFLAGS) $(SRC)/WYPB_Player.cpp -c

WYPB_Event.o: $(SRC)/WYPB_Event.cpp $(HEADERS) 
	$(CC) $(CFLAGS) $(SRC)/WYPB_Event.cpp -c

WYPB_PlayerMgr.o: $(SRC)/WYPB_PlayerMgr.cpp $(HEADERS) 
	$(CC) $(CFLAGS) $(SRC)/WYPB_PlayerMgr.cpp -c

WYPB_EventMgr.o: $(SRC)/WYPB_EventMgr.cpp $(HEADERS) 
	$(CC) $(CFLAGS) $(SRC)/WYPB_EventMgr.cpp -c

WYPB_Logger.o: $(SRC)/WYPB_Logger.cpp $(HEADERS) 
	$(CC) $(CFLAGS) $(SRC)/WYPB_Logger.cpp -c

WYPB_IO.o: $(SRC)/WYPB_IO.cpp $(HEADERS) 
	$(CC) $(CFLAGS) $(SRC)/WYPB_IO.cpp -c

WYPB_Serialize.o: $(SRC)/WYPB_Serialize.cpp $(HEADERS) 
	$(CC) $(CFLAGS) $(SRC)/WYPB_Serialize.cpp -c

clean:
	rm -rf *.o

distclean: clean
	rm -f $(TARGET)
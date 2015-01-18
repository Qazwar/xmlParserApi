###############
## Makefile
###############

STATIC_LIB=../lib/libMessageApi.a
DYNAMIC_LIB=../lib/libMessageApi.so
BIN=../bin/xmlMessageApiTest

##ARCH = $(shell uname -m)	# ARCH becomes the output from the uname -m command.
CXX=/usr/bin/g++
CXXFLAGS=-g -O2 -fPIC -std=c++11 -Wall -march=native -mtune=native -DOF_USING_GTK -pthread -D_REENTRANT $(INCS)
BOOST_ROOT=/home/dev/boost
OF_INCLUDE_ROOT=/home/dev/Downloads/of_v0.8.4_linux64_release/libs/openFrameworks
OF_EXTRA_INCLUDE_ROOT=/home/dev/Downloads/of_v0.8.4_linux64_release/libs

SRCS= XmlParser.cpp XmlNode.cpp
MAIN_SRC= MessageTest.cpp

OBJS = $(patsubst %.cpp, %.o, $(SRCS))
MAIN_OBJ = $(patsubst %.cpp, %.o, $(MAIN_SRC))

INCS = -I../include \
       -I$(BOOST_ROOT)/include \

LIBS = \
        $(BOOST_ROOT)/lib/libboost_thread.a \
	$(BOOST_ROOT)/lib/libboost_system.a \
	
$(STATIC_LIB): $(OBJS)
	ar rcs $@ $^
	
$(DYNAMIC_LIB): $(OBJS)
	$(CXX) -o $(DYNAMIC_LIB) $(OBJS) -shared

$(BIN): $(OBJS) $(MAIN_OBJ)
	$(CXX) -o $(BIN) $(OBJS) $(MAIN_OBJ) $(LIBS)

all: $(STATIC_LIB) $(DYNAMIC_LIB) $(BIN)
	
run:
	@echo "----------------------------"
	@echo "Running the programme. "
	@echo "----------------------------"
	$(BIN)
	@echo "----------------------------"

clean:
	rm -rf $(STATIC_LIB) $(DYNAMIC_LIB) $(BIN) *.o

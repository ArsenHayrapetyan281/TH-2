CC = g++
CFLAGS = -std=c++11 -Wall -pthread
LDFLAGS = -pthread

LIBRARY_NAME = libparallel_scheduler.so
DEMO_APP = demo-application

SRCS = parallel_scheduler.cpp demo_application.cpp
OBJS = parallel_scheduler.o demo_application.o

all: $(DEMO_APP)

$(DEMO_APP): $(OBJS) $(LIBRARY_NAME)
	$(CC) $(OBJS) -o $(DEMO_APP) -L. -lparallel_scheduler $(LDFLAGS)

$(LIBRARY_NAME): parallel_scheduler.o
	$(CC) -shared parallel_scheduler.o -o $(LIBRARY_NAME)

parallel_scheduler.o: parallel_scheduler.cpp
	$(CC) -fPIC $(CFLAGS) -c parallel_scheduler.cpp -o parallel_scheduler.o

demo_application.o: demo_application.cpp
	$(CC) $(CFLAGS) -c demo_application.cpp -o demo_application.o

clean:
	rm -f *.o $(LIBRARY_NAME) $(DEMO_APP)


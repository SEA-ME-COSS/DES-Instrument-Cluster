all: add-server_execution

%.o: %.c
		gcc -Wall -c $< `pkg-config --cflags dbus-1`

add-server_execution: add-server.o
		gcc add-server.o -o add-server_execution `pkg-config --libs dbus-1`

.PHONY: clean
clean:
		rm *.o add-server_execution

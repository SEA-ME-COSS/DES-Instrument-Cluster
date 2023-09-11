all: add-client_execution

%.o: %.c
		gcc -Wall -c $< `pkg-config --cflags dbus-1`

add-client_execution: add-client.o
		gcc add-client.o -o add-client_execution `pkg-config --libs dbus-1`

.PHONY: clean
clean:
		rm *.o add-client_execution

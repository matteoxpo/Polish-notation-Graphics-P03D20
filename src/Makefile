CC =gcc
CFLAGS = -Wall -Werror -Wextra -c

SOURCE = graph.c parsing.c matrix.c stack.c
OBJECTS = $(SOURCE:.c=.o)
EXECUTABLE = ../build/graph

all: $(OBJECTS)
	$(CC) $(OBJECTS)  -o $(EXECUTABLE)

rebuild: clean all

.o: .c
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(EXECUTABLE)
	-rm *.o

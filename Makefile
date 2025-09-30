CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC_COMMON = src/allocator.c src/heap.c src/utils.c

# Targets
TARGET1 = allocator_test
TARGET2 = frag_test
TARGET3 = perf_test

TEST1 = tests/test_allocator.c
TEST2 = tests/frag_test.c
TEST3 = tests/perf_test.c

OBJ1 = $(SRC_COMMON:.c=.o) $(TEST1:.c=.o)
OBJ2 = $(SRC_COMMON:.c=.o) $(TEST2:.c=.o)
OBJ3 = $(SRC_COMMON:.c=.o) $(TEST3:.c=.o)

all: $(TARGET1) $(TARGET2) $(TARGET3)

$(TARGET1): $(OBJ1)
	$(CC) $(CFLAGS) -o $@ $(OBJ1)

$(TARGET2): $(OBJ2)
	$(CC) $(CFLAGS) -o $@ $(OBJ2)

$(TARGET3): $(OBJ3)
	$(CC) $(CFLAGS) -o $@ $(OBJ3)

clean:
	rm -f src/*.o tests/*.o $(TARGET1) $(TARGET2) $(TARGET3)

test: $(TARGET1)
	./$(TARGET1)

frag: $(TARGET2)
	./$(TARGET2)

perf: $(TARGET3)
	./$(TARGET3)


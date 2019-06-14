CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o my_string.o generic_vector.o avl_tree.o
TEST_OBJECTS = unit_test.o test_def.o my_string.o

game: $(OBJECTS)
	$(CC) $(CFLAGS) -o game $(OBJECTS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

my_string.o: my_string.c
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o

generic_vector.o: generic_vector.c
	$(CC) $(CFLAGS) -c generic_vector.c -o generic_vector.o

avl_tree.o: avl_tree.c
	$(CC) $(CFLAGS) -c avl_tree.c -o avl_tree.o

unit_test: my_string.o unit_test.o test_def.o
	$(CC) $(CFLAGS) -o unit_test unit_test.o test_def.o my_string.o

unit_test.o: unit_test.c
	$(CC) $(CFLAGS) -c unit_test.c -o unit_test.o

test_def.o: test_def.c
	$(CC) $(CFLAGS) -c test_def.c -o test_def.o

clean:
	rm game $(OBJECTS) $(TEST_OBJECTS)

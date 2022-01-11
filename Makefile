all: helper.o
	gcc example_1.c helper.o -lm -o example_1
	gcc example_2.c helper.o -lm -o example_2
	gcc example_3.c helper.o -lm -o example_3

helper.o: helper.c
	gcc helper.c -c -o helper.o

clean:
	rm -f example_1 example_2 example_3 helper.o

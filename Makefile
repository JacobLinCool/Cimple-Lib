all: 
	gcc example_1.c -lm -o example_1
	gcc example_2.c -lm -o example_2
	gcc example_3.c -lm -o example_3
	gcc example_4.c -lm -o example_4

clean:
	rm -f example_1 example_2 example_3 example_4

all:
		gcc main.c task.c tasklist.c -I. -o main

run: all
	 ./main

clean:
		rm main

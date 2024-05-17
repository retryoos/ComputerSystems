FLAGS = -Wall -Werror -std=c99

all: fp_analyzer_f fp_analyzer_d

fp_analyzer_d: fp_analyzer.c main.c
		gcc $(FLAGS) -D DOUBLE fp_analyzer.c main.c -o fp_analyzer_d

fp_analyzer_f: fp_analyzer.c main.c
		gcc $(FLAGS) main.c fp_analyzer.c -o fp_analyzer_f

clean:
		rm -f fp_analyzer_d fp_analyzer_f
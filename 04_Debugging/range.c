#include <stdio.h>
#include <stdlib.h>

char help_info[] = "простейшая программа-генератор арифметической прогрессии range.c, принимающая от одного до трёх параметров по аналогии с питоновским range()\n\
\n\
Без параметров — выводит help \n\
С одним параметром N — выводит в столбик последовательность [0, 1, … N-1] \n\
С двумя — M, N — последовательность [M, M+1, … N-1] \n\
С тремя — M, N, S — последовательность [M, M+S, M+2S, … N-1]";

int main(int argc, char** argv) {
	long start = 0, stop, step = 1, count = 0;
	switch(argc) {
		case 1:
			printf("%s\n", help_info);
			break;
		case 2:
			stop = strtol(argv[1], NULL, 10);
			for (int i = start; i < stop; i += step) {
				count++;
				printf("%d\n", i);
			}
			break;
		case 3:
			start = strtol(argv[1], NULL, 10);
			stop = strtol(argv[2], NULL, 10);
			for (int i = start; i < stop; i += step) {
				count++;
				printf("%d\n", i);
			}
			break;
		case 4:
			start = strtol(argv[1], NULL, 10);
			stop = strtol(argv[2], NULL, 10);
			step = strtol(argv[3], NULL, 10);
			for (int i = start; i < stop; i += step) {
				count++;
				printf("%d\n", i);
			}
			break;
	};
}
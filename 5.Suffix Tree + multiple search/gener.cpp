#include <iostream>

int main(int argc, char* argv[]) {

	FILE *f = fopen(argv[1], "w");
	
	for (int i = 0; i < 25000; i++) {
		fprintf(f, "aabaabaabc");
	}
	fprintf(f, "\naab\n");
	fclose(f);
}



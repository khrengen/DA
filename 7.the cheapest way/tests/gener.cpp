#include<iostream>



	int main(int argc, char *argv[]){
	int a,a1,a2,a3,a4,a5,a6,b,c,d,g;


	FILE *in = fopen(argv[1], "w");

	fprintf(in, "2500 2500\n");
	for(int i = 0; i < 6250000; i++){
		srand(i + 7);
		a = rand() % 1000;/*
		a1 = rand() % 100;
		a2 = rand() % 100;
		a3 = rand() % 100;
		a4 = rand() % 100;
		a5 = rand() % 100;
		a6 = rand() % 100;
		b = rand() % 100;
		c = rand() % 100;
		d = rand() % 100;
		fprintf(in, "%d %d %d %d %d %d %d %d %d %d", a,a1,a2,a3,a4,a5,a6,b,c,d);
		*/
		fprintf(in, "%d ", a);
		
	}
	

	fclose(in);
	return 0;
}
#include<iostream>



	int main(int argc, char *argv[]){
	int a,a1,a2,a3,a4,a5,a6,b,c,d,g;


	FILE *in = fopen(argv[1], "w");

	fprintf(in, "50000 50000\n");
	for(int i = 0; i < 50000; i++){
		srand(i * 1439);
		a = rand() % 50000;
		a1 = rand() % 50000;/*
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
		fprintf(in, "%d %d\n", a, a1);
		
	}
	

	fclose(in);
	return 0;
}
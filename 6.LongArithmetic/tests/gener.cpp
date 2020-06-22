#include<iostream>



	int main(int argc, char *argv[]){
	int a,a1,a2,a3,a4,a5,a6,b,c,d,g;


	FILE *in = fopen(argv[1], "w");

	
	//for(int i = 0; i < 100; i++){
	//	srand(i*2);
		/*a = rand();
		a1 = rand();
		a2 = rand();
		a3 = rand();
		a4 = rand();
		a5 = rand();
		a6 = rand();
		b = rand();
		c = rand();
		g = rand()%1000000;
		d = rand();
		
		fprintf(in, "8888888888\n");
		fprintf(in, "+\n");
	}
*/
	for (int i = 0; i < 2500; i++) {
		fprintf(in, "9999999999");
	}
	fprintf(in, "\n");
	for (int i = 0; i < 2500; i++) {
		fprintf(in, "8888888888");
	}
	fprintf(in, "\n");
	fprintf(in, "+\n");
	fclose(in);
	return 0;
}
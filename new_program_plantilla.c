/* */
#include <stdio.h>

void esperarIntro(void);


int main(void){	

	esperarIntro();
	return 0;
}

void esperarIntro(void){
	fflush(stdin);
	puts("\n\nPulsar Intro para continuar...");
	getchar();
}	

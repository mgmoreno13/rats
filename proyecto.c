#include <math.h>
#include <stdio.h>
#include "memo.h"
#include "cut.h"


int main ( ) {
	srand (time(NULL));
	
	
	for(int j =1; j<=21; j++){                 //RECORRE LOS ARCHIVOS
	
		genetico(j);

	}
		

}

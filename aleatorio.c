#include "cut.h"
#include "memo.h"


void randpto1(random* rd,imagen* obj){
	time_t t;
	srand((unsigned) time(&t));	
	int r=0,i=0,b=0;
	//printf("antes pto 1 %d %d \n",obj->p1[0],obj->p1[1]);
	rd->r=0;

	while(i==0){

		do{
			b=0;
			rd->r=rand()%(20);
			
			//printf("\n1filas %d >> %d col %d >> %d \n",obj->p1[0]+rd->r,obj->rfil,obj->p1[1]+rd->r,obj->rcol);

			if((obj->p1[0]+rd->r)>=obj->rfil)b=1;
			if((obj->p1[0]+rd->r)<=0)b=1;

		}while(b==1);
	
		if(obj->rec[obj->p1[0]+rd->r][obj->p1[1]]==255){		
			obj->p1[0]=obj->p1[0]+rd->r;
			
			i++;
		}		

	}
	
	//printf("nuevo pto 1 %d %d \n",obj->p1[0],obj->p1[1]);
	
}

void randpto2(random* rd,imagen* obj){
	time_t t;
	srand((unsigned) time(&t));	
	int r=0,i=0,b=0;
	rd->r=0;

	while(i==0){

		do{
			b=0;
			rd->r=rand()%(20);
			


			if((obj->p2[0]+rd->r)>=obj->rfil)b=1;
			if((obj->p2[1]+rd->r)>=obj->rfil)b=1;
			if((obj->p2[0]+rd->r)<=0)b=1;
			if((obj->p2[1]+rd->r)<=0)b=1;
		}while(b==1);

		if(obj->rec[obj->p2[0]+rd->r][obj->p2[1]+rd->r]==255){		
			obj->p2[0]=obj->p2[0]+rd->r;
			obj->p2[1]=obj->p2[1]+rd->r;
			i++;
		}		

	}
	
}


void randpto3(random* rd,imagen* obj){
	time_t t;
	srand((unsigned) time(&t));	
	int r=0,i=0,b=0;
	rd->r=0;

	while(i==0){

		do{
			b=0;
			rd->r=rand()%(10);
			
			if((obj->p3[0]+rd->r)>=obj->rfil)b=1;
			if((obj->p3[1]-rd->r)>=obj->rfil)b=1;
			if((obj->p3[0]+rd->r)<=0)b=1;
			if((obj->p3[1]-rd->r)<=0)b=1;
		}while(b==1);

		if(obj->rec[obj->p3[0]+rd->r][obj->p3[1]-rd->r]==255){		
			obj->p3[0]=obj->p3[0]+rd->r;
			obj->p3[1]=obj->p3[1]-rd->r;
			i++;
		}		

	}
	
}
void randpto4(random* rd,imagen* obj){
	time_t t;
	srand((unsigned) time(&t));	
	int r=0,i=0,b=0;
	rd->r=0;

	while(i==0){

		do{
			b=0;
			rd->r=-10+rand()%(10+1+10);
		

			if((obj->p4[0]+rd->r)>=obj->rfil)b=1;
			if((obj->p4[1]+rd->r)>=obj->rfil)b=1;
			if((obj->p4[0]+rd->r)<=0)b=1;
			if((obj->p4[1]+rd->r)<=0)b=1;
		}while(b==1);
	
		if(obj->rec[obj->p4[0]+rd->r][obj->p4[1]+rd->r]==255){		
			obj->p4[0]=obj->p4[0]+rd->r;
			obj->p4[1]=obj->p4[1]+rd->r;
			i++;
		}		

	}
	
}

void randpto5(random* rd,imagen* obj){
	
	int r=0,i=0,b=0;
	rd->r=0;

	while(i==0){

		do{
			b=0;
			rd->r=rand()%(10);


			if((obj->p5[0]-rd->r)>=obj->rfil)b=1;
			//if((obj->p5[1]-rd->r)>=obj->rfil)b=1;
			if((obj->p5[0]-rd->r)<=0)b=1;
			//if((obj->p5[1]-rd->r)<=0)b=1;
		}while(b==1);

		if(obj->rec[obj->p5[0]-rd->r][obj->p5[1]]==255){		
						
			obj->p5[0]=obj->p5[0]-rd->r;

			i++;
		}	


	}
}
void randw(random* rd){
	//time_t t;
	//srand((unsigned) time(&t));
	//rd->w=0;

	rd->w=5+rand()%(10+1-5);
}

void refill(imagen* obj,random* rd){//genera matriz con esqueleltización y ancho w

	rd->fill=createMatrixint(obj->rfil,obj->rcol);	
		if(fabs(obj->penA)<1){
			for (int i =obj->p1[0]; i<obj->p2[0]; i++) //columnas
					for(int j=-rd->w;j<=rd->w;j++){
						if(i+j>=obj->rfil||i+j<=0){	
							continue;
						}else{
							rd->fill[i+j][obj->rectaA[i]]=150;
						}
					}
		}else{ for ( int j=obj->p2[1]; j<obj->p1[1]; j++) //columnas
					for(int i=-rd->w;i<=rd->w;i++)	
						if(i+j>=obj->rcol||i+j<=0){
							continue;
						}else{
							rd->fill[obj->rectaA[j]][j+i]=150;						
						}
		}
		if(fabs(obj->penB)<1){
			for ( int i =obj->p2[0]; i<obj->p3[0]; i++) //iterando filas
					for(int j=-rd->w;j<=rd->w;j++)	
						if(i+j>=obj->rfil||i+j<=0){	
							continue;
						}else{
							rd->fill[i+j][obj->rectaB[i]]=150;
						}
		}else{ for ( int j=obj->p2[1]; j<obj->p3[1]; j++) //iterando columnas
					for(int i=-rd->w;i<=rd->w;i++)	
						if(i+j>=obj->rcol||i+j<=0){
							continue;
						}else{
							rd->fill[obj->rectaB[j]][j+i]=150;						
						}
		}
		if(fabs(obj->penC)<1){
				for ( int i =obj->p3[0]; i<obj->p4[0]; i++) //iterando filas
					for(int j=-rd->w;j<=rd->w;j++)	
						if(i+j>=obj->rfil||i+j<=0){	
							continue;
						}else{
							rd->fill[i+j][obj->rectaC[i]]=150;
						}
		}else{ for ( int j=obj->p4[1]; j<obj->p3[1]; j++){ //iterando columnas
					for(int i=-rd->w;i<=rd->w;i++)	
						if(i+j>=obj->rcol||i+j<=0){
							continue;
						}else{
							
							rd->fill[obj->rectaC[j]][j+i]=150;						
						}//obtengo filas//obtengo filas				
				}
		}
		if(fabs(obj->penD)<1){
			for ( int i =obj->p4[0]; i<obj->p5[0]; i++) //iterando filas
					for(int j=-rd->w;j<=rd->w;j++)	
						if(i+j>=obj->rfil||i+j<=0){	
							continue;
						}else{
							rd->fill[i+j][obj->rectaD[i]]=150;
						}
		}else{ for ( int j=obj->p4[1]; j<obj->p5[1]; j++)//iterando columnas
					for(int i=-rd->w;i<=rd->w;i++)	
						if(i+j>=obj->rcol||i+j<=0){
							continue;
						}else{
							rd->fill[obj->rectaD[j]][j+i]=150;						
						}//obtengo filas
		}





}

void printRefill(imagen* obj,random* rd,FILE* out){

	int a=rd->w/3;
	for ( int i=obj->p1[0]-a; i<=obj->p1[0]+a; i++){ //renglones y
   		for ( int j=obj->p1[1]-a; j<=obj->p1[1]+a; j++){ 
			if(i>=obj->rfil||i<=0)continue;
			if(j>=obj->rcol||j<=0)continue;
				rd->fill[i][j]=150;		
		
		}
	}
	for ( int i=obj->p2[0]-a; i<=obj->p2[0]+a; i++){ //renglones y
   		for ( int j=obj->p2[1]-a; j<=obj->p2[1]+a; j++){ 
			if(i>=obj->rfil||i<=0)continue;
			if(j>=obj->rcol||j<=0)continue;
				rd->fill[i][j]=150;		
		
		}
	}

	for ( int i=obj->p3[0]-a; i<=obj->p3[0]+a; i++){ //renglones y
   		for ( int j=obj->p3[1]-a; j<=obj->p3[1]+a; j++){ 
			if(i>=obj->rfil||i<=0)continue;
			if(j>=obj->rcol||j<=0)continue;
				rd->fill[i][j]=150;		
		
		}
	}
	for ( int i=obj->p3[0]-a; i<=obj->p3[0]+a; i++){ //renglones y
   		for ( int j=obj->p3[1]-a; j<=obj->p3[1]+a; j++){ 
			if(i>=obj->rfil||i<=0)continue;
			if(j>=obj->rcol||j<=0)continue;
				rd->fill[i][j]=150;		
		
		}
	}
	for ( int i=obj->p4[0]-a; i<=obj->p4[0]+a; i++){ //renglones y
   		for ( int j=obj->p4[1]-a; j<=obj->p4[1]+a; j++){ 
			if(i>=obj->rfil||i<=0)continue;
			if(j>=obj->rcol||j<=0)continue;
				rd->fill[i][j]=150;		
		
		}
	}
	for ( int i=obj->p5[0]-a; i<=obj->p5[0]+a; i++){ //renglones y
   		for ( int j=obj->p5[1]-a; j<=obj->p5[1]+a; j++){ 
			if(i>=obj->rfil||i<=0)continue;
			if(j>=obj->rcol||j<=0)continue;
				rd->fill[i][j]=150	;	
		
		}
	}




	fprintf(out,"%s\n",obj->str) ;
	fprintf(out,"%d %d\n%d\n",obj->rcol,obj->rfil,obj->ngrises) ;

		for ( int i =0; i<obj->rfil; i++) //renglones y
    		for ( int j =0; j<obj->rcol; j++) //columnas x
				fprintf(out," %d ",rd->fill[i][j]);

}



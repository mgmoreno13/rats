#include "cut.h"
#include "memo.h"



void genetico(int j){
	
	FILE *in,*esq,*aprox,*fill;
	char archivo[100],entrada[100]="",entrada1[100]="",entrada2[100]="",entrada3[100]="";
	int i=0;
	strcpy(entrada1,"frame");
	strcpy(entrada2,"esq");
	strcpy(entrada3,"fill");	
	imagen* obj=(imagen*)malloc(sizeof(imagen));
	random* rd=(random*)malloc(sizeof(random));
	metrica* m=(metrica*)malloc(sizeof(metrica));	
	individuo ind[6];//arreglo de individuos en la poblacion
	mejor mej[1];
	sprintf(entrada, "%s_%d.pgm",entrada1,j);

   	in=fopen(entrada, "r");
	leerimagen(in,obj);
	recortar(obj,j);	
	generatePob(obj,rd,ind,m);//generando poblacion 

	do{

		insertion_sort(ind,6);//asgina a cada individuo su posicion de mayor a menor según la metrica

		seleccionCruce(ind);//seleccion cruce y reemplazo del peor
		
		evaluar(ind,obj,rd,m);//calcula metrica de nueva poblacion (incluye al hijo) y sale sin ordenar

		best(ind,mej);
		//printf("Generación i %d",i);
		i++;

	}while(mej[0].fitness!=1&&i<20);

	printf("\nMEJOR INDIVIDUO frame %d \np1 (fila %d col %d) \np2 (fila %d  col %d) \np3 (fila %d  col %d)   \np4 (fila %d  col %d) \np5 (fila %d  col %d)  \nfitness %lf \nw(ancho) %d \n",j,mej[0].p1[0],mej[0].p1[1],mej[0].p2[0],mej[0].p2[1],mej[0].p3[0],mej[0].p3[1], mej[0].p4[0],mej[0].p4[1],mej[0].p5[0],mej[0].p5[1],mej[0].fitness,mej[0].w);

	esqbest(obj,mej,rd);//pasando el mejor al objeto

	sprintf(entrada, "%s_%d.pgm",entrada2,j);
	esq=fopen(entrada,"w");
	esqueleto(obj,esq);//solo imprimira al mejor
	angleLength(obj,j);
	sprintf(entrada, "%s_%d.pgm",entrada3,j);
	fill=fopen(entrada,"w");
	printRefill(obj,rd,fill);
	

	fclose(in);
	fclose(esq);
	fclose(fill);
	freeOBJ(obj);
	free(obj);
	freeRD(rd);
	free(rd);
	free(m);





}


void generatePob(imagen* obj, random* rd,individuo *ind,metrica* m){

	for(int i=0;i<6;i++){
		randpto1(rd,obj);
		ind[i].p1[0]=obj->p1[0];
		ind[i].p1[1]=obj->p1[1];
		randpto2(rd,obj);	
		ind[i].p2[0]=obj->p2[0];
		ind[i].p2[1]=obj->p2[1];
		randpto3(rd,obj);
		ind[i].p3[0]=obj->p3[0];
		ind[i].p3[1]=obj->p3[1];
		randpto4(rd,obj);
		ind[i].p4[0]=obj->p4[0];
		ind[i].p4[1]=obj->p4[1];
		randpto5(rd,obj);
		ind[i].p5[0]=obj->p5[0];
		ind[i].p5[1]=obj->p5[1];
		randw(rd);
		ind[i].w=rd->w;
		graficaA(obj);
		graficaB(obj);
		graficaC(obj);
		graficaD(obj);	
		refill(obj,rd);
		params(obj,rd,m);
		accuracy(m);
		ind[i].fitness=m->accur;
		ind[i].pos=i;
	}
}

void seleccionCruce(individuo* ind){

	int mejor,sec,n,peor,a,b,c,d,e,f,i;
	//seleccionando	a mejor y segundo mejor (padres) //conocida como seleccion uniforme
	mejor=0;//el individuo en la posicion 0 es el de mejor fitness
	sec=1;
	peor=5;//como está ordenado de mayor fitness a menor la 5 es la peor
	n=1+rand()%(3+1-1);//cruce por punto

	switch(n)
	{
		case 1://reemplaza solo un gen
			a=mejor;b=sec;c=sec;d=sec;e=sec;f=sec;
		break;
		case 2://reemplaza dos genes
			a=mejor;b=mejor;c=sec;d=sec;e=sec;f=sec;
		break;
		case 3://reemplaza tres genes
		    a=mejor;b=mejor;c=mejor;d=sec;e=sec;f=sec;
		break;
		
	}//genes: p1 p2 p3 p4 p5 y w (ancho)

		ind[peor].p1[0]=ind[a].p1[0];

		ind[peor].p1[1]=ind[a].p1[1];

		ind[peor].p2[0]=ind[b].p2[0];
		ind[peor].p2[1]=ind[b].p2[1];
		ind[peor].p3[0]=ind[c].p3[0];
		ind[peor].p3[1]=ind[c].p3[1];
		ind[peor].p4[0]=ind[d].p4[0];
		ind[peor].p4[1]=ind[d].p4[1];
		ind[peor].p5[0]=ind[e].p5[0];
		ind[peor].p5[1]=ind[e].p5[1];
		ind[peor].w=ind[f].w;
		i=peor;		
	
}

void evaluar(individuo *ind,imagen* obj,random* rd,metrica* m){
	for(int i=0;i<6;i++){
		obj->p1[0]=ind[i].p1[0];
		obj->p1[1]=ind[i].p1[1];
	
		obj->p2[0]=ind[i].p2[0];
		obj->p2[1]=ind[i].p2[1];

		obj->p3[0]=ind[i].p3[0];
		obj->p3[1]=ind[i].p3[1];

		obj->p4[0]=ind[i].p4[0];
		obj->p4[1]=ind[i].p4[1];

		obj->p5[0]=ind[i].p5[0];
		obj->p5[1]=ind[i].p5[1];

		rd->w=ind[i].w;
		
		graficaA(obj);
		graficaB(obj);
		graficaC(obj);
		graficaD(obj);	
		refill(obj,rd);
		params(obj,rd,m);
		accuracy(m);
		ind[i].fitness=m->accur;
		ind[i].pos=i;
	
	}
}

void best(individuo *ind,mejor *mej){


	mej[0].p1[0]=ind[0].p1[0];
	mej[0].p1[1]=ind[0].p1[1];
	mej[0].p2[0]=ind[0].p2[0];
	mej[0].p2[1]=ind[0].p2[1];
	mej[0].p3[0]=ind[0].p3[0];
	mej[0].p3[1]=ind[0].p3[1];
	mej[0].p4[0]=ind[0].p4[0];
	mej[0].p4[1]=ind[0].p4[1];
	mej[0].p5[0]=ind[0].p5[0];
	mej[0].p5[1]=ind[0].p5[1];
	mej[0].w=ind[0].w;
	mej[0].fitness=ind[0].fitness;


}

void esqbest(imagen* obj,mejor *mej,random *rd){

	obj->p1[0]=mej[0].p1[0];
	obj->p1[1]=mej[0].p1[1];
	obj->p2[0]=mej[0].p2[0];
	obj->p2[1]=mej[0].p2[1];
	obj->p3[0]=mej[0].p3[0];
	obj->p3[1]=mej[0].p3[1];
	obj->p4[0]=mej[0].p4[0];
	obj->p4[1]=mej[0].p4[1];
	obj->p5[0]=mej[0].p5[0];
	obj->p5[1]=mej[0].p5[1];
	rd->w=mej[0].w;


}

void angleLength(imagen* obj,int j){
	FILE* ANGULOS,*LONGITUDES;

	obj->L1=pow(pow(obj->p1[0]-obj->p2[0],2)+pow(obj->p1[1]-obj->p2[1],2),0.5);
	obj->L2=pow(pow(obj->p2[0]-obj->p3[0],2)+pow(obj->p2[1]-obj->p3[1],2),0.5);
	obj->L3=pow(pow(obj->p3[0]-obj->p4[0],2)+pow(obj->p3[1]-obj->p4[1],2),0.5);
	obj->L4=pow(pow(obj->p4[0]-obj->p5[0],2)+pow(obj->p4[1]-obj->p5[1],2),0.5);
	printf("L1 %lf L2 %lf L3 %lf L4 %lf ",obj->L1,obj->L2,obj->L3,obj->L4);
	LONGITUDES=fopen("LONGITUDES.txt","a");	
	fprintf(LONGITUDES,"%d %lf %lf %lf %lf \n",j,obj->L1,obj->L2,obj->L3,obj->L4);
	obj->A1=atan(-1/obj->penA);
	obj->A2=atan(-1/obj->penB);
	obj->A3=atan(-1/obj->penC);
	obj->A4=atan(-1/obj->penD);
	ANGULOS=fopen("ANGULOS.txt","a");

	fprintf(ANGULOS,"%d %lf %lf %lf %lf \n",j,obj->A1,obj->A2,obj->A3,obj->A4);

	printf("\nA1 %lf A2 %lf A3 %lf A4 %lf ",obj->A1,obj->A2,obj->A3,obj->A4);

	fclose(ANGULOS);
	fclose(LONGITUDES);


}


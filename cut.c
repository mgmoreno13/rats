 #include "cut.h"


void imprimir(FILE* out,imagen* obj){
	fprintf(out,"%s\n",obj->str) ;
	fprintf(out ,"%d %d\n%d\n",obj->rcol,obj->rfil,obj->ngrises) ;
	//printf("sup col%d  inf col %d  sup fil %d inf fil%d %d \n",obj->p5[1],obj->p1[1],obj->p5[0],obj->p1[0],0) ;
	
	for ( int i =0; i<obj->rfil; i++){ //renglones y
		
    		for ( int j =0; j<obj->rcol; j++){ //columnas
			
				fprintf(out," %d ",obj->rec[i][j]);	
		}
	}

	//findPto3(obj);
}
void imprimirRecta1(FILE* out,imagen* obj){

	fprintf(out,"%s\n",obj->str) ;
	fprintf(out ,"%d %d\n%d\n",obj->rcol,obj->rfil,obj->ngrises) ;
	//printf("sup col%d  inf col %d  sup fil %d inf fil%d %d \n",obj->p5[1],obj->p1[1],obj->p5[0],obj->p1[0],0) ;
	graficarRecta1(obj->p5[1],obj->p1[1],obj->p5[0],obj->p1[0],obj->penrect1,obj);//devuelve vector con recta entre p1 y p5
	//printf("%d",obj->vx[4]);
	for ( int i =0; i<obj->rfil; i++){ //renglones y
		
    		for ( int j =0; j<obj->rcol; j++){ //columnas
			if(j==obj->recta1[i]){
				fprintf(out," %d ",150);
			}else{
				fprintf(out," %d ",obj->rec[i][j]);
			}	
		}
	}
	//printf("\nPENDIENTE RECTA 1                                %lf",obj->penrect1);
	
}
void imprimirRecta2(FILE* out,imagen* obj){

	fprintf(out,"%s\n",obj->str) ;
	fprintf(out ,"%d %d\n%d\n",obj->rcol,obj->rfil,obj->ngrises) ;
	//printf("RECTA 2 sup col%d  inf col %d  sup fil %d inf fil%d %d \n",obj->p3[1],obj->p1[1],obj->p3[0],obj->p1[0],0) ;
	graficarRecta2(obj->p3[1],obj->p1[1],obj->p3[0],obj->p1[0],obj->penrect2,obj);
	for ( int i =0; i<obj->rfil; i++){ //renglones y
    		for ( int j =0; j<obj->rcol; j++){ //columnas x
			//if(i<=obj->p3[0]&&i>=obj->p1[0]){	
				if(j==obj->recta2[i]&&i<=obj->p3[0]&&i>=obj->p1[0]){
					//printf("\nRECTA 2 i %d j %d vx %d\n",i,j,obj->recta2[i]);
					fprintf(out," %d ",110);
				
			}else{
					fprintf(out," %d ",obj->rec[i][j]);
				}	
			
		}
	}


}
void imprimirRecta3(FILE* out,imagen* obj){

	fprintf(out,"%s\n",obj->str) ;
	fprintf(out ,"%d %d\n%d\n",obj->rcol,obj->rfil,obj->ngrises) ;
	//printf("RECTA 3 sup col%d  inf col %d  sup fil %d inf fil%d %d \n",obj->p3[1],obj->p1[1],obj->p3[0],obj->p1[0],0) ;
	graficarRecta3(obj->p3[1],obj->p3[0],(-1/obj->penrect1),obj);
	for ( int i =0; i<obj->rfil; i++){ //renglones y
    		for ( int j =0; j<obj->rcol; j++){ //columnas x
				
				if(i==obj->recta3[j]&&j>=0&&j<=obj->p3[1]){
					
					//printf("\nRECTA 3 i %d j %d vy %d\n",i,j,obj->recta3[i]);
					fprintf(out," %d ",110);	
			}else{
					fprintf(out," %d ",obj->rec[i][j]);
				}	
			
		}
	}


}

void recortar(imagen* obj,int h){

	int k=0,l=0;
	FILE *out,*outrect,*outrect1,*outrect2,*outesq;
	char entrada[100],entrada1[100],entrada2[100],entrada3[100];
	strcpy(entrada1,"recor");
	sprintf(entrada, "%s_%d.pgm",entrada1,h);
	out=fopen(entrada, "w");
	strcpy(entrada1,"recor_rect1");
	sprintf(entrada2, "%s_%d.pgm",entrada1,h);
	outrect=fopen(entrada2, "w");
	strcpy(entrada1,"recor_rect2");
	sprintf(entrada2, "%s_%d.pgm",entrada1,h);
	outrect1=fopen(entrada2, "w");
	strcpy(entrada1,"recor_rect3");
	sprintf(entrada3, "%s_%d.pgm",entrada1,h);
	outrect2=fopen(entrada3, "w");


	obj->rfil=obj->inferior[0]-obj->superior[0];
	obj->rcol=obj->derecho[1]-obj->izquierdo[1];
	obj->rec=createMatrixint(obj->rfil+1,obj->rcol+1);

	obj->p1[0]=1;//filas
	obj->p1[1]=obj->superior[1]-obj->izquierdo[1];//columnas
	obj->p5[0]=obj->inferior[0]-obj->superior[0];//filas
	obj->p5[1]=obj->inferior[1]-obj->izquierdo[1];//columnas


	for ( int i =obj->superior[0]; i<obj->inferior[0] ; i++){ //renglones
		k=i-obj->superior[0];
		
    		for ( int j =obj->izquierdo[1]; j<obj->derecho[1]; j++){ //columnas
			l=j-obj->izquierdo[1];   		
			obj->rec[k][l]=obj->img[i][j];//imagen recortada
		}
	}

	imprimir(out,obj);
	imprimirRecta1(outrect,obj);
	findPtos(obj);
	findPto3(obj);
	imprimirRecta2(outrect1,obj);
	imprimirRecta3(outrect2,obj);
	findPto2y4(obj);
	//esqueleto(obj,outesq);
	obj->p1[0]=obj->p1[0]+10;
	obj->p2[1]=obj->p2[1]+10;
	obj->p3[1]=obj->p3[1]-10;
	obj->p4[1]=obj->p4[1]+10;
	obj->p5[0]=obj->p5[0]-5;
	fclose(out);
}

void leerimagen(FILE* in,imagen* obj){

	fscanf(in,"%s\n",obj->str) ;
	fscanf( in ,"%d %d\n",&obj->nc , &obj->nr ) ;
	fscanf( in , "%d\n" ,&obj->ngrises) ;
	//printf("str %s nr %d nc %d ngrises %d \n",obj->str,obj->nr,obj->nc,obj->ngrises);

	obj->img=createMatrixint(obj->nr,obj->nc) ;

	for ( int i =0; i<obj->nr ; i ++){ //renglones
    	for ( int j =0; j<obj->nc ; j ++){ //columnas
    		fscanf(in,"%d",&obj->img[i][j]);
		}
	}

	maxMin(obj);
}

void maxMin(imagen* obj){
int ban=0;
	for(int i=0;i<obj->nr;i++){
		for(int j=0;j<obj->nc;j++){
			if(obj->img[i][j]==255){
				obj->superior[0]=i;
				obj->superior[1]=j;
				ban=1;				
				break;
			}			
		}
		if(ban==1)break;
	}
	ban=0;
	for(int i=obj->nr-1;i>=0;i--){
		for(int j=0;j<obj->nc;j++){
			if(obj->img[i][j]==255){
			obj->inferior[0]=i;
			obj->inferior[1]=j;
				ban=1;				
				break;
			}			
		}
		if(ban==1)break;
	}
	ban=0;	
	for(int j=0;j<obj->nc;j++){
		for(int i=obj->superior[0];i<=obj->inferior[0];i++){

			if(obj->img[i][j]==255){
			obj->izquierdo[1]=j;
			obj->izquierdo[0]=i;
				ban=1;				
				break;
			}			
		}
		if(ban==1)break;
	}
	ban=0;
	for(int j=obj->nc-1;j>=0;j--){
		for(int i=obj->superior[0];i<obj->inferior[0];i++){
			if(obj->img[i][j]==255){
				obj->derecho[1]=j;
				obj->derecho[0]=i;
				ban=1;				
				break;
			}			
		}
		if(ban==1)break;
	}

}

void graficarRecta1(int x1,int x2, int y1, int y2,double pen,imagen* obj){

	//printf("graficar %d %d %d %d",x1,x2,y1,y2);
	obj->recta1=(int*)malloc(sizeof(int)*(obj->rfil));

	obj->penrect1=(y2-y1)/(double)(x2-x1);

	for(int i=0;i<obj->rfil;i++){
		//printf("\nI ES %d\n",i);
		obj->recta1[i]=(1/obj->penrect1)*(i-y1)+x1;

		//printf("%d %d \n ",i,obj->recta1[i]);
	}
	//printf("PENDIENTE RECTA 1 DENTRO DE FUNCION %lf",obj->penrect1);

	
}
void graficarRecta2(int x1,int x2, int y1, int y2,double pen,imagen* obj){

	//printf("graficar %d %d %d %d",x1,x2,y1,y2);
	obj->recta2=(int*)malloc(sizeof(int)*(obj->rfil));

	pen=(y2-y1)/(double)(x2-x1);

	for(int i=0;i<obj->rfil;i++){
		//printf("\nI ES %d\n",i);
		obj->recta2[i]=(1/pen)*(i-y1)+x1;

		//printf("RECTA 2 f %d col %d \n ",i,obj->recta2[i]);
	}

	
}

void graficarRecta3(int x1, int y1,double pen,imagen* obj){
//PERPENDICULAR
	obj->recta3=(int*)malloc(sizeof(int)*(obj->rcol));

	for(int i=0;i<obj->rcol;i++){//iterando x
		//printf("\nI ES %d\n",i);
		obj->recta3[i]=(pen)*(i-x1)+y1;

		//printf("RECTA 3 col %d fil %d \n ",i,obj->recta3[i]);
	}

	
}
void findPtos(imagen* obj){//busca puntos importantes pero NO los criticos
	int b=1,n=0;
	for (int i=1;i<obj->rfil;i++){ //renglones y | bajando por vector y
				
		//printf ("obj->rec[i][obj->recta1[i]] %d\n",obj->rec[i][obj->recta1[i]]);
		if(obj->rec[i][obj->recta1[i]]==0&&n==0){//buscar primer negro		
			
			n++;
			obj->p11[0]=i;
			obj->p11[1]=obj->recta1[i];
			b=0;
		}

		if(obj->rec[i][obj->recta1[i]]==255&&b==0){
			//printf("PRIMER BLANCO%d posicion en x de recta 1 %d renglon %d \n",obj->rec[i][obj->recta1[i]],obj->recta1[i],i);
			b++;			
			obj->p111[0]=i;
			obj->p111[1]=obj->recta1[i];
			n==0;			
		}

	}
	b=1,n=0;
	for (int i=obj->rfil-1;i>=1;i--){ //renglones y | subiendo por vector y
				
		if(obj->rec[i][obj->recta1[i]]==0&&n==0){//buscar primer negro		
		
			n++;
			obj->p55[0]=i;
			obj->p55[1]=obj->recta1[i];
			b=0;
		}

		if(obj->rec[i][obj->recta1[i]]==255&&b==0){
			//printf("PRIMER BLANCO%d posicion en x de recta 1 %d renglon %d \n",obj->rec[i][obj->recta1[i]],obj->recta1[i],i);
			b++;			
			obj->p555[0]=i;
			obj->p555[1]=obj->recta1[i];
			n==0;			
		}

	}		
}


void findPto3(imagen* obj){
	int valmax=0;
	for(int i=obj->p111[0];i<obj->p555[0];i++){//filas
		for(int j=obj->recta1[i];j<obj->rcol;j++){
			if(obj->rec[i][j]==255&&j>valmax){
				valmax=j;
				obj->p3[0]=i;
				obj->p3[1]=valmax;
			}
		}
	}
}

void findPto2y4(imagen* obj){

	int valmin=obj->rcol,valmin2=obj->rfil;//inicializado en el valor mas grande de columnas

	for(int i=0;i<obj->rfil;i++){//filas
		for(int j=0;j<obj->rcol;j++){
			
			if(obj->recta3[j]<=i)continue;
			//printf("FILAS RECTA 3 %d > i %d valor %d",obj->recta3[j],i,obj->rec[i][j]);
			if(obj->rec[i][j]==255&&j<valmin){
				valmin=j;
				obj->p2[0]=i;
				obj->p2[1]=valmin;
			}
		}
	}

	//printf("\nP2 fil %d col %d \n",obj->p2[0],obj->p2[1]);
	
	//valmin=obj->rcol;
	int max=0;

	for(int i=0;i<obj->rfil;i++)
		for(int j=0;j<obj->rcol;j++)
			if((obj->recta1[i]==j&&obj->recta3[j]==i)||(obj->recta1[i]==j+1&&obj->recta3[j]==i+1)){
				obj->interseccion[0]=i;
			}
	//printf("\nInterseccion %d obj->rfil %d \n",obj->interseccion[0],obj->rfil);



	for(int i=obj->rfil-1;i>=obj->interseccion[0];i--){//filas
		for(int j=0;j<obj->recta1[i];j++){	
				//printf("max, %d \n",max);
				//printf("obj->recta1[i] %d j %d",obj->recta1[i],j);
			if(obj->rec[i][j]==255&&abs(obj->recta1[i]-j)>max){
//printf("max %d rec %d",abs(obj->recta1[i]-j),obj->rec[i][j]);
				//printf("obj->recta1[i] %d j %d",obj->recta1[i],j);
				max=abs(obj->recta1[i]-j);
				obj->p4[0]=i;
				obj->p4[1]=j;
				//printf("p4[0] %d p4[1] %d \n",obj->p4[0],obj->p4[1]);
			}
			if(obj->rec[i][j]==255)break;
		
		}
	}


	//printf("\nP4 fil %d col %d \n",obj->p4[0],obj->p4[1]);
	//printf("\nP5 fil %d col %d \n",obj->p5[0],obj->p5[1]);

}
void esqueleto(imagen* obj,FILE* outesq){
	obj->esq=createMatrixint(obj->rfil,obj->rcol); 
	for ( int i =0; i<obj->rfil; i++) //renglones y
    		for ( int j =0; j<obj->rcol; j++) //columnas x
			obj->esq[i][j]=obj->rec[i][j];


	fprintf(outesq,"%s\n",obj->str) ;
	fprintf(outesq,"%d %d\n%d\n",obj->rcol,obj->rfil,obj->ngrises) ;
	
	graficaA(obj);//devuelve vector con recta entre p1 y p2
	graficaB(obj);//devuelve vector con recta entre p2 y p3
	graficaC(obj);//devuelve vector con recta entre p3 y p4
	graficaD(obj);//devuelve vector con recta entre p4 y p5


	//printf("obj->penA %lf\n",fabs(obj->penA));
		if(fabs(obj->penA)<1){

			for (int i =obj->p1[0]; i<obj->p2[0]; i++) //columnas
			obj->esq[i][obj->rectaA[i]]=150;
			
				
		}else{
		
			for ( int j=obj->p2[1]; j<obj->p1[1]; j++) //columnas
				obj->esq[obj->rectaA[j]][j]=150;
			

		}
	//printf("obj->penB %lf\n",fabs(obj->penB));
		if(fabs(obj->penB)<1){
			
			for ( int i =obj->p2[0]; i<obj->p3[0]; i++) //iterando filas
				obj->esq[i][obj->rectaB[i]]=150;
		}else{
			
			for ( int j=obj->p2[1]; j<obj->p3[1]; j++) //iterando columnas
				obj->esq[obj->rectaB[j]][j]=150;//obtengo filas
			

		}
	//printf("p3[0] %d obj->p3[1] %d obj->p4[0] %d obj->p4[1] %d\n",obj->p3[0],obj->p3[1],obj->p4[0],obj->p4[1]);
	//printf("obj->penC %lf\n",fabs(obj->penC));
		if(fabs(obj->penC)<1){
			
			for ( int i =obj->p3[0]; i<obj->p4[0]; i++) //iterando filas
				obj->esq[i][obj->rectaC[i]]=150;
		}else{
				
			for ( int j=obj->p4[1]; j<obj->p3[1]; j++){ //iterando columnas
				obj->esq[obj->rectaC[j]][j]=150;//obtengo filas
				//printf("fil rectaC es %d col j es %d",obj->rectaC[j],j);				
				}

		}

	//printf("obj->penD %lf\n",fabs(obj->penD));
		if(fabs(obj->penD)<1){
			
			for ( int i =obj->p4[0]; i<obj->p5[0]; i++) //iterando filas
				obj->esq[i][obj->rectaD[i]]=150;
		}else{
				
			//printf("obj->p4[1] %d obj->p5[1] %d %d",obj->p4[1],obj->p5[1],obj->rectaD[obj->p5[1]]);
			for ( int j=obj->p4[1]; j<obj->p5[1]; j++){ //iterando columnas
				obj->esq[obj->rectaD[j]][j]=150;//obtengo filas
			
				}
			

		}




		for ( int i =0; i<obj->rfil; i++) //renglones y
    		for ( int j =0; j<obj->rcol; j++) //columnas x
			fprintf(outesq," %d ",obj->esq[i][j]);
					
			
}

void graficaA(imagen* obj){
	obj->penA=(obj->p2[1]-obj->p1[1])/(double)(obj->p2[0]-obj->p1[0]);
	if(fabs(obj->penA)<1){
	
		obj->rectaA=(int*)malloc(sizeof(int)*(obj->rfil));

		for(int i=0;i<obj->rfil;i++)//iterando x
			obj->rectaA[i]=(obj->penA)*(i-obj->p1[0])+obj->p1[1];

	}else{
		obj->rectaA=(int*)malloc(sizeof(int)*(obj->rcol));

		for(int i=0;i<obj->rcol;i++)
			obj->rectaA[i]=(1/obj->penA)*(i-obj->p1[1])+obj->p1[0];
	}

	
}

void graficaB(imagen* obj){
	obj->penB=(obj->p3[1]-obj->p2[1])/(double)(obj->p3[0]-obj->p2[0]);
	if(fabs(obj->penB)<1){//GUARDANDO COLUMNAS
	
		obj->rectaB=(int*)malloc(sizeof(int)*(obj->rfil));

		for(int i=0;i<obj->rfil;i++)//iterando y
			obj->rectaB[i]=(obj->penB)*(i-obj->p2[0])+obj->p2[1];

	}else{//LLENANDO VECTOR CON FILAS
		obj->rectaB=(int*)malloc(sizeof(int)*(obj->rcol));

		for(int i=0;i<obj->rcol;i++)//iterando x
			obj->rectaB[i]=(1/obj->penB)*(i-obj->p2[1])+obj->p2[0];
	}

	
}
void graficaC(imagen* obj){
	obj->penC=(obj->p4[1]-obj->p3[1])/(double)(obj->p4[0]-obj->p3[0]);
	if(fabs(obj->penC)<1){
	
		obj->rectaC=(int*)malloc(sizeof(int)*(obj->rfil));

		for(int i=0;i<obj->rfil;i++)//iterando x
			obj->rectaC[i]=(obj->penC)*(i-obj->p3[0])+obj->p3[1];

	}else{
		obj->rectaC=(int*)malloc(sizeof(int)*(obj->rcol));

		for(int i=0;i<obj->rcol;i++){
			obj->rectaC[i]=(1/obj->penC)*(i-obj->p3[1])+obj->p3[0];
			//printf("i es %d obj->rectaC[i] es %d\n",i,obj->rectaC[i]);		
		}

	}
	
}
void graficaD(imagen* obj){
	
	obj->penD=(obj->p5[1]-obj->p4[1])/(double)(obj->p5[0]-obj->p4[0]);
	if(fabs(obj->penD)<1){

	//printf("ENTRO 2 ");
	
		obj->rectaD=(int*)malloc(sizeof(int)*(obj->rfil));

		for(int i=0;i<obj->rfil;i++)//iterando x
			obj->rectaD[i]=(obj->penD)*(i-obj->p4[0])+obj->p4[1];

	}else{
		//printf("ENTRO 1 ");
		obj->rectaD=(int*)malloc(sizeof(int)*(obj->rcol));

		for(int i=0;i<obj->rcol;i++){
			obj->rectaD[i]=(1/obj->penD)*(i-obj->p4[1])+obj->p4[0];
			//printf("obj->rectaD[%d] con fila %d\n",i,obj->rectaD[i]);
			}
	}

}





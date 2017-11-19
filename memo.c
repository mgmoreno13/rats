
#include "memo.h"
#include "cut.h"

int **createMatrixint(int nr, int nc) {
    int  i;
    int **mat;

    // Reservamos memoria
    mat= (int **) malloc( (nr)*sizeof(int *));
    if(mat==NULL) return(NULL);
    mat[0] = (int *)malloc(nr*nc*sizeof(int));
    if(mat[0]==NULL) return(NULL);
    for(i=1; i<nr; ++i) 
        mat[i] = mat[i-1] + nc;

	for(int i=0;i<nr;i++)
	for(int j=0;j<nc;j++)
		mat[i][j]=0;
    return(mat);
}

void freeOBJ(imagen* obj){

    free(obj->img[0]);
    free(obj->img);
    free(obj->rec[0]);
    free(obj->rec);
	free(obj->esq[0]);
    free(obj->esq);
	free(obj->recta1);
	free(obj->recta2);
	free(obj->recta3);
	free(obj->rectaA);
	free(obj->rectaB);
	free(obj->rectaC);
	free(obj->rectaD);
	for(int i=0;i<2;i++){	
		obj->superior[i]=0;
		obj->inferior[i]=0;
		obj->izquierdo[i]=0;
		obj->derecho[i]=0;
		obj->p1[i]=0;
		obj->p2[i]=0;
		obj->p11[i]=0;
		obj->p111[i]=0;
		obj->p5[i]=0;
		obj->p55[i]=0;
		obj->p555[i]=0;
		obj->p3[i]=0;
		obj->p4[i]=0;
		obj->rizq[i]=0;//punto donde se recorto por margen izquierda
		obj->rder[i]=0;
		obj->interseccion[i]=0;
	}
obj->penD=0;

}

void freeRD(random* rd){

	free(rd->fill[0]);
	free(rd->fill);
}




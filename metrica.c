#include "cut.h"
#include "memo.h"

void params(imagen* obj,random* rd,metrica* m){
	m->TP=0;
	m->FN=0;
	m->FP=0;
	m->TN=0;

	for(int i=0;i<obj->rfil;i++)
		for(int j=0;j<obj->rcol;j++) {

			if(obj->rec[i][j]==255&&rd->fill[i][j]==150)
				m->TP++;
			if(obj->rec[i][j]==255&&rd->fill[i][j]==0)
				m->FN++;
			if(obj->rec[i][j]==0&&rd->fill[i][j]==150)
				m->FP++;
			if(obj->rec[i][j]==0&&rd->fill[i][j]==0)
				m->TN++;
	}
}
void accuracy(metrica* m){

	m->accur=(m->TP+m->TN)/(double)(m->TP+m->TN+m->FP+m->FN);

}

void swap(individuo *e1,individuo *e2) 
{
  individuo tmp = *e1;
  *e1 = *e2;
  *e2 = tmp;
}

void insertion_sort(individuo* s,int n)
{
  int i,j;
  for (i=1; i<n+1; i++) {
    j=i;
    while ((j>0) && (s[j].fitness > s[j-1].fitness)) {
     	 swap(&s[j],&s[j-1]);
	  //swap(&s[j].pos,&s[j-1].pos);
      j = j-1;
    }
  }
}



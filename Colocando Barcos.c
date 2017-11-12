#include <stdio.h>
#include <stdlib.h>
#define max 1000

	typedef struct{
		int fila;
		int columna;
	}barco;
		
void cargar_posiciones(barco *P);
int distancia(barco pos[max], int x);

int main(int argc, char *argv[]) {
barco pos[max];
int i, x, dist = 0;

	do{
		scanf("%d", &x);
		for(i = 0; i < x; i++){
			cargar_posiciones(&pos[i]);
		}
		
		printf("%d\n", distancia(pos, x));
		
	}while(x!=0);
	
	return 0;
}

void cargar_posiciones(barco *P){
	scanf("%d %d", &P->fila, &P->columna);
}

int distancia(barco pos[max], int x){
	int j, k, distancia = 0;
	int f1, f2, c1, c2, st, fs, cs;
	
	for(j = 0; j < x; j++){
		for(k = 1; k < x;k++){
			f1 = pos[j].fila;
			f2 = pos[k].fila;
			fs = f1 - f2;
			if(fs < 0){
				fs = fs * -1;
			}
			c1 = pos[j].columna;
			c2 = pos[k].columna;
			cs = c1 - c2;
			if(cs < 0){
				cs = cs * -1;
			}
			
			st = fs + cs;
			if(distancia < st){
				distancia = st;
			}
		}
	}
	return (distancia);
}


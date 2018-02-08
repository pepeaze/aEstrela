
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

typedef struct no{
	char c;
	int lin,col;
	float f,g,h;
}no;

typedef struct Lista{
    no n;
    struct Lista *prox;
}lista;

/*PROTOTYPES*/
lista* inicializaLista();

no **allocMatrix (int l, int c);
void readMap (FILE *m, no **map, int l, int c);
void printMap(no **map, int l, int c);
void setF (no *node, no *ini, no *goal);
no* checkNeighbours(no **map, int l, int c, no *closed, no *open, int *viz);
int checkSmallerF (no *open, int tam);
/*END PROTOTYPES*/

int main(){
	no **map;
	int l,c;
	no ini, goal;
	FILE *m;
	m = fopen("map.txt", "r");
	fscanf(m, "%d %d\n", &l, &c);
	printf("Map Size: %d X %d\n", l,c);
	fscanf(m, "%d %d\n", &ini.lin, &ini.col);
	printf("Ini: %d X %d\n", ini.lin,ini.col);
	fscanf(m, "%d %d\n", &goal.lin, &goal.col);
	printf("Goal: %d X %d\n", goal.lin,goal.col);
	map = allocMatrix(l,c);
	readMap (m, map, l, c);
	printMap(map,l,c);
	findPath (map, l, c, &ini, &goal);
	fclose(m);
}

lista *inicializaLista(){
    return NULL;
}

lista *insereLista(lista *l,)

no **allocMatrix (int l, int c){
	no** m;
	int i;
	m = (no**)malloc(l*sizeof(no*));
	for(i=0;i<l;i++){
		m[i] = (no*)malloc(c*sizeof(no));
	}
	return m;
}

void readMap (FILE *m, no **map, int l, int c){
	int row, col;
	for (row=0; row<l;row++){
		for (col=0;col<c;col++){
			fscanf(m, "%c ", &map[row][col].c);
			map[row][col].lin=row;
			map[row][col].col=col;
		}
	}

}

void printMap(no **map, int l, int c){
	int row,col;
	printf("\nMap:\n");
	for (row=0;row<l;row++){
		for(col=0;col<c;col++){
			printf("%c ",map[row][col].c);
		}
		printf("\n");
	}
}

void setF (no *node, no *ini, no *goal){
	if(node->lin == ini->lin && node->col == ini->col){
		node->h=0;
	}
	else{
		node->h = sqrt(pow((node->lin-ini->lin),2) + pow((node->col-ini->col),2));
	}
	node->g = sqrt(pow((node->lin-goal->lin),2) + pow((node->col-goal->col),2));
	node->f = node->h+node->g;
}

int ehVizinho (no vizinho, int l, int c){
    //printf("if(%d>=0 && %d>=0 && %d<l && %d<c)\n",vizinho.lin,vizinho.col,vizinho.lin);
    if(vizinho.lin>=0 && vizinho.col>=0 && vizinho.lin<l && vizinho.col<c){
        return 1;
    }
    else
        return 0;
}

no *checkNeighbours(no **map, int l, int c, no *closed, no *open, int *viz){
    printf("closed %d %d\n", closed->lin, closed->col);
    int row, col, i=0;
    no vizinho;
    for(row=-1;row<=1;row++){
        for(col=-1;col<=1;col++){
            vizinho.lin = closed->lin+row;
            vizinho.col = closed->col+col;
            if(ehVizinho(vizinho, l, c)==1){
                vizinho.c = map[vizinho.lin][vizinho.col].c;
                if ((vizinho.c!='X') && (vizinho.c!='I') && (vizinho.c!='G') && (vizinho.lin != closed->lin ) && (vizinho.col != closed->col )){
                    printf("Vizinho valido: %d %d\n", vizinho.lin, vizinho.col);
                    getchar();
                    (*viz)++;
                    printf("%d\n", *viz);
                    open = (no*) realloc(open, (*viz)*sizeof(no));

                    open[i] = map[vizinho.lin][vizinho.col];
                    i++;
                }
            }
        }
    }

    return open;
}

int checkSmallerF (no *open, int tam){
    int i, smallerF=INT_MAX;
    for(i=0;i<tam;i++){
        if(open[i].f<smallerF){
            smallerF=i;
        }
    }
    return smallerF;
}

void findPath (no **map, int l, int c, no *ini, no *goal){
	lista *closed, *open;
	no info;
	int row, col, contOpen = 0, viz=0, clos = 1, smallerF;

	closed = inicializaLista();
	open = inicializaLista();



	row = ini->lin;
	col = ini->col;
	setF(ini,ini,goal);
	info = map[ini->lin][ini->col];
	setF(&info,ini,goal);
	//printf("\nini: %d %d %c\n", closed[0].lin, closed[0].col, closed[0].c);
	while(1){//(x!=goal->x && y!=goal->y){
        open = checkNeighbours(map,l,c,&closed[clos-1],open, &viz);
        if(viz==1){
            setF(&open[0],ini,goal);
            clos++;
            closed = (no*) realloc(closed, (clos)*sizeof(no));
            closed[clos-1] = open[0];
        }
        else{
            smallerF = checkSmallerF (open,viz);
            clos++;
            closed = (no*) realloc(closed, (clos)*sizeof(no));
            closed[clos-1] = open[smallerF];
        }
        for(row=0;row<clos;row++)
        printf("Closed %d\tPos: %d %d, F: %f, H: %f, G: %f\n", row, closed[row].lin, closed[row].col, closed[row].f, closed[row].h, closed[row].g);
        getchar();
        free(open);
        viz=0;
        getchar();

	}

    for(row=0;row<clos;row++)
        printf("Closed %d\tPos: %d %d, F: %f, H: %f, G: %f\n", row, closed[row].lin, closed[row].col, closed[row].f, closed[row].h, closed[row].g);
		//getchar();

	//}



}


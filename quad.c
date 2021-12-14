#include <stdio.h>
#include <stdbool.h>
#include <time.h>


struct Square {
    int x1, y1, x2, y2, d, pos;
    struct Square* topLeft;
    struct Sqaure* topRight;
    struct Square* botLeft;
    struct Square* botRight;
    bool leaf;
};

struct Square* initSquare(int x1, int y1, int x2, int y2, int d, int n, int pos) {
    
    struct Square* sq = (struct Square *) malloc(sizeof(struct Square));
    sq->x1 = x1;
    sq->y1 = y1;
    sq->x2 = x2;
    sq->y2 = y2;
    sq->d = d;
    sq->pos = pos;
    if (n >= d) {
        sq->leaf = false;
        initGrid( sq, n );
    } else {
        sq->leaf = true;
    }
    return sq;
}

void initGrid(struct Square* sq, int n) {

    int w = sq->x2 - sq->x1;
    int h = sq->y2 - sq->y1;
    int midX = sq->x1 + w/2;
    int midY = sq->y1 + h/2;

    sq->topLeft = initSquare( sq->x1, sq->y1, midX, midY, sq->d + 1, n, 1 );
    sq->topRight = initSquare( midX, sq->y1, sq->x2, midY, sq->d + 1, n, 2 );
    sq->botLeft = initSquare( sq->x1, midY, midX, sq->y2, sq->d + 1, n, 3 );
    sq->botRight = initSquare(midX, midY, sq->x2, sq->y2, sq->d + 1, n, 4);

}


int getPosFromPoint(struct Square* sq, int x, int y) {
    int w = sq->x2 - sq->x1;
    int h = sq->y2 - sq->y1;
    int midX = sq->x1 + w/2;
    int midY = sq->y1 + h/2;
    bool isTop = false;
    bool isLeft = false;

    if ( x < midX ) isLeft = true;
    if ( y < midY ) isTop = true;

    if ( isTop && isLeft ) return 1;
    else if ( isTop && !isLeft ) return 2;
    else if ( !isTop && isLeft ) return 3;
    else if ( !isTop && !isLeft) return 4;
}

int getPoint(struct Square* sq, int x, int y, int index) {
    if(sq->leaf) return index;
    int pos = getPosFromPoint(sq, x, y);

    switch(pos) {
        case 1:
            // 00
            printf("topLeft\n");
            getPoint(sq->topLeft, x, y, index);
            break;
        case 2:
            // 01
            printf("topRight\n");
            index = index | (1 << sq->d*2);
            getPoint(sq->topRight, x, y, index);
            break;
        case 3:
            // 10
            printf("botLeft\n");
            index = index | (2 << sq->d*2);
            getPoint(sq->botLeft, x, y, index);
            break;
        case 4:
            // 11
            printf("botRight\n");
            index = index | (3 << sq->d*2);
            getPoint(sq->botRight, x, y, index);
            break;
    }    
}

int getRange( struct Square* sq, int x1, int x2, int y1, int y2) {
    if( sq->leaf ) return 1;

    int pos1 = getPosFromPoint(sq, x1, y1);
    int pos2 = getPosFromPoint(sq, x2, y2);
    int pos3 = getPosFromPoint(sq, x1, y2);
    int pos4 = getPosFromPoint(sq, x2, y1);

    recurseByPos( sq, pos1, x1, y1, x2, y2 );
    recurseByPos( sq, pos2, x1, y1, x2, y2 );
    recurseByPos( sq, pos3, x1, y1, x2, y2 );
    recurseByPos( sq, pos4, x1, y1, x2, y2 );

}

void recurseByPos( struct Square* sq, int pos, int x1, int x2, int y1, int y2 ) {
    switch( pos ) {
        case 1:
            getRange( sq->topLeft, x1, y1, x2, y2);
            break;
        case 2:
            getRange( sq->topRight, x1, y1, x2, y2);
            break;
        case 3:
            getRange( sq->botLeft, x1, y1, x2, y2);
            break;
        case 4:
            getRange( sq->botRight, x1, y1, x2, y2);
            break;
    }
}

int main() {
   struct Square* sq = initSquare( 0, 0, 10000, 10000, 1, 6, 1 );
   int index = getPoint( sq, 9000, 9000, 0);
   printf("Result: %i\n", index);
   clock_t begin = clock();
   getRange( sq, 0, 0, 3000, 6000 );
   clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f", time_spent);
   return 0;
}
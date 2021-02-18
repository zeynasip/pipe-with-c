#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]){   

    //printf("satsut girdi\n");

    char *rowcol[6]= {"row1", "col1", "row2", "col2", "row3", "col3"};
    
    int rnd = atoi(argv[0]);
 
    char randRowCol[5];
    strcpy(randRowCol, rowcol[rnd]);

    //writing the random row or column to pipe
    write(4, &randRowCol, 10*sizeof(char));

}

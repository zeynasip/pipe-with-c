#include<stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    
    //printf("kofak girdi\n");

    int comp[3], matrix1[2][2], matrix2[2][2], matrix3[2][2]; 
    int cofac1, cofac2, cofac3;
    int p1, p2, p3;

    //reading the 2x2 matrix and array from the determinant3x3
    read(3, &p1, sizeof(int));
    read(3, &p2, sizeof(int));
    read(3, &p3, sizeof(int));
    read(3, &comp, 3*sizeof(int));
    read(3, &matrix1, 4*sizeof(int));
    read(3, &matrix2, 4*sizeof(int));
    read(3, &matrix3, 4*sizeof(int));

    //puts("kofak okudu");

    int comp1 = comp[0];
    int comp2 = comp[1];
    int comp3 = comp[2]; 
    
    if(p1 % 2 == 1){
        cofac1 = (-1) * comp1 * ((matrix1[0][0] * matrix1[1][1]) - (matrix1[0][1] * matrix1[1][0]));
    }
    else{
        cofac1 = comp1 * ((matrix1[0][0] * matrix1[1][1]) - (matrix1[0][1] * matrix1[1][0]));
    }

    if(p2 % 2 == 1){
        cofac2 = (-1) * comp2 * ((matrix2[0][0] * matrix2[1][1]) - (matrix2[0][1] * matrix2[1][0]));
    }
    else{
        cofac2 = comp2 * ((matrix2[0][0] * matrix2[1][1]) - (matrix2[0][1] * matrix2[1][0]));
    }

    if(p3 % 2 == 1){
        cofac3 = (-1) * comp3 * ((matrix3[0][0] * matrix3[1][1]) - (matrix3[0][1] * matrix3[1][0]));
    }
    else{
        cofac3 = comp3 * ((matrix3[0][0] * matrix3[1][1]) - (matrix3[0][1] * matrix3[1][0]));
    }

    //printf("cofaclar: %d %d %d\n", cofac1, cofac2, cofac3);

    //writing the resut of the cofactor to pipe
    write(4, &cofac1, sizeof(int));
    write(4, &cofac2, sizeof(int));
    write(4, &cofac3, sizeof(int));

    return 0;

}

#include<stdlib.h>
#include<stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char *intstr(int number){
    int count=0;
    int numbertmp=number;
    while(numbertmp>0)
    {
        int digit= numbertmp%10;
        numbertmp/=10;
        count++;
    }
    char * value= (char * ) calloc (count,sizeof(unsigned char)  );
    numbertmp=number;
    count--;
    while(numbertmp>0)
    {
        int digit= numbertmp%10;
        numbertmp/=10;
        char x=(char) 48+digit;
        *(value+count)=x;
        count--;
    }
    return value;
}

int main(){

    //defining the matrix
    puts("");
    int matrix[3][3];
    int i, j;
    for(i = 0; i <= 2; i++){
        for(j = 0; j <= 2; j++){
            printf("%d.row, %d.column element : ", i+1, j+1);
            scanf("%d", &matrix[i][j]); 
        }
    }
    puts("");

    //int matrix[3][3] = {1, 2, -1, 0, 1, -1, -1, 3, 1};   
    
    int random, fv;
    
    //random number for satsutsec.c
    srand(time(0));
    random = 0 + rand() % 5;

    //defining array to send random number for satsutsec.c with execv
    char *args[3];    
    args[0] = (char*)malloc(5 * sizeof(char));
    strcpy(args[0], intstr(random));
    args[1] = NULL;
    args[2] = NULL;  

    //piping or the return value for the other process
    int pipefd[2];
    if(pipe(pipefd) < 0)
        printf("pipe error");

    //fork for the satsutsec.c
    fv = fork();
    if(fv == 0){      
        i = execv("satsutsec", args);      
        exit(0);     
    }
    else{
        wait(&i);
    }

    //defining a char array for reading the return value from satsutsec.c
    char selected[10];
    read(pipefd[0], &selected, 10*sizeof(char));
    //printf("secilen row or col: %s\n", selected);

    //defining variables to be used in operations
    int arr[3], kmatrix1[2][2], kmatrix2[2][2], kmatrix3[2][2];
    int row, col;
    int pow1, pow2, pow3;
    int result1, result2, result3;
    int totalRes;

    //if the random selected is row
    if(selected[0] == 'r'){

        if(selected[3] == '1') row = 1;
        else if(selected[3] == '2') row = 2;
        else if(selected[3] == '3') row = 3;

        //assining selected row values to an array
        for(i = 0; i < 3; i++){
            arr[i] = matrix[row - 1][i];
        }

        //filling 2x2 matrix according to the selected row
        if(selected[3] == '1'){
                
            kmatrix1[0][0] = matrix[1][1];
            kmatrix1[0][1] = matrix[1][2];
            kmatrix1[1][0] = matrix[2][1];
            kmatrix1[1][1] = matrix[2][2];

            kmatrix2[0][0] = matrix[1][0];
            kmatrix2[0][1] = matrix[1][2];
            kmatrix2[1][0] = matrix[2][0];
            kmatrix2[1][1] = matrix[2][2];

            kmatrix3[0][0] = matrix[1][0];
            kmatrix3[0][1] = matrix[1][1];
            kmatrix3[1][0] = matrix[2][0];
            kmatrix3[1][1] = matrix[2][1];

            pow1 = 2;
            pow2 = 3;
            pow3 = 4;
                
            write(pipefd[1], &pow1, sizeof(int));    
            write(pipefd[1], &pow2, sizeof(int));      
            write(pipefd[1], &pow3, sizeof(int));          
            write(pipefd[1], &arr, 3*sizeof(int));
            write(pipefd[1], &kmatrix1, 4*sizeof(int));
            write(pipefd[1], &kmatrix2, 4*sizeof(int));
            write(pipefd[1], &kmatrix3, 4*sizeof(int));

            fv = fork();
            if(fv == 0){
                i = execv("kofakhesap2x2", NULL);
                exit(0);
            }
    else{
        wait(&i);
    }

            read(pipefd[0], &result1, sizeof(int));
            read(pipefd[0], &result2, sizeof(int));
            read(pipefd[0], &result3, sizeof(int));

            totalRes = result1 + result2 + result3;
        }

        else if(selected[3] == '2'){

           kmatrix1[0][0] = matrix[0][1];
           kmatrix1[0][1] = matrix[0][2];
           kmatrix1[1][0] = matrix[2][1];
           kmatrix1[1][1] = matrix[2][2];
           
           kmatrix2[0][0] = matrix[0][0];
           kmatrix2[0][1] = matrix[0][2];
           kmatrix2[1][0] = matrix[2][0];
           kmatrix2[1][1] = matrix[2][2];           
           
           kmatrix3[0][0] = matrix[0][0];
           kmatrix3[0][1] = matrix[0][1];
           kmatrix3[1][0] = matrix[2][0];
           kmatrix3[1][1] = matrix[2][1];

            pow1 = 3;
            pow2 = 4;
            pow3 = 5;
                
            write(pipefd[1], &pow1, sizeof(int));    
            write(pipefd[1], &pow2, sizeof(int));      
            write(pipefd[1], &pow3, sizeof(int));             
            write(pipefd[1], &arr, 3*sizeof(int));
            write(pipefd[1], &kmatrix1, 4*sizeof(int));
            write(pipefd[1], &kmatrix2, 4*sizeof(int));
            write(pipefd[1], &kmatrix3, 4*sizeof(int));

            fv = fork();
            if(fv == 0){
                i = execv("kofakhesap2x2", NULL);
                exit(0);
            }
    else{
        wait(&i);
    }

            read(pipefd[0], &result1, sizeof(int));
            read(pipefd[0], &result2, sizeof(int));
            read(pipefd[0], &result3, sizeof(int));

            totalRes = result1 + result2 + result3;
        }

        else if(selected[3] == '3'){

            kmatrix1[0][0] = matrix[0][1];
            kmatrix1[0][1] = matrix[0][2];
            kmatrix1[1][0] = matrix[1][1];
            kmatrix1[1][1] = matrix[1][2];
            
            kmatrix2[0][0] = matrix[0][0];
            kmatrix2[0][1] = matrix[0][2];
            kmatrix2[1][0] = matrix[1][0];
            kmatrix2[1][1] = matrix[1][2];
            
            kmatrix3[0][0] = matrix[0][0];
            kmatrix3[0][1] = matrix[0][1];
            kmatrix3[1][0] = matrix[1][0];
            kmatrix3[1][1] = matrix[1][1];
            
            pow1 = 4;
            pow2 = 5;
            pow3 = 6;
                
            write(pipefd[1], &pow1, sizeof(int));    
            write(pipefd[1], &pow2, sizeof(int));      
            write(pipefd[1], &pow3, sizeof(int)); 
            write(pipefd[1], &arr, 3*sizeof(int));
            write(pipefd[1], &kmatrix1, 4*sizeof(int));
            write(pipefd[1], &kmatrix2, 4*sizeof(int));
            write(pipefd[1], &kmatrix3, 4*sizeof(int));

            fv = fork();
            if(fv == 0){
                i = execv("kofakhesap2x2", NULL);
                exit(0);
            }
    else{
        wait(&i);
    }

            read(pipefd[0], &result1, sizeof(int));
            read(pipefd[0], &result2, sizeof(int));
            read(pipefd[0], &result3, sizeof(int));

            totalRes = result1 + result2 + result3;
        }
    }

    //if the random selected is column
    else if(selected[0] == 'c'){

        if(selected[3] == '1') col = 1;
        else if(selected[3] == '2') col = 2;
        else if(selected[3] == '3') col = 3;

        //assining selected column values to an array
        for(i = 0; i < 3; i++){
            arr[i] = matrix[i][col - 1];
        }

        //filling 2x2 matrix according to the selected column
        if(selected[3] == '1'){

            kmatrix1[0][0] = matrix[1][1];
            kmatrix1[0][1] = matrix[1][2];
            kmatrix1[1][0] = matrix[2][1];
            kmatrix1[1][1] = matrix[2][2];
            
            kmatrix2[0][0] = matrix[0][1];
            kmatrix2[0][1] = matrix[0][2];
            kmatrix2[1][0] = matrix[2][1];
            kmatrix2[1][1] = matrix[2][2];
            
            kmatrix3[0][0] = matrix[0][1];
            kmatrix3[0][1] = matrix[0][2];
            kmatrix3[1][0] = matrix[1][1];
            kmatrix3[1][1] = matrix[1][2];

            pow1 = 2;
            pow2 = 3;
            pow3 = 4;
                
            write(pipefd[1], &pow1, sizeof(int));    
            write(pipefd[1], &pow2, sizeof(int));      
            write(pipefd[1], &pow3, sizeof(int));
            write(pipefd[1], &arr, 3*sizeof(int));
            write(pipefd[1], &kmatrix1, 4*sizeof(int));
            write(pipefd[1], &kmatrix2, 4*sizeof(int));
            write(pipefd[1], &kmatrix3, 4*sizeof(int));

            fv = fork();
            if(fv == 0){
                i = execv("kofakhesap2x2", NULL);
                exit(0);
            }
    else{
        wait(&i);
    }

            read(pipefd[0], &result1, sizeof(int));
            read(pipefd[0], &result2, sizeof(int));
            read(pipefd[0], &result3, sizeof(int));

            totalRes = result1 + result2 + result3;
        }

        else if(selected[3] == '2'){

            kmatrix1[0][0] = matrix[1][0];
            kmatrix1[0][1] = matrix[1][2];
            kmatrix1[1][0] = matrix[2][0];
            kmatrix1[1][1] = matrix[2][2];
            
            kmatrix2[0][0] = matrix[0][0];
            kmatrix2[0][1] = matrix[0][2];
            kmatrix2[1][0] = matrix[2][0];
            kmatrix2[1][1] = matrix[2][2];
            
            kmatrix3[0][0] = matrix[0][0];
            kmatrix3[0][1] = matrix[0][2];
            kmatrix3[1][0] = matrix[1][0];
            kmatrix3[1][1] = matrix[1][2];

            pow1 = 3;
            pow2 = 4;
            pow3 = 5;
                
            write(pipefd[1], &pow1, sizeof(int));    
            write(pipefd[1], &pow2, sizeof(int));      
            write(pipefd[1], &pow3, sizeof(int));
            write(pipefd[1], &arr, 3*sizeof(int));
            write(pipefd[1], &kmatrix1, 4*sizeof(int));
            write(pipefd[1], &kmatrix2, 4*sizeof(int));
            write(pipefd[1], &kmatrix3, 4*sizeof(int));

            fv = fork();
            if(fv == 0){
                i = execv("kofakhesap2x2", NULL);
                exit(0);
            }
    else{
        wait(&i);
    }

            read(pipefd[0], &result1, sizeof(int));
            read(pipefd[0], &result2, sizeof(int));
            read(pipefd[0], &result3, sizeof(int));

            totalRes = result1 + result2 + result3;
        }

        else if(selected[3] == '3'){

            kmatrix1[0][0] = matrix[1][0];
            kmatrix1[0][1] = matrix[1][1];
            kmatrix1[1][0] = matrix[2][0];
            kmatrix1[1][1] = matrix[2][1];
            
            kmatrix2[0][0] = matrix[0][0];
            kmatrix2[0][1] = matrix[0][1];
            kmatrix2[1][0] = matrix[2][0];
            kmatrix2[1][1] = matrix[2][1];
            
            kmatrix3[0][0] = matrix[0][0];
            kmatrix3[0][1] = matrix[0][1];
            kmatrix3[1][0] = matrix[1][0];
            kmatrix3[1][1] = matrix[1][1];
            
            pow1 = 4;
            pow2 = 5;
            pow3 = 6;
                
            write(pipefd[1], &pow1, sizeof(int));    
            write(pipefd[1], &pow2, sizeof(int));      
            write(pipefd[1], &pow3, sizeof(int));
            write(pipefd[1], &arr, 3*sizeof(int));
            write(pipefd[1], &kmatrix1, 4*sizeof(int));
            write(pipefd[1], &kmatrix2, 4*sizeof(int));
            write(pipefd[1], &kmatrix3, 4*sizeof(int));

            fv = fork();
            if(fv == 0){
                i = execv("kofakhesap2x2", NULL);
                exit(0);
            }
    else{
        wait(&i);
    }

            read(pipefd[0], &result1, sizeof(int));
            read(pipefd[0], &result2, sizeof(int));
            read(pipefd[0], &result3, sizeof(int));

            totalRes = result1 + result2 + result3;
        }
    }
    
    close(pipefd[0]);
    close(pipefd[1]);    
    
    puts("");
    printf("Determinant of the matrix: %d\n", totalRes);
    puts("");

    return 0;

}

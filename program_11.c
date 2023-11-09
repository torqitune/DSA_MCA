#include<stdio.h>
int main(){
    int row,col,count = 0;
    printf("Enter value of row :");
    scanf("%d",&row);                                           //entering row value
    printf("Enter value of column :");
    scanf("%d",&col);                                           //entering column value
    printf("\n***Enter values in sparse matrix***\n");
    int mat[row][col];                                          //declaring sparse matrix
    int lim = (int)((row*col)/4);                               //declaring 1/4rth limit codition
    for(int i = 0; i<row ; i++){
        for(int j = 0; j<col ; j++){
            scanf("%d",&mat[i][j]);                             //inputting value
            if(mat[i][j]!=0)
                count++;                                        //incrementing count value if non-zero element is entered
            if(count>lim){                                      //if within the loop , limit exceeds then exit the code
                printf("\n***IN-VALID sparse matrix, 1/4th limit exceeds. ***");
                return 0;
            }
        }
    }
    printf("\n***SPARSE-MATIX***\n");                           //printing sparse matrix
    for(int i = 0; i<row ; i++){
        for(int j = 0; j<col ; j++){
            printf("%d  ",mat[i][j]);
        }
        printf("\n");
    }



        int triplet[count+1][3];                                //declaring triplet matrix
        triplet[0][0]=row;                                      //setting row 1st with dimensions of sparse matrix
        triplet[0][1]=col;
        triplet[0][2]=count;                                    //setting non-zero elements.
        int t_row=1;
        for(int i = 0; i<row; i++){                             //traversing the sparse matrix
            for(int j = 0; j<col; j++){
                if(mat[i][j]!=0){
                    triplet[t_row][0] = i;                      //setting the positions of non-zero elements
                    triplet[t_row][1] = j;
                    triplet[t_row][2] = mat[i][j];              
                    t_row++;
                }
            }
        }
        printf("\n***TRIPLET***\n");                            //printing triplet.
        for(int i = 0; i<count+1 ; i++){
            for(int j = 0 ; j<3 ; j++){
                printf("%d  ",triplet[i][j]);
            }
            printf("\n");
        }

    return 0;
}
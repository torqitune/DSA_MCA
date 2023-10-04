#include<stdio.h>
#include<stdlib.h>

int *array; 

int top = -1;

void display(){
    printf("\nArray : ");
    for(int i = 0 ; i<=top; i++){
        printf("%d ",array[i]);
    }
}

void push(int n){
    if(top >=9){
        printf("***OVERFLOW***\n");
    }
    else{
        top++;
        array[top] = n;
    }
}

void pop(){
    if(top<0){
        printf("***UNDERFLOW***\n");        
    }
    else{
        top--;
    }
}


int main(){
    array = (int*)malloc(10*sizeof(int));
    push(1);
    display();

    push(2);
    display();

    push(3);
    display();

    push(4);
    display();

    push(5);
    display();
    push(6);
    display();
    push(7);
    display();
    push(8);
    display();
    push(9);
    display();
    push(10);
    display();
    push(11);
    display();

    push(121);
    display();
 
    return 0;
}

#include<stdio.h>
#include<stdlib.h>

int *array; 

int top = -1;

void display(){
    if(top == -1){              //array is still empty
        printf("\nArray : EMPTY\n");
    }
    else{
        printf("\nArray : ");
        for(int i = 0 ; i<=top; i++){
            printf("%d ",array[i]);
        }
    }
}

void push(int n){
    if(top >=5){                //our array size is 6, so if reach index greater then 5 then it is an overflow condition.
        printf("\n***OVERFLOW***\n");       
    }
    else{
        top++;
        array[top] = n;
    }
}

void pop(){                 //handling uderflow condition
    if(top<0){
        printf("\n***UNDERFLOW***\n");   
        return;     
    }
    else{   
        top--;              //in normal case decrement top
    }
}



void menu_array()
{
    printf("\n===STACK===");
    printf("\n1.PUSH");
    printf("\n2.POP.");
    printf("\n3.DISPLAY.");
    printf("\n4.Exit.");
    printf("\n==========\n");

single_label:
    printf("\nEnter your choice (1-4) : ");
    int choice;

    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4)
    { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
        printf("\n***ENTER A VALID INTEGER***.\n");
        while (getchar() != '\n')
            ; // Clear the input buffer
        goto single_label;
    }

    // if (choice == 1)
    // {
    //     print_array(&curr);
    //     menu_array();
    // }

    if (choice == 1)
    {
        int value;
    push:
        printf("\nEnter value : ");
        if (scanf("%d", &value) != 1)
        { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n'); // Clear the input buffer
            goto push;
        }
        else
        {
            push(value);
            display();
            menu_array();
        }
    }
    else if (choice == 2)
    {
        pop();
        display();
        menu_array();
    }
    else if (choice == 3)
    {
        display();
        menu_array();
    }

    else if (choice == 4)
    {
        printf("Program Terminated succesfully.\n");
        exit(1);
    }
}

int main(){
    array = (int*)malloc(6*sizeof(int));
    menu_array();
    return 0;
}

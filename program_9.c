#include<stdlib.h>
#include<stdio.h>

#define size 5              //declaring a constant size
int array[size];
int front = -1;             //front is front of queue
int rear = -1;              //rear is end/rear of list

void display(){
    if(front == -1)                 //front=-1 represent empty 
        printf("\nQueue : EMPTY");      
    else{
        printf("\nQueue : ");           //else normal display

        if(rear>=front){                //if rear hasn't made the loop to start,i.e rear hasn't reached last position now.
            for(int i = front ; i<=rear ; i++){
                printf("%d  ",array[i]);
            }
        }
        else{                           //else rear had reached last position and made a cicular loop to start , so in this case print like below
            for(int i = 0 ; i<=rear ; i++){
                printf("%d  ",array[i]);
            }
            for(int i = front ; i<size ; i++){
                printf("%d  ",array[i]);
            }
        }
        printf("\n");
    }
}

void enqueue(int value){
    if(front == -1 && rear == -1){
        front = rear = 0;
        array[rear] = value;
    }
    else if( (front==0 && rear==size-1) || (front == rear+1))
        printf("\n***OVERFLOW***\n");
    else if(rear==size-1 && front!=0){
        rear = 0;
        array[rear] = value;
    }
    else{
        array[++rear] = value;
    }

}

void dequeue(){
    if(front==-1 && rear==-1)               //if fornt=rear = -1 which means queue is already empty and popping is not possible.
        printf("\n***UNDERFLOW***\n");
    else if(front == rear)
        front = rear = -1;
    else if(front == size-1)
        front = 0;
    else    
        front++;

}

void status(){                                  //checks current status of queuue
    if(front==-1 && rear==-1)                   //if no element is present
        printf("\nSTATUS : Queue is EMPTY.\n");
    else if((front == 0 && rear==size-1) || (front==rear+1))                     //if rear is at last index
        printf("\nSTATUS : Queue is FULL.\n");
    else    
        printf("\nSTATUS : Space available.\n");    //if some elements are already there and some space is still available.

}



void menu_array()
{
    printf("\n\n==CIRCULAR-QUEUE==");
    printf("\n1.Display queue.");
    printf("\n2.Enqueue.");
    printf("\n3.Dequeue.");
    printf("\n4.Status.");
    printf("\n5.Exit.");
    printf("\n====================\n");

single_label:
    printf("\nEnter your choice (1-5) : ");
    int choice;

    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 5)
    { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
        printf("\n***ENTER A VALID INTEGER***.\n");
        while (getchar() != '\n'); // Clear the input buffer
        goto single_label;
    }

    if (choice == 1)
    {
        display();
        menu_array();
    }

    else if (choice == 2)
    {
        int value;
    insert_head:
        printf("\nEnter data : ");
        if (scanf("%d", &value) != 1)
        { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n')
                ; // Clear the input buffer
            goto insert_head;
        }
        else
        {
            enqueue(value);
            display();
            menu_array();              // returning menu again.
        }
    }
    else if (choice == 3)
    {
        dequeue();
        display();
        menu_array();
    }
    else if (choice == 4)
    {
        status();
        display();
        menu_array();
    }
    else if (choice == 5)
    {
        printf("Program Terminated succesfully.\n");
        exit(1);
    }
}

int main(){
    
    menu_array();
    return 0;
}
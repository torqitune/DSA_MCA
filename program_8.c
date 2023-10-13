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
        for(int i = front ; i<=rear ; i++){
            printf("%d  ",array[i]);
        }
        printf("\n");
    }
}

void enqueue(int value){
    if(rear == size-1)                  //if rear reaches last position
        printf("\n***OVERFLOW***\n");
    else{
        if(front == -1 && rear==-1){        //if no elements were pushed, so the list was still at -1 index, so start from oth index
            front = rear = 0;
        }
        else
            rear++;                      //else increment rear for next value insertion
        array[rear] = value;            //insert value at rear position.
    }
}

void dequeue(){
    if(front==-1 && rear==-1)               //if fornt=rear = -1 which means queue is already empty and popping is not possible.
        printf("\n***UNDERFLOW***\n");
    else{
        if(front == rear)               //if only single element is present, i.e front & rear then will point to same position,so delete that & set both front&rear to -1 , as our queue become empty.
            front = rear = -1;
        else    
            front++;                    //if already some elements are available then just increment front so that it now points to next element.
    }

}

void status(){                                  //checks current status of queuue
    if(front==-1 && rear==-1)                   //if no element is present
        printf("\nSTATUS : Queue is EMPTY.\n");
    else if(rear == size-1)                     //if rear is at last index
        printf("\nSTATUS : Queue is FULL.\n");
    else    
        printf("\nSTATUS : Space available.\n");    //if some elements are already there and some space is still available.

}



void menu_array()
{
    printf("\n\n=======QUEUE=======");
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
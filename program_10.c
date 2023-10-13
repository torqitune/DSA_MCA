#include <stdio.h>
#include <stdlib.h>

struct Node
{ // our structure of linked list.
    int data;
    struct Node *next;
};

struct Node *head = NULL;  // declaring head as global
struct Node *rear = NULL;  // same for rear also, rear is pointing to last node of list.
struct Node *head1 = NULL; // this head1 will keep track of head of stack.
struct Node *top = NULL;   // creating a top pointer for stack top

struct Node *createNode(int value)
{                                                                      // this function creates a new node with the given value & returns it.
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node)); // dynamically creating new node
    if (newNode != NULL)
    { // just in case if our node was not created
        newNode->data = value;
        newNode->next = NULL;
    }
    return newNode; // return created node to caller
}

void display()
{ // no need to say anything
    if (head == NULL)
        printf("\nQueue : EMPTY");
    else
    {
        struct Node *temp = head;
        printf("\nQueue : ");
        while (temp != NULL)
        {
            printf("%d  ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void display_stack()
{ // no need to say anything
    if (head1 == NULL)
        printf("\nSTACK : EMPTY");
    else
    {
        struct Node *temp = head1;
        printf("\nSTACK : ");
        while (temp != NULL)
        {
            printf("%d  ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void enqueue(int value)
{
    struct Node *temp = createNode(value); // creating a new node temp
    if (head == NULL)
    {                // if list is empty then
        head = temp; // add the created node & point both head & rear to it.
        rear = temp;
    }
    else
    {
        rear->next = temp; // else add the created node to last of the list.
        rear = temp;       // point this list rear to end
    }
}

void dequeue()
{
    if (head == NULL) // if list is already empty then underflow
        printf("\n***Underflow***\n");
    else
    {
        struct Node *del = head;
        head = head->next; // shift the head to next position
        free(del);         // delete previous node
    }
}

void push(int value)
{
    struct Node *temp = createNode(value); // creating a new node
    if (head1 == NULL)
    {               // if stack is already empty
        top = temp; // set both top & head to new created node, i.e now our stack contains one node
        head1 = temp;
    }
    else
    {
        top->next = temp; // else keep on pushing new node to next position of top , and then setting top to top element.
        top = temp;
    }
}

void pop()
{
    if (head1 == NULL) // if no element is present
        printf("\n***Underflow***\n");
    else if (head1 == top) // if only one element is present
        head1 = top = NULL;
    else
    {
        struct Node *temp = head1; // else create a new node
        while (temp->next != top)
        {
            temp = temp->next; // reach till 2nd last node of the stack
        }
        free(temp->next); // delete top element which is at next position of temp.
        temp->next = NULL;
        top = temp; // set top to actual position .
    }
}

void menu_array()
{
    printf("\n\n==Queue(Linked List)==");
    printf("\n1.Display queue.");
    printf("\n2.Enqueue.");
    printf("\n3.Dequeue.");
    printf("\n4.Exit.");
    printf("\n========================\n");

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
            menu_array(); // returning menu again.
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
        printf("Program Terminated succesfully.\n");
        exit(1);
    }
}

void menu_stack()
{
    printf("\n\n==STACK(Linked List)==");
    printf("\n1.Display Stack.");
    printf("\n2.Push.");
    printf("\n3.Pop.");
    printf("\n4.Exit.");
    printf("\n========================\n");

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

    if (choice == 1)
    {
        display_stack();
        menu_stack();
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
            push(value);
            display_stack();
            menu_stack(); // returning menu again.
        }
    }
    else if (choice == 3)
    {
        pop();
        display_stack();
        menu_stack();
    }

    else if (choice == 4)
    {
        printf("Program Terminated succesfully.\n");
        exit(1);
    }
}

void choice()
{
    printf("\n\n==CHOOSE ANY ONE==");
    printf("\n1.Queue using Linked List.");
    printf("\n2.Stack using Linked List.");
    printf("\n3.Exit.");
    printf("\n=====================\n");

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

    if (choice == 1)
    {
        menu_array();
    }

    else if (choice == 2)
    {
        menu_stack();
    }
    else if (choice == 3)
    {
        printf("Program Terminated succesfully.\n");
        exit(1);
    }
}

int main()
{
    choice();
    return 0;
}

#include <stdlib.h>
#include <stdio.h>

struct Node
{ // creating struct for our linked list, note: I will not use
    int data;
    struct Node *next;
};

struct Node *head = NULL; // Intializing head to null. Note: we are declaring this globally so that instead of making multiple copies of linked list , we work on only one list using refrencing.

struct Node *createNode(int data)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node)); // dynamically allocating memory to our newly created temp node.
    if (temp != NULL)
    {                      // if memory is not alloted just in case , then temp == NULL, so this condition will check if our node is created or not , if created then only proceed further.
        temp->data = data; // assigning data
        temp->next = NULL;
    }
    return temp;
}

void print_list(struct Node **head)
{ // here we are passing the head by reference i.e by address.
    if (*head == NULL)
    {
        printf("\nLinked List : NULL\n");
    }
    else
    {
        struct Node *temp = *head;
        printf("\nLinked List : ");
        while (temp != NULL)
        {
            printf("%d->", temp->data);
            temp = temp->next;
        }
        printf("\b \b");
        printf("\b \b\n");
    }
}

void insertAtHead(struct Node **head, int data)
{                                            // passing head by refrence
    struct Node *newNode = createNode(data); // creating a new node using another function which we will insert at head.
    if (newNode != NULL)
    {
        newNode->next = *head;
        *head = newNode; // now our head is pointing to our newly created node and new node is inserted at head successfully
    }
}

void insertAtEnd(struct Node **head, int data)
{                      // passing head as reference
    if (*head == NULL) // if our list is empty then we can insert node at head or at end, at last we will be getting only one node , so I used insert at head function
        insertAtHead(head, data);
    else
    {
        struct Node *temp = *head; // if list is not empty then traverse till last node of the list
        struct Node *newNode = createNode(data);
        if (newNode != NULL)
        {
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newNode; // make the link
            newNode->next = NULL; // break the link
        }
    }
}
void count(struct Node **head)
{
    if (*head == NULL)
    {
        printf("\nCount : %d\n", 0); // if no node is there then count is 0.
        return;
    }
    struct Node *temp = *head;
    int count = 0;
    while (temp != NULL)
    {
        count++;
        temp = temp->next; // count is incremented every time we traverse the list.
    }
    printf("\nCount : %d\n", count); // print the count data.
}

void reverse(struct Node **head)
{
    if (*head == NULL)
    {
        printf("\n**NOT POSSIBLE**\n"); // if no node is there then reverse can't take place
    }
    else
    {
        struct Node *prev = NULL;  // prev pointer will keep track of previous position of current , i.e current->next will always point to prev position.
        struct Node *curr = *head; // curr will be used to traverse the list.
        struct Node *forw = NULL;  // NEXT  pointer will always point to next position of current.
        while (curr != NULL)
        {
            forw = curr->next;
            curr->next = prev; // joining curr to prev position.
            prev = curr;       // incrementing prev to curr position.
            curr = forw;       // incrementing curr to next node.
        }
        *head = prev; // at last head has to be changed to prev , now prev will act as head to reversed liked list.
    }
}

void menu_singleList()
{
    printf("\n\n=======SINGLE-LINKED-LIST=======");
    printf("\n1.Print Linked List.");
    printf("\n2.Enter at Begin.");
    printf("\n3.Enter at end.");
    printf("\n4.Count No. of Nodes.");
    printf("\n5.Reverse linked list.");
    printf("\n6.Exit.");
    printf("\n================================\n");

single_label:
    printf("\nEnter your choice (1-6) : ");
    int choice;

    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 6)
    { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
        printf("\n***ENTER A VALID INTEGER***.\n");
        while (getchar() != '\n')
            ; // Clear the input buffer
        goto single_label;
    }

    if (choice == 1)
    {
        print_list(&head);
        menu_singleList(); // going back to menu of single linked list.
    }

    else if (choice == 2)
    {
        int value;
    insert_head:
        printf("\nEnter data of node : ");
        if (scanf("%d", &value) != 1)
        { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n')
                ; // Clear the input buffer
            goto insert_head;
        }
        else
        {
            insertAtHead(&head, value); // even if our list is empty insert at head will work fine.
            print_list(&head);          // printing the single linked list

            menu_singleList(); // going back to menu of single linked list.
        }
    }
    else if (choice == 3)
    {
        int value;
    insert_tail:
        printf("\nEnter data of node : ");
        if (scanf("%d", &value) != 1)
        { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n')
                ; // Clear the input buffer
            goto insert_tail;
        }
        else
        {
            insertAtEnd(&head, value); // even if our list is empty insert at head will work fine.
            print_list(&head);         // printing the single linked list

            menu_singleList(); // going back to menu of single linked list.
        }
    }
    else if (choice == 4)
    {
        count(&head);
        menu_singleList();
    }

    else if (choice == 5)
    {
        reverse(&head);
        print_list(&head);
        menu_singleList();
    }
    else if (choice == 6)
    {
        printf("Program Terminated succesfully.\n");
        exit(1);
    }
}
int main()
{
    menu_singleList();
    return 0;
}
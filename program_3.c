#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
};

struct Node *head = NULL;  // Intializing head to null. Note: we are declaring this globally so that instead of making multiple copies of linked list , we work on only one list using refrencing.
struct Node *head1 = NULL; // This list is for circular double list.

void main_menu(); // Declaring our function here so that we don't get an error while function calling due to order of function defination.

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node)); // dynamically allocating memory to our newly created temp node.
    if (newNode != NULL)
    {                         // if memory is not alloted just in case , then temp == NULL, so this condition will check if our node is created or not , if created then only proceed further.
        newNode->data = data; // assigning data
        newNode->next = NULL;
        newNode->prev = NULL; // each newly created node will only have data value, and prev and next will be pointing to NULL initially.
    }
    return newNode;
}

void print_list(struct Node **head)
{ // here we are passing the head by reference i.e by address.
    if (*head == NULL)
    { // if list is already empty then handle this case
        printf("\nLinked List : NULL\n");
    }
    else
    {
        struct Node *temp = *head;
        printf("\nLinked List : ");
        while (temp != NULL)
        { // traversing list untill we reach last node.
            printf("%d->", temp->data);
            temp = temp->next;
        }
        printf("\b \b");
        printf("\b \b\n");
    }
}

void insertAtHead(struct Node **head, int data)
{
    struct Node *newNode = createNode(data); // creating a new node using another function which we will insert at head.
    if (newNode != NULL)
    {
        if (*head == NULL)
        { // if head is already null then setting prev pointer will not take place
            newNode->next = *head;
            newNode->prev = NULL;
            *head = newNode;
        }
        else
        { // else if there are more then one node in the list , then we set the previous pointer of head too , and shift head to original 1st position.
            newNode->next = *head;
            newNode->prev = NULL;
            (*head)->prev = newNode;
            *head = newNode; // now our head is pointing to our newly created node and new node is inserted at head successfully
        }
    }
}

void insertAtTail(struct Node **head, int data)
{
    if (*head == NULL) // if our list is empty then we can insert node at head or at end, at last we will be getting only one node , so I used insert at head function
        insertAtHead(head, data);
    else
    {
        struct Node *temp = *head; // if list is not empty then traverse till last node of the list
        struct Node *newNode = createNode(data);
        if (newNode != NULL)
        { // check if node creation was succesful or not.
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newNode; // make the link
            newNode->next = NULL; // break the link
        }
    }
}

bool element_present(struct Node **head, int info)
{ // this function is checking if element is present in list or not.
    struct Node *temp = *head;
    while (temp != NULL)
    {
        if (temp->data == info)
        { // while travesing each node , if we found the element in between then we return true , else return false.
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void insertAtPos(struct Node **head, int info, int data)
{
    if (element_present(head, info))
    { // here we are checking if our element is present in the list or not, if element is present in the list then only we are going to insert the node.
        struct Node *temp = *head;
        while (temp->data != info)
        { // reaching till our desired node.
            temp = temp->next;
        }
        if (temp->next == NULL)
        { // if we reach the last element , then add at tail.
            insertAtTail(head, data);
        }
        else
        {
            struct Node *FORW = temp->next; // FORW is a pointer pointing just next position to our desired node
            struct Node *newNode = createNode(data);
            temp->next = newNode; // making appropriate links
            FORW->prev = newNode;
            newNode->next = FORW;
            newNode->prev = temp;
        }
    }
    else
    {
        printf("***ELEMENT NOT FOUND***\n");
    }
}

void deleteHead(struct Node **head)
{
    if (*head == NULL) // if we have a empty list
        printf("***EMPTY LIST***\n");
    else
    {
        struct Node *del = *head; // else delete head.
        *head = (*head)->next;    // shift head to one position ahead and then delete.
        free(del);
    }
}

void deleteEnd(struct Node **head)
{
    if (*head == NULL) // if we have a empty list
        printf("***EMPTY LIST***\n");
    else if ((*head)->next == NULL)
    { // if only one node is there, I am deleting head only
        deleteHead(head);
    }
    else
    {
        struct Node *curr = *head;
        struct Node *BACK = NULL;
        while (curr->next != NULL)
        { // iterating till we reaches the last node. Also using another 'BACK' pointer which points to just immediate backward postion of curr,
            BACK = curr;
            curr = curr->next;
        }
        BACK->next = NULL; // once we reach last node, 'BACK' will be pointing to 2nd last node , so we perform deletion.
        free(curr);
    }
}

void deleteAtPos(struct Node **head, int info)
{
    if (element_present(head, info))
    { // here we are checking if our element is present in the list or not, if element is present in the list then only we are going to delete the node.
        struct Node *temp = *head;
        while (temp->data != info)
        { // using this loop we will reach till our desired node value
            temp = temp->next;
        }
        if (temp->next == NULL)
        { // if we reach the last element , then we delete at tail.
            deleteEnd(head);
            return;
        }
        else if (temp == *head)
        { // if we want to delete the starting node itself , then I deleted head.
            deleteHead(head);
        }
        else
        { // if our node to be deleted is somewhere in list.
            struct Node *FORW = temp->next;
            struct Node *BACK = temp->prev; // we reached till that node, and I made two pointers BACK and FORW which are pointing to immediate back and forward position of temp.
            BACK->next = FORW;
            FORW->prev = BACK; // I made appropriate links .
            free(temp);        // deleting temp.
            return;
        }
    }
    else
    {
        printf("***ELEMENT NOT FOUND***\n");
        return;
    }
}

void menu_doubleList()
{
    printf("\n\n=====DOUBLE-LINKED-LIST=====");
    printf("\n1.Print Linked List.");
    printf("\n2.Enter at Begin.");
    printf("\n3.Enter at end.");
    printf("\n4.Enter at a position.");
    printf("\n5.Delete at Begin.");
    printf("\n6.Delete at End.");
    printf("\n7.Delete at a position.");
    printf("\n8.GOTO Main-Menu.");
    printf("\n9.Exit.");
    printf("\n==============================\n");

circular_label:
    printf("\nEnter your choice (1-9) : ");
    int choice;

    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 9)
    { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
        printf("\n***ENTER A VALID INTEGER***.\n");
        while (getchar() != '\n')
            ; // Clear the input buffer
        goto circular_label;
    }

    if (choice == 1)
    {
        print_list(&head);
        menu_doubleList();
    }
    else if (choice == 2)
    {
        int value_c;
    c_insert_head:
        printf("\nEnter data of node : ");
        if (scanf("%d", &value_c) != 1)
        { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n')
                ; // Clear the input buffer
            goto c_insert_head;
        }
        else
        {
            insertAtHead(&head, value_c); // even if our list is empty insert at head will work fine.
            print_list(&head);            // printing the single linked list
            menu_doubleList();            // going back to menu of single linked list.
        }
    }
    else if (choice == 3)
    {
        int value_c;
    c_insert_end:
        printf("\nEnter data of node : ");
        if (scanf("%d", &value_c) != 1)
        { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n')
                ; // Clear the input buffer
            goto c_insert_end;
        }
        else
        {
            insertAtTail(&head, value_c); // even if our list is empty insert at head will work fine.
            print_list(&head);            // printing the single linked list
            menu_doubleList();            // going back to menu of single linked list.
        }
    }
    else if (choice == 4)
    {
        int c_element, info;
    c_insert_val:
        printf("\nEnter Data of node : ");
        if (scanf("%d", &c_element) != 1)
        { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n')
                ; // Clearing the input buffer
            goto c_insert_val;
        }

    c_insert_pos:
        printf("\nEnter INFO of node : ");
        if (scanf("%d", &info) != 1)
        { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n')
                ; // Clear the input buffer
            goto c_insert_pos;
        }

        insertAtPos(&head, info, c_element);
        print_list(&head);
        menu_doubleList();
    }
    else if (choice == 5)
    {
        deleteHead(&head);
        print_list(&head); // printing the single linked list
        menu_doubleList();
    }
    else if (choice == 6)
    {
        deleteEnd(&head);
        print_list(&head); // printing the single linked list
        menu_doubleList();
    }
    else if (choice == 7)
    {
        int info;
    c_del_pos:
        printf("\nEnter INFO of node : ");
        if (scanf("%d", &info) != 1)
        { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n')
                ; // Clear the input buffer
            goto c_del_pos;
        }
        deleteAtPos(&head, info);
        print_list(&head);
        menu_doubleList();
    }
    else if (choice == 8)
    {
        main_menu();
    }
    else if (choice == 9)
    {
        printf("Program Terminated succesfully.\n");
        exit(1);
    }
}

void print_circular(struct Node **head1)
{                       // here we are passing the head by reference i.e by address.
    if (*head1 == NULL) // if no node is present in list
    {
        printf("\nLinked List : NULL\n");
    }
    else if ((*head1)->next == *head1)
    { // if only one node is present then just print that node.
        printf("\nLinked List : ");
        printf("%d\n", (*head1)->data);
    }
    else
    {
        struct Node *temp = *head1; // if multiple elements are there.
        printf("\nLinked List : ");
        do
        {                               // I used do while loop , bcoz if I use normal while loop with temp->next != *head1, then all elements were printing except last node coz this loop will break at last node itself.
            printf("%d->", temp->data); // And if I use condition temp != *head then it will terminate at first position itself .
            temp = temp->next;          // So if used the condition temp!=*head with do-while loop , so it will print 1st node and then proceed to next node without terminating at 1st position itself.
        } while (temp != *head1);
        printf("\b \b");
        printf("\b \b\n");
        // printf("head : %d   tail : %d\n",(*head1)->data,(*head1)->prev->data);
    }
}

void c_insertAtHead(struct Node **head1, int data)
{
    struct Node *newNode = createNode(data);
    if (newNode != NULL)
    {
        if (*head1 == NULL)
        {                            // if no node is there.
            newNode->next = newNode; // then create a new node and makes its prev and next point to itself , NOTE: here I am pointing both prev and next to same node.
            newNode->prev = newNode;
            *head1 = newNode;
            return;
        }
        else
        {                                       // there are already some nodes present.
            struct Node *TAIL = (*head1)->prev; // tail is pointing to the last element of list.
            newNode->next = *head1;             // setting links
            newNode->prev = TAIL;
            TAIL->next = newNode; // tail now point to 1st position.
            *head1 = newNode;     // head now points to 1st position.
        }
    }
}

void c_insertEnd(struct Node **head1, int data)
{
    if (*head1 == NULL)
    { // if no element is there then we can Insert at head.
        c_insertAtHead(head1, data);
        return;
    }
    else if ((*head1)->next == *head1){ // if only one node is there.
        struct Node *newNode = createNode(data);
        (*head1)->next = newNode;
        newNode->next = *head1; // breaking the link and making the link.
        newNode->prev = *head1;
        (*head1)->prev = newNode; // we make sure that head is always pointing to the last element.
    }
    else
    {
        struct Node *newNode = createNode(data);
        struct Node *TAIL = (*head1)->prev; // setting tail pointer;

        TAIL->next = newNode;
        newNode->prev = TAIL;
        newNode->next = *head1;   // breaking the link and making the link.
        (*head1)->prev = newNode; // we make sure that head is always pointing to the last element.
    }
}



bool c_element_present(struct Node **head1, int info){ // this function is checking if element is present in list or not.
    if(*head1 == NULL){                               //if no element is present then return false.
        return false;
    }
    struct Node *temp = *head1;
    do{                                               //we used do-while so that it won't stop for case when only one node is there.
        if(temp->data == info){
            return true;
        }
        temp = temp->next;
    }while(temp != *head1);

    return false;
}


void c_insertAtPos(struct Node **head1, int info, int data)
{
    if (c_element_present(head1, info)){                                // here we are checking if our element is present in the list or not, if element is present in the list then only we are going to insert the node.
        struct Node *temp = *head1;
        while (temp->data != info){                                     // reaching till our desired node.
            temp = temp->next;
        }
        if (temp->next == *head1){                                      // if we reach the last element , then add at tail.
            c_insertEnd(head1, data);
        }
        else{
            struct Node *FORW = temp->next;                             // FORW is a pointer pointing just next position to our desired node
            struct Node *newNode = createNode(data);
            temp->next = newNode;                                       // making appropriate links
            FORW->prev = newNode;
            newNode->next = FORW;
            newNode->prev = temp;
        }
    }
    else
    {
        printf("***ELEMENT NOT FOUND***\n");
    }
}



void c_deleteHead(struct Node** head1){
    if(*head1 == NULL){
        printf("\n***List Already Empty.***\n");                            //if no node is present
    }
    else if((*head1)->next == *head1){                                      //if only one node is there.
        struct Node* del = *head1;
        *head1 = NULL;
        free(del);
    }
    else{
        struct Node* TAIL = (*head1)->prev;                                //if multiple nodes are present.
        struct Node* del = *head1;
        *head1 = (*head1)->next;
        (*head1)->prev = TAIL;                                              
        TAIL->next = *head1;                                                //making the links and breaking the links
        free(del);
    }
}


void c_deleteEnd(struct Node** head1){                          
    if(*head1 == NULL){
        printf("\n***List Already Empty.***\n");                        //if no node is present
    }
    else if((*head1)->next == *head1){                                  //if only one node is present
        c_deleteHead(head1);
    }
    else{
        struct Node* TAIL = (*head1)->prev;
        struct Node* del = TAIL;
        struct Node* BACK = TAIL->prev;                                 //tail is last node and back is 2nd last node.
        BACK->next = *head1;
        (*head1)->prev = BACK;                                          //we delete tail and add appropriate links to back pointer.
        free(TAIL);
    }
}


void c_deletePos(struct Node** head1, int info){
    if (c_element_present(head1, info)){                                // here we are checking if our element is present in the list or not, if element is present in the list then only we are going to insert the node.
        struct Node *temp = *head1;
        while (temp->data != info){                                     // reaching till our desired node.
            temp = temp->next;
        }
        if (temp->next == *head1){                                      // if we reach the last element , then we delete tail.
            c_deleteEnd(head1);
        }
        else if(temp->data == (*head1)->data){                          
            c_deleteHead(head1);                                        //if our info matches with the 1st node itself then we delete head.
        }
        else{
            struct Node* BACK = temp->prev;
            struct Node* FORW = temp->next;
            BACK->next = FORW;
            FORW->prev = BACK;                                          //if our node lies in somewhere middle the we use BAck and FORW pointer to make links and delete temp.
            free(temp);   
        }
    }
    else
    {
        printf("***ELEMENT NOT FOUND***\n");
    }
}

void menu_circularDouble()
{
    printf("\n\n=====CIRCULAR-DOUBLE-LIST=====");
    printf("\n1.Print Linked List.");
    printf("\n2.Enter at Begin.");
    printf("\n3.Enter at end.");
    printf("\n4.Enter at a position.");
    printf("\n5.Delete at Begin.");
    printf("\n6.Delete at End.");
    printf("\n7.Delete at a position.");
    printf("\n8.GOTO Main-Menu.");
    printf("\n9.Exit.");
    printf("\n==============================\n");

double_label:
    printf("\nEnter your choice (1-9) : ");
    int choice;

    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 9)
    { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
        printf("\n***ENTER A VALID INTEGER***.\n");
        while (getchar() != '\n')
            ; // Clear the input buffer
        goto double_label;
    }

    if (choice == 1)
    {
        print_circular(&head1);
        menu_circularDouble();
    }
    else if (choice == 2)
    {
        int value_c;
    c_double_insert_head:
        printf("\nEnter data of node : ");
        if (scanf("%d", &value_c) != 1)
        { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n')
                ; // Clear the input buffer
            goto c_double_insert_head;
        }
        else
        {
            c_insertAtHead(&head1, value_c); // even if our list is empty insert at head will work fine.
            print_circular(&head1);          // printing the single linked list
            menu_circularDouble();           // going back to menu of single linked list.
        }
    }
    else if (choice == 3)
    {
        int value_c;
    c_double_insert_end:
        printf("\nEnter data of node : ");
        if (scanf("%d", &value_c) != 1)
        { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n')
                ; // Clear the input buffer
            goto c_double_insert_end;
        }
        else
        {
            c_insertEnd(&head1, value_c);
            print_circular(&head1); // printing the double circular linked list
            menu_circularDouble();  // going back to menu of single linked list.
        }
    }
    else if(choice==4){
        int c_element, info;
        c_double_insert_val:
        printf("\nEnter Data of node : ");
        if (scanf("%d", &c_element) != 1){                              // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n'); // Clearing the input buffer
            goto c_double_insert_val;
        }

        c_double_insert_pos:
        printf("\nEnter INFO of node : ");
        if (scanf("%d", &info) != 1){                                       // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n');                                      // Clear the input buffer
            goto c_double_insert_pos;
        }

        c_insertAtPos(&head1,info,c_element);
        print_circular(&head1);
        menu_circularDouble();
    }
    else if(choice==5){
        c_deleteHead(&head1);
        print_circular(&head1);
        menu_circularDouble();
    }
    else if(choice==6){
        c_deleteEnd(&head1);
        print_circular(&head1);
        menu_circularDouble();
    }
    else if(choice==7){
        int info;
        c_double_del_pos:
        printf("\nEnter INFO of node : ");
        if (scanf("%d", &info) != 1)
        {                                                                           // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n');                                              // Clear the input buffer
            goto c_double_del_pos;
        }
        c_deletePos(&head1,info);
        print_circular(&head1);
        menu_circularDouble();
    }
    else if (choice == 8)
    {
        main_menu();
    }
    else if (choice == 9)
    {
        printf("Program Terminated succesfully.\n");
        exit(1);
    }
}

void main_menu()
{
    printf("\n=========MAIN-MENU==========\n");
    printf("1.Double Linked List.\n");
    printf("2.Circular Double Linked List.\n");
    printf("3.Exit Program.");
    printf("\n============================\n");

    int choice;

choice_label:
    printf("\nEnter your choice (1-3) : ");

    if (scanf("%d", &choice) != 1)
    { // Handling a case if user enters any alphabet , whether upper or lower case
        printf("\n***ENTER A VALID INTEGER***.\n");
        while (getchar() != '\n')
            ; // Clear the input buffer
        goto choice_label;
    }

    if (choice == 1)
    { // WRITE CODE FOR SINGLE LINKED LIST
        printf("\nyour choice : %d", choice);
        menu_doubleList();
    }
    else if (choice == 2)
    {
        menu_circularDouble();
    }
    else if (choice == 3)
    {
        printf("Program Terminated succesfully.\n");
        exit(0);
    }
    else
    { // if user enter a choice which is not there in the menu then we re-direct it to input again
        printf("\n***ENTER A VALID INTEGER***.\n\n");
        goto choice_label;
    }
}

int main()
{
    main_menu();
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node
{ // creating struct for our linked list, note: I will not use
    int data;
    struct Node *next;
};

struct Node *head = NULL; // Intializing head to null. Note: we are declaring this globally so that instead of making multiple copies of linked list , we work on only one list using refrencing.
struct Node* head1 = NULL;  //I am using 'head1' for circular linked list, and initializing thid node as global bcoz I will be using head1 by reference.4

void main_menu(); // Declaring our function here so that we don't get an error while function calling due to order of function defination.

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


void insertAtPos(struct Node **head, int element, int position)
{
    if (position < 0)                                       //If position is negative then handle it.
        printf("\n***NEGATIVE POSITION***\n");
    else if (*head == NULL)                                 //if no node is present then handle this case.
    {
        if (position == 0)
            insertAtHead(head, element);
        else
            printf("Node can't be inserted in EMPTY LIST.\n");
    }
    else if (position == 1)                                 //if we want to insert at next position of head, so instead of a loop , I handled it with a simple case
    {   
        struct Node *newNode = createNode(element);
        if (newNode != NULL)
        {
            newNode->next = (*head)->next;
            (*head)->next = newNode;
        }
    }
    else if (position == 0 && *head != NULL)                 //if pos = 0 , then we insert at head.
        insertAtHead(head, element);

    else
    {
        int count = 0;
        struct Node *newNode = createNode(element);
        struct Node *temp = *head;
        while (temp != NULL && count < position - 1)        //iterating to the node afte which we want to enter our node
        {
            temp = temp->next;
            count++;
        }
        if (count == position - 1 && temp != NULL)          //once our loo terminates , we are checking if we reached the desired node or if our list exhausted before reaching desired node.
        {
            struct Node *NEXT = temp->next;
            temp->next = newNode;
            newNode->next = NEXT;
        }
        else if(*head != NULL){                             //handle case if our list gets exhausted before reaching the actual location
            printf("\n***LIST TOO SHORT***.\n");
        }
    }
}

void deleteHead(struct Node** head){
    if(*head==NULL)                                         //if we have a empty list
        printf("***EMPTY LIST***\n");
    else{
        struct Node* del = *head;                           //else delete head.
        *head = (*head)->next;
        free(del);
    }

}


void deleteEnd(struct Node** head){
    if(*head==NULL)                                         //if list is already empty
        printf("**EMPTY LIST**\n");
    else if((*head)->next == NULL){                         //if only one node is there, I am deleting head only
        deleteHead(head);
    }
    else{                                                   
        struct Node* curr = *head;
        struct Node* prev = NULL;
        while(curr->next!=NULL){                             //iterating till we reaches the last node. Also using another 'prev' pointer which points to just immediate backward postion of curr,
            prev = curr;
            curr=curr->next;
        }   
        prev->next = NULL;                                   //once we reach last node, 'prev' will be pointing to 2nd last node , so we perform deletion.
        free(curr);
    }
}



void deleteAtPos(struct Node** head,int position){
    if(position<0){                                           //if we have negative position
        printf("Position can't be negative.\n");
    }
    else if(*head == NULL){                                   //we have empty list
        printf("**LIST ALREADY EMPTY, DELETION NOT POSSIBLE**\n");
    }
    else if(position==0){                                     //we are starting our postion from 1, and not from 0.
        printf("**NOT POSSIBLE**\n");
    }
    else if(position==1)                                      //position =1 is actually our head of the list.
        deleteHead(head);
    else{
        struct Node* curr = *head;
        struct Node* prev = NULL;
        int count = 0;
        while(curr!=NULL && count < position-1){               //we are using 2 pointers, once the loop terminates, curr will be pointing to node which has to be deleted.
            prev = curr;
            curr = curr->next;
            count++;
        }
        if(count == position-1 && curr!=NULL){                //check if we reached the desired node or if the list exhausted too early.
            prev->next = curr->next;                          //using 'prev' pointer deleting corresponding node.
            free(curr);
        }
        else{                                                 //else our list was too short for a position
            printf("\n**POSITION GREATER THAN LIST**\n");
        }
    }
}



void print_circular(struct Node** head1){                     //print function for circular list
    if(*head1 == NULL){                                       //if list is empty
        printf("\nLinked List : NULL\n");
        return;
    }
    struct Node* temp = *head1;
    printf("Linked List : ");
    do{                                                       //I am using do-while loop , bcoz if there is only 1 node in list and if I use while loop , then condition would not be met and list could not be printed.
        printf("%d->", temp->data);
        temp = temp->next;
    } while (temp != *head1);
    printf("\b \b");
    printf("\b \b\n");
}


void c_insertHead(struct Node** head1,int data){              //insert at head for circular list.
    struct Node* newNode = createNode(data);
    if(*head1 == NULL){
        *head1 = newNode;                                     //if list is empty then we will add a node, and point it to itself.
        (*head1)->next = *head1;
    }
    else{
        struct Node* tail = *head1;                           //if there are multiple eelemnts
        while(tail->next != *head1){
            tail = tail->next;
        }
        tail->next = newNode;                                  //then we use loop and iterate till end of list i.e 'tail' , then add the node to head and make/break corresponding links.
        newNode->next = *head1;
        *head1 = newNode;
    }
}


void c_insertEnd(struct Node** head1,int data){                //insert at end for circular linked list.
    struct Node* newNode = createNode(data);
    if(*head1 == NULL){                                         //if we have empty list then we simply insert at head.
        c_insertHead(head1,data);
    }
    else{                                                       //if multiple nodes are there.
        struct Node* tail = *head1;
        while(tail->next != *head1){                            //creating a tail pointer which will reach at the end of list(!=NULL)
            tail = tail->next;
        }
        tail->next = newNode;                                   //make/break the corresponding link.
        newNode->next = *head1;
    }
    
}

void c_insertAtPos(struct Node** head1,int position,int element){
    if (position < 0)                                       //If position is negative then handle it.
        printf("\n***NEGATIVE POSITION***\n");
    else if(position==0){
        c_insertHead(head1,element);
        return;
    }
    else if (*head1 == NULL)                                 //if no node is present then handle this case.
    {
        if (position == 0)
            c_insertHead(head1, element);
        else
            printf("Node can't be inserted in EMPTY LIST.\n");
        return;
    }
    else if (position == 1)                                 //if we want to insert at next position of head, so instead of a loop , I handled it with a simple case
    {   
        struct Node *newNode = createNode(element);
        if (newNode != NULL)
        {
            if((*head1)->next != NULL){                    //if there are more then one elements in the list. 
                newNode->next = (*head1)->next;             //then simply add between them
                (*head1)->next = newNode;
            }
            else{                                           //if only one element is there in the list
                (*head1)->next = newNode;
                newNode->next = *head1;
            }
        }
    }
    // else if (position == 0 && *head1 != NULL)                 //if pos = 0 , then we insert at head.
    //     c_insertHead(head1, element);
    else{
        int count = 0;
        struct Node *newNode = createNode(element);
        struct Node *temp = *head1;
        while (temp->next != *head1 && count < position - 1){        //iterating to the node afte which we want to enter our node
        
            temp = temp->next;
            count++;
        }
        if (count == position - 1 && temp != NULL){          //once our loop terminates , we are checking if we reached the desired node or if our list exhausted before reaching desired node.
            struct Node *NEXT = temp->next;
            temp->next = newNode;
            newNode->next = NEXT;
        }
        else if(temp != NULL){                             //handle case if our list gets exhausted before reaching the actual location
            printf("\n***LIST TOO SHORT***.\n");
        }
    }
}


void c_deleteHead(struct Node** head1){                    //deleting head of circular linked list.
    if(*head1 == NULL){                                     //empty list spotted.
        printf("\n**LIST ALREADY EMPTY**\n");
    }
    else if((*head1)->next == *head1){                     //only one node is there. Then after deleting the node I am setting head to NULL.
        free(*head1);
        *head1 = NULL;
        return;
    }
    else{
        struct Node* curr = *head1;                         //if multiple nodes are there in the list.
        while(curr->next != *head1){                        //using 'curr' pointer I am reaching at last node
            curr = curr->next;
        }
        struct Node* del = *head1;                          //deleting head.
        *head1 = (*head1)->next;
        curr->next = *head1;                                //using 'curr' which denotes the last node, I am fixing the connection.
        free(del);
    }
}




void c_deleteEnd(struct Node** head1){                      //deleting end of circular linked list
    if(*head1 == NULL){                                     //if list is already empty
        printf("\n**LIST ALREADY EMPTY**\n");
    }
    else if((*head1)->next == *head1){                      //only one node is there. Then free memory and set head = NULL
        free(*head1);
        *head1 = NULL;
        return;
    }   
    else{
        struct Node* tail = *head1;                         //if multiple nodes are there.
        while(tail->next->next != *head1){                  //reach till 2nd last of the linked list
            tail = tail->next;
        }
        free(tail->next);                                   //delete next node of 2nd last element and fix the link.
        tail->next = *head1;
    }
}



void c_deleteAtPos(struct Node** head1,int position){
    if (position <= 0)                                       //If position is negative then handle it.
        printf("\n***POSITION NOT POSSIBLE***\n");
    else if(*head1 == NULL){                                 //if no node is there.
        printf("\n***List Already Empty***\n");
    }
    // else if((*head1)->next == *head1){                        //if only one node is there then delete head/tail, I deleted head here.
    //     c_deleteHead(head1);
    //     return;
    // }
    else if(position == 1){                                   //if want to delete 1st node , then simply delete the head.
        c_deleteHead(head1);
    }
    else{
        struct Node* curr = *head1;
        struct Node* prev = NULL;
        int count = 0;
        while(curr->next != *head1 && count < position-1){               //we are using 2 pointers, once the loop terminates, curr will be pointing to node which has to be deleted.
            prev = curr;
            curr = curr->next;
            count++;
        }
        if(count == position-1 && curr!=NULL){                //check if we reached the desired node or if the list exhausted too early.
            prev->next = curr->next;                          //using 'prev' pointer fixing the link and then deleting the node.
            free(curr);
        }
        else{                                                 //else our list was too short for a position
            printf("\n**POSITION GREATER THAN LIST**\n");
        }
    }
}



void menu_circularList(){
    printf("\n\n=====CIRCULAR-LINKED-LIST=====");
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

    if(choice==1){
        print_circular(&head1);
        menu_circularList();
    }
    else if(choice==2){
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
            c_insertHead(&head1, value_c); // even if our list is empty insert at head will work fine.
            print_circular(&head1);          // printing the single linked list
            menu_circularList(); // going back to menu of single linked list.
        }
    }
    else if(choice==3){
        int value_c;
        c_insert_end:
        printf("\nEnter data of node : ");
        if (scanf("%d", &value_c) != 1){ // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n')
                ; // Clear the input buffer
            goto c_insert_end;
        }
        else
        {
            c_insertEnd(&head1, value_c); // even if our list is empty insert at head will work fine.
            print_circular(&head1);          // printing the single linked list
            menu_circularList(); // going back to menu of single linked list.
        }
    }
    else if(choice==4){
        int c_element, c_position;
    c_insert_val:
        printf("\nEnter Data of node : ");
        if (scanf("%d", &c_element) != 1){ // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n')
                ; // Clearing the input buffer
            goto c_insert_val;
        }

    c_insert_pos:
        printf("\nEnter Position : ");
        if (scanf("%d", &c_position) != 1)
        { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n'); // Clear the input buffer
            goto c_insert_pos;
        }

        c_insertAtPos(&head1, c_position, c_element);
        print_circular(&head1);          // printing the circular single linked list 
        menu_circularList();
    }
    else if(choice==5){
        c_deleteHead(&head1);
        print_circular(&head1); // printing the single linked list
        menu_circularList();
    }
    else if(choice==6){
        c_deleteEnd(&head1);
        print_circular(&head1); // printing the single linked list
        menu_circularList();
    }
    else if(choice==7){
        int c_position;
        c_del_pos:
        printf("\nEnter Position to be DELETED : ");
        if (scanf("%d", &c_position) != 1)
        { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n'); // Clear the input buffer
            goto c_del_pos;
        }
        c_deleteAtPos(&head1,c_position);
        print_circular(&head1);
        menu_circularList();
    }
    else if(choice==8){
        main_menu();
    }
    else if(choice==9){
        printf("Program Terminated succesfully.\n");
        exit(1);
    }
}


void menu_singleList()
{
    printf("\n\n=======SINGLE-LINKED-LIST=======");
    printf("\n1.Print Linked List.");
    printf("\n2.Enter at Begin.");
    printf("\n3.Enter at end.");
    printf("\n4.Enter at a position.");
    printf("\n5.Delete at Begin.");
    printf("\n6.Delete at End.");
    printf("\n7.Delete at a position.");
    printf("\n8.GOTO Main-Menu.");
    printf("\n9.Exit.");
    printf("\n================================\n");

single_label:
    printf("\nEnter your choice (1-9) : ");
    int choice;

    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 9)
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
        int element, position;
    insert_val:
        printf("\nEnter Data of node : ");
        if (scanf("%d", &element) != 1)
        { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n')
                ; // Clearing the input buffer
            goto insert_val;
        }

    insert_pos:
        printf("\nEnter Position : ");
        if (scanf("%d", &position) != 1)
        { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n')
                ; // Clear the input buffer
            goto insert_pos;
        }

        insertAtPos(&head, element, position);
        print_list(&head); // printing the single linked list
        menu_singleList();
    }
    else if (choice == 5){
        deleteHead(&head);
        print_list(&head); // printing the single linked list
        menu_singleList();
    }
    else if (choice == 6){
        deleteEnd(&head);
        print_list(&head); // printing the single linked list
        menu_singleList();
    }
    else if (choice == 7){
        int position;
        del_pos:
        printf("\nEnter Position to be DELETED : ");
        if (scanf("%d", &position) != 1)
        { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n')
                ; // Clear the input buffer
            goto del_pos;
        }
        deleteAtPos(&head,position);
        print_list(&head);
        menu_singleList();
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
    printf("1.Single Linked List.\n");
    printf("2.Circular Linked List.\n");
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
    {
        // WRITE CODE FOR SINGLE LINKED LIST
        printf("\nyour choice : %d", choice);
        menu_singleList();
    }
    else if (choice == 2)
    {
        menu_circularList();
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
    main_menu(); // calling main menu function
    return 0;
}
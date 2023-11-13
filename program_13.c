#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define size 20

// int top = -1;                                       //top refers to top of stack

struct Node{                                        //creating a struct for tree
    int data;
    struct Node* left;
    struct Node* right;
};



struct Node* createTree(){                          //this function will create a tree & return the root.
    struct Node* root = (struct Node*)malloc(sizeof(struct Node));      //dynamically creating a local root.
    int data;
    printf("Enter Node data : ");
    scanf("%d",&data);
    if(data == -1)                                  //if user enters -1 then no further tree has to be made, so assign NULL to children
        return NULL;

    root->data = data;                              //assigning data to current root's data.
    
    printf("Enter data for left of : %d\n",data);
    root->left = createTree();                      //recursivly creating left subtree.
    printf("Enter data for right of : %d\n",data);
    root->right = createTree();                     //recursilvely creating right subtree.
    return root;                                    //returning root.
}


void preoreder_stack(struct Node* root){
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    int top = -1;                                     //top refers to top of stack.
    struct Node* stack[size];                         //creating a stack using array.
    stack[++top] = NULL;                              //pushing null to empty stack
    struct Node* ptr = root;                          //setting ptr to root.

    while(ptr != NULL){
        printf("%d  ",ptr->data);               //processing node first , NLR.
        if(ptr->right)                          //if right child exists.
            stack[++top] = ptr->right;                //then push right child to stack
        if(ptr->left)                           //if left child exists.
            ptr = ptr->left;                    //then set ptr to left child for further traversal.
        else{                                   //if left child does not exists
            ptr = stack[top];                   //then set ptr to top of stack & pop it. now iteration will start from this ptr again in next while loop iteration.
            top--;
        }
    }
}

void inorder_stack(struct Node* root){
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    struct Node* stack[size];                   //declaring a stack
    int top = -1;
    stack[++top] = NULL;
    struct Node* ptr = root;                           //ptr points to root
    struct Node* temp = root;                          //taking a temp pointer which will be used for stack elements
    while(temp!=NULL || top<0 ){           //if stack is not empty or temp does not hit NULL.
        while(ptr!=NULL){                       
            stack[++top] = ptr;                       //push ptr if any left child exists.
            ptr = ptr->left;                    //also keep on updating left child
        }
        temp = stack[top];                        //temp will be used to access stack elements which has to be processed.

        if(temp==NULL)                          //if stack has only NULL value, then exit.
            return;
        top--;                               //popping current / temp element
        printf("%d  ",temp->data);              //printing current element (temp still holds current element).
        if(temp->right)                         //if any right child of popped element exists then set ptr to it. After which loop will again start from it with same logic.
            ptr = temp->right;
    }
}



void postorder_stack(struct Node* root){   
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
  
    int top = -1;                  
    struct Node* stack[size];                                       //creating an empty stack
    struct Node* ptr = root;                                      //setting ptr to root.
    do{                                                    //this do-while loop will run untill stack does not becomes empty.
        while(ptr!=NULL){
            if(ptr->right)                                 //if current element's right child exists then push that right child to stack.
                stack[++top] = ptr->right;
            stack[++top] = ptr;                                  //now push the current ptr to stack 
            ptr = ptr->left;                               //and set ptr to its left child for further traversal
        }
                                                            //the above while loop will be over when no left child can be traversed.
        ptr = stack[top];                                    
        top--;                                           //pop top of stack
        if(ptr->right && top>=0 && ptr->right == stack[top]){  //if any right child of ptr exists whose right child's values is equal to top of stack then 
            top--;                                       //then pop that right child.
            stack[++top] = ptr;                                   //and push the current ptr.
            ptr = ptr->right;                               //now we will start from that element's right child 
        }
        else{
            printf("%d  ",ptr->data);                           //if no right child of ptr exists then simply print its data
            ptr = NULL;                                     //and set its data to null
        }
    }while (top>=0);
}



bool search_tree(struct Node* root,int element){
    if(root == NULL)
        return false;
    if(root->data == element)
        return true;
    if(element < root->data)
        return search_tree(root->left,element);
    else{
        return search_tree(root->right,element);
    }
    return false;
}


void menu_Tree(struct Node* root){
    printf("\n\n=====Binary Search Tree=====");
    printf("\n1.Insertion");
    printf("\n2.Inorder Traversal.");
    printf("\n3.Preorder Traversal.");
    printf("\n4.Postorder Traversal.");
    printf("\n5.GOTO Main-Menu.");
    printf("\n6.Exit.");
    printf("\n=============================\n");

    circular_label:
    printf("\nEnter your choice (1-9) : ");
    int choice;

    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 9)
    { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
        printf("\n***ENTER A VALID INTEGER***.\n");
        while (getchar() != '\n'); // Clear the input buffer
        goto circular_label;
    }

    if(choice==1){
        root = createTree();
        menu_Tree(root);
    }

    // else if(choice==3){
    //     int element;
    //     search:
    //     printf("\nEnter element to be searched : ");
    //     if (scanf("%d", &element) != 1){ // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
    //         printf("\n***ENTER A VALID INTEGER***.\n");
    //         while (getchar() != '\n'); // Clear the input buffer
    //         goto search;
    //     }
    //     if(!search_tree(root,element))
    //         printf("\nElement NOT FOUND!");
    //     else    
    //         printf("\nElement PRESENT!");
    //     menu_Tree(root);
    // }
    else if(choice==2){
        printf("\nIn-Order : ");
        inorder_stack(root);
        menu_Tree(root);
        
    }
    else if(choice==3){
        printf("\nPre-Order : ");
        preoreder_stack(root);
        menu_Tree(root);
    }
    else if(choice==4){
        printf("\nPost-Order : ");
        postorder_stack(root);
        menu_Tree(root);
    }
 
    else if(choice==5){
        menu_Tree(root);
    }
    else if(choice==6){
        printf("Program Terminated succesfully.\n");
        exit(1);
    }
}
int main(){
    struct Node* root = NULL;
    menu_Tree(root);
    return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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


void preorder(struct Node* root){                   //preorder uses NLR approach
    if(root == NULL)                                //base case
        return;
    printf("%d  ",root->data);                      //N
    preorder(root->left);                           //L
    preorder(root->right);                          //R
}

void inorder(struct Node* root){                    //inorder uses LNR approach.
    if(root == NULL)                                //base case.
        return;
    inorder(root->left);                            //L
    printf("%d  ",root->data);                      //N
    inorder(root->right);                           //R
}



void postorder(struct Node* root){                  //postorder uses LRN approach.
    if(root == NULL)                                //base case
        return;
    postorder(root->left);                          //L
    postorder(root->right);                         //R
    printf("%d  ",root->data);                      //N
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
    printf("\n2.Deletion");
    printf("\n3.Search.");
    printf("\n4.Inorder Traversal.");
    printf("\n5.Preorder Traversal.");
    printf("\n6.Postorder Traversal.");
    printf("\n7.GOTO Main-Menu.");
    printf("\n8.Exit.");
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
    else if(choice==2){
        
    }
    else if(choice==3){
        int element;
        search:
        printf("\nEnter element to be searched : ");
        if (scanf("%d", &element) != 1){ // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n'); // Clear the input buffer
            goto search;
        }
        if(!search_tree(root,element))
            printf("\nElement NOT FOUND!");
        else    
            printf("\nElement PRESENT!");
        menu_Tree(root);
    }
    else if(choice==4){
        printf("\nIn-Order : ");
        if(root==NULL)
            printf("***Empty***\n");
        else
            inorder(root);
        menu_Tree(root);
        
    }
    else if(choice==5){
        printf("\nPre-Order : ");
        if(root==NULL)
            printf("***Empty***\n");
        else
            preorder(root);
        menu_Tree(root);
    }
    else if(choice==6){
        printf("\nPost-Order : ");
        if(root==NULL)
            printf("***Empty***\n");
        else
            postorder(root);
        menu_Tree(root);
    }
    else if(choice==7){
        menu_Tree(root);
    }
    else if(choice==8){
        printf("Program Terminated succesfully.\n");
        exit(1);
    }
}
int main(){
    struct Node* root = NULL;
    menu_Tree(root);
    return 0;
}

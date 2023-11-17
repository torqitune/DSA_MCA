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




bool search_tree(struct Node* root,int element){             //function to search an element
    if(root == NULL)                                            //base case , if empty tree.
        return false;
    if(root->data == element)                               //another base case , if we found the element.
        return true;
    if(element < root->data)                                //if our element is in left subtree.
        return search_tree(root->left,element);             //then make recursive call to left.
    else{                                                   //else if the node is in right subtree then make right recursive call.
        return search_tree(root->right,element);
    }   
    return false;                                           //if none of the conditions are satisfied then we have not found our element.
}


struct Node* del_tree(struct Node* root,int element){                      //this will return then minimum element from left subtree of BST.
    if(root == NULL)                                                       //if our list is already empty.
        printf("**EMPTY TREE.**\n");
    if(element < root->data)                                                //if element to be deleted is present in left subtree.
        root->left = del_tree(root->left,element);                          //then reach till that node while also updating the current node.
    else if(element > root->data)                                           //if element is to be deleted is present in right subtree.
        root->right = del_tree(root->right,element);                        //then reach till that node and keep on updating the current node.
    else{                                                                   //now we are at position where node has to be deleted.
        if(root->left==NULL && root->right==NULL)                           //check if the node is leaf node or not, if it is a leaf node then return null so that it becomes null at that postion.
            return NULL;
        if(root->left==NULL || root->right==NULL){                          //if the node has one child either left or right may be present.
            if(root->left)                                                  //if a left child is present then delete the current node and make the link of its left child.
                return root->left;  
            else                                                            //if a right child is present then delete the node and make a linkg of its right child.
                return root->right;
        }
                                                                            //but if the node has both left and right child then delete we will find the maximum from the left subtree to replace its value.
        struct Node* temp = root->left;                                     //making temp to initialize with left subtree where it will find maximum child.
        while(temp->right != NULL)                                          //reaching till that node using while loop.
            temp = temp->right;
        root->data = temp->data;                                            //we replace the node to be deleted with maximum element from left subtree
        root->left = del_tree(root->left,temp->data);                       //now we will use recursion to delete that maximum node which we replaced with the node to be deleted.
    }
    return root;
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
        int element;
        delete:
        printf("\nEnter element to be deleted : ");
        if (scanf("%d", &element) != 1){ // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n'); // Clear the input buffer
            goto delete;
        }
        if(root==NULL)
            printf("\n***EMPTY TREE!***\n");
        else if(!search_tree(root,element)){
            printf("\n***Element NOT IN TREE***!");           
        }
        else{
            root = del_tree(root,element);
            printf("\n==DELETION DONE==");
        }
        menu_Tree(root);
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

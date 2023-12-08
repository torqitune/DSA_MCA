#include<stdio.h>
#include<stdlib.h>

struct Node{                                        //creating a struct for tree
    int data;
    struct Node* left;
    struct Node* right;
};

int count = 0;                           //count the total no. of nodes present in the tree.

struct Node* createNode(int data){              //creat only single node.
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));      //dynamically creating a temporary node.
    temp->data = data;  //set data
    temp->left = NULL;
    temp->right = NULL;             //both left and right of node are set to NULL.
    return temp;
}


struct Node* createTree(){                          //this function will create a tree & return the root.
    struct Node* root = (struct Node*)malloc(sizeof(struct Node));      //dynamically creating a local root.
    int data;
    printf("Enter Node data : ");
    scanf("%d",&data);
    if(data == -1)                                  //if user enters -1 then no further tree has to be made, so assign NULL to children
        return NULL;

    root->data = data;                              //assigning data to current root's data.
    count++;

    printf("Enter data for left of : %d\n",data);
    root->left = createTree();                      //recursivly creating left subtree.
    printf("Enter data for right of : %d\n",data);
    root->right = createTree();                     //recursilvely creating right subtree.
    return root;                                    //returning root.
}

int i = 0;                              //this index will keep track of inorder array index.
void inorder(struct Node* root,int *arr){                    //inorder uses LNR approach.
    if(root == NULL)                                //base case.
        return;
    inorder(root->left,arr);                            //L
    // printf("%d  ",root->data);                      //N
    arr[i++] = root->data;                      //filling inorder traversal to our array.
    inorder(root->right,arr);                           //R
}

struct Node* recur(int *arr,int start,int end){         //this function will return root(here temp) of the AVL tree.
    if(start>end)                           //base case , if this happens , then NULL will be set.
        return NULL;
    if(start==end){                         //if this happens then
        struct Node* temp = createNode(arr[start]);     //create a temporary node whose value can either be arr[start] or arr[end] coz both are equal.
        return temp;                                       //return this created node.
    }
    int mid = (start+end)/2;                            //else we find mid from our array , this value will be treated as current root's value.
    struct Node* temp = createNode(arr[mid]);           //make node for this mid.
    temp->left = recur(arr,start,mid-1);    //recursiveley call for temp's left subtree , setting its left node .
    temp->right = recur(arr,mid+1,end);     //doing same for the right subtree also.
    return temp;                            //return this created node.
}



void preorder(struct Node* root){                   //preorder uses NLR approach
    if(root == NULL)                                //base case
        return;
    printf("%d  ",root->data);                      //N
    preorder(root->left);                           //L
    preorder(root->right);                          //R
}


int main(){
    printf("\n***Enter Node in BST***\n");
    struct Node* root = NULL;           //create our root node.
    root = createTree();                //create a tree for it.
    int arr[count];                     //once we get value of count(total no. of nodes in tree) then make an array of that size i.e count.
    inorder(root,arr);                  //calling inorder fucntion , here our array will have inorder values
    printf("\nInorder of BST: ");           //printing inorder of our BST.
    for(int j = 0 ; j<count ; j++){
        printf("%d ",arr[j]);
    }
    root = recur(arr,0,count-1);        //calling our function which will return root of our AVL.
    printf("\n\nPre-order of AVL TREE : ");
    preorder(root);                     //printing preoder of AVL.
    return 0;
}
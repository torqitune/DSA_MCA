#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertionSort(int *arr,int size){
    for(int i = 1; i<size ; i++){           //this loop will start from 1st indez bcoz if we start from 0th index then we have no element left to compare on left side.
        int element = arr[i];               //storing element which we want to delete.
        for(int j = i-1 ; j>=0 ; j--){      //this loop will compare element with all element of its left side
            if(element < arr[j])        //if the element is less then current element then swap them, do it for all iteration 
                swap(&arr[j],&arr[j+1]);
        }
    }
}



int partition(int *arr,int left,int right){
    int pivot=arr[left];                                //here we are setting pivot as the first element
    int start=left;                     //start is for element greater then pivot
    int end=right;                      //end is for element less then pivot.
    while(start<end){
        while(arr[start]<=pivot){                       //after this loop terminates start will be pointing to element which is greater then the pivot element and needs to be swapped.
            start++;
        } 
        while(arr[end]>pivot){                           //after this loop terminates end will be pointing to element which is less then the pivot element and needs to be swapped.
            end--;
        }
        if(start<end){
            swap(&arr[start],&arr[end]);                  //here we swap the elements so that they now ordered correcty compared to the pivot.
        } 
    }
    swap( &arr[left] , &arr[end] );                           //at last we swap the pivot element to end position, i.e we have now placed the pivot element to its correct poisition.
    return end;                                         //return the index of the pivot element.

}


void quickSort(int *arr,int start,int end){
    if(start<end){                          //this condtion checkes that atleast two elements should be there , bcoz 1 element is itself considered sorted.
        int pivot = partition(arr,start,end); //this function will return index of pivot element after placing it at correct postion .
        quickSort(arr,start,pivot-1);           //sorting or setting the pivot element to its correct position , this function will set/sort the left part.
        quickSort(arr,pivot+1,end);      //sorting or setting the pivot element to its correct position , this function will set/sort the right part.
    }
}

void Sort(int *arr,int start,int mid,int end){                  //this function sorts array for each call
    int n1 = mid - start + 1;                       //this will give us size of left array which has to be created.
    int n2 = end - mid;                             //this wiil give use size of right subtree which has to be created.

    int L[n1];                                  //creating left array which will hold elements from start till mid.
    int R[n2];                                  //creating right array which will hold value from mid+1 till end
    
    for(int i = 0 ; i<n1 ; i++){            //here we are copying data from start till mid to this Left array , NOTE: left and right are temporary arrays for each iteration.
        L[i] = arr[start + i];
    }
    for(int j=0 ; j<n2 ; j++){              //here we are copying data from mid+1 till end.
        R[j] = arr[mid+1+j];
    }

    int i = 0;      //this index will be used for LEFT array.
    int j = 0;      //this index will be used for Right array.
    int k = start;  //this index will be used for sorted array.

    while(i<n1 && j<n2){        //this while loop will run untill one of either LEFT or Right array is exhausted.
        if(L[i] <= R[j]){       //if left's element is less then right's element
            arr[k] = L[i];      //then store it in actual array.
            i++;                //increment i , so that next element of LEFT can be accessed.
        }
        else{                   //else element of left is greater then element of right.
            arr[k] = R[j];      //assign Right's element to actual array.
            j++;                //increment j so that next element of right array can be accessed.
        }
        k++;                    //in this while we are sure the we filling our actual array , so each time we will increment k so that next element can be insert in actual array at its correct sorted position.
    }
    while (i < n1) {            //if any element from left arrray remains while right is completlye exhausted then fill those in actual array without comparing
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {            //same goes for right array too.
        arr[k] = R[j];
        j++;
        k++;
    }
}


void mergeSort(int arr[],int start,int end){           //taking copy of our array.
    if(start>=end)
        return;
    int mid = (start + end)/2;                          //finding mid of array.
    mergeSort(arr,start,mid);                           //recursive call from start till mid.
    mergeSort(arr,mid+1,end);                           //recursive call beyond mid till end.
    Sort(arr,start,mid,end);                            //after we return from dividing our array elements , its time to sort them.
}



void menu(int arr[],int size){
    printf("\n\n=====SORTING TECHNIQUES=====");
    printf("\n1.Insertion Sort");
    printf("\n2.Merge Sort");
    printf("\n3.Quick Sort.");
    printf("\n4.GOTO Main-Menu.");
    printf("\n5.Exit.");
    printf("\n=============================\n");

    circular_label:
    printf("\nEnter your choice (1-5) : ");
    int choice;

    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 5)
    { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
        printf("\n***ENTER A VALID INTEGER***.\n");
        while (getchar() != '\n'); // Clear the input buffer
        goto circular_label;
    }

    if(choice==1){
        insertionSort(arr,size);
        printf("\nSorted Array : ");
        for(int i = 0 ; i<size ; i++){
            printf("%d ",arr[i]);
        }
        exit(1);
    }
    else if(choice==2){
        mergeSort(arr,0,size-1);
        printf("\nSorted Array : ");
        for(int i = 0 ; i<size ; i++){
            printf("%d ",arr[i]);
        }
        exit(1);
    }
    else if(choice==3){
        quickSort(arr,0,size-1);
        printf("\nSorted Array : ");
        for(int i = 0 ; i<size ; i++){
            printf("%d ",arr[i]);
        }
        exit(1);
    }
    else if(choice==4){
      
        
    }
    else if(choice==5){
        
    }
    else if(choice==6){
        
    }
    else if(choice==7){
    }
    else if(choice==8){
        printf("Program Terminated succesfully.\n");
        exit(1);
    }
}




int main(){
    int size = 0;
    printf("Enter size of array : ");
    scanf("%d",&size);

    if(size==0){
        printf("\n***EMPTY ARRAY, CAN'T PROCEED!***\n");
        return 0;
    }
    
        int arr[size];
        printf("\n***Enter Array***\n");
        for(int i = 0 ; i<size ; i++){
            printf("Index %d : ",i);
            scanf("%d",&arr[i]);
        }
        printf("\nArray : ");
        for(int i = 0 ; i<size ; i++){
            printf("%d ",arr[i]);
        }
    
    menu(arr,size);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define size 50
int array[size];
int curr = 0; // curr will always point to the last index (which is empty).

void print_array(int *curr)
{
    if (*curr == 0)
    {
        printf("\nArray : EMPTY"); // here we are passing curr by reference
    }
    else
    {
        printf("\nArray : "); // here we are passing curr by reference
        for (int i = 0; i < *curr; i++)
        {
            printf("%d ", array[i]);
        }
        printf("\n");
    }
}

void insertStart(int *curr, int data)
{
    for (int i = *curr; i >= 1; i--)
    {
        array[i] = array[i - 1]; // shifting all elements after 0th index to one position right.
    }
    array[0] = data; // adding the data to 0th index
    (*curr)++;       // now curr is incremented.
}

void insertEnd(int *curr, int data)
{
    array[(*curr)++] = data; // just add the element at last index and increment the curr
}

void insertPos(int *curr, int index, int data)
{
    if (index > *curr)
    {
        printf("\n***Array too short***\n"); // if users enters a index value greater then size of array
    }
    else if (index < 0)
    {
        printf("\n***INVALID INDEX***\n"); // if users enters a invalid index.
    }
    else if (index == *curr)
    {
        insertEnd(curr, data); // if user enters last index value then insert element at end.
    }
    else
    {
        for (int i = *curr; i > index; i--)
        {
            array[i] = array[i - 1]; // if index lies somewhere in middle then iterate from last index till that position while shiftin each element one positino right.
        }
        array[index] = data; // enter element at our desired poistion.
        (*curr)++;
    }
}

void deleteEnd(int *curr)
{
    if (*curr <= 0)
    {
        printf("\n**NOT POSSIBLE.**\n");
    }
    else
    {
        (*curr)--; // to delete last element just decrement curr so that in print statement last element is not printed.
    }
}

void deleteStart(int *curr)
{
    if (*curr <= 0)
    {
        printf("\n**NOT POSSIBLE.**\n"); // if arrays is empty
    }
    else
    {
        for (int i = 0; i < *curr; i++)
        {
            array[i] = array[i + 1]; // shift all elements one position left
        }
        (*curr)--; // decrement curr
    }
}

void deletePos(int *curr, int index)
{
    if (index >= *curr)
    {
        printf("\n***Array too short***\n"); // if users enters a index value greater then size of array
    }
    else if (index < 0)
    {
        printf("\n***INVALID INDEX***\n"); // if users enters a invalid index.
    }
    else
    {
        for (int i = index; i < *curr; i++)
        {
            array[i] = array[i + 1]; // else, starting from index position shift all element to one position left .
        }
        (*curr)--;
    }
}

void linearSearch(int *curr, int data)
{
    if (*curr <= 0)
    {
        printf("\n***EMPTY ARRAY***\n"); // if array is null
    }
    else
    {
        int index = 0;
        for (int i = 0; i < *curr; i++)
        {
            if (array[i] == data)
            {
                printf("\nElement found at index : %d\n", index);
                return;
            }
            else
            {
                index++;
            }
        }
        printf("\n**NOT FOUND**\n");
    }
}

void menu_array()
{
    printf("\n\n=======ARRAY=======");
    printf("\n1.Print Array.");
    printf("\n2.Enter an start.");
    printf("\n3.Enter at end.");
    printf("\n4.Enter at specific position.");
    printf("\n5.Delete End.");
    printf("\n6.Delete Start.");
    printf("\n7.Delete at specific position.");
    printf("\n8.Linear Search.");
    printf("\n9.Exit.");
    printf("\n====================\n");

single_label:
    printf("\nEnter your choice (1-6) : ");
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
        print_array(&curr);
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
            insertStart(&curr, value); // add element to 0th index.
            print_array(&curr);        // printing array.
            menu_array();              // returning menu again.
        }
    }
    else if (choice == 3)
    {
        int value;
    insert_end:
        printf("\nEnter data : ");
        if (scanf("%d", &value) != 1)
        { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n')
                ; // Clear the input buffer
            goto insert_end;
        }
        else
        {
            insertEnd(&curr, value); // add element at last index value
            print_array(&curr);      // printing array.
            menu_array();            // returning menu again.
        }
    }
    else if (choice == 4)
    {
        int data, index;
    array_data:
        printf("\nEnter Data of node : ");
        if (scanf("%d", &data) != 1)
        { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n')
                ; // Clearing the input buffer
            goto array_data;
        }

    array_index:
        printf("\nEnter index : ");
        if (scanf("%d", &index) != 1)
        { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n')
                ; // Clear the input buffer
            goto array_index;
        }

        insertPos(&curr, index, data);
        print_array(&curr);
        menu_array();
    }

    else if (choice == 5)
    {
        deleteEnd(&curr);
        print_array(&curr);
        menu_array();
    }

    else if (choice == 6)
    {
        deleteStart(&curr);
        print_array(&curr);
        menu_array();
    }

    else if (choice == 7)
    {
        int index;
    index:
        printf("\nEnter index : ");
        if (scanf("%d", &index) != 1)
        { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n')
                ; // Clear the input buffer
            goto index;
        }

        deletePos(&curr, index);
        print_array(&curr);
        menu_array();
    }

    else if (choice == 8)
    {
        int data;
    search:
        printf("\nEnter element to be SEARCHED : ");
        if (scanf("%d", &data) != 1)
        { // Handling a case if user enters any alphabet or choice which is out of range , then we re-direct user to input choice again.
            printf("\n***ENTER A VALID INTEGER***.\n");
            while (getchar() != '\n')
                ; // Clear the input buffer
            goto search;
        }

        linearSearch(&curr, data);
        print_array(&curr);
        menu_array();
    }
    else if (choice == 9)
    {
        printf("Program Terminated succesfully.\n");
        exit(1);
    }
}
int main()
{
    menu_array();
    return 0;
}
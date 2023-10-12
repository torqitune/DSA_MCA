#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
#define size 50



int precedence(char ch){                    //this function will return the precedence oreder of the opertor.
    if(ch=='+' || ch=='-')
        return 1;
    else if(ch=='/' || ch=='*')
        return 2;
    else if(ch=='^')
        return 3;
    else                                    //if we encounter an opening/closing brace then my code will consider it to be operator too , so to avoid calculating there order I set the order to least i.e -1 so all other operators have higher precedence then ')' or '('
        return -1;
}


bool isOperater(char ch){                   //check if the current character is an operator or not
    if(ch=='+' || ch=='-' || ch=='/' || ch=='*' || ch=='^' || ch=='/' )
        return true;
    else
        return false;
}


void evaluate(char *s){
    int stack[size];                        //creating a stack 
    int top=-1;
    // printf("\nIn evaluate: %s",s);
    for(int i = 0 ; s[i]!='\0' ; i++){      //traversing list untill we dont encounter last character
        if(s[i]==' ')
            continue;
        if(!isOperater(s[i])){               //if current character is an operand then simply push it into the stack
            stack[++top] = s[i]-'0';       //converting the charachters into integers coz the postfix expression we will recieve is a string and we have to perform operations on integers.
        }
        else{                               //else it is an operator 
            int val2 = stack[top--];        //pop two elements from the stack, coz on these two values we will perform our operations.
            int val1 = stack[top--];
            if(s[i] =='+')
                stack[++top] = (val1 + val2);//perform addition operation on val1 & val2 and push the result back to stack, perform this for others also.
            else if(s[i]=='-')
                stack[++top] = (val1 - val2);
            else if(s[i]=='*')
                stack[++top] = (val1 * val2);
            else if(s[i]=='/')
                stack[++top] = (val1 / val2);
            else if(s[i] == '^')
                stack[++top] = (pow(val1,val2) );       //this section has some problem, integer related problem
        }
    }
    printf("\nEvaluated answer : %f",stack[top]);
}


void infixToPostfix(char *s){\
    // printf("%s",s);
    char pf[size]="";                     //creating an empty string to store postfix expression
    int stack[size];                    //creating a stack
    int top = -1;                       //stack top
    for(int i = 0 ; s[i]!='\0' ; i++){  //traverse infix string untill last character is hit.
        if(s[i]==' ')                   //if we encounter spaces in infix string then we ignore them.
            continue;
        else if(s[i] == '('){           //if we encounter open brace then simply push it to stack
            stack[++top] = s[i];
        }
        else if(!isOperater(s[i]) && s[i]!='(' && s[i]!=')'){         //if the current character is not an operator and not a brace i.e is an operand then simply just add it to postfix string.
            int len = strlen(pf);
            if (len < size - 1) {  // Check if there is space in pf to add another character
                pf[len] = s[i];     // Add the character to the end of pf
                pf[len + 1] = '\0';  // Null-terminate the string
            }
        }
        else if(s[i] == ')'){               //if we encounter a closing bracket then we pop untill we encounter an opening bracket or stack becomes empty
            while(top>-1 && stack[top]!='('){           //popping all elements untill we found an opening brace or stack becomes empty.
                int len = strlen(pf);
                if (len < size - 1) {  // Check if there is space in pf to add another character
                    pf[len] = stack[top--];     // Add the character to the end of pf
                    pf[len + 1] = '\0';  // Null-terminate the string
                }

            }
            if(top>-1 && stack[top] != '('){        //this case is handling that even after popping all elements from stack until an open brace is found even after if found open brace then simply delete it but if other operator was found then it is sure that no open brace was available for a closing brace, so handle this case.
                printf("\n***INVALID***\n");
                return;
            }
            else{                                   //if after popping all opertors also pop open brace.
                top--;
            }
        }
        else if(isOperater(s[i])){
            while(top>-1 && precedence(stack[top]) >= precedence(s[i]) ) {    //if the order the current is less then top element (i.e bottom element has a higher precedenc) then pop stack top until we found order of current is higher then top elements.
                
                int len = strlen(pf);
                if (len < size - 1) {  // Check if there is space in pf to add another character
                    pf[len] = stack[top--];                                                //keep on popping stack elements(operators) and add it to postfix string as top element is having a lower precedence.
                    pf[len + 1] = '\0';  // Null-terminate the string
                }
                
            }
            stack[++top] = s[i];                                            //else if current element's precedence is already higher then the stack top then push it to stack.
        }
    }
    while(top>-1){                          //if any remaining operator is still in the stack , then add them to string.
        if(stack[top] == '('){              //if any how we have any opening brace then it is sure no opening brace was available for it , so it is an error which we handled.
            printf("\n***INVALID***\n");
            return;
        }
        int len = strlen(pf);
        if (len < size - 1) {  // Check if there is space in pf to add another character
            pf[len] = stack[top--];     // Add the character to the end of pf
            pf[len + 1] = '\0';  // Null-terminate the string
        }
    }
    printf("Postfix Expression : %s",pf);       //NOW pf contains the postfix expression.
    evaluate(pf);
    
}

int main(){
    char s[50];                     //defining size of char array
    printf("-Use only single digits.\n-Give space b/w operand & operator.\nEnter Postfix Expression : ");
    gets(s);                        //gets will read spaces also
    // infixToPostfix(s);
    evaluate(s);
    return 0;
}
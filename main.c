#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define STACK_SIZE 100
#define INFIX_SIZE 100
#define PROCESSED_INFIX_SIZE 100

// typedef int element; 
// typedef struct {
//     int data[STACK_SIZE];
//     int top;
// } Stack;

char stack[STACK_SIZE];
int top = -1;

int isEmpty()
{
    return (top < 0) ? 1 : 0;
}
int isFull()
{
    return (top >= STACK_SIZE - 1) ? 1 : 0;
}
void push(char c)
{
    if (isFull() == 1)
        printf("Stack is full.\n");
    else
        stack[++top] = c;
}
char pop()
{
    if (isEmpty() == 1)
        printf("Stack is empty.\n");
    else
        return stack[top--];
}
char getTop()
{
    if (isEmpty() == 1)
        printf("Stack is Empty");
    else
        return stack[top];
}

int getPriority(char c)
{
    if (c == '-' || c == '+')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    return 0;
}

char infixToPostfix(char infix[INFIX_SIZE])
{
    char infix_[PROCESSED_INFIX_SIZE] = "";
    static char output[PROCESSED_INFIX_SIZE] = "";
    char temp;
    int i = 0;

    strcat(infix_, "(");
    strcat(infix_, infix);
    strcat(infix_, ")");

    while(infix_[i] != '\0')
    {
        if (isdigit(infix_[i]))
        {
            temp = infix_[i];
            strncat(output, &temp, 1);
            i++;
        }

        else if (infix_[i] == '(')
        {
            push('(');
            i++;
        }

        else if (infix_[i] == ')')
        {
            while (getTop() != '(')
            {
                strcat(output, " ");
                temp = pop();
                strncat(output, &temp, 1);
         
            }
            pop();
            i++;
        }

        else
        {
            strcat(output, " ");

            while (getPriority(infix_[i]) <= getPriority(getTop())) 
            {
                temp = pop();
                strncat(output, &temp, 1);
                strcat(output, " ");
            }

            push(infix_[i]);
            i++;
        }

    }

    while (isEmpty() == 0)
    {
        temp = pop();
        strncat(output, &temp, 1);
        strcat(output, " ");
    }

    printf("%s", output);

    return (char*)output;
}

int main(void)
{
    //char infix[INFIX_SIZE] = "32+8*4/8+6"; // 길이 10
    char infix[INFIX_SIZE] = "31+8*4/8+6+5+3*1*2*5+9/(4+5)"; // 길이 28
    char processedInfix[INFIX_SIZE];

    strcpy(processedInfix, infixToPostfix(infix));

    printf("%s", processedInfix);

    return 0;
}
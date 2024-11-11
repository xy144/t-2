#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct Node {
    int data;
    struct Node *next;
} Node;
typedef struct {
    Node *top;
} Stack;
int is_operator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}
int calculate(int a, char op, int b) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            exit(1);
    }
}

Stack *create_stack() {   // ������ջ
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

void push(Stack *stack, int data) {   // ��ջ����
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = stack->top;
    stack->top = node;
}

int pop(Stack *stack) {   // ��ջ����
    if (stack->top == NULL) {
        return -1;   // ���ջΪ�գ��򷵻�-1
    }
    Node *node = stack->top;
    int data = node->data;
    stack->top = node->next;
    free(node);
    return data;
}

int top(Stack *stack) {   // ����ջ��Ԫ��
    if (stack->top == NULL) {
        return -1;   // ���ջΪ�գ��򷵻�-1
    }
    return stack->top->data;
}
int getIndex(char theta) //��ȡ theta ����Ӧ������
{
     int index = 0;
 switch (theta)
 {
 case '+':
 index = 0;
 break;
 case '-':
 index = 1;
 break;
 case '*':
 index= 2;
 break;
 case '/':
 index = 3;
 break;
 case '(':
 index = 4;
 break;
 case ')':
 index = 5;
 break;
 case '#':
 index = 6;
 default:break;
 }
 return index;
 }

 char getPriority(char theta1, char theta2)
 //��ȡ theta1 �� theta2 ֮������ȼ�
 {
 const char priority[7][7] = //���������ȼ���ϵ
 {
   { '>','>','<','<','<','>','>' },
   { '>','>','<','<','<','>','>' },
   { '>','>','>','>','<','>','>' },
   { '>','>','>','>','<','>','>' },
   { '<','<','<','<','<','=','0' },
   { '>','>','>','>','0','>','>' },
   { '<','<','<','<','<','0','=' },
 };
 int index1 = getIndex(theta1);
 int index2 = getIndex(theta2);
 return priority[index1][index2];
 }
int evaluate_expression(char *expression) {
    Stack *s1 = create_stack();   // ������ջ�����ڴ洢������
    Stack *s2 = create_stack();   // ������ջ�����ڴ洢������

    for (int i = 0; expression[i] !='='; i++) {
        if (is_operator(expression[i])) {   // �����ǰ�ַ�Ϊ������
            while (s2->top != NULL && (getPriority(top(s2),expression[i])=='>'||getPriority(top(s2),expression[i])=='=')){
                // ���������ջ��Ϊ�գ�����ջ�������������ȼ����ڵ��ڵ�ǰ�����������ȼ�
                int b = pop(s1);    // ��ջһ����������Ϊ������Ҳ�����
                int a = pop(s1);    // �ٳ�ջһ����������Ϊ������������
                char op = pop(s2);  // ��ջһ��������
                int result = calculate(a, op, b);   // ���������������Ͳ������Ľ��
                push(s1, result);   // ����������ջ��������ջ��
            }
            push(s2, expression[i]);  // ��ǰ��������ջ��������ջ��
        } else if (expression[i] == '(') { // �����ǰ�ַ�Ϊ������
            push(s2, expression[i]);    // ��ջ��������ջ��
        } else if (expression[i] == ')') { // �����ǰ�ַ�Ϊ������
            while (top(s2) != '(') {    // ѭ��ִ��ֱ������������
                int b = pop(s1);    // ��ջһ����������Ϊ������Ҳ�����
                int a = pop(s1);    // �ٳ�ջһ����������Ϊ������������
                char op = pop(s2);  // ��ջһ��������
                int result = calculate(a, op, b);   // ���������������Ͳ������Ľ��
                push(s1, result);   // ����������ջ��������ջ��
            }
            pop(s2);    // ����������
        } else {    // �����ǰ�ַ�Ϊ����
            int num = expression[i] - '0';  // ����ǰ�ַ�ת��������
            while (expression[i + 1] >= '0' && expression[i + 1] <= '9') {
                // �����һ���ַ�Ҳ�����֣�����ϲ���һ��
                num = num * 10 + expression[++i] - '0';
            }
            push(s1, num);  // ��������ջ��������ջ��
        }
    }

    // ����ʣ��Ĳ�����
    while (s2->top != NULL) {
        int b = pop(s1);    // ��ջһ����������Ϊ������Ҳ�����
        int a = pop(s1);    // �ٳ�ջһ����������Ϊ������������
        char op = pop(s2);  // ��ջһ��������
        int result = calculate(a, op, b);   // ���������������Ͳ������Ľ��
        push(s1, result);   // ����������ջ��������ջ��
    }

    return pop(s1); // �������յļ�����
}


int main() {
    char expression[100];
    int result;
    printf("��������׺���ʽ��");
    while(1)
    {
         scanf("%s", expression);
        if(strcmp(expression,"=")==0)
            break;
        result = evaluate_expression(expression);
        printf("��������%d\n", result);
    }
    return 0;
}

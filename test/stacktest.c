#include <stack.h>

int main()
{
    stackStringTest();
    return 0;
}

void stackStringTest()
{
    char *str1 = "test1";
    char *str2 = "test2";
    char *str3 = "test3";
    char *str4 = "test4";
    char *string = NULL;
    struct stack *temp, *node = createStack();
    printf("push %s to stack\n", str1);
    pushStack(node, str1);
    printf("push %s to stack\n", str2);
    pushStack(node, str2);
    printf("push %s to stack\n", str3);
    pushStack(node, str3);
    printf("push %s to stack\n", str4);
    pushStack(node, str4);
    temp = popStack(node);
    string = (char *)(temp->element);
    printf("pop %s off stack\n", string);
    temp = popStack(node);
    string = (char *)(temp->element);
    printf("pop %s off stack\n", string);
    temp = popStack(node);
    string = (char *)(temp->element);
    printf("pop %s off stack\n", string);
    temp = popStack(node);
    string = (char *)(temp->element);
    printf("pop %s off stack\n", string);
}

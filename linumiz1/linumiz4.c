/*Name : keerthick vasa M
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

typedef struct {
    char *dirs[100];
    int top;
} DirStack;
void push(DirStack *stack, const char *dir)
{
    if (stack->top < (100-1))
    {
	stack->dirs[++(stack->top)] = strdup(dir);
    } else
    {
	printf("stack is full\n");
    }
}
char* pop(DirStack *stack)
{
    if (stack->top >= 0) {
	return stack->dirs[(stack->top)--];
    } else {
	printf("Stack underflow\n");
	return NULL;
    }
}
void pushd(DirStack *stack, const char *dir)
{
    char cwd[100];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
	push(stack, cwd);
	if (chdir(dir) == 0) {
	    getcwd(cwd, 100);
	    push(stack,cwd);
	    printf("Changed directory to %s\n", dir);
	} else {
	    printf("ERROR in change dirs\n");
	}
    } else {
	printf("getcwd return NULL\n");
    }
}
void popd(DirStack *stack)
{
      char c[100];
      printf("current working directory =  %s\n",getcwd(c,100));
    char *dir = pop(stack);
    if (dir != NULL) {
	if (chdir(dir) == 0) {
	    printf("Changed directory to %s\n", dir);
	    free(dir);
	} else {
	    printf("ERROR in change dirs\n");
	    free(dir);
	}
    }
}
void print_stack(DirStack *stack)
{
    if(stack->top==-1)
    {
	printf("Directory stack : Stack empty\n");
	return ;
    }
    printf("Directory stack:\n");

    for (int i = stack->top; i >= 0; i--) {
	printf("%s\n", stack->dirs[i]);
    }
}

int main(int argc, char *argv[])
{
    static DirStack stack;
    stack.top=-1;
    if (argc < 2)
    {
	printf("give the valide input");
	return 0;
    }
    if (strcmp(argv[1], "pushd") == 0) 
    {
	pushd(&stack, argv[2]);
    }
    else if (strcmp(argv[1], "popd") == 0)
    {
	popd(&stack);
    }
    else
    {
	printf("Invalid input\n");
	return 0;
    }

    print_stack(&stack);

    return 0;
}




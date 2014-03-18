#ifndef __STACK_H__
#define __STACK_H__


//Stack structure.
typedef struct
{
	void *topOfStack;
	
}Stack;

void push(Stack *stack , void *newMember);
void * pop(Stack *stack);


#endif //__STACK_H__
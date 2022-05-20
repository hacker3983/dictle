#include <stdlib.h>

typedef struct stack {
	char* string;
	size_t top;
} stack_t;

void stack_init(stack_t* stack) {
	stack->string = calloc(1, sizeof(char));
	stack->top = 0;
}

void stack_push(stack_t* stack, char x) {
	stack->string[stack->top++] = x;
	char* temp = stack->string;
	stack->string = calloc(stack->top+1, sizeof(char));
	for(size_t i=0;i<stack->top;i++) {
		stack->string[i] = temp[i];
	}
	free(temp); temp = NULL;
}

int stack_peek(stack_t stack) {
	if(stack.top == 0) {
		return -1;
	}
	return stack.string[stack.top-1];
}

int stack_pop(stack_t* stack) {
	if(stack->top == 0) {
		return -1;
	}
	return stack->string[--stack->top];
}

void stack_free(stack_t* stack) {
	free(stack->string); stack->string = NULL;
	stack->top = 0;
}

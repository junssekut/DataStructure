#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "./stack.cpp"
#include "./convertion_utils.cpp"
#include "./step.cpp"

char* infixToPostfix(const char* str) {
	Stack* stack = NULL;
	
	int len = strlen(str);
	
	char result[len + (len / 2)];
	Step steps[len + (len / 2)];
	
	int resultIndex = 0;
	int stepIndex = 0;
	
	for (int i = 0; i < len; i++) {
		char c = str[i];
		
		// if character is an operand push it to prefix
		if (isalnum(c)) {
			result[resultIndex++] = c;
			
			char messageBuffer[1024];
			{
				sprintf(messageBuffer, "ADD('%c')", c);
			}
			steps[stepIndex++] = createStep(c, stack, result, messageBuffer);
			continue;
		}
		
		// if character is an '('
		if (c == '(') {
			push(&stack, c);
			steps[stepIndex++] = createStep(c, stack, result, "PUSH('(')");
			continue;
		}
		
		// if character is an ')'
		if (c == ')') {
			while (stack != NULL && peek(stack) != '(')  {
				result[resultIndex++] = peekAndPop(&stack);
				
				steps[stepIndex++] = createStep(c, stack, result, "UPDATE STACK 1");
			}
			pop(&stack);
			
			continue;
		}
			
		while (stack != NULL && ((precedence(c)) < precedence(peek(stack)) || precedence(c) == precedence(peek(stack)) && associativity(c) == 'L')) {
			result[resultIndex++] = peekAndPop(&stack);
			steps[stepIndex++] = createStep(c, stack, result, "UPDATE STACK 2");
		}
		
		push(&stack, c);
		char messageBuffer[1024];
		{
			sprintf(messageBuffer, "PUSH('%c')", c);
		}
		steps[stepIndex++] = createStep(c, stack, result, messageBuffer);
	}
	
	// finish stack and add to result
	while (stack != NULL) {
		result[resultIndex++] = peekAndPop(&stack);
	}
		
	result[resultIndex] = '\0';
	
	for (int i = 0; i < stepIndex; i++) {
		Step s = steps[i];
		printf("%3c [%10s] [%15s] %10s\n", s.input, s.stack, s.result, s.message);
	} 
	
	return strdup(result);
}

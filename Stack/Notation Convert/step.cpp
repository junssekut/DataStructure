#include <string.h>

#include "./stack.h"
#include "./step.h"

struct Step {
	char input;
	char stack[1024];
	char result[1024];
	char message[1024];
};

Step createStep(const char input, Stack* top, const char* result, const char* message) {
	Step step;
	
	step.input = input;
	
	char stackBuffer[1024];
	{ // stack to string
		int bufferIndex = 0;
		
		Stack* ptr = top;
		while (ptr != NULL) {
			stackBuffer[bufferIndex++] = ptr->value;
			ptr = ptr->next;
		}
		stackBuffer[bufferIndex] = '\0'; 
		printf("tostr: [%s]\n", stackBuffer);
		
		strcpy(step.stack, stackBuffer);
	}
	
	strcpy(step.result, result);
	strcpy(step.message, message);
	
	return step;
}

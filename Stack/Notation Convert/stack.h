struct Stack;

Stack* createStack(char value);
int push(Stack** top, char value);
int pop(Stack** top);
bool isEmpty(Stack* top);
char peek(Stack* top);
char peekAndPop(Stack** top);

void display(Stack* top);

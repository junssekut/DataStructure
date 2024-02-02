int precedence(char c) {
	if (c == '^') return 3;
    else if (c == '/' || c == '*') return 2;
    else if (c == '+' || c == '-') return 1;
    else return -1;
}

char associativity(char c) {
	return c == '^' ? 'R' : 'L';
}

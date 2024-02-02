#include <stdio.h>
#include <string.h>

int main() {
	
	const char* str = "Kevin";
	
	int sum = 0;
	for (int i = 0; i < strlen(str); i++) {
		sum += str[i];
	}
	int hashCode = sum % 5;
	printf("\"%s\"->%d\n", str, hashCode);
	
	return 0;
}

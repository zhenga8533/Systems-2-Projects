#include <stdio.h>
#include <unistd.h>

int main(void) {
	freopen("test.txt", "w", stdout);

	for (int count = 1; count <= 10; count++) {
		printf("Testing... (%d/10)\n", count);
		sleep(1);
	}
	
	return 0;
}


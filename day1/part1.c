#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 1) {
	printf("Error: Did not enter input file path.\n");
    }

    FILE* file = fopen(argv[1], "r");
    
    if (file == NULL) {
        printf("Error: File not found.\n");
        fclose(file);
        return 1;
    }
    
    char c;
    int first = -1;
    int last = -1;
    int sum = 0;

    while (fread(&c, sizeof(char), 1, file)) {
        if (isdigit(c)) {
            if (first == -1) {
                first = atoi(&c);
            } else {
                last = atoi(&c);
            }
        } else if (c == '\n') {
            if (last == -1) {
                last = first;
            }

            sum += first * 10 + last;
            first = -1;
            last = -1;
        }
    }

    fclose(file);
    printf("The sum is %i.\n", sum);
}

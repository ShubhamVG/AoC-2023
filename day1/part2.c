#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int extract_number(char* str);
char* strrev(char* str); 

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Error: No input path.\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Error: Failed to open file.\n");
        fclose(file);
        return 1;
    }

    char c;
    int index = 0;
    int sum = 0;
    char word[65];

    while (fread(&c, sizeof(char), 1, file)) {
        if (c == '\n') {
            word[index] = '\0';
            index = 0;
            sum += extract_number(&word[0]);
            continue;
        }
        
        word[index] = c;
        index++;
    }
    
    fclose(file);
    printf("The sum is %i.\n", sum);
}

int extract_number(char* str) {
    char* reversed_str = strrev(str);
    int first_index = 999999;
    int last_index = 999999;
    int first = -1;
    int last = -1;
    char* valid_tokens[10][2] = {
        {"0", "zero"},
        {"1", "one"},
        {"2", "two"},
        {"3", "three"},
        {"4", "four"},
        {"5", "five"},
        {"6", "six"},
        {"7", "seven"},
        {"8", "eight"},
        {"9", "nine"}
    };

    for (int curr_digit = 0; curr_digit < 10; curr_digit++) {
        for (int i = 0; i < 2; i++) {
            char* substr = valid_tokens[curr_digit][i];
            char* occurrence = strstr(str, substr);
            int position;

            if (occurrence != NULL) {
                position = occurrence - str;

                if (position < first_index) {
                    first_index = position;
                    first = curr_digit;
                }
            }

            substr = strrev(substr);
            occurrence = strstr(reversed_str, substr);

            if (occurrence != NULL) {
                position = occurrence - reversed_str;

                if (position < last_index) {
                    last_index = position;
                    last = curr_digit;
                }
            }

            free(substr);
        }
    }

    free(reversed_str);

    return first * 10 + last;
}

char* strrev(char* str) {
    int len = strlen(str);
    char* reversed_word = malloc(sizeof(char) * (len + 1));
    reversed_word[len] = '\0';

    for (int i = 0; i < len; i++) {
        reversed_word[i] = str[len - i - 1];
    }

    return reversed_word;
}


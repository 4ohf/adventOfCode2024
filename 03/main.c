/* Why did I decide to do this in C??? */

#include <regex.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void regMatcher(char *string, regex_t pattern, regmatch_t *match, int *sum)
{
        size_t start = 0;
        bool doit = true;
        while (start < strlen(string)) {
                if (regexec(&pattern, string + start, 1, match, 0) == 0) {
                        char word[13];
                        char *token, *left, *right;
                        int a, b;
                        int len = match[0].rm_eo - match[0].rm_so;

                        strncpy(word, string + start + match[0].rm_so, len);
                        word[len] = '\0';

                        // printf("%s\n", word);

                        if (strstr(word, "do()") != NULL)
                                doit = true;
                        if (strstr(word, "don't()") != NULL)
                                doit = false;

                        // if (strstr(word, "mul") != NULL) { // part 1 solution
                        if ((strstr(word, "mul") != NULL) && doit == 1) {
                                token = strtok(word, ",");
                                if (token != NULL)
                                        left = token;
                                token = strtok(NULL, " ");
                                if (token != NULL)
                                        right = token;
                                left = strtok(left + 4, "");
                                right[strcspn(right, ")")] = '\0';

                                a = atoi(left);
                                b = atoi(right);

                                *sum += a * b;
                                // printf("%d\t%d\n", doit, *sum);
                        }


                        start += match[0].rm_eo;
                } else {
                        start += 1;
                }
        }
}

int main(void)
{
        FILE *input = fopen("input", "r");
        char *line = NULL;
        size_t len = 0;
        int sum = 0;
        int *psum = &sum;

        if (input == NULL) {
                return 1;
        }

        regex_t pattern;
        regcomp(&pattern,
                "^mul\\([0-9]\{1,3},[0-9]\{1,3}\\)|^do\\(\\)|^don't\\(\\)",
                REG_EXTENDED);

        regmatch_t match[1];

        while (( getline(&line, &len, input)) != -1) {
                regMatcher(line, pattern, match, psum);
        }

        printf("%d\n", sum);

        fclose(input);

        return 0;
}

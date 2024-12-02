#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 100

int main()
{
        FILE *input = fopen("input", "r");
        char line[LINE_LENGTH];
        char *token;
        int safe_reports = 0;

        if (input == NULL) {
                printf("Could not open file\n");
                return 1;
        }

        while (fgets(line, sizeof(line), input) != NULL) {
                int index = 0;
                int prev, diff, prev_diff;
                int check = 0;
                token = strtok(line, " ");

                while (token != NULL) {
                        int num = atoi(token);

                        if (index != 0) {
                                diff = num - prev;
                                if (diff == 0)
                                        check++;
                                if (abs(diff) > 3)
                                        check++;
                                if (abs(diff) < 1)
                                        check++;
                                if ((index != 1) &&
                                    ((prev_diff > 0 && diff < 0) ||
                                     (prev_diff < 0 && diff > 0)))
                                        check++;
                                prev_diff = diff;
                        }

                        prev = num;
                        token = strtok(NULL, " ");
                        index++;
                }
                if (check == 0)
                        safe_reports++;
        }
        printf("Safe: %d\n", safe_reports);

        fclose(input);

        return 0;
}

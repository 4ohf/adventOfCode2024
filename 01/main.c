#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_NUMBERS 1000

int compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int main()
{
        FILE *file;
        char line[MAX_LINE_LENGTH];
        char *token;
        int left_list[MAX_NUMBERS], right_list[MAX_NUMBERS];
        int index = 0;
        int totat_dist = 0;
        int total_simi = 0;

        file = fopen("input", "r");
        if (file == NULL) {
                printf("Could not open file\n");
                return 1;
        }

        while (fgets(line, sizeof(line), file)) {
                token = strtok(line, " \t");
                if (token != NULL) {
                        left_list[index] = atoi(token);
                }

                token = strtok(NULL, " \t");
                if (token != NULL) {
                        right_list[index] = atoi(token);
                }

                index++;
        }

        fclose(file);

        qsort(left_list, MAX_NUMBERS, sizeof(left_list[0]), compare);
        qsort(right_list, MAX_NUMBERS, sizeof(right_list[0]), compare);

        for (int i = 0; i < index; i++) {
                int dist;
                dist = abs(left_list[i] - right_list[i]);
                totat_dist += dist;

                int curren_left = left_list[i];
                int simi = 0;

                for (int i = 0; i < index; i++) {
                        if (curren_left == right_list[i])
                                simi++;
                }
                total_simi += left_list[i] * simi;
        }

        printf("total distance: %d\ntotal similarity: %d\n", totat_dist,
               total_simi);

        return 0;
}

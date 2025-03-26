#include <stdio.h>

void main() {
    int i, j, k, min, rs[25], m[10], count[10], freq[10], flag[25], n, f, pf = 0;

    printf("Enter the length of reference string -- ");
    scanf("%d", &n);

    printf("Enter the reference string -- ");
    for (i = 0; i < n; i++) {
        scanf("%d", &rs[i]);
        flag[i] = 0;
    }

    printf("Enter the number of frames -- ");
    scanf("%d", &f);
    
    for (i = 0; i < f; i++) {
        count[i] = 0;
        freq[i] = 0;
        m[i] = -1;
    }

    printf("\nThe Page Replacement process is -- \n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < f; j++) {
            if (m[j] == rs[i]) {
                flag[i] = 1;
                freq[j]++;
                break;
            }
        }

        if (flag[i] == 0) {
            if (i < f) {
                m[i] = rs[i];
                freq[i] = 1;
            } else {
                min = 0;
                for (j = 1; j < f; j++) {
                    if (freq[min] > freq[j])
                        min = j;
                }
                m[min] = rs[i];
                freq[min] = 1;
            }
            pf++;
        }

        for (j = 0; j < f; j++)
            printf("\t%d", m[j]);

        if (flag[i] == 0)
            printf("\tPF No. %d", pf);

        printf("\n");
    }

    printf("\nThe number of Page Faults using LFU are %d\n", pf);
}

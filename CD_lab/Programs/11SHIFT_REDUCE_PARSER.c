#include<stdio.h>
#include<stdlib.h>

int a[10] = {121, 131, 514, 6, 181};
int stack[20], top = -1;

void push(int item) {
    if (top >= 20) {
        printf("Overflow");
        exit(1);
    }
    top++;
    stack[top] = item;
}

char convert(int item) {
    char ch;
    switch(item) {
        case 1: ch = 'e'; break;
        case 2: ch = '*'; break;
        case 3: ch = '+'; break;
        case 4: ch = '('; break;
        case 5: ch = ')'; break;
        case 6: ch = 'i'; break;
        case 7: ch = '$'; break;
        case 8: ch = '='; break;
    }
    return ch;
}

int action(int item) {
    int i;
    for (i = 0; i <= 4; i++) {
        if (a[i] == item)
            return 1;
    }
    return -1;
}

void main() {
    char ipstr[20];
    int ip[20], i, s, sum, j, l, m, n, cnt;
    printf("\nEnter the input string: ");
    scanf("%s", ipstr);

    for (i = 0; ipstr[i] != '\0'; i++) {
        switch (ipstr[i]) {
            case 'e': s = 1; break;
            case '*': s = 2; break;
            case '+': s = 3; break;
            case '(': s = 4; break;
            case ')': s = 5; break;
            case 'i': s = 6; break;
            case '$': s = 7; break;
            case '=': s = 8; break;
            default: 
                printf("Error");
                exit(1);
        }
        ip[i] = s;
    }
    ip[i] = -1;
    i = 0;
    push(7);
    printf("\tStack\tInput\tAction\n");
    printf("\t----------------------------\n\n");

    while (1) {
        printf("\t");
        for (m = 0; m <= top; m++)
            printf("%c", convert(stack[m]));
        printf("\t");
        for (n = i; ip[n] != -1; n++)
            printf("%c", convert(ip[n]));
        printf("\t");
        sum = 0;
        
        if ((stack[top] == 1) && (stack[top - 1] == 7) && (ip[i] == 7)) {
            printf("\tAccept");
            exit(1);
        } else {
            l = 1;
            while (l <= top) {
                j = l;
                sum = 0;
                cnt = 0;
                for (; j <= top; j++) {
                    sum = sum * 10 + stack[j];
                    cnt++;
                }
                s = action(sum);
                if (s == 1) {
                    top = top - cnt;
                    push(1);
                    printf("\tReduce");
                    break;
                }
                l++;
            }
            if (s == -1 && ip[i] == 7) {
                printf("\tError");
                exit(1);
            }
        }
        if (ip[i] != 7) {
            push(ip[i]);
            i++;
            printf("\tShift");
        }
        printf("\n");
    }
}

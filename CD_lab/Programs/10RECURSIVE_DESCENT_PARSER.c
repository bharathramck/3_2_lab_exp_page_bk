#include<stdio.h>
#include<ctype.h>

char str[15];
int p, chk = 1;

void e();
void eprime();
void t();
void tprime();
void f();

void main() {
    printf("Enter the input string: ");
    scanf("%s", str);
    printf("%s", str);
    p = 0;
    e();
    if (p == strlen(str) && chk)
        printf("\nString is acceptable");
    else {
        printf("\nThe given input string: %s", str);
        printf("\nThe string is not acceptable");
    }
    getch();
}

void e() {
    printf("\nE->TE'");
    t();
    eprime();
}

void eprime() {
    if (str[p] == '+') {
        printf("\nE'->+TE'");
        p++;
        t();
        eprime();
    } else {
        printf("\nE'->#");
    }
}

void t() {
    printf("\nT->FT'");
    f();
    tprime();
}

void tprime() {
    if (str[p] == '*') {
        printf("\nT'->*FT'");
        p++;
        f();
        tprime();
    } else {
        printf("\nT'->#");
    }
}

void f() {
    if (isalpha(str[p])) {
        p++;
        printf("\nF->i");
    } else if (str[p] == '(') {
        printf("\nF->(E)");
        p++;
        e();
        if (str[p] == ')')
            p++;
        else
            chk = 1;
    } else {
        chk = 1;
    }
}

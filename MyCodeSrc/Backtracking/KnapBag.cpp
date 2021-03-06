﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int w[10000], c[10000], x[10000], n, k, fk = 0, bk, gk = 0;
int fopt = -2147483646, xopt[10000] = { 0 };

void BranchBag(int i) { // duyet nhanh can
    int t;
    if (bk >= w[i]) t = 1;
    else t = 0;
    for (int j = t; j >= 0; j--) {
        x[i] = j;
        bk = bk - w[i] * x[i];
        fk = fk + c[i] * x[i];
        if (i < n) gk = fk + c[i + 1] * bk / w[i + 1];
        if (i == n) {
            if (fk >= fopt) {
                fopt = fk;
                for (int h = 1; h <= n; h++) {
                    xopt[h] = x[h];
                }
            }
        }
        else if (gk >= fopt) BranchBag(i + 1); // nếu giới hạn trên nhỏ hơn kỷ lục thì cắt nhánh đang xét ngược lại tiêpd tục xét.
        bk = bk + w[i] * x[i];
        fk = fk - c[i] * x[i];
        if (i < n) gk = fk - c[i + 1] * bk / w[i + 1];
    }
}

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void BBSort()
{
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < n; j++) {
            if (double(c[j]) / double(w[j]) < double(c[j + 1]) / double(w[j + 1])) {
                swap(&c[j], &c[j + 1]);
                swap(&w[j], &w[j + 1]);
            }
        }
    }
}
int main() {
    scanf("%d%d", &n, &bk);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &w[i], &c[i]);
    }
    BBSort();
    BranchBag(1);
    printf("%d", fopt);
    return 0;
}
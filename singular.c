#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "singular.h"


//enum filter_type { EQ = 0, NEQ = 1, GEQ = 2, LEQ = 3, LESS = 4, GREATER = 5 };

int prec = 6;

//SHIFT function
void shift(double a[], size_t size, double by){

    for(int i = 0; i < size; i++){
        a[i]+=by;
    }

}

//PRINT function
void print(double a[], size_t size){

    for(int i = 0; i < size; i++){
        if(prec == 0){
            printf("%.0f ", a[i]);
        } else if (prec == 1){
            printf("%.1f ", a[i]);
        } else if (prec == 2){
            printf("%.2f ", a[i]);
        } else if (prec == 3){
            printf("%.3f ", a[i]);
        } else if (prec == 4){
            printf("%.4f ", a[i]);
        } else if (prec == 5){
            printf("%.5f ", a[i]);
        } else if (prec == 6){
            printf("%f ", a[i]);
        } else if (prec == 7){
            printf("%.7f ", a[i]);
        } else if (prec == 8){
            printf("%.8f ", a[i]);
        } else if (prec == 9){
            printf("%.9f ", a[i]);
        }
        //printf("%f\n", a[i]);
    }
    printf("\n");
}

//FILTER function
size_t filter(double a[], size_t count, enum filter_type t, double threshold){
    size_t i, j;
    switch (t) {
        case 0:
            for (i = j = 0; i < count; i++) {
                if (a[i] == threshold) {
                    a[j++] = a[i];
                }
            }
            break;
        case 1:
            for (i = j = 0; i < count; i++) {
                if (a[i] != threshold) {
                    a[j++] = a[i];
                }
            }
            break;
        case 2:
            for (i = j = 0; i < count; i++) {
                if (a[i] >= threshold) {
                    a[j++] = a[i];
                }
            }
            break;
        case 3:
            for (i = j = 0; i < count; i++) {
                if (a[i] <= threshold) {
                    a[j++] = a[i];
                }
            }
            break;
        case 4:
            for (i = j = 0; i < count; i++) {
                if (a[i] < threshold) {
                    a[j++] = a[i];
                }
            }
            break;
        case 5:
            for (i = j = 0; i < count; i++) {
                if (a[i] > threshold) {
                    a[j++] = a[i];
                }
            }
            break;
    }
    return j;
}
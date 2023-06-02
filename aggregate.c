#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "aggregate.h"

//Array of strings of the functions name
static const char* funcnames[] = { "MIN", "MAX", "COUNT", "SUM", "AVG", "PAVG"};

//Prototype of all the non externally visible functions
static double min(double* arr, int s);
static double max(double* arr, int s);
static double count(double* arr, int s);
static double sum(double* arr, int s);
static double avg(double* arr, int s);
static double pavg(double* arr, int s);

//Array of function pointers
static double (*farray[6]) (double *, int) = {&min, &max, &count, &sum, &avg, &pavg};


//aggregate function
double aggregate(const char* func, double* arr, int size){
    int index = 0;

    //Checking the index of name of the function
    for(int i = 0; i < sizeof(funcnames); i++){
       if(strcasecmp(func, funcnames[i]) == 0){
        index = i;
        return farray[index](arr, size);
        } 
    }
    fprintf(stderr, "FATAL ERROR: Unknown function name\n");
    exit(1);
}

//MIN function
static double min(double* arr, int s){
    
    if(s < 0){
        fprintf(stderr, "FATAL ERROR: Invalid array size\n");
        exit(1);
    }

    double minimum = arr[0];

    for(int i = 1; i < s; i++){
        if(arr[i] < minimum){
            minimum = arr[i];
        }
    }

    return minimum;
}

//MAX function
static double max(double* arr, int s){
    
    if(s < 0){
        fprintf(stderr, "FATAL ERROR: Invalid array size\n");
        exit(1);
    }

    double maximum = arr[0];

    for(int i = 1; i < s; i++){
        if(arr[i] > maximum){
            maximum = arr[i];
        }
    }

    return maximum;
}

//COUNT function
static double count(double* arr, int s){
    
    if(s < 0){
        fprintf(stderr, "FATAL ERROR: Invalid array size\n");
        exit(1);
    }
    double count = s;

    return count;
}

//SUM function
static double sum(double* arr, int s){
    
    if(s < 0){
        fprintf(stderr, "FATAL ERROR: Invalid array size\n");
        exit(1);
    }

    double sum = 0;

    for(int i = 0; i < s; i++){
        sum += arr[i];
    }

    return sum;
}

//AVG function
static double avg(double* arr, int s){
    
    if(s < 0){
        fprintf(stderr, "FATAL ERROR: Invalid array size\n");
        exit(1);
    }
    
    double avg = 0;
    double sum = 0;

    for(int i = 0; i < s; i++){
        sum += arr[i];
    }

    avg = sum/s;

    return avg;
}

//PAVG function
static double pavg(double* arr, int s){
    
    if(s < 0){
        fprintf(stderr, "FATAL ERROR: Invalid array size\n");
        exit(1);
    }
    
    double pavg = 0;

    double minimum = min(arr, s);
    double maximum = max(arr, s);

    pavg = (minimum+maximum)/2;

    return pavg;
}
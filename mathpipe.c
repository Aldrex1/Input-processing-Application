#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include "aggregate.h"
#include "singular.h"


int main(int argc, char const *argv[])
{
    char func[20];
    int size = 0;
    prec = 6;
    double shift_v = 0;
    double thres = 0;
    enum filter_type filter_v = -1;
    
    void grateful(char *func, double *test1, int test_size, int size, double shift_v, double thres, enum filter_type filter_v);

    for(int i = 1; i<argc; i++){
        if(strncmp(argv[i], "-size=", 6) == 0){
            const char *size_char = argv[i];
            size = size_char[6]-48;
            if(size < 1){
                fprintf(stderr, "FATAL ERROR: Invalid size\n");
                exit(1);
            }

        } else if (strncmp(argv[i], "-prec=", 6) == 0){
            const char *prec_char = argv[i];
            prec = prec_char[6]-48;
            if(prec < 0){
                fprintf(stderr, "FATAL ERROR: Invalid precision\n");
                exit(1);
            }

        } else if ((strcasecmp(argv[i], "SHIFT") == 0)){
            strncpy(func, argv[i], sizeof(func) - 1);
            func[sizeof(func) - 1] = '\0';
            char* end;
            shift_v = strtod(argv[i+1], &end);
            i++;

        } else if ((strcasecmp(argv[i], "FILTER") == 0)){
            strncpy(func, argv[i], sizeof(func) - 1);
            func[sizeof(func) - 1] = '\0';
            if((strcasecmp(argv[i+1], "EQ") == 0)){
                filter_v = 0;
            } else if ((strcasecmp(argv[i+1], "NEQ") == 0)){
                filter_v = 1;
            } else if ((strcasecmp(argv[i+1], "GEQ") == 0)){
                filter_v = 2;
            } else if ((strcasecmp(argv[i+1], "LEQ") == 0)){
                filter_v = 3;
            } else if ((strcasecmp(argv[i+1], "LESS") == 0)){
                filter_v = 4;
            } else if ((strcasecmp(argv[i+1], "GREATER") == 0)){
                filter_v = 5;
            } else {
                fprintf(stderr, "FATAL ERROR: Unknown filter type\n");
                exit(1);
            }
            
            char* end;
            thres = strtod(argv[i+2], &end);
            i+=2;

        } else {
            strncpy(func, argv[i], sizeof(func) - 1);
            func[sizeof(func) - 1] = '\0';
        }
    }

    char *buffer;
    size_t bufsize = 32;
    size_t characters;

    buffer = (char *)malloc(bufsize * sizeof(char));
    if( buffer == NULL)
    {
        fprintf(stderr, "FATAL ERROR: No memory available\n");
        exit(1);
    }


    while((characters = getline(&buffer,&bufsize,stdin)) != -1){
        
        //Default size
        if(size == 0){
            
            double test[256] = { 0 };
            char * token = strtok(buffer, " ");
            int i = 0;
            char* end;
            //Populating the double array with the elements that we got from the line
            while(token != NULL){
                test[i] = strtod(token, &end);
                token = strtok(NULL, " ");
                i++;
                if(i >= 256){
                    int temp = size;
                    
                    if(size != i){
                        size = i;
                    }
                    
                    double test1[size];

                    i = 0;
                    while(test[i] != 0){
                        test1[i] = test[i];
                        i++;
                    }

                    int test_size = size;
                    size = temp;


                    grateful(func,test1,test_size,size,shift_v,thres,filter_v);
                    
                    i=0;
                }
            }
            //If i==0 then the i had just been reset after the last row, so we can continue to the next line
            if(i == 0){
                continue;
            }

            i = 0;
            while((test[i] != 0)){
                i++;
            }
        
            size = i;
            double test1[size];
            i = 0;
            while(test[i] != 0){
                test1[i] = test[i];
                i++;
            }

            int test_size = size;

            if(i == 0){
                continue;
            }

            grateful(func,test1,test_size,size,shift_v,thres,filter_v);
            
        } 
        //Defined size
        else if (size > 0){
            
            double test[size];
            char * token = strtok(buffer, " ");
            int i = 0;
            char* idk;
            //Dividing the line into doubles and putting them into an array
            while(token != NULL){
                test[i] = strtod(token, &idk);
                token = strtok(NULL, " ");
                i++;
                //If there are more elements than the size can hold, then we create a new array
                if(i >= size){
                    int temp = size;
                    
                    /*
                    if(size != i){
                        size = i;
                    }
                    */

                    double test1[size];
                    
                    i = 0;
                    while(test[i] != 0){
                        test1[i] = test[i];
                        i++;
                    }

                    int test_size = size;
                    size = temp;

                    if(i == 0){
                        continue;
                    }

                    grateful(func,test1,test_size,size,shift_v,thres,filter_v);
                    
                    i=0;
                }
            }

            if(i == 0){
                continue;
            }

            int temp = size;
            
            if(size != i){
                size = i;
            }
            
            double test1[size];

            i = 0;
            while(i != size){
                test1[i] = test[i];
                i++;
            }

            int test_size = size;
            size = temp;

            grateful(func,test1,test_size,size,shift_v,thres,filter_v);
        }
        
    }
    free(buffer);
    if((strcasecmp(func, "MAX") == 0) || (strcasecmp(func, "MIN") == 0) || (strcasecmp(func, "COUNT") == 0) || (strcasecmp(func, "SUM") == 0) || (strcasecmp(func, "AVG") == 0) || (strcasecmp(func, "PAVG") == 0)){
        printf("\n");    
    }
    
    return 0;
}


void grateful(char *func, double *test1, int test_size, int size, double shift_v, double thres, enum filter_type filter_v){
    if((strcasecmp(func, "MAX") == 0) || (strcasecmp(func, "MIN") == 0) || (strcasecmp(func, "COUNT") == 0) || (strcasecmp(func, "SUM") == 0) || (strcasecmp(func, "AVG") == 0) || (strcasecmp(func, "PAVG") == 0)){
        double agg = aggregate(func, test1, test_size);
        if(prec == 0){
            printf("%.0f ", agg);
        } else if (prec == 1){
            printf("%.1f ", agg);
        } else if (prec == 2){
            printf("%.2f ", agg);
        } else if (prec == 3){
            printf("%.3f ", agg);
        } else if (prec == 4){
            printf("%.4f ", agg);
        } else if (prec == 5){
            printf("%.5f ", agg);
        } else if (prec == 6){
            printf("%f ", agg);
        } else if (prec == 7){
            printf("%.7f ", agg);
        } else if (prec == 8){
            printf("%.8f ", agg);
        } else if (prec == 9){
            printf("%.9f ", agg);
        }
    } else if ((strcasecmp(func, "PRINT") == 0)){
        print(test1, test_size);
    } else if ((strcasecmp(func, "SHIFT") == 0)){
        shift(test1, test_size, shift_v);
        print(test1, test_size);
    } else if ((strcasecmp(func, "FILTER") == 0)){
        size_t panda = filter(test1, test_size, filter_v, thres);
        if(panda > 0){
            print(test1, panda);
        }
    }
}

#include<pthread.h>
#include <stdio.h>
#include <stdlib.h>

int Max[4];
//int pointer that points to the first address in the maximum array
int *l = Max;
//function to run threads and specify its work
// void param is a void pointer that must be casting when use, it represents the real address of the realative address in the array
void *runner(void  *param)
{
    int *Run;
//casting the void pointer the give the value to int pointer "run"
    Run=(int*) param;
//set the maximum number in this thread to the first value in this array section.
    int Max_Number=*Run;
//iterate 250 times what ever which section in the main array
    for(int i=0; i<250; i++)
    {
        if(*Run>Max_Number)
            Max_Number=*Run;
        Run++;
    }
//set the fist max "the max. of the i's section" 
    *l=Max_Number; //l[0] = max number from this thread
    l++; // l[1]
}
int main()
{
    pthread_t tid[4]; //array of 4 threads.
    pthread_attr_t attr; // attribute

    int ArrayInputsize=1000; //input 1000

    srand(time(NULL)); //seeding the ranmdom function

    int  x[ArrayInputsize];
        for(int i=0;i<ArrayInputsize;i++)
            x[i]=((int)rand()) %1000; // random number betweeen 0 and 999

    pthread_attr_init(&attr);
//create the 4 threads with ids , att. ,function of the thread and parametars passed to proccess in this function
    for(int i=0; i<4; i++)
    {
        pthread_create(&tid[i],&attr,runner,&x[250*i]);
    }
//waiting for the 4 threads to finish to calculate the global maximux of the array
//making the process synchronous :)
    for(int i=0; i<4; i++)
        pthread_join(tid[i],NULL);
//calculating the global maximum

    int max_1=Max[0];

    for(int i=0; i<4; i++)
    {
        printf("the max of threads number %d is : %d\n",i+1,Max[i]);
        if(Max[i]>max_1)
            max_1=Max[i];
    }
    printf("\nThe result is -------> %d\n",max_1);

    return 0;
}

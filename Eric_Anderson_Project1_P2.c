//Eric Anderson
//Project 1 - Part 2

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

//First Array Function
void *firstArraySum(void *vargp)
{
    int *fid = (int *)vargp; //Thread ID
    int farr[] = {3, 8, 12, 21, 1}; // Array to work with
    int farrSize = sizeof(farr)/sizeof(int); // Size of the array
    int farrsum = 0; //Tracking the sum

    //Adding all of the elements in the array
    for(int x = 0; x<farrSize; x++)
    {
        farrsum += farr[x];
    }

    //Printing the sum
    printf("Sum of first array :: %d \n", farrsum);
}

//Second Array Function
void *secondArraySum(void *vargp)
{
    int *sid = (int *)vargp; //Thread ID
    int sarr[] = {7, 23, 18, 15, 10}; //Array to work with
    int sarrsize =  sizeof(sarr)/sizeof(int); // Size of the array
    int sarrsum = 0; //Tracking the sum

    //Adding all of the elements in the array
    for(int y =0; y<sarrsize; y++)
    {
        sarrsum += sarr[y];
    }

    //Printing the sum
    printf("Sum of second array :: %d \n", sarrsum);
}

int main(int argc, char*argv[])
{
    //Thread ID Tracker
    pthread_t tid;

    //Creating the two threads for the two functions
    pthread_create(&tid, NULL, firstArraySum, (void *)&tid);
    pthread_create(&tid, NULL, secondArraySum,(void *)&tid);

    //Termination after the completion of threads
    pthread_exit(NULL);
    
    return 0;
}
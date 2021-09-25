//Eric Anderson
//Project 1 - Part 1

//Header files needed
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char*argv[])
{
    //Instantiating the array.
    int arr[] = {3,8,12,21,1,7,23,18,15,10};

    //Retrieving the size of the array.
    int arrSize = sizeof(arr)/sizeof(int);

    //Values for Start, End positions of array.
    int start, end;

    //Array for pipe process.
    int p[2];

    //Pipe less than 0 indicates a failure in the pipe creation.
    //So we want to exit when this happens.
    if(pipe(p) == -1)
    {
        printf("Pipe creation encountered a fault.\n");
        return 1;
    }

    //Calling the fork process.
    int pid = fork();

    //Negative pids indicate a fault occurence during the parent & child creation.
    //So we want to exit when this happens. 
    if(pid == -1)
    {
        printf("Parent and child process creation encountered a fault.\n");
        return 2;
    }
    
    //Child process.
    //It will be responsible for handling the left half of the array.
    if(pid == 0)
    {
        start = 0;
        end = arrSize / 2;
    }
    //Parent process.
    //It will be responsible for handling the right half of the array.
    else
    {
        start = arrSize / 2;
        end = arrSize;
    }
   
    //Sum Instantiation
    int sum = 0;
    int x;

    //Using starts and ends as defined by the parent and child processes,
    //we add the sum of the corresponding halfs for the array. 
    for(x = start; x<end; x++)
    {
        sum += arr[x];
    }

    //Child Process.
    //It will write it's sum in order to send it to the parent. 
    if (pid == 0)
    {
        close(p[0]);
        write(p[1], &sum, sizeof(sum));
        close(p[1]);
    }
    
    //Parent Process.
    //It will take the child's sum and add it to it's ownm
    //Giving us the total sum.
    else{
        wait(NULL);
        int childSum;
        close(p[1]);
        read(p[0], &childSum, sizeof(childSum));
        close(p[0]);
        int total = sum + childSum;
        printf("The sum of the array is :: %d \n", total);
    }

    return 0;
}
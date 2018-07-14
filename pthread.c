#include <stdio.h>
#include <string.h>
#include <pthread.h>
#define C_Limit 1000
pthread_t threads[5];
int count;
void *cas_main(void *);
void cas_run();
int cas_lock;

int main(void)
{
	int i;
	int rc;
	int status;

	count = 0;
	cas_lock = 0;

	printf("pid=%d\n", getpid());

	printf("============ CAS ============\n");
	cas_run();
	
	/*	for (i = 0; i < 5; i++)
	{	
		pthread_create(&threads[i], NULL, &thread_main, (void *)i);
		printf("%d, %ld\n", i, threads[i]);
	}

	for (i = 4; i >= 0; i--)
	{
	    rc = pthread_join(threads[i], (void **)&status);
		if (rc == 0)
		{
			printf("Completed join with thread %d status= %d\n",i, status);
		}
		else
		{
			printf("ERROR; return code from pthread_join() is %d, thread %d\n", rc, i);
         		         return -1;
		}
	}*/
	//printf("result: %d\n", count);
	return 0;
}

void *cas_main(void *arg)
{
	int i = 0;
	while(i < C_Limit) {
		//lock
		//while(compare_and_swap(&cas_lock, 0, 1));
		count++;
		//unlock
		//compare_and_swap(&cas_lock, 1, 0);
		i++;
	}
	pthread_exit((void *) 0);
}

void
cas_run() {
	int rc;
	int i;
	int status = 0;
	for (i = 0; i < 5; i++)
	{	
		pthread_create(&threads[i], NULL, &cas_main, (void *)i);
		printf("%d, %ld\n", i, threads[i]);
	}

	for (i = 4; i >= 0; i--)
	{
	    rc = pthread_join(threads[i], (void **)&status);
		if (rc == 0)
		{
			printf("Completed join with thread %d status= %d\n",i, status);
		}
		else
		{
			printf("ERROR; return code from pthread_join() is %d, thread %d\n", rc, i);
         		         return -1;
		}
	}
	printf("result: %d\n", count);
}

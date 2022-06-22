#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void*thread_main(void *arg);

int data = 0;

int main(int argc,char *argv[])
{

	pthread_t t_id_1, t_id_2;
	int pID1 = 1, pID2=2;


	if(pthread_create(&t_id_1,NULL,thread_main,(void*)&pID1)!=0)
	{
		puts("pthread_create() error");
		return -1;
	}

	if(pthread_create(&t_id_2,NULL,thread_main,(void*)&pID2)!=0)
	{
		puts("pthread_create() error");
		return -1;
	}

	sleep(10); puts("end of main");
	return 0;
}

void *thread_main(void *arg){

	int i;
//	int cnt = *((int*)arg);
	
	for(i = 0; i < 5 ; i ++){
		sleep(1); printf("pID[%d] : %d\n",*((int*)arg),++data);	
	}
}



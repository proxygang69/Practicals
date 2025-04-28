#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define max 10

int readCount = 0, var = 0;
sem_t writer,reader;
pthread_mutex_t mutex;

void *readerFunc(void *args)
{
	while(1) {
		pthread_mutex_lock(&mutex);
			readCount++;
			if(readCount == 1)
				sem_wait(&writer);
		pthread_mutex_unlock(&mutex);

		printf("\nReading is performed and the value read is: %d",var);
		pthread_mutex_lock(&mutex);
			readCount--;
			if(readCount == 0)
				sem_post(&writer);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

void *writerFunc(void *args)
{
	while(1) {
		sem_wait(&writer);
			var++;
			printf("\n\nWriting is performed and the value changed to: %d",var);
		sem_post(&writer);
		sleep(1);
	}
}

int main()
{	
	int read,write,i;

	if(sem_init(&writer,0,1) != 0) {
		printf("\nSEMAPHORE INITIALISATION FAILED!\n");
		exit(0);
	}

	if(pthread_mutex_init(&mutex,NULL) != 0) {
		printf("\nSEMAPHORE CREATION FAILED!\n");
		exit(0);	
	}

	printf("\nEnter the number of readers:");
	scanf("%d",&read);
	printf("\nEnter the number of writers:");
	scanf("%d",&write);

	pthread_t reads[max], writes[max];
	for(i=0; i<write; i++) {
		if(pthread_create(&writes[i],NULL,writerFunc,NULL) != 0) {
			printf("\nWriter thread no %d creation failed!",i+1);
		}
		else {
			printf("\n\nWriter thread no %d created!",i+1);
		}
	}

	for(i=0; i<read; i++) {
		if(pthread_create(&reads[i],NULL,readerFunc,NULL) != 0) {
			printf("\nReader thread no %d creation failed!",i+1);
		}
		else {
			printf("\n\nReader thread no %d created!",i+1);
		}
	}

	for(i=0; i<read; i++) {
		if(pthread_join(reads[i],NULL) != 0)
			printf("\nReader thread no %d failed!",i+1);
	}

	for(i=0; i<write; i++) {
		if(pthread_join(writes[i],NULL) != 0)
			printf("\nWriter thread no %d failed!",i+1);
	}
	sleep(100);
	sem_destroy(&writer);
	sem_destroy(&reader);
	pthread_mutex_destroy(&mutex);
	return 0;
}
/*************************************************************************
	> File Name: pthread_mutex.c
	> Author:likang 
	> Mail: 
	> Created Time: 2014年08月21日 星期四 21时33分02秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int shared = 0;
void increase_num(void);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int
main(void)
{
    int ret;
    pthread_t thrd1, thrd2, thrd3;
    ret = pthread_create(&thrd1,NULL,(void *)increase_num,NULL);
    ret = pthread_create(&thrd2,NULL,(void *)increase_num,NULL);
    ret = pthread_create(&thrd3,NULL,(void *)increase_num,NULL);
    pthread_join(thrd1,NULL);
    pthread_join(thrd2,NULL);
    pthread_join(thrd3,NULL);
    printf("shared = %d",shared);
    return 0;
}

void
increase_num()
{
    int i;
    for (i = 0; i < 10; i++)
    {
        if (pthread_mutex_lock(&mutex) != 0)
        {
            perror("pthread_mutex_lock");
            exit(EXIT_FAILURE);
        }
        shared++;
        if (pthread_mutex_unlock(&mutex) != 0)
        {
            perror("pthread_mutex_unlock");
            exit(EXIT_FAILURE);
        }
    }
}


/*
raghad qadah 1170142
leena bani odeh 1172351
shaymaa zaid 1170540

*/




#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <time.h>
union semun
{
    int              val;
    struct semid_ds *buf;
    ushort          *array;
};
int P0,P1,P2,P3,P4,P5;
int G_H =0;
int flagH;
int main(void)
{
    srand(getpid());
    G_H=rand()%10 +1;
    int pid;
    int pid_array[6];
    static struct sembuf acquire = {0, -1, SEM_UNDO},
    release = {0, 1, SEM_UNDO};
    int             semid,semid1, sem_value,sem_value1,sem_value2,sem_value3,sem_valu, i;
    struct semid_ds sem_buf;
    static ushort   sem_array[12] = {1,1,1,0,0,0,0,0,0,1,1,1};
    static ushort   sem_array1[2] = {2,0};
    union semun     arg;
    union semun     arg1;
    enum {p0,p1,p2,p0p1p2G,p0p1p2H,p5I,p0G,p1p2p3p4H,p1p2p3p4p5I,p3,p4,p5};
    enum {sh,rg};
    
    
    //creat semaphore
    key_t ipc_key=ftok(".", 'S');
    
    
    
    if ( (semid = semget(ipc_key, 12, IPC_CREAT |
                         0660)) == -1 )
    {
        perror("semget: IPC_CREAT | 0660");
        exit(1);
    }
    else
    {
        printf("6 semaphore\n");
    }
    arg.array = sem_array;

    if ( semctl(semid, 0, SETALL, arg) == -1 )
    {
        perror("semctl: SETALL");
        exit(3);
    }
    else
    {
        printf("ALL Values Set\n");
    }




    key_t ipc_key1=ftok(".", 'a');
    if ( (semid1 = semget(ipc_key1, 2, IPC_CREAT |
                          0660)) == -1 )
    {
        perror("semget: IPC_CREAT | 0660");
        exit(1);
    }
    else
    {
        printf("2 semaphore\n");
    }
    arg1.array = sem_array1;

    if ( semctl(semid1, 0, SETALL, arg1) == -1 )
    {
        perror("semctl: SETALL");
        exit(3);
    }
    else
    {
        printf("ALL Values Set\n");
    }

    P0 = fork();
    if(P0==0)   //p0
    {

        // Step 1 (p0 start moving to location G )

        srand(getpid());//p0
        int x=rand()%10 +1;

        acquire.sem_num = p0;
        printf("p0 start moving to location G in <%d Sec>\n",x);
        fflush(stdout);

        if ( semop(semid, &acquire, 1) == -1 )
        {
            perror("semop -- error");
            exit(3);
        }
        sleep(x);
        release.sem_num = p0p1p2G;
        if ( semop(semid, &release, 1) == -1 )
        {
            perror("semop -- error");
            exit(5);
        }
        printf("p0 got to location G\n");
        fflush(stdout);

        //step 2 (Once P0 , P1 and P2 reach location G, they walk togetherto location H)

        sleep(11-x);
        if ( (sem_value = semctl(semid, 3, GETVAL, 0)) == -1 )
        {
            perror("semctl: GETVAL");
            exit(4);
        }

        if (sem_value ==3 )
        {
            printf("p0 start moving to location H in <%d Sec>\n",G_H);
            fflush(stdout);
            printf("p1 start moving to location H in <%d Sec>\n",G_H);
            fflush(stdout);
            printf("p2 start moving to location H in <%d Sec>\n",G_H);
            fflush(stdout);
            acquire.sem_num = p0p1p2G;
            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            acquire.sem_num = p0p1p2G;
            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            acquire.sem_num = p0p1p2G;
            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            sleep(G_H);
            printf("p2 got to location H\n");
            fflush(stdout);
            printf("p0 got to location H\n");
            fflush(stdout);
            printf("p1 got to location H\n");
            fflush(stdout);
            release.sem_num = p0p1p2H;

            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }
            release.sem_num = p0p1p2H;

            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }
            release.sem_num = p0p1p2H;


            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }


        }

        //step 4(When either P3 or P4 gets to location H, P0 starts moving back to location G)
        while(sem_value1!=1 && sem_value1!=2)
        {
            if ( (sem_value1 = semctl(semid, 7, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);
            }
        }

        srand(getpid());
        int x1=rand()%10 +1;
        if(sem_value1 ==1 || sem_value1 ==2)
        {
            acquire.sem_num = p0p1p2H;
            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            printf("p0 starts moving back to location G in <%d Sec>  \n",x1);
            fflush(stdout);
            sleep(x1);
            printf("p0 got back to location G\n");
            fflush(stdout);
            release.sem_num = p0p1p2G;

            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }

            acquire.sem_num = p0p1p2H;
            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            acquire.sem_num = p0p1p2H;
            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            release.sem_num = p1p2p3p4H;
            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }
            release.sem_num = p1p2p3p4H;
            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }


        }



       //When processes P1. . .P5 reach location I, process P0 starts moving back to location A
      
        while(sem_value2!=5)
        {


            if ( (sem_value2 = semctl(semid, 8, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);

            }

        }




        if(sem_value2==5)
        {
            srand(getpid());
            int x1=rand()%10 +1;

            acquire.sem_num = p0p1p2G;
            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }

            printf("p0 start moving back to location A in <%d Sec>\n",x1);
            fflush(stdout);
            sleep(x1);
            printf("p0 got to location A \n");
            fflush(stdout);
            release.sem_num = p0;

            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }




        }

        while(1);
    }

    else if( (P1 = fork())==0) // p1


    {
    
        // step 1 p1 start moving to location G 
        srand(getpid());//p1
        int x=rand()%10 +1;

        acquire.sem_num = p1;
        printf("p1 start moving to location G in <%d Sec>\n",x);
        fflush(stdout);

        if ( semop(semid, &acquire, 1) == -1 )
        {
            perror("semop -- error");
            exit(3);
        }
        sleep(x);
        release.sem_num = p0p1p2G;
        if ( semop(semid, &release, 1) == -1 )
        {
            perror("semop -- error");
            exit(5);
        }
        printf("p1 got to location G\n");
        fflush(stdout);
        
        
        
        //step 4  P1. . .P4 start moving to location  I.
        while(sem_value1!=4)
        {
            if ( (sem_value1 = semctl(semid, 7, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);
            }
        }
        if(sem_value1==4)
        {
            srand(getpid());
            int x=rand()%10 +1;
            printf("p1 start moving to location I in <%d Sec>\n",x);
            fflush(stdout);
            release.sem_num = p1p2p3p4p5I;
            sleep(x);
            printf("p1 got to location I \n");
            fflush(stdout);
            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }


        }



       //step 6 Once process P0 gets to location A  P1,P2,P3 and P4 start moving back to location H

        while(sem_value2!=1)
        {


            if ( (sem_value2 = semctl(semid, 0, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);

            }
        }

        if(sem_value2==1)
        {
            acquire.sem_num = p1p2p3p4p5I;
            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            srand(getpid());
            int x=rand()%10 +1;

            printf("p1 start moving back to location H in <%d Sec>\n",x);
            fflush(stdout);
            release.sem_num = p1p2p3p4H;
            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }
            sleep(x);
            printf("p1 got to location H \n");
            fflush(stdout);

        }

        while(sem_valu!=1 && sem_value1!=1)
        {
            if ( (sem_valu = semctl(semid, 9, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);
            }
            if ( (sem_value1 = semctl(semid, 10, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);
            }
        }

        if(sem_valu ==1 || sem_value1 ==1)
        {
            srand(getpid());
            int x=rand()%10 +1;
            acquire.sem_num = p1p2p3p4H;
            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }

            printf("p1 start moving back to location G in <%d Sec>\n",x);
            fflush(stdout);
            release.sem_num = p0p1p2G;
            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }
            sleep(x);
            printf("p1 got back to location G\n");
            fflush(stdout);

        }
        //step 9  (When both process P3 is back to location D and process P4 is back to location E,process P1 starts moving back to location B)

        while(sem_value!=1 )
        {
            if ( (sem_value = semctl(semid, 9, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);
            }
        }
        while(sem_value1!=1)
        {
            if ( (sem_value1 = semctl(semid, 10, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);
            }
        }

        if(sem_value ==1 && sem_value1 ==1)
        {
            acquire.sem_num = p0p1p2G;
            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            srand(getpid());
            int x=rand()%10 +1;
            printf("p1 start moving back to location B in <%d Sec>\n",x);
            fflush(stdout);
            sleep(x);
            printf("p1 got back to location B\n");
            fflush(stdout);
            release.sem_num = p1;
            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }

            acquire.sem_num = sh;
            if ( semop(semid1, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }

            release.sem_num = rg;
            if ( semop(semid1, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            if ( (sem_value2 = semctl(semid1, 1, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);

            }
           
        }

        //*****************
        while(1);
    }
    else if( (P2 = fork())==0)  //p2

    {
    
      // step 1 p2 start moving to location G
        srand(getpid());//p2
        int x=rand()%10 +1;

        acquire.sem_num = p2;
        printf("p2 start moving to location G in <%d Sec>\n",x);
        fflush(stdout);

        if ( semop(semid, &acquire, 1) == -1 )
        {
            perror("semop -- error");
            exit(3);
        }
        sleep(x);
        release.sem_num = p0p1p2G;
        if ( semop(semid, &release, 1) == -1 )
        {
            perror("semop -- error");
            exit(5);
        }
        printf("p2 got to location G\n");
        fflush(stdout);
        
        
        
        // //step 4  P1. . .P4 start moving to location  I.
        while(sem_value1!=4)
        {
            if ( (sem_value1 = semctl(semid, 7, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);
            }
        }
        if(sem_value1==4)
        {

            srand(getpid());
            int x=rand()%10 +1;

            printf("p2 start moving to location I in <%d Sec>\n",x);
            fflush(stdout);
            release.sem_num = p1p2p3p4p5I;
            sleep(x);

            printf("p2 got to location I \n");
            fflush(stdout);


            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }


        }


       // step 6  Once process P0 gets to location A  P1,P2,P3 and P4 start moving back to location H
        while(sem_value2!=1)
        {


            if ( (sem_value2 = semctl(semid, 0, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);

            }
        }

        if(sem_value2==1)
        {
            acquire.sem_num = p1p2p3p4p5I;
            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            srand(getpid());
            int x=rand()%10 +1;
            printf("p2 start moving back to location H in <%d Sec>\n",x);
            fflush(stdout);
            release.sem_num = p1p2p3p4H;
            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }
            sleep(x);
            printf("p2 got to location H \n");
            fflush(stdout);

        }
        //step 8
        while(sem_value!=1 && sem_value1!=1)
        {
            if ( (sem_value = semctl(semid, 9, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);
            }
            if ( (sem_value1 = semctl(semid, 10, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);
            }
        }

        if(sem_value ==1 || sem_value1 ==1)
        {
            acquire.sem_num = p1p2p3p4H;
            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            srand(getpid());
            int x=rand()%10 +1;
            printf("p2 start moving back to location G in <%d Sec>\n",x);
            fflush(stdout);
            release.sem_num = p0p1p2G;
            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }
            sleep(x);
            printf("p2 got back to location G\n");
            fflush(stdout);

        }
        //step 9  (When both process P3 is back to location D and process P4 is back to location E,process P2 starts moving back to location C)

        while(sem_value!=1 )
        {
            if ( (sem_value = semctl(semid, 9, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);
            }
        }
        while(sem_value1!=1)
        {
            if ( (sem_value1 = semctl(semid, 10, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);
            }
        }




        if(sem_value ==1 && sem_value1 ==1)
        {
            acquire.sem_num = p0p1p2G;
            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            srand(getpid());
            int x=rand()%10 +1;
            printf("p2 start moving back to location C in <%d Sec>\n",x);
            fflush(stdout);
            sleep(x);
            printf("p2 got back to location c\n");
            fflush(stdout);
            release.sem_num = p2;
            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }
            acquire.sem_num = sh;
            if ( semop(semid1, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            release.sem_num = rg;
            if ( semop(semid1, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            if ( (sem_value2 = semctl(semid1, 1, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);

            }
          
        }

        while(1);
    }

    else if( (P3 = fork())==0)  //p3

    {
        while(sem_value1!=3)
        {
            if ( (sem_value1 = semctl(semid, 4, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);
            }
        }

        if(sem_value1==3)
        {
            //step 3 ***************************
            srand(getpid());//p2
            int x=rand()%10 +1;
            acquire.sem_num = p3;
            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            printf("p3 start moving to location H in <%d Sec>\n",x);
            fflush(stdout);
            release.sem_num = p1p2p3p4H;
            sleep(x);
            printf("p3 got to location H \n");
            fflush(stdout);

            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }


        }
        
        
        
        
         //step 4  P1. . .P4 start moving to location  I.
        while(sem_value1!=4)
        {
            if ( (sem_value1 = semctl(semid, 7, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);
            }
        }
        if(sem_value1==4)
        {
            srand(getpid());
            int x=rand()%10 +1;
            
            printf("p3 start moving to location I in <%d Sec>\n",x);
            fflush(stdout);
            sleep(x);
            printf("p3 got to location I \n");
            fflush(stdout);
            release.sem_num = p1p2p3p4p5I;
            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }


        }


      //  step 6 Once process P0 gets to location A  P1,P2,P3 and P4 start moving back to location H
        while(sem_value2!=1)
        {


            if ( (sem_value2 = semctl(semid, 0, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);

            }
        }

        if(sem_value2==1)
        {
            acquire.sem_num = p1p2p3p4p5I;
            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            srand(getpid());
            int x=rand()%10 +1;
            printf("p3 start moving back to location H in <%d Sec>\n",x);
            fflush(stdout);
            release.sem_num = p1p2p3p4H;
            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }
            sleep(x);
            printf("p3 got back to location H \n");
            fflush(stdout);

        }


// //step 7 Once process P5 gets to location F, process P3 starts moving back to location D while process P4 starts moving back to location E.
        while(sem_value3!=1)
        {
            if ( (sem_value3 = semctl(semid, 11, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);
            }
        }

        if(sem_value3==1)
        {
            srand(getpid());
            int x=rand()%10 +1;
            acquire.sem_num = p1p2p3p4H;
            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }

            printf("p3 start moving back to location D in <%d Sec>\n",x);
            fflush(stdout);

            sleep(x);
            printf("p3 got back to location D \n");
            fflush(stdout);
            release.sem_num = p3;
            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }



        }


        while(1);
    }


    else if( (P4 = fork())==0) //p4

    {
        while(sem_value1!=3)
        {
            if ( (sem_value1 = semctl(semid, 4, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);
            }
        }
        if(sem_value1==3)
        {
            //step 3*************************
            srand(getpid());//p4
            int x=rand()%10 +1;
            acquire.sem_num = p4;
            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            printf("p4 start moving to location H in <%d Sec>\n",x);
            fflush(stdout);
            release.sem_num = p1p2p3p4H;
            sleep(x);
            printf("p4 got to location H \n");
            fflush(stdout);

            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }


        }
        
       //step 4  P1. . .P4 start moving to location  I.
        while(sem_value1!=4)
        {
            if ( (sem_value1 = semctl(semid, 7, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);
            }
        }
        if(sem_value1==4)
        {
            
            srand(getpid());//p4
            int x=rand()%10 +1;
            printf("p4 start moving to location I in <%d Sec>\n",x);
            fflush(stdout);
            sleep(x);
            printf("p4 got to location I \n");
            fflush(stdout);
            release.sem_num = p1p2p3p4p5I;
            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }


        }
        
          //step 6 Once process P0 gets to location A  P1,P2,P3 and P4 start moving back to location H

        while(sem_value2!=1)
        {


            if ( (sem_value2 = semctl(semid, 0, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);

            }
        }

        if(sem_value2==1)
        {
            acquire.sem_num = p1p2p3p4p5I;
            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            srand(getpid());
            int x=rand()%10 +1;
            printf("p4 start moving back to location H in <%d Sec>\n",x);
            fflush(stdout);
            release.sem_num = p1p2p3p4H;
            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }
            sleep(x);
            printf("p4 got to location H \n");
            fflush(stdout);

        }

     //step 7 Once process P5 gets to location F, process P3 starts moving back to location D while process P4 starts moving back to location E.
        while(sem_value3!=1)
        {
            if ( (sem_value3 = semctl(semid, 11, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);
            }
        }

        if(sem_value3==1)
        {
            srand(getpid());
            int x=rand()%10 +1;
            acquire.sem_num = p1p2p3p4H;
            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }

            printf("p4 start moving back to location E in <%d Sec>\n",x);
            fflush(stdout);

            sleep(x);
            printf("p4 got back to location E \n");
            fflush(stdout);
            release.sem_num = p4;
            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }



        }


        while(1);
    }

    else if( (P5 = fork())==0) //p5

    {
    
    
    // step 3 once P0,P1 and P2 get to location H, processesP3 and P4start moving towards location H and at the same time process P5 starts    
    //moving towards location I.
        while(sem_value1!=3)
        {
            if ( (sem_value1 = semctl(semid, 4, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);
            }
        }
        if(sem_value1==3)
        {
            srand(getpid());//p5
            int x=rand()%10 +1;

            acquire.sem_num = p5;
            printf("p5 start moving to location I in <%d Sec>\n",x);
            fflush(stdout);

            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            sleep(x);
            printf("p5 got to location I \n");
            fflush(stdout);
            release.sem_num = p5I;
            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }

        }


        while(sem_value1!=4)
        {
            if ( (sem_value1 = semctl(semid, 8, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);
            }

        }
        if(sem_value1==4)
        {
            acquire.sem_num = p1p2p3p4H;
            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            acquire.sem_num = p1p2p3p4H;


            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            acquire.sem_num = p1p2p3p4H;


            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            acquire.sem_num = p1p2p3p4H;


            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }
            release.sem_num = p1p2p3p4p5I;
            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }
            acquire.sem_num = p5I;


            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }




        }
        
        //Once process P0 gets to location A p5 start moving back to location F

        while(sem_value2!=1)
        {


            if ( (sem_value2 = semctl(semid, 0, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);

            }
        }

        if(sem_value2==1)
        {
            srand(getpid());//p5
            int x5=rand()%10 +1;
            acquire.sem_num = p1p2p3p4p5I;
            if ( semop(semid, &acquire, 1) == -1 )
            {
                perror("semop -- error");
                exit(3);
            }

            printf("p5 start moving back to location F in <%d Sec>\n",x5);
            fflush(stdout);
            sleep(x5);
            printf("p5 got to location F \n");
            fflush(stdout);
            release.sem_num = p5;
            if ( semop(semid, &release, 1) == -1 )
            {
                perror("semop -- error");
                exit(5);
            }



        }



        while(1);
    }

    else   //parent
    {
        while(sem_value2!=2)
        {



            if ( (sem_value2 = semctl(semid1, 1, GETVAL, 0)) == -1 )
            {
                perror("semctl: GETVAL");
                exit(4);

            }
        }
        printf("sem_value2 %d \n",sem_value2);
        fflush(stdout);

        if(sem_value2==2)
        {
            //   printf("kill all child");
            kill(p0, 9);
            kill(p1, 9);
            kill(p2, 9);
            kill(p3, 9);
            kill(p4, 9);
            kill(p5, 9);

        }

        // while(1);
    }






    exit(0);

}

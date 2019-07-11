#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MAXSIZE 27

void die(char *s){	//synarthsh wste otan yparxei error kata thn dhmioyrgia ths shared memory na kanei exit
	perror(s);	//gia na apofygoume to segmentation fault(core dumped)
	exit(1);
}


int main(){

	int first;	//metavlhtes gia to fibonacci
	int second;	//first,second,next einai gia ton typo ths akolouthias fibonacci
	int next,c,n;	//c einai o counter kai n einai to plhthos twn gyrwn

	int shmid;	//id tou shared memory
	key_t key;	//ena koino key poy exoyn mono oi diergasies poy epikoinwnoyn me t osygkekrimeno kommati shared memory
	int *shm1,*shm2,*shm0,*shm3,*s1,*s2,*s3,*s0; //pointers gia na anaferomaste kathe fora sthn dieuthinsh ths shared memory
	key = 5678;	//edw to key mas einai ayto 
	
	if ((shmid = shmget(key, MAXSIZE, 0666)) < 0)die("shmget");	//int shmget(key,size,flags) vriskei to tmhma koinhs mnhmhs me to key kai epistrefei to anagnwristiko ths
	if ((shm1 = shmat(shmid, NULL, 0)) == (int *) -1)die("shmat");	//edw desmeysame MAXSIZE 27 kai flag 0666 h alliws IPC_CREAT poy dhmioyrgei/desmeyei ena neo kommati mnhmhs

	if ((shmid = shmget(key, MAXSIZE, 0666)) < 0)die("shmget");	//void *shmat(shmid,address,flags) syndeei to shared memory me thn mnhmh ths diergasias
	if ((shm2 = shmat(shmid, NULL, 0)) == (int *) -1)die("shmat");	//to addr einai NULL wste h dieythinsh na epilexthei aytomata apo to leitoyrgiko 
	
	if ((shmid = shmget(key, MAXSIZE, 0666)) < 0)die("shmget");	//ta vazoume ola ayta mesa se if wste se opoiadhpote apotyxia na klhthei h die
	if ((shm0 = shmat(shmid, NULL, 0)) == (int *) -1)die("shmat");	//otan aytes oi synarthseis vgaloyn error tote epistrefoyn -1 kai oxi NULL

	if ((shmid = shmget(key, MAXSIZE, 0666)) < 0)die("shmget");	//exoyme 4 koines metavlhtes 2 gia na ginei h prosthesh fibonacci,2 flags gia to plhthos twn gyrvn kai gia ton sygxronismo sto shared memory
	if ((shm3 = shmat(shmid, NULL, 0)) == (int *) -1)die("shmat");

	while (*shm3 != 0){		//oso to flag gia tous gyroys mas den einai 0 ,dhladh oso den exei teleiwsei o server 

		//Now read what the server put in the memory.
		printf("\no server evale : %d \n",*s0);
		printf("\no server evale : %d \n",*s1);
		printf("\no server evale : %d to flag\n",*s2);

		//to pairnoume gia na ypologisoyme
		first=*s0;
		second=*s1;
	
		next=first+second;	//typos/algorithmos fibonacci
		first=second;
		second=next;
		
		*shm0 = next;		//vazoyme sthn shared memory tis nees times fibonacci
		*shm1 = first;

		printf("\no client vazei : %d \n",*shm0);
		printf("\no client vazei : %d \n",*shm1);
		printf("\no client vazei : %d \n",*shm2);
	
		*shm2 = 1;		//enhmerwnoyme to flag sygxronismoy gia na kserei o server oti to allaksame 
		while (*shm2 != 0){
				sleep(1);	//perimenei na apanthsei o server
		
		}
	}
}






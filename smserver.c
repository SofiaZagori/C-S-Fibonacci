#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXSIZE 27

void die(char *s){	//synarthsh gia gia error wste na mhn exoyme segmentation fault(core dumped)
	perror(s);
	exit(1);
}



int main(){
	int c,n;	//metavlhtes gia fibonacci,c=counter,n=plhthos arithhmwn 
	int next;
	int first=0;	//arxikopoioume ta 2 prwta giati o server panta ksekina prwtos kai o client akolouthei
	int second=1;

	int shmid;	//id tou shared memory
	key_t key;	//key shared memory,mono oi diergasies me idio key exoun prosvash se ayto to kommati koinhs mnhmhs 
	int *shm1,*shm2,*shm0,*shm3,*s1,*s2,*s0,*s3;	//pointers gia na anaferomaste stis dieythinseis toy shared memory
	key = 5678;	//to idio key exw valei kai ston client 


	printf("Enter the number: \n");		//zhtame apo ton xrhsth na dwsei to plhthos arithmwn ths akolouthias fibonacci
	scanf("%d",&n);
	printf("the fibonacci sequence is: %d",first);	//vazoume to 0 prwto gt apo ekei kai meta ksekinaei o algorithmos kai den emfanizetai alliws to 0 

	
	
	if ((shmid = shmget(key, MAXSIZE, IPC_CREAT | 0666)) < 0)die("shmget");  //o shm0 einai tou fibonacci ,ston client exw grapsei analytika ti kanei h kathe synarthsh 
	if ((shm0 = shmat(shmid, NULL, 0)) == (int *) -1) die("shmat");

	if ((shmid = shmget(key, MAXSIZE, IPC_CREAT | 0666)) < 0)die("shmget");  //o shm1 einai tou fibonacci
	if ((shm1 = shmat(shmid, NULL, 0)) == (int *) -1) die("shmat");

	if ((shmid = shmget(key, MAXSIZE, IPC_CREAT | 0666)) < 0)die("shmget"); //o shm2 einai flag gia sygxronismo diergasiwn,kanonika to shm2 kai shm3 poy einai flags eprepe na ginoyn me shmatophorous dyadikous poy pairnoyn mono times 0 1 alla den eixa xrono na toys ftiaksw opote evala 2 koines metavlhtes flags 
	if ((shm2 = shmat(shmid, NULL, 0)) == (int *) -1) die("shmat");

	if ((shmid = shmget(key, MAXSIZE, IPC_CREAT | 0666)) < 0)die("shmget"); //o shm3 einai flag gia to plhthos wste na enhmerwsei ton client pote na stamathsei 
	if ((shm3 = shmat(shmid, NULL, 0)) == (int *) -1) die("shmat");
	
	s3 = shm3;
	*s3 = n;
	

	for(c=0;c<n/2;c++){	//to miso output to kanei o server kai to allo miso o client enallaks giayto einai n/2

		next=first+second;	//typos/algorithmos fibonacci -> o epomenos arithmos einai athroisma twn 2 prohgoymenwn,diaaste thn ekfwnhsh ths ergasias ton perigrafei kai ekei 
		first=second;
		second=next;
		printf(" %d \n",next);

		//put something in the memory for reading 
		s1 = shm1;		//to s einai deikths mnhmhs ths diergasias kai to shm einai to shared memory,edw ta kanw isa 
		*s1 = next;		//vazw to epomeno/athroisma twn arithmwn poy vrhka sthn metavlhth 1 kai sthn 0 vazw to amesws prohgoymeno wste na ta parei o client na ta prosthesei kai na moy epistrepsei ta kainoyria antistoixa

		s0 = shm0;
		*s0 = second;
		
		s2=shm2;		//mhdenizw to flag wste o client na kserei oti evala kati kainoyrio kai na to parei 
		*s2 = 0;

		printf("valame sto shared memory %d kai %d \n",second,next);
	

		while (*shm2 != 1){	//mexri na ta parei kai na valei nees times o client ,o server perimenei.Antistoixa kanei to idio kai o client otan perimenei ton server 
			sleep(1);
		
		}
	}
	*s3 = 0;	//ginetai 0 wste na termatisei kai o client
	s3 = shm3;
	
}


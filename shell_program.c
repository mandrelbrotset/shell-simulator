/*
 _________________________________________________
||						 						 ||
|| Name --------: SHERIFF OLAOYE		 		 ||
|| Description -: A shell simulator	         	 ||
||_______________________________________________||
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main(){
	char* execPaths = getenv("PATH");		// get all system paths

	char* paths[30] = {NULL};				// create an array and initilize items to NULL
	char* path = strtok(execPaths, ":");	// split the string

	//printf("System PATH\n");
	// split execPaths into an array so each path is an array element
	int i=0;
	while(path != NULL){
		paths[i] = path;
		//printf("%s\n", paths[i]);
		path = strtok(NULL, ":");
		i++;
	}
	printf("\n");
	
	int numOfPaths = i;		// variable to keep track of the number of PATHS available
	char input[50];			// declare char to store user input

	// infinite loop to run the shell forever
	for(;;){
		printf("Shell >>> ");			// print the shell prompt
		fgets(input, 50, stdin);		// get user input

		// quit program if user executes "quit" or "exit" in our shell
		if(strcmp(input, "quit\n") == 0 || strcmp(input, "exit\n") == 0){
			fprintf(stderr, "Exiting shell (o ^ o)\n");
			return 0;
		}else{	
			if(fork() == 0){
				// divide the user input into arguments for the execvp system call
				const char s[2] = " ";
			    char* args[20] = {NULL};
	        	char* x;
		        i = 0;
			    x = strtok(input, s);
		        while(x != NULL){
	        	        	args[i] = x;
	                		x = strtok(NULL, s);
	                		i++;
				}

				// remove \n from the last string the arguments list
				args[i - 1][strcspn ( args[i - 1], "\n" )] = '\0';
				
				char cmd[255];
				// iterate through all the paths and run users command using each PATH
				int k;
				for(k=0; k < numOfPaths; k++){
					strcpy(cmd, paths[k]);
					strcat(cmd, "/");
					strcat(cmd, args[0]);
					// remove \n (newline) from the string
					cmd[strcspn(cmd, "\n" )] = '\0';
					execvp(cmd, args);
				}
			}else{
				wait(NULL);
			}
		}
	}
}

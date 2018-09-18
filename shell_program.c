/*
 _________________________________________________
||						 ||
|| Name --------: SHERIFF OLAOYE		 ||
|| Description -: A shell simulator	         ||
||_______________________________________________||
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

// function to get the system path
void getPath(char** paths, int* pathSize);
// function to execute commands
void executeCommands(char* input, char** paths, int pathSize);

int main(){
	char* paths[30] = {NULL};		// create an array and initilize items to NULL	
	int numOfPaths;
	
	getPath(paths, &numOfPaths);	// call function to get the path
		
	char input[50];			// declare char to store user input

	// infinite loop to run the shell forever until user quits
	for(;;){
		printf("Shell >>> ");		// print the shell prompt
		fgets(input, 50, stdin);	// get user input

		// quit program if user executes "quit" or "exit" in our shell
		if(strcmp(input, "quit\n") == 0 || strcmp(input, "exit\n") == 0){
			fprintf(stderr, "Exiting shell\n");
			// exit(0);
			// return 0;
			break;
		}else{	
			if(fork() == 0){	// create a child process
				// call method to execute user commands
				executeCommands(input, paths, numOfPaths);
			}else{
				wait(NULL);
			}
		}
	}

	return 0;
}

// implementation for method to get path directories
void getPath(char** paths, int* numOfPaths){
	char* execPaths = getenv("PATH");	// get all system paths

	char* path = strtok(execPaths, ":");	// split the string

	// split execPaths into an array so each path is an array element
	int i=0;
	while(path != NULL){
		paths[i] = path;
		// printf("%s\n", paths[i]);	// print paths
		path = strtok(NULL, ":");
		i++;
	}
	printf("\n");
	
	*numOfPaths = i;	// variable to keep track of the number of paths available	
}

// implementation for method to execute commands
void executeCommands(char* input, char** paths, int pathSize){
	// divide the user input into arguments for the execvp system call
	const char s[2] = " ";
	char* args[20] = {NULL};	// create and initialize array to store arguments to NULL 
	// declare a C string to store the next extracted argument from the user input string
	char* x;
	int i = 0;
	x = strtok(input, s);
	while(x != NULL){
		args[i] = x;
	        x = strtok(NULL, s);
	        i++;
	}

	// remove \n from the last string the arguments list
	args[i - 1][strcspn ( args[i - 1], "\n" )] = '\0';
	
	char cmd[255];	// declare a char to store the user
	int k;		// declare an int to for the for loop
	// iterate through all the paths and run users command using each PATH
	for(k=0; k < pathSize; k++){
		strcpy(cmd, paths[k]);	// copy the path into cmd
		strcat(cmd, "/");	// add a forward slash to the string cmd
		strcat(cmd, args[0]);	// add the first command user enters to the string cmd
		cmd[strcspn(cmd, "\n" )] = '\0';	// remove \n from the string
		execvp(cmd, args);
	}

	fprintf(stderr, "No such command\n");	// print error message if the command doesnt exist
}

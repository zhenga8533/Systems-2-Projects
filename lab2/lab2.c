/**
 * BY SUBMITTING THIS FILE TO CARMEN, I CERTIFY THAT I HAVE PERFORMED ALL OF THE
 * WORK TO CREATE THIS FILE AND/OR DETERMINE THE ANSWERS FOUND WITHIN THIS
 * FILE MYSELF WITH NO ASSISTANCE FROM ANY PERSON (OTHER THAN THE INSTRUCTOR
 * OR GRADERS OF THIS COURSE) AND I HAVE STRICTLY ADHERED TO THE TENURES OF THE
 * OHIO STATE UNIVERSITY’S ACADEMIC INTEGRITY POLICY.
 *
 * Author: Allen Zheng
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXLINE 80 /* 80 chars per line, per command, should be enough. */

/** The setup() routine reads in the next command line string storing it in the input buffer.
The line is separated into distinct tokens using whitespace as delimiters.  Setup also 
modifies the args parameter so that it holds points to the null-terminated strings which 
are the tokens in the most recent user command line as well as a NULL pointer, indicating the
end of the argument list, which comes after the string pointers that have been assigned to
args. ***/

void setup(char iBuffer[], char *args[],int *bgrnd)
{
    int length,  /* #  characters in the command line */
        i,       /* Index for iBuffer arrray          */
        start,   /* Beginning of next command parameter           */
        j;       /* Where to place the next parameter into args[] */

    /* Read what the user enters */
    length = read(STDIN_FILENO, iBuffer, MAXLINE);  

    j = 0;
    start = -1;

    if (length == 0)
        exit(0);            					/* Cntrl-d was entered, end of user command stream */

    if (length < 0) {
        perror("error reading command");
		exit(-1);           					/* Terminate with error code of -1 */
    }
    
    /* Examine every character in the input buffer */
    for (i = 0; i < length; i++) {
 
        switch (iBuffer[i]){
		    case ' ':
		    case '\t' :          				/* Argument separators */

		        if(start != -1){
		            args[j] = &iBuffer[start];	/* Set up pointer */
		            j++;
		        }

		        iBuffer[i] = '\0'; 				/* Add a null char; make a C string */
		        start = -1;
		        break;

		    case '\n':             				/* Final char examined */
		        if (start != -1){
		            args[j] = &iBuffer[start];     
		            j++;
		        }

		        iBuffer[i] = '\0';
		        args[j] = NULL; 				/* No more arguments to this command */
		        break;

		    case '&':
		        *bgrnd = 1;
		        iBuffer[i] = '\0';
		        break;
		        
		    default :             				/* Some other character */
		        if (start == -1)
		            start = i;
		}
 
    }    
    args[j] = NULL; 							/* Just in case the input line was > 80 */
} 

int main(void) {
    char iBuffer[MAXLINE]; 		/* Buffer to hold the command entered */
    char *args[MAXLINE/2+1];	/* Command line (of 80) has max of 40 arguments */
    int bgrnd;             		/* Equals 1 if a command is followed by '&', else 0 */
    
	/* Program terminates normally inside setup */
    while (1) {

		bgrnd = 0;

		printf("Sys2Sh: ");  				/* Shell prompt */
        fflush(0);

        setup(iBuffer, args, &bgrnd);       /* Get next command */
        printf("%s %s\n", iBuffer, *args);

		
		/* (1) Fork a child process using fork() */
		int rc = fork();
		
		if (rc < 0) {
			fprintf(stderr, "fork failed\n");
			exit(1);
		} else if (rc == 0) {		/* (2) The child process will invoke execvp() */
			if (execvp(args[0], args) == -1) {
				fprintf(stderr, "execvp failed\n");
				return 1;
			}
		} else {					/* (3) If bgrnd == 0, the parent will wait, o/w continues. */
			if (bgrnd == 0) {
				int status;
				waitpid(rc, &status, 0);
			}
		}
    }
    
    return 0;
}


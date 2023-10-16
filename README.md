# OS_assignment_on_Simple_Scheduler_Section A

:---Members:---
Prakhar Agrawal(2022361)
Priyanshu Yadav(2022383)


---:Use:---
This is a simple Scheduler for performing a number of Unix commands. List of commands it can perform - 
  ls
  ls /home
  echo you should be aware of the plagiarism policy
  wc -l fib.c
  wc -c fib.c
  grep printf helloworld.c
  ls -R
  ls -l
  ./fib 40
  ./helloworld
  sort fib.c
  uniq file.txt
  cat fib.c | wc -l
  ps
  touch
  free
  pwd
  submit


  
:---Libraries used in whole project:---
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/time.h>

---:Steps to Run The Project:---
1. Download the whole project from Google Classroom.
3. Extract the zip file and navigate to the folder which contains all the downloaded data of the zip file.
4. Now select the file "Main_shell.c".
5. Now run this selected file. This file uses the other two to perform further commands as a source file for the content.

:---Description of the Logic used to develop the project:---
Various functions have been defined each specifying the work to be executed. A command line array is the main key required to execute the scheduler effectively when operating. The Scheduler basically accepts all the commands entered in a FIFO manner and executes them accordingly.

The main programme of the scheduler is mentioned in "Main_shell.c" file while the est other files are helper files like fib.c, file.txt and helloworld.c i.e - they have supporting data.
	Along with them test files are being uploaded too to have a quick try of the code like loop1.c , loop2.c and loop3.c i.e - they have trial cases.

The Shell program begins with the initialization of taking a bash command. Each bash command perform various functions and gives output accordingly viz:
1."ls" - Used to list all the files and directories in that directory.
2. "ls /home" - Lists all the files and directories in each user accordingly.
3."echo" - Would display the line or the statement correspond to it given as the output.
4."wc -l file" - It would count the number of lines given in the provided file.
5."wc -c file" would count the number of bytes in the provided file.
6."grep printf file" - It would search for a particular command in the file and print a similar command as the output.
7."ls -R" - Lists all the files and directories along with their sub-directories.
8."ls -l" - Lists all the files and directories in a vertical listing manner along with the additional information.
9."./fib 40" -
10."./helloworld" -
11."uniq file" - Removes any type of repetition in the file and gives the output accordingly.
12."sort fil" - Sorts the data of the file in an alphabetical order.
13."cat file | wc -l" - Uses the concept of pipelining and takes the output of from the file defined next to cat while wc -l counts the number of lines present in that file.
14. ps - The ps command in Linux is used to display information about the currently running processes on your system.
15. touch - The touch command in Linux and Unix-like operating systems is used to create empty files and update the access and modification timestamps of existing files.
16. free -The free command in Linux is used to display information about the system's memory usage.
17. pwd - The pwd command in Linux stands for "Print Working Directory." When you run this command in a terminal, it displays the current directory (folder) you are in.
18.submit - Just a user command input to finalise the entry of commands and allowing the scheduler to execute the process and give an output.

While the Scheduler reads the value entered splits the bash command using separator and passes on to the Shell to execute them accordingly.

---:While the functioninf of the code would be as follow:---
1. void history_display();
Demonstrates two paths of displaying the command history i.e., a basic one mode that prints the command strings, and a detailed mode where it provides additional information like PID, execution time, and duration.

2.void sig_terimnation();
	sig_terminate = 1;

3.void clean();
	free(command);
Free's the memory allocated for a command string.

4.char* read_user_input();
Functioned so as to read the command from the user in a command-line shell program ,handles the code updates the command history structure.

5.char** command_line_array();
This identifies the command user inputs and splits them to an array of words so as to pass the arguments while launching the process.
	If argv[0] == "Submit" , it continues to read to NCPU and TSLICE value and their properties from the main function. Converts integer value to string and allocate them to the array.

6.void child_process();
This portion receives the separated elements of string as array and then identifies the command name at the 0th index and functions accordingly i.e. if the condition is mentioned of that command it would give the output according to the identified command and if not then it would give an error input statement.

7.int launch();
A condition is specified to read the input value. If input value is not equal to "TERMINATE" then it reads the various properties of the process like current_time, end_time and pid; and calculates its execution_time and duration_time respectively.
	While if the sub-command is "submit" then it checks for count and fork() to be zero. On getting zero it forms a child process where it stores the properties of the commands each like its current_time, end_time and pid;and calculates its execution_time and duration_time respectively.


8.void shell_loop();
Program shell core where it takes the user commands provides an environment for them to process and executes them according to the input command given.

9.int main();
Serves as the entry point of the shell loop.
	Takes user input of NCPU and TSLICE value and checks the value at each index of command line entered and return it to Shell to further execute process.
: ---Contributions: --- 1. Prakhar Agrawal - Programmed the main code of the Simple Scheduler along with making it capable to recieve and execute various commands given as input. Functions programmed includes developing a main_shell enviornment, creating an array, taking NCPU and TSLIC values as input, preparing the test file, defining conditions etc. 2. Priyanshu Yadav - Helped in coding for the shared memory part and writing the content of readme file.

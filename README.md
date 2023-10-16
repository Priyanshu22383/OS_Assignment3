# OS_assignment_on_Simple_Shell_Section A

:---Members:---
Prakhar Agrawal(2022361)
Priyanshu Yadav(2022383)


---:Use:---
This is a simple shell for performing a number of Unix commands. List of commands it can perform - 
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


  
:---Libraries used in whole project:---
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

---:Steps to Run The Project:---
1. Download the whole project from Google Classroom.
3. Extract the zip file and navigate to the folder which contains all the downloaded data of the zip file.
4. Now select the file "Main_shell.c".
5. Now run this selected file. This file uses the other two to perform further commands as a source file for the content.

:---Description of the Logic used to develop the project:---
Various functions have been defined each specifying the work to be executed separately:struct history_command , int sig_terminate , void history_display , void sig_termination , void clean , read_user_input , command_line_array , void child_process , int launch , void background , void shell_loop and int main.

Rest other files are helper files like fib.c and file.txt i.e - they have supporting data.

The program begins with the initialization of taking a bash command.Each bash command perform various functions and gives output accordingly viz:
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
13."cat file | wc -l" - Uses the concept of pipeling and takes the output of from the file defined next to cat while wc -l counts the number of lines present in that file.
14. ps - The ps command in Linux is used to display information about the currently running processes on your system.
15. touch - The touch command in Linux and Unix-like operating systems is used to create empty files and update the access and modification timestamps of existing files.
16. free -The free command in Linux is used to display information about the system's memory usage.
17. pwd - The pwd command in Linux stands for "Print Working Directory." When you run this command in a terminal, it displays the current directory (folder) you are in

---:While the functioninf of the code would be as follow:---
1. void history_display();
Demonstrates two paths of diplaying the command history i.e. a basic one mode that prints the command strings, and a detailed mode where it provides additional information like PID, execution time, and duration.

2.void sig_terimnation();
	sig_terminate = 1;

3.void clean();
	free(command);
Free's the memory allocated for a command string.

4.char* read_user_input();
Functioned so as to read the command from the user in a command-line shell program ,handles the code updates the command history structure.

5.char** command_line_array();
This identifies the command user inputs and splits them to an array of words so as to pass the arguments while launching the process.

6.void child_process();
This protion recieves the splitted elements of string as array and then identifies the command name at the 0th index and functions accordingly i.e. if the condition is mentioned of that command it would give the output according to the identified command and if not then it would give an error input statement.

7.int launch();

8.void shell_loop();
Program shell core where it takes the user commands provides an enviornment for them to process and executes them according to the input command given.

9.int main();
Serves as the entry point of the shell loop.

10.int file();

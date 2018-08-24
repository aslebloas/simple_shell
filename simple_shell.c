#include "holberton.h"

/**                                                                                                                                               
 * main - simple shell                                                                                                                            
 * @argc: counts of arguments                                                                                                                     
 * @argv: string containing the arguments                                                                                                         
 *                                                                                                                                                
 * Return: 0 on success                                                                                                                           
 */
int main(int argc, char **argv)
{
        int read_c = 1, i; /* number of bytes read */
        int status, error;
        size_t nbytes = 200; /* number of bytes for the stream */
        char *string, *full_path; /* command line */
        pid_t child;
        char **command = NULL, **path_array = NULL;
        char *path;

        struct stat st; /* structure of stat output */

        /* Handle non-interactive mode */
        if (argc > 1)
                string = argv[1];

        /* Interactive mode */
        /* Programs runs until Ctrl+D is pressed */
        while (read_c != EOF)
        {
                /* Display a prompt */
                write(STDIN_FILENO, "#cisfun$ ", 9);

                /* Allocated memory for the string command */
                string = malloc(nbytes + 1);

                /* Get user input */
                read_c = getline(&string, &nbytes, stdin);
                if (read_c == -1)
                {
                        exit(90);
                        printf("getline() failed");
                }
                else if (read_c == 1)
                        continue;
                command = splitstring(string);

                if (!strcmp(command[0], "exit"))
                {
                        free(command);
                        return (0);
                }

                /* check if str is in directory */
                if (stat(string, &st) == 0)
                {
                        /* program is present */
                        /* fork program */
                        child = fork();
                        if (child == 0)
                        {
                                /* execute the command in child */
                                error = execve(command[0], command, NULL);
                                if (error == -1)
                                        perror("Error:");
                                else
                                        return (0);
                        }
                        wait(&status);

                        free(command);
                        free(string);

                }
                else if (read_c == 1)
                {
                        printf("./shell: No such file or directory\n");

                        free(command);
                        free(string);
                }
                else
                {
                        /* Store the path directories into an array */
                        path_array = tok_path();
                        /* check if the concatenation of the command with */
                        /* the elements of the path array exist */
                        /*i = 0;*/
                        for(i = 0; path_array[i] != '\0'; i++)
                        {
                                printf("path before concat %s\n", path_array[i]);

                                full_path = path_concat(path_array[i], command[0]);
                                printf("full path right now: %s\n", full_path);

                                if (access(full_path, X_OK) == 0)
                                {
                                        printf("Found it!\n");
                                        /* program is present */
                                        /* fork program */
                                        child = fork();
                                        if (child == 0)
                                        {
                                                printf("in the child\n");
                                                /* execute the command in child */
                                                error = execve(full_path, command, NULL);
                                                if (error == -1)
                                                        perror("Error:");
                                                else
                                                        return (0);
                                        }
                                        wait(&status);

                                        free(command);
                                        free(full_path);
                                        free(string);
                                }
                                printf("This is the i: %d\n", i);
                        }
                }
        }

        return (0);
}
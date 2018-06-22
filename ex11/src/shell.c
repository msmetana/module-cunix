#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "../include/minishell.h"

hashtable_t *ht;

int lsh_ls(char **args);
int lsh_echo(char **args);
int lsh_export(char **args);
int lsh_env(char **args);
int lsh_exit(char **args);

char *builtin_str[] = {
  "ls",
  "echo",
  "export",
  "env",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &lsh_ls,
  &lsh_echo,
  &lsh_export,
  &lsh_env,
  &lsh_exit
};

int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

int lsh_ls(char **args)
{
  struct dirent *pDirent;
  DIR *pDir;

  pDir = opendir (args[1]);

  if (pDir == NULL){
    fprintf(stderr, "lsh: ожидается аргумент для \"ls\"\n");
    return 0;
  }
  printf ("$_>");
  while ((pDirent = readdir(pDir)) != NULL) {
    if(pDirent->d_name[0] != '.')
      printf ("%s ", pDirent->d_name);
  }

  printf ("\n");
  closedir (pDir);

  return 1;
}

int lsh_echo(char **args)
{
  int i;
  char *word;

  word = malloc(10*sizeof(char));
  i = 1;

  while(args[i] != NULL){
    if( i > 1)
      printf(" ");

    if(args[i][0] == '$'){
      strcpy(word, hash_get(ht, args[i] + 1));
      printf("%s", word);
      i++;
      continue;
    }

    printf("%s", args[i]);
    i++;
  }
  free(word);
  printf("\n");

  return 1;
}

int lsh_export(char **args)
{
  char *key, *data, *p, *word;

  if(args[1] == NULL)
    return 1;

  word = args[1];
  p = strtok(word, "=");
  key = malloc((strlen(p)+1)*sizeof(char ));
  strcpy(key, p);
  printf("\n");

  while(p != NULL){
    data = malloc((strlen(p)+1)*sizeof(char *));
    strcpy(data, p);
    p = strtok(NULL, "=");
  }

  if(key == data)
    return 1;

  hash_set(ht, key, (void*)data);

  return 1;
}

int lsh_env(char **args)
{
  hash_print(ht);

  return 1;
}

int lsh_exit(char **args)
{
  printf("\n");

  return 0;
}

int lsh_launch(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();

  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1)
      perror("lsh");

    exit(EXIT_FAILURE);
  }
  else
    if (pid < 0) {
    perror("lsh");
  } else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int lsh_execute(char **args)
{
  int i;

  if (args[0] == NULL)
    return 1;

  for (i = 0; i < lsh_num_builtins(); i++)
    if (strcmp(args[0], builtin_str[i]) == 0)
      return (*builtin_func[i])(args);

  return lsh_launch(args);
}

char *lsh_read_line(void)
{
  char *line;
  ssize_t bufsize;

  line = NULL;
  bufsize = 0;

  getline(&line, &bufsize, stdin);

  return line;
}

char **lsh_split_line(char *line)
{
  int bufsize, position;
  char **tokens;
  char *token;

  bufsize = 64;
  position = 0;
  tokens = malloc(bufsize * sizeof(char*));

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, " \t\r\n\a");

  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += 64;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, " \t\r\n\a");
  }

  tokens[position] = NULL;

  return tokens;
}

void lsh_loop(void)
{
  char *line;
  char **args;
  int status;

  do {
    printf("$_>");
    line = lsh_read_line();
    args = lsh_split_line(line);
    status = lsh_execute(args);

    free(line);
    free(args);
  } while (status);
}

int main(int argc, char **argv)
{
  ht = hash_create(10);

  lsh_loop();
  printf("\n");
  hash_destroy(ht);

  return EXIT_SUCCESS;
}


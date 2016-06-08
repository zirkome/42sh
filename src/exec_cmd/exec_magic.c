/*
** exec_magic.c for exec_magic in /home/linard_f/tmp/42sh-2017-fillon_g
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Sat May 25 12:59:13 2013 fabien linardon
** Last update Sun May 26 22:12:20 2013 guillaume fillon
*/

#include "42s.h"
#include "builtins.h"

char	*magic_son(int *pipefd, char **cmd, char **av, t_shenv *shenv)
{
  close(pipefd[0]);
  if (dup2(pipefd[1], 1) == -1)
    return (magic_error());
  if (lookfor_type(av, cmd, shenv, -1) == EXIT_FAILURE)
    return (NULL);
  if (is_pipe(cmd) && !is_mass_redirect(cmd) &&
      is_builtin(cmd, NULL))
    return (NULL);
  return ("Success.\n");
}

static int	is_mass_builtin(char **cmd)
{
  int		rk;

  rk = -1;
  while (cmd[++rk])
    {
      if (cmd[rk] && !strcmp(cmd[rk], "|"))
	++rk;
      if (cmd[rk] && is_builtin(&cmd[rk], NULL))
	return (TRUE);
      while (cmd[rk] && cmd[++rk] && strcmp(cmd[rk], "|"));
      if (!cmd[rk])
	--rk;
    }
  return (FALSE);
}

char	*exec_magic(char **cmd, int *ret, t_shenv *shenv, char **av)
{
  int	pipefd[2];
  pid_t	pid;
  char	*str;

  str = NULL;
  if (pipe(pipefd) == -1 || (pid = fork()) == -1)
    return (magic_error());
  if (pid == 0)
    {
      create_real_son(getpid());
      if (!magic_son(pipefd, cmd, av, shenv) && (*ret = -1))
      	return (NULL);
    }
  else
    {
      if (is_mass_builtin(cmd))
	waitpid(pid, &shenv->status, WUNTRACED);
      close(pipefd[1]);
      str = magic_read(pipefd[0]);
      if (!is_mass_builtin(cmd))
	waitpid(pid, &shenv->status, WUNTRACED);
      back_to_shell(shenv->pid);
    }
  return (str);
}

char	*magic_error(void)
{
  fprintf(stderr, "%s\n", strerror(errno));
  return (NULL);
}

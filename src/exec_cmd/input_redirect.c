/*
** input_redirect.c for input_redirect in /home/linard_f/42sh/exec_cmd
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Sat Mar 23 13:34:49 2013 fabien linardon
** Last update Sun May 26 12:12:46 2013 fabien linardon
*/

#include "42s.h"

static int	input_no_fork(int fd, t_shenv *shenv, char **av, char **cmd)
{
  if (dup2(fd, 0) == -1)
    return (my_error(""));
  return (lookfor_type(&av[1], cmd, shenv, -1));
}

int	exec_dbl_input(char **av, char **cmd, t_shenv *shenv, char *str)
{
  pid_t	pid;
  int	pipefd[2];

  if (pipe(pipefd) == -1)
    return (my_error(""));
  if ((pid = fork()) == -1)
    return (my_error(""));
  if (!pid)
    {
      close(pipefd[0]);
      if (dup2(pipefd[1], 1) == -1)
	return (my_error(""));
      write(1, str, strlen(str));
      if (strlen(str))
	xfree(1, &str);
      return (EXIT_FAILURE);
    }
  else
    {
      wait(&shenv->status);
      close(pipefd[1]);
      if (dup2(pipefd[0], 0) == -1)
	return (my_error(""));
    }
  return (lookfor_type(&av[1], cmd, shenv, -1));
}

int	simple_input(char **av, char **cmd, t_shenv *shenv, int n)
{
  pid_t	pid;
  int	fd;

  if ((fd = open(av[1], O_RDONLY)) == -1 && my_error(av[1]))
    return ((!n) ? (-1) : (EXIT_FAILURE));
  if (n == 0)
    {
      if ((pid = fork()) == -1)
	return (my_error(""));
      if (!pid)
	{
	  create_real_son(getpid());
	  if (dup2(fd, 0) == -1)
	    return (my_error(""));
	  return (lookfor_type(&av[1], cmd, shenv, -1));
	}
      else
	{
	  wait(&shenv->status);
	  back_to_shell(shenv->pid);
	  close(fd);
	  handle_status(pid, cmd[0], shenv);
	}
    }
  return ((n) ? (input_no_fork(fd, shenv, av, cmd)) : (EXIT_SUCCESS));
}

int	double_input(char **av, char **cmd, t_shenv *shenv)
{
  char	buf[4000];
  char	*tmp;
  char	*str;
  int	len;

  if (!(tmp = my_strcat(av[1], "\n")))
    return (EXIT_FAILURE);
  str = "";
  write(shenv->tty_fd , "> ", 2);
  while ((len = read(0, buf, 4000)) > 0)
    {
      buf[len] = 0;
      if (!strcmp(buf, tmp))
	{
	  xfree(1, &tmp);
	  return (exec_dbl_input(av, cmd, shenv, str));
	}
      else
	{
	  if (!(str = my_strcat(str, buf)))
	      return (EXIT_FAILURE);
	  write(shenv->tty_fd, "> ", 2);
	}
    }
  return (EXIT_FAILURE);
}

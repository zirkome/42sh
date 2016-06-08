/*
** output_redirect.c for output_redirect in /home/linard_f/42sh/exec_cmd
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Sat Mar 23 12:49:13 2013 fabien linardon
** Last update Sun May 26 11:32:54 2013 fabien linardon
*/

#include "42s.h"

static int	out_no_fork(int fd, t_shenv *shenv, char **av, char **cmd)
{
  if (dup2(fd, 1) == -1)
    return (my_error(""));
  return (lookfor_type(&av[1], cmd, shenv, -1));
}

int	simple_output(char **av, char **cmd, t_shenv *shenv, int n)
{
  pid_t	pid;
  int	fd;

  if ((fd = open(av[1], O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
    return ((!n) ? (-1) : (EXIT_FAILURE));
  if (n == 0)
    {
      if ((pid = fork()) == -1)
	return (my_error(""));
      if (!pid)
	{
	  create_real_son(getpid());
	  if (dup2(fd, 1) == -1)
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
  return ((n) ? (out_no_fork(fd, shenv, av, cmd)) : (EXIT_SUCCESS));
}

int	double_output(char **av, char **cmd, t_shenv *shenv, int n)
{
  pid_t	pid;
  int	fd;

  if ((fd = open(av[1], O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
    return ((!n) ? (-1) : (EXIT_FAILURE));
  if (!n)
    {
      if ((pid = fork()) == -1)
	return (my_error(""));
      if (!pid)
	{
	  create_real_son(getpid());
	  if (dup2(fd, 1) == -1)
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
  return ((n) ? (out_no_fork(fd, shenv, av, cmd)) : (EXIT_SUCCESS));
}

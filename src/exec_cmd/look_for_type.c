/*
** look_for_type.c for look_for_type.c in /home/linard_f/42sh/42sh/42sh-2017-fillon_g
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Wed May 15 10:44:22 2013 fabien linardon
** Last update Sun May 26 22:24:58 2013 guillaume fillon
*/

#include "42s.h"
#include "builtins.h"

static int	double_left(char **av, char **cmd, t_shenv *shenv, int n)
{
  pid_t		pid;
  int		ret;

  if (n == 0)
    {
      if ((pid = fork()) == -1)
	return (my_error(""));
      if (!pid)
	{
	  create_real_son(getpid());
	  return (double_input(&av[0], cmd, shenv));
	}
      else
	{
	  waitpid(-1, &shenv->status, WUNTRACED);
	  back_to_shell(shenv->pid);
	  ret = handle_status(pid, cmd[0], shenv);
	}
    }
  else
    return (double_input(&av[0], cmd, shenv));
  if (shenv->status)
    return (shenv->status);
  return (ret);
}

static int	my_redirection(char **av, char **cmd, t_shenv *shenv, int n)
{
  int		ret;

  if (!strcmp(av[0], ">"))
    ret = simple_output(&av[0], cmd, shenv, n);
  else if (!strcmp(av[0], ">>"))
    ret = double_output(&av[0], cmd, shenv, n);
  else if (!strcmp(av[0], "<"))
    ret = simple_input(&av[0], cmd, shenv, n);
  else if (!strcmp(av[0], "<<"))
    ret = double_left(av, cmd, shenv, n);
  return (ret);
}

static int	my_pipe_fork(char **cmd, t_shenv *shenv)
{
  pid_t		pid;
  int		ret;

  if ((pid = fork()) == -1)
    return (my_error(""));
  if (!pid)
    {
      create_real_son(getpid());
      if (!is_pipe(cmd) && my_pipe(cmd, shenv) == EXIT_FAILURE)
	return (-1);
      else if (exec_bin(cmd, shenv) == EXIT_FAILURE)
	return (-1);
    }
  else
    {
      waitpid(-1, &shenv->status, WUNTRACED);
      back_to_shell(shenv->pid);
      ret = handle_status(pid, cmd[0], shenv);
    }
  if (shenv->status)
    return (shenv->status);
  return (ret);
}

int	lookfor_type(char **av, char **cmd, t_shenv *shenv, int n)
{
  int	rk;
  int	ret;

  rk = -1;
  while (av && av[++rk])
    if (is_redirect(av[rk]) == TRUE)
      {
	if ((ret = my_redirection(&av[rk], cmd, shenv, n)) == EXIT_FAILURE)
	  return (EXIT_FAILURE);
	return ((ret == -1) ? (-1) : (EXIT_SUCCESS));
      }
  if (!n)
    {
      if ((ret = my_pipe_fork(cmd, shenv)) == -1)
	return (EXIT_FAILURE);
    }
  else
    {
      if (!is_pipe(cmd) && my_pipe(cmd, shenv) == EXIT_FAILURE)
	return (EXIT_FAILURE);
      else if (exec_bin(cmd, shenv) == EXIT_FAILURE)
	return (EXIT_FAILURE);
    }
  return ((ret) ? (-1) : (EXIT_SUCCESS));
}

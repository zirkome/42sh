/*
** pipe.c for pipe in /home/linard_f//42sh/exec_cmd
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Tue Mar 19 15:21:15 2013 fabien linardon
** Last update Sat May 25 19:44:39 2013 fabien linardon
*/

#include "42s.h"

int	is_pipe(char **cmd)
{
  int	rk;

  rk = -1;
  while (cmd[++rk])
    if (!strcmp(cmd[rk], "|"))
      return (0);
  return (-1);
}

static int	first_side_pipe(char **cmd, t_shenv *shenv, int pipefd[2])
{
  close(pipefd[0]);
  if (dup2(pipefd[1], 1) == -1)
    return (my_error(""));
  return (exec_bin(cmd, shenv));
}

static int	second_side_pipe(char **cmd, t_shenv *shenv, int pipefd[2])
{
  close(pipefd[1]);
  if (dup2(pipefd[0], 0) == -1)
    return (my_error(""));
  if (!is_pipe(cmd))
    return (my_pipe(cmd, shenv));
  return (exec_bin(cmd, shenv));
}

int	my_pipe(char **cmd, t_shenv *shenv)
{
  pid_t	pid;
  int	pipefd[2];
  int	rk;

  rk = -1;
  while (cmd[++rk] && strcmp(cmd[rk], "|"));
  cmd[rk] = NULL;
  if (pipe(pipefd) == -1)
    return (my_error(""));
  if ((pid = fork()) == -1)
    return (my_error(""));
  if (!pid && first_side_pipe(cmd, shenv, pipefd) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  else if (second_side_pipe(&cmd[rk + 1], shenv, pipefd) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

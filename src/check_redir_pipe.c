/*
** check_redir_pipe.c for 42sh in /home/degreg_e/projets/42sh
**
** Made by enzo degregorio
** Login   <degreg_e@epitech.net>
**
** Started on  Sat Mar 23 21:11:04 2013 enzo degregorio
** Last update Sat May 25 16:39:33 2013 fabien linardon
*/

#include "42s.h"

static int	count_redirection(char **cmd)
{
  int		i;
  int		red_l;
  int		red_r;

  i = -1;
  red_l = 0;
  red_r = 0;
  while (cmd[++i] != NULL)
    {
      if (!strcmp(cmd[i], "<") || !strcmp(cmd[i], "<<"))
	++red_l;
      else if (!strcmp(cmd[i], ">") ||
	       !strcmp(cmd[i], ">>") || !strcmp(cmd[i], ">&"))
	++red_r;
    }
  if (red_l > 1)
    return (-1);
  else if (red_r > 1)
    return (-2);
  return (EXIT_SUCCESS);
}

int	check_redirection(char **cmd,
			  __attribute__((unused)) t_shenv *shenv)
{
  int	i;
  int	err;

  i = -1;
  while (cmd[++i + 1] != NULL);
  if (!strcmp(cmd[i], "<") || !strcmp(cmd[i], "<<") ||
      !strcmp(cmd[i], ">") || !strcmp(cmd[i], ">>") ||
      !strcmp(cmd[i], ">&") || !strcmp(cmd[i], "<<") ||
      (is_mass_redirect(cmd) && len_tab(cmd) < 3))
    {
      fprintf(stderr, "Invalid command syntax.\n");
      return (EXIT_FAILURE);
    }
  if ((err = count_redirection(cmd)) == -1 || err == -2)
    {
      if ((err = count_redirection(cmd)) == -1)
	fprintf(stderr, "Ambigious input redirection.\n");
      else if (err == -2)
	fprintf(stderr, "Ambigious output redirection.\n");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

static int	check_syntax_pipe(char **cmd, int i)
{
  if ((!strcmp(cmd[i], "|") && !strcmp(cmd[i + 1], "|")) ||
      (!strcmp(cmd[i], "|") && !strcmp(cmd[i + 1], "<")) ||
      (!strcmp(cmd[i], "|") && !strcmp(cmd[i + 1], "<<")) ||
      (!strcmp(cmd[i], "|") && !strcmp(cmd[i + 1], ">")) ||
      (!strcmp(cmd[i], "|") && !strcmp(cmd[i + 1], ">>")) ||
      (!strcmp(cmd[i], "|") && !strcmp(cmd[i + 1], ">&")) ||
      (!strcmp(cmd[i], "<") && !strcmp(cmd[i + 1], "|")) ||
      (!strcmp(cmd[i], "<<") && !strcmp(cmd[i + 1], "|")) ||
      (!strcmp(cmd[i], ">") && !strcmp(cmd[i + 1], "|")) ||
      (!strcmp(cmd[i], ">>") && !strcmp(cmd[i + 1], "|")) ||
      (!strcmp(cmd[i], ">&") && !strcmp(cmd[i + 1], "|")))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int	check_pipe(char **cmd, __attribute__((unused)) t_shenv *shenv)
{
  int	i;

  i = -2;
  while (cmd[++i + 1] != NULL);
  if (!strcmp(cmd[0], "|") || !strcmp(cmd[i], "|"))
    {
      fprintf(stderr, "Invalid null command.\n");
      return (EXIT_FAILURE);
    }
  i = -1;
  while (cmd[++i + 1] != NULL)
    {
      if (check_syntax_pipe(cmd, i) == EXIT_FAILURE)
	{
	  fprintf(stderr, "Invalid command syntax.\n");
	  return (EXIT_FAILURE);
	}
    }
  return (EXIT_SUCCESS);
}

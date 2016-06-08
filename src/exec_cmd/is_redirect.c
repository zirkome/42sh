/*
** is_redirect.c for is_redirect in /home/linard_f//42sh/exec_cmd
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Tue Mar 19 14:42:39 2013 fabien linardon
** Last update Tue May 21 14:38:53 2013 fabien linardon
*/

#include "42s.h"

int	is_redirect(char *cmd)
{
  if (cmd && (!strcmp(cmd, "<") || !strcmp(cmd, ">") ||
	      !strcmp(cmd, "<<") || !strcmp(cmd, ">>")))
    return (TRUE);
  return (FALSE);
}

int	is_mass_redirect(char **cmd)
{
  int	rk;

  rk = -1;
  while (cmd[++rk])
    if (!strcmp(cmd[rk], "<") || !strcmp(cmd[rk], ">") ||
	!strcmp(cmd[rk], "<<") || !strcmp(cmd[rk], ">>"))
      return (TRUE);
  return (FALSE);
}

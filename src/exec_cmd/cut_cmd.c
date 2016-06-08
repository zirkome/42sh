/*
** cut_cmd.c for cut_cmd$ in /home/linard_f//42sh/exec_cmd
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Tue Mar 19 14:38:21 2013 fabien linardon
** Last update Sun May 26 16:33:21 2013 nicolas bridoux
*/

#include "42s.h"

static int	lenght_of_cmd(char **cmd)
{
  int		rk;
  int		len;

  rk = -1;
  len = 0;
  if (!cmd)
    return (-1);
  if (is_redirect(cmd[0]) == TRUE)
    rk = 1;
  while (cmd[++rk] && is_redirect(cmd[rk]) == FALSE)
    ++len;
  if (cmd[rk] == NULL)
    return (len);
  if (is_redirect(cmd[rk]) == TRUE)
    ++rk;
  while (cmd[++rk] && is_redirect(cmd[rk]) == FALSE)
    ++len;
  return (len);
}

static char	**fill_new_cmd(char **cmd, char **new, int rk, int i)
{
  if (is_redirect(cmd[rk]) == TRUE)
    ++rk;
  while (cmd[++rk] && is_redirect(cmd[rk]) == FALSE)
    new[++i] = my_strdup(cmd[rk]);
  new[i + 1] = NULL;
  return (new);
}

char	**cut_cmd(char **cmd)
{
  char	**new;
  int	rk;
  int	i;

  if (!cmd)
    return (NULL);
  if ((new = malloc((lenght_of_cmd(cmd) + 1) * sizeof(char *))) == NULL)
    {
      fprintf(stderr, "Can't perform malloc.\n");
      return (NULL);
    }
  rk = -1;
  i = -1;
  if (is_redirect(cmd[0]) == TRUE)
    rk = 1;
  while (cmd[++rk] && is_redirect(cmd[rk]) == FALSE)
    new[++i] = my_strdup(cmd[rk]);
  if (cmd[rk] == NULL && (new[i + 1] = NULL) == NULL)
    return (new);
  return (fill_new_cmd(cmd, new, rk, i));
}

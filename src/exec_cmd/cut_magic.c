/*
** cut_magic.c for cut_magic in /home/linard_f/tmp/42sh-2017-fillon_g
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Thu May 23 15:37:00 2013 fabien linardon
** Last update Sun May 26 11:40:47 2013 fabien linardon
*/

#include "42s.h"

void	fill_magic(char **cmd, char **magic, char **new, int len)
{
  int	rk;
  int	i;
  int	j;

  rk = -1;
  i = -1;
  j = -1;
  while (++rk != len)
    {
      if (i == -1 || cmd[i])
	++i;
      if (cmd[i] && strcmp(cmd[i], "`"))
	new[rk] = my_strdup(cmd[i]);
      else if (cmd[i] && !strcmp(cmd[i], "`"))
	{
	  while (magic && magic[++j])
	    new[rk++] = my_strdup(magic[j]);
	  if (j)
	    --rk;
	  while (cmd[++i] && strcmp(cmd[i], "`"));
	}
      if (rk == len)
	--rk;
    }
  new[rk] = NULL;
}

char	**cut_magic(char **cmd, char **magic)
{
  int	len;
  char	**new;

  if (!(len = len_of_magic(cmd, magic)))
    return (NULL);
  if (!(new = malloc((len + 1) * sizeof(char*))))
    {
      fprintf(stderr, "Not enough memory.\n");
      return (NULL);
    }
  fill_magic(cmd, magic, new, len);
  return (new);
}

int	len_of_magic(char **cmd, char **magic)
{
  int	rk;
  int	n;

  rk = -1;
  n = 0;
  while (cmd && cmd[++rk])
    {
      if (strcmp(cmd[rk], "`"))
	++n;
      else
	while (cmd[++rk] && strcmp(cmd[rk], "`"));
    }
  rk = 0;
  while (magic && magic[rk++]);
  return ((!rk) ? (rk + n) : ((rk - 1) + n));
}

char	**my_magic_cmd(char **cmd)
{
  int	rk;
  char	**new;

  rk = -1;
  while (cmd[++rk] && strcmp(cmd[rk], "`"));
  if (!rk)
    return (NULL);
  if (!(new = malloc((rk + 1) * sizeof(char*))))
    {
      fprintf(stderr, "Not enough memory.\n");
      return (NULL);
    }
  rk = -1;
  while (cmd[++rk] && strcmp(cmd[rk], "`"))
    new[rk] = my_strdup(cmd[rk]);
  new[rk] = NULL;
  return (new);
}

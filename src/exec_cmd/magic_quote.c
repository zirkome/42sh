/*
** magic_quote.c for magic_quot in /home/linard_f/tmp/42sh-2017-fillon_g
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Wed May 22 16:06:22 2013 fabien linardon
** Last update Sun May 26 21:15:07 2013 nicolas bridoux
*/

#include "42s.h"

char	**magic_quote(char **cmd, t_shenv *shenv, int *ret)
{
  int	rk;
  char	**new;
  char	*str;
  char	**av;

  av = NULL;
  rk = -1;
  if (!check_magic(cmd) && (*ret = EXIT_FAILURE))
    return (NULL);
  while (cmd[++rk] && strcmp(cmd[rk], "`"));
  if (!strcmp(cmd[rk], "`"))
    av = my_magic_cmd(&cmd[rk + 1]);
  rk = -1;
  new = cut_cmd(av);
  if (check_path(new, shenv, 0) == FALSE && (*ret = EXIT_FAILURE))
    return (NULL);
  if (!new || (!(str = exec_magic(new, ret, shenv, av)) && (*ret)))
    return (NULL);
  rk = -1;
  while (str && str[++rk])
    if (str[rk] == '\n')
      str[rk] = ' ';
  av = my_str_to_argtab(str, -1, -1, 0);
  av = cut_magic(cmd, av);
  return (av);
}

int	is_magic(char **cmd)
{
  int	rk;

  rk = -1;
  while (cmd[++rk])
    if (!strcmp(cmd[rk], "`"))
      return (TRUE);
  return (FALSE);
}

int	check_magic(char **cmd)
{
  int	n;
  int	rk;

  n = 0;
  rk = -1;
  while (cmd[++rk])
    if (!strcmp(cmd[rk], "`"))
      ++n;
  if (n != 2 && n)
    {
      fprintf(stderr, "Syntax error on magic quote.\n");
      return (FALSE);
    }
  return (TRUE);
}

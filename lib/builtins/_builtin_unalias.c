/*
** _builtins_alias.c for 42sh in /home/fillon_g/projets/42sh-2017-fillon_g/srcs/builtins
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.net>
**
** Started on  Wed May  8 17:19:46 2013 guillaume fillon
** Last update Sun May 19 04:59:29 2013 guillaume fillon
*/

#include "builtins.h"
#include "list.h"

int		_builtin_unalias(char **cmd, t_shenv *shenv)
{
  int		i;

  i = 1;
  if (cmd[1] == NULL)
    {
      fprintf(stderr, "unalias: not enough argmuments\n");
      return (EXIT_FAILURE);
    }
  while (cmd[i])
    {
      my_rm_eq(&shenv->alias, cmd[i]);
      ++i;
    }
  return (EXIT_SUCCESS);
}

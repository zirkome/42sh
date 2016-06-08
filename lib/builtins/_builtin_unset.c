/*
** _builtins_unset.c for builtin 42sh in /home/degreg_e/
**
** Made by enzo degregorio
** Login   <degreg_e@epitech.net>
**
** Started on  Fri May 10 16:31:33 2013 enzo degregorio
** Last update Sun May 26 12:24:06 2013 nicolas bridoux
*/

#include "builtins.h"
#include "list.h"

int	_builtin_unset(char **cmd, t_shenv *shenv)
{
  int	i;

  if (cmd == NULL || cmd[1] == NULL)
    {
      fprintf(stderr, "familial_sh: unset: Too few arguments\n");
      return (EXIT_FAILURE);
    }
  i = 1;
  while (cmd[i] != NULL)
    {
      my_rm_eq(&shenv->lvar, cmd[i]);
      ++i;
    }
  return (EXIT_SUCCESS);
}

/*
** _unsetenv.c for 42sh in /home/kokaz/projets/42sh/srcs/builtins
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.eu>
**
** Started on  Tue Mar  19 01:20:33 2013 guillaume fillon
** Last update Sun May 26 12:12:00 2013 nicolas bridoux
*/

#include "builtins.h"
#include "list.h"

int		_builtin_unsetenv(char **cmd, t_shenv *shenv)
{
  if (cmd[1] == NULL)
    {
      fprintf(stderr, "familial_sh: unsetenv: Too few arguments\n");
      return (EXIT_FAILURE);
    }
  my_rm_eq(&shenv->env, cmd[1]);
  return (EXIT_SUCCESS);
}

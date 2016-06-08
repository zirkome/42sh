/*
** _builtin_pwd.c for 42sh in /home/fillon_g/projets/42sh-2017-fillon_g/lib/builtins
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.net>
**
** Started on  Tue May 14 16:56:04 2013 guillaume fillon
** Last update Thu May 16 15:21:26 2013 guillaume fillon
*/

#include "builtins.h"

int		_builtin_pwd(__attribute__((unused)) char **cmd,
			     __attribute__((unused)) t_shenv *shenv)
{
  printf("%s\n", my_getcwd());
  return (EXIT_SUCCESS);
}

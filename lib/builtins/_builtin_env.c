/*
** _env.c for 42sh in /home/kokaz/projets/42sh/srcs/builtins
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.eu>
**
** Started on  Tue Mar  19 01:20:33 2013 guillaume fillon
** Last update Thu May 16 16:47:01 2013 guillaume fillon
*/

#include "builtins.h"
#include "list.h"

int	_builtin_env(__attribute__((unused)) char **cmd,
		     t_shenv *shenv)
{
  my_show_list(shenv->env);
  return (EXIT_SUCCESS);
}

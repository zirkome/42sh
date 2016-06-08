/*
** _builtins_getenv.c for 42sh in /home/kokaz/projets/42sh/srcs/builtins
**
** Made by guillaume fillon
** Login   <kokaz@epitech.net>
**
** Started on  Sun Mar 24 21:28:03 2013 guillaume fillon
** Last update Wed May 22 19:10:30 2013 guillaume fillon
*/

#include "builtins.h"

char		*_builtin_getenv(char *name, t_shenv *shenv)
{
  t_list	*tmp;

  tmp = shenv->env;
  while (tmp != NULL)
    {
      if (name && strcmp(name, tmp->name) == 0)
	return (strdup(tmp->value));
      tmp = tmp->next;
    }
  return (NULL);
}

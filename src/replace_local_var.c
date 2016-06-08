/*
** replace_local_var.c for replace_local_var.c in /home/bridou_n/42sh/src
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Thu May 23 16:05:37 2013 nicolas bridoux
** Last update Sun May 26 22:02:56 2013 guillaume fillon
*/

#include "42s.h"

char		*get_local_var(char *name, t_shenv *shenv)
{
  t_list	*tmp;

  tmp = shenv->lvar;
  while (tmp)
    {
      if (name && !strcmp(name, tmp->name))
	return (strdup(tmp->value));
      tmp = tmp->next;
    }
  return (NULL);
}

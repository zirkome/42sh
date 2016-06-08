/*
** my_free_list.c for 42sh in /home/fillon_g/projets/42sh/srcs/list
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.net>
**
** Started on  Tue Mar 19 17:27:25 2013 guillaume fillon
** Last update Thu May 23 01:01:32 2013 guillaume fillon
*/

#include "list.h"

void		my_free_list(t_list **env)
{
  t_list	*tmp;
  t_list	*prev;
  int		i;

  i = 0;
  tmp = NULL;
  if (env)
    tmp = *env;
  while (tmp)
    {
      prev = tmp;
      if (tmp->value != NULL)
	xfree(2, &tmp->name, &tmp->value);
      tmp = tmp->next;
      xfree(1, &prev);
      ++i;
    }
}

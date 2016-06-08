/*
** my_rm_eq.c for 42sh in /home/fillon_g/projets/42sh/srcs/list
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.net>
**
** Started on  Tue Mar 19 17:25:30 2013 guillaume fillon
** Last update Wed May 22 21:04:39 2013 guillaume fillon
*/

#include "list.h"

void		my_rm_eq(t_list **list, char *name_delete)
{
  t_list	*tmp;
  t_list	*prev;

  tmp = *list;
  prev = NULL;
  while  (tmp != NULL && strcmp(tmp->name, name_delete))
    {
      prev = tmp;
      tmp = tmp->next;
    }
  if (tmp != NULL && !strcmp(tmp->name, name_delete))
    {
      if (prev)
	prev->next = tmp->next;
      else
	*list = tmp->next;
      xfree(3, &tmp->value, &tmp->name, &tmp);
    }
}

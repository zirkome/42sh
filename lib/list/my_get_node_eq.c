/*
** my_get_node_eq.c for 42sh in /home/fillon_g/projets/42sh-2017-fillon_g/lib/list
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.net>
**
** Started on  Thu May 16 14:50:04 2013 guillaume fillon
** Last update Thu May 16 14:51:38 2013 guillaume fillon
*/

#include "list.h"

t_list		*my_get_node_eq(t_list *list, char *name)
{
  t_list	*tmp;

  tmp = list;
  while (tmp != NULL)
    {
      if (!strcmp(name, tmp->name))
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}

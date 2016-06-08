/*
** my_list.c<2> for my_list.c in /home/bridou_n/42sh
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Tue Mar 19 11:34:05 2013 nicolas bridoux
** Last update Sun May 26 15:30:59 2013 guillaume fillon
*/

#include "list.h"

void		my_put_in_end(t_list **list, char *name, char *value)
{
  t_list	*elem;
  t_list	*tmp;

  tmp = NULL;
  if (list)
    tmp = *list;
  if (tmp == NULL)
    my_put_in_list(list, name, value);
  else
    {
      if ((elem = malloc(sizeof(*elem))) == NULL)
	{
	  fprintf(stderr, "Not enough memory\n");
	  return ;
	}
      while (tmp->next != NULL)
	tmp = tmp->next;
      elem->name = name;
      elem->value = value;
      elem->next = NULL;
      tmp->next = elem;
    }
}

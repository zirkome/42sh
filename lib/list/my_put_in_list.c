/*
** my_put_in_list.c for 42sh in /home/fillon_g/projets/42sh/srcs/list
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.net>
**
** Started on  Tue Mar 19 17:24:11 2013 guillaume fillon
** Last update Sun May 26 15:31:47 2013 guillaume fillon
*/

#include "list.h"

void		my_put_in_list(t_list **list, char *name, char *value)
{
  t_list	*elem;

  if ((elem = malloc(sizeof(*elem))) == NULL)
    {
      fprintf(stderr, "Not enough memory\n");
      return ;
    }
  elem->name = name;
  elem->value = value;
  elem->next = *list;
  *list = elem;
}

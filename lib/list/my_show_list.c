/*
** my_show_list.c for 42sh in /home/fillon_g/projets/42sh/srcs/list
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.net>
**
** Started on  Tue Mar 19 17:26:05 2013 guillaume fillon
** Last update Thu May 16 15:18:57 2013 guillaume fillon
*/

#include "list.h"

void		my_show_list(t_list *list)
{
  t_list	*tmp;

  tmp = list;
  while (tmp != NULL)
    {
      printf("%s=%s\n", tmp->name, (tmp->value == NULL) ? "" : tmp->value);
      tmp = tmp->next;
    }
}

void		my_show_alias(t_list *list)
{
  t_list	*tmp;

  tmp = list;
  while (tmp != NULL)
    {
      printf("%s='%s'\n", tmp->name, (tmp->value == NULL) ? "" : tmp->value);
      tmp = tmp->next;
    }
}

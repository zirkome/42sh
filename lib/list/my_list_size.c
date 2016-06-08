/*
** my_list_size.c for 42sh in /home/fillon_g/projets/42sh-2017-fillon_g/src
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.net>
**
** Started on  Sat May 11 15:01:31 2013 guillaume fillon
** Last update Sun May 26 22:13:02 2013 guillaume fillon
*/

#include "list.h"

int		my_list_size(t_list *list)
{
  int		n;
  t_list	*tmp;

  tmp = list;
  n = 0;
  while (tmp != NULL)
    {
      tmp = tmp->next;
      ++n;
    }
  return (n);
}

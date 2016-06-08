/*
** my_put_list_to_tab.c for my_put_list_to_tab in /home/linard_f//Myls
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Fri Nov 30 13:55:25 2012 fabien linardon
** Last update Wed May 22 21:04:55 2013 guillaume fillon
*/

#include "list.h"

char		**my_put_list_to_tab(t_list *list)
{
  char		**t;
  int		rk;
  t_list	*tmp;
  char		*cpy;

  rk = 0;
  tmp = list;
  if (!(t = malloc((1 + my_list_size(list)) * sizeof(*t))))
    {
      fprintf(stderr, "Can't perform malloc.\n");
      return (NULL);
    }
  t[my_list_size(list)] = NULL;
  while (tmp != NULL)
    {
      if (!(t[rk] = my_strcat(tmp->name, (cpy = my_strcat("=", tmp->value)))))
	return (NULL);
      tmp = tmp->next;
      xfree(1, &cpy);
      ++rk;
    }
  return (t);
}

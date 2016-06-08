/*
** xfree.c for 42sh in /home/fillon_g/projets/42sh-2017-fillon_g/src
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.net>
**
** Started on  Sat May 11 14:40:56 2013 guillaume fillon
** Last update Sat May 25 21:38:25 2013 guillaume fillon
*/

#include <stdarg.h>
#include "42s.h"

int		xfree(const int count, ...)
{
  int		i;
  void		**ptr;
  va_list	args;

  i = 0;
  va_start(args, count);
  while (i < count)
    {
      if ((ptr = va_arg(args, void **)) != NULL)
	if (*ptr != NULL && (unsigned long int)*ptr < 0x7fff00000000)
	  {
	    free(*ptr);
	    *ptr = NULL;
	  }
      ++i;
    }
  va_end(args);
  return (1);
}

int	my_free_tab(char **tab)
{
  int	i;

  i = -1;
  while (tab && tab[++i])
    xfree(1, &tab[i]);
  if (tab)
    xfree(1, &tab);
  return (TRUE);
}

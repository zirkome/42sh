/*
** my_strdup.c for 42sh in /home/fillon_g/projets/42sh-2017-fillon_g/src
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.net>
**
** Started on  Sat May 11 15:00:35 2013 guillaume fillon
** Last update Sun May 19 04:08:11 2013 guillaume fillon
*/

#include "42s.h"

char	*my_strdup(char *str)
{
  char	*cpy;

  if (!str)
    return (NULL);
  if (!(cpy = strdup(str)))
    {
      fprintf(stderr, "Not enough memory\n");
      return (NULL);
    }
  return (cpy);
}

/*
** magic_read.c for magic_read.c in /home/bridou_n/42sh/src
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Sat May 11 18:32:45 2013 nicolas bridoux
** Last update Sun May 26 19:09:44 2013 guillaume fillon
*/

#include "42s.h"

static char	*my_realloc(char *str)
{
  char		*ret;

  if (!(ret = malloc(sizeof(char) * ((int)strlen(str) + READ + 1))))
    {
      xfree(1, &str);
      return (NULL);
    }
  strcpy(ret, str);
  xfree(1, &str);
  return (ret);
}

char	*magic_read(const int fd)
{
  char	*ret;
  int	size_read;
  int	i;
  char	tmp[4001];

  i = -1;
  ret = NULL;
  if (!(ret = malloc(sizeof(char) * (READ + 1))))
    return (NULL);
  while ((size_read = read(fd, &ret[++i * READ], READ)) == READ)
    {
      ret[READ * i + size_read] = '\0';
      if ((i * READ + size_read) > 4000)
      	{
      	  while (read(fd, tmp, 4000) > 0);
      	  return (ret);
      	}
      if (!(ret = my_realloc(ret)))
	return (NULL);
    }
  if (i >= 0)
    ret[READ * i + size_read] = '\0';
  else
    return (NULL);
  return (ret);
}

/*
** read_fd.c for read_fd.c in /home/bridou_n/42sh/src
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Sat May 11 18:32:45 2013 nicolas bridoux
** Last update Sun May 26 14:07:22 2013 nicolas bridoux
*/

#include "42s.h"

char		*read_fd(const int fd)
{
  char		*ret;
  struct stat	p;

  if (fstat(fd, &p) == -1)
    {
      fprintf(stderr, "familial_sh : %d %s", fd, strerror(errno));
      return (NULL);
    }
  if (!(ret = malloc(sizeof(char) * (p.st_size + 1))))
    return (NULL);
  if (read(fd, ret, p.st_size * sizeof(char)) < p.st_size)
    {
      free(ret);
      return (NULL);
    }
  ret[p.st_size] = '\0';
  return (ret);
}

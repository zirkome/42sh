/*
** get_cmd.c for get_cmd.c in /home/bridou_n/42sh
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Tue Mar 19 12:09:54 2013 nicolas bridoux
** Last update Sun May 19 04:06:53 2013 guillaume fillon
*/

#include "42s.h"

char	*my_getcwd(void)
{
  char	buf[MAX_PATH_SIZE];

  if (getcwd(buf, MAX_PATH_SIZE) == NULL)
    {
      fprintf(stderr, "%s\n", strerror(errno));
      return (NULL);
    }
  return (my_strdup(buf));
}

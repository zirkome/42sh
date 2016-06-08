/*
** error.c for error in /home/linard_f/42sh/exec_cmd
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Sat Mar 23 13:25:22 2013 fabien linardon
** Last update Thu May 23 15:02:12 2013 fabien linardon
*/

#include "42s.h"

int	my_error(char *str)
{
  if (str && strlen(str))
    {
      write(2, str, strlen(str));
      write(2, ": ", 2);
    }
  fprintf(stderr, "%s\n", strerror(errno));
  return (EXIT_FAILURE);
}

/*
** aff_histo.c for aff_histo in /home/linard_f/42sh/42sh-2017-fillon_g
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Mon May 20 11:56:13 2013 fabien linardon
** Last update Sun May 26 14:06:01 2013 fabien linardon
*/

#include "42s.h"

void	my_aff_histo(char *str, t_line *line, char *old)
{
  int	rk;

  while (line->rk)
    my_left(0, old, line);
  while (str[line->rk])
    my_aff_char(str[line->rk], line);
  rk = line->rk;
  while (old && line->rk < (int)strlen(old))
    my_aff_char(' ', line);
  while (line->rk != rk)
    my_left(0, old, line);
}

void	my_aff_char(char c, t_line *line)
{
  write(1, &c, 1);
  ++line->rk;
  if (++line->x == line->win_x)
    {
      line->x = 0;
      ++line->y;
      write(line->fd, "\n", 1);
    }
}

/*
** arrow_management.c for arrow_management in /home/linard_f/42sh/cmd_edition
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Sun Apr 14 10:24:19 2013 fabien linardon
** Last update Sun May 26 11:56:20 2013 fabien linardon
*/

#include "42s.h"

char	*my_left(int buf, char *str, t_line *line)
{
  buf = buf;
  if (line->rk <= 0)
    return (str);
  if (--line->x < line->prompt && !line->y && line->rk == 0)
    {
      line->x = line->prompt;
      return (str);
    }
  --line->rk;
  if (line->x < 0 && line->y > 0)
    {
      --line->y;
      go_up();
      while (++line->x != line->win_x)
	go_right();
      --line->x;
      return (str);
    }
  go_left();
  return (str);
}

char	*my_right(int buf, char *str, t_line *line)
{
  buf = buf;
  if (str == NULL || !str[line->rk])
    return (str);
  if (str[line->rk] && ++line->x == line->win_x)
    {
      write(line->fd, "\n", 1);
      ++line->rk;
      line->x = 0;
      ++line->y;
      return (str);
    }
  if (str[line->rk])
    {
      go_right();
      ++line->rk;
    }
  return (str);
}

char	*go_to_begin(__attribute__((unused)) int buf, char *str, t_line *line)
{
  while (line->rk)
    my_left(0, str, line);
  return (str);
}

char	*end_of_line(__attribute__((unused)) int buf, char *str, t_line *line)
{
  while (str && str[line->rk])
    my_right(0, str, line);
  return (str);
}

/*
** delete.c for delete in /home/linard_f/42sh/cmd_edition
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Mon Apr 15 14:38:44 2013 fabien linardon
** Last update Sun May 26 11:58:13 2013 fabien linardon
*/

#include "42s.h"

char	*my_delete(int buf, char *str, t_line *line)
{
  if (str == NULL || !str[line->rk])
    return (str);
  if (line->rk == 0 && !str[1])
    {
      line->x = 0;
      line->rk = 0;
      write(line->fd, " ", 1);
      go_left();
      xfree(1, &str);
      return (NULL);
    }
  if (!str[line->rk + 1])
    {
      str[line->rk] = 0;
      write(line->fd, " ", 1);
      go_left();
      return (str);
    }
  return (my_delete_and_recup(buf, str, line));
}

char	*my_back_space(int buf, char *str, t_line *line)
{
  char	*cpy;

  if (!line->rk)
    return (str);
  if (!str[line->rk])
    {
      str[line->rk - 1] = 0;
      my_left(buf, str, line);
      write(line->fd, " ", 1);
      go_left();
      if (line->x == line->win_x - 1)
	go_right();
      return (str);
    }
  my_left(buf, str, line);
  if ((cpy = strdup(&str[line->rk + 1])) == NULL)
    return (NULL);
  write(line->fd, &str[line->rk + 1], strlen(&str[line->rk]));
  str[line->rk] = 0;
  if ((cpy = my_strcat(str, cpy)) == NULL)
    return (NULL);
  recup_position(cpy, line, str, 0);
  return (cpy);
}

void	recup_position(char *cpy, t_line *line, char *str, int rk)
{
  rk = line->rk;
  write(line->fd, " ", 1);
  while (cpy[++line->rk])
    if (++line->x == line->win_x)
      {
	line->x = 0;
	++line->y;
      }
  if (++line->x == line->win_x)
    {
      line->x = 0;
      ++line->y;
    }
  if (++line->x == line->win_x)
    {
      line->x = 0;
      ++line->y;
    }
  ++line->rk;
  if (!line->x)
    write(line->fd, "\n", 1);
  while (str && rk != line->rk)
    my_left(0, str, line);
  xfree(1, &str);
}

char	*my_delete_and_recup(int buf, char *str, t_line *line)
{
  char	*cpy;
  char	*tmp;

  cpy = NULL;
  buf = buf;
  if ((cpy = strdup(&str[line->rk + 1])) == NULL)
    return (NULL);
  tputs(tgetstr("vi", NULL), 1, &my_putint);
  write(line->fd, cpy, strlen(cpy));
  write(line->fd, " ", 1);
  tmp = cpy;
  str[line->rk] = 0;
  if ((cpy = my_strcat(str, cpy)) == NULL)
    return (NULL);
  xfree(1, &tmp);
  my_recup(cpy, line, 0, str);
  return (cpy);
}

void	my_recup(char *cpy, t_line *line, int rk, char *str)
{
  rk = line->rk;
  while (cpy[++line->rk])
    if (++line->x == line->win_x)
      {
	line->x = 0;
	++line->y;
      }
  if (++line->x == line->win_x)
    {
      line->x = 0;
      ++line->y;
    }
  if (++line->x == line->win_x)
    {
      line->x = 0;
      ++line->y;
    }
  ++line->rk;
  if (!line->x)
    write(line->fd, "\n", 1);
  while (str && rk != line->rk)
    my_left(0, str, line);
  tputs(tgetstr("ve", NULL), 1, &my_putint);
  xfree(1, &str);
}

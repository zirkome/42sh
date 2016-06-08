/*
** cut_paste.c for cut_paste in /home/linard_f/42sh/42sh-2017-fillon_g
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Sun May 26 13:49:28 2013 fabien linardon
** Last update Sun May 26 15:29:27 2013 fabien linardon
*/

#include "42s.h"

char	*my_cut(__attribute__((unused)) int buf, char *str, t_line *line)
{
  int	rk;

  if (str && str[line->rk])
    {
      xfree(1, &line->cpy);
      line->cpy = my_strdup(&str[line->rk]);
      rk = line->rk;
      while (str[line->rk])
	my_aff_char(' ', line);
      while (line->rk != rk)
	my_left(0, str, line);
      str[line->rk] = 0;
    }
  return (str);
}

static char	*paste_into_string(char *str, t_line *line, char *tmp)
{
  int		rk;
  char		*cpy;

  cpy = my_strdup(&str[line->rk]);
  str[line->rk] = 0;
  str = my_strcat(str, line->cpy);
  xfree(1, &tmp);
  tmp = str;
  str = my_strcat(str, cpy);
  rk = line->rk;
  while (str[line->rk])
    my_aff_char(str[line->rk], line);
  while (line->rk != rk)
    my_left(0, str, line);
  xfree(1, &tmp);
  return (str);
}

char	*my_paste(__attribute__((unused)) int buf, char *str, t_line *line)
{
  char	*tmp;

  if (!line->cpy || (int)strlen(line->cpy) == 0)
    return (str);
  tmp = str;
  if (!str[line->rk])
    {
      str = my_strcat(str, line->cpy);
      while (str[line->rk])
	my_aff_char(str[line->rk], line);
      xfree(1, &tmp);
    }
  else
    str = paste_into_string(str, line, tmp);
  return (str);
}

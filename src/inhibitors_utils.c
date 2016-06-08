/*
** inhibitors_utils.c for inhibitors_utils.c in /home/bridou_n/42sh/src
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Sun May 19 20:43:21 2013 nicolas bridoux
** Last update Sat May 25 21:12:03 2013 guillaume fillon
*/

#include "42s.h"

void	ignore_it(char *str, int *i)
{
  char	tmp;

  if (str[*i] == '"' || str[*i] == '\'')
    {
      tmp = str[*i];
      while (str[++(*i)] && str[*i] != tmp);
    }
}

char	*concat_end(char *end, char *str)
{
  char	*ret;

  ret = my_strcat(str, end);
  xfree(2, &end, &str);
  return (ret);
}

void	check_last_and_first_char(char *str)
{
  int	i;

  if (str)
    i = strlen(str);
  if (i && str && (str[i - 1] == ' ' || str[i - 1] == '\t'))
    str[i - 1] = '\0';
  if (str && (str[0] == ' ' || str[0] == '\t'))
    shift(str, 0);
}

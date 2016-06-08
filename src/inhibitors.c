/*
** inhibitors.c for inhibitors.c in /home/bridou_n/42sh/src
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Sun May 19 15:37:24 2013 nicolas bridoux
** Last update Sun May 26 17:02:21 2013 nicolas bridoux
*/

#include "42s.h"

char	*epur_string(char *str, int i, int k, char *ret)
{
  char	*end;

  if (check_inhibitors(str) || !str || !ret || !strlen(str))
    {
      xfree(1, &ret);
      return (NULL);
    }
  while (str[++i])
    {
      while (str[i] && str[i] != '"' && str[i] != '\'')
	++i;
      if (!str[i])
	{
	  ret = concat_end(epur_str(&str[k]), ret);
	  check_last_and_first_char(ret);
	  return (ret);
	}
      end = get_end(str, &i, &k, &ret);
      ret = concat_end(end, ret);
    }
  check_last_and_first_char(ret);
  return (ret);
}

char	*get_end(char *str, int *i, int *k, char **ret)
{
  char	*end;
  char	tmp;

  tmp = str[*i];
  str[*i] = '\0';
  *ret = concat_end(epur_str(&str[*k]), *ret);
  str[*i] = tmp;
  *k = *i;
  while (str[++(*i)] && str[*i] != tmp);
  str[*i] = '\0';
  end = concat_end((tmp == '"') ? (my_strdup("\""))
		   : (my_strdup("'")), my_strdup(&str[*k]));
  str[*i] = tmp;
  *k = *i + 1;
  return (end);
}

int	check_inhibitors(char *str)
{
  int	i;
  char	tmp;

  i = -1;
  while (str && str[++i])
    {
      while (str[i] && str[i] != '"' && str[i] != '\'')
	++i;
      if (!(tmp = str[i]))
	return (EXIT_SUCCESS);
      while (str[++i] && str[i] != tmp);
      if (!str[i])
	return (fprintf(stderr, "Unmatched %c.\n", tmp));
    }
  return (EXIT_SUCCESS);
}

void	delete_inhibitors(char **tab)
{
  int	i;
  int	k;
  char	tmp;

  i = -1;
  while (tab && tab[++i])
    {
      k = -1;
      while (tab[i][++k])
	{
	  if (tab[i][k] == '"' || tab[i][k] == '\'')
	    {
	      tmp = tab[i][k];
	      shift(tab[i], k);
	      while (tab[i][k] && tab[i][k] != tmp)
		++k;
	      shift(tab[i], k);
	      --k;
	    }
	  if (tab[i][k + 1] && tab[i][k] == '\\' && tab[i][k + 1] != '\''
	      && tab[i][k + 1] != '"')
	    shift(tab[i], k);
	}
    }
}

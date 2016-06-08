/*
** env_var.c for env_var.c in /home/bridou_n/42sh/src
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Sun May 19 21:44:39 2013 nicolas bridoux
** Last update Sun May 26 21:57:28 2013 nicolas bridoux
*/

#include "42s.h"
#include "builtins.h"

char	*complete_str(char *str, int k, int i, char *value)
{
  char	*begin;
  char	*end;
  char	*ret;
  char	tmp;

  tmp = str[--k];
  str[k] = '\0';
  if (!(begin = my_strdup(&str[0])))
    return (NULL);
  str[k] = tmp;
  if (!(end = my_strdup(&str[i])))
    return (NULL);
  if (!(ret = malloc(sizeof(char) * (strlen(begin)
    + strlen(value) + strlen(end) + 1))))
  return (NULL);
  strcpy(ret, begin);
  strcat(ret, value);
  strcat(ret, end);
  xfree(3, &begin, &end, &value);
  return (ret);
}

char	*replace_env_var(char *str, int *i, t_shenv *shenv, int k)
{
  char	*name;
  char	*value;
  char	tmp;

  while (str[++(*i)] && is_alphanumeric(str[*i]));
  if (*i != k)
    {
      tmp = str[*i];
      if ((str[*i] = '\0') == 0 && !(name = my_strdup(&str[k])))
	return (NULL);
      str[*i] = tmp;
      if (!(value = _builtin_getenv(name, shenv))
	&& !(value = get_local_var(name, shenv)))
	{
	  fprintf(stderr, "%s : Undefined variable.\n", name);
	  xfree(1, &name);
	  return (NULL);
	}
      if (!(str = complete_str(str, k, *i, value)))
	return (NULL);
      *i = -1;
    }
  else
    --(*i);
  return (str);
}

char	*replace_var(char *str, t_shenv *shenv, int history, int replace)
{
  int	i;

  i = -1;
  while (str[++i] && replace < 15)
    {
      if (str[i] == '\'')
	while (str[++i] && str[i] != '\'');
      if (str[i] == '$')
	if (++replace && !(str = replace_env_var(str, &i, shenv, i + 1)))
	return (NULL);
      if (i >= 0 && str[i] == '!' && ++history)
	if ((str[i + 1] >= '0' && str[i + 1] <= '9') || str[i + 1] == '-')
	if (!(str = get_good_line(str, i, my_getnbr(&str[i + 1]))))
	return (NULL);
    }
  if (history)
    printf("%s\n", str);
  return (str);
}

char	*get_good_line(char *str, int i, int nb)
{
  char	**tab;
  char	*begin;
  char	*end;
  char	*value;

  if (!(tab = get_history_line()))
    return (NULL);
  if (!nb || nb > len_tab(tab) || (-1 *nb) > len_tab(tab))
    {
      fprintf(stderr, "%d : Event not found.\n", nb);
      my_free_tab(tab);
      return (NULL);
    }
  str[i] = '\0';
  if (!(begin = my_strdup(&str[0])))
    return (NULL);
  while (str[++i] && ((str[i] <= '9' && str[i] >= '0') || str[i] == '-'));
  if (!(end = my_strdup(&str[i])))
    return (NULL);
  value = (nb < 0) ? (my_strdup(tab[len_tab(tab)
  + nb])) : (my_strdup(tab[nb - 1]));
  my_free_tab(tab);
  return (complete_history_str(begin, value, end));
}

char	*complete_history_str(char *begin, char *value, char *end)
{
  char	*ret;

  if (!(ret = malloc(sizeof(char) * (strlen(begin)
    + strlen(value) + strlen(end) + 1))))
  return (NULL);
  strcpy(ret, begin);
  strcat(ret, value);
  strcat(ret, end);
  xfree(3, &begin, &end, &value);
  return (ret);
}

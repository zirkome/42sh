/*
** my_parse_cmd.c for parse_cmd.c in /home/bridou_n/42sh
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Tue Mar 19 14:14:27 2013 nicolas bridoux
** Last update Sun May 26 19:01:19 2013 guillaume fillon
*/

#include "42s.h"

int	parse_cmd(char *cmd, t_shenv *shenv, int n)
{
  char	**tab;
  int	ret;

  tab = NULL;
  if (cmd && !strcmp(cmd, ""))
    return (EXIT_FAILURE);
  if (cmd && !(tab = my_str_to_argtab(cmd, -1, -1, 0)))
    return (EXIT_FAILURE);
  if (!(tab = make_globing(tab)))
    return (EXIT_FAILURE);
  tab = replace_alias(tab, shenv);
  ret = dispatch_cmd(tab, shenv, n);
  my_free_tab(tab);
  return (ret);
}

char	**my_str_to_argtab(char *str, int i, int k, int j)
{
  char	**tab;
  char	tmp;
  int	max;

  max = nb_cmd(str, ' ');
  if (!max || !str || !(tab = malloc(sizeof(char *) * max)))
    return (NULL);
  while (str[++i])
    {
      if (str[i] == '"' || str[i] == '\'')
	{
	  tmp = str[i];
	  while (str[++i] && str[i] != tmp);
	}
      if (i && str[i] == ' ' && str[i - 1] != '\\')
	{
	  str[i] = '\0';
	  tab[++k] = my_strdup(&str[j]);
	  j = i + 1;
	}
    }
  if ((int)strlen(&str[j]))
    tab[++k] = my_strdup(&str[j]);
  tab[++k] = NULL;
  return (tab);
}

int	nb_cmd(char *str, char delim)
{
  int	i;
  int	count;

  count = 1;
  i = -1;
  if (!str)
    return (0);
  while (str && str[++i])
    if (str[i] == delim)
      ++count;
  return (++count);
}

int	is_redirection(char *str)
{
  if (str && (!strcmp(str, ">") || !strcmp(str, ">>")
	      || !strcmp(str, "<") || !strcmp(str, "<<")
	      || !strcmp(str, ">&")))
    return (TRUE);
  return (FALSE);
}

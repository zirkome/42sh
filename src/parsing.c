/*
** parsing.c for parsing.c in /home/bridou_n/42sh
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Tue Mar 19 13:57:19 2013 nicolas bridoux
** Last update Sun May 26 14:18:56 2013 nicolas bridoux
*/

#include "42s.h"

static int	count_nb_cmd(char *str)
{
  int		i;
  int		count;

  count = 0;
  i = 0;
  while (str && str[i] != '\0')
    {
      if (str[i] == ';' || (str[i] == '|' && str[i + 1] == '|')
	  || (str[i] == '&' && str[i + 1] == '&'))
	++count;
      ++i;
    }
  return (++count);
}

static void	fill_tab_cmd(char **tab, char *str, int i, int j)
{
  int		k;

  k = 0;
  while (str && str[++i] != '\0')
    {
      ignore_it(str, &i);
      if (i && (str[i] == ';' || (str[i] == '&' && str[i + 1] == '&')
		|| (str[i] == '|' && str[i + 1] == '|')))
	{
	  str[i - 1] = '\0';
	  tab[k++] = my_strdup(&str[j]);
	  (str[i] == ';') ? (j = i + 2) : (j = i + 3);
	  if (str[i] == ';')
	    tab[k++] = my_strdup(";");
	  if (str[i] == '&')
	    tab[k++] = my_strdup("&&");
	  if (str[i] == '|')
	    tab[k++] = my_strdup("||");
	}
    }
  tab[k] = my_strdup(&str[j]);
  tab[++k] = NULL;
}

char	**make_tab_cmd(char *str)
{
  int	nb_cmd;
  char	**tab;

  nb_cmd = count_nb_cmd(str);
  if ((tab = malloc(sizeof(char *) * (nb_cmd * 2 + 1))) == NULL)
    {
      fprintf(stderr, "Not enough memory\n");
      return (NULL);
    }
  fill_tab_cmd(tab, str, -1, 0);
  return (tab);
}

static int	init_parsing(char **str, t_shenv *shenv,
			     int *ret, char ***cmd)
{
  *ret = 0;
  if (!(*str = replace_var(*str, shenv, 0, 0)))
    return (EXIT_SUCCESS);
  add_history_line(*str, shenv);
  if (!(*cmd = make_tab_cmd(*str)))
    return (EXIT_SUCCESS);
  if (strncmp(*cmd[0], ";", 1) && strncmp(*cmd[0], "&&", 2)
      && strncmp(*cmd[0], "||", 2))
    *ret = parse_cmd(*cmd[0], shenv, 0);
  return (EXIT_FAILURE);
}

int	parsing(char *str, t_shenv *shenv, int n)
{
  char	**cmd;
  int	ret;
  int	i;

  i = -1;
  if (!(init_parsing(&str, shenv, &ret, &cmd)))
    return (EXIT_SUCCESS);
  while (cmd && cmd[++i])
    {
      if (!strncmp(cmd[i], ";", 1) && cmd[i + 1]
	  && strncmp(cmd[i + 1], ";", 1))
	ret = parse_cmd(cmd[++i], shenv, n);
      if (!strncmp(cmd[i], "&&", 2) && cmd[i + 1]
	  && strncmp(cmd[i + 1], "&&", 2))
	(!ret) ? (ret = parse_cmd(cmd[++i], shenv, n)) : ++i;
      if (!strncmp(cmd[i], "||", 2) && cmd[i + 1]
	  && strncmp(cmd[i + 1], "||", 2))
	(ret == EXIT_FAILURE) ? (ret = parse_cmd(cmd[++i], shenv, n)) : ++i;
      if (ret == -1)
	return (EXIT_FAILURE);
      n = 0;
    }
  my_free_tab(cmd);
  return (EXIT_SUCCESS);
}

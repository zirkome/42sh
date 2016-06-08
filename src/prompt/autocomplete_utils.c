/*
** autocomplete_utils.c for autocomplete_utils.c in /home/bridou_n/42sh/src
** 
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri May 24 16:32:26 2013 nicolas bridoux
** Last update Sun May 26 21:12:55 2013 nicolas bridoux
*/

#include "42s.h"

void	free_cmd_tab(char **tab)
{
  int	i;

  i = -1;
  while (tab && tab[++i])
    xfree(1, &tab[i]);
}

int	find_max(char **tab)
{
  int	i;
  int	max;

  i = -1;
  max = 0;
  if (tab && tab[0])
    max = strlen(tab[0]);
  while (tab && tab[++i])
    if ((int)strlen(tab[i]) > max)
      max = strlen(tab[i]);
  return (max);
}

int	fill_tab_complete(char **tab, char *str, int rk)
{
  int	tmp;
  int	end;

  tmp = str[rk];
  str[rk] = '\0';
  tab[0] = my_strdup(&str[0]);
  str[rk] = tmp;
  tmp = rk;
  while (str[tmp] && str[++tmp] && str[tmp] != ' ' && str[tmp] != '>'
	 && str[tmp] != '<' && str[tmp] != '|' && str[tmp] != '&');
  tab[2] = my_strdup(&str[tmp]);
  if (!(tab[1] = malloc(sizeof(char) * (strlen(&str[rk]) + 2))))
    return (EXIT_FAILURE);
  end = str[tmp];
  str[tmp] = '\0';
  strcpy(tab[1], &str[rk]);
  strcat(tab[1], "*");
  str[tmp] = end;
  tab[3] = NULL;
  return (EXIT_SUCCESS);
}

int	cut_completion(char **tab, char *str, int rk)
{
  char	tmp;

  if (!str)
    return (EXIT_FAILURE);
  while (rk && --rk >= 0)
    {
      if (str[rk] == ' ' || str[rk] == '>' || str[rk] == '<'
	  || str[rk] == '|' || str[rk] == '&')
	return (fill_tab_complete(tab, str, rk + 1));
    }
  if (str && ((str[0] == '.' && str[1] == '/') || str[0] == '/'))
    return (fill_tab_complete(tab, str, 0));
  tab[0] = my_strdup("");
  while (str[++rk] && str[rk] != ' ' && str[rk] != '>' && str[rk] != '<'
	 && str[rk] != '|' && str[rk] != '&');
  tmp = str[rk];
  tab[2] = my_strdup(&str[rk]);
  str[rk] = '\0';
  tab[1] = my_strdup(&str[0]);
  str[rk] = tmp;
  tab[3] = NULL;
  return (EXIT_SUCCESS);
}

int	first_n_char_are_the_same(char **tab, int n)
{
  int	i;

  i = -1;
  while (tab[++i] && tab[i + 1])
    if ((int)strlen(tab[i]) < n || strncmp(tab[i], tab[i + 1], n))
      return (FALSE);
  return ((!i) ? (FALSE) : (TRUE));
}

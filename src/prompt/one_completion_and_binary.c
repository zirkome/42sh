/*
** one_completion_and_binary.c for one_completion_and_binary.c in /home/bridou_n/42sh/src
** 
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Fri May 24 22:31:04 2013 nicolas bridoux
** Last update Sun May 26 11:21:41 2013 nicolas bridoux
*/

#include "42s.h"

char	*one_completion(t_line *line, char *tab, char *str, char **tab_cmd)
{
  char	*ret;
  int	len;
  int	rk;

  len = strlen(tab_cmd[0]) + strlen(tab_cmd[2]) + strlen(tab) + 2;
  if (!(ret = malloc(sizeof(char) * len)))
    return (str);
  strcpy(ret, tab_cmd[0]);
  strcat(ret, tab);
  strcat(ret, " ");
  strcat(ret, tab_cmd[2]);
  tab_cmd[1][strlen(tab_cmd[1]) - 1] = '\0';
  rk = line->rk + (strlen(tab) - strlen(tab_cmd[1])) + 1;
  my_aff_histo(ret, line, str);
  while (line->rk > rk)
    my_left(0, ret, line);
  xfree(1, &str);
  str = ret;
  free_cmd_tab(tab_cmd);
  return (str);
}

int	only_one_completion(char **tab, char *str)
{
  int	i;

  i = -1;
  while (tab[++i])
    if (!strcmp(tab[i], str))
      {
	if (i)
	  {
	    xfree(1, &tab[0]);
	    tab[0] = my_strdup(tab[i]);
	  }
	return (TRUE);
      }
  if (i == 1 && !strncmp(tab[0], str, strlen(str)))
    return (TRUE);
  return (FALSE);
}

char	*complete_binary(char *str, t_line *line,
			 t_shenv *shenv, char *tab[4])
{
  char	**comp_tab;
  char	*ret;

  comp_tab = fill_tab_binary(tab[1], creat_binary_path(shenv), -1, -1);
  if (!comp_tab)
    {
      free_cmd_tab(tab);
      return (str);
    }
  if (only_one_completion(comp_tab, tab[1]))
    ret = one_completion(line, comp_tab[0], str, tab);
  else
    {
      dprintf(line->fd, "%s", GREEN_BOLD);
      ret = display_matches(line, comp_tab, str, tab);
    }
  my_free_tab(comp_tab);
  return (ret);
}

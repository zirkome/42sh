/*
** replace_alias.c for 42sh in /home/fillon_g/projets/42sh-2017-fillon_g/src
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.net>
**
** Started on  Sun May 19 02:36:08 2013 guillaume fillon
** Last update Sun May 26 15:04:10 2013 nicolas bridoux
*/

#include "42s.h"

int	is_and_or(char *str)
{
  if (str && (!strcmp(str, "&&") || !strcmp(str, "||")))
    return (TRUE);
  return (FALSE);
}

static int	tabsize(char **tab)
{
  int		i;

  i = 0;
  if (tab)
    {
      while (tab[i])
	++i;
      return (i);
    }
  return (FALSE);
}

static char	**merge_tab(char **t1, char **t2, int pos)
{
  int		i;
  int		j;
  char		**final;

  final = malloc((tabsize(t1) + tabsize(t2)) * sizeof(char *));
  if (final == NULL)
    return (t1);
  i = 0;
  while (t1[i] && i < pos)
    {
      final[i] = t1[i];
      ++i;
    }
  j = 0;
  while (t2[j])
    final[i++] = t2[j++];
  j = i - j + 1;
  while (t1[j])
    final[i++] = t1[j++];
  final[i] = NULL;
  return (final);
}

static char	**get_match(char **cmd, t_shenv *shenv, int i)
{
  char		**tab;
  char		*name;
  t_list	*tmp;

  tab = NULL;
  tmp = shenv->alias;
  name = NULL;
  while (tmp != NULL)
    {
      if (tmp->name != NULL && cmd[i] && !strcmp(cmd[i], tmp->name))
	{
	  name = tmp->name;
	  tab = my_str_to_argtab(epur_str(strdup(tmp->value)), -1, -1, 0);
	  tmp->name = NULL;
	  cmd = merge_tab(cmd, tab, i);
	  cmd = get_match(cmd, shenv, i);
	  tmp->name = name;
	  return (cmd);
	}
      tmp = tmp->next;
    }
  return (cmd);
}

char		**replace_alias(char **cmd, t_shenv *shenv)
{
  int		i;

  i = 0;
  while (cmd[i])
    {
      if (i == 0 || (i > 0 && (is_and_or(cmd[i - 1])
			       || !strcmp(cmd[i - 1], ";"))))
	{
	  if (cmd[i][0] != '\\')
	    cmd = get_match(cmd, shenv, i);
	  else
	    shift(cmd[i], 0);
	}
      ++i;
    }
  return (cmd);
}

/*
** globing.c for globing.c in /home/bridou_n/42sh/srcs
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Wed Apr 17 13:56:32 2013 nicolas bridoux
** Last update Sun May 26 14:48:26 2013 nicolas bridoux
*/

#include "42s.h"

static int	my_strcmp_tab(char **tab, char **tab2)
{
  int		i;

  i = -1;
  while (tab[++i] && tab2[i])
    if (strcmp(tab[i], tab2[i]))
      return (TRUE);
  if ((!tab[i] && tab2[i]) || (!tab2[i] && tab[i]))
    return (TRUE);
  return (FALSE);
}

static char	**fill_tab_glob(char **tab, char **glob_tab, int i, int k)
{
  int		j;
  glob_t	elem;

  while (tab[++i])
    {
      j = -1;
      if (glob(tab[i], GLOB_TILDE | GLOB_BRACE | GLOB_NOCHECK, NULL, &elem))
	return (tab);
      while (elem. gl_pathv[++j])
	if (!(glob_tab[++k] = my_strdup(elem.gl_pathv[j])))
	  return (NULL);
      globfree(&elem);
    }
  glob_tab[++k] = NULL;
  if (!my_strcmp_tab(tab, glob_tab))
    {
      fprintf(stderr, "%s: No match.\n", tab[0]);
      my_free_tab(glob_tab);
      xfree(1, &tab);
      return (NULL);
    }
  xfree(1, &tab);
  return (glob_tab);
}

static char	**globing(char **tab)
{
  glob_t	elem;
  int		i;
  int		count;
  char		**glob_tab;

  count = 1;
  i = -1;
  elem.gl_offs = 1;
  while (tab[++i])
    {
      if (glob(tab[i], GLOB_TILDE | GLOB_BRACE | GLOB_NOCHECK, NULL, &elem))
	return (tab);
      count += elem.gl_pathc;
      globfree(&elem);
    }
  if (!(glob_tab = malloc(sizeof(char *) * (count + 1))))
    {
      my_error("");
      return (NULL);
    }
  return (fill_tab_glob(tab, glob_tab, -1, -1));
}

static int	need_globing(char c)
{
  if (c == '?' || c == '*' || c == '[' || c == '{'
      || c == '~' || c == '}' || c == ']')
    return (TRUE);
  return (FALSE);
}

char	**make_globing(char **tab)
{
  int	i;
  int	k;

  i = -1;
  while (tab[++i])
    {
      k = -1;
      while (tab[i][++k])
	{
	  if ((tab[i][k] == '\\' || tab[i][k] == '$') && tab[i][k + 1])
	    k += 2;
	  if (tab[i][0] != '"' && tab[i][0] != '\''
	      && need_globing(tab[i][k]))
	    return (globing(tab));
	  if (!tab[i][k])
	    --k;
	}
    }
  return (tab);
}

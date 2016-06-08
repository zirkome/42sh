/*
** copy_path.c for 42sh in /home/degreg_e/projets/42sh/srcs
**
** Made by enzo degregorio
** Login   <degreg_e@epitech.net>
**
** Started on  Thu Mar 21 01:30:03 2013 enzo degregorio
** Last update Wed May 22 20:55:46 2013 guillaume fillon
*/

#include "42s.h"

static int	nb_path(char *str)
{
  int		i;
  int		count;

  count = 1;
  i = -1;
  while (str[++i])
    if (str[i] == ':')
      ++count;
  return (++count);
}

char	**my_str_to_pathtab(char *str, int i, int j, int k)
{
  char	**tab;
  char	*tmp;

  if (!(tab = malloc(sizeof(char *) * nb_path(str))))
    {
      fprintf(stderr, "Not enough memory\n");
      return (NULL);
    }
  while (str[++i])
    if (str[i] == ':')
      {
	str[i] = '\0';
	tmp = my_strdup(&str[k]);
	tab[++j] = my_strcat(tmp, "/");
	xfree(1, &tmp);
	k = i + 1;
      }
  tmp = my_strdup(&str[k]);
  tab[++j] = my_strcat(tmp, "/");
  tab[++j] = NULL;
  xfree(2, &tmp, &str);
  return (tab);
}

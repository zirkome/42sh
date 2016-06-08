/*
** strcat.c for strcat in /home/linard_f/42sh/exec_cmd
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Sun Mar 24 11:30:11 2013 fabien linardon
** Last update Sun May 26 14:50:54 2013 nicolas bridoux
*/

#include "42s.h"

char	*my_strcat(char *a, char *b)
{
  char	*new;
  int	rk;
  int	i;
  int	len;

  len = 0;
  if (a)
    len += strlen(a);
  if (b)
    len += strlen(b);
  if ((new = malloc((len + 1) * sizeof(char))) == NULL)
    {
      fprintf(stderr, "Can't perform malloc.\n");
      return (NULL);
    }
  rk = -1;
  i = -1;
  while (a && a[++i])
    new[++rk] = a[i];
  i = -1;
  while (b && b[++i])
    new[++rk] = b[i];
  new[++rk] = 0;
  return (new);
}

char	*my_strcat2(char *a, int b)
{
  char	*new;
  int	rk;
  int	i;
  int	len;

  len = 0;
  if (a)
    len += strlen(a);
  if (b)
    len += sizeof(b);
  if ((new = malloc((len + 1) * sizeof(char))) == NULL)
    {
      fprintf(stderr, "Can't perform malloc.\n");
      return (NULL);
    }
  rk = -1;
  i = -1;
  while (a && a[++i])
    new[++rk] = a[i];
  new[++rk] = b;
  new[++rk] = 0;
  return (new);
}

int	is_alphanumeric(char c)
{
  if ((c <= '9' && c >= '0') || (c >= 'a' && c <= 'z')
      || (c >= 'A' && c <= 'Z') || c == '_' || c == '?')
    return (TRUE);
  return (FALSE);
}

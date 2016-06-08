/*
** levenshtein.c for levenshtein.c in /home/bridou_n//minishell1/Bonus
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Tue Dec 11 13:41:44 2012 nicolas bridoux
** Last update Wed May 22 20:59:07 2013 guillaume fillon
*/

#include "42s.h"

static int	min(int a, int b, int c)
{
  int		min;

  min = a;
  if (b < min)
    min = b;
  if (c < min)
    min = c;
  return (min);
}

static int	init_tab(t_lev *p)
{
  if ((p->tab = malloc((sizeof(int)) * (p->len_1 + 1)
		       * (p->len_2 + 1))) == NULL)
    return (FALSE);
  p->len_1++;
  p->len_2++;
  p->i = 0;
  while (p->i < p->len_1)
    {
      p->tab[p->i] = p->i;
      p->i++;
    }
  p->i = 0;
  while (p->i < p->len_2)
    {
      p->tab[p->i * p->len_1] = p->i;
      p->i++;
    }
  p->i = 1;
  return (TRUE);
}

static void	complete_tab(t_lev *p, char *str1, char *str2)
{
  while (p->i < p->len_1)
    {
      p->j = 1;
      while (p->j < p->len_2)
	{
	  if (str1[p->i - 1] == str2[p->j - 1])
	    p->cost = 0;
	  else
	    p->cost = 1;
	  p->tab[p->j * p->len_1 + p->i] =
	    min(p->tab[(p->j - 1) * p->len_1 + p->i] + 1,
		p->tab[p->j * p->len_1 + p->i - 1] + 1,
		p->tab[(p->j - 1) * p->len_1 + p->i - 1] + p->cost);
	  p->j++;
	}
      p->i++;
    }
}

int	levenshtein_lenght(char *str1, char *str2)
{
  t_lev	p;
  int	distance;

  p.len_1 = strlen(str1);
  p.len_2 = strlen(str2);
  if (p.len_1 && p.len_2)
    {
      if (!init_tab(&p))
	return (FALSE);
      complete_tab(&p, str1, str2);
      distance = p.tab[p.len_1 * p.len_2 - 1];
      xfree(1, &p.tab);
      return (distance);
    }
  else
    return (FALSE);
}

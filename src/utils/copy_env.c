/*
** copy_env.c for copy_env.c in /home/bridou_n/42sh
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Tue Mar 19 11:43:38 2013 nicolas bridoux
** Last update Sun May 19 04:07:21 2013 guillaume fillon
*/

#include "42s.h"
#include "list.h"

t_list	*copy_env(t_list *list, char *env[])
{
  int	i;
  int	j;

  i = -1;
  while (env && env[++i])
    {
      j = -1;
      while (env[i][++j])
	if (env[i][j] == '=')
	  {
	    env[i][j] = '\0';
	    my_put_in_end(&list, my_strdup(env[i]), my_strdup(&env[i][j + 1]));
	    while (env[i][j + 1])
	      ++j;
	  }
    }
  return (list);
}

void	shift(char *str, int i)
{
  while (str[i])
    {
      str[i] = str[i + 1];
      ++i;
    }
}

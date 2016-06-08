/*
** search_binary.c for search_binary.c in /home/bridou_n/42sh/src
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Fri May 24 19:18:47 2013 nicolas bridoux
** Last update Sun May 26 12:11:20 2013 guillaume fillon
*/

#include "42s.h"

int	actual_path(char *str)
{
  int	i;

  if (strlen(str) && str[strlen(str) - 1] == '*')
    str[strlen(str) - 1] = '\0';
  i = strlen(str);
  while (--i >= 0)
    {
      if (str[i] == ' ')
	{
	  while (--i >= 0 && str[i] == ' ');
	  return ((str[i] == '|' || str[i] == '&' || !i) ? (FALSE) : (TRUE));
	}
      if (str[i] == '>' || str[i] == '<' || str[i] == '/')
	return (TRUE);
      if (str[i] == '|' || str[i] == '&')
	return (FALSE);
    }
  return (FALSE);
}

char	**creat_binary_path(t_shenv *shenv)
{
  char	*str;
  char	**ret;

  if (!(str = _builtin_getenv("PATH", shenv)))
    return (NULL);
  if (!(ret = my_str_to_pathtab(str, -1, -1, 0)))
    return (NULL);
  return (ret);
}

int		count_binary_match(char *str, char **path)
{
  int		i;
  int		count;
  struct dirent	*entry;
  DIR		*dirp;

  count = 0;
  if (str[strlen(str) - 1] == '*')
    str[strlen(str) - 1] = '\0';
  i = -1;
  while (path[++i])
    if ((dirp = opendir(path[i])))
      {
	while ((entry = readdir(dirp)))
	  {
	    if (strlen(entry->d_name) >= strlen(str))
	      if (!strncmp(entry->d_name, str, strlen(str)))
		++count;
	  }
	closedir(dirp);
      }
  return (count);
}

char		**fill_tab_binary(char *str, char **path, int i, int k)
{
  char		**ret;
  struct dirent *entry;
  DIR		*dirp;
  int		count;

  if (!path || !(count = count_binary_match(str, path)))
    return (NULL);
  if (!(ret = malloc(sizeof(char *) * (count + 1))))
    return (NULL);
  while (path[++i])
    if ((dirp = opendir(path[i])))
      {
	while ((entry = readdir(dirp)))
	  {
	    if (strlen(entry->d_name) >= strlen(str))
	      if (!strncmp(entry->d_name, str, strlen(str)))
		ret[++k] = my_strdup(entry->d_name);
	  }
	closedir(dirp);
      }
  my_free_tab(path);
  ret[++k] = NULL;
  return (ret);
}

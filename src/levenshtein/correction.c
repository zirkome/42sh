/*
** correction.c for correction.c in /home/bridou_n/42sh/src
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Mon May 13 12:24:29 2013 nicolas bridoux
** Last update Sun May 26 13:33:49 2013 nicolas bridoux
*/

#include "42s.h"

static char	*good_correct(char *cmd, char *path)
{
  char		*ret;

  printf(" %sYes%s, sir\n", GREEN_BOLD, INIT);
  if (!(ret = malloc(sizeof(char) * (strlen(cmd) + strlen(path) + 1))))
    {
      xfree(2, &path, &cmd);
      return (NULL);
    }
  strcpy(ret, path);
  strcat(ret, cmd);
  xfree(2, &path, &cmd);
  return (ret);
}

static char	*ask_correction(char *cmd, char *path,
				struct termios *t, int lev)
{
  char		buffer;

  if (!cmd || !path || lev > 5)
    return (NULL);
  dprintf(STDOUT_FILENO, "familial_sh : You mean %s%s%s, right ? (y | N) ",
	 WHITE_BOLD, cmd, INIT);
  if (raw_mode(t))
    return (NULL);
  if (read(STDIN_FILENO, &buffer, sizeof(char)) > 0)
    {
      if (raw_mode_off(t))
      	return (NULL);
      if (buffer == 'y')
      	return (good_correct(cmd, path));
      else
      	printf(" %sNo%s, thanks\n", RED_BOLD, INIT);
    }
  xfree(2, &cmd, &path);
  return (NULL);
}

char			*correct(char *av, char **path, int lev, int dist)
{
  struct termios	t;
  struct dirent		*entry;
  DIR			*dirp;
  int			i;
  char			*bin;
  char			*bin_path;

  if (!(bin = NULL) && !(bin_path = NULL)
      && tcgetattr(STDIN_FILENO, &t) == -1)
    return (NULL);
  i = -1;
  while (path && path[++i])
    if ((dirp = opendir(path[i])))
      {
	while ((entry = readdir(dirp)))
	  if ((lev = levenshtein_lenght(av, entry->d_name)) < dist
	      && strlen(entry->d_name) > 1 && strcmp("..", entry->d_name))
	    {
	      dist = lev;
	      bin = my_strdup(entry->d_name);
	      bin_path = my_strdup(path[i]);
	    }
	closedir(dirp);
      }
  return (ask_correction(bin, bin_path, &t, lev));
}

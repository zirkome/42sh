/*
** epur_str.c for epur_str.c in /home/bridou_n/42sh
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Tue Mar 19 13:45:13 2013 nicolas bridoux
** Last update Sat May 25 22:26:16 2013 fabien linardon
*/

#include "42s.h"

static int	is_after_key_char(char *str, int i, char *cmd, int j)
{
  if (cmd[j] == ';' || (cmd[j] == '&' && cmd[j - 1] == '&')
      || (cmd[j] == '|' && j && cmd[j - 1] == '|')
      || (cmd[j] == '|' && str[i + 1] != '|')
      || (cmd[j] == '>' && j && cmd[j - 1] == '>')
      || (cmd[j] == '>' && str[i + 1] != '>')
      || (cmd[j] == '<' && j && cmd[j - 1] == '<')
      || (cmd[j] == '<' && str[i + 1] != '<')
      || (cmd[j] == '`'))
    return ((i && cmd[j - 1] == '\\') ? (FALSE) : (TRUE));
  return (FALSE);
}

static int	is_before_key_char(char *str, int i)
{
  if (str[i] == ';' || (str[i] == '&' && str[i + 1] == '&')
      || (str[i] == '|' && str[i + 1] == '|')
      || (str[i] == '|' && i && str[i - 1] != '|')
      || (str[i] == '>' && str[i + 1] == '>')
      || (str[i] == '>' && i && str[i - 1] != '>')
      || (str[i] == '<' && str[i + 1] == '<')
      || (str[i] == '<' && i && str[i - 1] != '<')
      || (str[i] == '`') || (!i && str[i] == '|' && str[i + 1] != '|')
      || (!i && str[i] == '>')
      || (!i && str[i] == '<'))
    return ((i && str[i - 1] == '\\') ? (FALSE) : (TRUE));
  return (FALSE);
}

static char	*fill_cmd_multiple(char *str, int nb_cmd, int i, int j)
{
  char		*cmd;

  if (!str)
    return (NULL);
  if ((cmd = malloc(sizeof(char) * strlen(str) + nb_cmd + 1)) == NULL)
    {
      fprintf(stderr, "Not enough memory\n");
      return (NULL);
    }
  while (str[++i])
    {
      if (is_before_key_char(str, i))
	cmd[j++] = ' ';
      cmd[j] = str[i];
      if (is_after_key_char(str, i, cmd, j))
	cmd[++j] = ' ';
     ++j;
    }
  cmd[j] = '\0';
  i = -1;
  while (cmd[++i])
    while (cmd[i] == ' ' && cmd[i + 1] == ' ')
      shift(cmd, i);
  return (cmd);
}

static char	*multiple_cmd(char *str)
{
  int		i;
  int		count;

  count = 1;
  i = -1;
  while (str && str[++i] != '\0')
    {
      while (str[i] == ';' && str[i + 1] == ';')
	shift(str, i);
      if (str[i] == ';' || str[i] == '&' || str[i] == '|'
	  || str[i] == '>' || str[i] == '<' || str[i] == '`')
	count += 2;
    }
  return (fill_cmd_multiple(str, count, -1, 0));
}

char	*epur_str(char *str)
{
  int	i;

  i = -1;
  while (str && str[++i])
    if (str[i] == '\t')
      str[i] = ' ';
  i = -1;
  while (str && str[++i] != '\0')
    if (str[i] == ' ')
      while (str[i + 1] == ' ')
	shift(str, i);
  return (multiple_cmd(str));
}

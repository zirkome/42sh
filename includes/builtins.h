/*
** builtins.h for 42sh in /home/fillon_g/projets/42sh-2017-fillon_g/src
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.net>
**
** Started on  Thu May 16 16:08:29 2013 guillaume fillon
** Last update Sun May 26 22:17:11 2013 guillaume fillon
*/

#ifndef BUILTINS_H_
# define BUILTINS_H_

# include "42s.h"

# define NO_LINE	1
# define NO_CHARS	2

typedef struct s_echo t_echo;
struct	s_echo
{
  char	key;
  char	value;
};

/*
** srcs/builtins
*/
int	handle_builtins(char **cmd, t_shenv *shenv);
int	is_builtin(char **cmd, t_shenv *shenv);
char	*_builtin_getenv(char *name, t_shenv *shenv);
int	_builtin_cd(char **cmd, t_shenv *shenv);
int	_builtin_unsetenv(char **cmd, t_shenv *shenv);
int	_builtin_setenv(char **cmd, t_shenv *shenv);
int	_builtin_env(char **cmd, t_shenv *shenv);
int	_builtin_export(char **cmd, t_shenv *shenv);
int	_builtin_history(char **cmd, t_shenv *shenv);
int	_builtin_pwd(char **cmd, t_shenv *shenv);
int	_builtin_exit(char **cmd, t_shenv *shenv);
int	_builtin_echo(char **cmd, t_shenv *shenv);
int	_builtin_alias(char **cmd, t_shenv *shenv);
int	_builtin_unalias(char **cmd, t_shenv *shenv);
int	_builtin_set(char **cmd, t_shenv *shenv);
int	_builtin_unset(char **cmd, t_shenv *shenv);
int	_builtin_help(char **cmd, t_shenv *shenv);

#endif /* !BUILTINS_H_ */

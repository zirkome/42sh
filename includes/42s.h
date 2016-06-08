/*
** main.h for main.h in /home/bridou_n/42sh
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Tue Mar 19 11:24:11 2013 nicolas bridoux
** Last update Sun May 26 22:21:55 2013 guillaume fillon
*/

#ifndef H42S_H_
# define H42S_H_

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <strings.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <pwd.h>
# include <errno.h>
# include <glob.h>
# include <term.h>
# include <termios.h>
# include <dirent.h>
# include <sys/ioctl.h>
# undef tab

# define GREEN		"\033[00;32m"
# define GREEN_BOLD	"\033[01;32m"
# define CYAN		"\033[00;36m"
# define CYAN_BOLD     	"\033[01;36m"
# define BLUE		"\033[00;34m"
# define BLUE_BOLD	"\033[01;34m"
# define YELLOW		"\033[00;33m"
# define YELLOW_BOLD	"\033[01;33m"
# define RED		"\033[00;31m"
# define RED_BOLD	"\033[01;31m"
# define MAGENTA	"\033[00;35m"
# define MAGENTA_BOLD	"\033[01;35m"
# define WHITE_BOLD	"\033[01;37m"
# define INIT		"\033[00;0m"

# define MAX_PATH_SIZE	4096
# define READ		MAX_PATH_SIZE
# define TRUE		1
# define FALSE		0
# define LEV		50
# define K_UP		0x00415B1B
# define K_DOWN		0x00425B1B
# define K_RIGHT	0x00435B1B
# define K_LEFT		0x00445B1B
# define K_ENTER	0x0000000A
# define K_TAB		0x00000009
# define K_DEL		0x7E335B1B
# define K_BCKSP	0x0000007F
# define K_BEGIN	0x00485B1B
# define K_END		0x00465B1B
# define K_PG_UP	0x7E355B1B
# define K_PG_DOWN	0x7E365B1B
# define K_CUT		0x0000000B
# define K_PASTE	0x00000019

# define ABS(x)		((x) > 0) ? (x) : (-x)
# define MAX(a, b)	((a) > (b)) ? (a) : (b)

struct	s_status
{
  int	sig;
  char	*message;
};

typedef struct s_status t_status;

struct	s_lev
{
  int	i;
  int	j;
  int	len_1;
  int	len_2;
  int	*tab;
  int	cost;
};

typedef struct s_lev t_lev;

struct		s_list
{
  char		*name;
  char		*value;
  struct s_list	*next;
};

typedef struct s_list t_list;

struct		s_shenv
{
  t_list	*env;
  char		**envp;
  t_list	*lvar;
  t_list	*alias;
  int		status;
  int		exit;
  int		tty_fd;
  int		interactive;
  pid_t		pid;
};

typedef struct s_shenv t_shenv;

struct	s_builtin
{
  char	*name;
  int	(*fptr)(char **, t_shenv *);
};

typedef struct s_builtin t_builtin;

typedef	struct	s_line
{
  int		rk;
  int		x;
  int		y;
  int		win_x;
  int		win_y;
  int		prompt;
  int		history;
  int		fd;
  char		*actual;
  char		*cpy;
}		t_line;

/*
** display_prompt.c
*/
void	display_prompt(char *path, int fd);

/*
** get_cmd.c
*/
int	get_cmd(t_shenv *shenv);

/*
** catch_cmd.c
*/
char	*catch_cmd(char *iterm, int prompt, t_shenv *shenv, int i_raw);

/*
** cmd_tab.c
*/
char	*cmd_tab(int buf, char *str, t_line *line, t_shenv *shenv);

/*
** parsing.c
*/
int	parsing(char *str, t_shenv *shenv, int n);
char	**make_tab_cmd(char *str);

/*
** parse_cmd.c
*/
char	**my_str_to_argtab(char *str, int i, int k, int j);
int	nb_cmd(char *str, char delim);
int	parse_cmd(char *cmd, t_shenv *shenv, int n);
int	is_redirection(char *str);

/*
** globing.c
*/
char	**make_globing(char **tab);

/*
** dispatch_cmd.c
*/
int	dispatch_cmd(char **cmd, t_shenv *shenv, int n);
int	check_path(char **av, t_shenv *shenv, int rk);

/*
** replace_alias.c
*/
int	is_and_or(char *str);
char	**replace_alias(char **cmd, t_shenv *shenv);

/*
** is_redirect.c
*/
int	is_redirect(char *cmd);
int	is_mass_redirect(char **cmd);

/*
** check_redir_pipe.c
*/
int	check_redirection(char **cmd, t_shenv *shenv);
int	check_pipe(char **cmd, t_shenv *shenv);

/*
** look_for_type.c
*/
int	lookfor_type(char **av, char **cmd, t_shenv *shenv, int n);

/*
** output_redirect.c
*/
int	simple_output(char **av, char **cmd, t_shenv *shenv, int n);
int	double_output(char **av, char **cmd, t_shenv *shenv, int n);

/*
** input_redirect.c
*/
int	simple_input(char **av, char **cmd, t_shenv *shenv, int n);
int	double_input(char **av, char **cmd, t_shenv *shenv);

/*
** pipe.c
*/
int	is_pipe(char **cmd);
int	my_pipe(char **cmd, t_shenv *shenv);

/*
** path_management.c
*/
char	**make_path(char **env);
char	*path_management(char *av, t_shenv *shenv);
int	is_bin(char *bin);

/*
** cut_cmd.c
*/
char	**cut_cmd(char **cmd);

/*
** exec_cmd.c
*/
int	exec_bin(char **av, t_shenv *shenv);
int	exec_cmd(char **cmd, t_shenv *shenv, int n);
int	handle_status(pid_t pid, char *cmd, t_shenv *shenv);

/*
** magic_quote.c
*/
char	**magic_quote(char **cmd, t_shenv *shenv, int *ret);
int	is_magic(char **cmd);
int	check_magic(char **cmd);
char	*exec_magic(char **cmd, int *ret, t_shenv *shenv, char **av);
char	*magic_error(void);
char	**cut_magic(char **cmd, char **magic);
int	len_of_magic(char **cmd, char **magic);
char	**my_magic_cmd(char **cmd);
char	*tab_to_word_str(char **tab);
char	*magic_read(const int fd);

/*
** levenshtein
*/
char	*correct(char *av, char **path, int lev, int dist);
int	levenshtein_lenght(char *str1, char *str2);

/*
** termcaps
*/
int	my_put_in_raw(char *iterm);
void	my_put_off_raw(void);
int	my_putc(int c);
int	raw_mode(struct termios *t);
int	raw_mode_off(struct termios *t);
char	*my_left(int buf, char *str, t_line *line);
char	*my_right(int buf, char *str, t_line *line);
char	*go_to_begin(int buf, char *str, t_line *line);
char	*end_of_line(int buf, char *str, t_line *line);
int	my_putint(int c);
void	go_up(void);
void	go_left(void);
void	go_right(void);
char	*my_delete(int buf, char *str, t_line *line);
char	*my_back_space(int buf, char *str, t_line *line);
void	recup_position(char *cpy, t_line *line, char *str, int rk);
char	*my_delete_and_recup(int buf, char *str, t_line *line);
void	my_recup(char *cpy, t_line *line, int rk, char *str);
char	*my_cut(int buf, char *str, t_line *line);
char	*my_paste(int buf, char *str, t_line *line);

/*
** add_history_line.c
*/
char	*get_history_file_path(void);
int	add_history_line(char *cmd, t_shenv *shenv);
char	*my_up(int buf, char *str, t_line *line);
char	*my_down(int buf, char *str, t_line *line);
char	**get_history_line(void);
void	my_aff_histo(char *str, t_line *line, char *old);
void	my_aff_char(char c, t_line *line);

/*
** utils
*/
char	*my_getcwd(void);
char	*my_strcat(char *a, char *b);
char	*my_strcat2(char *a, int b);
char	*my_strdup(char *str);
int	xfree(const int count, ...);
int	my_free_tab(char **tab);
int	my_error(char *str);
int	my_getnbr(char *str);
char	*read_fd(const int fd);
t_list	*copy_env(t_list *list, char *env[]);
void	shift(char *str, int i);
char	**my_str_to_pathtab(char *str, int i, int j, int k);
char	*epur_str(char *str);
int	is_alphanumeric(char c);

/*
** Inhibitors
*/
int	check_inhibitors(char *str);
char	*epur_string(char *cmd, int i, int k, char *ret);
void	ignore_it(char *str, int *i);
void	delete_inhibitors(char **tab);
void	check_last_and_first_char(char *str);
char	*concat_end(char *end, char *str);
char	*get_end(char *str, int *i, int *k, char **ret);

/*
** env_var.c
*/
char	*replace_var(char *cmd, t_shenv *shenv, int history, int replace);
char	*get_good_line(char *str, int i, int nb);
int	len_tab(char **tab);
char	*complete_history_str(char *begin, char *value, char *end);
char	*complete_str(char *str, int k, int i, char *value);
char	*get_local_var(char *name, t_shenv *shenv);

/*
** autocomplete_utils.c
*/
int	fill_tab_complete(char **tab, char *str, int rk);
int	cut_completion(char **tab, char *str, int rk);
int	find_max(char **tab);
int	first_n_char_are_the_same(char **tab, int n);
void	free_cmd_tab(char **tab);

/*
** autocomplete.c
*/
char	*auto_complete(char *str, t_line *line, t_shenv *shenv);
char	*display_matches(t_line *line, char **tab, char *str, char **tab_cmd);
char	*complete_if_possible(char *, char **, char **, t_line *);

/*
** search_binary.c
*/
int	actual_path(char *str);
char	**creat_binary_path(t_shenv *shenv);
char	*_builtin_getenv(char *name, t_shenv *shenv);
char	**fill_tab_binary(char *str, char **path, int i, int k);
int	count_binary_match(char *str, char **path);

/*
** one_completion_and_binary.c
*/
char	*one_completion(t_line *line, char *tab, char *str, char **tab_cmd);
char	*complete_binary(char *str, t_line *line, t_shenv *shnv, char *tab[4]);
int	only_one_completion(char **tab, char *str);

/*
** job_control.c
*/
void	create_real_son(pid_t pid);
void	back_to_shell(pid_t pid);

/*
** load_conf_file.c
*/
void	load_conf_file(t_shenv *shenv);

#endif /* !H42S_H_ */

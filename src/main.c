/*
** main.c for main.c in /home/bridou_n/42sh
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Tue Mar 19 11:23:45 2013 nicolas bridoux
** Last update Sun May 26 20:29:20 2013 fabien linardon
*/

#include "42s.h"
#include "list.h"

static void	sig_int(int sig)
{
  if (sig == SIGINT)
    {
      putchar('\n');
      display_prompt(my_getcwd(), 1);
    }
  return ;
}

static void	catch_signal()
{
  signal(SIGINT, &sig_int);
  signal(SIGQUIT, SIG_IGN);
  signal(SIGTSTP, SIG_IGN);
  signal(SIGUSR1, SIG_IGN);
  signal(SIGUSR2, SIG_IGN);
}

static void	init_sh_env(t_shenv *shenv, t_list *env)
{
  int		fd;

  shenv->env = env;
  shenv->alias = NULL;
  shenv->lvar = NULL;
  shenv->exit = 65535;
  shenv->pid = getpid();
  shenv->tty_fd = ((fd = open("/dev/tty", O_RDWR)) != -1) ? fd : 2;
}

static void	free_shenv(t_shenv *shenv)
{
  my_free_tab(shenv->envp);
  my_free_list(&shenv->env);
  my_free_list(&shenv->lvar);
  my_free_list(&shenv->alias);
}

int		main(__attribute__((unused)) int argc,
		       __attribute__((unused)) char *argv[],
		       char *envp[])
{
  t_shenv	shenv;
  t_list	*env;

  setsid();
  env = NULL;
  env = copy_env(env, envp);
  init_sh_env(&shenv, env);
  catch_signal();
  shenv.envp = NULL;
  shenv.interactive = FALSE;
  load_conf_file(&shenv);
  display_prompt(my_getcwd(), shenv.tty_fd);
  if (get_cmd(&shenv) == EXIT_FAILURE)
  {
    free_shenv(&shenv);
    if (shenv.exit != 65535)
      return ((unsigned char) shenv.exit);
    return (EXIT_FAILURE);
  }
  free_shenv(&shenv);
  close(shenv.tty_fd);
  return (EXIT_SUCCESS);
}

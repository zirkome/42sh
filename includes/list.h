/*
** list.h for 42sh in /home/fillon_g/projets/42sh-2017-fillon_g/src
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.net>
**
** Started on  Thu May 16 16:07:31 2013 guillaume fillon
** Last update Sun May 26 22:17:26 2013 guillaume fillon
*/

#ifndef LIST_H_
# define LIST_H_

# include "42s.h"

/*
** linked list
*/
t_list	*my_get_node_eq(t_list *list, char *name);
char	**my_put_list_to_tab(t_list *list);
void	my_put_in_end(t_list **list, char *name, char *value);
void	my_put_in_list(t_list **list, char *name, char *value);
void	my_rm_eq(t_list **list, char *name_delete);
void	my_show_list(t_list *list);
void	my_show_alias(t_list *list);
void	my_free_list(t_list **env);
int	my_list_size(t_list *list);

#endif /* !LIST_H_ */

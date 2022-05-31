/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvioleta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:57:01 by vvioleta          #+#    #+#             */
/*   Updated: 2022/05/21 14:57:03 by vvioleta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_node
{
	int		ac;
	int		fd[2][2];
	int		fd_in;
	int		fd_out;
	int		here_doc_flag;
	char	**av;
	char	**env;
	int		size;
}	t_node;

typedef struct s_cmd
{
	char			**cmd;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}	t_cmd;

int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2, int flag);
size_t	ft_strlen(const char *n);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	here_doc(t_node **node);
void	fill_cmd(t_cmd **cmd, t_node *node, char *str, int i);
void	ft_execve(t_cmd **cmd, t_node **node);
int		lst_size(t_cmd **cmd);
void	find_path(t_cmd **cmd, t_node *node);
void	check_here_doc(t_node **node, t_cmd **cmd);
void	init_node(t_node **node, int ac, char **av, char **env);
void	first_child(int *i, t_cmd **cmd, t_node **node, pid_t *pid);
void	second_child(int *i, t_cmd **cmd, t_node **node, pid_t *pid);
void	process(t_cmd	**cmd, t_node	**node, pid_t *pid);
void	free_init(t_cmd **cmd, pid_t *pid);
void	path_join(t_cmd **cmd, char **path, t_cmd *tmp);

#endif

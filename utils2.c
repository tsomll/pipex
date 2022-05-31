/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvioleta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:57:24 by vvioleta          #+#    #+#             */
/*   Updated: 2022/05/21 14:57:25 by vvioleta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if ((int)n == 0)
		return (0);
	while ((unsigned char)(*s1) == (unsigned char )(*s2) && \
	n > 1 && *s1 != '\0' && *s2 != '\0')
	{
		s1++;
		s2++;
		n--;
	}
	return ((unsigned char )*s1 - (unsigned char)*s2);
}

void	ft_execve(t_cmd	**cmd, t_node **node)
{
	if (!access((*cmd)->cmd[0], X_OK))
		execve((*cmd)->cmd[0], (*cmd)->cmd, (*node)->env);
	write(2, "pipex: ", 7);
	write(2, (*cmd)->cmd[0], ft_strlen((*cmd)->cmd[0]));
	write(2, " :command not found\n", 20);
	exit(127);
}

void	init_node(t_node **node, int ac, char **av, char **env)
{
	(*node)->ac = ac;
	(*node)->fd_in = -2;
	(*node)->fd_out = -2;
	(*node)->env = env;
	(*node)->av = av;
}

void	free_init(t_cmd **cmd, pid_t *pid)
{
	t_cmd	*tmp;
	int		i;

	tmp = *cmd;
	while (tmp)
	{
		i = -1;
		while (tmp->cmd[++i])
			free(tmp->cmd[i]);
		free(tmp->cmd);
		free(tmp);
		tmp = tmp->next;
	}
	*cmd = NULL;
	free(pid);
}

int	lst_size(t_cmd **cmd)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = *cmd;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

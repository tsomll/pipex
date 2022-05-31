/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvioleta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:56:49 by vvioleta          #+#    #+#             */
/*   Updated: 2022/05/21 14:56:50 by vvioleta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(int *i, t_cmd **cmd, t_node **node, pid_t *pid)
{
	if (*cmd)
	{
		pipe((*node)->fd[0]);
		pid[*i] = fork();
		if (!pid[*i])
		{
			if ((*cmd)->fd_in > 0)
				dup2((*cmd)->fd_in, 0);
			else if (*i > 0)
				dup2((*node)->fd[1][0], 0);
			if ((*cmd)->fd_out > 0)
				dup2((*cmd)->fd_out, 1);
			else if (*i < (*node)->size - 1)
				dup2((*node)->fd[0][1], 1);
			close((*node)->fd[0][1]);
			close((*node)->fd[0][0]);
			ft_execve(cmd, node);
		}
		close((*node)->fd[0][1]);
		close((*node)->fd[1][0]);
		*cmd = (*cmd)->next;
		(*i)++;
	}
}

void	second_child(int *i, t_cmd **cmd, t_node **node, pid_t *pid)
{
	if (*cmd)
	{
		pipe((*node)->fd[1]);
		pid[*i] = fork();
		if (!pid[*i])
		{
			if ((*cmd)->fd_in > 0)
				dup2((*cmd)->fd_in, 0);
			else if (*i > 0)
				dup2((*node)->fd[0][0], 0);
			if ((*cmd)->fd_out > 0)
				dup2((*cmd)->fd_out, 1);
			else if (*i < (*node)->size - 1)
				dup2((*node)->fd[1][1], 1);
			close((*node)->fd[0][0]);
			close((*node)->fd[1][1]);
			ft_execve(cmd, node);
		}
		close((*node)->fd[0][0]);
		close((*node)->fd[1][1]);
		*cmd = (*cmd)->next;
		(*i)++;
	}
}

void	fill_cmd(t_cmd **cmd, t_node *node, char *str, int i)
{
	t_cmd	*curr;
	t_cmd	*tmp;

	tmp = malloc(sizeof(t_cmd));
	tmp->fd_in = -2;
	tmp->fd_out = -2;
	tmp->cmd = ft_split(str, ' ');
	tmp->next = NULL;
	if (*cmd == NULL)
	{
		tmp->fd_in = node->fd_in;
		*cmd = tmp;
		return ;
	}
	if (i == node->ac - 2)
		tmp->fd_out = node->fd_out;
	curr = *cmd;
	while (curr->next)
		curr = curr->next;
	curr->next = tmp;
}

int	main(int ac, char **av, char **env)
{
	t_node	*node;
	t_cmd	*cmd;
	pid_t	*pid;
	int		i;

	if (ac < 5)
		return (write(2, "Error\n", 6), 1);
	node = malloc(sizeof(t_node));
	if (!node)
		return (2);
	cmd = NULL;
	init_node(&node, ac, av, env);
	check_here_doc(&node, &cmd);
	node->size = lst_size(&cmd);
	pid = malloc(sizeof(int) * node->size);
	if (pid == NULL)
		exit(3);
	process(&cmd, &node, pid);
	i = 0;
	while (i++ < node->size - 1)
		waitpid(pid[i], NULL, 0);
	free(node);
	free_init(&cmd, pid);
}

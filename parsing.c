/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvioleta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:56:37 by vvioleta          #+#    #+#             */
/*   Updated: 2022/05/21 14:56:38 by vvioleta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_env(t_node **node, char *str)
{
	int	i;

	i = -1;
	while ((*node)->env[++i])
		if (!ft_strncmp((*node)->env[i], str, ft_strlen(str)))
			return ((*node)->env[i] + ft_strlen(str));
	return (NULL);
}

void	path_join(t_cmd **cmd, char **path, t_cmd *tmp)
{
	int		i;
	char	*res;

	while (tmp && path)
	{
		i = 0;
		while (path[i++])
		{
			res = ft_strjoin(path[i], "/", 0);
			res = ft_strjoin(res, tmp->cmd[0], 1);
			if (!access(res, X_OK))
			{
				free(tmp->cmd[0]);
				tmp->cmd[0] = ft_strdup(res);
				free(res);
				break ;
			}
			free(res);
		}
		tmp = tmp->next;
	}
}

void	find_path(t_cmd **cmd, t_node *node)
{
	int		i;
	t_cmd	*tmp;
	char	**path;

	tmp = *cmd;
	path = ft_split(find_env(&node, "PATH="), ':');
	path_join(cmd, path, tmp);
	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
}

void	process(t_cmd	**cmd, t_node	**node, pid_t *pid)
{
	int	i;

	i = 0;
	while (i < (*node)->size)
	{
		first_child(&i, cmd, node, pid);
		second_child(&i, cmd, node, pid);
	}
}

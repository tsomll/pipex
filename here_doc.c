/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvioleta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:56:28 by vvioleta          #+#    #+#             */
/*   Updated: 2022/05/21 14:56:29 by vvioleta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_next_line(void)
{
	char	*s;
	char	*c;

	s = malloc(2);
	c = NULL;
	while (read(0, s, 1) == 1 && s[0] != '\0')
	{
		s[1] = '\0';
		c = ft_strjoin(c, s, 1);
		if (s[0] == '\n')
			break ;
	}
	free(s);
	return (c);
}

void	check_here_doc(t_node **node, t_cmd **cmd)
{
	int	i;

	if (!ft_strcmp((*node)->av[1], "here_doc"))
	{
		(*node)->fd_out = open((*node)->av[(*node)->ac - 1], O_CREAT | O_APPEND \
		| O_WRONLY, 0644);
		here_doc(node);
		i = 2;
	}
	else
	{
		(*node)->fd_out = open((*node)->av[(*node)->ac - 1], O_CREAT | O_TRUNC \
		| O_WRONLY, 0644);
		if (access((*node)->av[1], F_OK))
			exit (write(2, "ErrorFile\n", 10));
		(*node)->fd_in = open((*node)->av[1], O_RDONLY);
		i = 1;
	}
	while (++i < (*node)->ac - 1)
		fill_cmd(cmd, *node, (*node)->av[i], i);
	find_path(cmd, *node);
}

void	here_doc(t_node **node)
{
	char	*res;
	char	*tmp;
	int		fd[2];
	char	*stop;

	res = NULL;
	stop = ft_strjoin((*node)->av[2], "\n", 0);
	while (1)
	{
		write(1, "here_doc> ", 10);
		tmp = get_next_line();
		if (!ft_strcmp(tmp, stop))
			break ;
		res = ft_strjoin(res, tmp, 1);
		free(tmp);
	}
	pipe(fd);
	write(fd[1], res, ft_strlen(res));
	(*node)->fd_in = fd[0];
	(*node)->here_doc_flag = 1;
	close(fd[1]);
	free(res);
	free(tmp);
	free(stop);
}

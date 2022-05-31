/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvioleta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:57:15 by vvioleta          #+#    #+#             */
/*   Updated: 2022/05/21 14:57:17 by vvioleta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (s1 - s2);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char	*first_join(char const *s2)
{
	int		i;
	char	*str;
	char	*rez;

	i = -1;
	str = (char *)s2;
	rez = malloc(sizeof(char) * ft_strlen((str) + 1));
	if (!rez)
		exit(2);
	while (str[++i])
		rez[i] = str[i];
	rez[i] = '\0';
	return (rez);
}

char	*ft_strjoin(char const *s1, char const *s2, int flag)
{
	char	*src;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (s2 == NULL || s2[0] == '\0')
		return (NULL);
	if (s1 == NULL)
		src = first_join(s2);
	else
	{
		src = malloc((ft_strlen((char *) s1) + ft_strlen((char *) s2) + 2));
		if (src == NULL)
			return (NULL);
		while (s1[k] != '\0')
			src[i++] = s1[k++];
		k = 0;
		while (s2[k] != '\0')
			src[i++] = s2[k++];
		src[i] = '\0';
	}
	if (flag)
		free((char *)s1);
	return (src);
}

size_t	ft_strlen(const char *n)
{
	int	s;

	s = 0;
	while (*n != '\0')
	{
		n++;
		s++;
	}
	return ((size_t)s);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		size;

	size = ft_strlen((char *)s1);
	s2 = (char *)malloc(size + 1);
	if (s2 == NULL)
		return (NULL);
	s2[size] = '\0';
	while (size-- > 0)
		s2[size] = s1[size];
	return (s2);
}

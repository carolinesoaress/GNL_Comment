/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagoncal <cagoncal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:02:04 by cagoncal          #+#    #+#             */
/*   Updated: 2023/12/04 15:16:50 by cagoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *str, int c)
{
	char	caracter;

	caracter = c;
	if (!str)
		return (NULL);
	while (*str != caracter)
	{
		if (*str == '\0')
		{
			return (NULL);
		}
		str++;
	}
	return ((char *) str);
}

char	*ft_cpy(char *line, int pos)
{
	char	*line_to_return;
	int		i;

	i = 0;
	if (!line || pos < 0)
		return (NULL);
	line_to_return = (char *)malloc(sizeof(char) * (pos + 1));
	if (!line_to_return)
		return (NULL);
	while (line && i < pos)
	{
		line_to_return[i] = line[i];
		i++;
	}
	line_to_return[i] = '\0';
	return (line_to_return);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	n;
	size_t	i;
	size_t	result;
	char	*str3;

	result = ft_strlen(s1) + ft_strlen(s2);
	n = 0;
	i = 0;
	str3 = (char *)malloc(result + 1);
	if (str3 == NULL)
		return (NULL);
	while (s1 && s1[n] != '\0')
	{
		str3[n] = s1[n];
		n++;
	}
	while (s2 && s2[i] != '\0')
	{
		str3[n + i] = s2[i];
		i++;
	}
	str3[n + i] = '\0';
	free ((char *)s1);
	return (str3);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	char	*cpy;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(str) + 1;
	cpy = (char *)malloc(len);
	if (!cpy)
		return (NULL);
	while (str[i] != '\0')
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

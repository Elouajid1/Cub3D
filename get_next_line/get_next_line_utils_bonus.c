/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-ouaj <mel-ouaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:51:09 by mel-ouaj          #+#    #+#             */
/*   Updated: 2025/02/25 15:23:06 by mel-ouaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strchr(const char *str, char c)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*str;

	if (count != 0 && (size > SIZE_MAX / count))
		return (NULL);
	str = malloc(count * size);
	if (!str)
		return (NULL);
	i = 0;
	while (i < (count * size))
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

char	*ft_strdup(const char *str)
{
	size_t	i;
	size_t	len;
	char	*s;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	s = ft_calloc(sizeof(char) * (len + 1), 1);
	if (!s)
		return (NULL);
	i = 0;
	while (i < len)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		s1 = ft_strdup("");
	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), 1);
	if (!str)
		return (free(s1), NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (free(s1), str);
}

// int main()
// {
//     char *s1 = "abc";
//     char *s2 = "def";
//     printf("%s", ft_strjoin(s1, s2));
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschiman <mschiman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 11:30:57 by mschiman          #+#    #+#             */
/*   Updated: 2021/09/07 13:52:04 by mschiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen_del(const char *s, char del)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i] != del && s[i] != '\0')
			i++;
	}
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;
	size_t			i;

	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	while (n > 0 && i < n)
	{
		ptr_dest[i] = ptr_src[i];
		i++;
	}
	return (dest);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n > 0)
	{
		*ptr = c;
		ptr++;
		n--;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*res;
	size_t	i;

	res = (char *) malloc(nmemb * size);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < (nmemb * size))
	{
		res[i] = '\0';
		i++;
	}
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	join_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	join_len = ft_strlen_del(s1, '\0') + ft_strlen_del(s2, '\0');
	join = (char *) ft_calloc ((join_len + 1), sizeof (char));
	if (join == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		join[i + j] = s2[j];
		j++;
	}
	free((char *)s1);
	return (join);
}

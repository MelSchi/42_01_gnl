/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschiman <mschiman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 10:22:39 by mschiman          #+#    #+#             */
/*   Updated: 2021/09/07 13:51:55 by mschiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/* Moves everything after the newline to the front of the string*/
static void	move_str_to_front(char *buff)
{
	int		str_len;
	int		str_len_del;
	int		new_len;
	char	*temp;
	int		i;

	str_len = ft_strlen_del(buff, '\0');
	str_len_del = ft_strlen_del(buff, '\n');
	new_len = str_len - str_len_del;
	i = 0;
	temp = (char *) ft_calloc((new_len + 1), sizeof(char));
	while (i <= new_len)
	{
		temp[i] = buff[str_len_del + 1 + i];
		i++;
	}
	ft_memset(buff, '\0', str_len);
	i = 0;
	while (i < new_len)
	{
		buff[i] = temp[i];
		i++;
	}
	free (temp);
}

/* Extracts the string including newline and returns it (incl. \n and \0).
** Returns NULL if no newline was found */
static char	*extract_line(char *str, int nb)
{
	int		str_len;
	int		str_len_del;
	char	*line;

	str_len = ft_strlen_del(str, '\0');
	str_len_del = ft_strlen_del(str, '\n');
	if (str_len_del < str_len)
	{
		line = (char *) ft_calloc((str_len_del + 2), sizeof(char));
		if (line == NULL)
			return (NULL);
		ft_memcpy(line, str, (str_len_del + 1));
		if (nb > 0)
			free (str);
		return (line);
	}
	return (NULL);
}

static int	handle_old_buff(char **line, char *buff)
{
	int		str_len;

	str_len = 0;
	if (buff[0] != '\0')
	{
		*line = extract_line(buff, 0);
		if (*line != NULL)
		{
			move_str_to_front(buff);
			return (1);
		}
		str_len = ft_strlen_del(buff, '\0');
		*line = (char *) ft_calloc((str_len + 1), sizeof(char));
		if (*line == NULL)
			return (-1);
		ft_memcpy(*line, buff, str_len);
		ft_memset(buff, '\0', (BUFFER_SIZE + 1));
		return (0);
	}
	return (0);
}

static int	handle_read(int fd, char *buff, char **line, int *bytes_read)
{
	ft_memset(buff, '\0', (BUFFER_SIZE + 1));
	*bytes_read = read(fd, buff, BUFFER_SIZE);
	if ((**line == '\0' && *bytes_read == 0) || *bytes_read == -1)
	{
		free(*line);
		ft_memset(buff, '\0', (BUFFER_SIZE + 1));
		return (-1);
	}
	if (*bytes_read != 0)
	{
		*line = ft_strjoin(*line, buff);
		if (ft_strlen_del(buff, '\n') < *bytes_read)
		{
			*line = extract_line(*line, 1);
			move_str_to_front(buff);
			*bytes_read = 1;
			return (1);
		}
	}
	ft_memset(buff, '\0', (BUFFER_SIZE + 1));
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buff[1024][BUFFER_SIZE + 1];
	char		*line;
	int			status;
	int			bytes_read;

	if (fd < 0 || fd > 1024)
		return (NULL);
	status = 0;
	bytes_read = -2;
	line = (char *) ft_calloc(1, sizeof(char));
	while (bytes_read != 0)
	{
		if (buff[fd][0] != '\0')
			free(line);
		status = handle_old_buff(&line, buff[fd]);
		if (status == 1 || status == -1)
			return (line);
		status = handle_read(fd, buff[fd], &line, &bytes_read);
		if (status == 1)
			return (line);
		if (status == -1)
			return (NULL);
	}
	return (line);
}

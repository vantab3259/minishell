/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbae <tbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 12:53:41 by tbae              #+#    #+#             */
/*   Updated: 2023/02/02 14:38:21 by tbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_search(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (i);
	else
		return (-1);
}

static char	*ft_newline(char *str)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	line = malloc(i + 2);
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i] = '\n';
	else
		line[i] = '\0';
	line[i + 1] = '\0';
	return (line);
}

static char	*ft_newstr(ssize_t nb_read, char *buffer, int fd)
{
	char		*tmp;
	static char	*str[1024];

	if (!str[fd] && nb_read == 0)
		return (NULL);
	if (!str[fd])
	{
		str[fd] = malloc(1);
		str[fd][0] = '\0';
	}
	tmp = gnl_dub(str[fd]);
	free(str[fd]);
	str[fd] = gnl_join(tmp, buffer, nb_read);
	free(tmp);
	tmp = gnl_dub(str[fd]);
	if (ft_search(str[fd]) >= 0 || nb_read < BUFFER_SIZE)
	{
		free(str[fd]);
		str[fd] = gnl_trim(tmp);
	}
	return (tmp);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	*str;
	char	*buffer;
	int		nb_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	nb_read = read(fd, buffer, BUFFER_SIZE);
	if (nb_read >= 0)
		str = ft_newstr(nb_read, buffer, fd);
	free (buffer);
	if (nb_read < 0)
		return (NULL);
	if (!str || ft_search(str) >= 0 || nb_read < BUFFER_SIZE)
		line = ft_newline(str);
	else
		line = get_next_line(fd);
	free (str);
	return (line);
}

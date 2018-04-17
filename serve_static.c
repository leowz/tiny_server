/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serve_static.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:07:00 by zweng             #+#    #+#             */
/*   Updated: 2018/04/17 21:47:55 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tiny_server.h"

void	get_filetype(char *filename, char *filetype)
{
	if (ft_strstr(filename, ".html"))
	{
		ft_strcpy(filetype, "text/html");
	}
	else if (ft_strstr(filename, ".gif"))
	{
		ft_strcpy(filetype, "text/gif");
	}
	else if (ft_strstr(filename, ".jpg"))
	{
		ft_strcpy(filetype, "text/gif");
	}
	else
	{
		ft_strcpy(filetype, "text/plain");
	}
}

void	serve_static(int fd, char *filename, int filesize)
{
	int		srcfd;
	char	*srcp, filetype[MAXLINE], buf[MAXBUF];	

	get_filetype(filename, filetype);
	sprintf(buf, "HTTP/1.0 200 OK\r\n");
	sprintf(buf, "%sServer: Tiny Server\r\n", buf);
	sprintf(buf, "%sContent-length: %d\r\n", buf, filesize);
	sprintf(buf, "%sContent-type: %s\r\n\r\n", buf, filetype);
	write(fd, buf, strlen(buf));

	if ((srcfd = open(filename, O_RDONLY)) < 0)
		return ;
	srcp = mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
	close(srcfd);
	write(fd, srcp, filesize);
	munmap(srcp, filesize);
}

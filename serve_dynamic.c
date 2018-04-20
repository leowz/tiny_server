/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serve_dynamic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 21:48:23 by zweng             #+#    #+#             */
/*   Updated: 2018/04/20 15:58:50 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include "tiny_server.h"

extern char **environ;

void	serve_dynamic(int fd, char *filename, char *cgiargs)
{
	char	buf[MAXBUF], *ept[] = {NULL};

	sprintf(buf, "HTTP/1.0 200 OK\r\n");
	sprintf(buf, "%sServer: Tiny server\r\n", buf);
	write(fd, buf, ft_strlen(buf));
	if (fork() == 0)
	{
		setenv("QUERY_STRING", cgiargs, 1);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			printf("redirect fails\n");
			exit(1);
		}	
		if (execve(filename, ept, environ) == -1)
		{
			printf("execve fails: %s\n", strerror(errno));
			exit(1);
		}
	}
	wait(NULL);
}

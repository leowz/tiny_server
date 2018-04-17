/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 19:49:09 by zweng             #+#    #+#             */
/*   Updated: 2018/04/17 19:07:30 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tiny_server.h"

int		main(int ac, char **av)
{
	int					listenfd, connfd, port,  n;
	unsigned int 		clientlen;
	struct sockaddr_in 	clientaddr;
	//struct hostent		*hp;
	char				*haddrp;
	char				*line;

	ac > 1 ? (port = ft_atoi(av[1])) : (port = 80);
	if ((listenfd = open_listenfd(port)) < 0)
	{
		printf("open listenfd fails!\n");
	}
	while (1)
	{
		clientlen = sizeof(clientaddr);
		connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
		haddrp = inet_ntoa(clientaddr.sin_addr);
		
		while ((n = get_next_line(connfd, &line)) > 0)
		{
			printf("server received %d bytes\n", ft_strlen(line));
			printf("%s\n", line);
			ft_strdel(&line);
		}
		close(connfd);
	}
	return (0);
}

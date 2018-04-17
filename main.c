/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 19:49:09 by zweng             #+#    #+#             */
/*   Updated: 2018/04/17 21:33:00 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tiny_server.h"

int		main(int ac, char **av)
{
	int					listenfd, connfd, port;
	unsigned int 		clientlen;
	struct sockaddr_in 	clientaddr;

	ac > 1 ? (port = ft_atoi(av[1])) : (port = 80);
	if ((listenfd = open_listenfd(port)) < 0)
	{
		printf("open listenfd fails!\n");
		return (-1);
	}
	while (1)
	{
		clientlen = sizeof(clientaddr);
		connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
		handle_request(connfd);
		close(connfd);
	}
	return (0);
}

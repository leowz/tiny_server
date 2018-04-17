/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_listenfd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 17:22:34 by zweng             #+#    #+#             */
/*   Updated: 2018/04/17 18:02:50 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tiny_server.h"

int		open_listenfd(int port)
{
	int					listenfd;
	int					optval;
	struct sockaddr_in	serveraddr;

	optval = 1;
	printf("listen to port %d\n", port);
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket fail\n");
		return (-1);
	}
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,
					(const void *)&optval, sizeof(int)) < 0)
	{
		printf("setsockopt fail\n");
		return (-1);
	}
	ft_bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons((unsigned short)port);
	if (bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
	{
		printf("bind fail\n");
		return (-1);
	}
	if (listen(listenfd, 1024) < 0)
	{
		printf("listen fail\n");
		return (-1);
	}
	return (listenfd);
}

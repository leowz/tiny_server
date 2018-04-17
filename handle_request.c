/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_request.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 20:14:37 by zweng             #+#    #+#             */
/*   Updated: 2018/04/17 21:44:58 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tiny_server.h"

int		parse_uri(char *uri, char *filename, char *cgiargs)
{
	if (ft_strstr(uri, ".php"))
	{
		return (0);	
	}
	else
	{
		ft_strcpy(cgiargs, "");
		ft_strcpy(filename, ".");
		ft_strcat(filename, uri);
		if (uri[ft_strlen(uri) - 1] == '/')
			ft_strcat(filename, "index.html");
		return (1);	
	}
}

void	handle_request(int fd)
{
	int				is_static;
	struct stat 	sbuf;
	char			*reqline;
	char			method[MAXLINE], uri[MAXLINE], version[MAXLINE];
	char			filename[MAXLINE], cgiargs[MAXLINE];

	if (get_next_line(fd, &reqline) <= 0)
	{
		printf("get request line fail\n");
		return ;
	}
	sscanf(reqline, "%s %s %s", method, uri, version);
	if (ft_strcmp(method, "GET"))
	{
		client_error(fd, method, "501", "Not supported",
				"This method is not supported");
		return ;
	}
	//TODO: handle headers
	is_static = parse_uri(uri, filename, cgiargs);
	if (stat(filename, &sbuf) < 0)
	{
		client_error(fd, filename, "404", "Not found",
				"This file cannot be found");
		return ;
	}
	if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode))
	{
		client_error(fd, filename, "403", "Forbidden",
				"This file is not accessible");
		return ;
	}
	if (is_static)
	{
		serve_static(fd, filename, sbuf.st_size);
	}
	else
	{
		serve_dynamic(fd, filename, cgiargs);
	}
}

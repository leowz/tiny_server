/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_request.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 20:14:37 by zweng             #+#    #+#             */
/*   Updated: 2018/04/20 15:33:12 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tiny_server.h"

int		parse_uri(char *uri, char *filename, char *cgiargs)
{
	char	*ptr;

	ptr = NULL;
	if (ft_strstr(uri, ".php"))
	{
		printf("dynam content\n");
		if ((ptr = ft_strchr(uri, '?')))
		{
			ft_strcpy(cgiargs, ptr + 1);
			*ptr = '\0';
		}
		else
			ft_strcpy(cgiargs, "");
		ft_strcpy(filename, ".");
		ft_strcat(filename, uri);
		return (0);	
	}
	else
	{
		printf("static content\n");
		ft_strcpy(cgiargs, "");
		ft_strcpy(filename, ".");
		ft_strcat(filename, uri);
		if (uri[ft_strlen(uri) - 1] == '/')
			ft_strcat(filename, "index.html");
		return (1);	
	}
}

void	get_headers(int fd)
{
	char	*line;

	while (1)
	{
		get_next_line(fd, &line);
		if(line && !ft_strcmp(line, "\r"))
		{
			ft_strdel(&line);
			return ;
		}
		printf("%s\n", line);
		ft_strdel(&line);
	}
}

int		get_request_line(int fd, char *reql)
{
	char	*line;

	if (get_next_line(fd, &line) <= 0)
	{
		printf("get request line fail\n");
		return (FUN_FAIL);
	}
	printf("%s\n", line);
	ft_strcpy(reql, line);
	ft_strdel(&line);
	return (FUN_SUCS);
}

void	handle_request(int fd)
{
	int				is_static;
	struct stat
		sbuf;
	char			reqline[MAXLINE], method[MAXLINE],
					uri[MAXLINE], version[MAXLINE];
	char			filename[MAXLINE], cgiargs[MAXLINE];

	if (!get_request_line(fd, reqline))
		return ;
	sscanf(reqline, "%s %s %s", method, uri, version);
	if (ft_strcmp(method, "GET"))
	{
		client_error(fd, method, "501", "Not supported",
				"This method is not supported");
		return ;
	}
	get_headers(fd);
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

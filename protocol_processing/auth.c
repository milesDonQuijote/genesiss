#include "protocol.h"

int	end_param(char *req)
{
	char	*tmp;

	tmp = req;
	while (*req)
	{
		if (*req++ == ' ')
			continue ;
		else if (*req++ == ':')
			break ;
		else
			return (-1);
	}
	return ((int)(req - tmp));
}

char	*get_token(char *req)
{
	char	*rtn;
	int	tlen;
	int	index;

	tlen = 1;
	index = 0;
	while (*req && *req == ' ')
		req++;
	while (*req && *req != ' ' && *req != '\n')
		req += !!tlen++;
	rtn = (char *)malloc(sizeof(char) * tlen);
	while (*req && *req != ' ' && *req != '\n')
		rtn[index++] = *req++;
	rtn[index] = 0;
	return (rtn);
}

int	auth(char *req, AUTHObject *auth_data)
{
	char	*tmp;
	int	req_err;

	if (strncmp(req, "token", 5))
		return (-1);
	req += 5;
	req_err = end_param(req);
	if (req_err)
		return (req_err);
	req +=  req_err;
	auth_data->token =  get_token(req);
	req = strchr(req, '\n');
	if (strncmp(req, "content-length", 14))
		return (-1);
	req_err = end_param(req);
	if (req_err)
		return (-1);
	req += req_err;
	auth_data->len = atoi(req);
	if (auth_data->len < 1)
		return (-1);
	req = strchr(req, '\n');
	if (*req != '\n')
		return (-1);
	auth_data->content = get_token(req);
	return (!auth_data->content);
}

int	main()
{
	char	*req = "token: TOKEN23123jshd23djs8df8d8Ds8DshEND\ncontent-length:            123    \n\nu:arbiyski;p:password";
	AUTHObject	auth_data;
	if (!auth(req, &auth_data))
	{
		printf("req error");
		exit(0);
	}
	printf("token = %s\ncontent-length = %i\ncontent = %s\n", auth_data.token, auth_data.len, auth_data.content);
	return (0);
}

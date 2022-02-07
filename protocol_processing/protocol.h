#ifndef PROTOCOL_H
# define PROTOCOL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

# define AUTH_PROT "GIP/1.0"

typedef struct s_auth {
	char	*token;
	int	len;
	char	*content;
} AUTHObject;

int	auth(char *req, AUTHObject *auth_data);

#endif

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	// printf("heere\n");
	if(!s1 && !s2)
		return(0);
	else if(!s1)
		return(-1);
	else if(!s2)
		return(1);
	while ((s1[i] == s2[i]) && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	return (s1[i] - s2[i]);
}

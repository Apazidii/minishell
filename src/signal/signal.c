#include "minishell.h"



static char *get_promt(void)
{
	char *res;
	char *str;
	char cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror("SIGINT");
		errno = 0;
		return (NULL);
	}
	str = ft_strjoin("\033[0;35mminishell\033[0m:\033[0;36m", cwd);
	res = ft_strjoin(str, "\033[0m$ ");
	free(str);
	if (res == NULL)
	{
		free(res);
		return (NULL);
	}
	return (res);
}

void sig_int(int k)
{
	char *promt;

	printf("\n");
	promt = get_promt();
	if (promt)
		printf("%s", promt);
}

#include "minishell.h"

int pwd(t_base *base)
{
	if (get_cwd(base))
		return (BUILTIN_ERROR);
	printf("%s\n", base->cwd);
	return (SUCCES);
}

#include "minishell.h"

void built_env(t_info *struktura)
{
    t_env *here;
    int i = 0;
    here = struktura->envp_list;

// printf("\n"); // ПОТОМ УДАЛИТЬ
    while (here)
	{
		i++;
        printf("%s=%s\n", here->key, here->value);
		here = here->next;
	}
// printf("\n"); // ПОТОМ УДАЛИТЬ
// printf("всего = %d\n", i);

    struktura->command_result = 0;
    
    exit(0);
}

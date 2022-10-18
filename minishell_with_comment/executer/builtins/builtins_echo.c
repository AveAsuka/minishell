#include "minishell.h"

/*  1) echo с опцией -n;
Команда echo - это не системная утилита, у нее нет исполняемого файла. 
Она существует только внутри интерпретатора Bash. 
Синтаксис команды echo linux очень прост:
$ echo опции строка

-n - не выводить перевод строки;

Тут всё кажется простым - просто выписываем через "write (1, ?, ?)" всё что подали
в строку, если же встретили '-n', то отрубаем его
немного непонятно как реализовать формат '$CAPS' - он наверно должен как-то 
фиксироваться в нашей stroka */
void built_echo(t_info *struktura, char **stroka)
{
    int flag; // если с '-n', то 0, если БЕЗ, то другое
    int i;

    if (stroka[0] && stroka[1])
    {
    // возможно не так заносится нужное значение
        flag = ft_strncmp_mod("-n", stroka[1], 2);
// printf("flag = %d\n", flag);
        if (flag == 1)
            i = 2;
        else // (flag == 0)
            i = 1;

        while(stroka[i])
        {
            ft_putstr_fd(stroka[i], 1);
            if (stroka[i + 1])
                ft_putstr_fd(" ", 1);
            i++;
        }

        if (flag == 0)
            write(1, "\n", 1);

        struktura->command_result = 0;
    }
    
    exit(0); // выход в наш(!) терминал
}

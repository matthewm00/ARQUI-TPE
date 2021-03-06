#include <shell.h>

static char userName[USER_SIZE] = "ArquiUser";

void initialize()
{

    printf("\n\tArquitectura de Computadoras - 2Q 2021\n\n");
    printf("\n\tPara mas informacion sobre los funcionalidades del programa utilice el comando /help\n\n\n");
    getCommandAndRun();
}

static int readAux(char *userInput, char *command, char argv[MAX_ARGUMENTS][BUFFER_SIZE])
{
    int argc = 0;
    int i = 0;
    for (i = 0; userInput[i] != 0 && userInput[i] != ' '; i++)
    {
        command[i] = userInput[i];
    }
    command[i] = 0;
    int argIdx = 0;

    for (int j = 0; j < MAX_ARGUMENTS; j++)
    {
        argv[j][0] = 0;
    }

    while (userInput[i] != 0 && argc < MAX_ARGUMENTS)
    {
        i++;
        argIdx = 0;
        for (; userInput[i] != ' ' && userInput[i] != 0; i++, argIdx++)
        {
            argv[argc][argIdx] = userInput[i];
        }
        argv[argc][argIdx] = 0;
        argc++;
    }
    if (argc == MAX_ARGUMENTS && userInput[i] != 0)
        return -1;
    return argc;
}
void printUser()
{
    int len = strlen(userName);
    len += 4;
    printf("$ ");
    printf("%s", userName);
    printf(" > ");
}
void getCommandAndRun()
{
    char command[BUFFER_SIZE] = {0};
    char argv[MAX_ARGUMENTS][BUFFER_SIZE];
    char userInput[BUFFER_SIZE] = {0};
    int argc = 0;

    while (1)
    {
        printUser();

        userInput[0] = 0;

        scanf("%s", userInput);

        argc = readAux(userInput, command, argv);

        if (argc == -1)
        {
            printf("\nIngreso argumentos de mas.\nLa maxima cantidad de argumentos permitida es: %d.\n\n", MAX_ARGUMENTS);
        }
        else if (strcmp("/help", command) == 0)
        {
            help(argc, argv);
        }
        else if (strcmp("/inforeg", command) == 0)
        {
            getInfoReg(argc, argv);
        }
        else if (strcmp("/clear", command) == 0)
        {
            clear(argc, argv);
        }
        else if (strcmp("/exit", command) == 0)
        {
            exit(argc, argv);
            // otra forma de hacer el exit seria con un flag de exit = 0
            // while (!exit), y dentro de esto se corre todo el codigo
            // entonces no haria falta una funcion exit.
            // Solo hacer:
            //              printf("Hasta a la vista bby");
            //              exit = 1;
        }
        else if (strcmp("/opcode", command) == 0)
        {
            opCode(argc, argv);
        }
        else if (strcmp("/divzero", command) == 0)
        {
            divZero(argc, argv);
        }
        else if (strcmp("/date&time", command) == 0)
        {
            getCurrentDayTime(argc, argv);
        }
        else if (strcmp("/printmem", command) == 0)
        {
            getMem(argc, argv);
        }
        // else if (strcmp("/games", command) == 0)
        // {
        //     games(argc, argv, 1);
        // }
        else
        {
            printf("\nComando invalido: use /help\n\n");
        }
    }
    return;
}

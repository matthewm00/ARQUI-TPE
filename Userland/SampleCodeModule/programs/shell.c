#include <shell.h>
#include <libc.h>
#include <commands.h>
#include <stdint.h>

void initialize()
{
    printf("\n  Utilice el comando help para obtener el manual de usuario.\n\n\n\n");
    shellExecute();
}

static int getCommandArgs(char *userInput, char *command, char argv[MAX_ARGUMENTS][BUFFER_SIZE])
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

void shellExecute()
{
    char command[BUFFER_SIZE] = {0};
    char argv[MAX_ARGUMENTS][BUFFER_SIZE];
    char userInput[BUFFER_SIZE] = {0};
    int argc = 0;

    while (1)
    {
        printf("$> ");

        userInput[0] = 0;

        scanf("%s", userInput);

        argc = getCommandArgs(userInput, command, argv);

        if (argc == -1)
        {
            printf("\nIngreso argumentos de mas.\nLa maxima cantidad de argumentos permitida es: %d.\n\n", MAX_ARGUMENTS);
        }
        else if (strcmp("help", command) == 0)
        {
            help(argc, argv);
        }
        else if (strcmp("inforeg", command) == 0)
        {
            getInfoReg(argc, argv);
        }
        else if (strcmp("clear", command) == 0)
        {
            clear(argc, argv);
        }
        else if (strcmp("exit", command) == 0)
        {
            exit(argc, argv);
        }
        else if (strcmp("opcode", command) == 0)
        {
            opCode(argc, argv);
        }
        else if (strcmp("date", command) == 0)
        {
            getCurrentDayTime(argc, argv);
        }
        else if (strcmp("printmem", command) == 0)
        {
            getMem(argc, argv);
        }
        else if (strcmp("divzero", command) == 0)
        {
            divZero(argc, argv);
        }
        else if (strcmp("games", command) == 0)
        {
            games(argc, argv);
        }
        else
        {
            printf("\nComando invalido: use help\n\n");
        }
    }
    return;
}

// callmemStatus "mem", "Imprime el estado de la memoria"
//     callStatus, "sem", "Imprime el estado de los semaforos"
//     callProcessStatus, "ps", "Imprime el estado de los procesos"
//     callSetPriority, "nice", "Cambia la prioridad de un proceso"
//     callKillProcess, "kill", "Mata un proceso"
//     callBlockProcess, "block", "Bloquea un proceso"
//     callUnblockProcess, "unblock", "Desbloquea un proceso"
//     cat, "cat", "Imprime el texto ingresado luego de   ejecutar el comando"
//     loop, "loop", "Imprime un saludo cada 3 segundos"
//     callPipeStatus, "pipe", "Imprime el estado de los pipes"
//     filter "filter"
//      "Filtra las vocales del texto ingresadoluego de ejecutar el comando"
//     wc, "wc"
//      "Cantidad de lineas del texto ingresadoluego de ejecutar el comando"
//     phylo, "phylo", "Problema de filosofos comensales"
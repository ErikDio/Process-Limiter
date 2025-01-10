#include <windows.h>
#include <stdio.h>
#include <TlHelp32.h>
#include <stdbool.h>
#include "gerenciador_processos.h"
bool DEBUG = false;

int Iniciar(int argc, char **argv) {
    for(int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-debug") == 0) {
            DEBUG = true;
        }
    }
    
    DWORD attribs = GetFileAttributes("./config.cfg");
    if(attribs == INVALID_FILE_ATTRIBUTES) {
        printf("Número de telas: ");
        int telas;
        scanf("%d", &telas);
        FILE *arq = fopen("./config.cfg", "w");
        if(arq == NULL) {
            printf("Erro ao criar arquivo de configuração\n");
            return -1;
        } else {
            fprintf(arq, "%d", telas);
            fclose(arq);
            SetFileAttributes("./config.cfg", FILE_ATTRIBUTE_READONLY);
            SetFileAttributes("./config.cfg", FILE_ATTRIBUTE_HIDDEN);
            system("icacls \"./config.cfg\" /inheritance:r /grant:r \"Users:R\" /grant:r \"Administrators:F\"");
            return telas;
        }
    } else {
        FILE *arq = fopen("./config.cfg", "r");
        if(arq == NULL) {
            printf("Erro ao abrir arquivo de configuração\n");
            return -1;
        } else {
            char buffer[10];
            if (fgets(buffer, sizeof(buffer), arq) != NULL) {
                int telas = atoi(buffer);
                fclose(arq);
                return telas;
            } else {
                printf("Erro ao ler arquivo de configuração\n");
                fclose(arq);
                return -1;
            }
        }
    }
}

int main(int argc, char **argv) {
    int telas = Iniciar(argc, argv);
    if(telas <= 0) {
        printf("Erro ao iniciar o programa\n");
        return 0;
    }
    Processos(DEBUG, telas);
    getchar();
    return 0;
}
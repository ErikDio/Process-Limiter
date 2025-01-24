#include <windows.h>
#include <stdio.h>
#include <TlHelp32.h>
#include <stdbool.h>
#include <locale.h>
#include "gerenciador_processos.h"
bool DEBUG = false;

void saveConfig(int telas, const char* processo) {
    FILE *file = fopen("config.cfg", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de configuração\n");
        return;
    }
    fprintf(file, "%d|%s\n", telas, processo);
    fclose(file);
}

void loadConfig(int *telas, char* processo) {
    FILE *file = fopen("config.cfg", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de configuração\n");
        return;
    }
    fscanf(file, "%d|%s", telas, processo);
    fclose(file);
}

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
        printf("Insira o nome do processo alvo (ex: notepad.exe): ");
        char processo[256];
        scanf("%s", processo);
        saveConfig(telas, processo);
        DWORD newAttribs = attribs | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN;
        if (!SetFileAttributes("./config.cfg", newAttribs)) {
            printf("Failed to set read-only attribute. Error: %lu\n", GetLastError());
        }
        return telas;
    } else {
        return 1;
    }
}

int main(int argc, char **argv) {
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "pt_PT.UTF-8");
    char processo[256];
    int telas = 0;
    int status = Iniciar(argc, argv);
    if(status <= 0) {
        printf("Erro ao iniciar o programa\n");
        return 0;
    }
    HWND consoleWindow = GetConsoleWindow();
    if (!DEBUG) {
        ShowWindow(consoleWindow, SW_HIDE);
    } else {
        ShowWindow(consoleWindow, SW_SHOW);
        printf("Debug mode is ON\n");
    }
    loadConfig(&telas, processo);
    Processos(DEBUG, telas, processo);
    if(DEBUG){
        getchar();
    }
    return 0;
}
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<windows.h>

void Processos(bool DEBUG, int telas, char processo[256]) {
    if (DEBUG) {
        printf("Debug mode is ON\n");
    }
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    int *telas_permitidas = NULL;
    int *processos_programa = NULL;
    int count = 0;
    int capacity = 10;
    if(DEBUG){
        printf("%d", telas);
    }
    telas_permitidas = (int *) calloc (telas, sizeof(int));
    processos_programa = (int *) calloc (capacity, sizeof(int));
    int nloops = 0;
    while (true) {
        hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if(hProcessSnap == INVALID_HANDLE_VALUE) {
            if(DEBUG){
                printf("Erro ao criar snapshot dos processos\n");
            }
            free(telas_permitidas);
            free(processos_programa);
            return;
        }
        pe32.dwSize = sizeof(PROCESSENTRY32);
        if(!Process32First(hProcessSnap, &pe32)) {
            if(DEBUG){
                printf("Erro ao obter a primeira entrada do snapshot\n");
            }
            CloseHandle(hProcessSnap);
            free(telas_permitidas);
            free(processos_programa);
            return;
        } do {
            //printf("Nome do processo: %-30sID: %d\n", pe32.szExeFile, pe32.th32ProcessID);
            if(strcmp(pe32.szExeFile, processo) == 0) {
                processos_programa[count] = pe32.th32ProcessID;
                if(DEBUG){
                    printf("Processo %s encontrado com ID: %d\n", processo, processos_programa[count]);
                }
                count++;
                if(count == capacity) {
                    capacity += 10;
                    processos_programa = (int *) realloc(processos_programa, capacity * sizeof(int));
                }
            }
        } while(Process32Next(hProcessSnap, &pe32));


    for(int i = 0; i < capacity; i++) {
        if(processos_programa[i] == 0) {
            break;
        }
        bool continuar = false;
        int disponivel = -1;
        bool existe = false;
        for(int j = 0; j < telas; j++) {
            if(telas_permitidas[j] == processos_programa[i]) {
                existe = true;
                break;
            } else if(telas_permitidas[j] != 0) {
                continue;
            } else {
                disponivel = j;
                continue;
            }
        } if(existe == false && disponivel != -1) {
            telas_permitidas[disponivel] = processos_programa[i];
        } if(continuar) {
            continue;
        } else {
            for(int j = 0; j < telas; j++) {
                if(processos_programa[i] == telas_permitidas[j]) {
                    continuar = true;
                    break;
                } else {
                    continue;
                }
            }
        } if(continuar) {
            continue;
        } else {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processos_programa[i]);
            if(hProcess == NULL) {
                if(DEBUG){
                    printf("Erro ao terminar o processo %d\n", processos_programa[i]);
                }
            } else {
                if(TerminateProcess(hProcess, 0)) {
                    if(DEBUG){
                        printf("Processo %d finalizado com sucesso\n", processos_programa[i]);
                    }
                } else {
                    if(DEBUG){
                        printf("Erro ao finalizar o processo %d\n", processos_programa[i]);
                    }
                }
                CloseHandle(hProcess);
            }
        }
    } for (int i = 0; i < telas; i++) {
            if(telas_permitidas[i] != 0) {
                bool existe = false;
                for (int j = 0; j < count; j++) {
                    if(telas_permitidas[i] == processos_programa[j]) {
                        existe = true;
                        break;
                    } 
                } if(existe) {
                    if(DEBUG){
                        printf("PID %d: %d\n", i, telas_permitidas[i]);
                    }
                } else {
                    telas_permitidas[i] = 0;
                }
            }
        }
        CloseHandle(hProcessSnap);
        free(processos_programa);
        capacity = 10;
        count = 0;
        processos_programa = (int *) calloc (capacity, sizeof(int));
        if(DEBUG) {
            nloops++;
            if(nloops == 100) {
                break;
            }
            Sleep(2000);
        } else {
            Sleep(1000);
        }
    }
    free(telas_permitidas);
    free(processos_programa);
    return;
}
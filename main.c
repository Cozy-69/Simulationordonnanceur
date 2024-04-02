#include <stdio.h>
#include <stdlib.h>
#include "processus.h"

int main() {
    Processus* file_processus = NULL; // File des processus prêts
    int choix;
    int PID, temps_arrivee, temps_execution, quantum;

    do {
        printf("\nMenu:\n");
        printf("1. Saisir un processus\n");
        printf("2. Afficher les processus dans la file\n");
        printf("3. Appliquer l'algorithme FIFO\n");
        printf("4. Appliquer l'algorithme Round Robin\n");
        printf("0. Quitter\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("\nEntrez les informations sur le processus (PID, Temps d'Arrivee, Temps d'Execution) :\n");
                printf("PID: ");
                scanf("%d", &PID);
                printf("Temps d'Arrivee: ");
                scanf("%d", &temps_arrivee);
                printf("Temps d'Execution: ");
                scanf("%d", &temps_execution);
                ajouterProcessus(&file_processus, saisirProcessus(PID, temps_arrivee, temps_execution));
                break;
            case 2:
                printf("\nProcessus dans la file :\n");
                affichfile(file_processus);
                break;
            case 3:
                triProcessus(&file_processus);
                fifoProcessus(&file_processus);
                diag_gantt(file_processus);
                break;
            case 4:
                printf("\nEntrez le quantum pour Round Robin : ");
                scanf("%d", &quantum);
                triProcessus(&file_processus);
                rrProcessus(&file_processus, quantum);
                diag_gantt(file_processus);
                break;
            case 0:
                printf("Fin du programme.\n");
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    } while (choix != 0);

    // Libérer la mémoire allouée pour les processus restants dans la file
    Processus* temp;
    while (file_processus != NULL) {
        temp = file_processus;
        file_processus = file_processus->suivant;
        detruireProcessus(temp);
    }

    return 0;
}

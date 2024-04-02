#include <stdio.h>
#include <stdlib.h>
#include "processus.h"

// Fonction pour créer un nouveau processus
Processus* saisirProcessus(int PID, int temps_arrivee, int temps_execution) {
    Processus* nouveau_processus = (Processus*)malloc(sizeof(Processus));
    if (nouveau_processus == NULL) {
        printf("Erreur lors de l'allocation memoire pour le nouveau processus.\n");
        exit(1);
    }
    nouveau_processus->PID = PID;
    nouveau_processus->temps_arrivee = temps_arrivee;
    nouveau_processus->temps_execution = temps_execution;
    nouveau_processus->temps_rotation = 0;
    nouveau_processus->temps_attente = 0;
    nouveau_processus->temps_fin_execution = 0;
    nouveau_processus->suivant = NULL;
    return nouveau_processus;
}

// Fonction pour afficher les informations d'un processus
void affichProcessus(Processus* processus) {
    printf("PID: %d, Temps Arrivee: %d, Temps Execution: %d, Temps Rotation: %d, Temps Attente: %d, Temps Fin Execution: %d\n",
           processus->PID, processus->temps_arrivee, processus->temps_execution, processus->temps_rotation,
           processus->temps_attente, processus->temps_fin_execution);
}

// Fonction pour initialiser la file des processus prêts à NULL
void initfile(Processus** tete) {
    *tete = NULL;
}

// Fonction pour ajouter un processus à la fin de la liste
void ajouterProcessus(Processus** tete, Processus* nouveau_processus) {
    if (*tete == NULL) {
        *tete = nouveau_processus;
    } else {
        Processus* temp = *tete;
        while (temp->suivant != NULL) {
            temp = temp->suivant;
        }
        temp->suivant = nouveau_processus;
    }
}

// Fonction pour afficher tous les processus de la liste
void affichfile(Processus* tete) {
    Processus* temp = tete;
    while (temp != NULL) {
        affichProcessus(temp);
        temp = temp->suivant;
    }
}

// Fonction pour trier les processus selon leur temps d'arrivée
void triProcessus(Processus** tete) {
    Processus *temp1, *temp2;
    int temp_pid, temp_arrivee, temp_execution;
    if (*tete == NULL)
        return;
    for (temp1 = *tete; temp1->suivant != NULL; temp1 = temp1->suivant) {
        for (temp2 = temp1->suivant; temp2 != NULL; temp2 = temp2->suivant) {
            if (temp1->temps_arrivee > temp2->temps_arrivee) {
                // Échanger les données des processus
                temp_pid = temp1->PID;
                temp_arrivee = temp1->temps_arrivee;
                temp_execution = temp1->temps_execution;
                temp1->PID = temp2->PID;
                temp1->temps_arrivee = temp2->temps_arrivee;
                temp1->temps_execution = temp2->temps_execution;
                temp2->PID = temp_pid;
                temp2->temps_arrivee = temp_arrivee;
                temp2->temps_execution = temp_execution;
            }
        }
    }
}

// Fonction pour appliquer l'algorithme FIFO (First Come First Serve)
void fifoProcessus(Processus** tete) {
    Processus* temp = *tete;
    if (temp == NULL) {
        printf("Aucun processus dans la file.\n");
        return;
    }
    printf("Algorithme de Planification FIFO (FCFS):\n");
    while (temp != NULL) {
        temp->temps_rotation = temp->temps_execution;
        temp->temps_attente = 0;
        temp->temps_fin_execution = temp->temps_arrivee + temp->temps_rotation;
        affichProcessus(temp);
        temp = temp->suivant;
    }
}

// Fonction pour appliquer l'algorithme Round Robin
void rrProcessus(Processus** tete, int quantum) {
    if (*tete == NULL) {
        printf("Aucun processus dans la file.\n");
        return;
    }

    printf("Algorithme de Planification Round Robin (RR) avec quantum %d:\n", quantum);

    Processus* current_process = *tete;
    while (current_process != NULL) {
        if (current_process->temps_execution <= quantum) {
            // Si le temps d'exécution du processus est inférieur ou égal au quantum
            // Met à jour les temps
            current_process->temps_rotation += current_process->temps_execution;
            current_process->temps_attente = 0;
            current_process->temps_fin_execution = current_process->temps_arrivee + current_process->temps_rotation;
            // Affiche le processus
            affichProcessus(current_process);
            // Passe au processus suivant
            Processus* next_process = current_process->suivant;
            // Supprime le processus courant de la liste
            free(current_process);
            // Affecte le processus suivant comme le processus courant
            current_process = next_process;
        } else {
            // Si le temps d'exécution du processus est supérieur au quantum
            // Réduit le temps d'exécution du processus par le quantum
            current_process->temps_execution -= quantum;
            // Met à jour les temps
            current_process->temps_rotation += quantum;
            current_process->temps_fin_execution = current_process->temps_arrivee + current_process->temps_rotation;
            // Affiche le processus
            affichProcessus(current_process);
            // Passe au processus suivant
            Processus* next_process = current_process->suivant;
            // Déplace le processus courant à la fin de la file
            ajouterProcessus(tete, current_process);
            // Affecte le processus suivant comme le processus courant
            current_process = next_process;
        }
    }
}


// Fonction pour afficher le diagramme de Gantt
void diag_gantt(Processus* tete) {
    printf("Diagramme de Gantt:\n");
    Processus* temp = tete;
    while (temp != NULL) {
        printf("| P%d ", temp->PID);
        temp = temp->suivant;
    }
    printf("|\n");
}

// Fonction pour libérer la mémoire allouée pour un processus
void detruireProcessus(Processus* processus) {
    free(processus);
}
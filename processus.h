#ifndef PROCESSUS_H
#define PROCESSUS_H

// Structure de données pour un processus
typedef struct Processus {
    int PID; // Identifiant du processus
    int temps_arrivee; // Temps d'arrivée du processus
    int temps_execution; // Temps d'exécution du processus
    int temps_rotation; // Temps de rotation du processus
    int temps_attente; // Temps d'attente du processus
    int temps_fin_execution; // Temps de fin d'exécution du processus
    struct Processus* suivant; // Pointeur vers le processus suivant dans la file
} Processus;

// Prototypes des fonctions
Processus* saisirProcessus(int PID, int temps_arrivee, int temps_execution);
void affichProcessus(Processus* processus);
void initfile(Processus** tete);
void ajouterProcessus(Processus** tete, Processus* nouveau_processus);
void affichfile(Processus* tete);
void triProcessus(Processus** tete);
void fifoProcessus(Processus** tete);
void rrProcessus(Processus** tete, int quantum);
void diag_gantt(Processus* tete);
void detruireProcessus(Processus* processus);

#endif /* PROCESSUS_H */

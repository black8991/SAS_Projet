#include <stdio.h>
#include <stdlib.h>
#include<time.h>
typedef struct Date {
    int year, month, day;
} Date;

typedef struct Tache {
    int id;
    char Description[100];
    char tache[25];
    Date debut;
    Date dedline;
    int status;
} Tache;


void Trier_par_deadline(Tache *tach, int taille);
void ajout(Tache **tach, int *taille);
void ajoutplus(Tache **tach, int *taille, int match);
void afficher(Tache *tach);
void afficherplus(Tache *tach, int taille);
void tri_special(Tache *tach,int taille);
void mod_description(Tache **tach, int index);
void mod_status(Tache *tach, int index);

void Trier_par_deadline(Tache *tach, int taille) {
    Tache temp;
    int i, j;
    for (i = 0; i < taille - 1; i++) {
        for (j = i + 1; j < taille; j++) {
            if (tach[i].debut.year > tach[j].debut.year) {
                temp = tach[i];
                tach[i] = tach[j];
                tach[j] = temp;
            } else if (tach[i].debut.year == tach[j].debut.year) {
                if (tach[i].debut.month > tach[j].debut.month) {
                    temp = tach[i];
                    tach[i] = tach[j];
                    tach[j] = temp;
                } else if (tach[i].debut.month == tach[j].debut.month) {
                    if (tach[i].debut.day > tach[j].debut.day) {
                        temp = tach[i];
                        tach[i] = tach[j];
                        tach[j] = temp;
                    }
                }
            }
        }
    }
}

void ajout(Tache **tach, int *taille) {
    (*taille)++;
    if (*taille == 1) {
        *tach = (Tache *)malloc(sizeof(Tache));
    } else {
        *tach = (Tache *)realloc(*tach, *taille * sizeof(Tache));
    }

    Tache *newtach = *tach;
      tach += (*taille - 1);

     newtach->id = *taille - 1;

    printf("\t tache: ");
    scanf("%s", newtach->tache);
    printf("\t Description: ");
    scanf(" %[^\n]s", newtach->Description);
    printf("Enter date debut:\n");
    printf("Day: ");
    scanf("%d", &newtach->debut.day);
    printf("\t Month: ");
    scanf("%d", &newtach->debut.month);
    printf("\t Year: ");
    scanf("%d", &newtach->debut.year);
    printf("\t Enter dedline date:\n");
    printf("\t Day: ");
    scanf("%d", &newtach->dedline.day);
    printf("\t Month: ");
    scanf("%d", &newtach->dedline.month);
    printf("\t   Year: ");
    scanf("%d", &newtach->dedline.year);

    printf("choix 1 ou 2 ou 3:\n"
           "\t [1] a realiser\n"
           "\t [2] en cours de realisation\n"
           "\t [3] finalisee\n");

    int i;
    printf("number of ch");
    scanf("%d", &i);

    if (i == 1) {
        newtach->status = 1;
    } else if (i == 2) {
        newtach->status = 2;
    } else if (i == 3) {
        newtach->status = 3;
    } else {
        printf("Invalid choice\n");
        newtach->status = -1;
    }

    printf("\nTache added to stock successfully!\n");
}

void ajoutplus(Tache **tach, int *taille, int match) {
    for (int i = 0; i < match; i++) {
        ajout(tach, taille);
    }
}

void afficher(Tache *tach) {
 //   Tache *tach = *tache;
 printf("\n===================================================\n");
        printf("\n\tId:%d", tach->id);
        printf("\n\tTache  : %s", tach->tache);
        printf("\n\tDescription:%s", tach->Description);
        printf("\n\tdate debut :%d/%d/%d", tach->debut.day, tach->debut.month, tach->debut.year);
        printf("\n\tdate debut :%d/%d/%d", tach->dedline.day, tach->dedline.month, tach->dedline.year);
        if (tach->status == 1) {
            printf("\n\tStatus:%s", "a realiser\n");
        } else if (tach->status == 2) {
            printf("\n\tStatus:%s", "en cours de realisation.\n");
        } else if (tach->status == 3) {
            printf("\n\tStatus:%s", "finalisee.\n");
     }
        printf("\n===================================================\n");
}
void afficherplus(Tache *tach, int taille) {
    for (int i = 0; i < taille; i++) {
        printf("Task %d:\n", i + 1);
        afficher(tach);
        printf("\n");
    }
}

void mod_description(Tache **tach, int index) {
    printf("new description:");
    scanf(" %[^\n]s", (*tach)[index].Description);
}

void mod_status(Tache *tach, int index) {
    printf("new status:"
           "[1] a realiser\n"
           "[2] en cours de realisation\n"
           "[3] finalisee\n");

    int i;
    printf("number of status");
    scanf("%d", &i);
    if (i == 1) {
        tach[index].status = 1;
    } else if (i == 2) {
        tach[index].status = 2;
    } else if (i == 3) {
        tach[index].status = 3;
    }
}

int main() {
    int taille = 0;
    Tache *taches = NULL;
    int choix, match;
    int  index;
    do {
        printf("Menu:\n"
                "[1] Ajouter une tache\n"
                "[2] Ajouter plusieurs taches\n"
                "[3] Afficher les taches\n"
                "[4]\n"
                "[5]\n"
                "[6]\n"
                "[7]\n"
                "[0] Quitter\n"
                "Votre choix: ");

        if (scanf("%d", &choix) != 1) {
            printf("Invalid input.\n");
            break;
        }

        switch (choix) {
            case 1:
                ajout(&taches, &taille);
                break;
            case 2:
                printf("Combien de taches souhaitez-vous ajouter ? ");
                scanf("%d", &match);
                ajoutplus(&taches, &taille, match);
                break;
            case 3:
                afficherplus(taches, taille);
                break;
            case 4:
                printf("Enter the index of the task to modify: ");
                scanf("%d", &index);
                mod_description(&taches, index);
                mod_status(taches, index);
                break;
            case 5:
                tri_special(taches, taille);
                break;
            case 6:
                break;
            case 7:
                break;
            case 0:
                printf("Quitting...\n");
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }
    } while (choix != 0);

    free(taches);

    return 0;
}

void tri_special(Tache *tach,int taille) {
  time_t current_time;
  struct tm *time_info;
  time(&current_time);
  time_info = localtime(&current_time);
  int day = time_info->tm_mday;
  int month = time_info->tm_mon + 1;
  int year = time_info->tm_year + 1900;
  int var1 = year * 360 + month * 30 + day;

  for (int i; i < taille; i++) {
    int var2 = (tach[i].dedline.day) +
      (tach[i].dedline.month) * 30 +
               (tach[i].dedline.year) * 360;
    if (0 < var1 - var2 && var1 - var2 <= 3) {
    printf("the task that lest[0,3] for the and.");
      afficher(tach);
    }
  }

}







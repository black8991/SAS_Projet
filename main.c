#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void functions();
void ajout(Tache **tach, int *taille);
void ajoutplus(Tache **tach, int *taille, int match);
void afficher(Tache *tach);
void afficherplus(Tache *tach, int taille);
void Trier_par_deadline(Tache *tach, int taille);
void tri_special(Tache *tach, int taille);
void tri_paralpha(Tache *tach, int taille);
void mod_description(Tache *tach, int index);
void mod_status(Tache *tach, int index);
void mod_deadline(Tache *tach);
void delete_tach(Tache *tach, int taille, int id);
void search_id(Tache *tach, int taille, int id);
void search_Titre(Tache *tach, int taille,char *tacheRe);
void Statistiques(Tache *tach, int taille);
void case3function(Tache *taches, int taille);
void case4function(Tache *taches, int taille);
void case6function(Tache *taches, int taille);


void ajout(Tache **tach, int *taille) {
  (*taille)++;
  if (*taille == 1) {
    *tach = (Tache *)malloc(sizeof(Tache));
  } else {
    *tach = (Tache *)realloc(*tach, *taille * sizeof(Tache));
  }

  if (*tach == NULL) {
    printf("Memory allocation failed.\n");
  }

  Tache *newtach = *tach + (*taille - 1);

  newtach->id = *taille - 1;

  printf("\n\t Tache: ");
  scanf("%s", newtach->tache);
  printf("\n\t Description: ");
  scanf(" %[^\n]s", newtach->Description);
  /*  printf("\n Enter date debut->\n");
    printf("\n\t\t Day: ");
    scanf("%d", &newtach->debut.day);
    printf("\n\t\t Month: ");
    scanf("%d", &newtach->debut.month);
    printf("\n\t\t Year: ");
    scanf("%d", &newtach->debut.year);*/
  printf("\n  Enter dedline date->\n");
  printf("\n\t\t Day: ");
  scanf("%d", &newtach->dedline.day);
  printf("\n\t\t Month: ");
  scanf("%d", &newtach->dedline.month);
  printf("\n\t\t Year: ");
  scanf("%d", &newtach->dedline.year);

  printf("\n______________status________________\n"
         "\n\t [1] a realiser\n"
         "\t [2] en cours de realisation\n"
         "\t [3] finalisee\n"
         "______________________________________\n");

  int i;
  printf("Number of status: ");
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
  printf("\n\tId:%d", tach->id);
  printf("\n\tTache  : %s", tach->tache);
  printf("\n\tDescription:%s", tach->Description);
  printf("\n\tDate debut :%d/%d/%d", tach->debut.day, tach->debut.month,
         tach->debut.year);
  printf("\n\tDate deadline :%d/%d/%d", tach->dedline.day, tach->dedline.month,
         tach->dedline.year);
  if (tach->status == 1) {
    printf("\n\ta realiser\n");
  } else if (tach->status == 2) {
    printf("\n\tStatus:%s", "en cours de realisation.\n");
  } else if (tach->status == 3) {
    printf("\n\tStatus:%s", "finalisee.\n");
  }
  printf("\n______________________________________\n");
}

void afficherplus(Tache *tach, int taille) {
  for (int i = 0; i < taille; i++) {
    printf("Task %d:\n", i + 1);
    afficher(&tach[i]);
    printf("\n");
  }
}

void Trier_par_deadline(Tache *tach, int taille) {
  Tache temp;
  for (int i = 0; i < taille - 1; i++) {
    for (int j = i + 1; j < taille; j++) {
      Date date1 = tach[i].debut;
      Date date2 = tach[j].debut;
      if (date1.year > date2.year ||
          (date1.year == date2.year && date1.month > date2.month) ||
          (date1.year == date2.year && date1.month == date2.month &&
           date1.day > date2.day)) {
        temp = tach[i];
        tach[i] = tach[j];
        tach[j] = temp;
      }
    }
  }
}

void tri_paralpha(Tache *tach, int taille) {
  Tache temp;
  for (int i = 0; i < taille - 1; i++) {
    for (int j = i + 1; j < taille; j++) {
      if (strcmp(tach[i].tache, tach[i + 1].tache) == 1) {
        temp = tach[i];
        tach[i] = tach[j];
        tach[j] = temp;
      }
    }
  }
}

void tri_special(Tache *tach, int taille) {
  int var1 = match_days();
  for (int i = 0; i < taille; i++) {
    int var2 = (tach[i].dedline.day) + (tach[i].dedline.month) * 30 +
               (tach[i].dedline.year) * 360;
    if (0 < var2 - var1 && var2 - var1 <= 3) {
      printf("The task that left [0,3] days for the deadline:\n");
      afficher(&tach[i]);
      break;
    }
  }
}

void mod_description(Tache *tach, int index) {
  printf("\tNew description:");
  scanf(" %[^\n]s", tach[index].Description);
}

void mod_status(Tache *tach, int index) {
  printf("New status:\n"
         "[1] a realiser\n"
         "[2] en cours de realisation\n"
         "[3] finalisee\n");

  int i;
  printf("\tNumber of status: ");
  scanf("%d", &i);
  if (i == 1) {
    tach[index].status = 1;
  } else if (i == 2) {
    tach[index].status = 2;
  } else if (i == 3) {
    tach[index].status = 3;
  }
}

void mod_deadline(Tache *tach) {
  printf("\t Enter new dedline date:\n");
  printf("\t   Day: ");
  scanf("%d", &tach->dedline.day);
  printf("\t   Month: ");
  scanf("%d", &tach->dedline.month);
  printf("\t   Year: ");
  scanf("%d", &tach->dedline.year);
}

void delete_tach(Tache *tach, int taille, int id) {
  int i, j;
  for (int i = 0; i < taille; i++) {
    if (tach[i].id == id) {
      for (j = i; j < taille - i; j++) {
        tach[j] = tach[j + 1];
      }
    }
  }
}

void search_id(Tache *tach, int taille, int id) {
  for (int i = 0; i < taille; i++) {
    if (tach[i].id == id) {
      afficher(&tach[i]);
    }
  }
}

void search_Titre(Tache *tach, int taille,char *tacheRe) {
    for (int i = 0; i < taille; i++) {
        if (strcmp(tach[i].tache,tacheRe) == 0) {

            afficher(&tach[i]);
        }
    }
}

void Statistiques(Tache *tach, int taille) {
  int compl = 0, incompl = 0, var, var1;
  var = match_days();
  for (int i = 0; i < taille; i++) {
    if (tach[i].status == 3) {
      compl ++;
    } else {
      incompl++;
    }
    printf("");
    for (int i = 0; i < taille; i++) {
      var1 = (tach[i].dedline.day) + (tach[i].dedline.month) * 30 +
             (tach[i].dedline.year) * 360;
      printf("tache %d: %d jour ", i + 1, (var1 - var));
    }
  }
}



int main() {

  int taille = 0;
  Tache *taches = NULL;
  char titre[25];
  int choix, match, index, id;

  do {
    functions();
   if (scanf("%d", &choix) != 1) {
      printf("Invalid input.\n");
      break;
    }

    switch (choix) {
    case 1:
      system("cls");
      ajout(&taches, &taille);
      break;
    case 2:
      system("cls");
      printf("Combien de taches souhaitez-vous ajouter ? ");
      scanf("%d", &match);
      ajoutplus(&taches, &taille, match);
      break;
    case 3:
      system("cls");
      case3function(taches, taille);

      break;
    case 4:
      system("cls");
      case4function(taches, taille);
      break;
    case 5:
     system("cls");
      printf("Entrez le nombre de la tâche à Supprimer:");
      scanf("%d", &id);
      delete_tach(taches, taille, id);
      break;
    case 6:
      system("cls");
      case6function(taches, taille);
      break;
    case 7:
        system("cls");
      Statistiques(taches, taille);
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


int match_days() {
  time_t current_time;
  struct tm *time_info;
  time(&current_time);
  time_info = localtime(&current_time);
  int day = time_info->tm_mday;
  int month = time_info->tm_mon + 1;
  int year = time_info->tm_year + 1900;
  return year * 360 + month * 30 + day;
}

void functions() {
  system("cls");
  printf("\n________________Functions:__________________\n\n"
         "\t[1] Ajouter une tache\n"
         "\t[2] Ajouter plusieurs taches\n"
         "\t[3] Afficher les taches\n"
         "\t[4] Modifier une tache\n"
         "\t[5] Supprimer une tache par identifiant\n"
         "\t[6] Rechercher les Taches \n"
         "\t[7] Statistiques \n"
         "\t[0] Quitter\n"
         "_____________________________________________\n"
         "Votre choix: ");
}

void case3function(Tache *taches, int taille) {
  printf("\n_________________________________________________________\n\n"
         "\t[1]Trier les tâches par ordre alphabétique\n"
         "\t[2]Trier les tâches par deadline\n"
         "\t[3]Afficher les tâches dont le deadline est\n\t   dans 3 jours ou "
         "moins\n"
         "_________________________________________________________\n");
  printf("Votre choix:");
  int choix;
  scanf("%d", &choix);
  if (choix == 1) {
    tri_paralpha(taches, taille);
    afficherplus(taches, taille);
  } else if (choix == 2) {
    Trier_par_deadline(taches, taille);
    printf("Tasks sorted by deadline.\n");
    afficherplus(taches, taille);
  } else if (choix == 3) {
    tri_special(taches, taille);
  }
}

void case4function(Tache *taches, int taille) {
  printf("\n______________________________________________\n\n"
         "\t[1] Modifier la description d'une tâche\n"
         "\t[2] Modifier le statut d’une tâche\n"
         "\t[3] Modifier le deadline d’une tâche\n"
         "______________________________________________\n");
  printf("Votre choix:");
  int choix, id;
  scanf("%d", &choix);
  printf("Entrez le nombre de la tâche à modifier :");
  scanf("%d", &id);
  if (choix == 1) {
    mod_description(taches, id);
  } else if (choix == 2) {
    mod_status(taches, id);
  } else if (choix == 3) {
    mod_deadline(taches);
  }
}

void case6function(Tache *taches, int taille) {
  int choix;
  int id;
  char tache[25];

  printf("\n______________________________________________\n\n"
         "\t[1] Rechercher une tâche par son Identifiant\n"
         "\t[2] Rechercher une tâche par son Titre\n"
         "______________________________________________\n");
  printf("Votre choix:");
  scanf("%d", &choix);

  if (choix == 1) {
    printf("Entrez l'ID de la tâche à rechercher: ");
    scanf("%d", &id);
    search_id(taches, taille, id);
  } else if (choix == 2) {

    printf("Entrez le titre de la tâche à rechercher: ");
    scanf("%s",tache);
    search_Titre(taches, taille, tache);
  } else {
    printf("Choix invalide. Veuillez choisir 1 ou 2.\n");
  }
}

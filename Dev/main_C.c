#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Nombre maximal de colonnes et de lignes pour un fichier CSV
#define MAX_ROWS 500
#define MAX_COLS 6

// Pour des questions pratique, sur chaque fichier CSV, la première ligne a été retirée manuellement.
// Fonction qui calcule la somme de des premiers éléments de chaque sous liste du dataset - Me permet de connaître le nombre d'individus présent dans un set
int somme_premiers(char liste[][6], int taille) {
    int somme = 0;
    for (int i = 0; i < taille; i++) {
        somme = somme + liste[i][0];
    }
    return somme;
}

// Fonction qui calcule le coût d'une famille
int fonction_cout_1famille(char L[6], int len_L) {
    int c = 0;
    if (L[len_L-1] == 2) {
        c = c + 50;
    } else if (L[len_L-1] == 3) {
        c = c + 50 + (9 * L[0]);
    } else if (L[len_L-1] == 4) {
        c = c + 100 + (9 * L[0]);
    } else if (L[len_L-1] == 5) {
        c = c + 200 + (9 * L[0]);
    } else {
        c = c + 0;
    }
    return c;
}

// Fonction qui calcule le coût total de toutes les familles
int cout_total(char M[][6], int len_M, int len_L) {
    int c = 0;
    for (int i = 0; i < len_M; i++) {
        c = c + fonction_cout_1famille(M[i], len_L);
    }
    return c;
}

// Fonction qui calcule les pénalités
double penalite(char liste_J[6], int len_liste_J) {
    double p = 0;
    for (int i = 0; i < len_liste_J; i++) {
        if (i <= 5) {
            p += pow((((double) liste_J[i] - 125) / 400) * (double) liste_J[i], fabs((double) liste_J[i] - (double) liste_J[i + 1]) / 50);
        } else {
            p += pow((((double) liste_J[i] - 125) / 400) * (double) liste_J[i], 1);
        }
    }
    return p;
}

// La fonction répartition est expliquée dans le rapport ci-joint avec le fichier C
int** repartition(int grande_liste[][6], int rows, int cols, int maximum_personnes, int num_present_each_day[7]) {
    int** P = (int**)malloc(rows * sizeof(int*));
    int** deux = (int**)malloc(rows * sizeof(int*));
    int** trois = (int**)malloc(rows * sizeof(int*));
    int** quatre = (int**)malloc(rows * sizeof(int*));
    int** cinq = (int**)malloc(rows * sizeof(int*));
    int** six = (int**)malloc(rows * sizeof(int*));

    int i, j;
    for (i = 0; i < rows; i++) {
        P[i] = (int*)malloc((cols+1) * sizeof(int));
        deux[i] = (int*)malloc(cols * sizeof(int));
        trois[i] = (int*)malloc(cols * sizeof(int));
        quatre[i] = (int*)malloc(cols * sizeof(int));
        cinq[i] = (int*)malloc(cols * sizeof(int));
        six[i] = (int*)malloc(cols * sizeof(int));
    }

    int p_index = 0;
    for (i = 0; i < rows; i++) {
        if (num_present_each_day[grande_liste[i][1]] < maximum_personnes) {
            grande_liste[i][cols] = 1;
            for (j = 0; j < cols+1; j++) {
                P[p_index][j] = grande_liste[i][j];
            }
            num_present_each_day[grande_liste[i][1]] += grande_liste[i][0];
            p_index++;
        }
        else {
            for (j = 0; j < cols; j++) {
                deux[p_index][j] = grande_liste[i][j];
            }
            p_index++;
        }
    }

    int deux_index = 0;
    for (i = 0; i < p_index; i++) {
        if (num_present_each_day[deux[i][2]] < maximum_personnes) {
            deux[i][cols] = 2;
            for (j = 0; j < cols+1; j++) {
                P[deux_index][j] = deux[i][j];
            }
            num_present_each_day[deux[i][2]] += deux[i][0];
            deux_index++;
        }
        else {
            for (j = 0; j < cols; j++) {
                trois[deux_index][j] = deux[i][j];
            }
            deux_index++;
        }
    }

    int trois_index = 0;
    for (i = 0; i < deux_index; i++) {
        if (num_present_each_day[trois[i][3]] < maximum_personnes) {
            trois[i][cols] = 3;
            for (j = 0; j < cols+1; j++) {
                P[trois_index][j] = trois[i][j];
            }
            num_present_each_day[trois[i][3]] += trois[i][0];
            trois_index++;
        }
        else {
            for (j = 0; j < cols; j++) {
                quatre[trois_index][j] = trois[i][j];
            }
            trois_index++;
        }
    }

    int quatre_index = 0;
    for (i = 0; i < trois_index; i++) {
        if (num_present_each_day[quatre[i][34]] < maximum_personnes)
        {
            quatre[i][cols] = 4;
            for (j = 0; j < cols+1; j++) {
                P[quatre_index][j] = quatre[i][j];
            }
            num_present_each_day[quatre[i][4]] += quatre[i][0];
            quatre_index++;
        }
        else {
            for (j = 0; j < cols; j++) {
                cinq[quatre_index][j] = quatre[i][j];
            }
            quatre_index++;
        }
    }

    int cinq_index = 0;
    for (i = 0; i < quatre_index; i++) {
        if (num_present_each_day[trois[i][3]] < maximum_personnes) {
            cinq[i][cols] = 5;
            for (j = 0; j < cols+1; j++) {
                P[cinq_index][j] = cinq[i][j];
            }
            num_present_each_day[cinq[i][5]] += cinq[i][0];
            cinq_index++;
        }
        else {
            for (j = 0; j < cols; j++) {
                six[cinq_index][j] = cinq[i][j];
            }
            cinq_index++;
        }
    }

    return P;
}


int main() {
    // Il ne faut pas oublier de changer l'adresse du fichier pour faire tourner le programme
    char filename[] = "emplacement_du_fichier";
    FILE *pF = fopen(filename, "r");
    char buffer[255];
    char *token;
    int row = 0, col = 0;
    double data[MAX_ROWS][MAX_COLS];

    if (pF == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    while(fgets(buffer, 255, pF) != NULL && row < MAX_ROWS)
    {
        col = 0;
        token = strtok(buffer, ";");
        while (token != NULL && col < MAX_COLS) {
            double value = atof(token);
            data[row][col] = value;
            token = strtok(NULL, ";");
            col++;
        }
        row++;
    }


    // Afficher la matrice à deux dimensions
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%f ", data[i][j]);
        }
        printf("\n");
    }

    int taille = sizeof(data) / sizeof(data[0]);
    int resultat = somme_premiers(data, taille);
    int population[7] = {0};
    int** repartition_set =  repartition(data, 500, 6, 270, population);
    int cout_tot = cout_total(repartition_set, 500, 6);
    double penalite_tot = penalite(population, 7);
    printf("La somme des premiers élements de chaque sous-liste est : %d\n", resultat);
    printf("Le coût total pour ce set est de : %d\n", cout_tot);
    printf("La pénalité total est de : %d\n", penalite_tot);
    fclose(pF);
    return 0;
}

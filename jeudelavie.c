#include <stdio.h>

void ini_plateau_de_jeu(int d, int tab[d][d]){ 
    for(int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++){
            scanf("%1d", &tab[i][j]); // %1d et pas %d pour pouvoir lire les tableaux en entree avec les valeurs de chaque cellules collés car ca ne marche pas avec %d si les cases du tableau sont collées 
        }
    }
}

void affichage_tab(int d, int tab[d][d]){ //affichage des tableaux apres chaque iteration
    for(int i = 0; i < d; i++){
        for (int j = 0; j < d; j++){
            printf("%d ", tab[i][j]); 
        }
        printf("\n");
    }
    printf("\n\n"); // revenir a la ligne deux fois pour afficher le prochain nouveau tableau apres avoir sauter une ligne 
}

int somme_cellules_voisines(int d, int tab[d][d], int x, int y){
    int somme = 0;
    for(int l = -1; l <= 1; l++){ // -1 à 1 car dans les 8 cellules vosiines, on fonctionne avecdes coordonnees et on remarque que pour les atteindre on monte ou on descend d'une case et on recule ou avance d'une case
        for(int c = -1; c <= 1; c++){
            if(l != 0 || c != 0){ //on verifie que l'on ne s'interesse pas à la cellule elle meme mais que aux voisines de celles-ci
                int voisine_x = x + l;
                int voisine_y = y + c;

                if(voisine_x >= 0 && voisine_x < d && voisine_y >= 0 && voisine_y < d){ // on verifie que l'on a pas depassé les limites (pour les cases aux bord notament)
                    somme += tab[voisine_x][voisine_y]; 
                }
            }   
        }
    }
    return somme;
}

void maj_tableau(int d, int tab[d][d], int b){ // maj = mise a jour / nouveau tableau apres 1 iteration
    int copie[d][d]; //  on fait une copie temporaire pour stocker les nouvelles valeurs lorsqu'il y en  a

    for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
            int somme = somme_cellules_voisines(d, tab, i, j);

            if(somme > b){ //si la somme des compteurs de vie est superieure au seuil de vie/mort , la cellule vaut 0 , elle meurt
                copie[i][j] = 0;
            } 
            else{
                copie[i][j] = tab[i][j]; // sinon la cellule ne change pas 
            }
        }
    }

    for(int i = 0; i < d; i++){     //changement du tableau avec les nouvelles valeurs des cellules mortes 
        for(int j = 0; j < d; j++){
            tab[i][j] = copie[i][j];
        }
    }
}

int main(){
    int a;    // a represente la taille du tableau (a lignes et a colonnes)
    printf("Veuillez saisir la taille du tableau:\n");
    scanf("%d", &a);

    int b;  // b represente le seuil de vie ou de mort
    printf("Veuillez saisir le seuil de vie ou de mort:\n");
    scanf("%d", &b);

    int c; // c represente le nbre d'iterations
    printf("Veuillez saisir le nbre d'iterations:\n");
    scanf("%d", &c);

    int tab[a][a]; 

    ini_plateau_de_jeu(a, tab);//appel fonction pour liree

    printf("\n");// pour sauter une ligne avant l'affichage du premier tableau apres 1 iteration

    for(int i = 0; i < c; i++){ // boucle qui appelle la fonction d'affichage de chaque tableau apres chaque iteration pour les afficher selon le nbre d'iterations lues en redirection
        maj_tableau(a, tab, b);
        affichage_tab(a, tab);
    }

    return 0;
}
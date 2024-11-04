#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>

void drawGrid(int grid[7][6]);
bool playTurn(int grid[7][6], int column, int player);
int victory(int grid[7][6], int player);
void initialisation(int grid[7][6], int player);
int prediction(int grid[7][6], int player);
void random_choice(int grid[7][6]);

int main(int argc, char** argv){
    int grille[7][6] = {};
    std::string choix;
    std::string decision;
    char rejouer;

    int player = 1;
    srand(time(NULL));

    while (true){
        //Choix du mode de jeu
        std::cout << "\n";
        std::cout << "Choisissez le mode de jeu : \n 1 - Joueur_1 VS Jouer_2 \n 2 - Joueur_1 VS IA \n 3 - exit " <<std::endl;
        std::cout << "Décision -> ";
        std::cin >> decision;

        //Pour le mode J1 VS J2
        if(decision == "1"){
            while(true){
                //Choix de la colonne par le joueur
                std::cout << "Joueur_" << player << " -> col :";
                std::cin >> choix;

                bool success = false;

                //Vérification du choix et  conversion en entier
                if (choix.size() == 1){
                    if (choix[0] >= '0' && choix[0] <= '7'){
                        int col = choix[0]  - '0';

                        success = playTurn(grille, col, player);
                    }
                }

                //Détermination d'une potentielle victoire des joueurs
                if(victory(grille, player) != 0){
                    system("clear");
                    std::cout << "Le Player " << victory(grille, player) << " remporte la victoire\n";
                    drawGrid(grille);
                    std::cout << "Voulez vous rejouer? (o/n) : ";
                    std::cin >> rejouer;
                    if(rejouer == 'o'){
                        initialisation(grille, player);
                        continue;
                    }else{
                        exit(0);
                    }
                }

                //Nettoyage de la fenêtre
                system("clear");

                //Vérification du choix
                if (!success){
                    std::cout << "votre choix est incorrect\n";
                } else{
                    if (player == 1) player = 2;
                    else player = 1;
                }

                //Affichage de la grille de jeu
                drawGrid(grille);
            }
        }

        //Pour le mode J1 VS IA
        else if(decision == "2"){
            while(true){
                if(player == 1){
                    //Choix de la colonne par le joueur
                    std::cout << "Joueur_" << player << " -> col :";
                    std::cin >> choix;

                    bool success = false;

                    //Vérification du choix et  conversion en entier
                    if (choix.size() == 1){
                        if (choix[0] >= '0' && choix[0] <= '7'){
                            int col = choix[0]  - '0';

                            success = playTurn(grille, col, player);
                        }
                    }

                    //Détermination d'une potentielle victoire du joueurs
                    if(victory(grille, player) != 0){
                        system("clear");
                        std::cout << "Le Player " << victory(grille, player) << " remporte la victoire\n";
                        drawGrid(grille);
                        std::cout << "Voulez vous rejouer? (o/n) : ";
                        std::cin >> rejouer;
                        if(rejouer == 'o'){
                            initialisation(grille, player);
                            continue;
                        }else{
                            exit(0);
                        }
                    }

                    //Nettoyage de la fenêtre
                    system("clear");

                    //Vérification du choix
                    if (!success){
                        std::cout << "votre choix est incorrect\n";
                    } else{
                        if (player == 1) player = 2;
                        else player = 1;
                    }

                    //Affichage de la grille de jeu
                    drawGrid(grille);

                }else
                if(player == 2){
                    if(prediction(grille, 1) != 7){
                        bool success = playTurn(grille, prediction(grille, 1), 2);
                    }else{
                        random_choice(grille);
                    }
                    //Détermination d'une potentielle victoire du joueurs
                    if(victory(grille, player) != 0){
                        system("clear");
                        std::cout << "L'IA remporte la victoire\n";
                        drawGrid(grille);
                        std::cout << "Voulez vous rejouer? (o/n) : ";
                        std::cin >> rejouer;
                        if(rejouer == 'o'){
                            initialisation(grille, player);
                            continue;
                        }else{
                            exit(0);
                        }
                    }

                    //Nettoyage de la fenêtre
                    system("clear");

                    player = 1;

                    //Affichage de la grille de jeu
                    drawGrid(grille);
                } 
            }
        }

        //Pour le choix de quitter le jeux
        else if(decision == "exit"){
            break;
        }
        //Choix invalide
        else{
            std::cout << "Opération invalide \n";
        }


    }

    return 0;
}


// 0, 1, 2
void drawGrid(int grille[7][6]){
    for (int ligne = 0; ligne < 6; ligne++){
        std::cout << "|";
        for (int col = 0; col < 7; col++){
            if (grille[col][ligne] == 1){
                std::cout << "\033[31m*\033[37m";
            } else 
            if (grille[col][ligne] == 2){
                std::cout << "\033[32m*\033[37m";
            }
            else {
                std::cout << "\033[37m*\033[37m";
            }
            std::cout << "|";
        }
        std::cout << "\n";
    }
}

bool playTurn(int grid[7][6], int column, int player){
    for (int line = 5 ; line >= 0; line--){
        if (grid[column - 1][line] == 0){
            grid[column - 1][line] = player;
            return true;
        }
    }
    return false;
}

int victory(int grid[7][6], int player){
    int i, j;
    for(i = 0; i < 7 ; i++){
        for(j = 5; j > 2; j--){
            if(grid[i][j] == player && grid[i][j-1] == player && grid[i][j-2] == player && grid[i][j-3] == player)
                return player;
        }
    }
    for(i = 0; i < 4 ; i++){
        for(j = 0; j < 6; j++){
            if(grid[i][j] == player && grid[i+1][j] == player && grid[i+2][j] == player && grid[i+3][j] == player)
                return player;
        }
    }
    for(i = 0; i < 4 ; i++){
        for(j = 0; j < 3; j++){
            if(grid[i][j] == player && grid[i+1][j+1] == player && grid[i+2][j+2] == player && grid[i+3][j+3] == player)
                return player;
        }
    }
    for(i = 0; i < 7 ; i++){
        for(j = 5; j > 2; j--){
            if(grid[i][j] == player && grid[i+1][j-1] == player && grid[i+2][j-2] == player && grid[i+3][j-3] == player)
                return player;
        }
    }

    return 0;
}

void initialisation(int grid[7][6], int player){
    for(int  i = 0; i < 7; i++){
        for(int  j = 0; j < 7; j++){
            grid[i][j] = {};
        }
    }
    player = 1;
}

int prediction(int grid[7][6], int player){
    int i, j;
    for(i = 0; i < 7 ; i++){
        for(j = 5; j > 2; j--){
            if(grid[i][j] == player && grid[i][j-1] == player && grid[i][j-2] == player && grid[i][j-3] == 0)
                return i;
        }
    }
    for(i = 0; i < 4 ; i++){
        for(j = 0; j < 6; j++){
            if(grid[i][j] == player && grid[i+1][j] == player && grid[i+2][j] == player && grid[i+3][j] == 0)
                return i+3;
        }
    }
    for(i = 0; i < 4 ; i++){
        for(j = 0; j < 3; j++){
            if(grid[i][j] == player && grid[i+1][j+1] == player && grid[i+2][j+2] == player && grid[i+3][j+3] == 0)
                return i+3;
        }
    }
    for(i = 0; i < 7 ; i++){
        for(j = 5; j > 2; j--){
            if(grid[i][j] == player && grid[i+1][j-1] == player && grid[i+2][j-2] == player && grid[i+3][j-3] == 0)
                return i+3;
        }
    }

    return 7;
}

void random_choice(int grid[7][6]){
    bool success = false;

    while(!success){
        int column = rand()%7;

        success = playTurn(grid, column, 2);
    }
}
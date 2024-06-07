#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>

// all the notes at this moment are all in romanian, I'm going to update them in eng

//functie ce are functionalitate dubla:
// cmd == 0 -> initializez tot board-ul cu 0
// cmd == 1 -> afisez tot board-u + atribuitele sale
void act_on_gameboard(int gameboard[4][4], int cmd, int score, int high_score){
    int i, j;
    //initializarea variabelor pentru aflarea timpului curent
    time_t c_time;
    struct tm *lc_time;

    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
            switch(cmd){
                //initializez tot board-ul cu 0
                case 0:
                    gameboard[i][j] = 0;
                    break;
                //arat board-ul
                case 1:
                    //componentele pentru setarea timpului
                    time(&c_time);
                    lc_time = localtime(&c_time);    
                    int lc_min = lc_time->tm_min;
                    int lc_hour = lc_time->tm_hour;
                    int lc_day = lc_time->tm_mday;
                    int lc_mon = lc_time->tm_mon + 1;
                    int lc_year = lc_time->tm_year + 1900;
                    

                    ///componente pentru setarea culorilor
                    int aux, pow = 0;
                    int body_width = 20, body_heigh = 5;
                    //intreaga paleta de culori folosita, intai declarand culorile ca mai apoi sa declar set-ulde culori folosit
                    init_color(100, 900, 900, 900);   
                    init_color(101, 900, 566, 581);   
                    init_color(102, 900, 693, 635);   
                    init_color(103, 900, 666, 608);   
                    init_color(104, 642, 770, 823);   
                    init_color(105, 526, 832, 526);   
                    init_color(106, 800, 784, 619);   
                    init_color(107, 780, 540, 780);   
                    init_color(108, 900, 658, 702);   
                    init_color(109, 642, 900, 642);   
                    init_color(110, 900, 748, 642);  
                    init_color(111, 860, 800, 500);  
                    init_color(112, 730, 700, 800);
                    init_pair(1, 100, 101);
                    init_pair(2, 100, 102);
                    init_pair(3, 100, 103);
                    init_pair(4, 100, 104);
                    init_pair(5, 100, 105);
                    init_pair(6, 100, 106);
                    init_pair(7, 100, 107);
                    init_pair(8, 100, 108);
                    init_pair(9, 100, 109);
                    init_pair(10,100, 110);
                    init_pair(11,100, 111);
                    init_pair(12,100, 112);

                    //intai sa afisez gameboard-ul, afisez titlul jocului, ora curenta si scorul jocului in desfasurare
                    if(i == 0 && j == 0){
                        clear(); 
                        mvprintw(1, 20,"2048 The Game");
                        mvprintw(5 , 65 ,"Date:%02d.%02d.%d", lc_day, lc_mon , lc_year);
                        mvprintw(6 , 65 ,"Clock:%02d:%02d\n", lc_hour, lc_min);
                        mvprintw(9 , 65 ,"(W) Move up the cubes");
                        mvprintw(11 , 65 ,"(D) Move to the right the cubes");
                        mvprintw(13 , 65 ,"(S) Move down the cubes");
                        mvprintw(15 , 65 ,"(A) Move to the legt the cubes");
                        mvprintw(2, 20, "Score: %d", score);
                        //respectiv anunt player-ul daca a obtinut un highscore
                        if(score > high_score) 
                            printw(" (new highscore!)");
                        //printw("\n");
                    }
                    //set de comezi care determin la ce putere a lui 2 este o anumite casuta
                    aux = gameboard[i][j];
                    while(aux != 1 && aux !=0){
                        pow++;
                        aux /= 2;
                    }
                    pow++;
                    //iar in funcie de puterea lui 2 atribui o culoare casutei din gameboard
                    attron(COLOR_PAIR(pow));
                    move(i * 3 + body_heigh     , j * 9 + body_width);
                    printw("         ");
                    move(i * 3 + body_heigh + 1 , j * 9 + body_width);
                    printw(" %*d    ", 4, gameboard[i][j]);
                    move(i * 3  + body_heigh + 2, j * 9 + body_width);
                    printw("         ");
                    move(i * 3 + body_heigh     , j * 9 + body_width);
                    attroff(COLOR_PAIR(pow));
                    break;
                default:
                    printf("ERROR1!");
            }    

}

//functie care este apelata odata ce se verifica daca se poate introduce un element si il introduce
void trow_in_num(int gameboard[4][4]){
    int i, j; 
    //aleg un i si j aleatoriu care defineste o causta din gameboard
    do{        
        i = rand() % 4; 
        j = rand() % 4; 
    }while(gameboard[i][j] != 0); 
    
    //aleg aleatoriu daca sa inserez fie 2 fie 4
    if(rand() % 2 == 0)
        gameboard[i][j] = 2;
    else
        gameboard[i][j] = 4;   
}

//functie care verifica daca se mai poate insera un element (2 sau 4) in gameboard
void check_if_trow(int gameboard[4][4]){
    int i, j;

    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
            if( gameboard[i][j] == 0){
                trow_in_num(gameboard);
                return;
                }
}

//functie ce verifica pe gameboard dace doua casute au acelasi nr pe ele
int check_aroud(int gameboard[4][4], int i, int j){

    if( j <= 2 && gameboard[i][j] == gameboard[i][j + 1])
        return 1;
    if( j >= 1 && gameboard[i][j] == gameboard[i][j - 1])
        return 1;
    if( i <= 2 && gameboard[i][j] == gameboard[i + 1][j])
        return 1;
    if( i >= 1 && gameboard[i][j] == gameboard[i - 1][j])
        return 1;
    return 0;
}

//functie ce verifica daca jocul nu s-a incheiat
int check_gameboard_state(int gameboard[4][4]){
    int i, j;
    //verific daca player-ul a ajuns la 2048
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
            if( gameboard[i][j] == 2048)
                return 2; 
    //verific daca pe gameboard se mai poate face o mutare
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
            if( !gameboard[i][j] || check_aroud(gameboard, i, j))
                return 0;
        
    return 1;
}

//set de 4 functii care se ocupa cu toate miscarile care pot fi aplicate board-ului
void move_west(int gameboard[4][4], int **score){
    int i, j, k, t;
    
    for(i = 0; i < 4; i++){
        k = 0;
        for(j = 0; j < 4; j++)
            //caut un element care nu e 0 
            if(gameboard[i][j]){
                //ca dupa sa caut alt element care nu e 0 si este egal cu el
                for(t = j + 1; t < 4; t++){
                    //in caz afirmativ inmultesc casutele si dau update la score
                    if(gameboard[i][t] && gameboard[i][j] == gameboard[i][t]){
                        gameboard[i][j] *= 2;
                        gameboard[i][t] = 0;
                        **score += gameboard[i][j];
                        break;
                    }
                    //in caz negativ ma opresc cu cautarea de la elementul initial
                    if(gameboard[i][t])break;
                }
                //mut elementele gasite in funcie de coordonata miscarii 
                gameboard[i][k] = gameboard[i][j];
                if(k++ != j)gameboard[i][j]   = 0;
            }   

    }
}

void move_east(int gameboard[4][4], int **score){
    int i, j, k, t;

    for(i = 0; i < 4; i++){
        k = 3;
        for(j = 3; j >= 0; j--)
            //caut un element care nu e 0 
            if(gameboard[i][j]){
                //ca dupa sa caut alt element care nu e 0 si este egal cu el
                for(t = j - 1; t >= 0; t--){
                    //in caz afirmativ inmultesc casutele si dau update la score
                    if(gameboard[i][t] && gameboard[i][j] == gameboard[i][t]){
                        gameboard[i][j] *= 2;
                        gameboard[i][t] = 0;
                        **score += gameboard[i][j];
                        break;
                    }
                    //in caz negativ ma opresc cu cautarea de la elementul initial
                    if(gameboard[i][t])break;
                }
                //mut elementele gasite in funcie de coordonata miscarii 
                gameboard[i][k] = gameboard[i][j];
                if(k-- != j)gameboard[i][j]   = 0;
            }
    }
}

void move_nord(int gameboard[4][4], int **score){
    int i, j, k, t;

    for(i = 0; i < 4; i++){
        k = 0;
        for(j = 0; j < 4; j++)
            //caut un element care nu e 0 
            if(gameboard[j][i]){
                //ca dupa sa caut alt element care nu e 0 si este egal cu el
                for(t = j + 1; t < 4; t++){
                    //in caz afirmativ inmultesc casutele si dau update la score
                    if(gameboard[t][i] && gameboard[j][i] == gameboard[t][i]){
                        gameboard[j][i] *= 2;
                        gameboard[t][i] = 0;
                        **score += gameboard[j][i];
                        break;
                    }
                    //in caz negativ ma opresc cu cautarea de la elementul initial
                    if(gameboard[t][i])break;
                }
                //mut elementele gasite in funcie de coordonata miscarii 
                gameboard[k][i] = gameboard[j][i];
                if(k++ != j)gameboard[j][i]   = 0;
            }
    }
}

void move_south(int gameboard[4][4], int **score){
    int i, j, k, t;

    for(i = 0; i < 4; i++){
        k = 3;
        for(j = 3; j >= 0; j--)
            //caut un element care nu e 0 
            if(gameboard[j][i]){
                //ca dupa sa caut alt element care nu e 0 si este egal cu el
                for(t = j - 1; t >= 0; t--){
                    //in caz afirmativ inmultesc casutele si dau update la score
                    if(gameboard[t][i] && gameboard[j][i] == gameboard[t][i]){
                        gameboard[j][i] *= 2;
                        gameboard[t][i] = 0;
                        **score += gameboard[j][i];
                        break;
                    }
                    //in caz negativ ma opresc cu cautarea de la elementul initial
                    if(gameboard[t][i])break;
                }
                //mut elementele gasite in funcie de coordonata miscarii 
                gameboard[k][i] = gameboard[j][i];
                if(k-- != j)gameboard[j][i] = 0;
            }
    }
}

//verifica daca doua matrici sunt egale
int check_gameboard_compatibility(int a_gameboard[4][4], int b_gameboard[4][4]){
    int i, j;
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
            if(a_gameboard[i][j] != b_gameboard[i][j])  
                return 0;
    return 1;
}

//functie care copiaza o matrice de 4x4 in alta
void copy_gameboard(int a_gameboard[4][4], int b_gameboard[4][4]){
    int i, j;
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
            a_gameboard[i][j] = b_gameboard[i][j];
}

//functie care creeaza un bot care sa verifice ce miscari valide se pot face ca mai apoi sa le efectueze
char bot_helper(int gameboard[4][4]){
    //initializare a unei matrici auxiliare care va fi comparata cu matricea gameboard-ului
    int aux_gameboard[4][4];
    int *aux_score = malloc(sizeof(int));
    *aux_score = 0;

    //copiez matricea jocului in cea auxiliara
    copy_gameboard(aux_gameboard, gameboard);

    //set de comenzi prin care aplic fiecare miscare posibila si verific daca odata aplicate matriciile sunt diferite
    move_nord(aux_gameboard, &aux_score);
    if( !check_gameboard_compatibility(aux_gameboard,gameboard) )
        return 'w';
        
    move_east(aux_gameboard, &aux_score);
    if( !check_gameboard_compatibility(aux_gameboard,gameboard) )
        return 'd';
        
    move_south(aux_gameboard, &aux_score);
    if( !check_gameboard_compatibility(aux_gameboard,gameboard) )
        return 's';
        
    move_west(aux_gameboard, &aux_score);
    if( !check_gameboard_compatibility(aux_gameboard,gameboard) )
        return 'a';
        
    return '0';
}

//functie ce se ocupa de input-ul dat de player 
int chose(int gameboard[4][4],  int *score, int high_score){
    char command;

    //initializarea unor variabile prin care calculez de cat timp nu a mai raspuns 
    time_t start_input = time(NULL);
    time_t current_input;
    int dif_response = 0;

    //cat timp nu primeste input de la player este activ un timer care sa dea refresh la pagina la fiecare sec
    while(command != 's' && command != 'w' && command != 'd' && command != 'a'){
        timeout(100);
        //daca este apasat q atunci se intoarece la meniu
        if(command == 'q') return 0;
        command = getch();    

        //resetarea timer-ului odata ce este apasat un buton
        if(command != ERR)start_input = time(NULL);
        else{
            current_input = time(NULL);
            dif_response = difftime(current_input, start_input);
        }

        //dupa o perioada de timp este activat un bot care sa te ajute sa faci miscari valide
        if(dif_response == 6)
            command = bot_helper(gameboard);
        
        //actualizarea la fiecare secunda a gameboard-ului
        act_on_gameboard(gameboard, 1, *score, high_score);
    }

    switch (command){
    case 's':
        move_south(gameboard, &score);
        break;
    case 'w':
        move_nord(gameboard, &score);
        break;
    case 'd':
        move_east(gameboard, &score);
        break;
    case 'a':
        move_west(gameboard, &score);
        break;
    default:
        break;
    }

    return 1;
}

//functie care printeaza optiunea de highscore
void high_score_show(int high_score, char name[10]){

    int press= 1;
    clear();
    mvprintw(5, 20,"* * * The high score: %d (%s) * * *", high_score, name);
    refresh();
    while( press != 113)
        press = getch();
}

//functie ce verifica daca player-ul a castigat/pierdut si afiseaza conform 
void check_win(int gameboard[4][4], int score, int high_score, char name[10]){
    timeout(-1);
    
    if(check_gameboard_state(gameboard) == 1){
        //printeaza pentru ultima data gameboard-ul, iti zice frumos ca ai pierdut si 
        // daca ai facut un highscore te pune sa iti introduci numele salvand noul scor
        act_on_gameboard(gameboard, 1, score, high_score);
        mvprintw(20, 20, "You lost.. good job, genius!\n");
        char aux_name[30];
        if(score == high_score){
            mvprintw( 21, 20,"Enter your name tho, ");
            mvprintw( 22, 22, "You got a highscore (use a nickname with max 9 characters): ");
            echo();
            getstr(aux_name);
            //verific prin aux_name daca nu s-a introdus un nume mai mare de 9 character3
            while(strlen(aux_name) > 9){
                mvprintw( 21, 20,"Enter your name tho, ");
                mvprintw( 22, 22, "You got a highscore (use a nickname with max 9 characters): ");
                mvprintw( 22, 82, "                                 ");
                move(22,82);
                getstr(aux_name);
            }
            strcpy(name, aux_name);

            noecho();
        }
        refresh();
    }else{
        //printeaza pentru ultima data gameboard-ul si iti zice uimit ca ai castigat 
        act_on_gameboard(gameboard, 1, score, high_score);
        mvprintw(20, 20,"You...won.. but how ?!");
        getch();
        refresh();
    }
}

//functie ce reseteaza intreg jocul 
void new_game(int gameboard[4][4], int *score, int high_score){
    act_on_gameboard(gameboard, 0, 0, high_score);
    *score = 0;
    check_if_trow(gameboard);
    check_if_trow(gameboard);
}

//functie ce se ocupa de logica din spatele jocului
void game(int gameboard[4][4], int *score, int *game_in_progress, int *high_score, char name[10]){
    //while ce verifica daca jocu se poate continua
    while( !check_gameboard_state(gameboard) ){
        //chem funcia cu 1 pentru a da print la joc
        act_on_gameboard(gameboard, 1, *score, *high_score);

        //functie care se ocupa de input-ul player-ului 
        if( !chose(gameboard, score, *high_score) ) return;

        //verfic daca se poate insera un nou element in tabla de joc
        check_if_trow(gameboard);
    }

    //actiuni ce se iau odata ce jocul s-a sfarsit
    *game_in_progress = 0;
    if(*high_score < *score) *high_score = *score;
    check_win(gameboard, *score, *high_score, name);
}

//declar o fereastra special dedicata pentru meniu si creez o casuta de design
void print_menu(WINDOW *menu_win){
    clear();
    //refresh();
    mvprintw( 2, 7, "2048 The Game");
    box(menu_win, 0 , 0);
    wmove(menu_win, 1, 1);
    refresh();
    wrefresh(menu_win); 
}

//functia pentru meniu care se ocupa de majoritatea functionalitatii a jocului
void menu(){
    //initializez gameboard ul si toate atribuitele importante ale acestuia
    int gameboard[4][4];
    int high_score = 0, score, game_in_progres = 0;
    char name[10];
    int i, j;

    //initializez un pointer catre fisierul data.txt, verific daca exista si in caz afirmativ preiau informatiile din ea
    FILE *fl;
    fl = fopen("data.txt", "r");   
    if(fl != NULL){
        int check;
        fscanf(fl, "%d %s %d", &high_score, name, &check);

        if(check == 1){            
        for(i = 0; i < 4; i++)
            for(j = 0; j < 4; j++)
                fscanf(fl, "%d", &gameboard[i][j] );
        fscanf(fl, "%d", &score );
        game_in_progres = 1;
        }
        fclose(fl);
    }

    //initializez componentele esentiale ale meniului si fereastra atribuita ei
    char menu_options[4][10] = { "New Game", "Resume", "Scores","Quit"};
    int width_max, height_max, option, highlight_option = 0;
    getmaxyx(stdscr, height_max, width_max);
    WINDOW *menu_win = newwin(8 , 12, height_max / 10, width_max /20 );

    //while ce se ocupa de functionalitatea meniului
    while(1){
        //printarea meniului
        print_menu(menu_win);
        for(i = 0; i < 4; i++){
            if(highlight_option == i)
                wattron(menu_win, A_REVERSE);

            mvwprintw(menu_win, i + 1, 1, "%s", menu_options[i]);

            if(highlight_option == i)
                wattroff(menu_win, A_REVERSE);

        }

        //alegerea opiuni pe care o vrei tu din meniu
        keypad(menu_win, true);
        option = wgetch(menu_win);
        switch (option){
        case KEY_UP:
            highlight_option--;
            if(highlight_option < 0)
                highlight_option = 0;
            break;
        case KEY_DOWN:
            highlight_option++;
            if(highlight_option > 3)
                highlight_option = 3;
            break;
        default:
            break;
        }

        //switch ce se ocupa de aplicarea actiunilor dupa ce am apasat ENTER
        if(option == 10){
            switch (highlight_option){
            //incepe un nou joc
            case 0:
                new_game(gameboard, &score, high_score);
                game_in_progres = 1;
                game(gameboard, &score, &game_in_progres, &high_score, name);
                break;

            //continua jocul
            case 1:
                if(game_in_progres == 1)
                    game(gameboard, &score, &game_in_progres, &high_score, name);
                break;

            //arata highscore-ul curent
            case 2:
                high_score_show(high_score, name);
                break;

            //iesi din joc
            case 3:
                //pana a iesi din joc sunt salvate datele importante precum highscore-ul 
                // si gameboard-ul daca e un joc in desfasurare
                fl = fopen("data.txt", "w");
                fprintf(fl,"%d %s", high_score, name);
                if(game_in_progres == 1){
                    fprintf(fl," 1\n");
                    for(i = 0; i < 4; i++)
                        for(j = 0; j < 4; j++)
                            fprintf(fl, "%d ", gameboard[i][j] );
                    fprintf(fl, "\n %d \n", score );
                }else
                    fprintf(fl," -1\n");
                return;
                break;
            default:
                break;
            }
        }
    }


}

//functia main in care initializez screen-ul, setez setarile pentru ncurses si chem functia menu 
int main(int argc, char *argv[]){
    //initializez ecranul
    initscr();
    //fac astefel inca sa nu se vada input ul player ului
    noecho();
    //functie care activeaza spectrul de culori 
    start_color();
    //functie care seteaza un seed random in functie de timp
    srand(time(NULL));

    //functie meniu care este practic core-ul jocului
    menu();

    //functia de sfarist care opreste ncurses-ul
    endwin();
    return 0;
}
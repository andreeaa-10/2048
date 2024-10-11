#include <ctype.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define dimensiuni 9.5
#define linii dimensiuni
#define coloane dimensiuni * 2.5

void valoarerandom(int tabla[4][4]) {  
  int col = 0, lin = 0, valoare = 0;
  srand(time(NULL));
  do {  
    col = rand() % 4;
    lin = rand() % 4;
    valoare = (rand() % 2 + 1) * 2;  
  } while (tabla[lin][col] != 0);  
  tabla[lin][col] = valoare;
}
void afisaretabla(int tabla[4][4], WINDOW *jocnou) {  
  int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if (tabla[i][j] != 0) {
        if (tabla[i][j] == 2)  
        {
          wattron(jocnou, COLOR_PAIR(4));
          mvwprintw(jocnou, i * 2 + 2, j * 6 + 3.5, "%d  ", tabla[i][j]);
          wattroff(jocnou, COLOR_PAIR(4));
        } else if (tabla[i][j] == 4)  
        {
          wattron(jocnou, COLOR_PAIR(5));
          mvwprintw(jocnou, i * 2 + 2.5, j * 6 + 3.5, "%d  ", tabla[i][j]);
          wattroff(jocnou, COLOR_PAIR(5));
        } else if (tabla[i][j] == 8)  
        {
          wattron(jocnou, COLOR_PAIR(6));
          mvwprintw(jocnou, i * 2 + 2.5, j * 6 + 3.5, "%d  ", tabla[i][j]);
          wattroff(jocnou, COLOR_PAIR(6));
        } else if (tabla[i][j] == 16)  
        {
          wattron(jocnou, COLOR_PAIR(7));
          mvwprintw(jocnou, i * 2 + 2.5, j * 6 + 3.5, "%d  ", tabla[i][j]);
          wattroff(jocnou, COLOR_PAIR(7));
        } else if (tabla[i][j] == 32)  
        {
          wattron(jocnou, COLOR_PAIR(8));
          mvwprintw(jocnou, i * 2 + 2.5, j * 6 + 3.5, "%d  ", tabla[i][j]);
          wattroff(jocnou, COLOR_PAIR(8));
        } else if (tabla[i][j] == 64)  
        {
          wattron(jocnou, COLOR_PAIR(4));
          mvwprintw(jocnou, i * 2 + 2.5, j * 6 + 3.5, "%d  ", tabla[i][j]);
          wattroff(jocnou, COLOR_PAIR(4));
        } else if (tabla[i][j] == 128)  
        {
          wattron(jocnou, COLOR_PAIR(5));
          mvwprintw(jocnou, i * 2 + 2.5, j * 6 + 3.5, "%d  ", tabla[i][j]);
          wattroff(jocnou, COLOR_PAIR(5));
        } else if (tabla[i][j] == 256)  
        {
          wattron(jocnou, COLOR_PAIR(6));
          mvwprintw(jocnou, i * 2 + 2.5, j * 6 + 3.5, "%d  ", tabla[i][j]);
          wattroff(jocnou, COLOR_PAIR(6));
        } else if (tabla[i][j] == 512)  
        {
          wattron(jocnou, COLOR_PAIR(7));
          mvwprintw(jocnou, i * 2 + 2.5, j * 6 + 3.5, "%d  ", tabla[i][j]);
          wattroff(jocnou, COLOR_PAIR(7));
        } else if (tabla[i][j] == 1024)  
        {
          wattron(jocnou, COLOR_PAIR(8));
          mvwprintw(jocnou, i * 2 + 2.5, j * 6 + 3.5, "%d ", tabla[i][j]);
          wattroff(jocnou, COLOR_PAIR(8));
        } else if (tabla[i][j] == 2048)  
        {
          wattron(jocnou, COLOR_PAIR(4));
          mvwprintw(jocnou, i * 2 + 2.5, j * 6 + 3.5, "%d ", tabla[i][j]);
          wattroff(jocnou, COLOR_PAIR(4));
        }
      } else
        mvwprintw(jocnou, i * 2 + 2.5, j * 6 + 3.5, "  ");  
    }
  }
}

void mutare_stanga(int tabla[4][4], int *scor, int testare[4][4]) {  
  int i, j, k, ok = 0, cnt = 0;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      testare[i][j] =
          tabla[i][j];  
  }
  for (i = 0; i < 4; i++) {
    for (j = 1; j < 4; j++) {
      if (tabla[i][j] != 0) {  
        k = j;
        while (k > 0 &&
               tabla[i][k - 1] == 0) {  
          tabla[i][k - 1] = tabla[i][k];
          tabla[i][k] = 0;
          k--;
        }
      }
    }
  }

  for (i = 0; i < 4; i++) {
    for (j = 1; j < 4; j++) {
      if (tabla[i][j] == tabla[i][j - 1]) {  
        tabla[i][j - 1] = 2 * tabla[i][j - 1];
        tabla[i][j] = 0;
        *scor = *scor + tabla[i][j - 1];  
        if (tabla[i][j] == 0) {
          k = j;
          while (k < 3 &&
                 tabla[i][k + 1] != 0) {  
            tabla[i][k] = tabla[i][k + 1];
            tabla[i][k + 1] = 0;
            k++;
          }
        }
      }
    }
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (tabla[i][j] != testare[i][j])
        ok = 1;  
  }
  if (ok)
    valoarerandom(tabla);  
                           

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      testare[i][j] = 0;  
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (tabla[i][j] == 0)
        cnt++;  
                
  }
  if (cnt == 15)
    valoarerandom(tabla);  
}

void mutare_dreapta(int tabla[4][4], int *scor, int testare[4][4]) {
int i, j, k, ok = 0, cnt = 0;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      testare[i][j] =
          tabla[i][j];  
  }
  for (i = 0; i < 4; i++) {
    for (j = 2; j >= 0; j--) {
      if (tabla[i][j] != 0) {  
        k = j;
        while (k < 3 && tabla[i][k + 1] ==
                            0) {  
          tabla[i][k + 1] = tabla[i][k];
          tabla[i][k] = 0;
          k++;
        }
      }
    }
  }
  for (i = 0; i < 4; i++) {
    for (j = 2; j >= 0; j--) {
      if (tabla[i][j] == tabla[i][j + 1]) {  
        tabla[i][j + 1] = 2 * tabla[i][j + 1];
        tabla[i][j] = 0;
        *scor = *scor + tabla[i][j + 1];  
        k = j;
        while (k > 0 &&
               tabla[i][k - 1] !=
                   0) {  
          tabla[i][k] = tabla[i][k - 1];
          tabla[i][k - 1] = 0;
          k--;
        }
      }
    }
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (tabla[i][j] != testare[i][j])
        ok = 1;  
  }
  if (ok)
    valoarerandom(tabla);  
                           
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      testare[i][j] = 0;  
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (tabla[i][j] == 0)
        cnt++;  
                
  }
  if (cnt == 15)
    valoarerandom(tabla);  
}

void mutare_sus(int tabla[4][4], int *scor, int testare[4][4]) {
  int i, j, k, ok = 0, cnt = 0;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      testare[i][j] =
          tabla[i][j];  
  }
  for (j = 0; j < 4; j++) {
    for (i = 1; i < 4; i++) {
      if (tabla[i][j] != 0) {  
        k = i;
        while (k > 0 && tabla[k - 1][j] ==
                            0) {  
          tabla[k - 1][j] = tabla[k][j];
          tabla[k][j] = 0;
          k--;
        }
      }
    }
  }
  for (j = 0; j < 4; j++) {
    for (i = 1; i < 4; i++) {
      if (tabla[i][j] == tabla[i - 1][j]) {  
        tabla[i - 1][j] = 2 * tabla[i - 1][j];
        tabla[i][j] = 0;
        *scor = *scor + tabla[i - 1][j];  
        k = i;
        while (k < 3 &&
               tabla[k + 1][j] !=
                   0) {  
          tabla[k][j] = tabla[k + 1][j];
          tabla[k + 1][j] = 0;
          k++;
        }
      }
    }
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (tabla[i][j] != testare[i][j])
        ok = 1;  
  }
  if (ok)
    valoarerandom(tabla);  
                           
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      testare[i][j] = 0;  
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (tabla[i][j] == 0)
        cnt++;  
                
  }
  if (cnt == 15)
    valoarerandom(tabla);  
}

void mutare_jos(int tabla[4][4], int *scor, int testare[4][4]) {
  int i, j, k, ok = 0, cnt = 0;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      testare[i][j] =
          tabla[i][j];  
  }
  for (j = 0; j < 4; j++) {
    for (i = 2; i >= 0; i--) {
      if (tabla[i][j] != 0) {  
        k = i;
        while (k < 3 && tabla[k + 1][j] ==
                            0) {  
          tabla[k + 1][j] = tabla[k][j];
          tabla[k][j] = 0;
          k++;
        }
      }
    }
  }
  for (j = 0; j < 4; j++) {
    for (i = 2; i >= 0; i--) {
      if (tabla[i][j] == tabla[i + 1][j]) {  
        tabla[i + 1][j] = 2 * tabla[i + 1][j];
        tabla[i][j] = 0;
        *scor = *scor + tabla[i + 1][j];  
        k = i;
        while (k > 0 &&
               tabla[k - 1][j] !=
                   0) {  
          tabla[k][j] = tabla[k - 1][j];
          tabla[k - 1][j] = 0;
          k--;
        }
      }
    }
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (tabla[i][j] != testare[i][j])
        ok = 1;  
  }
  if (ok)
    valoarerandom(tabla);  
                           
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      testare[i][j] = 0;  
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (tabla[i][j] == 0)
        cnt++;  
                
  }
  if (cnt == 15)
    valoarerandom(tabla);  
}
void game_over(int tabla[4][4], WINDOW *panoudecontrol) {  
  int i, j, cnt = 0;
  for (i = 1; i < 3; i++) {
    for (j = 1; j < 3; j++)  
                             
      if (tabla[i][j] != tabla[i - 1][j] && tabla[i][j] != tabla[i + 1][j] &&
          tabla[i][j] != tabla[i][j - 1] && tabla[i][j] != tabla[i][j + 1] &&
          tabla[i][j] != 0 && tabla[i][j + 1] != 0 && tabla[i][j - 1] != 0 &&
          tabla[i + 1][j] != 0 && tabla[i - 1][j] != 0)
        cnt++;  
  }
  if (tabla[1][0] != tabla[2][0] && tabla[2][0] != 0 &&
      tabla[1][0] != 0)  
    cnt++;
  if (tabla[1][3] != tabla[2][3] && tabla[2][3] != 0 && tabla[1][3] != 0) cnt++;
  if (tabla[0][1] != tabla[0][2] && tabla[0][1] != 0 && tabla[0][2] != 0) cnt++;
  if (tabla[3][1] != tabla[3][2] && tabla[3][1] != 0 && tabla[3][2] != 0) cnt++;
  if (tabla[0][0] != tabla[0][1] &&
      tabla[0][0] != tabla[1][0] &&  
      tabla[0][0] != 0 && tabla[0][1] != 0 && tabla[1][0] != 0)
    cnt++;  
  if (tabla[0][3] != tabla[0][2] &&
      tabla[0][3] != tabla[1][3] &&  
      tabla[0][3] != 0 && tabla[0][2] != 0 && tabla[1][3] != 0)
    cnt++;
  if (tabla[3][0] != tabla[3][1] &&
      tabla[3][0] != tabla[2][0] &&  
      tabla[3][0] != 0 && tabla[3][1] != 0 && tabla[2][0] != 0)
    cnt++;
  if (tabla[3][3] != tabla[3][2] &&
      tabla[3][3] != tabla[2][3] &&  
      tabla[3][3] != 0 && tabla[3][2] != 0 && tabla[2][3] != 0)
    cnt++;
  if (cnt == 12) {           
    wclear(panoudecontrol);  
                             
    wrefresh(panoudecontrol);
    box(panoudecontrol, 0, 0);  
    wrefresh(panoudecontrol);
    mvwprintw(panoudecontrol, 2, 2, "You lost!");  
    mvwprintw(panoudecontrol, 3, 2, "Press 'Q' to return to menu");
    wrefresh(panoudecontrol);
  }
}
void winner(WINDOW *panoudecontrol, int tabla[4][4]) {  
  int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (tabla[i][j] == 2048) {  
        wclear(panoudecontrol);   
                                 
        wrefresh(panoudecontrol);
        box(panoudecontrol, 0, 0);  
        wrefresh(panoudecontrol);
        mvwprintw(panoudecontrol, 1, 2, "You won!");  
        mvwprintw(panoudecontrol, 4, 2, "Press 'Q' to return to menu");
        mvwprintw(panoudecontrol, 2, 2, "Keep playing to reach even");
        mvwprintw(panoudecontrol, 3, 2, "higher scores!");
        mvwprintw(panoudecontrol, 5, 2, "Press 'U' to undo");
        wrefresh(panoudecontrol);
        break;
      }
  }
}
void afisare_scor(WINDOW *panoudecontrol, int *scor) {  
  mvwprintw(panoudecontrol, 2, 2, "Score: %d", *scor);
  wrefresh(panoudecontrol);
}

int max(int a, int b) {
  return (a > b) ? a : b;
}  
void undo(int tabla[4][4], int *scor, int tabla_veche[4][4], int *scor_vechi) {  
  int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      tabla[i][j] =
          tabla_veche[i][j];  
                              
  }
  *scor = *scor_vechi;  
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      tabla_veche[i][j] =
          0;  
  }
}
void best_move_new(int aux1[4][4], int aux2[4][4], int tabla[4][4], int *scor, int testare[4][4]) {  
  int i, j, nr = 0;
  int cnt1_1 = 0, cnt2_1 = 0, cnt3_1 = 0, cnt4_1 = 0;
  int cnt1_2 = 0, cnt2_2 = 0, cnt3_2 = 0, cnt4_2 = 0;
  int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0;
  int scor_initial = *scor;  
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      aux1[i][j] = tabla[i][j];  
      aux2[i][j] = tabla[i][j];
    }
  }
  mutare_stanga(aux1, scor, testare);  
  *scor = scor_initial;                
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (aux1[i][j] == 0)
        cnt1_1++;  
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (aux1[i][j] != aux2[i][j])
        cnt1_2 =
            1;  
  }
  if (cnt1_1 >= 0 && cnt1_2 == 1)
    cnt1 = cnt1_1;  
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      aux1[i][j] = aux2[i][j];  
    }
  }
  mutare_dreapta(aux1, scor, testare);  
  *scor = scor_initial;                 
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (aux1[i][j] == 0)
        cnt2_1++;  
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (aux1[i][j] != aux2[i][j])
        cnt2_2 =
            1;  
  }
  if (cnt2_1 >= 0 && cnt2_2 == 1)
    cnt2 = cnt2_1;  
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      aux1[i][j] = aux2[i][j];  
    }
  }
  mutare_sus(aux1, scor, testare);  
  *scor = scor_initial;             
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (aux1[i][j] == 0)
        cnt3_1++;  
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (aux1[i][j] != aux2[i][j])
        cnt3_2 =
            1;  
  }
  if (cnt3_1 >= 0 && cnt3_2 == 1)
    cnt3 = cnt3_1;  
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      aux1[i][j] = aux2[i][j];  
    }
  }
  mutare_jos(aux1, scor, testare);  
  *scor = scor_initial;             
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (aux1[i][j] == 0)
        cnt4_1++;  
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (aux1[i][j] != aux2[i][j])
        cnt4_2 =
            1;  
  }
  if (cnt4_1 >= 0 && cnt4_2 == 1)
    cnt4 = cnt4_1;  
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      aux1[i][j] = 0;  
      aux2[i][j] = 0;
    }
  }
  int max_gol = max(max(max(cnt1, cnt2), cnt3),
                    cnt4);  
  if (max_gol == cnt1)
    nr++;  
  if (max_gol == cnt2) nr++;
  if (max_gol == cnt3) nr++;
  if (max_gol == cnt4) nr++;
  if (nr > 1) {  
    if (max_gol == cnt1)
      mutare_stanga(tabla, scor, testare);
    else if (max_gol == cnt2)
      mutare_dreapta(tabla, scor, testare);
    else if (max_gol == cnt3)
      mutare_sus(tabla, scor, testare);
    else if (max_gol == cnt4)
      mutare_jos(tabla, scor, testare);
  }
  if (nr == 1) {  
    if (max_gol == cnt1) mutare_stanga(tabla, scor, testare);
    if (max_gol == cnt2) mutare_dreapta(tabla, scor, testare);
    if (max_gol == cnt3) mutare_sus(tabla, scor, testare);
    if (max_gol == cnt4) mutare_jos(tabla, scor, testare);
  }
}
void best_move_resume(int aux1[4][4], int aux2[4][4], int tabla[4][4], int *scor_resume, int testare[4][4]) {  
  int i, j, nr = 0;  
  int cnt1_1 = 0, cnt2_1 = 0, cnt3_1 = 0, cnt4_1 = 0;
  int cnt1_2 = 0, cnt2_2 = 0, cnt3_2 = 0, cnt4_2 = 0;
  int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0;
  int scor_initial = *scor_resume;  
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      aux1[i][j] = tabla[i][j];
      aux2[i][j] =
          tabla[i][j];  
    }
  }
  mutare_stanga(aux1, scor_resume, testare);  
  *scor_resume = scor_initial;                
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (aux1[i][j] == 0)
        cnt1_1++;  
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (aux1[i][j] != aux2[i][j])
        cnt1_2 =
            1;  
  }
  if (cnt1_1 > 0 && cnt1_2 == 1)
    cnt1 = cnt1_1;  
                    
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      aux1[i][j] = aux2[i][j];
    }
  }
  mutare_dreapta(aux1, scor_resume, testare);  
  *scor_resume = scor_initial;                 
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (aux1[i][j] == 0)
        cnt2_1++;  
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (aux1[i][j] != aux2[i][j])
        cnt2_2 =
            1;  
  }
  if (cnt2_1 > 0 && cnt2_2 == 1)
    cnt2 = cnt2_1;  
                    
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      aux1[i][j] = aux2[i][j];
    }
  }
  mutare_sus(aux1, scor_resume, testare);  
  *scor_resume = scor_initial;             
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (aux1[i][j] == 0)
        cnt3_1++;  
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (aux1[i][j] != aux2[i][j])
        cnt3_2 =
            1;  
  }
  if (cnt3_1 > 0 && cnt3_2 == 1)
    cnt3 = cnt3_1;  
                    
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      aux1[i][j] = aux2[i][j];
    }
  }
  mutare_jos(aux1, scor_resume, testare);  
  *scor_resume = scor_initial;             
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (aux1[i][j] == 0)
        cnt4_1++;  
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      if (aux1[i][j] != aux2[i][j])
        cnt4_2 =
            1;  
  }
  if (cnt4_1 > 0 && cnt4_2 == 1)
    cnt4 = cnt4_1;  
                    
  int max_gol = max(max(max(cnt1, cnt2), cnt3),
                    cnt4);  
  if (max_gol == cnt1)
    nr++;  
           
  if (max_gol == cnt2) nr++;
  if (max_gol == cnt3) nr++;
  if (max_gol == cnt4) nr++;
  if (nr > 1) {  
                 
                 
    if (max_gol == cnt1)
      mutare_stanga(tabla, scor_resume, testare);
    else if (max_gol == cnt2)
      mutare_dreapta(tabla, scor_resume, testare);
    else if (max_gol == cnt3)
      mutare_sus(tabla, scor_resume, testare);
    else if (max_gol == cnt4)
      mutare_jos(tabla, scor_resume, testare);
  }
  if (nr == 1) {  
                  
    if (max_gol == cnt1) mutare_stanga(tabla, scor_resume, testare);
    if (max_gol == cnt2) mutare_dreapta(tabla, scor_resume, testare);
    if (max_gol == cnt3) mutare_sus(tabla, scor_resume, testare);
    if (max_gol == cnt4) mutare_jos(tabla, scor_resume, testare);
  }
}
void color_box(WINDOW *meniu)  
{
  wattron(meniu, COLOR_PAIR(8));
  box(meniu, 0, 0);
  wattroff(meniu, COLOR_PAIR(8));
  wrefresh(meniu);
}
void chenar(WINDOW *jocnou)  
{
  int xmax, ymax;
  getmaxyx(jocnou, ymax, xmax);

  mvwhline(jocnou, (ymax / 2) - (linii / 2) + 3.5,(xmax / 2) - (coloane / 2) - 1, ACS_HLINE, 26);  
  mvwhline(jocnou, (ymax / 2) - (linii / 2) + 5.5,(xmax / 2) - (coloane / 2) - 1, ACS_HLINE, 26);
  mvwhline(jocnou, (ymax / 2) - (linii / 2) + 7.5,(xmax / 2) - (coloane / 2) - 1, ACS_HLINE, 26);

  mvwvline(jocnou, 1, 8, ACS_VLINE,((xmax / 2) - (coloane / 2) - 1) * 8);  
  mvwvline(jocnou, 1, 14, ACS_VLINE, ((xmax / 2) - (coloane / 2) - 1) * 8);
  mvwvline(jocnou, 1, 20, ACS_VLINE, ((xmax / 2) - (coloane / 2) - 1) * 8);
  wrefresh(jocnou);
}
void newgame(WINDOW *jocnou, WINDOW *panoudecontrol, WINDOW *meniu, int tabla[4][4], int aux[4][4], int *scor, int *scor_resume) {  
  wbkgd(jocnou, COLOR_PAIR(3));
  box(jocnou, 0, 0);
  wrefresh(jocnou);
  chenar(jocnou);

  wbkgd(panoudecontrol, COLOR_PAIR(3));
  box(panoudecontrol, 0, 0);
  wrefresh(panoudecontrol);
  time_t t = time(NULL);
  mvwprintw(panoudecontrol, 1, 2, "%s", ctime(&t));  
  mvwprintw(panoudecontrol, 1, 2, "%c", '\0');
  sleep(1);
  mvwprintw(panoudecontrol, 2, 2, "Score: 0");
  mvwprintw(panoudecontrol, 3, 2, "Press 'Q' to return to menu");
  mvwprintw(panoudecontrol, 4, 2, "Press 'U' to undo");
  mvwprintw(panoudecontrol, 5, 2, "In order to move, press arrows");
  wrefresh(panoudecontrol);

  wrefresh(jocnou);
  keypad(
      jocnou,
      true);  
  keypad(stdscr, true);  
  wrefresh(panoudecontrol);

  int ch, iesiri = 0, i, j, testare[4][4] = {0}, aux1[4][4] = {0},
          aux2[4][4] = {0}, scor_vechi = 0, tabla_veche[4][4] = {0};
  valoarerandom(tabla);  
                         
  valoarerandom(tabla);
  afisaretabla(tabla, jocnou);

  wrefresh(jocnou);

  while (1) {      
    ch = getch();  
    timeout(
        10000);  
    if (ch == ERR) {  
      box(jocnou, 0, 0);
      wrefresh(jocnou);
      chenar(jocnou);
      for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++)
          tabla_veche[i][j] =
              tabla[i][j];  
      }
      scor_vechi = *scor;  
      best_move_new(aux1, aux2, tabla, scor,
                    testare);  
      wrefresh(jocnou);
      afisaretabla(tabla, jocnou);  
      wrefresh(jocnou);
      afisare_scor(panoudecontrol, scor);  
      game_over(tabla, panoudecontrol);    
      winner(panoudecontrol, tabla);       
      wrefresh(panoudecontrol);  
                                 
      wclear(jocnou);
    }
    switch (ch) {   
      case KEY_UP:  
        box(jocnou, 0, 0);
        wrefresh(jocnou);
        chenar(jocnou);  
        for (i = 0; i < 4; i++) {
          for (j = 0; j < 4; j++)
            tabla_veche[i][j] =
                tabla[i]
                     [j];  
        }
        scor_vechi = *scor;  
        mutare_sus(tabla, scor, testare);  
        wrefresh(jocnou);
        afisaretabla(tabla, jocnou);  
        wrefresh(jocnou);
        afisare_scor(panoudecontrol, scor);  
        game_over(tabla, panoudecontrol);    
        winner(panoudecontrol, tabla);       
        wrefresh(panoudecontrol);  
                                   
        wclear(jocnou);
        break;
      case KEY_DOWN:  
        box(jocnou, 0, 0);
        wrefresh(jocnou);
        chenar(jocnou);  
        for (i = 0; i < 4; i++) {
          for (j = 0; j < 4; j++)
            tabla_veche[i][j] =
                tabla[i]
                     [j];  
        }
        scor_vechi = *scor;  
        mutare_jos(tabla, scor, testare);  
        wrefresh(jocnou);
        afisaretabla(tabla, jocnou);  
        wrefresh(jocnou);
        afisare_scor(panoudecontrol, scor);  
        game_over(tabla, panoudecontrol);    
        winner(panoudecontrol, tabla);       
        wrefresh(panoudecontrol);  
                                   
        wclear(jocnou);
        break;
      case KEY_LEFT:
        box(jocnou, 0, 0);
        wrefresh(jocnou);
        chenar(jocnou);  
        for (i = 0; i < 4; i++) {
          for (j = 0; j < 4; j++)
            tabla_veche[i][j] =
                tabla[i]
                     [j];  
        }
        scor_vechi = *scor;  
        mutare_stanga(tabla, scor, testare);  
        wrefresh(jocnou);
        afisaretabla(tabla, jocnou);  
        wrefresh(jocnou);
        afisare_scor(panoudecontrol, scor);  
        game_over(tabla, panoudecontrol);    
        winner(panoudecontrol, tabla);       
        wrefresh(panoudecontrol);  
                                   
        wclear(jocnou);
        break;
      case KEY_RIGHT:
        box(jocnou, 0, 0);
        wrefresh(jocnou);
        chenar(jocnou);  
        for (i = 0; i < 4; i++) {
          for (j = 0; j < 4; j++)
            tabla_veche[i][j] =
                tabla[i]
                     [j];  
        }
        scor_vechi = *scor;  
        mutare_dreapta(tabla, scor, testare);  
        wrefresh(jocnou);
        afisaretabla(tabla, jocnou);  
        wrefresh(jocnou);
        afisare_scor(panoudecontrol, scor);  
        game_over(tabla, panoudecontrol);    
        winner(panoudecontrol, tabla);       
        wrefresh(panoudecontrol);  
                                   
        wclear(jocnou);
        break;
      case 'u':  
        box(jocnou, 0, 0);
        wrefresh(jocnou);
        chenar(jocnou);  
        undo(tabla, scor, tabla_veche, &scor_vechi);  
        afisaretabla(tabla, jocnou);                  
        wrefresh(jocnou);
        afisare_scor(panoudecontrol, scor);  
        wrefresh(panoudecontrol);  
                                   
        wclear(jocnou);
        break;
      case 'q':    
        iesiri++;  
        for (i = 0; i < 4; i++) {
          for (j = 0; j < 4; j++)
            aux[i][j] =
                tabla[i]
                     [j];  
        }
        for (i = 0; i < 4; i++) {
          for (j = 0; j < 4; j++)
            tabla[i][j] =
                0;  
        }
        *scor_resume = *scor;  
        *scor = 0;  
        keypad(jocnou,
               false);  
        break;
      default:
        break;
    }
    if (iesiri > 0) {  
      wclear(jocnou);  
      wrefresh(jocnou);
      wclear(panoudecontrol);  
      wrefresh(panoudecontrol);
      wclear(panoudecontrol);
      wrefresh(panoudecontrol);
      color_box(meniu);
      wrefresh(meniu);
      break;
    }
  }
}

void resume(WINDOW *continuare, WINDOW *panoudecontrol, WINDOW *meniu, int aux[4][4], int *scor_resume, int tabla[4][4], int *scor) {  
  wbkgd(continuare, COLOR_PAIR(3));
  box(continuare, 0, 0);
  wrefresh(continuare);

  chenar(continuare);

  wbkgd(panoudecontrol, COLOR_PAIR(3));
  box(panoudecontrol, 0, 0);
  wrefresh(panoudecontrol);
  time_t t = time(NULL);
  mvwprintw(panoudecontrol, 1, 2, "%s", ctime(&t));
  mvwprintw(panoudecontrol, 1, 2, "%c", '\0');
  sleep(1);
  mvwprintw(panoudecontrol, 2, 2, "Score: %d", *scor_resume);
  mvwprintw(panoudecontrol, 3, 2, "Press 'Q' to return to menu");
  mvwprintw(panoudecontrol, 4, 2, "Press 'U' to undo");
  mvwprintw(panoudecontrol, 5, 2, "In order to move, press arrows");
  wrefresh(panoudecontrol);

  wrefresh(continuare);
  keypad(continuare, true); 
  keypad(stdscr, true);
  wrefresh(panoudecontrol);

  int ch, iesiri = 0, i, j, testare[4][4] = {0}, aux1[4][4] = {0},
          aux2[4][4] = {0}, scor_vechi = *scor, tabla_veche[4][4] = {0};
  afisaretabla(aux, continuare);
  wrefresh(continuare);
  while (1) {
    ch = getch();
    timeout(10000);
    if (ch == ERR) {
      box(continuare, 0, 0);
      wrefresh(continuare);
      chenar(continuare);  
      for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++)
          tabla_veche[i][j] =
              aux[i][j];  
      }
      scor_vechi = *scor_resume;  
      best_move_resume(aux1, aux2, aux, scor_resume, testare);  
      wrefresh(continuare);
      afisaretabla(aux, continuare);
      wrefresh(continuare);
      afisare_scor(panoudecontrol, scor_resume);  
      game_over(tabla, panoudecontrol);           
      winner(panoudecontrol, aux);                
      wrefresh(panoudecontrol);  
      wclear(continuare);
    }
    switch (ch) {
      case KEY_UP:
        box(continuare, 0, 0);
        wrefresh(continuare);
        chenar(continuare);  
        for (i = 0; i < 4; i++) {
          for (j = 0; j < 4; j++)
            tabla_veche[i][j] =
                aux[i][j];  
        }
        scor_vechi = *scor_resume;  
        mutare_sus(aux, scor_resume, testare);  
        wrefresh(continuare);
        afisaretabla(aux, continuare);  
        wrefresh(continuare);
        afisare_scor(panoudecontrol, scor_resume);  
        wrefresh(panoudecontrol);
        game_over(aux, panoudecontrol);  
        wrefresh(panoudecontrol);
        winner(panoudecontrol, aux);  
        wrefresh(panoudecontrol);  
        wclear(continuare);
        break;
      case KEY_DOWN:
        box(continuare, 0, 0);
        wrefresh(continuare);
        chenar(continuare);  
        for (i = 0; i < 4; i++) {
          for (j = 0; j < 4; j++)
            tabla_veche[i][j] =
                aux[i][j];  
        }
        scor_vechi = *scor_resume;  
        mutare_jos(aux, scor_resume, testare);  
        wrefresh(continuare);
        afisaretabla(aux, continuare);  
        wrefresh(continuare);
        afisare_scor(panoudecontrol, scor_resume);  
        game_over(aux, panoudecontrol);             
        winner(panoudecontrol, aux);                
        wrefresh(panoudecontrol);  
        wclear(continuare);
        break;
      case KEY_LEFT:
        box(continuare, 0, 0);
        wrefresh(continuare);
        chenar(continuare);  
        for (i = 0; i < 4; i++) {
          for (j = 0; j < 4; j++)
            tabla_veche[i][j] =
                aux[i][j];  
        }
        scor_vechi = *scor;  
        mutare_stanga(aux, scor_resume, testare);  
        wrefresh(continuare);
        afisaretabla(aux, continuare);  
        wrefresh(continuare);
        afisare_scor(panoudecontrol, scor_resume);  
        game_over(aux, panoudecontrol);             
        winner(panoudecontrol, aux);                
        wrefresh(panoudecontrol);  
        wclear(continuare);
        break;
      case KEY_RIGHT:
        box(continuare, 0, 0);
        wrefresh(continuare);
        chenar(continuare);  
        for (i = 0; i < 4; i++) {
          for (j = 0; j < 4; j++)
            tabla_veche[i][j] =
                aux[i][j];  
        }
        scor_vechi = *scor_resume;  
        mutare_dreapta(aux, scor_resume,
                       testare);  
        wrefresh(continuare);
        afisaretabla(aux, continuare);  
        wrefresh(continuare);
        afisare_scor(panoudecontrol, scor_resume);  
        game_over(aux, panoudecontrol);             
        winner(panoudecontrol, aux);                
        wrefresh(panoudecontrol);  
        wclear(continuare);
        break;
      case 'u':
        box(continuare, 0, 0);
        chenar(continuare);  
        undo(aux, scor_resume, tabla_veche, &scor_vechi);
        afisaretabla(aux, continuare);  
        wrefresh(continuare);
        afisare_scor(panoudecontrol, scor_resume);  
        wrefresh(panoudecontrol);
        wclear(continuare);
        break;
      case 'q':
        iesiri++;
        keypad(continuare, false);
        break;
      default:
        break;
    }
    if (iesiri > 0) {  
      wclear(continuare);
      wrefresh(continuare);
      wclear(panoudecontrol);
      wrefresh(panoudecontrol);
      wclear(panoudecontrol);
      wrefresh(panoudecontrol);
      color_box(meniu);
      wrefresh(meniu);
      break;
    }
  }
}
int main() {
  int tabla[4][4] = {0}, scor = 0;
  int aux[4][4] = {0}, scor_resume = 0;
  initscr();    
  noecho();     
  cbreak();     
  curs_set(0);  

  int ymax, xmax;
  getmaxyx(stdscr, ymax, xmax);  

  start_color();  
  init_pair(1, COLOR_CYAN, COLOR_WHITE);
  init_pair(2, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(3, COLOR_WHITE, COLOR_BLACK);
  init_pair(4, COLOR_RED, COLOR_BLACK);
  init_pair(5, COLOR_GREEN, COLOR_BLACK);
  init_pair(6, COLOR_YELLOW, COLOR_BLACK);
  init_pair(7, COLOR_CYAN, COLOR_BLACK);
  init_pair(8, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(9, COLOR_BLACK, COLOR_BLACK);

  WINDOW *meniu =
      newwin(11, 28, (ymax / 2) - (linii / 2),
             (xmax / 2) - (coloane / 2) + 2);  
  wbkgd(meniu, COLOR_PAIR(8));
  refresh();
  wattron(meniu, COLOR_PAIR(8));
  box(meniu, 0, 0);
  wattroff(meniu, COLOR_PAIR(8));
  wrefresh(meniu);
  keypad(meniu, true);

  char optiuni[3][20] = {"New Game", "Resume", "Quit"};  
  int optiune, ales = 0;

  WINDOW *jocnou =
      newwin(11, 28, (ymax / 2) - (linii / 2),
             (xmax / 2) - (coloane / 2) + 2);  
  color_box(jocnou);
  WINDOW *panoudecontrol =
      newwin(7, 34, 3, 26);  
  WINDOW *continuare =
      newwin(11, 28, (ymax / 2) - (linii / 2),
             (xmax / 2) - (coloane / 2) + 2);  
  color_box(continuare);
  wattron(meniu, COLOR_PAIR(8));
  mvwprintw(meniu, 1, 1.5, "   ___   ___   ____  ___ ");
  mvwprintw(meniu, 2, 1.5, "  |_  | / _ / / /   ( _  )");
  mvwprintw(meniu, 3, 1.5, " / __/ / /// /_  _// _  | ");
  mvwprintw(meniu, 4, 1.5, "/____/  __/  /_/    ___/ ");
  wattroff(meniu, COLOR_PAIR(8));

  int i;
  while (1) {  
    for (i = 0; i < 3; i++) {
      if (i == ales)
        wattron(meniu, COLOR_PAIR(8) | A_REVERSE);  
      mvwprintw(meniu, i + 6, 11, "%s", optiuni[i]);  
      wattroff(meniu, COLOR_PAIR(8) | A_REVERSE);
    }

    optiune = wgetch(meniu);  

    switch (optiune) {  
      case KEY_UP:
        ales--;
        if (ales == -1) ales = 0;
        break;
      case KEY_DOWN:
        ales++;
        if (ales == 3) ales = 2;
        break;
      case 10:           
        switch (ales) {  
          case 0:        
            newgame(jocnou, panoudecontrol, meniu, tabla, aux, &scor,
                    &scor_resume);
            break;
          case 1:  
            resume(continuare, panoudecontrol, meniu, aux, &scor_resume, tabla,
                   &scor);
            break;
          case 2:  
            endwin();
            return 0;
            break;
        }
        break;
      default:
        break;
    }
    wrefresh(meniu);
  }

  getch();
  endwin();  

  return 0;
}

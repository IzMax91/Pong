#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int player1 = 12, player2 = 12;

int game_mechanics(int ball_x, int ball_y, int score_player_1,
                   int score_player_2);
int field(int coordinates_p1, int coordinates_p2, int ball_x, int ball_y,
          int score_player_1, int score_player_2);
int the_end(char player);
void* control();

int main() {
  void* thread_data = NULL;
  pthread_t thread;
  pthread_create(&thread, NULL, control, thread_data);

  int score_player_1 = 0, score_player_2 = 0;
  int ball_x = 38, ball_y = 12;

  the_end(game_mechanics(ball_x, ball_y, score_player_1, score_player_2));
}

void* control() {
  system("stty -icanon -echo");

  while (1) {
    char ent = getchar();
    if (ent == 'a' && player1 != 1)  // player1
      player1 -= 1;
    else if (ent == 'z' && player1 != 21)
      player1 += 1;

    if (ent == 'k' && player2 != 1)  // player2
      player2 -= 1;
    else if (ent == 'm' && player2 != 21)
      player2 += 1;
  }
}

int game_mechanics(int ball_x, int ball_y, int score_player_1,
                   int score_player_2) {
  int victory;
  int game = 1;
  int up = 0;
  int down = 1;
  int left = 1;
  int right = 0;

  while (game) {
    field(player1, player2, ball_x, ball_y, score_player_1, score_player_2);

    usleep(50000);

    // ball change of direction
    if (ball_y == 1) {
      up = 0;
      down = 1;
    }
    if (ball_y == 23) {
      up = 1;
      down = 0;
    }

    for (int i = -1; i < 4; i++) {
      if (ball_x == 3 && ball_y == player1 + i) {
        left = 0;
        right = 1;
      }
    }

    for (int i = -1; i < 4; i++) {
      if (ball_x == 76 && ball_y == player2 + i) {
        left = 1;
        right = 0;
      }
    }

    // ball movement
    if (up) ball_y--;
    if (down) ball_y++;
    if (left) ball_x--;
    if (right) ball_x++;

    // Goal
    if (ball_x == 1) {
      score_player_2++;
      ball_x = 38;
      ball_y = 12;
    }
    if (ball_x == 79) {
      score_player_1++;
      ball_x = 38;
      ball_y = 12;
    }

    for (int i = 0; i < 30; i++) {
      printf("\n");
    }

    if (score_player_1 == 24) {
      victory = 1;
      game = 0;
    }
    if (score_player_2 == 24) {
      victory = 2;
      game = 0;
    }
  }
  return victory;
}

int field(int coordinates_p1, int coordinates_p2, int ball_x, int ball_y,
          int score_player_1, int score_player_2) {
  printf("LEFT PLAYER: %d, RIGHT PLAYER: %d\n\n", score_player_1,
         score_player_2);

  char pixel = '#';
  char pixel_player = '|';
  char pixel_ball = '@';
  int label_p1 = coordinates_p1;
  int label_p2 = coordinates_p2;

  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 80; j++) {
      if (i == 0 || i == 24 || j == 0 || j == 79)
        printf("%c", pixel);

      else if (j == ball_x && i == ball_y)
        printf("%c", pixel_ball);  // ball

      else if (j == 2 && label_p1 == i) {  // player1
        if (label_p1 - coordinates_p1 != 2) {
          label_p1 += 1;
        }
        printf("%c", pixel_player);
      }

      else if (j == 77 && label_p2 == i) {  // player2
        if (label_p2 - coordinates_p2 != 2) {
          label_p2 += 1;
        }
        printf("%c", pixel_player);
      }

      else {
        printf(" ");
      }
    }
    printf("\n");
  }

  return 0;
}

int the_end(char player) {
  printf("\t\t╔═╗───────╔╗     ─────────╔╗─\n");
  printf("\t\t║╬║╔═╗╔═╗╔╝║     ╔╗─╔╦╗╔═╗║╠╗\n");
  printf("\t\t╠╗║║╬║║╬║║╬║     ║╚╗║║║║═╣║═╣\n");
  printf("\t\t╚═╝╚═╝╚═╝╚═╝     ╚═╝╚═╝╚═╝╚╩╝\n");

  for (int i = 0; i < 14; i++) {
    printf("\n");
  }

  return 0;
}
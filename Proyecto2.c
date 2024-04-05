#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLUMNAS 8
#define FILAS 8

//! Funciones protótipo
void InicioJuego(int jugadores);
void Impresion(int tablero[][COLUMNAS]);
void MenuInicio();
void ClearScreen();
void AcomodarBarcos(int tablero1[][COLUMNAS], int tablero2[][COLUMNAS],
                    int tableroPrincipal[][COLUMNAS], int jugadores);
int ValidarNumero(int numero);
int ValidarLetra(char letra);
int letraAIndice(char letra);
void SolicitarEntrada(int *entrada1, int *entrada2);
void SolicitarOrientacion(int *orientacion);
void EstablecerBarcos(int tablero[][COLUMNAS], int orientacion, int entrada1,
                      int entrada2);
void InicializarTablero(int tableroJuego[FILAS][COLUMNAS]);
int ValidarOrientacion(int orientacion);
int VerificadorDeColisiones(int tablero1[][COLUMNAS], int tablero2[][COLUMNAS],
                            int jugador, int orientacion, int entrada1,
                            int entrada2);

void Acomodo_IA(int tablero1[][COLUMNAS], int tablero2[][COLUMNAS],
                int tableroPrincipal[][COLUMNAS]);
void Disparo(int tablero1[][COLUMNAS], int tablero2[][COLUMNAS],
             int tableroPrincipal[][COLUMNAS], int jugador);
void Juego(int tablero1[][COLUMNAS], int tablero2[][COLUMNAS],
           int tableroPrincipal[][COLUMNAS], int jugadores);
void Disparo_IA(int tablero[][COLUMNAS], int tableroPrincipal[][COLUMNAS]);
char IndiceALetra(int indice);

// int disparo_IA(int tablero[][COLUMNAS]);

void ClearScreen() {
  for (int i = 0; i < 100; i++) {
    printf("\n");
  }
}

int ValidarNumero(int numero) {
  if (numero >= 1 && numero <= 7) {
    return 1;
  } else {
    printf("\nNúmero inválido. Por favor, ingresa un número entre 1 y 7.\n");
    return 0;
  }
}

int ValidarLetra(char letra) {
  letra = toupper(letra);
  if (letra >= 'A' && letra <= 'G') {
    return 1;
  } else {
    printf("\nLetra inválida. Por favor, ingresa una letra entre A y F.\n");
    return 0;
  }
}

// Función para convertir una letra a su correspondiente índice en el tablero
int letraAIndice(char letra) { return toupper(letra) - 'A' + 1; }

void Disparo(int tablero1[][COLUMNAS], int tablero2[][COLUMNAS],
             int tableroPrincipal[][COLUMNAS], int jugador) {
  int entrada1, entrada2;
  printf("Jugador %d es tu turno de atacar...\n", jugador);
  SolicitarEntrada(&entrada1, &entrada2);
  if (jugador == 1) {
    if (tablero2[entrada1][entrada2] == 'X') {
      printf("Atinaste!!\n");
      tableroPrincipal[entrada1][entrada2] = 'H';
      tablero1[entrada1][entrada2] = 'H';
    } else {
      printf("Agua!\n");
      tableroPrincipal[entrada1][entrada2] = 'M';
      tablero1[entrada1][entrada2] = 'M';
    }
  } else if (jugador == 2) {
    if (tablero1[entrada1][entrada2] == 'X') {
      printf("Atinaste!!\n");
      tableroPrincipal[entrada1][entrada2] = 'H';
      tablero2[entrada1][entrada2] = 'H';
    } else {
      printf("Agua!\n");
      tableroPrincipal[entrada1][entrada2] = 'M';
      tablero2[entrada1][entrada2] = 'M';
    }
  }
}

// Funcion para acomodar barcos de la IA
void Acomodo_IA(int tablero1[][COLUMNAS], int tablero2[][COLUMNAS],
                int tableroPrincipal[][COLUMNAS]) {
  srand(time(NULL));
  int orientacion;
  int entrada1, entrada2;
  int barcos = 3;
  while (barcos > 0) {
    orientacion = rand() % 2 + 1;
    entrada1 = rand() % 6 + 1;
    entrada2 = rand() % 6 + 1;
    if (VerificadorDeColisiones(tablero1, tablero2, 2, orientacion, entrada1,
                                entrada2)) {
      EstablecerBarcos(tablero2, orientacion, entrada1,
                       entrada2); // Cambiado de tablero2 a tablero1
      barcos--;
    }
  }
}

// Funcion para solicitar entrada
void SolicitarEntrada(int *entrada1, int *entrada2) {
  char letra;
  int numero;
  do {
    printf("En que coordenada lo quieres? (x-y)\n");
    fflush(stdin);
    scanf("%c-%d", &letra, &numero);
  } while (!ValidarLetra(letra) || !ValidarNumero(numero));
  *entrada1 = letraAIndice(letra);
  *entrada2 = numero;
}

void InicializarTablero(int tableroJuego[FILAS][COLUMNAS]) {
  for (int i = 0; i < FILAS; i++) {
    for (int j = 0; j < COLUMNAS; j++) {
      if (i == 0 && j == 0) {
        tableroJuego[i][j] = 32; // Espacio en blanco en ASCII
      } else if (i == 0 && j > 0) {
        tableroJuego[i][j] = '0' + j; // Números del encabezado
      } else if (j == 0 && i > 0) {
        tableroJuego[i][j] = 'A' + i - 1; // Letras del encabezado
      } else {
        tableroJuego[i][j] = '0'; // Espacio en blanco
      }
    }
  }
}

int ValidarOrientacion(int orientacion) {
  if (orientacion == 1 || orientacion == 2) {
    return 1;
  } else {
    printf("\nOrientación inválida. Por favor, ingresa 1 o 2.\n");
    return 0;
  }
}

void SolicitarOrientacion(int *orientacion) {
  printf("En que orientacion lo quieres? (1.- Horizontal, 2.- Vertical)\n");
  scanf("%d", orientacion);
  while (!ValidarOrientacion(*orientacion)) {
    scanf("%d", orientacion);
  }
}

void EstablecerBarcos(int tablero[][COLUMNAS], int orientacion, int entrada1,
                      int entrada2) {
  switch (orientacion) {
  case 1:
    tablero[entrada1][entrada2] = 'X';
    tablero[entrada1][entrada2 + 1] = 'X';
    tablero[entrada1][entrada2 + 2] = 'X';
    break;
  case 2:
    tablero[entrada1][entrada2] = 'X';
    tablero[entrada1 + 1][entrada2] = 'X';
    tablero[entrada1 + 2][entrada2] = 'X';
    break;
  default:
    break;
  }
}

void AcomodarBarcos(int tablero1[][COLUMNAS], int tablero2[][COLUMNAS],
                    int tableroPrincipal[][COLUMNAS], int jugadores) {
  for (int jugador = 1; jugador <= jugadores; jugador++) {
    int barcos = 3;
    int orientacion;
    int entrada1, entrada2;

    printf("Jugador %d es tu turno de acomodar Barcos\n", jugador);
    printf("Tienes 3 Barcos por acomodar de tamaños (3-3-3)\n");

    while (barcos > 0) {
      printf("Acomodando barco %d ...Como quieres que este?\n", barcos);
      SolicitarOrientacion(&orientacion);
      SolicitarEntrada(&entrada1, &entrada2);
      if (jugador == 1) {
        if (VerificadorDeColisiones(tablero1, tablero2, jugador, orientacion,
                                    entrada1, entrada2)) {
          EstablecerBarcos(tablero1, orientacion, entrada1, entrada2);
          EstablecerBarcos(tableroPrincipal, orientacion, entrada1, entrada2);
          barcos--;
        }
      } else {
        if (VerificadorDeColisiones(tablero2, tablero1, jugador, orientacion,
                                    entrada1, entrada2)) {
          EstablecerBarcos(tablero2, orientacion, entrada1, entrada2);
          EstablecerBarcos(tableroPrincipal, orientacion, entrada1, entrada2);

          barcos--;
        }
      }
    }
  }
}

int VerificadorDeColisiones(int tablero1[][COLUMNAS], int tablero2[][COLUMNAS],
                            int jugador, int orientacion, int entrada1,
                            int entrada2) {
  int(*tablero)[COLUMNAS];
  int(*otroTablero)[COLUMNAS];
  if (jugador == 1) {
    tablero = tablero1;
    otroTablero = tablero2;
  } else {
    tablero = tablero2;
    otroTablero = tablero1;
  }

  switch (orientacion) {
  case 1:
    if (entrada2 + 2 >= COLUMNAS || tablero[entrada1][entrada2] == 'X' ||
        tablero[entrada1][entrada2 + 1] == 'X' ||
        tablero[entrada1][entrada2 + 2] == 'X' ||
        otroTablero[entrada1][entrada2] == 'X' ||
        otroTablero[entrada1][entrada2 + 1] == 'X' ||
        otroTablero[entrada1][entrada2 + 2] == 'X') {
      if (jugador == 1) {
        printf(
            "Colisión detectada o barco fuera del tablero. Por favor, ingresa "
            "otra coordenada.\n");
      }
      return 0;
    }
    break;
  case 2:
    if (entrada1 + 2 >= FILAS || tablero[entrada1][entrada2] == 'X' ||
        tablero[entrada1 + 1][entrada2] == 'X' ||
        tablero[entrada1 + 2][entrada2] == 'X' ||
        otroTablero[entrada1][entrada2] == 'X' ||
        otroTablero[entrada1 + 1][entrada2] == 'X' ||
        otroTablero[entrada1 + 2][entrada2] == 'X') {
      if (jugador == 1) {
        printf(
            "Colisión detectada o barco fuera del tablero. Por favor, ingresa "
            "otra coordenada.\n");
      }
      return 0;
    }
    break;
  default:
    break;
  }
  return 1;
}

char IndiceALetra(int indice) { return 'A' + indice - 1; }

void Disparo_IA(int tablero[][COLUMNAS], int tableroPrincipal[][COLUMNAS]) {
  int entrada1, entrada2;
  printf("Es el turno de la IA de atacar...\n");
  entrada1 = rand() % 6 + 1;
  entrada2 = rand() % 6 + 1;
  if (tablero[entrada1][entrada2] == 'X') {
    printf("La IA atinó en las coordenadas (%c %d)!!\n", IndiceALetra(entrada1),
           entrada2);
    tableroPrincipal[entrada1][entrada2] = 'H';
  } else {
    printf("La IA falló en las coordenadas (%c, %d)!!\n",
           IndiceALetra(entrada1), entrada2);
    tableroPrincipal[entrada1][entrada2] = 'M';
  }
}

void Juego(int tablero1[][COLUMNAS], int tablero2[][COLUMNAS],
           int tableroPrincipal[][COLUMNAS], int jugadores) {
  int turno = 0; // 0 para el jugador 1, 1 para el jugador 2 (IA)
  while (1) {
    if (turno == 0) {
      Disparo(tablero1, tablero2, tableroPrincipal, 1);
      Impresion(tableroPrincipal);
    } else if (jugadores == 2) {
      Disparo(tablero1, tablero2, tableroPrincipal, 2);
      Impresion(tablero2);
    } else {
      Disparo_IA(tablero1, tableroPrincipal);
      Impresion(tableroPrincipal);
    }

    // Cambiar el turno
    turno = 1 - turno;
  }
}
// Funcion para imprimir tablero
void Impresion(int tablero[][COLUMNAS]) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      printf("\t%c", tablero[i][j]);
    }
    printf("\n");
  }
}

// Funcion para iniciar el juego
void InicioJuego(int jugadores) {
  int tableroJuego[FILAS][COLUMNAS];
  int tableroJuego2[FILAS][COLUMNAS];
  int tableroPrincipal[FILAS][COLUMNAS];
  InicializarTablero(tableroPrincipal);
  AcomodarBarcos(tableroJuego, tableroJuego2, tableroPrincipal, jugadores);
  Impresion(tableroPrincipal);
  if (jugadores == 1) {
    Acomodo_IA(tableroJuego, tableroJuego2, tableroPrincipal);
  }
  Impresion(tableroJuego2);
  Juego(tableroJuego, tableroJuego2, tableroPrincipal, jugadores);
}

// Funcion para menu
void MenuInicio() {
  int jugadores = 0;
  int opcion;
  printf("Bievenido BattleChip !!!\n");
  printf("Elige tu opción:\n");
  printf("1.- Jugador vs AI\n");
  printf("2.- Jugador vs Jugador\n");
  printf("3.- Salir\n");
  while (opcion != 3) {
    scanf("%d", &opcion);
    switch (opcion) {
    case 1:
      InicioJuego(jugadores = 1);
      break;
    case 2:
      InicioJuego(jugadores = 2);
      break;
    case 3:
      printf("Gracias por jugar\n");
      exit(0);
      break;
    default:
      printf("Opción no valida\n");
      break;
    }
  }
}

//! Funcion principal
int main() {
  ClearScreen();
  MenuInicio();
  return 0;
}
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
                    int jugadores);
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
// int disparo_IA(int tablero[][COLUMNAS]);

//! Funcion principal
int main() {
  ClearScreen();
  MenuInicio();
  return 0;
}

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
                    int jugadores) {

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
          barcos--;
        }
      } else {
        if (VerificadorDeColisiones(tablero1, tablero2, jugador, orientacion,
                                    entrada1, entrada2)) {
          EstablecerBarcos(tablero1, orientacion, entrada1, entrada2);
          barcos--;
        }
      }
    }
  }
}

// // Funcion para disparar
// int disparo_IA(int tablero[][COLUMNAS]) {
//   int numero = 0;
//   int letra = 0;
//   srand(time(NULL));
//   numero = (1 + rand() % 6);
//   letra = (1 + rand() % 6);
//   printf("%d,%d\n", numero, letra);
//   tablero[numero][letra] = 88;
//   if (tablero[numero][letra] == 254) {
//     tablero[numero][letra] = 42;
//   }
// }

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
      printf("Colisión detectada o barco fuera del tablero. Por favor, ingresa "
             "otra coordenada.\n");
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
      printf("Colisión detectada o barco fuera del tablero. Por favor, ingresa "
             "otra coordenada.\n");
      return 0;
    }
    break;
  default:
    break;
  }
  return 1;
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
  InicializarTablero(tableroJuego);
  Impresion(tableroJuego);
  AcomodarBarcos(tableroJuego, tableroJuego2, jugadores);
  Impresion(tableroJuego);
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
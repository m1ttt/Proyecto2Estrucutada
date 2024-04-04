#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//! Funciones protótipo
int tablero();
int entradas(int tablero[][7]);
int disparo_IA(int tablero[][7]);
int impresion(int tablero[][7]);
int vertical(int tablero[][7], int barcos);
void MenuInicio();
void ClearScreen();
int validarNumero(int numero);
int validarLetra(char letra);

//! Funcion principal
int main() {
  ClearScreen();
  MenuInicio();
  tablero();
  return 0;
}

void ClearScreen() {
  for (int i = 0; i < 100; i++) {
    printf("\n");
  }
}

int validarNumero(int numero) {
  if (numero >= 1 && numero <= 7) {
    return 1;
  } else {
    printf("Número inválido. Por favor, ingresa un número entre 1 y 7.\n");
    return 0;
  }
}

int validarLetra(char letra) {
  letra = toupper(letra);
  if (letra >= 'A' && letra <= 'F') {
    return 1;
  } else {
    printf("Letra inválida. Por favor, ingresa una letra entre A y F.\n");
    return 0;
  }
}

// Funcion para generar tablero
int tablero() {
  int tableroJuego[7][7];
  char numero = 6;
  char letra = 64;
  for (int indiceLetra = 0; indiceLetra < 7; indiceLetra++) {
    for (int indiceNumero = 0; indiceNumero < 7; indiceNumero++) {
      tableroJuego[indiceLetra][indiceNumero] = 48;
      tableroJuego[0][indiceLetra] = letra;
      tableroJuego[indiceNumero][0] = numero;
      tableroJuego[0][0] = 32;
      numero++;
    }
    letra++;
  }
  entradas(tableroJuego);
  printf("ataque\n");
  int cantidadDisparos = 0;
  while (cantidadDisparos < 2) {
    disparo_IA(tableroJuego);
    cantidadDisparos++;
  }
  impresion(tableroJuego);
}

// Funcion para ingresar barcos
int entradas(int tablero[][7]) {
  int barcos = 0;
  char entrada1 = 0;
  int entrada2 = 0;
  int direccion = 0;
  while (barcos < 3) {
    switch (barcos) {
    case 0:
      printf("Ingresa el barco de una casilla\n");
      printf("La letra:");
      fflush(stdin);
      scanf("%c", &entrada1);
      while (!validarLetra(entrada1)) {
        printf("La letra:");
        fflush(stdin);
        scanf("%c", &entrada1);
      }
      entrada1 = toupper(entrada1);
      printf("El numero:");
      scanf("%d", &entrada2);
      while (!validarNumero(entrada2)) {
        printf("El numero:");
        scanf("%d", &entrada2);
      }
      switch (entrada1) {
      case 'A':
        entrada1 = 1;
        break;
      case 'B':
        entrada1 = 2;
        break;
      case 'C':
        entrada1 = 3;
        break;
      case 'D':
        entrada1 = 4;
        break;
      case 'E':
        entrada1 = 5;
        break;
      case 'F':
        entrada1 = 6;
        break;
      }
      tablero[entrada2][entrada1] = 254;
      impresion(tablero);
      break;
    case 1:
      direccion = 0;
      printf("Ingreso del barco de dos casillas\n");
      // printf("El barco sera Vertical o Horizontal?:\n");
      // scanf("%d", direccion);
      vertical(tablero, barcos);
      break;
    case 2:
      printf("Ingresa el barco de tres casillas\n");
      printf("Primera letra:");
      scanf("%c", &entrada1);
      while (!validarLetra(entrada1)) {
        printf("Primera letra:");
        fflush(stdin);
        scanf("%c", &entrada1);
      }
      entrada1 = toupper(entrada1);
      printf("Primer numero:");
      scanf("%d", &entrada2);
      while (!validarNumero(entrada2)) {
        printf("Primer numero:");
        scanf("%d", &entrada2);
      }
      tablero[entrada1][entrada2] = 254;
      impresion(tablero);

      printf("Segunda letra:");
      scanf("%c", &entrada1);
      while (!validarLetra(entrada1)) {
        printf("Segunda letra:");
        fflush(stdin);
        scanf("%c", &entrada1);
      }
      entrada1 = toupper(entrada1);
      printf("Segundo numero:");
      scanf("%d", &entrada2);
      while (!validarNumero(entrada2)) {
        printf("Segundo numero:");
        scanf("%d", &entrada2);
      }
      tablero[entrada1][entrada2] = 254;
      impresion(tablero);

      printf("Tercera letra letra:");
      scanf("%c", &entrada1);
      while (!validarLetra(entrada1)) {
        printf("Tercera letra:");
        fflush(stdin);
        scanf("%c", &entrada1);
      }
      entrada1 = toupper(entrada1);
      printf("Tercer numero:");
      scanf("%d", &entrada2);
      while (!validarNumero(entrada2)) {
        printf("Tercer numero:");
        scanf("%d", &entrada2);
      }
      tablero[entrada1][entrada2] = 254;
      impresion(tablero);
      break;

    default:
      break;
    }
    barcos++;
  }
}

// Funcion para ingresar barcos verticales
int vertical(int tablero[][7], int barcos) {
  char entrada1a = 0;
  int entrada2a = 0;
  char entrada3 = 0;
  int entrada4 = 0;
  printf("Primera letra:");
  scanf("%c", &entrada1a);
  while (!validarLetra(entrada1a)) {
    printf("Primera letra:");
    fflush(stdin);
    scanf("%c", &entrada1a);
  }
  entrada1a = toupper(entrada1a);
  printf("Primer numero:");
  scanf("%d", &entrada2a);
  while (!validarNumero(entrada2a)) {
    printf("Primer numero:");
    scanf("%d", &entrada2a);
  }
  if (tablero[entrada1a][entrada2a] == 254) {
    printf("Lo siento, la posicion no es correcta:\n");
    printf("Primera letra:");
    scanf("%c", &entrada1a);
    while (!validarLetra(entrada1a)) {
      printf("Primera letra:");
      fflush(stdin);
      scanf("%c", &entrada1a);
    }
    entrada1a = toupper(entrada1a);
    printf("Primer numero:");
    scanf("%d", &entrada2a);
    while (!validarNumero(entrada2a)) {
      printf("Primer numero:");
      scanf("%d", &entrada2a);
    }
  }
  tablero[entrada1a][entrada2a] = 254;
  switch (barcos) {
  case 1:
    printf("Segunda letra:");
    scanf("%c", &entrada3);
    while (!validarLetra(entrada3)) {
      printf("Segunda letra:");
      fflush(stdin);
      scanf("%c", &entrada3);
    }
    entrada3 = toupper(entrada3);
    printf("Segundo numero:");
    scanf("%d", &entrada4);
    while (!validarNumero(entrada4)) {
      printf("Segundo numero:");
      scanf("%d", &entrada4);
    }
    while ((entrada3 != entrada1a && entrada4 != entrada2a + 1) ||
           (entrada3 != entrada1a && entrada4 != entrada2a - 1)) {
      printf("Lo siento, la posicion no es correcta:");
      printf("Segunda letra:");
      scanf("%c", &entrada1a);
      while (!validarLetra(entrada1a)) {
        printf("Segunda letra:");
        fflush(stdin);
        scanf("%c", &entrada1a);
      }
      entrada1a = toupper(entrada1a);
      printf("Segundo numero:");
      scanf("%d", &entrada2a);
      while (!validarNumero(entrada2a)) {
        printf("Segundo numero:");
        scanf("%d", &entrada2a);
      }
      impresion(tablero);
    }
    tablero[entrada1a][entrada2a] = 254;
    tablero[entrada3][entrada4] = 254;
    break;
  case 2:
    printf("Segunda letra:");
    scanf("%c", &entrada3);
    while (!validarLetra(entrada3)) {
      printf("Segunda letra:");
      fflush(stdin);
      scanf("%c", &entrada3);
    }
    entrada3 = toupper(entrada3);
    printf("Segundo numero:");
    scanf("%d", &entrada4);
    while (!validarNumero(entrada4)) {
      printf("Segundo numero:");
      scanf("%d", &entrada4);
    }
    while ((entrada3 != entrada1a && entrada4 != entrada2a + 1) ||
           (entrada3 != entrada1a && entrada4 != entrada2a - 1)) {
      printf("Lo siento, la posicion no es correcta:");
      printf("Segunda letra:");
      scanf("%c", &entrada1a);
      while (!validarLetra(entrada1a)) {
        printf("Segunda letra:");
        fflush(stdin);
        scanf("%c", &entrada1a);
      }
      entrada1a = toupper(entrada1a);
      printf("Segundo numero:");
      scanf("%d", &entrada2a);
      while (!validarNumero(entrada2a)) {
        printf("Segundo numero:");
        scanf("%d", &entrada2a);
      }
      tablero[entrada1a][entrada2a] = 254;
      impresion(tablero);
    }
    tablero[entrada3][entrada4] = 254;

    printf("Tercera letra:");
    scanf("%c", &entrada1a);
    while (!validarLetra(entrada1a)) {
      printf("Tercera letra:");
      fflush(stdin);
      scanf("%c", &entrada1a);
    }
    entrada1a = toupper(entrada1a);
    printf("Tercer numero:");
    scanf("%d", &entrada2a);
    while (!validarNumero(entrada2a)) {
      printf("Tercer numero:");
      scanf("%d", &entrada2a);
    }
    while ((entrada1a != entrada3 && entrada2a != entrada4 + 1) ||
           (entrada1a != entrada3 && entrada2a != entrada4 - 1)) {
      printf("Lo siento, la posicion no es correcta:");
      printf("Tercera letra:");
      scanf("%c", &entrada1a);
      while (!validarLetra(entrada1a)) {
        printf("Tercera letra:");
        fflush(stdin);
        scanf("%c", &entrada1a);
      }
      entrada1a = toupper(entrada1a);
      printf("Tercer numero:");
      scanf("%d", &entrada2a);
      while (!validarNumero(entrada2a)) {
        printf("Tercer numero:");
        scanf("%d", &entrada2a);
      }
      tablero[entrada1a][entrada2a] = 254;
      impresion(tablero);
    }
    tablero[entrada1a][entrada2a] = 254;
    break;
  default:
    break;
  }
}

// Funcion para disparar
int disparo_IA(int tablero[][7]) {
  int numero = 0;
  int letra = 0;
  srand(time(NULL));
  numero = (1 + rand() % 6);
  letra = (1 + rand() % 6);
  printf("%d,%d\n", numero, letra);
  tablero[numero][letra] = 88;
  if (tablero[numero][letra] == 254) {
    tablero[numero][letra] = 42;
  }
}

// Funcion para imprimir tablero
int impresion(int tablero[][7]) {
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      printf("\t%c", tablero[j][i]);
    }
    printf("\n");
  }
}

// Funcion para menu
void MenuInicio() {
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
      tablero();
      break;
    case 2:
      // tablero();
      break;
    case 3:
      printf("Gracias por jugar\n");
      break;
    default:
      printf("Opción no valida\n");
      break;
    }
  }
}
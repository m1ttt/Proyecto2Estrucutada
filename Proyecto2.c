#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

int tablero();
int entradas (int tablero [][7]);
int disparo_IA (int tablero [][7]);
int impresion(int tablero [][7]);
int vertical (int tablero [][7], int barcos);
int main()
{
 tablero();
return 0;
}

int tablero()
{
 
int tablero[7][7];
char nm=6;
char lt=64;
for (int let= 0; let < 7; let++)
{
   for (int num = 0; num < 7; num++)
   {
    tablero [let][num]=48;
    tablero [0][let]=lt;
    tablero [num][0]=nm;
    tablero[0][0]=32;
    nm++;
   }
   lt++;
} 
entradas(tablero);
printf ("ataque\n");
char disparos=0;
while (disparos<2)
{
  disparo_IA(tablero);
  disparos++;
}
impresion(tablero);
}

int entradas (int tablero [][7])
{
int barcos=0;
int entrada1=0;
int entrada2=0;
int direccion=0;
while (barcos<3)
{
  switch (barcos)
  {
  case 0:
  printf("ingresa el barco de una casilla\n");
  printf("La letra:");
  scanf("%d", &entrada1);
  printf("El numero:");
  scanf("%d", &entrada2);
  tablero[entrada1][entrada2]=254;
  impresion(tablero);
  break;
  case 1:
  direccion=0;
  printf("Ingreso del barco de dos casillas\n");
  //printf("El barco sera Vertical o Horizontal?:\n");
  //scanf("%d", direccion);
  vertical(tablero, barcos);
  break;
  case 2:
  printf("Ingresa el barco de tres casillas\n");
  printf("Primera letra:");
  scanf("%d", &entrada1);
  printf("Primer numero:");
  scanf("%d", &entrada2);
  tablero[entrada1][entrada2]=254;
  impresion(tablero);

  printf("Segunda letra:");
  scanf("%d", &entrada1);
  printf("Segundo numero:");
  scanf("%d", &entrada2);
  tablero[entrada1][entrada2]=254;
  impresion(tablero);

  printf("Tercera letra letra:");
  scanf("%d", &entrada1);
  printf("Tercer numero:");
  scanf("%d", &entrada2);
  tablero[entrada1][entrada2]=254;
  impresion(tablero);
  break;

  default:
  break;
}
barcos++;
}
}
int vertical (int tablero [][7], int barcos)
{
int entrada1a=0;
int entrada2a=0;
int entrada3=0;
int entrada4=0;
printf("Primera letra:");
scanf("%d", &entrada1a);
printf("Primer numero:");
scanf("%d", &entrada2a);
if(tablero[entrada1a][entrada2a]=254)
{
  printf("Lo siento, la posicion no es correcta:\n");
  printf("Primera letra:");
  scanf("%d", &entrada1a);
  printf("Primer numero:");
  scanf("%d", &entrada2a);
}
tablero[entrada1a][entrada2a]=254;
switch (barcos)
{
case 1:
printf("Segunda letra:");
scanf("%d", &entrada3);
printf("Segundo numero:");
scanf("%d", &entrada4);
while ((entrada3!=entrada1a && entrada4!=entrada2a+1)||(entrada3!=entrada1a && entrada4!=entrada2a-1))
{
printf("Lo siento, la posicion no es correcta:");
printf("Segunda letra:");
scanf("%d", &entrada1a);
printf("Segundo numero:");
scanf("%d", &entrada2a);
impresion(tablero);
}
tablero[entrada1a][entrada2a]=254;
tablero[entrada3][entrada4]=254;
break;
case 2:
printf("Segunda letra:");
scanf("%d", &entrada3);
printf("Segundo numero:");
scanf("%d", &entrada4);
while ((entrada3!=entrada1a && entrada4!=entrada2a+1)||(entrada3!=entrada1a && entrada4!=entrada2a-1))
{
printf("Lo siento, la posicion no es correcta:");
printf("Segunda letra:");
scanf("%d", &entrada1a);
printf("Segundo numero:");
scanf("%d", &entrada2a);
tablero[entrada1a][entrada2a]=254;
impresion(tablero);
}
tablero[entrada3][entrada4]=254;

printf("Tercera letra:");
scanf("%d", &entrada1a);
printf("Tercer numero:");
scanf("%d", &entrada2a);
while ((entrada1a!=entrada3 && entrada2a!=entrada4+1)||(entrada1a!=entrada3 && entrada2a!=entrada4-1))
{
printf("Lo siento, la posicion no es correcta:");
printf("Tercera letra:");
scanf("%d", &entrada1a);
printf("Tercer numero:");
scanf("%d", &entrada2a);
tablero[entrada1a][entrada2a]=254;
impresion(tablero);
}
tablero[entrada1a][entrada2a]=254;
break;
default:
  break;
}

}
int disparo_IA (int tablero [][7])
{
  int numero=0;
  int letra=0;
  srand(time(NULL));
  numero=(1+rand()% 6);
  letra=(1+rand()% 6);
  printf("%d,%d\n", numero, letra);
  tablero[numero][letra]=88;
  if (tablero[numero][letra]=254)
  {
   tablero[numero][letra]=42;
  }
}

int impresion(int tablero [][7])
{
for (int i = 0; i < 7; i++)
    {
       for (int j = 0; j < 7; j++)
       {
         printf("\t%c", tablero[j][i]);
       }
       printf("\n");
    } 
}
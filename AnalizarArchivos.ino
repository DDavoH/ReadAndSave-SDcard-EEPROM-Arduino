#include <EEPROM.h>

using namespace std;


struct DATOS{
   char cadena1[15]; 
   char cadena2[15];
   char cadena3[15];
   char cadena4[15];
   boolean usable;
   };

union MEMORIA{
   DATOS dato;
   byte  b[sizeof(DATOS)];
}
miMemoria;


#include <EEPROM.h>
#define address 0


void setup()
{
   // Se recuperan los datos de la memoria EEPROM:
   for( int i=0 ; i<sizeof(DATOS) ; i++  ){
      miMemoria.b[i] = EEPROM.read( address+i );
   }

   // Se comprueba que se hayan podido leer los datos (que no se haya leido basura)
   // No es la forma mas elegante de hacerlo pero funciona:
   if( miMemoria.dato.usable == true )
   {
      miMemoria.dato.cadena1[0] = '1';
      miMemoria.dato.cadena2[0] = '2';
      miMemoria.dato.cadena3[0] = '3';
      miMemoria.dato.cadena4[0] = '4';
   }
   // Si nunca se habian usado se inicializan todos los datos:
   else
   {
      miMemoria.dato.cadena1[0] ='1';
      miMemoria.dato.cadena2[0] = '2';
      miMemoria.dato.cadena3[0] = '3';
      miMemoria.dato.cadena4[0] = '4';
      miMemoria.dato.usable = true;
   }


   // Se guardan los datos en la memoria EEPROM:
   for( int i=0 ; i<sizeof(DATOS) ; i++  ){
      EEPROM.write( address+i , miMemoria.b[i] );
   }

   // Se imprime por pantalla los datos:
   delay(1000);
   Serial.begin(9600);
   Serial.print("Cadena1= "); Serial.println(miMemoria.dato.cadena1[0]);
   Serial.print("Cadena2= "); Serial.println(miMemoria.dato.cadena2[0]);
   Serial.print("Cadena3= "); Serial.println(miMemoria.dato.cadena3[0]);
   Serial.print("Cadena4= "); Serial.println(miMemoria.dato.cadena4[0]);
   pinMode(13, OUTPUT);
   digitalWrite(13, HIGH);
}

void loop()
{
   // Una vez cargamos los datos en el SETUP ya podemos hacer uso de ellos desde nuestro programa.
   // ...
}

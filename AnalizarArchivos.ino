#include <SD.h>
#include <EEPROM.h>
#define address 0

using namespace std;

struct DATOS{
   char caracter1[15]; 
   char caracter2[15];
   char caracter3[15];
   char caracter4[15];
   char caracter5[15];
   char caracter6[15];
   char caracter7[15];
   char caracter8[15];
   char caracter9[15];
   char caracter10[15];
   boolean usable;
   };

union MEMORIA{
   DATOS dato;
   byte  b[sizeof(DATOS)];
}
miMemoria;


 File myFile;
 int UltimaPocicion=0;  
 char Arreglo[100];
 int x=0;
 int contador=0;
 bool lectura=true;
 String paquetes[20];
 bool imprimir=true;
 bool imprimirE=true;
 int Econtador;
 int tamano[30];


 char c1[10];
 char c2[10];
 char c3[10];
 char c4[10];
 char c5[10];
 char c6[10];
 char c7[10];
 char c8[10];
 char c9[10];
 char c10[10];

 
void setup()
{
 
  
  Serial.begin(9600);
  Serial.print("Iniciando SD ...");
  if (!SD.begin(4)) {

    
     Serial.println("No se pudo inicializar");


     LeerEEPROM();
     while(1);
    //return;
  }else{



  Serial.println("inicializacion exitosa");
  Serial.println();
  Serial.println("Matriz del archivo :");
  }
  


  
}

void loop()
{
  myFile = SD.open("prueba.txt");//abrimos  el archivo
  int totalBytes=myFile.size();
  char caracter;
  String cadena="";
 
  if (myFile){   
      if(UltimaPocicion>=totalBytes){
        //UltimaPocicion=0; 
          EEPROM.write(235, contador);
          lectura=false;   
          if(imprimir==true){
            Serial.println();
            for(int i=0; i<contador; i++){
               Serial.print("Paquete ");
               Serial.print(i);
               Serial.print(" Almacenado: ");
               Serial.print(c1[i]);
               Serial.print(c2[i]);
               Serial.print(c3[i]);
               Serial.print(c4[i]);
               Serial.print(c5[i]);
               Serial.print(c6[i]);
               Serial.print(c7[i]);
               Serial.print(c8[i]);
               Serial.print(c9[i]);
               Serial.println(c10[i]);

       miMemoria.dato.caracter1[i] =c1[i];
       miMemoria.dato.caracter2[i] =c2[i];
       miMemoria.dato.caracter3[i] =c3[i];
       miMemoria.dato.caracter4[i] =c4[i];
       miMemoria.dato.caracter5[i] =c5[i];
       miMemoria.dato.caracter6[i] =c6[i];
       miMemoria.dato.caracter7[i] =c7[i];
       miMemoria.dato.caracter8[i] =c8[i];
       miMemoria.dato.caracter9[i] =c9[i];
       miMemoria.dato.caracter10[i] =c10[i];
      
              
               }
               
           // Se guardan los datos en la memoria EEPROM:
   for( int i=0 ; i<sizeof(DATOS) ; i++  ){
      EEPROM.write( address+i , miMemoria.b[i] );
   }
         
          }
  LeerEEPROM();
  imprimir=false;
      }
      
     
      if(UltimaPocicion<=totalBytes){
          myFile.seek(UltimaPocicion); 
       }
     
      if(lectura==true){
        //--Leemos una línea de la hoja de texto--------------
        while (myFile.available()>0){
          caracter=myFile.read();
          cadena=cadena+caracter;
           
            if( caracter==10  || caracter==63 || caracter==00 || caracter==255)//ASCII de nueva de línea
            { 
              UltimaPocicion=UltimaPocicion+3;                                 
              break;      
            }
            if(caracter==((char)' ') ||caracter==((char)'/n') ){
              UltimaPocicion=UltimaPocicion+7;  
              break; 
            }
 
          UltimaPocicion=myFile.position();
          Arreglo[x]=caracter;
          Serial.print(caracter); 
         
         x++;                    
        }

     x=0;
      
      
    c1[contador]=Arreglo[0];
    c2[contador]=Arreglo[2];
    c3[contador]=Arreglo[4];
    c4[contador]=Arreglo[6];
    c5[contador]=Arreglo[8];
    c6[contador]=Arreglo[10];
    c7[contador]=Arreglo[12];
    c8[contador]=Arreglo[14];
    c9[contador]=Arreglo[16];
    c10[contador]=Arreglo[18];
    contador++;


      
     
    Serial.println();
     
      
     
    myFile.close(); //cerramos el archivo
 
    }
  } 

}

void LeerEEPROM(){
    Econtador=EEPROM.read(235);
       // Se recuperan los datos de la memoria EEPROM:
   for( int i=0 ; i<sizeof(DATOS) ; i++  ){
      miMemoria.b[i] = EEPROM.read( address+i );
   }
if(imprimirE==true){
  Serial.println();
   for(int i=0; i<Econtador; i++){
    Serial.print("Datos en EEPROM Pila "); 
    Serial.print(i);
    Serial.print(" :");
    Serial.print(miMemoria.dato.caracter1[i]);
    Serial.print(miMemoria.dato.caracter2[i]);
    Serial.print(miMemoria.dato.caracter3[i]);
    Serial.print(miMemoria.dato.caracter4[i]);
    Serial.print(miMemoria.dato.caracter5[i]);
    Serial.print(miMemoria.dato.caracter6[i]);
    Serial.print(miMemoria.dato.caracter7[i]);
    Serial.print(miMemoria.dato.caracter8[i]);
    Serial.print(miMemoria.dato.caracter9[i]);
    Serial.println(miMemoria.dato.caracter10[i]);
   }
}
   

  
    imprimirE=false;
}
 
 

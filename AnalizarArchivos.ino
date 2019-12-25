#include <SD.h>
#include <EEPROM.h>

 File myFile;
 int UltimaPocicion=0;  
 char Arreglo[100];
 int x=0;
 int contador=0;
 bool lectura=true;
 String paquetes[20];
 bool imprimir=true;
 bool imprimirE=true;
 
 int eeAddress[100];
 int Econtador;
 
void setup()
{
  eeAddress[0]+=sizeof(String);
  eeAddress[1]+=eeAddress[0]+sizeof(String);
  eeAddress[2]+=eeAddress[1]+sizeof(String);
  eeAddress[3]+=eeAddress[2]+sizeof(String);
  eeAddress[4]+=eeAddress[3]+sizeof(String);
  eeAddress[5]+=eeAddress[4]+sizeof(String);
  eeAddress[6]+=eeAddress[5]+sizeof(String);
  eeAddress[7]+=eeAddress[6]+sizeof(String);
  eeAddress[8]+=eeAddress[7]+sizeof(String);
  eeAddress[9]+=eeAddress[8]+sizeof(String);
  eeAddress[10]+=eeAddress[9]+sizeof(String);
  eeAddress[11]+=eeAddress[10]+sizeof(String);
  eeAddress[12]+=eeAddress[11]+sizeof(String);
  eeAddress[13]+=eeAddress[12]+sizeof(String);
  eeAddress[14]+=eeAddress[13]+sizeof(String);
  eeAddress[15]+=eeAddress[14]+sizeof(String);
  eeAddress[16]+=eeAddress[15]+sizeof(String);
  eeAddress[17]+=eeAddress[16]+sizeof(String);
  eeAddress[18]+=eeAddress[17]+sizeof(String);
  eeAddress[19]+=eeAddress[18]+sizeof(String);
  
  Serial.begin(9600);
  Serial.print("Iniciando SD ...");
  if (!SD.begin(4)) {
    Serial.println("No se pudo inicializar");
     LeerEEPROM();
     while(1);
    //return;
  }
  Serial.println("inicializacion exitosa");
  Serial.println();

  
  
}

void loop()
{
  myFile = SD.open("prueba.txt");//abrimos  el archivo
  int totalBytes=myFile.size();
  String cadena="";
  char caracter;
 

  String cadena1, cadena2, cadena3, cadena4, cadena5, cadena6, cadena7, cadena8, cadena9, cadena10;
 
  if (myFile) {   
      if(UltimaPocicion>=totalBytes){
        //UltimaPocicion=0; 
        EEPROM.write(255, contador);
          lectura=false;   
          if(imprimir==true){
            Serial.println();
  for(int i=0; i<contador; i++){
    Serial.print("Paquete ");
    Serial.print(i+1);
    Serial.print(" Almacenado: ");
    Serial.println(paquetes[i]);
      
    //Almacenado de datos en EEPROM
    EEPROM.put(eeAddress[i], paquetes[i]);
  
  }}
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
      
      
      cadena1=Arreglo[0];
      cadena2=Arreglo[2];
      cadena3=Arreglo[4];
      cadena4=Arreglo[6];
      cadena5=Arreglo[8];
      cadena6=Arreglo[10];
      cadena7=Arreglo[12];
      cadena8=Arreglo[14];
      cadena9=Arreglo[16];
      cadena10=Arreglo[18];
      paquetes[contador]=cadena1+cadena2+cadena3+cadena4+cadena5+cadena6+cadena7+cadena8+cadena9+cadena10;
      contador++;

     
 
      Serial.print(" Almacenando.. : ");
      Serial.print(cadena1);
      Serial.print(cadena2);
      Serial.print(cadena3);
      Serial.print(cadena4);
      Serial.print(cadena5);
      Serial.print(cadena6);
      Serial.print(cadena7);
      Serial.print(cadena8);
      Serial.print(cadena9);
      Serial.print(cadena10);

      Serial.print(" paquete: ");
      Serial.print(contador);
      
     
      Serial.println();
     
      
     
      myFile.close(); //cerramos el archivo
 
      }}else {
        
    
  } 
  }

  void LeerEEPROM(){
    Econtador=EEPROM.read(255);
      if(imprimirE==true){
      Serial.println();
    
    for(int i=0; i<Econtador; i++){
    Serial.print("Direccion EEPROM ");
    Serial.print(i);
    Serial.print(" Almacenado: ");
    EEPROM.get(eeAddress[i], paquetes[i]);
    Serial.println(paquetes[i]);
  }}
  
  imprimirE=false;
      }
 
 

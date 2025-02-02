/******************* 

O funcionamento actual da montaxe será como se indica a seguir:

 - Ó premer unha vez, actívase o motor (relé) 
   que corresponde co estado actual do sistema. 
 - O motor permanece activo até que o fin de carreira 
   correspondente detecta a chegada do vidro, 
   momento no queo motor para, 
 - En calquera momento intermedio, o pulsador da xanela 
   pode parar o vidro (unha pulsación) 
   ou invertir o movemento (seguinte pulsación).

*********************/

#define UP 7
#define DOWN 6
#define BOTON 13
#define SENSOR_UP 12   
#define SENSOR_DOWN 11  

bool pulsa = 0;
int contador = -1;

bool estado = 0;                 /* Por defecto,
								    a xanela está abaixo*/

void setup()
    
{
  pinMode(BOTON, INPUT);         // Pulsador 1 no pin 13

  pinMode(UP, OUTPUT);           // Subir vidro
  pinMode(DOWN, OUTPUT);         // Baixar vidro
  pinMode(SENSOR_UP, INPUT);     // Sensor de fin de carreira superior
  pinMode(SENSOR_DOWN, INPUT);   // Sensor de fin de carreira inferior

  Serial.begin(9600);			 // Para ver o Monitor Serie
}

void loop(){
  
/*********** Comprobamos o PULSADOR. ************/
  
  pulsa = digitalRead(BOTON);    // Miro se o botón está pulsado.
 
  if ( pulsa == true ){          // Se o botón se pulsa...
 
    estado = !estado;            // Alternamos estado do pulsador
    
   while(digitalRead(BOTON)){ 
      delay(20);                 /* Aseguro unha única lectura.
      							    Por eso lle poño unha espera de 20ms 
							        entre lecturas de pulsación.*/
    }
          
    digitalWrite(UP, estado);    // Sube o vidro.
    digitalWrite(DOWN,!estado);  // Ordenamos que o vidro non baixe.
    contador = 700;              // Tempo que dura subindo ou baixando o vidro.
    
  }
  
/*********** Comprobamos os SENSORES. ************/

  if (estado == true) {          // Se está subindo...    
  	if (digitalRead(SENSOR_UP) == HIGH ) {

   	    digitalWrite(UP, LOW);   // Para de subir.
        contador = 0;            // Cancelamos contador.
    } 
  } 
  if (estado == false) {         // Se está baixando...    
	if (digitalRead(SENSOR_DOWN) == HIGH ) {
      
        digitalWrite(DOWN, LOW); // Para de baixar.
        contador = 0;            // Cancelamos contador.
    }
  } 
 
/*********** Cancelamos a Marcha dos Motores. ************/
  
  if ( contador > 0 ){           // Se o contador é maior a "0".
    
    contador -= 1;			     // Desconta 1 segundo.                           
  
  } else{
    digitalWrite(UP, LOW);       // Para de subir.
    digitalWrite(DOWN, LOW);     // Para de baixar.
    }
  
  
/***************  Monitor Serie  ***************/
  
  Serial.print(estado); Serial.print("  "); Serial.println(contador);
}

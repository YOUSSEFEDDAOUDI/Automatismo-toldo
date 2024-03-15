 #define FCABRIR  13
 #define FCCERRAR 11      
 #define PULSADOR 12 
 #define IZQ 10
 #define DER 9
 #define ACTIVAR 8
 #define POTENCIA 5
 #define VALORLUZ A0    
                 // entrada analogica


 bool motorActual = false;
 bool estado = false;
 int tAcero=7000; 
 int contador = 0;
int valorA0;
int nivel;
int velocidad;

void setup(){
        
  pinMode(FCABRIR, INPUT);
  pinMode(FCCERRAR, INPUT);
  pinMode(IZQ, OUTPUT);
  pinMode(DER, OUTPUT);
  pinMode(ACTIVAR, OUTPUT);
  pinMode(PULSADOR, INPUT);
  Serial.begin(9600);
  int contador=0;
}
void loop (){
  if(digitalRead(PULSADOR)){// Verifica si el pulsador está presionado
    Serial.println("pulso");  
    if(contador > 0){ // Si está parado
        contador = 0;     // Almacena el tiempo del último cambio
      }
    else {
        contador = 100;
    	estado = !estado;
   	}
   
    	while(digitalRead(PULSADOR)){
      	delay(20);
  	}
  }
  
  
    if(digitalRead(FCABRIR)){ //FIN di carrera motor 1
          if(contador>0){
            contador=0;
     	}
    }
  
     if(digitalRead(FCCERRAR)){ //FIN di carrera motor 2
          if(contador>0){
            contador=0;
     	}
    }
  
  if(contador>0){
    digitalWrite(ACTIVAR, HIGH);
    analogWrite(POTENCIA, velocidad);
    digitalWrite(IZQ, estado);
    digitalWrite(DER, !estado);
    cambiarVelocidad();
  }
  else{
    digitalWrite(ACTIVAR, HIGH);
    analogWrite(POTENCIA, 0);
    digitalWrite(IZQ, LOW);
    digitalWrite(DER, LOW);
  }
  
    delay(70);
      }
  

void cambiarVelocidad(){
  Serial.println(velocidad);
  valorA0 = analogRead(VALORLUZ);
  nivel = map(valorA0, 0, 1023, 5, 0);
  velocidad = max(255*nivel/5,1);
  velocidad = 1 + 20*nivel;
}


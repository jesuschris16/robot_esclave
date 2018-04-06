
#include <SoftwareSerial.h>

///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
////////// PROGRAMMES POUR COMMANDER LES MOTEURS /////////////////
///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

 void Arret()
  {
    int pin_brake_A = 9 ; 
    int pin_brake_B = 8 ; 

    digitalWrite( pin_brake_A , HIGH) ; 
    digitalWrite( pin_brake_B , HIGH) ;
  };

  void Avancer(int pourcentage_speed)
  {
    // initialisation moteur A

     int pin_motor_A = 12 ;
     int pin_brake_A = 9 ; 
     int pin_pwm_A = 3 ; 

     //initialisation moteur B 
     
     int pin_motor_B = 13 ;
     int pin_brake_B = 8 ; 
     int pin_pwm_B = 11 ;

     //enclenchement moteur A

     digitalWrite( pin_motor_A , HIGH) ; 
     digitalWrite( pin_brake_A , LOW) ; 
     analogWrite( pin_pwm_A , map(pourcentage_speed,0,100,0,255) ) ; 

     //enclenchement moteur B

     digitalWrite( pin_motor_B , HIGH) ; 
     digitalWrite( pin_brake_B , LOW) ; 
     analogWrite( pin_pwm_B , map(pourcentage_speed,0,100,0,255) ) ; 


  };

    void Reculer(int pourcentage_speed)
  {
    // initialisation moteur A

     int pin_motor_A = 12 ;
     int pin_brake_A = 9 ; 
     int pin_pwm_A = 3 ; 

     //initialisation moteur B 
     
     int pin_motor_B = 13 ;
     int pin_brake_B = 8 ; 
     int pin_pwm_B = 11 ;

     //enclenchement moteur A

     digitalWrite( pin_motor_A , LOW) ; 
     digitalWrite( pin_brake_A , LOW) ; 
     analogWrite( pin_pwm_A , map(pourcentage_speed,0,100,0,255) ) ; 

     //enclenchement moteur B

     digitalWrite( pin_motor_B , LOW) ; 
     digitalWrite( pin_brake_B , LOW) ; 
     analogWrite( pin_pwm_B , map(pourcentage_speed,0,100,0,255) ) ;
  };

  void Tourner(int pourcentage_speed, int n_motor)
  {
     int pin_motor = 99 ; 
     int pin_brake = 99 ; 
     int pin_pwm = 99 ; 
     
     switch(n_motor)
     {
        case 1 :
        
          pin_motor = 12 ; // pin motor A 
          pin_brake = 9 ; // pin brake A
          pin_pwm = 3 ; // pin PWM A
        
        break;

        case -1 : 

           pin_motor = 13 ; // pin motor B 
           pin_brake = 8 ; // pin brake B
           pin_pwm = 11 ; // pin PWM B

        break; 

        default :
            
        Serial.println( " n_motor non valide (doit être -1 ou 1 ) " ); //affichage si erreur 
       
        
     }

     if( n_motor == 1 || n_motor == -1 )
     {
       digitalWrite(pin_motor, HIGH); 
       digitalWrite(pin_brake, LOW) ; 
       analogWrite(pin_pwm , map(pourcentage_speed, 0 ,100, 0, 255));
     }
  };
  
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
////////// FIN PROGRAMMES POUR COMMANDER LES MOTEURS /////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void decode(char c)
{
  if(c == 's')
    {
      Arret();
    }else 
      if(c == 'a')
      {
         Avancer(100);//speed à 50% par défaut pour les test
      }else 
        if(c == 'b')
        {
          Reculer(100); ////speed à 50% par défaut pour les test
        }else 
           if(c == 'd')
           {
              Tourner(100, 1);
           }else 
              if( c == 'g' )
              {
                  Tourner(100,-1); 
              }
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
                   
int key = 10 ; // uniquement pour la configuration du bluetooth 
int pTx = 6 ; 
int pRx = 5 ;
char c = ' ' ; // vas contenir l'instruction

// initialisation moteur A

     int pin_motor_A = 12 ;
     int pin_brake_A = 9 ; 
     int pin_pwm_A = 3 ; 

//initialisation moteur B 
     
     int pin_motor_B = 13 ;
     int pin_brake_B = 8 ; 
     int pin_pwm_B = 11 ;


SoftwareSerial mavoieserie(pTx, pRx); // ne pas toucher à ces paramètres, ils sont bons ! 

void setup()
{
    Serial.begin(9600); // Ouvre la voie série avec l'ordinateur
    pinMode(pin_motor_A, OUTPUT);
    pinMode(pin_brake_A, OUTPUT);
    pinMode(pin_pwm_A, OUTPUT);
    pinMode(pin_motor_B, OUTPUT);
    pinMode(pin_brake_B, OUTPUT);
    pinMode(pin_pwm_B, OUTPUT);
    mavoieserie.begin(9600); // Ouvre la voie série avec le module BT
}
 
void loop()
{  
   
    while (mavoieserie.available()) // on attend d'avoir la chaine de caractère venant du module bluetooth 
    { 
        
        for (int i=0;i<1;i++) //on en lit 4
        {
          c = mavoieserie.read(); // lecture

          Serial.println(c) ; 
        }

        delay(4); 
    }

    while (mavoieserie.available()) //s'il reste des données
    {
      mavoieserie.read(); //on les lit sans les stocker
    }

    decode(c) ; 
}

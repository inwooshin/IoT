void setup() {  
  pinMode( 2, OUTPUT );  
  pinMode( 16, OUTPUT );  
}  
  
void loop() {  
  digitalWrite(2, LOW);
  delay(500);
  
  for ( int i=0; i<=1000; i++ ){  
    analogWrite( 16, i );  
    delay(1);  
  }  

  digitalWrite(2, HIGH);
  delay(500);

  for ( int i=1000; i>=0; i-- ){  
    analogWrite( 16, i );  
    delay(1);  
  }
  
}  

#include <LiquidCrystal.h> //biblioteca LCD

LiquidCrystal lcd(9, 8, 5, 4, 3, 2); //pinos ligados ao LCD

int segundo, minuto, hora, dia, mes, ano, ahora, aminuto; //variáveis relacionadas a data e horário, ahora é a hora do alarme e aminuto é o minuto do alarme

//melodia do jogo do Mario
int melodia[] = {660,660,660,510,660,770,380,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,500,500,500,580,660,500,430,380,500,500,500,500,580,660,870,760,500,500,500,500,580,660,500,430,380,660,660,660,510,660,770,380};

//duraçao de cada nota
int duracaodasnotas[] = {100,100,100,100,100,100,100,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,60,80,60,80,80,80,80,80,80,60,80,60,80,80,80,80,80,60,80,60,80,80,80,80,80,80,100,100,100,100,100,100,100};

const int buzzer = 7;  //porta ligada no buzzer

const int botao = 6; //porta ligado no botão

int estadobotao; //variável para leitura do estado do botão (HIGH ou LOW, apertado ou não)

int flag=0; // flag utilizada para interrupção da música de alarme  

unsigned long UtlTime; //variável de tempo

void setup() 
{
  lcd.begin(16, 2);  //inicializa o LCD: colunas=16, linhas=2
  Serial.begin(9600); //inicializa o serial, taxa de comunicação em bits por segundo: 9600
  UtlTime = 0;
  hora = 0;
  ahora = 0; //configuração da hora do alarme
  minuto = 0;
  aminuto = 0; //configuração dos minutos do alarme
  segundo = 0;
  dia = 0;
  mes = 0;
  ano = 0;
  pinMode(botao, INPUT); //configura o botão como INPUT

/*********Apresentação*********/ 

  lcd.setCursor(0,0); //posição do cursor no led, ou seja, aonde vai aparecer o print
  lcd.print("Data e horario");
  lcd.setCursor(0,1);
  lcd.print("usando Arduino");
  delay (2000); //por 2 segundos
  lcd.clear();

/*********Configurando a data*********/

//configurando o dia
lcd.clear(); //limpa o display do LCD
lcd.setCursor(0,0);  
lcd.print("Dia: ");  
while(dia==0)   
  if (Serial.available() > 0) //verifica se foi digitado um valor          
    dia = Serial.parseInt(); //o valor inteiro é colocado na variável dia
lcd.print(dia);  //imprime o valor digitado no LCD
delay(1000); //por 1 segundo

//configurando o mês
lcd.clear(); //limpa o display do LCD
lcd.setCursor(0,0);  
lcd.print("Mes: ");  
while(mes==0)   
  if (Serial.available() > 0) //verifica se foi digitado um valor          
    mes = Serial.parseInt(); //o valor inteiro é colocado na variável mês
lcd.print(mes);  //imprime o valor digitado no LCD
delay(1000); //por 1 segundo

//configurando o ano
lcd.clear(); //limpa o display do LCD
lcd.setCursor(0,0);  
lcd.print("Ano: ");  
while(ano==0)   
  if (Serial.available() > 0) //verifica se foi digitado um valor          
    ano = Serial.parseInt(); //o valor inteiro é colocado na variável ano
lcd.print(ano);  //imprime o valor digitado no LCD
delay(1000); //por 1 segundo

/*********Configurando o relógio*********/

  //configurando as horas
  lcd.clear(); //limpa o display do LCD
  lcd.setCursor(0,0);  
  lcd.print("Horas: ");   
  while(hora==0)   
    if (Serial.available() > 0) //verifica se foi digitado um valor          
      hora = Serial.parseInt(); //o valor inteiro é colocado na variável hora
  lcd.print(hora);  //imprime o valor digitado no LCD
  delay(1000); //por 1 segundo

   //configurando os minutos
  lcd.clear(); //limpa o display do LCD
  lcd.setCursor(0,0);  
  lcd.print("Minutos: ");  
  while(minuto==0)   
    if (Serial.available() > 0) //verifica se foi digitado um valor          
      minuto = Serial.parseInt(); //o valor inteiro é colocado na variável minuto
  lcd.print(minuto);  //imprime o valor digitado no LCD
  delay(1000); //por 1 segundo

/*********Configurando o alarme*********/

  lcd.clear(); //limpa o display do LCD
  lcd.setCursor(0,0);  
  lcd.print("|Alarme|");  
  
  //configurando a hora do alarme
  lcd.setCursor(0,1);  
  lcd.print("Hora: ");  
  while(ahora==0)   
    if (Serial.available() > 0) //verifica se foi digitado um valor          
      ahora = Serial.parseInt(); //o valor inteiro é colocado na variável ahora
  lcd.print(ahora);
  delay(1000);    
  
  //configurando os minutos do alarme
  lcd.setCursor(0,1);
  lcd.print("Minuto: "); 
  while(aminuto==0)   
    if (Serial.available() > 0) //verifica se foi digitado um valor          
      aminuto = Serial.parseInt(); //o valor inteiro é colocado na variável aminuto
  lcd.print(aminuto);
  delay(1000);

  //mostrando como o alarme foi configurado no LCD
  lcd.clear(); //limpa o display do LCD
  lcd.setCursor(0,0); 
  lcd.print("Alarme config."); 
  lcd.setCursor(0, 1);
  lcd.print("para: ");
  lcd.print(ahora);
  lcd.print(":");
  lcd.print(aminuto);
  delay(4000); //por 4 segundos
}


void loop() 
{
      if(millis()-UtlTime<0)     
        UtlTime=millis();  
      else      
        segundo=int((millis()-UtlTime)/1000);  
      if(segundo>59)  //60 segundos = 1 minuto e 0 segundos
      {    
        segundo=00;    
        minuto++;    
        UtlTime=millis();    
        if(minuto>59) //60 minutos = 1 hora, 0 minutos e 0 segundos
        {      
          hora++;      
          minuto=00;     
          if(hora>23) //24 horas = 1 dia, 0 hora, 0 minutos e 0 segundos     
          {        
            dia++;        
            hora=00;        
            if(mes==1||mes==3||mes==5||mes==7||mes==8||mes==10||mes==12)   //meses que tem 31 dias     
            {     
              if(dia>31)          
              {            
                dia=1;            
                mes++;            
                if(mes>12)            
                {              
                  ano++;              
                  mes=1;            
                }          
              }        
           }        
           else 
            if(mes==2) //Fevereiro tem 29 dias     
            {          
              if(ano%400==0)          
              {            
                if(dia>29)            
                {              
                  dia=1;              
                  mes++;            
                }          
              }          
              else 
              {
                if((ano%4==0)&&(ano%100!=0)) //ano bissexto         
                {            
                  if(dia>29)            
                  {              
                    dia=1;              
                    mes++;            
                  }          
                }          
                else          
                {            
                  if(dia>28)            
                  {              
                    dia=1;              
                    mes++;            
                  }          
                }        
              }  }        
              else               
                if(dia>30)          
                {            
                  dia=1;            
                  mes++;          
                }        
                 
            }    
          }  
       }   

        lcd.clear();
    
        //imprime a data
        lcd.setCursor(0,0);  
        lcd.print("Data: ");  
        lcd.print(dia);  
        lcd.print("/");  
        lcd.print(mes);  
        lcd.print("/");  
        lcd.print(ano); 
    
        //imprime o horário
        lcd.setCursor(0,1);  
        lcd.print("Hora: ");  
        lcd.print(hora);  
        lcd.print(":");  
        lcd.print(minuto);  
        lcd.print(":");  
        lcd.print(segundo);
        delay(1000);
    
        //alarme tocando enquanto o botão não for acionado
        if (hora == ahora && minuto == aminuto && flag==0) //flag indica que o despertador ainda não tocou neste dia
        {
               for (int nota = 0; nota < 156; nota++) //notas musicais do despertador
            {
    
                  int duracaodanota = duracaodasnotas[nota];
                  tone(buzzer, melodia[nota],duracaodanota);
                   //pausa depois das notas
                  int pausadepoisdasnotas[] ={150,300,300,100,300,550,575,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500,300,100,150,150,300,300,150,150,300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,300,100,150,150,300,300,150,150,300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,150,300,350,150,350,150,300,150,600,150,300,350,150,150,550,325,600,150,300,350,150,350,150,300,150,600,150,300,300,100,300,550,575};
                  delay(pausadepoisdasnotas[nota]);
                  estadobotao=digitalRead(botao);
                  if (estadobotao==HIGH) //se o botao for apertado
                  {
                      noTone(buzzer); //desliga a música de alarme
                      flag=1; //flag indica que o alarme já tocou e foi desligado pelo usuário
                      break; //sai do laço for
                  }
                    
             }
    
                  noTone(buzzer); 
        }
}

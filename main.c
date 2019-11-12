// main.c
// Runs on TM4C123 using the simulator
// Do not edit this file, Spring 2019
// Grading engine for Lab2

// U0Rx (VCP receive) connected to PA0
// U0Tx (VCP transmit) connected to PA1
#include <stdint.h>
#include "UART.h"
#include "PLL.h"
#include "Lab2.h"

#define True 1
#define False 0
#define Mean 0
#define Monotonic 1
#define COUNT1 5
struct TestCase1{
  int16_t Readings[50];  // Temperatures
  int16_t Average;
  uint32_t Size;
};
typedef const struct TestCase1 TestCase1Type;
TestCase1Type Test1[COUNT1]={
{{267,-13,-20,-138,6,-147,227,-205,-252,192,-89,-226,-35,291,-35,287,198,118,-127,136,130,-79,264,-175,174,-214,17,-137,-68,-73},
  9,30},
{{3,-189,15,99,53,-129,-290,190,-41,12,-18,-53,295},
  -4,13},
{{84,-2,-98,233,-128,262,-289,-226,-35,199,-144,189,-177,-2,19,155,188,-175},
  2,18},
{{-41,18,-238,-70,148},
  -36,5},
{{-192,-261,85},
   -122,3}
};


#define COUNT3 5
struct TestCase3{
  int16_t Readings[30];  // Array of readings
  uint32_t Size;
  int Correct;    // true if monotonic or not
};
typedef const struct TestCase3 TestCase3Type;
TestCase3Type Test3[COUNT3]={
  { {-7,12,12,16,18,22,22,23,24,24,24,26,27,29,32,32,32,34,35,37,38},21,True},
  { {-7,12,12,16,18,22,22,23,24,26,27,29,32,32,32,34,35,37,36},      19,False},  
  { {80,80,80,80,80,80,80,80,80,80},                                 10,True},
  { { 2, 4, 7,16,27,29,35,29,28,10, -9, -9,10,13,16,21,24,27},       18,False},
  { {100},                                                            1, True}  
};
#define COUNT2 13
const int16_t Input2[COUNT2] = {-459,-332,-204,-76,52,180,307,435,563,691,819,946,1000};
const int16_t Correct2[COUNT2] = {-273,-202,-131,-60,11,82,153,224,295,366,437,508,538};
int main(void){ 
  uint32_t n;
  int16_t result,correct;
  int success=True, fails1=0,fails3=0,fails2=0; 

  PLL_Init(Bus80MHz);
  UART_Init();              // initialize UART
  UART_OutString("\n\rEE319K Spring 2019 Lab 2\n\r");
  UART_OutString("Temperature Sensor Data Analysis\n\r");
  UART_OutString("Test of your Find_Mean ... ");
  
  for(n = 0; n < COUNT1 ; n++){
    result = Find_Mean(Test1[n].Readings,Test1[n].Size);
    correct = Test1[n].Average;
    if((correct-result<-1)||(correct-result>1)){
      if(fails1<2){
        UART_OutString("\n\rNo, Input is {");
        for(int i=0;i<Test1[n].Size-1;i++){
          UART_OutSDec(Test1[n].Readings[i]);
          UART_OutChar(',');
        }
        UART_OutSDec(Test1[n].Readings[Test1[n].Size-1]);
        UART_OutString("}\n\r Correct Mean= ");
        UART_OutSDec(correct);  
        UART_OutString(" Your Mean= ");
        UART_OutSDec(result);
      }     
      success=False; fails1++;
    }
  }
  if(fails1 == 0){
    UART_OutString("ok\n\r");
  }else{
    UART_OutString("\n\rYour Find_Mean has bugs\n\r"); 
  }       


  UART_OutString("Test of your FtoC ... ");
  for(n=0; n<COUNT2; n++){
    result = FtoC(Input2[n]);
    if((result-Correct2[n]<-1)||(result-Correct2[n]>1)){
      if(fails2<3){
        UART_OutString("\n\r No, Input = ");
        UART_OutSDec(Input2[n]);
        UART_OutString("F, Correct Output= ");
        UART_OutSDec(Correct2[n]);  
        UART_OutString("C, Your Output= "); 
        UART_OutSDec(result);
        UART_OutString("C");
      }
      success=False;fails2++;
    }
  }
  if(fails2 == 0){
    UART_OutString("ok\n\r");
  }else{
    UART_OutString("\n\rYour FtoC has bugs\n\r"); 
  }    
  UART_OutString("Test of your IsMonotonic ... ");
  for(n = 0; n < COUNT3 ; n++){
    result = IsMonotonic(Test3[n].Readings,Test3[n].Size);
    if(result != Test3[n].Correct){
      if(fails3<2){
        UART_OutString("\n\rNo, Input is {");
        for(int i=0;i<Test3[n].Size-1;i++){
          UART_OutSDec(Test3[n].Readings[i]);
          UART_OutChar(',');
        }
        UART_OutSDec(Test3[n].Readings[Test3[n].Size-1]);
        UART_OutString("}\n\r Correct = ");
        if(Test3[n].Correct){
          UART_OutString("True ");
        }else{
          UART_OutString("False ");
        }
      }
      success=False;
      fails3++;
    }
  }
  if(fails3 == 0){
    UART_OutString("ok\n\r");
  }else{
    UART_OutString("\n\rYour IsMonotonic has bugs\n\r"); 
  }  
  if (success) {
    UART_OutString(" Passed all tests - ");
  }else{
    UART_OutString(" Failed ");
    UART_OutUDec(fails1+fails3+fails2);
    UART_OutString(" tests\n\r");
  }
  UART_OutString(" End of Analysis\n\r");
  while(1){
  }
}

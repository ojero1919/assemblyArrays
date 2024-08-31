/*
 *  CSCI 2021 
 *  Addressing Modes 
 *  Working with Arrays in Assembly Language 
 * 
 * 
 * 
 * 
 */
void  __attribute__ ((noinline)) fillArray(int a[], int n);
void  __attribute__ ((noinline)) fillArrayby25s(int a[], int n);
void  __attribute__ ((noinline)) fillArrayPerfectSquares(int a[], int n);
void  __attribute__ ((noinline)) fillArrayPowersOf2(int a[], int n);
void __attribute__ ((noinline)) reverseArray(int A[], int n);

void __attribute__ ((noinline)) bubbleSort(int A[], int n);
void __attribute__ ((noinline)) test(int A[], int n);
void fillArrayRand(int A[], int n);

void setup() {

     int a[20] = {0}; 
     int n = 20;
  // put your setup code here, to run once:
    Serial.begin(9600);
    //Serial.println("fill by 10's");
    //fillArray(a, n);
    //printArray(a, n);
    randomSeed(analogRead(2));
  
    
 //   Serial.println("fill by 25's");
  //  fillArrayby25s(a, n);
 //   printArray(a, n);
//    reverseArray(a,n);
//    printArray(a, n);
//    Serial.println("fill by squares's");
//    fillArrayPerfectSquares(a, n);
//    printArray(a, n);
//    Serial.println("fill by powers of 2");
//    fillArrayPowersOf2(a, n);
//    printArray(a, n);
      Serial.println("Randomize");
      fillArrayRand(a,n);
      //fillArray(a, n);
      printArray(a, n);
      Serial.println("Bubble Sort");
      bubbleSort(a, n);
      printArray(a, n);
      //Serial.println("test");
      //test(a,n);
      //printArray(a, n);
}

void loop() {

   
  // put your main code here, to run repeatedly:

}

void fillArray(int A[], int n)
{
  int i, fill = 10;
//  for(i = 0; i < n; ++i)
//  {
//      A[i] = fill;
//      fill += 10;
//  }

   asm volatile(
        "movw r30, %A0 \n\t" //z now holds the address of A[0]
        "ldi r16, 0 \n\t" //set i to 0
        "ldi r24, 10 \n\t" //this is fill
        "ldi r25, 0 \n\t" //set high byte of fill
        "top%=: cp %A1,r16 \n\t" // n- a
        "breq done%= \n\t" //exit the loop
        "st z+, r24 \n\t" //load the low byte of A[i], increment z
        "st z+, r25 \n\t" //load the high byte of A[i]
        "adiw r24, 10 \n\t" 
        "inc r16 \n\t" //++i
        "rjmp top%= \n\t"   //go back for another round
        "done%=: nop \n\t"
        :    //ouput list
        :    "d" (A), "d" (n) //input list
        :     "r16", "r24", "r25", "r30", "r31"   // i is r16, 
    );
}

void printArray(int a[], int n)
{
  int i;
  for(i = 0; i < n; ++i)
  {
    Serial.print(a[i]); 
    Serial.print(" ");
  }
   Serial.println();
  
  for(i = 0; i < n; ++i)
  {
    int addr = &a[i]; 
    Serial.print(addr, HEX); 
    Serial.print(" ");
  }
   Serial.println();
}

void   fillArrayby25s(int A[], int n)
{
  int i, fill = 25;
   for(i = 0; i < n; ++i)
   {
     A[i] = fill;
     fill +=25;
   }
}

void  fillArrayPerfectSquares(int a[], int n)
{
  int i, fill = 1;
   for(i = 0; i < n; ++i)
   {
    fill = (i+1) * (i+1);
     a[i] = fill;
   }
}
void fillArrayPowersOf2(int A[], int n)
{
  int i, fill = 1;
 for(i = 0; i < n; ++i)
//   {
//     A[i] = fill;
//     fill *= 2;
//    // fill <<= 1;
//   }

   asm volatile(
        "movw r30, %A0 \n\t" //z now holds the address of A[0]
        "ldi r16, 0 \n\t" //set i to 0
        "ldi r24, 0x00 \n\t" //this is fill
        "ldi r25, 0x80 \n\t" //set high byte of fill
        "top%=: cp %A1,r16 \n\t" // n- a
        "breq done%= \n\t" //exit the loop
        "st z+, r24 \n\t" //load the low byte of A[i], increment z
        "st z+, r25 \n\t" //load the high byte of A[i]
        "lsr r25 \n\t" //asr 
        "ror r24 \n\t" 
        "inc r16 \n\t" //++i
        "rjmp top%= \n\t"   //go back for another round
        "done%=: nop \n\t"
        :    //ouput list
        :    "d" (A), "d" (n) //input list
        :     "r16", "r24", "r25", "r30", "r31"   // i is r16, 
    );
}




void reverseArray(int A[], int n)
{
   int *p_start, *p_end;
   int temp1, temp2;
   
//    p_start = A;
//    p_end = A + n-1;
// 
//    while(p_start < p_end){
//      temp1 = *p_start;
//      temp2 = *p_end;
//      *p_start = temp2;
//      *p_end= temp1;
//
//      ++p_start;
//      --p_end;
//    }

    int myStack[50];
    int top = 0;
    int i;
//    for(i = 0; i < n; ++i){
//      //push on the stack
//      myStack[top] = A[i];
//      top++;
//    }
//
//    for(i = 0; i < n; ++i){
//      //pop off the stack
//       --top;
//       A[i] = myStack[top];
//    }

//    asm volatile(
//        "movw r30, %A0 \n\t" //z now holds the address of A[0]
//        "movw r28, %A0 \n\t" //x now holds the address of A[0]
//        "add r28, %A1 \n\t"
//        "adc r29, %B1 \n\t" //add n to x
//        "add r28, %A1 \n\t"
//        "adc r29, %B1 \n\t" //add n to x
//        "sbiw r28, 2 \n\t" //x now points to A[n-1]
//        
//        "top%=: cp r30,r28 \n\t" 
//        "cpc r31, r29 \n\t"   //while(p_start < p_end)
//        "brge done%= \n\t" //exit the loop
//        "ld r16,z \n\t"   //load from the beginning of the array
//        "ldd r17,z+1 \n\t"
//        "ld r24, y \n\t" //load from the end
//        "ldd r25, y+1 \n\t"
//        "st y, r16 \n\t" //store to the front
//        "std y+1,r17 \n\t"
//        "st z, r24 \n\t" //store to the end
//        "std z+1, r25 \n\t"
//        "adiw r30, 2 \n\t" //move z to next one
//        "sbiw r28, 2 \n\t" //move y down one element
//        "rjmp top%= \n\t"   //go back for another round
//        "done%=: nop \n\t"
//        :    //ouput list
//        :    "d" (A), "d" (n) //input list
//        :     "r16", "r17", "r24", "r25", "r30", "r31", "r28", "r29"  // i is r16, 
//    );

    asm volatile(
        "movw r30, %A0 \n\t" //z now holds the address of A[0]
        "movw r28, %A0 \n\t" //y now holds the address of A[0]
         //push a copy of the array on the stack
        "ldi r16, 0 \n\t" //i = 0
        "top%=: cp r16,%A1 \n\t"  //i < n
        "brge done%= \n\t" //exit the loop
        "ld r24,z+ \n\t"   //load from the beginning of the array
        "push r24 \n\t" //push the low byte of A[i]
        "ld r24,z+ \n\t"   //load from the beginning of the array
        "push r24 \n\t" //push the high byte of A[i]
        "inc r16 \n\t" //++i
        "rjmp top%= \n\t"   //go back for another round
        "done%=: nop \n\t"
        //now pop it off, and back into the array
        "movw r30, r28 \n\t" //get back to &A[0]
        "ldi r16, 0 \n\t" //i = 0
        "top2%=: cp r16,%A1 \n\t"  //i < n
        "brge done2%= \n\t" //exit the loop
        "pop r25 \n\t" //pop the high byte
        "pop r24 \n\t" //pop the low byte
        "st z+, r24 \n\t" 
        "st z+, r25 \n\t"
        "inc r16 \n\t" //++i
        "rjmp top2%= \n\t"   //go back for another round
        "done2%=: nop \n\t"
        :    //ouput list
        :    "d" (A), "d" (n) //input list
        :     "r16", "r17", "r24", "r25", "r30", "r31", "r28", "r29"  // i is r16, 
    );
}

void fillArrayRand(int A[], int n)
{
  int i;

  for (i = 0; i < n; ++i)
  {
    A[i] = random(1, 100);
  }
}

void __attribute__ ((noinline)) test(int A[], int n)
{
  asm volatile(
        //"movw r30, %A0 \n\t" //z now holds the address of A[0]

        "ldi r16, 1\n\t" //this is the I loop 1 to n-1
        "topI%=: cpi r16, 5 \n\t" //compare to n
        "breq endIloop%= \n\t"
        "inc r16 \n\t" //++i
        "rjmp topI%= \n\t"
        "endIloop%=: nop\n\t"
        :    //ouput list
        :    "d" (A), "d" (n) //input list
        :     "r16", "r17", "r18", "r19", "r20", "r21", "r30", "r31"  // i is r16, 
        );
   
  
  }
void __attribute__ ((noinline)) bubbleSort(int A[], int n)
{
  int i, j, temp;

//   for(i = 0; i < n-1; ++i){
//    for(j = 0; j < n-1; ++j)
//    {
//      if (A[j] > A[j+1]){
//        temp = A[j];
//        A[j] = A[j+1];
//        A[j+1] = temp;
//      }
//    }//for j
//   }//for i
      asm volatile(
        "movw r30, %A0 \n\t" //z now holds the address of A[0]
        //*****start of i loop
        "ldi r16, 1\n\t" //this is the I loop 1 to n-1
        "topI%=: cp r16, %A1 \n\t" //compare to n
        "breq endIloop%= \n\t"
        "inc r16 \n\t" //++i
        "rjmp topI%= \n\t"
        "endIloop%=: nop\n\t"
    
        //*****start of j loop
        "ldi r17, 1 \n\t" //this is the j loop 1 to n-1
        "topJ%=: cp r17, %A0 \n\t" //compare to n
        "breq endJloop%= \n\t"
        "ld r18, z \n\t" //low byte of A[j]
        "ldd r19, z+1 \n\t" //high byte of A[j]
        "ldd r20, z+2 \n\t" //low byte of A[j+1]
        "ldd r21, z+3 \n\t" //high byte of A[j+1]
        "cp r18, r20 \n\t"
        "cpc r19, r21 \n\t"
        "brlt else%= \n\t"
        "st z, r20 \n\t" 
        "std z+1, r21 \n\t"
        "std z+2, r18 \n\t"
        "std z+3, r19 \n\t"
        "else%=: nop\n\t"
        "adiw r30, 2 \n\t" //get to the next element
        "inc r17 \n\t" //++j
        "rjmp topJ%= \n\t"
        "endJloop%=: nop\n\t"
        //**end
        
        //"add r31, 2 \n\t" //get to the next element


        //"inc r16 \n\t" //++j

     
        
        :    //ouput list
        :    "d" (A), "d" (n) //input list
        :     "r16", "r17", "r18", "r19", "r20", "r21", "r30", "r31"  // i is r16, 
        );
}

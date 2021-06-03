#ifndef		MASTER_H_
#define		MASTER_H_
#define		F_CPU						16000000UL
#define		MYUBRR						F_CPU/16/BAUD-1			 //Calcultate UBRR 
#define		BAUD						9600 //set 9600bfs
#define		BLOCKED						1
#define		OPEN_ROAD					-1
#define		MY_DIRECTION				0
#define		Trigger_ON					PORTF|=0x01    //초음파 트리거 PF0
#define		Trigger_OFF					PORTF&=~0x01
#define	    Echo						(PINF&0x04)     //초음파 에코 PF2
#define		MAX_STACK_SIZE				20
#define		START_LOCATION				-1
#define		BLOCKED_SECTOR				1
#define		OPENED_SECTOR				0
#define		DESTINATION					2
#define		PASSED_SECTION				-2
#define		MAZE_GO_FORWARD				1
#define		MAZE_ROTATE_FORWARD_LEFT	2
#define		MAZE_ROTATE_LEFT_FORWARD	3

#define		FRONT						1
#define		LEFT						0	
//input maze
int maze[3][3];							//declaration of maze table

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*****************************************************************************
							Global Variable & init Function
******************************************************************************/
int isForward;
int isRotateLeft;
int frontSensorData;
int rearSensorData;
volatile unsigned char flag;
int flagBuffer[4];	//global variable for communication between the functions
unsigned int msec;	//the variable for milisecond
unsigned int sec;	//the variable for second
/*****************************************************************************
							Task1 Function
******************************************************************************/
/*****when runningMode is  'Q'******/
void stop();
/*****when runningMode is  'G' ****/
void goForward();
/******when runningMode is 'Q' ****/
void goBackward();
/******rotation*******/
void goForwardLeft();
void goForwardRight();
void goBackwardLeft();
void goBackwardRight();
/********************************************************************************
								Task2 Function
**********************************************************************************/
void initUsart();							//set USART option
void decidingRunningMode();					//decide running mode by the flag
/**********************************************************************************
								Interrupt Function
***********************************************************************************/
void hc_sr04_init(void);
unsigned int getEcho(void);
void testSupersonic(void);
void showDistance(void);
/**********************************************************************************
										LCD
***********************************************************************************/
void USART1_Init(unsigned int ubrr);		//setting usart1 option
void USART1_Transmit(char data);			//Transmit the data that's in UDR register
char USART1_Receive();						//take the data that's received in UDR register
void USART1_Transmit_String(char *str);		//transmission of string
void LCD_Transmit(int x, int y, char data);	//transmit the character to the location (x, y)
void LCD_Transmit_String(int x, int y, char* String);// string to the location (x, y)
void LCDTestCode();							//print test string on LCD
void LCDoption();							//
void mazeFindingMode();						//
/**********************************************************************************
										MAZE
***********************************************************************************/
/**************************************Stack********************************************/
typedef struct Pos{//index of 2d Array
	int x;
	int y;
}Pos;
typedef struct Stack{//stack
	Pos arr[MAX_STACK_SIZE];
	int top;
}Stack;
void initStack(Stack *s);		//initiation of stack
int isEmpty(Stack *s);			//check if stack is empty
int isFull(Stack *s);			//check if stack is full
void push(Stack *s, Pos p);		//push the element to the stack
Pos pop(Stack *s);				//take the element from the stack
/**************************************PathLog********************************************/
typedef struct PathLog{			//save the path to the array 'path'
	Pos path[10];
	int index;
}PathLog;
//pathLog's member function
void PathLogInit(PathLog *p);	//initiate data structure

/*************************************Function for Finding Path***************************/ 
void mazeForward();						//go forward
void mazeLeft();						//go left
void mazeRight();						//go right
void push_loc(Stack *s, int x, int y);	//push the location of maze
void findPath(PathLog *pl);				//find path of maze
void findPathDecision(const PathLog pl);//conversion from path of maze to sequence that includes path
void solvingMaze(int *pDecide, int len);//the RC car move by the info 
/**********************************************************************************
										Timer
***********************************************************************************/
void Timer_Init();						//initiate counter
#endif
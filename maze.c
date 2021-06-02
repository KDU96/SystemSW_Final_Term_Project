#include "master.h"
/*************************************three maze table information********************************/
#if 0
int maze[3][3] = {{START_LOCATION,	BLOCKED_SECTOR,		BLOCKED_SECTOR},
				  {OPENED_SECTOR,	BLOCKED_SECTOR,		BLOCKED_SECTOR},
				  {OPENED_SECTOR,	OPENED_SECTOR,		DESTINATION}};
#endif	
#if 0
int maze[3][3] = {{START_LOCATION,	BLOCKED_SECTOR,		BLOCKED_SECTOR},
				  {OPENED_SECTOR,	OPENED_SECTOR,		OPENED_SECTOR},
				  {BLOCKED_SECTOR,	BLOCKED_SECTOR,		DESTINATION}};
#endif

#if 1
int maze[3][3] = {{START_LOCATION,	BLOCKED_SECTOR,		BLOCKED_SECTOR},
				  {OPENED_SECTOR,	OPENED_SECTOR,		BLOCKED_SECTOR},
				  {BLOCKED_SECTOR,	OPENED_SECTOR,		DESTINATION}};				  
#endif		
/*************************************************************************************************/		    
void mazeForward(){// 2x2 box goForward
	goForward();
	_delay_ms(550); 
	stop();
	_delay_ms(1000);
}
void mazeLeft(){ // 2x2 box goLeft
	goForwardLeft();  
	_delay_ms(400);
	goForward();
	_delay_ms(450);
	stop();
	_delay_ms(1000);
}
void mazeRight(){// 2x2 box goRight
	goForwardRight();   
	_delay_ms(485);
	goForward();
	_delay_ms(430);
	stop();
	_delay_ms(1000);
}
void initStack(Stack *s){//set s->top=-1, if top=-1, stack is empty
	s->top = -1;
}
int isEmpty(Stack *s){//if s->top == -1, stack is empty
	return (s->top == -1);
}
int isFull(Stack *s){//if s->top = MAX_STACK_SIZE, stack is full
	return (s->top == MAX_STACK_SIZE - 1);
}
void push(Stack *s, Pos p){//push element to stack
	if(isFull(s)){
		return;
	}
	s->arr[++(s->top)] = p;
}
Pos pop(Stack *s){//pop element from stack
	if(isEmpty(s)){
		Pos tmp;
		tmp.x = -1;	tmp.y = -1;
		return tmp;
	}
	return s->arr[(s->top)--];
}
void push_loc(Stack *s, int x, int y){//push matrix index to stack
	Pos tmp;
	if(x < 0 || y < 0 || x > 2 || y > 2)	return;

	if(maze[x][y] != BLOCKED_SECTOR && maze[x][y] != PASSED_SECTION){
		tmp.x = x;	tmp.y = y;
		push(s, tmp);
	}
}
void PathLogInit(PathLog *p){
	p->index = 0;
	for(int i=0; i<10; i++){
		p->path[i].x = -1;	p->path[i].y=-1;
	}
}
void findPath(PathLog *pl){
	Stack s;
	Pos here;
	int i, j, x, y;
	initStack(&s);
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			if(maze[i][j] == START_LOCATION){//find start location
				here.x = i;	here.y = j;
				pl->path[0] = here;	pl->index++;	break;
			}
		}
	}
	while(maze[here.x][here.y] != DESTINATION){//before arrive to destination,
		x = here.x;
		y = here.y;
		
		maze[x][y] = PASSED_SECTION;
		
		//push index of matrix
		push_loc(&s, x+1, y);
		push_loc(&s, x-1, y);
		push_loc(&s, x, y+1);
		push_loc(&s, x, y-1);

		if(isEmpty(&s)){//before stack is empty
			return;
			}else{
			here = pop(&s);
			pl->path[pl->index++] = here;
		}
	}
}
void findPathDecision(const PathLog pl){
	int tmpX, tmpY;
	int headOfCarDirection = FRONT;
	
	for(int i=0; i<pl.index-1; i++){
		tmpX = pl.path[i+1].x - pl.path[i].x;
		tmpY = pl.path[i+1].y - pl.path[i].y;
		
		if(tmpX == 1 && headOfCarDirection == FRONT){
			headOfCarDirection = FRONT;
			flagBuffer[i] = MAZE_GO_FORWARD;
		}
		else if(tmpX == 1 && headOfCarDirection == LEFT){
			flagBuffer[i] = MAZE_ROTATE_LEFT_FORWARD;
			headOfCarDirection = FRONT;
		}
		else if(tmpY == 1 && headOfCarDirection == FRONT){
			flagBuffer[i] = MAZE_ROTATE_FORWARD_LEFT;
			headOfCarDirection = LEFT;
		}
		else if(tmpY == 1 && headOfCarDirection == LEFT){
			flagBuffer[i] = MAZE_GO_FORWARD;
			headOfCarDirection = LEFT;
		}
	}
}
void solvingMaze(int *pDecide, int len){
	USART1_Transmit_String("$I\r"); 	
	LCD_Transmit_String(1,2," Maze Mode"); //
	for(int i=0; i<len; i++){
		if(pDecide[i] == MAZE_GO_FORWARD)
			mazeForward();
		else if(pDecide[i] == MAZE_ROTATE_FORWARD_LEFT)
			mazeLeft();
		else if(pDecide[i] == MAZE_ROTATE_LEFT_FORWARD)
			mazeRight();
	}	
}
#define F_CPU 16000000UL
#include <avr/io.h>
#include "Test/SSD1306.h"
#include "Test/Font5x8.h"
#include <util/delay.h>

#define borderX 128
#define borderY 64

typedef struct entity {
	int x;
	int y;
	int width;
	int height;
	float speed;
} entity;

entity ball = {64, 32, 2, 2, 1.0};
entity player1 = {0, 32, 1, 10, 1.0};
entity player2 = {127, 32, 1, 10, 1.0};
int dirx;
int diry;


int init(void)
{
	DDRD = 0x00;
	
	dirx = 1;
	diry = 1;
	GLCD_Setup();
}
void render(){
	GLCD_Clear();
	GLCD_GotoXY(ball.x, ball.y);
	GLCD_DrawRectangle(ball.x,ball.y,ball.x+1,ball.y+1,GLCD_Black);
	GLCD_DrawLine(player1.x,player1.y,player1.x,player1.y+player1.height,GLCD_Black);
	GLCD_DrawLine(player2.x,player2.y,player2.x,player2.y+player2.height,GLCD_Black);
	GLCD_Render();
}
void ballMoviment(){
	ball.x+=dirx*ball.speed;
	ball.y+=diry*ball.speed;
	if(ball.x>borderX-ball.width)
	{
		ball.x=borderX-ball.width;
		dirx=-1;
		//speed+=0.25;
	}
	if(ball.x<0)
	{
		ball.x=0;
		//speed+=0.25;
		dirx=1;
	}
	if(ball.y>borderY-ball.height)
	{
		ball.y=borderY-ball.height;
		//speed+=0.25;
		diry=-1;
	}
	if(ball.y<16)
	{
		ball.y=16;
		//speed+=0.25;
		diry=1;
	}
}

void playerMoviment(){
	if(PIND ^= 0b00000100){
		player1.y++;
	}
}

int main(void)
{
	init();
	while(1)
	{
		ballMoviment();
		playerMoviment();		
		render();
	}
}

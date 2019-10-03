#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
struct pos{
	int row;
	int column;
	};
struct node{
	struct node *next;
	struct pos *qpos;
	};
struct stack{
	struct node *head;
	};
int init(struct stack *s){
	s->head = NULL;
	return 1;
}
int checkProtected(struct stack *s, struct pos *cur){
struct node *traverse = s->head;
int a,b,c,d,e,f,p,q;
c=cur->row;
d=cur->column;
e=(((d-1)*30)+115);
f=(((c-1)*30)+115);
setfillstyle(1,MAGENTA);
pieslice(e,f,0,360,10);
setcolor(BLACK);
circle(e,f,10);
delay(400);
while(traverse != NULL){
	a = ((traverse->qpos)->row);
	b = ((traverse->qpos)->column);
      	if( (d==b)||( (a-c)==(b-d) )||( (a-c)==(d-b) ) ){
		setcolor(RED);
		p=(((a-1)*30)+115);
		q=(((b-1)*30)+115);
		line(q,p,e,f);
		delay(400);
		setcolor(GREEN);
		line(q,p,e,f);
		 delay(400);
		 setfillstyle(1,GREEN);
		 bar(e-15,f-15,e+15,f+15);
		 setcolor(WHITE);
		 rectangle(e-15,f-15,e+15,f+15);
		return 0;}
	traverse = traverse->next;
}
setcolor(BLUE);
line(e-15,f,e,f+15);
line(e,f+15,e+15,f-15);
delay(400);
return 1;
}
int push(struct stack *s, struct pos *cur){
int a,b,x,y;
struct node *newNode=(struct node*)malloc(sizeof(struct node));
newNode->qpos = cur;
newNode->next = (s->head);
(s->head) = newNode;
setfillstyle(1,GREEN);
a=(100+((cur->row)-1)*30);
b=(100+((cur->column)-1)*30);
bar(b,a,b+30,a+30);
setcolor(WHITE);
rectangle(b,a,b+30,a+30);
printQueen(b,a);
return 1;
}
int pop(struct stack *s, struct pos **result){
int a,b;
struct node *temp=(s->head);
*result = ((s->head)->qpos);
(s->head) = ((s->head)->next);
free(temp);
a=(100+(((*result)->row)-1)*30);
b=(100+(((*result)->column)-1)*30);
setfillstyle(1,RED);
bar(b+2,a+2,b+28,a+28);
delay(400);
setfillstyle(1,GREEN);
bar(b,a,b+30,a+30);
setcolor(WHITE);
rectangle(b,a,b+30,a+30);
return 1;
}
int solveNQueen(struct stack *s, struct pos *cur, int n,int *flag){
	int a = cur->row;
	int b = cur->column;
	while((*flag)<n){
	  int j=0;
	  for(j = b; j<=n; j++){
		struct pos *temp=(struct pos*)malloc(sizeof(struct pos));
		temp->row = a;
		temp->column = j;
			if(checkProtected(s,temp)){
				push(s,temp);
				(*flag)++;
				temp  = NULL;
			       break;
			}
		}
		if(j>n){
			struct pos *result=(struct pos*)malloc(sizeof(struct pos));
			pop(s,&result);
			(*flag)--;
			      (result->column)++;
			      solveNQueen(s,result,n,flag);
		}
		a++;
		b=1;
	}
	return 0;
}
int printQueen(int x,int y){
	setfillstyle(1,BROWN);
	sector(x+15,y+30,0,180,11,5);
	setfillstyle(1,YELLOW);
	bar(x+11,y+15,x+19,y+25);
	setcolor(BLACK);
	line(x+15,y+15,x+15,y+7);
	line(x+15,y+15,x+9,y+9);
	line(x+15,y+15,x+21,y+9);
	setfillstyle(1,WHITE);
	sector(x+15,y+15,0,180,6,5);
	setfillstyle(1,YELLOW);
	pieslice(x+15,y+7,0,360,2);
	pieslice(x+9,y+9,0,360,2);
	pieslice(x+21,y+9,0,360,2);
	return 0;
}
int main(){
int n,a,b,i;
char mesg[10];
struct pos cur;
int flag = 0;
b=DETECT;
printf(":) Welcome To NQUEEN PROGRAM\n");
printf("Enter number of Rows\n");
scanf("%d",&n);
if(n<=3)  {
	printf("Not possible\n");
	getch();
	}
else{
      struct stack s;
      struct pos cur;
      init(&s);
	initgraph(&b,&a,"c:\\turboc3\\bgi");
	settextstyle(1,HORIZ_DIR,5);
	setcolor(WHITE);
	sprintf(mesg,"%d QUEENS",n);
	outtextxy(50,50,mesg);
	setfillstyle(1,GREEN);
	bar(100,100,(n*30)+100,(n*30)+100);
	setcolor(WHITE);
	for(i=100;i<=((n*30)+100);i+=30){
		line(100,i,((n*30)+100),i);


      line(i,100,i,((n*30)+100));
		}
	cur.row=1;
	cur.column=1;
	solveNQueen(&s,&cur,n,&flag);
	setcolor(BLUE);
	outtextxy(50,320,"SOLVED");
	getch();
	closegraph();
	}
getch();
return 0;
 }

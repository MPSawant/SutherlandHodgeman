
#include<stdio.h>
#include<graphics.h>

int wxmin,wxmax,wymin,wymax;
int code[2];

struct pt
{
 int x;
 int y;

};

float result[2]={0,0};
// result arry to hold x and y coords of the intersection

void intersection(int x0,int y0,int x1,int y1,char e)
{  float m,xt,xb,yl,yr;
  result[0]=0;
  result[1]=0;
 m=(y1-y0);
m=m/(x1-x0);
// finding intersection against top edge
if(e=='t')
{
result[1]=wymin;
result[0]=(wymin-y0);
result[0]=result[0]/m+x0;
}

// intersection against bottom edge
if(e=='b')
{
result[1]=wymax;
result[0]=(wymax-y0);
result[0]=result[0]/m+x0;
}
//intersection against left edge
if(e=='l')
{
result[0]=wxmin;
result[1]=m*(wxmin-x0)+y0;
}
// intersection agaist right edge/boundary
if(e=='r')
{
result[0]=wxmax;
result[1]=m*(wxmax-x0)+y0;
}

}

// function to check visibility of two points against an edge e
void check(int x0,int y0,int x1,int y1,char e)
{ code[0]=0;
code[1]=0;
 // code array indicates the visibility. ie if code[0]=0 that means first point is not visible.
 //if code[0]=1 then first point is visible .for second point code[1]

 if(e=='l')
 {
   if(x0<wxmin)
    code[0]=0;
   else
   code[0]=1;
   if(x1<wxmin)
    code[1]=0;
   else
    code[1]=1;
//  printf("x0:%d x1:%d code[0]:%d code[1]:%d",x0,x1,code[0],code[1]);
  }
  if(e=='r')
  {
   if(x0>wxmax)
    code[0]=0;
   else
   code[0]=1;
   if(x1>wxmax)
    code[1]=0;
   else
    code[1]=1;
 // printf("x0:%d x1:%d code[0]:%d code[1]:%d",x0,x1,code[0],code[1]);

  }
  if(e=='t')
  {
   if(y0<wymin)
    code[0]=0;
   else
   code[0]=1;
   if(y1<wymin)
    code[1]=0;
   else
    code[1]=1;
//  printf("y0:%d y1:%d code[0]:%d code[1]:%d",y0,y1,code[0],code[1]);

  }
  // considering bottom edge as wymax and top as wymin
  if(e=='b')
  {
   if(y0>wymax)
    code[0]=0;
   else
   code[0]=1;
   if(y1>wymax)
    code[1]=0;
   else
    code[1]=1;
//  printf("y0:%d y1:%d code[0]:%d code[1]:%d",y0,y1,code[0],code[1]);


  }
}

void main()
{int z;int poly1[10];
int clipwind[10]={50,50,200,50,200,200,50,200,50,50};
//int poly1[10]={100,100,250,100,250,250,100,250,100,100};
//int poly1[10]={25,100,150,75,150,125,25,150,25,100};
//int poly1[10]={25,150,150,25,225,150,150,225,25,150};
//int poly1[10]={10,150,100,120,30,150,100,180,10,150};
//int poly1[10]={25,50,100,50,100,150,25,150,25,50};
char e[4]="ltrb";
int k,gd,gm;
  struct pt a,b,c,d,i1,i2,input[100],output[100];
  int count,i,j,m;
  clrscr();

for(z=0;z<4;z++)
{
switch(z)
{
case 0:
	poly1[0]=25;
	poly1[1]=50;
	poly1[2]=100;
	poly1[3]=50;
	poly1[4]=100;
	poly1[5]=150;
	poly1[6]=25;
	poly1[7]=150;
	poly1[8]=25;
	poly1[9]=50;
	break;






case 1:
	poly1[0]=10;
	poly1[1]=150;
	poly1[2]=100;
	poly1[3]=120;
	poly1[4]=30;
	poly1[5]=150;
	poly1[6]=100;
	poly1[7]=180;
	poly1[8]=10;
	poly1[9]=150;
	break;


case 2:
	poly1[0]=25;
	poly1[1]=100;
	poly1[2]=150;
	poly1[3]=75;
	poly1[4]=150;
	poly1[5]=125;
	poly1[6]=25;
	poly1[7]=150;
	poly1[8]=25;
	poly1[9]=100;
	break;


case 3:
	poly1[0]=100;
	poly1[1]=100;
	poly1[2]=250;
	poly1[3]=100;
	poly1[4]=250;
	poly1[5]=250;
	poly1[6]=100;
	poly1[7]=250;
	poly1[8]=100;
	poly1[9]=100;
	break;

 }

  a.x=poly1[0];
  a.y=poly1[1];
  b.x=poly1[2];
  b.y=poly1[3];
  c.x=poly1[4];
  c.y=poly1[5];
  d.x=poly1[6];
  d.y=poly1[7];


  input[0]=output[0]=a;
  input[1]=output[1]=b;
  input[2]=output[2]=c;
  input[3]=output[3]=d;
  input[4]=output[4]=a;
wxmin=50;
wxmax=200;
wymin=50;
wymax=200;



  count=4;
  m=5;
  k=0;

  // to clip against four boundaries k loop will run 4 times
  for(k=0;k<4;k++)
  {

  // output of previous iteration is assigned to input of current iteration
  for(j=0;j<m;j++)
  {
  input[j]=output[j];
  }
  m=0;
  //m keeps track of the no. of entries in the output array
  for(i=0;i<count;i++)
  {
    check(input[i].x,input[i].y,input[i+1].x,input[i+1].y,e[k]);
    if(code[0]==0 && code[1]==1)
    { intersection(input[i].x,input[i].y,input[i+1].x,input[i+1].y,e[k]);
     output[m].x=result[0];
     output[m].y=result[1];
     m++;
     output[m++]=input[i+1];

   //   printf("(%d,%d)\n",output[m-2].x,output[m-2].y);
   //   printf("(%d,%d)\n",output[m-1].x,output[m-1].y);
     }
    if(code[0]==1 && code[1]==0)
    { intersection(input[i].x,input[i].y,input[i+1].x,input[i+1].y,e[k]);

     output[m].x=result[0];
     output[m].y=result[1];
     m++;
   //   printf("(%d,%d)\n",output[m-1].x,output[m-1].y);
     }
    if(code[0]==1 && code[1]==1)
    {
      output[m++]=input[i+1];
  //    printf("(%d,%d)\n",output[m-1].x,output[m-1].y);
     }


   }
output[m++]=output[0];
//printf("%d",m);
count=m-1;
   }

detectgraph(&gd,&gm);
initgraph(&gd,&gm,"");
drawpoly(5,clipwind);
drawpoly(5,poly1);
delay(2000);
cleardevice();
drawpoly(5,clipwind);
setcolor(RED);
for(i=0;i<m-1;i++)
line(output[i].x,output[i].y,output[i+1].x,output[i+1].y);
 delay(2000);
 cleardevice();

}

//clipping window
//setcolor(YELLOW);
//rectangle(50,50,200,200);
//drawpoly(4,poly1);
/*
x0=100;
x1=100;
x2=250;
x3=250;
y0=100;
y1=250;
y2=250;
y3=100;
intersection(x0,y0,x1,y1);
draw();

intersection(x1,y1,x2,y2);
draw();

intersection(x3,y3,x2,y2);
draw();

intersection(x0,y0,x3,y3);
draw();

*/
// putpixel(50,95,0);
// putpixel(50,145,0);

 getch();
}
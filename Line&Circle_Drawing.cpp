#include<stdio.h>
#include<iostream>
#include<math.h>
#include<conio.h>
#include<Windows.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<time.h>

using namespace std;
int r, xc, yc,x_0,y_0,x_1,y_1;

void display_lpoints(int x, int y)
{
    glColor3f(1.0, 1.0, 1.0);    
	glBegin(GL_POINTS);
	    glVertex2i(x,y);
	glEnd();
//	cout<<x<<' '<<y<<endl;
}

void display_points(int x, int y, int xc, int yc)
{
    glColor3f(1.0, 1.0, 1.0);    
	glBegin(GL_POINTS);
	    glVertex2i(xc + x, yc + y);
	    glVertex2i(xc + y, yc + x);
	    glVertex2i(xc + y, yc - x);
	    glVertex2i(xc + x, yc - y);
	    glVertex2i(xc - x, yc - y);
	    glVertex2i(xc - y, yc - x);
	    glVertex2i(xc - y, yc + x);
	    glVertex2i(xc - x, yc + y);
	glEnd();
//	cout<<x<<' '<<y<<endl;
}

void Eq_line(float x_0,float y_0,float x_1,float y_1)
{
	float m,c,y;
	m = (y_1 - y_0)/(x_1 - x_0);
	c = y_0 - m*x_0;
	for(int x = x_0;(x_1>x_0)?x<=x_1:x>=x_1;(x_1>x_0)?x++:x--)
    {        
 		y = m * x + c;
//        cout<<'('<<x<<','<<round(y)<<')'<<endl;
		display_lpoints(x,round(y));
    }
}

void DDA_Line(int x_0,int y_0,int x_1,int y_1){
	float x, y,dx,dy,steps;
	dx = (float)(x_1 - x_0);  
    dy = (float)(y_1 - y_0);  
    if(dx>=dy)  
           {  
        steps = abs(dx);  
    }  
    else  
           {  
        steps = abs(dy);  
    }  
    dx = dx/steps;  
    dy = dy/steps;  
    x = x_0;  
    y = y_0;  
    for(int i=1;i<= steps+1;i++){  
//        cout<<'('<<round(x)<<','<<round(y)<<')'<<endl;  
        display_lpoints(round(x),round(y));
        x += dx;  
        y += dy;    
    }  
}

void Bresenham_Line(int x_0,int y_0,int x_1,int y_1){
	
	int dx = x_1-x_0, dy = y_1-y_0, P0; bool flag=false,swp=false;
	
	// finding octave
	if(x_1>x_0 && y_1>y_0 && abs(dy)>abs(dx)){
		swap(x_0,y_0);
		swap(x_1,y_1);
		swp = true;
	}
	else if(x_1<=x_0 && y_1>y_0 && abs(dy)>=abs(dx)){
		swap(x_0,y_0);
		swap(x_1,y_1);
		swp = true;
		flag = true;
	}
	else if(x_1<=x_0 && y_1>y_0 && abs(dy)<abs(dx)){
		swap(x_0,x_1);
		swap(y_0,y_1);
		flag = true;
	}
	else if(x_1<=x_0 && y_1<=y_0 && abs(dy)<abs(dx)){
		swap(x_0,x_1);
		swap(y_0,y_1);
	}
	else if(x_1<=x_0 && y_1<=y_0 && abs(dy)>=abs(dx)){
		swap(x_0,x_1);
		swap(y_0,y_1);
		swap(x_0,y_0);
		swap(x_1,y_1);
		swp = true;
	}
	else if(x_1>x_0 && y_1<=y_0 && abs(dy)>=abs(dx)){
		swap(x_0,x_1);
		swap(y_0,y_1);
		swap(x_0,y_0);
		swap(x_1,y_1);
		swp = true;
		flag = true;
	}
	else if(x_1>x_0 && y_1<=y_0 && abs(dy)<abs(dx)){
		flag = true;
	}
	else flag = false;
	//print point
	if(!swp){
//		cout<<'('<<x_0<<','<<y_0<<')'<<endl;
		display_lpoints(x_0,y_0);
	}
	else{
//		cout<<'('<<y_0<<','<<x_0<<')'<<endl;
		display_lpoints(y_0,x_0);
	}
	dx = abs(x_1-x_0); dy = abs(y_1-y_0); P0 = 2*dy - dx;
	// calculation for coming point/pixel
	for(int i=0;i<abs(dx);i++){
		x_0++;
		if(P0<0){
			P0 = P0 + 2*dy;
		}
		else{
			if(flag) y_0--;
			else y_0++;
			P0 = P0 + 2*dy - 2*dx;
		}
		//print point/ on pixel
		if(!swp){
//			cout<<'('<<x_0<<','<<y_0<<')'<<endl;
			display_lpoints(x_0,y_0);
		}
		else{
//			cout<<'('<<y_0<<','<<x_0<<')'<<endl;
			display_lpoints(y_0,x_0);
		}
	}
}

void Bresenham_Circle(int xc, int yc, int r)
{
	int x = 0, y = r;
	int pk = 3 - 2 * r;
	display_points(x, y, xc, yc);
	while (y >= x)
	{
	    x++;
		if (pk < 0) {
	        pk = pk + 4 * x + 6;
	    }
		else{
	        y--;
	        pk = pk + 4 * (x - y) + 10;
	    }
		display_points(x, y, xc, yc);
	}
}

void MidPoint_Circle(int xc, int yc, int r)
{
    int x = 0, y = r;
    int P = 5/4 - r;
    display_points(x, y, xc, yc);
    while (y >= x)
    {
        x++;
        if (P < 0)
            P = P + 2*x + 3;
        else{
            y--;
            P = P + 2*x - 2*y + 5;
        }
		display_points(x, y, xc, yc);
    }
}

void display(){
	
	glClear(GL_COLOR_BUFFER_BIT);
	Bresenham_Circle((x_0+x_1)/2, (y_0+y_1)/2, 40);
//	MidPoint_Circle(xc, yc, r);
	Bresenham_Line(x_0,y_0,x_1,y_1);
//	DDA_Line(x_0,y_0,x_1,y_1);
//	Eq_line(x_0,y_0,x_1,y_1);
	
	glFlush();
}

void myinit() {
	glClearColor(0, 0, 0, 1);
    glColor3f(0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv) {

//	printf("Enter radius of circle : ");
//	scanf(" %d", &r);
//	printf("Enter xc and yc : ");
//	scanf(" %d %d", &xc, &yc);
	
	cout<<"Start Points: ";
	cin>>x_0>>y_0;
	cout<<"End Points: ";
	cin>>x_1>>y_1;
	
	glutInit(&argc, argv);          // Initialize GLUT
	glutCreateWindow("Circle Drawing");  // Create window with the given title
	glutInitWindowSize(320, 320);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); 
	
	clock_t start, end;
	double cpu_time_used;
    start = clock();
    myinit();
    
    glutDisplayFunc(display); // Register callback handler for window re-paint event
    
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("\nTime taken = %.5f", cpu_time_used);

	glutMainLoop();	
	
	return 0;
}

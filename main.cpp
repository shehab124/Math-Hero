#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits/stdc++.h>

int phyWidth= 700;
int phyHeight= 700;
int logWidth=100;
int logHeight=100;
int centerX=logWidth/2;
int centerY=logHeight/2;

int cx1=50,cy1=70,cx2=50,cy2=50,cx3=50,cy3=30; //buttons
int sqWid=20; //button width
int sqHeight=8;
int status=0; //scene
int mouseXX=centerX,mouseYY=centerY; //mouse location

float sqDelta1 = 0;//movement of square 1
float sqDelta2 = 0;
float sqDelta3 = 0;
float sqDelta4 = 0;
int maxY1=100,maxY2=200,maxY3=240; // squares
bool flagtimer2=true;

bool flag1 = 0, flag2 = 0 , flag3 = 0, flag4 = 0; //sqaures
int answers[4]={0};//list of answers on screen to compare with
char* eq1;
char* eq2;
char* eq3;
char* eq4;
char str1[10];
char str2[10];
char str3[10];
char str4[10];
bool flageq1,flageq2,flageq3,flageq4;//if equation is visible
char result[10]; //input from keyboard
int countchar=0; //number of inputs before pressing enter
int score=0; //current score
int usernumber=0;
int highscore[20] ={0}; //list of highscores
char * high[5];
//char highscores[100];
bool negativeFlag = false;
char h1[10],h2[10],h3[10],h4[10],h5[10];//high scores in strings
int sq3asfora=100;
bool flagTimer3=true;
bool flag3asfora=true;
int timing=10;
bool flagTimer1=true;//lel 3asfoora
int tamanin=80;

void draw3asfora()
{
    //DrawCircle(80,sq3asfora,5,1000);
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
        glVertex2f(centerX-sqWid/2, centerY-sqWid/2+sq3asfora); // x, y
        glVertex2f(centerX+sqWid/2, centerY-sqWid/2+sq3asfora); // x, y
        glVertex2f(centerX+sqWid/2, centerY+sqWid/2+sq3asfora); // x, y
        glVertex2f(centerX-sqWid/2, centerY+sqWid/2+sq3asfora); // x, y
    glEnd();
    sq3asfora--;
}

void Timer3(int value)
{
    if(flagTimer3)
    {
        glutTimerFunc(5000,Timer3,value);
        flagTimer3=false;
    }
    else
    {
        flag3asfora=false;
    }
}

void descSort() //sort highscore
{
    int i,j,temp;
    for(i=0;i<19;i++)
    {
        for(j=i+1;j<20;j++)
        {
            if(highscore[i] < highscore[j])
            {
                temp = highscore[i];
                highscore[i] = highscore[j];
                highscore[j] = temp;
            }
        }
    }
}

void specialkeyboard(int key , int x , int y)
{

    if (key== GLUT_KEY_F1)
    {
        status=1;
    }

    if (key== GLUT_KEY_F2)
    {
        status=0;
    }
}

void keyboard(unsigned char key,int x,int y)
{
    if(key == '-')
    {
        negativeFlag = true;
    }
    else if( key == '0' || key == '1'  || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9')
    {
        result[countchar] = key;
        countchar++;
    }
    else if( key == 0x0D)
    {
        countchar=0;
        int answ=atoi(result);
        if(negativeFlag)
        {
            answ = answ*-1;
        }
        if((answers[0] == answ && flageq1) || (answers[1] == answ && flageq2) || (answers[2] == answ && flageq3) || (answers[3] == answ && flageq4))
        {
            score++;
        }
        //result[0]='\0';
        memset(result,0,10);
        negativeFlag = false;
    }
}

void printString(char *str,int x,int y)
{

    glRasterPos2d(x,y);
    for (int i=0;i<strlen(str);i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
    glFlush();
}

char * generateFunction(int i,char str[])
{
    int upper = 10,lower=1;
    int num1 = (rand() % (upper - lower + 1)) + lower;
    int num2 = (rand() % (upper - lower + 1)) + lower;
    char str2[10];
    int x = (rand() % (3));
    if(x == 0) // +
    {
        sprintf(str,"%d",num1);
        sprintf(str2,"%d",num2);
        strcat(str,"+");
        strcat(str,str2);
        char *func = &str[0];
        answers[i]= num1+num2;

        return func;
    }
    else if(x == 1) // -
    {
        sprintf(str,"%d",num1);
        sprintf(str2,"%d",num2);
        strcat(str,"-");
        strcat(str,str2);
        char *func = &str[0];
        answers[i]= num1-num2;
        return func;
    }
    else if(x == 2) //*
    {
        sprintf(str,"%d",num1);
        sprintf(str2,"%d",num2);
        strcat(str,"x");
        strcat(str,str2);
        char *func = &str[0];
        answers[i] = num1*num2;
        return func;
    }
}

void Timer(int value)
{
    glutTimerFunc(timing, Timer, value);
    glutPostRedisplay();
    if(!flagTimer1)
    {
        timing=10;
    }
}

void gameOver()
{
    int i;
    for(i=0;i<20;i++)
    {
        if(score == highscore[i])
        {
            break;
        }
    }
    char zeft[2];
    i++;
    itoa(i,zeft,10);
    glColor3f(0.215, 0.662, 0.745);
    glBegin(GL_POLYGON);
        glVertex2i(0,0);
        glVertex2i(100,0);
        glVertex2i(100,100);
        glVertex2i(0,100);
    glEnd();
    char sc[10];
    itoa(score,sc,10);
    glColor3f(0,0,0);
    printString("Your score is: ",40,50);
    glColor3f(0,0,0);
    printString(sc,62,50);
    glColor3f(0,0,0);
    printString("Your rank is: ",40,30);
    printString(zeft,62,30);

}


void Timer2(int value)
{
    if(flagtimer2)
    {
        glutTimerFunc(60000,Timer2,value);
        flagtimer2=false;
    }
    else
    {
        status=4;
        highscore[usernumber]=score;
        usernumber++;
    }
}

void drawSquare1(int startx,int starty)
{
    glColor3f(0.215, 0.662, 0.745);
    glBegin(GL_POLYGON); // Each set of 4 vertices form a quad
    glVertex2f(startx-sqWid/2, starty-sqWid/2+sqDelta1); // x, y
    glVertex2f(startx+sqWid/2, starty-sqWid/2+sqDelta1); // x, y
    glVertex2f(startx+sqWid/2, starty+sqWid/2+sqDelta1); // x, y
    glVertex2f(startx-sqWid/2, starty+sqWid/2+sqDelta1); // x, y
    glEnd();
    sqDelta1+=0.4;
    //printf("%f\n",sqDelta1);
    if(sqDelta1 > 40 && flag1 == 0)
    {
        sqDelta2 = 0;
        flag2 = 0;
        flag1 = 1;
    }
    if(sqDelta1 > 0.39 && sqDelta1 < 0.41) //awel ma yetla3 3al shasha hane3mel generate le function w ne7ot answer fel array w ne5ali el flag=1
    {
        flageq1 = true;
        eq1 = generateFunction(0,str1);

    }
    //printf("%f\n",sqDelta1);
    if(sqDelta1 < 0 || sqDelta1 > 110) // lama yeb2a bara el shasha han5ali el answer b dummy value w ne5ali el flag = 0
    {
        answers[0] = INT_MAX;
        flageq1 = false;
    }
    if(sqDelta1 > 0.4 && sqDelta1 < 110 && flageq1) // tool ma howa 3al shasha hanetba3o fel box beta3o
    {
        glColor3f(1,1,1);
        printString(eq1,47,sqDelta1-10);
    }

}
void drawSquare2(int startx,int starty)
{
    glColor3f(0.215, 0.662, 0.745);
    glBegin(GL_POLYGON); // Each set of 4 vertices form a quad
    glVertex2f(startx-sqWid/2, starty-sqWid/2+sqDelta2); // x, y
    glVertex2f(startx+sqWid/2, starty-sqWid/2+sqDelta2); // x, y
    glVertex2f(startx+sqWid/2, starty+sqWid/2+sqDelta2); // x, y
    glVertex2f(startx-sqWid/2, starty+sqWid/2+sqDelta2); // x, y
    glEnd();
    sqDelta2+=0.40;
    if(sqDelta2 > 40 &&flag2 == 0){
        sqDelta3 = 0;
        flag3 = 0;
        flag2 = 1;
    }
    if(sqDelta2 > 0.39 && sqDelta2 < 0.41) //awel ma yetla3 3al shasha hane3mel generate le function w ne7ot answer fel array w ne5ali el flag=1
    {
        flageq2 = true;
        eq2 = generateFunction(1,str2);

    }
    if(sqDelta2 < 0.4 || sqDelta2 > 110) // lama yeb2a bara el shasha han5ali el answer b dummy value w ne5ali el flag = 0
    {
        answers[1] = INT_MAX;
        flageq2 = false;
    }
    if(sqDelta2 > 0.4 && sqDelta2 < 110 && flageq2) // tool ma howa 3al shasha hanetba3o fel box beta3o
    {
        glColor3f(1,1,1);
        printString(eq2,47,sqDelta2-10);
    }

}
void drawSquare3(int startx,int starty)
{
    glColor3f(0.215, 0.662, 0.745);
    glBegin(GL_POLYGON); // Each set of 4 vertices form a quad
    glVertex2f(startx-sqWid/2, starty-sqWid/2+sqDelta3); // x, y
    glVertex2f(startx+sqWid/2, starty-sqWid/2+sqDelta3); // x, y
    glVertex2f(startx+sqWid/2, starty+sqWid/2+sqDelta3); // x, y
    glVertex2f(startx-sqWid/2, starty+sqWid/2+sqDelta3); // x, y
    glEnd();
    sqDelta3+=0.40;
    if(abs(sqDelta3) > 40 && flag3 == 0)
    {
        sqDelta4 = 0;
        flag3 = 1;
        flag4 = 0;
    }
    if(sqDelta3 > 0.39 && sqDelta3 < 0.41) //awel ma yetla3 3al shasha hane3mel generate le function w ne7ot answer fel array w ne5ali el flag=1
    {
        flageq3 = true;
        eq3 = generateFunction(2,str3);

    }
    if(sqDelta3 < 0.4 || sqDelta3 > 110) // lama yeb2a bara el shasha han5ali el answer b dummy value w ne5ali el flag = 0
    {
        answers[2] = INT_MAX;
        flageq3 = false;
    }
    if(sqDelta3 > 0.4 && sqDelta3 < 110 && flageq3) // tool ma howa 3al shasha hanetba3o fel box beta3o
    {
        glColor3f(1,1,1);
        printString(eq3,47,sqDelta3-10);
    }
}
void drawSquare4(int startx,int starty)
{
    glColor3f(0.215, 0.662, 0.745);
    glBegin(GL_POLYGON); // Each set of 4 vertices form a quad
    glVertex2f(startx-sqWid/2, starty-sqWid/2+sqDelta4); // x, y
    glVertex2f(startx+sqWid/2, starty-sqWid/2+sqDelta4); // x, y
    glVertex2f(startx+sqWid/2, starty+sqWid/2+sqDelta4); // x, y
    glVertex2f(startx-sqWid/2, starty+sqWid/2+sqDelta4); // x, y
    glEnd();
    sqDelta4+=0.40;
    if(abs(sqDelta4) > 40 && flag4 == 0) //flag == 0 no new square is drawn
    {
        sqDelta1 = 0;
        flag4 = 1;
        flag1 = 0;
    }
    if(sqDelta4 > 0.39 && sqDelta4 < 0.41) //awel ma yetla3 3al shasha hane3mel generate le function w ne7ot answer fel array w ne5ali el flag=1
    {
        flageq4 = true;
        eq4 = generateFunction(3,str4);
    }
    if(sqDelta4 < 0.4 || sqDelta4 > 110) // lama yeb2a bara el shasha han5ali el answer b dummy value w ne5ali el flag = 0
    {
        answers[3] = INT_MAX;
        flageq4 = false;
    }
    if(sqDelta4 > 0.4 && sqDelta4 < 110 && flageq4) // tool ma howa 3al shasha hanetba3o fel box beta3o
    {
        glColor3f(1,1,1);
        printString(eq4,47,sqDelta4-10);
    }
}
void game()
{
    glColor3f(0.219, 0.168, 0.670);
    glBegin(GL_POLYGON); //Line in background
        glVertex2f(50,0);
        glVertex2f(51,0);
        glVertex2f(51,100);
        glVertex2f(50,100);
    glEnd();

    int startx=logWidth/2,starty=0;
    drawSquare1(startx,starty-10);
    if (sqDelta1>40){
        drawSquare2(startx,starty-10);
    }
    if(sqDelta2>40){
        drawSquare3(startx,starty-10);
    }
    if(sqDelta3>40){
        drawSquare4(startx,starty-10);
    }
    char sc[10];
    itoa(score,sc,10);
    printString(sc,5,90);
}

void init()
{

glClearColor(0.631, 0.631, 0.631,1); // COLOR BACKGROUND

glMatrixMode( GL_PROJECTION);
gluOrtho2D( 0.0, logWidth, 0.0, logHeight);

}


void drawButtons(){
    glColor3f(0.215, 0.662, 0.745); //
    glBegin(GL_POLYGON);
    glVertex2f(cx1-sqWid/2, cy1-sqHeight/2); // x, y
    glVertex2f(cx1+sqWid/2, cy1-sqHeight/2); // x, y
    glVertex2f(cx1+sqWid/2, cy1+sqHeight/2); // x, y
    glVertex2f(cx1-sqWid/2, cy1+sqHeight/2); // x, y
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(cx2-4-sqWid/2, cy2-sqHeight/2); // x, y
    glVertex2f(cx2+5+sqWid/2, cy2-sqHeight/2); // x, y
    glVertex2f(cx2+5+sqWid/2, cy2+sqHeight/2); // x, y
    glVertex2f(cx2-4-sqWid/2, cy2+sqHeight/2); // x, y
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(cx3-sqWid/2, cy3-sqHeight/2); // x, y
    glVertex2f(cx3+sqWid/2, cy3-sqHeight/2); // x, y
    glVertex2f(cx3+sqWid/2, cy3+sqHeight/2); // x, y
    glVertex2f(cx3-sqWid/2, cy3+sqHeight/2); // x, y
    glEnd();
}


void myDisplay()
{

    glClear( GL_COLOR_BUFFER_BIT);
    if(status==0)
    {
        drawButtons();
        glColor3f(1,1,1);
        printString("MA+H HERO",centerX-10,90);

        printString("PLAY ",cx1-5,cy1-1);
        printString("HIGH SCORES",cx2-10,cy2-1);
        printString("QUIT",cx3-5,cy3-1);

    }
    else if(status==1)
    {
        game();

    }
    else if(status==2)
    {

        printString("HIGHSCORES",40,85);
        int y=70;

        sprintf(h1,"%d. %d",1,highscore[0]);
        sprintf(h2,"%d. %d",2,highscore[1]);
        sprintf(h3,"%d. %d",3,highscore[2]);
        sprintf(h4,"%d. %d",4,highscore[3]);
        sprintf(h5,"%d. %d",5,highscore[4]);

        //printf("%s \t ", highscores);
        printString(h1,15,y);
        printString(h2,15,y-10);
        printString(h3,15,y-20);
        printString(h4,15,y-30);
        printString(h5,15,y-40);
    }
    else if(status==3)
    {
        exit(0);
    }
    else if(status ==4)
    {
        descSort();
        gameOver();
    }
    if(flag3asfora==false)
    {
        draw3asfora();
    }
    glFlush();
    glutSwapBuffers();

}

void mouseClick(int btn, int state, int x, int y) //mouse Function
{
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN && status==0)
    {
        mouseXX = x;
        mouseXX=0.5+1.0*mouseXX*logWidth/phyWidth;
        mouseYY = phyHeight - y;
        mouseYY=0.5+1.0*mouseYY*logHeight/phyHeight;
        if( mouseXX>=(cx1-sqWid/2) && mouseXX<=(cx1+sqWid/2) && mouseYY >=(cy1-sqWid/2) && mouseYY <=(cy1+sqWid/2))
        {
            flagTimer3=true;
            flagtimer2=true;
            flag3asfora=true;
            Timer2(1);
            Timer(1);
            Timer3(1);
            status=1;
            flag1 = 0;
            flag2 = 0;
            flag3 = 0;
            flag4 = 0;
            sqDelta1=0;
            sqDelta2 = 0;
            sqDelta3=0;
            sqDelta4=0;
            sq3asfora=100;
            score=0;
        }
        if( mouseXX>=(cx2-sqWid/2) && mouseXX<=(cx2+sqWid/2) && mouseYY >=(cy2-sqWid/2) && mouseYY <=(cy2+sqWid/2))
        {
            status=2;
        }
        if( mouseXX>=(cx3-sqWid/2) && mouseXX<=(cx3+sqWid/2) && mouseYY >=(cy3-sqWid/2) && mouseYY <=(cy3+sqWid/2))
        {
            status=3;
        }
    }
    if(btn == GLUT_LEFT_BUTTON && state==GLUT_DOWN && !flag3asfora)
    {
        printf("%d",mouseXX);
        if(mouseXX>=(centerX-sqWid/2) && mouseXX<=(centerX+sqWid/2) && mouseYY >=((centerY-sqWid/2)+sq3asfora) && mouseYY <= ((centerY+sqWid/2)+sq3asfora))
        {
            flagTimer1=false;
            timing=15000;
        }
    }
    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        status=0;
    }
    glutPostRedisplay();
}

int main( int argc, char ** argv)
{
    glutInit( &argc, argv);//
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100,100);//
    glutInitWindowSize(phyWidth, phyHeight);//
    glutCreateWindow("MATH HERO");
    init();
    glutDisplayFunc( myDisplay);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialkeyboard);
    glutMainLoop();
}

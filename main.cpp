#include <glut.h>
#include <cmath>
#include <ctime>
#include "ball.cpp"
#include "brick.cpp"

ball someBall(280, 7);
bit someBit;
brick bricks[10][15];

void generateBricks() //Генерируем массив рандомных блоков
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			bricks[i][j].isActive = rand() % 3;
			bricks[i][j].setCol(j);
			bricks[i][j].setRow(i);
			bricks[i][j].setHit(rand() % 2 + 1);
		}
	}
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.2, 0.8, 0.1);
	glRectf(someBit.getCoordX(), someBit.getCoordY(), someBit.getCoordX() + someBit.getWeight(), someBit.getCoordY() + someBit.getHeight());//Рисуем биту
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (float i = 0; i < 2 * 3.14; i += 3.14 / 4)//Рисуем мяч
	{
		glVertex2f(someBall.getCoordX() + someBall.getRadius() *sin(i), someBall.getCoordY() + someBall.getRadius()*cos(i));
	}
	glEnd();
	glBegin(GL_QUADS);
	for (int i = 0; i < 10; i++)//Рисуем массив блоков
	{
		for (int j = 0; j < 15; j++)
		{
			brick &b = bricks[i][j];
			if (b.isActive)
			{
				switch (b.getHit())
				{
				case 1:glColor3f(1.0, 1.0, 0.0); break;
				case 2:glColor3f(1.0, 0.0, 0.0); break;
				default:
					glColor3f(0.0, 0.0, 1.0);
					break;
				}
				glVertex2f(b.getCol()*b.getWeight() + 1, b.getRow()*b.getHeight() + 1);
				glVertex2f(b.getCol()*b.getWeight() + b.getWeight() - 1, b.getRow()*b.getHeight() + 1);
				glVertex2f(b.getCol()*b.getWeight() + b.getWeight() - 1, b.getRow()*b.getHeight() + b.getHeight() - 1);
				glVertex2f(b.getCol()*b.getWeight() + 1, b.getRow()*b.getHeight() + b.getHeight()- 1);
			}
		}
	}
	glEnd();
	glutSwapBuffers();
}
void Timer(int)
{
	if (someBall.isActive)
	{
		someBall.move(someBit);
		for (int i = 0; i < 10; i++)//Проходим по массиву блоков и проверяем столкнулся ли мяч с каждым блоком
		{
			for (int j = 0; j < 15; j++)
			{
				brick &b = bricks[i][j];
				if (someBall.isCollision(b))//В случае столкновения меняем направление мяча
				{
					if (abs(someBall.getCoordX() - b.getCol()*b.getWeight() - b.getWeight() / 2) < abs(someBall.getCoordY() - b.getRow()*b.getHeight() - b.getHeight() / 2))
					{
						someBall.setDirectionY(someBall.getDirectionY() * -1);
					}
					else if (abs(someBall.getCoordX() - b.getCol()*b.getWeight() - b.getWeight() / 2) > abs(someBall.getCoordY() - b.getRow()*b.getHeight() - b.getHeight() / 2))
					{
						someBall.setDirectionX(someBall.getDirectionX()* -1);
					}
					else
					{
						if (someBall.getDirectionX() > 0)
						{
							if (someBall.getCoordX() < b.getCol()*b.getWeight() + 1)
							{
								someBall.setDirectionX(someBall.getDirectionX()* -1);
							}
						}
						else if (someBall.getCoordX() > (b.getCol() + 1)*b.getWeight() - 1)
						{
							someBall.setDirectionX(someBall.getDirectionX()* -1);
						}
						if (someBall.getDirectionY() > 0)
						{
							if (someBall.getCoordY() < b.getRow()*b.getHeight() + 1)
							{
								someBall.setDirectionY(someBall.getDirectionY()* -1);
							}
						}
						else if (someBall.getCoordY() > (b.getRow() + 1)*b.getHeight() - 1)
						{
							someBall.setDirectionY(someBall.getDirectionY()* -1);
						}
					}
					b.setHit(b.getHit() - 1);
					if (b.getHit() < 1)
					{
						b.isActive = false;
					}
					i = 10;//Заканчиваем циклы, так как смысла проверять остальные блоки нет
					j = 15;
				}
			}
		}
	}
    Draw();
	glutTimerFunc(33, Timer, 0);
}
void MousePress(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && !someBall.isActive)//Если мяч не активен, делаем его активным, задаем направление по Х и Y и генерируем блоки
	{
		someBall.isActive = true;
		someBall.setDirectionX(4);
		someBall.setDirectionY(-4);
		generateBricks();
	}
}
void Mouse(int ax, int ay)
{
	someBit.setCoordX(ax - someBit.getWeight() / 2);//Двигаем биту по курсору
	if (!someBall.isActive)//Если мяч не активен, крепим его к бите
	{
		someBall.setCoordX(someBit.getCoordX() + someBit.getWeight() / 2);
		someBall.setCoordY (someBit.getCoordY() - someBall.getRadius());
	}
}

void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, 300, 300, 0, 1, 0);
}

int main(int argc, char** argv)
{
	srand(static_cast<unsigned int>(time(0)));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("CLICK TO START");
	glutDisplayFunc(Draw);
	glutTimerFunc(33, Timer, 0);
	glutPassiveMotionFunc(Mouse);
	glutMouseFunc(MousePress);
	Init();
	glutMainLoop();
	
	return 0;
}

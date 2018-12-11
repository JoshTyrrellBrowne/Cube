#include <Game.h>

bool updatable = false;

MyVector3 v3;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube")
{
	index = glGenLists(1);

	MyVector3 v1{ 1.0f, 1.0f, -15.0f };
	MyVector3 v2{ -1.0f, 1.0f, -15.0f };
	MyVector3 v3{ -1.0f, -1.0f, -15.0f };
	MyVector3 v4{ 1.0f, -1.0f, -15.0f };

	MyVector3 v5{ 1.0f, 1.0f, -5.0f };
	MyVector3 v6{ -1.0f, 1.0f, -5.0f };
	MyVector3 v7{ -1.0f, -1.0f, -5.0f };
	MyVector3 v8{ 1.0f, -1.0f, -5.0f };
}

Game::~Game(){}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning){

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		draw();
	}

}

void Game::initialize()
{
	isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	// glNewList(index, GL_COMPILE);
	// Creates a new Display List
	// Initalizes and Compiled to GPU
	// https://www.opengl.org/sdk/docs/man2/xhtml/glNewList.xml
	glNewList(index, GL_COMPILE);
	glBegin(GL_QUADS);
	{
		// whichever is last will be drawn ahead

		//Front Face - Blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -5.0f);
		glVertex3f(-1.0f, 1.0f, -5.0f);
		glVertex3f(-1.0f, -1.0f, -5.0f);
		glVertex3f(1.0f, -1.0f, -5.0f);

		//Back Face - GREEN
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, -15.0f);
		glVertex3f(-1.0f, 1.0f, -15.0f);
		glVertex3f(-1.0f, -1.0f, -15.0f);
		glVertex3f(1.0f, -1.0f, -15.0f);


		// Top Face - Red
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(1.0f, 1.0f, -5.0f);
		glVertex3f(-1.0f, 1.0f, -5.0f);
		glVertex3f(-1.0f, 1.0f, -15.0f);
		glVertex3f(1.0f, 1.0f, -15.0f);

		// Bottom Face - Yellow
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(-1.0f, -1.0f, -5.0f);
		glVertex3f(1.0f, -1.0f, -5.0f);
		glVertex3f(1.0f, -1.0f, -15.0f);
		glVertex3f(-1.0f, -1.0f, -15.0f);

		// Right Face - Pink
		glColor3f(1.0, 0.0, 1.0);
		glVertex3f(1.0f, 1.0f, -5.0f);
		glVertex3f(1.0f, -1.0f, -5.0f);
		glVertex3f(1.0f, -1.0f, -15.0f);
		glVertex3f(1.0f, 1.0f, -15.0f);

		// Left Face - White
		glColor3f(1.0, 2.0, 1.0);
		glVertex3f(-1.0f, -1.0f, -5.0f);
		glVertex3f(-1.0f, 1.0f, -5.0f);
		glVertex3f(-1.0f, 1.0f, -15.0f);
		glVertex3f(-1.0f, -1.0f, -15.0f);

		//Complete the faces of the Cube
	}
	glEnd();
	glEndList();
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!updatable)
		{
			updatable = true;
		}
		else
			updatable = false;
	}

	if (updatable)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}
	
	cout << "Update up" << endl;
}

void Game::draw()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cout << "Drawing Cube " << endl;
	//glLoadIdentity();
	//glRotatef(rotationAngle, 0, 0, 1); // Rotates the camera on Y Axis
	//glRotatef(rotationAngle, 0, 1, 0); // Rotates the camera on Y Axis
	checkKeyPress();

	glCallList(1);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

void Game::checkKeyPress()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		glRotatef(rotationAngle, 0, 0, 1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		glRotatef(rotationAngle, 0, 1, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		glRotatef(rotationAngle, 1, 0, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		glRotatef(rotationAngle, 0, 0, 1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		glLoadIdentity();
	}
}


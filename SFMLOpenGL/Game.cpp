#include <Game.h>

bool updatable = false;


Game::Game() : window(VideoMode(800, 600), "OpenGL Cube")
{
	index = glGenLists(1);

	startingVectors[0] = v1;
	startingVectors[1] = v2;
	startingVectors[2] = v3;
	startingVectors[3] = v4;
	startingVectors[4] = v5;
	startingVectors[5] = v6;
	startingVectors[6] = v7;
	startingVectors[7] = v8;

	
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

	glTranslatef(0, 0, -10);	// this moves the camera back

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
		glVertex3f(resultVectors[4].x, resultVectors[4].y, resultVectors[4].z);
		glVertex3f(resultVectors[5].x, resultVectors[5].y, resultVectors[5].z);
		glVertex3f(resultVectors[6].x, resultVectors[6].y, resultVectors[6].z);
		glVertex3f(resultVectors[7].x, resultVectors[7].y, resultVectors[7].z);

		//Back Face - GREEN
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(resultVectors[0].x, resultVectors[0].y, resultVectors[0].z);
		glVertex3f(resultVectors[1].x, resultVectors[1].y, resultVectors[1].z);
		glVertex3f(resultVectors[2].x, resultVectors[2].y, resultVectors[2].z);
		glVertex3f(resultVectors[3].x, resultVectors[3].y, resultVectors[3].z);


		// Top Face - Red
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(resultVectors[4].x, resultVectors[4].y, resultVectors[4].z);
		glVertex3f(resultVectors[5].x, resultVectors[5].y, resultVectors[5].z);
		glVertex3f(resultVectors[1].x, resultVectors[1].y, resultVectors[1].z);
		glVertex3f(resultVectors[0].x, resultVectors[0].y, resultVectors[0].z);

		// Bottom Face - Yellow
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(resultVectors[6].x, resultVectors[6].y, resultVectors[6].z);
		glVertex3f(resultVectors[7].x, resultVectors[7].y, resultVectors[7].z);
		glVertex3f(resultVectors[3].x, resultVectors[3].y, resultVectors[3].z);
		glVertex3f(resultVectors[2].x, resultVectors[2].y, resultVectors[2].z);

		// Right Face - Pink
		glColor3f(1.0, 0.0, 1.0);
		glVertex3f(resultVectors[4].x, resultVectors[4].y, resultVectors[4].z);
		glVertex3f(resultVectors[7].x, resultVectors[7].y, resultVectors[7].z);
		glVertex3f(resultVectors[3].x, resultVectors[3].y, resultVectors[3].z);
		glVertex3f(resultVectors[0].x, resultVectors[0].y, resultVectors[0].z);

		// Left Face - White
		glColor3f(1.0, 2.0, 1.0);
		glVertex3f(resultVectors[6].x, resultVectors[6].y, resultVectors[6].z);
		glVertex3f(resultVectors[5].x, resultVectors[5].y, resultVectors[5].z);
		glVertex3f(resultVectors[1].x, resultVectors[1].y, resultVectors[1].z);
		glVertex3f(resultVectors[2].x, resultVectors[2].y, resultVectors[2].z);

		//Complete the faces of the Cube
	}
	glEnd();
	glEndList();
}

void Game::update()
{
	checkKeyPress();
	updateResultVecs();

	glNewList(index, GL_COMPILE);
	glBegin(GL_QUADS);
	{
		// whichever is last will be drawn ahead

		//Front Face - Blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(resultVectors[4].x, resultVectors[4].y, resultVectors[4].z);
		glVertex3f(resultVectors[5].x, resultVectors[5].y, resultVectors[5].z);
		glVertex3f(resultVectors[6].x, resultVectors[6].y, resultVectors[6].z);
		glVertex3f(resultVectors[7].x, resultVectors[7].y, resultVectors[7].z);

		//Back Face - GREEN
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(resultVectors[0].x, resultVectors[0].y, resultVectors[0].z);
		glVertex3f(resultVectors[1].x, resultVectors[1].y, resultVectors[1].z);
		glVertex3f(resultVectors[2].x, resultVectors[2].y, resultVectors[2].z);
		glVertex3f(resultVectors[3].x, resultVectors[3].y, resultVectors[3].z);


		// Top Face - Red
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(resultVectors[4].x, resultVectors[4].y, resultVectors[4].z);
		glVertex3f(resultVectors[5].x, resultVectors[5].y, resultVectors[5].z);
		glVertex3f(resultVectors[1].x, resultVectors[1].y, resultVectors[1].z);
		glVertex3f(resultVectors[0].x, resultVectors[0].y, resultVectors[0].z);

		// Bottom Face - Yellow
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(resultVectors[6].x, resultVectors[6].y, resultVectors[6].z);
		glVertex3f(resultVectors[7].x, resultVectors[7].y, resultVectors[7].z);
		glVertex3f(resultVectors[3].x, resultVectors[3].y, resultVectors[3].z);
		glVertex3f(resultVectors[2].x, resultVectors[2].y, resultVectors[2].z);

		// Right Face - Pink
		glColor3f(1.0, 0.0, 1.0);
		glVertex3f(resultVectors[4].x, resultVectors[4].y, resultVectors[4].z);
		glVertex3f(resultVectors[7].x, resultVectors[7].y, resultVectors[7].z);
		glVertex3f(resultVectors[3].x, resultVectors[3].y, resultVectors[3].z);
		glVertex3f(resultVectors[0].x, resultVectors[0].y, resultVectors[0].z);

		// Left Face - White
		glColor3f(1.0, 2.0, 1.0);
		glVertex3f(resultVectors[6].x, resultVectors[6].y, resultVectors[6].z);
		glVertex3f(resultVectors[5].x, resultVectors[5].y, resultVectors[5].z);
		glVertex3f(resultVectors[1].x, resultVectors[1].y, resultVectors[1].z);
		glVertex3f(resultVectors[2].x, resultVectors[2].y, resultVectors[2].z);

		//Complete the faces of the Cube
	}
	glEnd();
	glEndList();


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
	// rotations...
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		for (int i = 0; i < 8; i++)
		{
			startingVectors[i] = (MyMatrix3::rotationX(0.001) * startingVectors[i]);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		for (int i = 0; i < 8; i++)
		{
			startingVectors[i] = (MyMatrix3::rotationX(-0.001) * startingVectors[i]);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		for (int i = 0; i < 8; i++)
		{
			startingVectors[i] = (MyMatrix3::rotationZ(0.001) * startingVectors[i]);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		for (int i = 0; i < 8; i++)
		{
			startingVectors[i] = (MyMatrix3::rotationZ(-0.001) * startingVectors[i]);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		glLoadIdentity();
	}
	// SCALE...
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		for (int i = 0; i < 8; i++)
		{
			startingVectors[i] = (MyMatrix3::scale(0.99) * startingVectors[i]);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		for (int i = 0; i < 8; i++)
		{
			startingVectors[i] = (MyMatrix3::scale(1.01) * startingVectors[i]);
		}
	}
	// TRANSLATION...
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		for (int i = 0; i < 8; i++)
		{
			displacementVectors[i] = displacementVectors[i] + MyVector3(0,0.01,0);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		for (int i = 0; i < 8; i++)
		{
			displacementVectors[i] = displacementVectors[i] + MyVector3(0, -0.01, 0);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		for (int i = 0; i < 8; i++)
		{
			displacementVectors[i] = displacementVectors[i] + MyVector3(0.01, 0, 0);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		for (int i = 0; i < 8; i++)
		{
			displacementVectors[i] = displacementVectors[i] + MyVector3(-0.01, 0, 0);
		}
	}

	/*vectors[i] = vectors[i] + (MyMatrix3::rotationX(-0.001) * vectors[i]);*/   //may be useful
}

void Game::updateResultVecs()
{
	for (int i = 0; i < 8; i++)
	{
		resultVectors[i] = startingVectors[i] + displacementVectors[i];
	}
}


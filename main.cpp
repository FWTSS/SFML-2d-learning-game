#include <SFML/Graphics.hpp>
#include <iostream> 
#include "map.h"
#include "view.h"
#include <sstream>
#include "mission.h"

using namespace sf;



////////////////////////////////////////////////////����� ������////////////////////////
class Player 
{
private: float x, y;
public:
	float w, h, dx, dy, speed;
	int dir, playerScore, health; // ����� ���������� ��� �������� ���������
	bool life; // ������ ���������� ������������ ��� ��� ����� ��������
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String F, float X, float Y, float W, float H) {
		playerScore = 0;
		dx = 0; dy = 0; speed = 0; dir = 0; health = 100; // ������������� ����� ������ � ������������
		life = true; // ������������� ���������� ����� ������ � true
		File = F;
		w = W; h = H;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(41, 33, 59));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
	void update(float time)
	{
		switch (dir)
		{
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
		}

		x += dx * time;
		y += dy * time;

		speed = 0;
		sprite.setPosition(x, y);
		interactionWithMap();//�������� �������, ���������� �� �������������� � ������
		if (health <= 0) { life = false; } // ���� ����� ������ ���� �� �������
	}


	void interactionWithMap()//�-��� �������������� � ������
	{

		for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������, �������������� � �������,, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
			for (int j = x / 32; j < (x + w) / 32; j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
			{
				if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
				{
					if (dy > 0)//���� �� ��� ����,
					{
						y = i * 32 - h;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
					}
					if (dy < 0)
					{
						y = i * 32 + 32;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
					}
					if (dx > 0)
					{
						x = j * 32 - w;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
					}
					if (dx < 0)
					{
						x = j * 32 + 32;//���������� ���� �����
					}
				}

				if (TileMap[i][j] == 's') //���� ������ ����� 's' (������)
				{ 
					playerScore++;
					TileMap[i][j] =' ';//������� ������, ���� ����� �����. ����� � �� �������, ������.
					std::cout << playerScore << std::endl;
				}
				if (TileMap[i][j] == 'f') // ���� ������ ����� 'f'(��������)
				{
					health -= 40;
					TileMap[i][j] =' ';
					std::cout << health << std::endl;
				}
				if (TileMap[i][j] == 'h') // ���� ������ ����� 'h' (������)
				{
					health += 20;
					TileMap[i][j] = ' ';
					std::cout << health << std::endl;
				}
			}
	}


	float getplayercoordinateX() {
		return x;
	}
	float getplayercoordinateY() {
		return y;
	}

};



int main()
{
	RenderWindow window(sf::VideoMode(1366, 768), "WWW",Style::Fullscreen);
	view.reset(sf::FloatRect(0, 0, 640, 480));

	Font font;//����� 
	font.loadFromFile("arial.ttf");  //�������� ������ ������ ���� ������
	
	Text text("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	
	text.setFillColor(Color::Black);
	

	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	Image quest_image;
	quest_image.loadFromFile("images/missionbg.jpg");
	quest_image.createMaskFromColor(Color(0, 0, 0));
	Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));  //���������� �����, ������� �������� ��������
	s_quest.setScale(0.6f, 0.6f);//���� ��������� ��������, => ������ ���� ������



	Player p("hero.png", 400, 400, 96.0, 96.0);

	bool showMissionText = true; // ���������� ����������, ���������� �� ��������� ������ ������ �� ������
		
	float CurrentFrame = 0;
	Clock clock;
	Clock gameTimeClock; // ���������� �������� �������, ����� ����� ������� ����� ����
	int gameTime = 0; // �������� ������� ����� � ����������������

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();

		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds(); else { view.move(1, 0); }  //������� ����� � �������� ��� ������, ���� ��� �����, ������������� ��� time ��� �� ����. ��� �� ��������� ������ ����
		clock.restart();
		time = time / 800;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if(event.type == Event::KeyPressed)//������� ������� �������
				if ((event.key.code == Keyboard::Tab)) // ���� ������ ������� TAB
				{
					switch (showMissionText) // ������������� ����������� �� ���������� ���������� showMissionText
					{
					case true: 
					{
						std::ostringstream playerHealthString; // ������ �������� ������
						playerHealthString << p.health; // ������� � ������ ��������

						std::ostringstream task; // ������ ��������� ������ ������
						task << getTextMission(getCurrentMission(p.getplayercoordinateX())); //���������� ������� getTextMission (��� ���������� ����� ������), ������� ��������� � �������� ��������� ������� getCurrentMission(������������ ����� ������), � ��� ��� �-��� ��������� � �������� ��������� ������� p.getplayercoordinateX() (��� �-��� ���������� ��� ���������� ������)
						text.setString("Health " + playerHealthString.str() + "\n" + task.str());
						
						showMissionText = false; // ��� ������ ��������� ������ ��� ��� �������� �� ������
						break;
					}
					case false:
					{
						text.setString(""); // ���� �� ������ ������� TAB, �� ���� ����� ������
						showMissionText = true; // � ��� ������ ��������� ����� ������ ������� TAB � ������� ����� �� �����
						break;
					}


					}




				}


		}

		float coordinatePlayerX, coordinatePlayerY = 0;
		coordinatePlayerX = p.getplayercoordinateX();
		coordinatePlayerY = p.getplayercoordinateY();

		
///////////////////////////////////////////���������� ���������� � ���������////////////////////////////////////////////////////////////////////////
		if (p.life == true)
		{
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				p.dir = 1; p.speed = 0.1;
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
			}

			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				p.dir = 0; p.speed = 0.1;
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
			}

			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				p.dir = 3; p.speed = 0.1;
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				p.dir = 2; p.speed = 0.1;
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
			}
			//getplayercoordinateforview(coordinatePlayerX, coordinatePlayerY); // ��������� ��������� ������ ��� �������� ������
		}
		//////////////////�������� ����� � ������� ���� ( ��� ������������ ���������� � ���� ����� ��� ���������� ���� � ����, � �� �����!!!)
		sf::Vector2i localPosition = Mouse::getPosition(window); // ������� � ������ ���������� ���� ������������ ���� (�,�). �� ���� ���� ���� 100�100 �� ���������� ������� ���������� ���� ����� (50,50)
		std::cout << " locPos " << localPosition.x << "\n"; //����������� ��� ����� ���� � ������� ���������� �
		
		if (localPosition.x < 3) { view.move(-0.2 * time, 0); } // ���� ������ � ����� ����� ������ �� ������ ������� �����
		if (localPosition.x > window.getSize().x-3) { view.move(0.2 * time, 0); } //������ ����-������
		if (localPosition.y > window.getSize().y-3) { view.move(0, 0.2 * time); } // ������ ���� - ����
		if (localPosition.y < 3) { view.move(0, -0.2 * time); } // ������� ���� - �����
		///////////////////////////////////////////////////




		p.update(time);



		window.setView(view);
		window.clear();

		/////////////////////////////������ �����/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));
				if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32)); // �������� ������
				if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32)); // �������� ������
				s_map.setPosition(j * 32, i * 32);

				window.draw(s_map);
			}
		if (!showMissionText) 
		{ 

			text.setPosition(view.getCenter().x + 120, view.getCenter().y - 120);// ������� ����� ���������� �����
			s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130); // ������� ��� ���� ��� �����
			window.draw(s_quest); 
			window.draw(text); 

		} //������ ������ ������ (��� ��� ������ ������). � ����� � �����. ��� ��� �������� �� ���������� ����������, ������� ������ ���� ��������� �� ������� ������� ���
		window.draw(p.sprite);
		
		window.display();
	}

	return 0;
}
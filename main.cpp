#include <SFML/Graphics.hpp>
#include <iostream> 
#include "map.h"
#include "view.h"
#include <sstream>
#include "mission.h"

using namespace sf;



////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player 
{
private: float x, y;
public:
	float w, h, dx, dy, speed;
	int dir, playerScore, health; // новая переменная для здоровья персонажа
	bool life; // булева переменная показывающая жив или мертв персонаж
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String F, float X, float Y, float W, float H) {
		playerScore = 0;
		dx = 0; dy = 0; speed = 0; dir = 0; health = 100; // инициализация жизни игрока в конструкторе
		life = true; // инициализация переменной жизни игрока в true
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
		interactionWithMap();//вызываем функцию, отвечающую за взаимодействие с картой
		if (health <= 0) { life = false; } // если жизнь меньше нуля то умираем
	}


	void interactionWithMap()//ф-ция взаимодействия с картой
	{

		for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по тайликам, контактирующим с игроком,, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
			for (int j = x / 32; j < (x + w) / 32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
			{
				if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
				{
					if (dy > 0)//если мы шли вниз,
					{
						y = i * 32 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
					}
					if (dy < 0)
					{
						y = i * 32 + 32;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
					}
					if (dx > 0)
					{
						x = j * 32 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
					}
					if (dx < 0)
					{
						x = j * 32 + 32;//аналогично идем влево
					}
				}

				if (TileMap[i][j] == 's') //если символ равен 's' (камень)
				{ 
					playerScore++;
					TileMap[i][j] =' ';//убираем камень, типа взяли бонус. можем и не убирать, кстати.
					std::cout << playerScore << std::endl;
				}
				if (TileMap[i][j] == 'f') // если символ равен 'f'(цветочек)
				{
					health -= 40;
					TileMap[i][j] =' ';
					std::cout << health << std::endl;
				}
				if (TileMap[i][j] == 'h') // если символ равен 'h' (сердце)
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

	Font font;//шрифт 
	font.loadFromFile("arial.ttf");  //передаем нашему шрифту файл шрифта
	
	Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	
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
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));  //приведение типов, размеры картинки исходные
	s_quest.setScale(0.6f, 0.6f);//чуть уменьшили картинку, => размер стал меньше



	Player p("hero.png", 400, 400, 96.0, 96.0);

	bool showMissionText = true; // логическая переменная, отвечающая за появление текста миссии на экране
		
	float CurrentFrame = 0;
	Clock clock;
	Clock gameTimeClock; // переменная игрового времени, здесь будем хранить время игры
	int gameTime = 0; // объявили игровое время и инициализировали

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();

		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds(); else { view.move(1, 0); }  //игровое время в секундах идёт вперед, пока жив игрок, перезагружать как time его не надо. оно не обновляет логику игры
		clock.restart();
		time = time / 800;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if(event.type == Event::KeyPressed)//событие нажатия клавиши
				if ((event.key.code == Keyboard::Tab)) // если нажата клавиша TAB
				{
					switch (showMissionText) // переключатель реагирующий на логическую переменную showMissionText
					{
					case true: 
					{
						std::ostringstream playerHealthString; // строка здоровья игрока
						playerHealthString << p.health; // заносим в строку здоровье

						std::ostringstream task; // строка состояния текста миссии
						task << getTextMission(getCurrentMission(p.getplayercoordinateX())); //вызывается функция getTextMission (она возвращает текст миссии), которая принимает в качестве аргумента функцию getCurrentMission(возвращающую номер миссии), а уже эта ф-ция принимает в качестве аргумента функцию p.getplayercoordinateX() (эта ф-ция возвращает Икс координату игрока)
						text.setString("Health " + playerHealthString.str() + "\n" + task.str());
						
						showMissionText = false; // эта строка позволяет убрать все что выведено на экране
						break;
					}
					case false:
					{
						text.setString(""); // если не нажата клавиша TAB, то этот текст пустой
						showMissionText = true; // а это строка позволяет снова нажать клавишу TAB и вывести текст на экран
						break;
					}


					}




				}


		}

		float coordinatePlayerX, coordinatePlayerY = 0;
		coordinatePlayerX = p.getplayercoordinateX();
		coordinatePlayerY = p.getplayercoordinateY();

		
///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
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
			//getplayercoordinateforview(coordinatePlayerX, coordinatePlayerY); // получение координат игрока для слежения камеры
		}
		//////////////////Скролинг карты с помощью мыши ( все используемые координаты в этом блоке это координаты мыши в окне, а не карты!!!)
		sf::Vector2i localPosition = Mouse::getPosition(window); // заносим в вектор координаты мыши относительно окна (х,у). То есть если окно 100х100 то координаты курсора посередине окна будут (50,50)
		std::cout << " locPos " << localPosition.x << "\n"; //отображение как ведет себя в консоли координата Х
		
		if (localPosition.x < 3) { view.move(-0.2 * time, 0); } // если курсор в левой части экрана то камеру двигаем влево
		if (localPosition.x > window.getSize().x-3) { view.move(0.2 * time, 0); } //правый край-вправо
		if (localPosition.y > window.getSize().y-3) { view.move(0, 0.2 * time); } // нижний край - вниз
		if (localPosition.y < 3) { view.move(0, -0.2 * time); } // верхний край - вверх
		///////////////////////////////////////////////////




		p.update(time);



		window.setView(view);
		window.clear();

		/////////////////////////////Рисуем карту/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));
				if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32)); // добавили цветок
				if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32)); // добавили сердце
				s_map.setPosition(j * 32, i * 32);

				window.draw(s_map);
			}
		if (!showMissionText) 
		{ 

			text.setPosition(view.getCenter().x + 120, view.getCenter().y - 120);// позицию всего текстового блока
			s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130); // позиция для фона для блока
			window.draw(s_quest); 
			window.draw(text); 

		} //рисуем спрайт свитка (фон для текста миссии). а затем и текст. все это завязано на логическую переменную, которая меняет свое состояние от нажатия клавиши ТАБ
		window.draw(p.sprite);
		
		window.display();
	}

	return 0;
}
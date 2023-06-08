# include <SFML/Graphics.hpp>

using namespace sf;

sf::View view; // создание объекта sfml view, который и является камерой

View getplayercoordinateforview(float x, float y) // функция которая считывает координаты игрока
{
	float tempX = x, tempY = y; // считываем координаты игрока и проверяем зашел ли он за край карты или нет

	if (x < 320) tempX = 320; // убираем из вида левую сторону
	if (y < 240) tempY = 240; // убираем из вида верхнюю часть 
	if (y > 554) tempY = 554; // убираем из вида нижнюю чать
	//if (x > 960)   tempX = 960; // убираем из вида правую сторону

	view.setCenter(tempX, tempY);
	//view.setCenter(x + 100, y); // передаем координаты игрока в объект view, тем самым следим за ним 
	return view; // возврат объекта view с обновленными координатами, то есть с новым местоположением
}


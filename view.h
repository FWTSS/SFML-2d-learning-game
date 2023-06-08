# include <SFML/Graphics.hpp>

using namespace sf;

sf::View view; // �������� ������� sfml view, ������� � �������� �������

View getplayercoordinateforview(float x, float y) // ������� ������� ��������� ���������� ������
{
	float tempX = x, tempY = y; // ��������� ���������� ������ � ��������� ����� �� �� �� ���� ����� ��� ���

	if (x < 320) tempX = 320; // ������� �� ���� ����� �������
	if (y < 240) tempY = 240; // ������� �� ���� ������� ����� 
	if (y > 554) tempY = 554; // ������� �� ���� ������ ����
	//if (x > 960)   tempX = 960; // ������� �� ���� ������ �������

	view.setCenter(tempX, tempY);
	//view.setCenter(x + 100, y); // �������� ���������� ������ � ������ view, ��� ����� ������ �� ��� 
	return view; // ������� ������� view � ������������ ������������, �� ���� � ����� ���������������
}


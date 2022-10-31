#include <SFML/Graphics.hpp>
#include<ctime>
#include<string>
#include<vector>

using namespace sf;

int size = 10;
const int bomb_count = 15;
bool gameOver = false;

struct Field
{
	bool mine=false;
	bool visible = false;
	bool checkbox = false;
	int value = 0,x,y;

};

std::vector<std::vector<Field>> fields;

bool check(int x,int y){ return x >= 0 && x < size && y >= 0 && y < size; }

int GetValue(Field var)
{
	int count = 0;
	//vector<pair<int, int>> pairs = { make_pair(var.x - 1,var.y - 1),make_pair(var.x,var.y - 1),make_pair(var.x + 1,var.y - 1),make_pair(var.x - 1,var.y),make_pair(var.x + 1,var.y),make_pair(var.x - 1,var.y + 1),make_pair(var.x,var.y + 1),make_pair(var.x + 1,var.y + 1) };
	//if (var.x == 2 && var.y == 9)
	//	count = count;
	//auto last_iter = remove_if(pairs.begin(), pairs.end(), [size](pair<int, int> vars) {return vars.first<0 | vars.first >= size | vars.second<0 | vars.second >= size; });
	//pairs.erase(last_iter, end(pairs));
	//*for (int i = 0; i < 8; )
	//{
	//	if (i == pairs.size())
	//		break;
	//	if (pairs[i].first < 0 | pairs[i].first >= size | pairs[i].second < 0 | pairs[i].second >= size)
	//	{
	//		pairs.erase(pairs.begin() + i);
	//	}
	//	else
	//		i++;
	//}*/
	//
	//for (pair<int,int> value : pairs)
	//{
	//	if (fields[value.second][value.first].status)
	//		count++;
	//}
	//return count;
	for (int dy = -1; dy < 2; dy++)
	{
		for (int dx = -1; dx < 2; dx++)
		{
			if (check(var.x + dx, var.y + dy) && fields[var.x + dx][var.y + dy].mine)
				count++;
		}
	}
	return count;
}

void OpenField(Field &var)
{
	if (var.visible)
		return;

	var.visible = true;
	if (var.value==0)
	{
		for (int dx = -1; dx < 2; dx++)
		{
			for (int dy = -1; dy < 2; dy++)
			{
			if(check(var.x+dx,var.y+dy))
				OpenField(fields[var.x + dx][var.y + dy]);
			}
		}		
	}
	//if (/*check(var.x,var.y)&&*/ var.value==0)
	//{
	//	var.visible = true;
	//	for (int dy = -1; dy < 2; dy++)
	//	{
	//		for (int dx = -1; dx < 2; dx++)
	//		{
	//			if (check(var.x + dx, var.y + dy)&& fields[var.x + dx][var.y + dy].visible != true/* && fields[var.y + dy][var.x + dx].visible*//* && fields[var.y + dy][var.x + dx].mine*/)
	//			{
	//				fields[var.x + dx][var.y + dy].visible=true;
	//				if (dy  == 0 | dx  == 0)
	//				{
	//					if (dx == 0 && dy == 0)
	//					{
	//					}
	//					else
	//					{
	//						if (fields[var.y + dy][var.x + dx].value == 0)
	//							v2(fields[var.y + dy][var.x + dx]);
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
	//Field &ptr = fields[var.y - 1][var.x];
	//if (!ptr.visible&&ptr.value)
	//{
	//	ptr.visible = true;
	//	v2(ptr);
	//}
	// ptr = fields[var.y + 1][var.x];
	//if (!ptr.visible&&ptr.value)
	//{
	//	ptr.visible = true;
	//	v2(ptr);
	//}
	// ptr = fields[var.y][var.x - 1];
	//if (!ptr.visible&&ptr.value)
	//{
	//	ptr.visible = true;
	//	v2(ptr);
	//}
	// ptr = fields[var.y][var.x + 1];
	//if (!ptr.visible&&ptr.value)
	//{
	//	ptr.visible = true;
	//	v2(ptr);
	//}
}


void q(String str, int x, int y, RenderWindow &windows)
{
	Font font;
	font.loadFromFile("ALGER.ttf");
	Text text(str, font);
	text.setCharacterSize(20);
	text.setPosition(x, y);
	windows.draw(text);
}

int menu()
{
	Texture t_VisibleTrue, t_VisibleFalse;
	t_VisibleTrue.loadFromFile("Resource/VisibleTrue.png");
	t_VisibleFalse.loadFromFile("Resource/VisibleFalse.png");

	Sprite s_VisibleTrue, s_VisibleFalse;
	s_VisibleTrue.setTexture(t_VisibleTrue);
	s_VisibleFalse.setTexture(t_VisibleFalse);

	//const Texture *ptr= &t_VisibleFalse;
	RenderWindow windows(sf::VideoMode(200, 200), "-----");
	/*setlocale(LC_ALL, "ru");
	Font font;
	font.loadFromFile("ALGER.ttf");
	Text text(L"сло", font);
	text.setCharacterSize(30);*/
	//text.setColor(sf::Color::Red);
	int field = 0;
	while (windows.isOpen())
	{
		windows.clear();
		sf::Event event;
		while (windows.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				windows.close();
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				int x = Mouse::getPosition(windows).x;
				int y = Mouse::getPosition(windows).y;

				if (x >= 5 && x <= 25 && y >= 10 && y <= 40)
					field = 0;
				if (x >= 5 && x <= 25 && y >= 40 && y <= 60)
					field = 1;
				if (x >= 5 && x <= 25 && y >= 70 && y <= 90)
					field = 2;

			}
			if (Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
			{
				return field * 5 + 5;
			}
		}
		RectangleShape R(Vector2f(20, 20));
		R.setTexture(&t_VisibleFalse);
		R.setTextureRect(IntRect(0, 0, 20, 20));
		for (int i = 10; i < 71; i += 30)
		{
			R.setPosition(5, i);
			windows.draw(R);

			s_VisibleFalse.setTextureRect(IntRect(20, 0, 20, 20));
			s_VisibleFalse.setPosition(5, field * 30 + 10);
			windows.draw(s_VisibleFalse);

		}
		/*R.setPosition(5, 10);
		windows.draw(R);*/

		q("EASY", 30, 10, windows);
		q("NORMAL", 30, 40, windows);
		q("HARD", 30, 70, windows);





		windows.display();
	}
	return 0;
}

int main()
{
	size = menu();
	fields.resize(size);

	for (int i = 0; i < size; i++)
		fields[i].resize(size);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			fields[i][j].x = i;
			fields[i][j].y = j;
		}
	}

	for (int i = 0; i < bomb_count;)
	{
		Field& link = fields[rand() % size][rand() % size];

		if (!link.mine)
		{
			link.mine = true;
			link.value = 9;
			i++;
		}
	}
	
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (!fields[i][j].mine)
				fields[i][j].value = GetValue(fields[i][j]);
		}
	}

	RenderWindow window(sf::VideoMode(200, 200), "-----");

		Texture t_VisibleTrue, t_VisibleFalse;
		t_VisibleTrue.loadFromFile("Resource/VisibleTrue.png");
		t_VisibleFalse.loadFromFile("Resource/VisibleFalse.png");
	
		Sprite s_VisibleTrue,s_VisibleFalse;
		s_VisibleTrue.setTexture(t_VisibleTrue);
		s_VisibleFalse.setTexture(t_VisibleFalse);
		
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			
			if (!gameOver)
			{
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					Field &link = fields[Mouse::getPosition(window).x / 20][Mouse::getPosition(window).y / 20];

					if (link.mine)
					{
						link.value = 10;
						gameOver = true;
					}
					else
						OpenField(link);
				}
				if (Mouse::isButtonPressed(Mouse::Right))
				{
					Field &link = fields[Mouse::getPosition(window).x / 20][Mouse::getPosition(window).y / 20];

					if (!link.visible)
					{
						if (link.checkbox)
							link.checkbox = false;
						else
							link.checkbox = true;
					}
				}
			}
		}

		window.clear();
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (fields[j][i].visible)
				{
					s_VisibleTrue.setTextureRect(IntRect(fields[j][i].value*20, 0, 20, 20));
					s_VisibleTrue.setPosition(j * 20, i * 20);
					window.draw(s_VisibleTrue);
				}
				else
				{
					s_VisibleFalse.setTextureRect(IntRect(0, 0, 20, 20));
					s_VisibleFalse.setPosition(j * 20, i * 20);
					window.draw(s_VisibleFalse);

					if (fields[j][i].checkbox)
					{
						s_VisibleFalse.setTextureRect(IntRect(20, 0, 20, 20));
						s_VisibleFalse.setPosition(j * 20, i * 20);
						window.draw(s_VisibleFalse);
					}
				}
			}
		}
		if (gameOver)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					if (fields[i][j].mine)
					{
						fields[i][j].visible = true;
					}
				}
			}
		}

		window.display();
	}
	return 0;
}

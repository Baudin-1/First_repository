#include <SFML/Graphics.hpp>
#include<ctime>

using namespace sf;




//const int w = 10, h = 15;//1
//bool x = false, gameover = false;
//int arr[h][w] = { 0 };

//struct point
//{
//	int x, y;
//}a[4], b[4];
//
//int arr2[7][4] =
//{
//	1,3,5,7,
//	2,4,5,7,
//	3,5,4,6,
//	3,5,4,7,
//	2,3,5,7,
//	3,5,7,6,
//	2,3,4,5
//};
//
//bool check()
//{
//	for (int i = 0; i < 4; i++)
//	{
//		if (a[i].x < 0 | a[i].x > w-1 | a[i].y >= h)
//			return true;
//
//		if (arr[a[i].y][a[i].x])
//			return true;
//	}
//
//	return false;
//};
const int size = 10;
int bomb_count = 5;
bool gameOver = false;

enum Status
{
	number,
	bomb
};

struct Field
{
	Status status;
	bool visible = false;
	bool checkbox = false;
	int value = 0,x,y;

}fields[size][size];

int v(Field var,const int size)
{
	using namespace std;
	int count = 0;

	vector<pair<int, int>> pairs = { make_pair(var.x - 1,var.y - 1),make_pair(var.x,var.y - 1),make_pair(var.x + 1,var.y - 1),make_pair(var.x - 1,var.y),make_pair(var.x + 1,var.y),make_pair(var.x - 1,var.y + 1),make_pair(var.x,var.y + 1),make_pair(var.x + 1,var.y + 1) };

	auto last_iter = remove_if(pairs.begin(), pairs.end(), [size](pair<int, int> vars) {return vars.first>0 && vars.first<size&&vars.second>0 && vars.second<size; });
	pairs.erase(last_iter, end(pairs));

	for (pair<int,int> value:pairs)
	{
		if (fields[value.first][value.second].status==bomb)
			count++;
	}
	return count;
}


int main()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			fields[i][j].x = j;
			fields[i][j].y = i;
		}
		
	}
	for (int i = 0; i < bomb_count;)
	{
		Field& link = fields[rand() % size][rand() % size];
		if (!link.status == bomb)
		{
			link.status = bomb;
			link.value = 10;
			i++;
		}
	}

	for each(Field var in fields)
	{
		if(var.status!=bomb)
		var.value=v(var, size);
	}

	//setlocale(LC_ALL, "ru");
	//srand(time(0));
	RenderWindow window(sf::VideoMode(200, 200), "-----");

	//Image i;
	//i.loadFromFile("C://Users/User/Desktop/плитка.png");
	//i.createMaskFromColor(Color(255, 255, 255));
	//Texture t,t2;
	//t.loadFromFile("C://Users/User/Desktop/фон.png");
	//t2.loadFromImage(i);
	//Texture t,t2;
	//t.loadFromFile("C://Users/User/Desktop/фон.png");

		Texture t_VisibleTrue, t_VisibleFalse;
		t_VisibleTrue.loadFromFile("C://Users/User/Desktop/VisibleTrue.png");
		t_VisibleFalse.loadFromFile("C://Users/User/Desktop/VisibleFalse.png");
	
		Sprite s_VisibleTrue,s_VisibleFalse;
		s_VisibleTrue.setTexture(t_VisibleTrue);
		s_VisibleFalse.setTexture(t_VisibleFalse);
		//s.setPosition(0, 0);
	/*Clock clock;
	float timer=0;
	float d = 0.7;
	bool Start = true;
	bool rotate = false;
	int n = rand() % 7;
	if (n == 6)
		x = true;
	
	int dx = 0;
	

	

	

	Sprite s,s1;
	s.setTexture(t);
	s.setPosition(0, 0);
	s1.setTexture(t2);
	s1.setPosition(90, 0);
*/
	while (window.isOpen()/*&& gameover ==false*/)
	{

		/*
		if (Start)
		{
			for (int i = 0; i < 4; i++)
			{
				a[i].x = arr2[n][i] % 2 +4;
				a[i].y = arr2[n][i] / 2 - 1;
			}
			Start = false;
		}

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;*/
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			/*if (Keyboard::isKeyPressed(Keyboard::D))
			{
				dx += 1;
			}
			if (Keyboard::isKeyPressed(Keyboard::A))
				dx -= 1;
			if (Keyboard::isKeyPressed(Keyboard::S))
				d = 0.2;
			if (Keyboard::isKeyPressed(Keyboard::W))
				rotate = true;*/
			if (!gameOver)
			{
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					Field& link = fields[Mouse::getPosition(window).x / 20][Mouse::getPosition(window).y / 20];
					link.visible = true;

					if (link.status == bomb)
						gameOver = true;
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

		/*for (int i = 0; i < 4; i++)
		{
			b[i] = a[i];
			a[i].x += dx/2;
		}
		if (check())
			for (int i = 0; i < 4; i++)
			{
				a[i] = b[i];
			}
		
		if (rotate)
		{
			if (x){}
			
			else
			{
				point p = a[1];
				for (int i = 0; i < 4; i++)
				{
					b[i] = a[i];
				}
				for (int i = 0; i < 4; i++)
				{

					int x = a[i].y - p.y;
					int y = a[i].x - p.x;
					a[i].x = p.x - x;
					a[i].y = p.y + y;
				}
				if (check())
					for (int i = 0; i < 4; i++)
					{
						a[i] = b[i];
					}

				rotate = false;
			}
		}
		
		
		if (timer > d)
		{
			for (int i = 0; i < 4; i++)
			{
				b[i] = a[i];
				a[i].y += 1;
			}
			if (check())
			{
				int n = rand() % 7;
				if (n == 6)
					x = true;
				else
					x = false;
				for (int i = 0; i < 4; i++)
				{
					arr[b[i].y][b[i].x] = 1;
				}
				for (int i = 0; i < 4; i++)
				{
					a[i].x = arr2[n][i] % 2 + 4;
					a[i].y = arr2[n][i] / 2 - 1;
				}
				for (int i = 0; i < 4; i++)
				{
					if (arr[a[i].y][a[i].x])
					{
						gameover = true;
					}
				}
			}
			timer = 0;
		}
		int k = h - 1;
		for (int i = h-1; i > 0; i--)
		{
			int count = 0;
			for (int j = 0; j < w;j++)
			{
				if (arr[i][j])
				{
					count++;
				}
				arr[k][j] = arr[i][j];
			}
			if (count<w)
				k--;
			else
			{
				k = k;
			}
		}*/
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
					if (fields[i][j].status==bomb)
					{
						fields[i][j].visible = true;
					}
				}
			}
		}







		//window.draw();
		/*if (!gameover)
			for (int i = 0; i < 4; i++)
			{
				s1.setPosition(a[i].x * 20, a[i].y * 20);
				window.draw(s1);
			}
		
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				if (arr[i][j])
				{
					s1.setPosition(j * 20,i * 20);
					window.draw(s1);
				}
			}
		}*/
		window.display();
		/*dx = 0;
		d = 0.7;*/
	}
	return 0;
}

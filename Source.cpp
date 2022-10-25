#include <SFML/Graphics.hpp>
#include<ctime>

using namespace sf;

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

	RenderWindow window(sf::VideoMode(200, 200), "-----");

		Texture t_VisibleTrue, t_VisibleFalse;
		t_VisibleTrue.loadFromFile("C://Users/User/Desktop/VisibleTrue.png");
		t_VisibleFalse.loadFromFile("C://Users/User/Desktop/VisibleFalse.png");
	
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
	
		window.display();
	}
	return 0;
}

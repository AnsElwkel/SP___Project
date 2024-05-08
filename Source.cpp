#include"lib.h"
namespace ELARABY
{
	pathFinder::pathFinder(int x, int y)
	{
		arr.resize(x);
		for (size_t i = 0; i < x; i++)
		{
			arr.at(i) = new object[y];
		}
		Enemy.resize(5,new enemy);
		pushing(x, 0, 0, y);
	}
	sf::Vector2f pathFinder::moveMent(object* fir, int x, int y, int x1, int y1, int gridsize, int i)
	{
		if (fir == &arr.at(max((int)Enemy[i]->start->position.x / gridsize - 1, x1))[(int)Enemy[i]->start->position.y / gridsize])
		{
			return { -1,0 };
		}
		else if (fir == &arr.at(min((int)Enemy[i]->start->position.x / gridsize + 1, x - 1))[(int)Enemy[i]->start->position.y / gridsize])
		{
			return { 1,0 };
		}
		else if (fir == &arr.at((int)Enemy[i]->start->position.x / gridsize)[max((int)Enemy[i]->start->position.y / gridsize - 1, y1)])
		{
			return { 0,-1 };
		}
		else if (fir == &arr.at((int)Enemy[i]->start->position.x / gridsize)[min((int)Enemy[i]->start->position.y / gridsize + 1, y - 1)])
		{
			return { 0,1 };
		}
		else
		{
			return { 0,0 };
		}
	}
	void pathFinder::pushing(int x, int x1, int y1, int y)
	{
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				if (j)
				{
					arr.at(i)[j].childs.push_back(&arr.at(i)[j - 1]);
				}
				if (i)
				{
					arr.at(i)[j].childs.push_back(&arr.at(i - 1)[j]);
				}
				if (j < y - 1)
				{
					arr.at(i)[j].childs.push_back(&arr.at(i)[j + 1]);
				}
				if (i < x - 1)
				{
					arr.at(i)[j].childs.push_back(&arr.at(i + 1)[j]);
				}
			}
		}
	}

	double  pathFinder::distance(object* ob1, object* ob2)
	{
		return sqrt((ob1->position.x - ob2->position.x) * (ob1->position.x - ob2->position.x) + (ob1->position.y - ob2->position.y) * (ob1->position.y - ob2->position.y));
	}
	void pathFinder::initial(Sprite shape[], int size)
	{
		for (size_t i = 0; i < size; i++)
		{
			Enemy[i]->start = &arr[(int)(shape[i].getPosition().x / 100)][(int)(shape[i].getPosition().y / 100)];
		}
	}
	void pathFinder::reset(int x, int x1, int y1, int y, int i)
	{
		for (int i = x1; i < x; i++)
		{
			for (int j = y1; j < y; j++)
			{
				arr.at(i)[j].visited = 0;
				arr.at(i)[j].global = INFINITY;
				arr.at(i)[j].local = INFINITY;
				arr.at(i)[j].father = nullptr;
			}
		}
		Enemy[i]->start->local = 0;
		Enemy[i]->start->global = distance(Enemy[i]->start, End);
	}

	bool pathFinder::isItReached(sf::Sprite& shape, int gridsize, int i)
	{
		if ((int)abs(((int)shape.getPosition().y / gridsize) * gridsize - shape.getPosition().y) < 2 && (int)abs((int)(shape.getPosition().x / gridsize) * gridsize - shape.getPosition().x) < 2)
		{
			Enemy[i]->start = &arr.at((int)(shape.getPosition().x) / gridsize)[((int)shape.getPosition().y / gridsize)];
			return true;
		}
		else if ((int)abs(((int)shape.getPosition().y / gridsize) * gridsize - Enemy[i]->start->position.y) > gridsize || (int)abs((int)(shape.getPosition().x / gridsize) * gridsize - Enemy[i]->start->position.x) > gridsize)
		{
			Enemy[i]->start = &arr.at((int)(shape.getPosition().x) / gridsize)[((int)shape.getPosition().y / gridsize)];
			return true;
		}
		return false;
	}

	object* pathFinder::getMove()
	{
		object* now = End, * walk = nullptr;
		while (now->father != nullptr)
		{
			now = now->father;
			if (now->father != nullptr)
			{
				walk = now;
			}
		}
		//cout << walk->position.x << " " << walk->position.y << endl;
		return walk;
	}


	void pathFinder::update(object* walk, sf::Sprite& shape, int x, int y, int x1, int y1, int gridsize, int i)
	{
		//cout << "here" << endl;
		//	cout << 1 << endl;
		if(walk!=nullptr)
		Enemy[i]->currentSpeed = moveMent(walk, x, y, x1, y1, gridsize, i);
		//shape.move(Enemy[i]->currentSpeed);
	}

	Vector2f pathFinder::Astar(int x, int x1, int y1, int y, sf::Sprite& monster, int gridsize, Sprite& player, int i)
	{

		Vector2i pos = { (int)(player.getPosition().x - player.getGlobalBounds().width / 2)/gridsize,(int)(player.getPosition().y - player.getGlobalBounds().height / 2)/gridsize };
		if (Enemy[i]->currentSpeed.x == -10 || isItReached(monster, gridsize, i))
		{
			End = &arr[pos.x][pos.y];
			reset(min(pos.x+115,140), max(pos.x-115,0), max(pos.y - 100, 0), min(pos.y+115,100), i);
			std::list<object*>tabor;
			tabor.push_back(Enemy[i]->start);
			while (!tabor.empty() && distance(tabor.back(), End))
			{
				tabor.sort([](object* ob1, object* ob2) {return ob1->global < ob2->global; });
				while (!tabor.empty() && tabor.front()->visited)
					tabor.pop_front();
				if (tabor.empty())
				{
					update(getMove(), monster, x, y, x1, y1, gridsize, i);
					return Enemy[i]->currentSpeed;
				}
				object* curr = tabor.front();
				curr->visited = 1;
				for (auto child : curr->childs)
				{
					float lo = curr->local + distance(curr, child);
					if (lo < child->local)
					{
						child->father = curr;
						child->local = lo;
						child->global = child->local + distance(child, End);
					}
					if (!child->visited && !child->block)
						tabor.push_back(child);
					if (child == End)
					{
						//cout << Enemy[i]->currentSpeed.x << Enemy[i]->currentSpeed.y << endl;
						update(getMove(), monster, x, y, x1, y1, gridsize, i);
						return Enemy[i]->currentSpeed;

					}
				}
			}
		}
		else
		{
			//cout << Enemy[i]->currentSpeed.x << Enemy[i]->currentSpeed.y << endl;
			return Enemy[i]->currentSpeed;
		}

	}
}

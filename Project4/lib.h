#pragma once
#include"includes.h"
#include<list>
using namespace sf;
using namespace std;
namespace ELARABY
{
	template <typename t>
	struct Vector
	{
		int size = 0, capacity = 64;
		t* vec = nullptr;
		Vector();
		Vector(int x);
		t& at(int x);
		bool empty();
		t& back();
		t& front();
		void setAt(int x, t y);
		void expand(int x);
		void resize(int x);
		void push_back(t x);
		void pop_back();
		void erase(t* erased);
		int getSize();
		void clear();
		t* begin();
		t& operator[](int index);
		t* end();
	};
	template<typename t>
	Vector<t>::Vector()
	{
		vec = new t[capacity];;
	}
	template<typename t>
	Vector<t>::Vector(int x)
	{
		size = x;
		capacity = 2 * x;
		vec = new t[capacity];
		for (int i = 0; i < x; i++)
		{
			vec[i] = 0;
		}
	}

	template<typename t>
	t& Vector<t>::at(int x)
	{
		return vec[x];
	}

	template<typename t>
	bool Vector<t>::empty()
	{
		return size;
	}

	template<typename t>
	t& Vector<t>::back()
	{
		return vec[size - 1];
	}


	template<typename t>
	t& Vector<t>::front()
	{
		return vec[0];
	}

	template<typename t>
	void Vector<t>::setAt(int x, t y)
	{
		vec[x] = y;
	}

	template<typename t>
	void Vector<t>::expand(int x)
	{
		capacity = x;
		t* vecCopy = vec;
		vec = new t[capacity];
		for (int i = 0; i < size; i++)
		{
			vec[i] = vecCopy[i];
		}
		delete[] vecCopy;
	}

	template<typename t>
	void Vector<t>::resize(int y)
	{
		size = y;
		capacity = 2 * y;
		vec = new t[capacity];
		for (int i = 0; i < y; i++)
		{
			vec[i] = 0;
		}
	}

	template<typename t>
	void Vector<t>::push_back(t x)
	{
		if (size < capacity)
		{
			vec[size] = x;
		}
		else
		{
			expand(size * 2);
			vec[size] = x;
		}
		size++;
	}

	template<typename t>
	void Vector<t>::pop_back()
	{
		if (size)
		{
			vec[size - 1] = 0;
			size--;
		}
	}

	template<typename t>
	void Vector<t>::erase(t* erased)
	{
		t* vecCopy = vec;
		vec = new t[size - 1];
		for (int i = 0, j = 0; i < size; i++)
		{
			if (&vecCopy[i] != erased)
			{
				vec[j] = vecCopy[i];
				j++;
			}
		}
		size--;
		delete[] vecCopy;
	}

	template<typename t>
	int Vector<t>::getSize()
	{
		return size;
	}

	template<typename t>
	void Vector<t>::clear()
	{
		size = 0;
		capacity = 64;
		delete[] vec;
		vec = nullptr;
		vec = new t[capacity];
	}

	template<typename t>
	t* Vector<t>::begin()
	{
		return &vec[0];
	}

	template<typename t>
	t& Vector<t>::operator[](int index)
	{
		return vec[index];
	}

	template<typename t>
	t* Vector<t>::end()
	{
		return &vec[size];
	}
	template<typename t>
	struct Stack
	{
		int size=0;
		struct node
		{
			t value;
			node* next;
		};
		node* top;
		void push(t x);
		void pop();
		bool empty();
		t front();
		Stack();
	};

	template<typename t>
	Stack<t>::Stack()
	{
		top = new node;
		top->value = 0;
		top->next = nullptr;

	}
	template<typename t>
	void Stack<t>::push(t x)
	{
		node* temp = top;
		top = new node;
		top->value = x;
		top->next = temp;
		size++;
	}

	template<typename t>
	t Stack<t>::front()
	{
		return top->value;
	}

	template<typename t>
	void Stack<t>::pop()
	{
		if (top->next != nullptr)
		{
			node* temp = top->next;
			delete top;
			top = temp;
			size--;
		}
	}

	template<typename t>
	bool Stack<t>::empty()
	{
		return size;
	}

	struct object
	{
		long double global = INFINITY, local = INFINITY;
		bool visited = 0, block = 0;
		std::vector<object*>childs;
		object* father;
		Vector2f position;
	};
	struct enemy
	{
		Vector2f currentSpeed = { -10,0 };
		object* start = nullptr;
	};
	struct pathFinder
	{
		Vector<object*>arr;
		object* End = nullptr;
		vector<enemy*>Enemy;
		sf::Vector2f moveMent(object* fir, int x, int y, int x1, int y1, int gridsize, int i);
		pathFinder(int, int);
		void update(object* walk, sf::Sprite& shape, int x, int y, int x1, int y1, int gridsize, int i);
		Vector2f Astar(int x, int x1, int y1, int y, sf::Sprite& monster, int gridsize, Sprite& player,int i);
		double distance(object* ob1, object* ob2);
		void initial(Sprite arr[], int size);
		object* getMove();
		void reset(int x, int x1, int y1, int y, int i);
		bool isItReached(sf::Sprite& shape, int gridsize, int i);
		void pushing(int x, int x1, int y1, int y);
	};

}
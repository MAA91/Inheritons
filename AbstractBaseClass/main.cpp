#include <iostream>
using namespace std;

class Animal
{
public:
	virtual void sound() = 0;
};

class Cat:public Animal
{

};

class Tiger :public Cat
{
public: 
	void sound() override
	{
		cout << "rrrrrr" << endl;
	}
};

class HomeCat :public Cat
{
public:
	void sound()override
	{
		cout << "mew - mew";
	}
};

void main()
{
	setlocale(0, "");
	//Animal animal;
	//Cat cat;
	Tiger tiger;
	tiger.sound();
	HomeCat Tom;
	Tom.sound();
}
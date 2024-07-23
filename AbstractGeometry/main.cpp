#define _USE_MATH_DEFINES
#include<Windows.h>
#include <iostream>
#include<cmath>
using namespace std;

namespace Geometry
{
	enum Color
	{
		RED = 0x000000FF,
		DARK_RED = 0x00000077,
		GREEN = 0x0000FF00,
		BLUE = 0x00FF0000,
		YELLOW = 0x0000FFFF,

		CONSOLE_BLUE = 0x99,
		CONSOLE_GREEN = 0xAA,
		CONSOLE_RED = 0xCC,
		CONSOLE_DEFAULT = 0x07
	};

#define SHAPE_TAKE_PARAMETERS	unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color
#define SHAPE_GIVE_PARAMETERS	start_x, start_y, line_width, color
	class Shape
	{
	protected:
		Color color;
		static const int MIN_START_X = 100;
		static const int MAX_START_X = 1000;
		static const int MIN_START_Y = 100;
		static const int MAX_START_Y = 700;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 31;
		static const int MIN_SIZE = 50;
		static const int MAX_SIZE = 550;

		unsigned int start_x;
		unsigned int start_y;
		unsigned int line_width;
	public:
		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		Color get_color()const
		{
			return color;
		}
		void set_color(Color color)
		{
			this->color = color;
		}
		unsigned int get_start_x()const
		{
			return start_x;
		}
		unsigned int get_start_y()const
		{
			return start_y;
		}
		unsigned int get_line_width()const
		{
			return line_width;
		}
		void set_start_x(unsigned int start_x)
		{
			if (start_x < MIN_START_X)
				start_x = MIN_START_X;
			if (start_x > MAX_START_X)
				start_x = MAX_START_X;
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			if (start_y < MIN_START_Y)
				start_y = MIN_START_Y;
			if (start_y > MAX_START_Y)
				start_y = MAX_START_Y;
			this->start_y = start_y;
		}
		void set_line_width(unsigned int line_width)
		{
			if (line_width < MIN_LINE_WIDTH)
				line_width = MIN_LINE_WIDTH;
			if (start_x > MAX_LINE_WIDTH)
				line_width = MAX_LINE_WIDTH;
			this->line_width = line_width;
		}
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры:" << get_perimeter() << endl;
			draw();
		}

		double filter_size(double size)
		{
			if (size < MIN_SIZE)size = MIN_SIZE;
			if (size > MAX_SIZE)size = MAX_SIZE;
			return size;
		}
	};

	class Rectangle :public Shape
	{
		double width;
		double height;
	public:
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_width(width);
			set_height(height);
		}
		~Rectangle() {}
		double get_area()const override
		{
			return width * height;
		}
		double get_perimeter()const override
		{
			return (width + height) * 2;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);	
			HPEN hPen = CreatePen(PS_SOLID, line_width, get_color());

			HBRUSH hBrush = CreateSolidBrush(get_color());

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height);

			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
		}
		double get_width()const
		{
			return width;
		}
		double get_height()const
		{
			return height;
		}
		void set_width(double width)
		{
			this->width = filter_size(width);
		}
		void set_height(double height)
		{
			this->height = filter_size(height);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина: " << get_width() << endl;
			cout << "Высота: " << get_height() << endl;
			Shape::info();
		}
	};
	class Square :public Rectangle
	{
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
		~Square() {}
	};

	class Circle : public Shape
	{
		double radius;
	public:

		Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_radius(radius);
		}
		~Circle() {}
		void set_radius(double radius)
		{
			this->radius = filter_size(radius);
		}
		double get_radius()const
		{
			return radius;
		}
		double get_diameter()const
		{
			return 2 * radius;
		}
		double get_area()const override
		{
			return M_PI * radius * radius;
		}
		double get_perimeter()const override
		{
			return M_PI * get_diameter();
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		} 

		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус: " << radius << endl;
			this->draw();
		}
	};

	class Triangle :public Shape
	{
	public:
		virtual double get_height()const = 0;
		Triangle(SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS) {}
		~Triangle() {}
		void info() const override
		{
			cout << "Высота треугольника: " << get_height();
		}
	};
	class EquilateralTriangle :public Triangle
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			this->side = filter_size(side);
		}
		double get_height()const override
		{
			return sqrt(side * side - side * side / 4);
		}
		double get_area()const override
		{
			return side / 2 * get_height();
		}
		double get_perimeter()const override
		{
			return side * 3;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT apt[] = 
			{
				{start_x, start_y + side },
				{start_x + side, start_y + side },
				{start_x + side/2, start_y + side - get_height()},
			};
			::Polygon(hdc, apt, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}

		EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		~EquilateralTriangle() {}
		void info() const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны: " << side << endl;
			Triangle::info();
			this->draw();
		}
	};
	class IsoscelesTriangle : public Triangle
	{
		double side;
		double base;
	public: 
		double get_side()const
		{
			return side;
		}
		double get_base()const
		{
			return base;
		}
		void set_side(double side)
		{
			this->side = filter_size(side);
		}
		void set_base(double base)
		{
			this->base = filter_size(base);
		}
		double get_height()const override
		{
			return sqrt(side * side - base * base / 4);
		}
		double get_area()const override
		{
			return side * get_height() / 2;
		}
		double get_perimeter()const override
		{
			return 2 * side + base;
		}
		void draw() const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT apt[] =
			{
				{start_x, start_y + side },
				{start_x + base, start_y + side },
				{start_x + base / 2, start_y + side - get_height()},
			};
			::Polygon(hdc, apt, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}

		IsoscelesTriangle(double side, double base, SHAPE_TAKE_PARAMETERS) : Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_base(base);
			set_side(side);
		}
		~IsoscelesTriangle() {}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны: " << side << endl;
			cout << "Длина основания: " << base << endl;
			Triangle::info();
			this->draw();
		}
	};
	class RectangularTriangle : public Triangle
	{
		double catheter1;
		double catheter2;
	public:
		double get_catheter1()const
		{
			return catheter1;
		}
		double get_catheter2()const
		{
			return catheter2;
		}
		void set_catheter1(double catheter1)
		{
			this->catheter1 = filter_size(catheter1);
		}
		void set_catheter2(double catheter2)
		{
			this->catheter2 = filter_size(catheter2);
		}
		double get_area()const override
		{
			return catheter1 * catheter2 / 2;
		}
		double get_hypotenuse()const
		{
			return sqrt(catheter1 * catheter1 + catheter2 * catheter2);
		}
		double get_height()const override
		{
			return get_area() / get_hypotenuse();
		}
		double get_perimeter()const override
		{
			return catheter1 + catheter2 + get_hypotenuse();
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT apt[] =
			{
				{start_x, start_y },
				{start_x, start_y + catheter1 },
				{start_x + catheter2, start_y + catheter1},
			};
			::Polygon(hdc, apt, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		
		RectangularTriangle(double catheter1, double catheter2, SHAPE_TAKE_PARAMETERS): Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_catheter1(catheter1);
			set_catheter2(catheter2);
		}
		~RectangularTriangle() {}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Катет 1: " << catheter1 << endl;
			cout << "Катет 2: " << catheter2 << endl;
			cout << "Гипотенуза: " << get_hypotenuse() << endl;
			Triangle::info();
			this->draw();
		}
	};
}

void main()
{
	setlocale(0, "");

	Geometry::RectangularTriangle r_triangle(150, 200, 500, 200, 5, Geometry::Color::YELLOW);
	r_triangle.info();
}
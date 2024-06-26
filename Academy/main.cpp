//Academy
#include<iostream>

using namespace std;

#define delimetr "\n----------------\n"

#define HUMAN_TAKE_PARAMETRS const std::string last_name, std::string first_name, unsigned int age
#define HUMAN_GIVE_PARAMETRS last_name, first_name, age
class Human
{
	std::string last_name;
	std::string first_name;
	unsigned int age;
public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	const unsigned int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(const unsigned int age)
	{
		this->age = age;
	}

	//Constructors
	Human(HUMAN_TAKE_PARAMETRS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor\t" << this << endl;
	}
	virtual ~Human()
	{
		cout << "HDestructor\t" << this << endl;
	}

	//Metods
	virtual void print()const
	{
		cout << last_name << " " << first_name << " " << age;
	}
	virtual void info()const
	{
		//this->print();
		cout << last_name << " " << first_name << " " << age;
		cout << endl;
	}

	//Operators
};

#define STUDENT_TAKE_PARAMETRS const std::string speciality, std::string group, double rating, double attendanse
#define STUDENT_GIVE_PARAMETRS speciality, group, rating, attendanse
class Student :public Human
{
	std::string speciality;
	std::string group;
	double rating;
	double attendanse;

public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	const std::string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendanse()const
	{
		return attendanse;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendanse(double attendanse)
	{
		this->attendanse = attendanse;
	}

	//Constructors
	Student(HUMAN_TAKE_PARAMETRS, STUDENT_TAKE_PARAMETRS):Human(HUMAN_GIVE_PARAMETRS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendanse(attendanse);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student() override
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//Metods
	void print() const override
	{
		Human::info();
		cout << speciality << " " << group << " " << rating << " " << attendanse;
	}
	void info()const override
	{
		//this->print();
		Human::info();
		cout << speciality << " " << group << " " << rating << " " << attendanse;
		cout << "\n";
	}
};


#define GRADUATE_TAKE_PARAMETRS std::string subject
#define GRADUATE_GIVE_PARAMETRS subject
class Graduate: public Student
{
	std::string subject;
public:
	const std::string& get_subject()const
	{
		return subject;
	}
	void set_subject(std::string& subject)
	{
		this->subject = subject;
	}

	//Constructors
	Graduate(HUMAN_TAKE_PARAMETRS, STUDENT_TAKE_PARAMETRS, std::string subject): Student(HUMAN_GIVE_PARAMETRS, STUDENT_GIVE_PARAMETRS)
	{
		set_subject(subject);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate() override
	{
		cout << "GDestructor:\t" << this << endl;
	}

	//Metods
	void print()const override
	{
		Student::info();
		cout << subject;
	}
	void info()const override
	{
		//this->print();
		Student::info();
		cout << subject;
		cout << endl;
	}
};

#define TEACHER_TAKE_PARAMETRS std::string speciality, unsigned int experiance
#define TEACHER_GIVE_PARAMETRS speciality, experiance
class Teacher: public Human
{
	std::string speciality;
	unsigned int experiance;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	unsigned int get_experiance()const
	{
		return experiance;
	}
	void set_speciality(std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experiance(unsigned int experiance)
	{
		this->experiance = experiance;
	}

	//Constructors
	Teacher(HUMAN_TAKE_PARAMETRS, TEACHER_TAKE_PARAMETRS):Human(HUMAN_GIVE_PARAMETRS)
	{
		set_speciality(speciality);
		set_experiance(experiance);
		cout << "TConstuctor:\t" << this << endl;
	}
	~Teacher() override
	{
		cout << "TDestructor:\t" << this << endl;
	}

	//Metods
	void print()const override
	{
		Human::info();
		cout << speciality << " " << experiance;
	}
	void info()const override
	{
		//this->print();
		Human::info();
		cout << speciality << " " << experiance;
		cout << endl;
	}
};

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	obj.print();
	return os;
}

//#define INHERITANCE_CHECK
void main()
{
	setlocale(0, "");
#ifdef INHERITANCE_CHECK
	Human human("Vercetty", "Tommy", 30);
	human.info();

	Student student("Pinkman", "Jessy", 22, "Chemystry", "WW_220", 45, 26);
	student.info();

	Teacher teacher("White", "Wolter", 50, "Chemystry", 35);
	teacher.info();
#endif // INHERITANCE_CHECK

	Human* group[] =
	{
		new Student("Pinkman", "Jessy", 22, "Chemystry", "WW_220", 45, 26),
		new Teacher("White", "Wolter", 50, "Chemystry", 35),
		new Graduate("Conor", "McD", 30, "C", "BOW", 98, 100, "How win every time"),
		new Student("Vercetty", "Tommy", 30, "Theft", "Vice", 97, 98)
	};
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		cout << delimetr;
		cout << *group[i] << endl;// ->info();
	}
	cout << delimetr;
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
		delete group[i];
}
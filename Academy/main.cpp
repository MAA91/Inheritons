//Academy
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

#define delimetr "\n----------------\n"

#define HUMAN_TAKE_PARAMETRS const std::string last_name, std::string first_name, unsigned int age
#define HUMAN_GIVE_PARAMETRS last_name, first_name, age
class Human
{
	static const int HUMAN_TYPE_WIDTH = 10;
	static const int LAST_NAME_WIDTH = 15;
	static const int FIRST_NAME_WIDTH = 15;
	static const int AGE_WIDTH = 5;
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
	virtual void info()const
	{
		cout << last_name << " " << first_name << " " << age;
	}
	virtual std::ostream& info(std::ostream& os)const
	{
		return os << last_name << " " << first_name << " " << age;
	}
	virtual std::ofstream& write(std::ofstream& ofs)const
	{
		ofs.width(HUMAN_TYPE_WIDTH); ofs << left << std::string(strchr(typeid(*this).name(), ' ') + 1) + ":";
		ofs.width(LAST_NAME_WIDTH); ofs << left << last_name;
		ofs.width(FIRST_NAME_WIDTH); ofs << left << first_name; 
		ofs.width(AGE_WIDTH);  ofs << left << age;
		return ofs;
	}
	virtual std::ifstream& read(std::ifstream& ifs)
	{
		ifs >> last_name >> first_name >> age;
		return ifs;
	}
	//Operators
};

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.info(os);
}
std::ofstream& operator<<(std::ofstream& ofs, const Human& obj)
{
	return obj.write(ofs);
}
std::ifstream& operator>> (std::ifstream& is, Human& obj)
{
	return obj.read(is);
}

#define STUDENT_TAKE_PARAMETRS const std::string speciality, std::string group, double rating, double attendanse
#define STUDENT_GIVE_PARAMETRS speciality, group, rating, attendanse
class Student :public Human
{
	static const int SPECIALITY_WIDTH = 25;
	static const int GROUP_WIDTH = 8;
	static const int RATING_WIDTH = 8;
	static const int ATTENDANSE_WIDTH = 8;
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
	void info()const override
	{
		Human::info();
		cout << speciality << " " << group << " " << rating << " " << attendanse << "\n";
	}
	std::ostream& info(std::ostream& os)const override
	{
		return Human::info(os) << " " << speciality << " " << group << " " << rating << " " << attendanse;
	}
	std::ofstream& write(std::ofstream& ofs)const override 
	{
		Human::write(ofs);
		ofs.width(SPECIALITY_WIDTH);	ofs << left <<  speciality;
		ofs.width(GROUP_WIDTH);			ofs << left <<  group;
		ofs.width(RATING_WIDTH);		ofs << left <<  rating;
		ofs.width(ATTENDANSE_WIDTH);	ofs << left <<  attendanse;
		return ofs;
	}
	std::ifstream& read(std::ifstream& ifs)override
	{
		Human::read(ifs) >> speciality >> group >> rating >> attendanse;
		return ifs;
	}
};


#define GRADUATE_TAKE_PARAMETRS std::string subject
#define GRADUATE_GIVE_PARAMETRS subject
class Graduate: public Student
{
	static const int SUBJECT_WIDTH = 32;
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
	Graduate(HUMAN_TAKE_PARAMETRS, STUDENT_TAKE_PARAMETRS, std::string subject) : Student(HUMAN_GIVE_PARAMETRS, STUDENT_GIVE_PARAMETRS)
	{
		set_subject(subject);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate() override
	{
		cout << "GDestructor:\t" << this << endl;
	}

	//Metods
	void info()const override
	{
		Student::info();
		cout << subject << endl;
	}
	std::ostream& info(std::ostream& os)const override
	{
		 return Student::info(os) << " " << subject;
	}
	std::ofstream& write(std::ofstream& ofs)const override
	{
		Student::write(ofs);
		ofs.width(SUBJECT_WIDTH); ofs << subject;
		return ofs;
	}
	std::ifstream& read(std::ifstream& ifs)override
	{
		Student::read(ifs);
		std::getline(ifs, subject);
		return ifs;
	}
};

#define TEACHER_TAKE_PARAMETRS std::string speciality, unsigned int experiance
#define TEACHER_GIVE_PARAMETRS speciality, experiance
class Teacher: public Human
{
	static const int SPECIALITY_WIGTH = 25;
	static const int EXPERIANCE_WIGTH = 15;
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
	void info()const override
	{
		Human::info();
		cout << speciality << " " << experiance << endl;
	}
	std::ostream& info(std::ostream& os)const override
	{
		return Human::info(os) << " " << speciality << " " << experiance;
	}
	std::ofstream& write(std::ofstream& ofs)const override
	{
		Human::write(ofs);
		ofs.width(SPECIALITY_WIGTH); ofs << left <<  speciality;
		ofs.width(EXPERIANCE_WIGTH); ofs << left <<  experiance;
		return ofs;
	}
	std::ifstream& read(std::ifstream& ifs)
	{
		Human::read(ifs);// >> speciality >> experiance;
		const int SIZE = SPECIALITY_WIGTH;
		char buffer[SIZE]{};
		ifs.read(buffer, SIZE);
		int poz = strrchr(buffer, ' ') - buffer;
		buffer[poz] = 0;
		this->speciality = buffer;
		ifs >> experiance;
		return ifs;
	}
};

void Print(Human* group[], const int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << delimetr;
		cout << *group[i] << endl;// ->info();
	}
	cout << delimetr;
}
void Clear(Human* group[], const int size)
{
	for (int i = 0; i < size; i++)
		delete[] group[i];
}

void Save(Human* group[], const int size, const std::string& filename)
{
	std::ofstream fout(filename);
	for (int i = 0; i < size; i++)
		fout << *group[i] << endl;
	fout.close();
	/*std::string cmd = "notepad " + filename;
	system(cmd.c_str());*/
}
Human* HumanFactory(const std::string type)
{
	Human* human = nullptr;
	if (type == "Human:")human = new Human("", "", 0);
	else if (type == "Student:")human = new Student("", "", 0, "", "", 0, 0);
	else if (type == "Teacher:")human = new Teacher("", "", 0, "", 0);
	else if (type == "Graduate:")human = new Graduate("", "", 0, "", "", 0, 0, "");
	return human;
}
Human** load(const std::string& filename, int& size)
{
	Human** group = nullptr;
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		size = 0;
		while (!fin.eof())
		{
			std::string buffer;
			std::getline(fin, buffer);
			if (buffer.size() < 16) continue;
			size++;
		}
		//cout << size << endl;
		group = new Human* [size] {};

		//cout << fin.tellg() << endl;
		fin.clear();
		fin.seekg(0);
		//cout << fin.tellg() << endl;

		for (int i = 0; i < size; i++)
		{
			std::string type;
			fin >> type;
			group[i] = HumanFactory(type);
			if (group[i])fin >> *group[i];
			else continue;
		}

		fin.close();
	}
	else
		std::cerr << "Error: File not found";
	return group;
}

//#define INHERITANCE_CHECK
//#define POLIMORFISM_CHECK

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

#ifdef POLIMORFISM_CHECK
	Human* group[] =
	{
		new Student("Pinkman", "Jessy", 22, "Chemystry", "WW_220", 45, 26),
		new Teacher("White", "Wolter", 50, "Chemystry", 35),
		new Graduate("Shredor", "Hank", 40, "Criminalistic", "OBN", 80, 90, "How to catch Hesinberg"),
		new Student("Vercetty", "Tommy", 30, "Theft", "Vice", 97, 98),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20)
	};

	Print(group, sizeof(group) / sizeof(group[0]));
	Save(group, sizeof(group) / sizeof(group[0]), "group.txt");
	Clear(group, sizeof(group) / sizeof(group[0]));
#endif //POLIMORFISM_CHECK

	int size = 0;
	Human** group = load("group.txt", size);
	Print(group, size);
	Clear(group, size);
}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<ctime>

using namespace std;
#define  WRITE_TO_FILE
#define  READ_TO_FILE
void main()
{
	setlocale(0, "");
#ifdef WRITE_TO_FILE

	std::ofstream fout;
	fout.open("File.txt");
	//fout << "Hello";

	time_t now = time(NULL);
	fout << ctime(&now) << endl;

	fout.close();
#endif // WRITE_TO_FILE
#ifdef READ_TO_FILE
	std::ifstream fin("File.txt");
	if (fin.is_open())
	{
		const int SIZE = 256;
		char buffer[SIZE]{};

		while (!fin.eof())
		{
			//fin >> buffer;
			fin.getline(buffer, SIZE);
			cout << buffer << endl;
		}
		fin.close();
	}
	else
		std::cerr << "Error: File not Found";
#endif // READ_TO_FILE

}
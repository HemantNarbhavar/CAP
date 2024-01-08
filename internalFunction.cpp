#include<cstdlib>
#include<exception>
#include<fstream>
#include<ostream>
#include "internalMethod3.cpp"

subStatus checkSolution(string file)
{
	enum subStatus stat;

try{
	ofstream MyFile("newFile.cpp");
	MyFile << file;
	MyFile.close();
	system("g++ newFile.cpp");
	system("./a.out");
	cout << ifstream("test.txt").rdbuf();
	system("rm test.txt");
	stat = CORRECT;
}
catch(exception& e)
{
	cout << e.what() << endl;
	return stat = INCORRECT;
}
	return stat;
}


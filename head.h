#include <ios>
#include <fstream>
#include <iostream>

class DiskOperate{
	public:
	DiskOperate(){};
	int setDbFile();
	int changeDbFile();
};
class Interface{
	public:
	Interface(){};
	int options();
};
class Authenticate{
	public:
	Authenticate(){};
	int verify();
	int changePass();
};
using namespace std;

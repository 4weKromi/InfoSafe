#include <ios>
#include <fstream>
#include <iostream>

class Interface{
	public:
	Interface(){};
	int options();
};
class ChooseSet{
	char passValue[64];
	char dbName[64];
	char setValue[64];
	char setName[64];
	char shash[64];
	char filename[64];
	char ch;
	unsigned int cSetV=0;
	unsigned int cSetN=0;
	unsigned int i;
	public:
	ChooseSet(){};
	int setFile();
	int verify();
	int changePass();
};
using namespace std;

#include <ios>
#include <fstream>
#include <iostream>

class Interface{
	public:
	Interface(){};
	int options();
};
class ChooseSet{
	char setValue[64];
	char setName[64];
	char shash[64];
	char dbName[64];
	char ch;
	unsigned int flagPass,flagDb;
	unsigned int cSetV=0;
	unsigned int cSetN=0;
	unsigned int i;
	protected:
	char passValue[64];
	char filename[64];
	public:
	ChooseSet(){};
	int checkFile();
	int currentDb();
	int verify();
	int changePass();
	int changeDb();
};
class FileOperate: public ChooseSet{
	unsigned int lenW,lenD;
	char encryptWord[32];
	char encryptDesc[480];
	char ch;
	public:
	FileOperate(){};
	int createDb();
	int loadFile();
	int enText(char word[],char desc[]);
	int deText();
};
using namespace std;

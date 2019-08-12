#include <ios>
#include <fstream>
#include <iostream>
using namespace std;
class Interface{
	char choice;
protected:
	unsigned int flagWrite;
	char buffEntity[32],buffDesc[480];
public:
	Interface(){};
	int options();
};

class ChooseSet{
	char setValue[64],setName[64];
	char ch;
	unsigned int cSetV=0;
	unsigned int cSetN=0;
	unsigned int i;
protected:
	char shash[64],filename[64];
	unsigned int flagPass,flagDb;
	char dbName[64],passValue[64];
	char buffer[512],infoTemp[448];
	unsigned int stage,lenFi;
public:
	ChooseSet(){};
	int setEncrypt(char setEn[]);
	int setDecrypt(char setDe[]);
	int checkFile();
	int verify();
	int changePass();
	int changeDb();
	int createDb();
	int reset();
};

class FileOperate: public ChooseSet{
	unsigned int lenW,lenD;
	unsigned int dbSize=0;
	char bufferEntity[32],bufferDesc[480];
	char ch;
public:
	FileOperate(){};
	int currentDb();
	int fileSize();
	int loadFile(int arg);
	int writeFile();
	int enText(char entity[],char desc[]);
	int deText(char entity[],char desc[]);
};


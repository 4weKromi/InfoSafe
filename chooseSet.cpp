
#include "head.h"
#include "hash/md5.h"
#include <cstdio> //strcmp
#define SET "setApp.conf"
#include <windows.h>

void SetStdinEcho(bool enable = true)
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    if( !enable )
        mode &= ~ENABLE_ECHO_INPUT;
    else
        mode |= ENABLE_ECHO_INPUT;
    SetConsoleMode(hStdin, mode );
}

struct data{
char dbKey[64];
char exInfo[448];
}head;

ChooseSet::setEncrypt(char setEn[]){
	unsigned int i;
	lenFi=strlen(setEn);
	for(i=0;i<lenFi;i++){
		ch=setEn[i]+98;
		buffer[i]=ch;
	}
	buffer[i]='\0';
	return 0;
}
ChooseSet::setDecrypt(char setDe[]){
	unsigned int i;
	lenFi=strlen(setDe);
	for(i=0;i<lenFi;i++){
		ch=setDe[i]-98;
		buffer[i]=ch;
	}
	buffer[i]='\0';
	return 0;
}
ChooseSet::reset(){
	ofstream fileOut;
	fileOut.open(SET);
	fileOut<<"<key>"<<";\n";
	fileOut<<"<sel_file>"<<";\n";
	fileOut.close();
	return 0;
}
ChooseSet::checkFile(){
	ifstream fileIn,fileInD;
	ofstream fileOut;
	unsigned int count=0;
	flagPass=0;
	flagDb=0;
	fileIn.open(SET);
	if(fileIn){
		while(fileIn){
			fileIn.get(ch);
			if(ch=='<'){
				fileIn.get(ch); //skip '<'
				for(cSetN=0;ch!='>';cSetN++){
					setName[cSetN]=ch;
					fileIn.get(ch);
				}
				if(ch=='>'){
					fileIn.get(ch); //skip '>'
					for(cSetV=0;ch!=';';cSetV++){
						setValue[cSetV]=ch;
						fileIn.get(ch);
					}
				}
				count++;
				if (count==1&&cSetV>0){							
					for (i = 0; i < cSetV; i++) 
						passValue[i] = setValue[i];
					passValue[i]='\0';
					flagPass = 1; //pass assigned
				}else if(count==1&&cSetV<=0){
					flagPass = 0; //pass not set
				}
				if(count==2&&cSetV>0){
					for (i = 0; i < cSetV; i++)
						dbName[i] = setValue[i]; 
					dbName[i]='\0';
					flagDb = 1;	//db assigned
					setDecrypt(dbName);
					fileInD.open(buffer);
					if(fileInD)
						flagDb=2;//db file found
					else
						flagDb=3;//db not found
					fileInD.close();
				}else if(count==2&&cSetV<=0){
					flagDb = 0; //db not set
				}
			}
		}
		fileIn.close();
	}else{	/*Create a new config file, nothing assigned*/
		fileOut.open(SET);
		fileOut<<"<key>"<<";\n";
		fileOut<<"<sel_file>"<<";\n";
		fileOut.close();
		cout<<"\n Creating a new setApp.conf file ";
	}
	return 0;
}
	
ChooseSet::changePass(){
	ofstream fileOut;
	string str;
	checkFile();
	/*Remove current config file*/
	if (remove(SET)==0){
			fileOut.open(SET);
			cout<<" Enter new pass : ";
			cin>>shash;
			str=md5(shash);
			int n = str.length();
			/*To compare string with array */
			char arr[n+1];
			for (i = 0; i < sizeof(arr); i++) { 
				arr[i] = str[i]; 
			}
			setEncrypt(arr);
			fileOut<<"<key>"<<buffer<<";\n";
			cout<<"\n Pass Hash : "<<str<<endl;
	}else{
		cout<<" Failed to change pass";
	}
	/* if db not assigned, db is reset*/
	if(flagDb>=1){
		fileOut<<"<sel_file>"<<dbName<<";\n";
	}else{
		fileOut<<"<sel_file>"<<";\n";		
	}
	fileOut.close();
	return 0;
}

ChooseSet::verify(){
	char pcompare[64];
	ofstream fileOut;
	string str;
	checkFile();
	/*if pass assigned*/
	if(flagPass==1){
		while(true){
			cout<<"\n Enter pass : ";
			/* Remove echo */
			SetStdinEcho(false);
			cin>>pcompare;
			SetStdinEcho(true);
			str=md5(pcompare);
			int n = str.length();
			/*To compare string with array */
			char arr[n+1];
			for (i = 0; i < sizeof(arr); i++) { 
				arr[i] = str[i]; 
			}
			setEncrypt(arr);
			strcpy(arr,buffer);
			if(strcmp(passValue,arr)==0){
				cout<<"\n Okay !!";
				return 0;
			}else
				cout<<"\n Try Again ! ";
		}
	}else{	/*if pass not set, or removed manually*/
		if (remove(SET)==0){
			fileOut.open(SET);
			cout<<"\n Enter new pass : ";
			SetStdinEcho(false);
			cin>>shash;
			SetStdinEcho(true);
			str=md5(shash);
			int n = str.length();
			char tmp[n+1];
			for(i=0;i<sizeof(tmp);i++){
				tmp[i] = str[i];
			}
			setEncrypt(tmp);
			fileOut<<"<key>"<<buffer<<";\n";
			/*pass not found, DB is reset*/
			fileOut<<"<sel_file>"<<";\n";
			fileOut.close();
			cout<<" Pass Hash : "<<str<<endl;
		}else{
			cout<<" Failed to change pass";
		}	
	}
	return 0;
}

ChooseSet::changeDb(){
	ifstream fileIn;
	ofstream fileOut;
	string str;
	stage=0;
	cout<<"\n Enter new Database name (Syntax: filename.ext )[<64] : ";
	cin>>filename;
	fileIn.open(filename);
	if(fileIn){
		fileIn.seekg(0,fileIn.beg);
		fileIn.read((char *)&head,sizeof(head));
		setDecrypt(head.dbKey);/* Decrypt to buffer*/
		cout<<"\n Enter DB Key : ";
		SetStdinEcho(false);
		cin>>shash;
		SetStdinEcho(true);
		str=md5(shash);
		int n = str.length();
		char tmp[n+1];
		for(i=0;i<sizeof(tmp);i++){
			tmp[i] = str[i];
		}
		/* Decrypted buffer compares user input hash */
		cout<<"\n Key Hash : "<<buffer;
		if(strcmp(buffer,tmp)==0) 
			stage++;
		if(stage>=1){
			cout<<"\n Db Data Access Granted ";
			fileOut.open(SET);
			fileOut<<"<key>"<<passValue<<";\n";/* App Key*/
			setEncrypt(filename);
			fileOut<<"<sel_file>"<<buffer<<";\n";/* Selected DB*/
		}
		else{
			cout<<"\n Db Data Access Denied ";
			cout<<"\n Entered Hash : "<<tmp;
		}
	}
	else
		cout<<"\n "<<filename<<" does not exist";
	return 0;
}

ChooseSet::createDb(){
	checkFile();
	string str;
	ofstream fileOut;
	ifstream fileIn;
	cout<<"\n Enter new Database name (Syntax: filename.ext )[<64] : ";
	cin>>filename;
	fileIn.open(filename);
	if(fileIn){
		cout<<"\n Failed ! Database File Exist ";
		cout<<"\n Replace Existing File ? Y/N : ";
		cin>>ch;
		if(ch=='N'||ch=='n'){
			cout<<"\n Using Existing file ";
			changeDb();
			return 0;
		}
	}
	fileOut.open(filename);
	cout<<"\n New Database file created : "<<filename;
	cout<<"\n Enter "<<filename<<" info [<448] for readablity add '_' after each word\n : ";
	i=0;
	cin.ignore(1);
	while(cin.peek()!='\n'){
		cin>>infoTemp[i++];
	}
	/* cin.getline(infoTemp,480,'\n'); */
	cout<<"\n Enter new pass [<64]: ";
	SetStdinEcho(false);
	cin>>shash;
	SetStdinEcho(true);
	str=md5(shash);
	int n = str.length();
	char tmp[n+1];
	for(i=0;i<sizeof(tmp);i++){
		tmp[i] = str[i];
	}
	setEncrypt(tmp);
	strcpy(head.dbKey,buffer);
	setEncrypt((infoTemp));
	strcpy(head.exInfo,buffer);
	fileOut.write((char *)&head,sizeof(head));
	cout<<"\n Set Database Manually ";
	fileIn.close();
	fileOut.close();
	return 0;
}

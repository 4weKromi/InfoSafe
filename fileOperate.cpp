/* https://github.com/4weKromi */
#include "head.h"
#include <cstring> //strlen, strcpy
#include <limits> //numeric_limits<streamsize>::max

struct record{
	char entity[32],desc[480];
}data;

FileOperate::enText(char entity[],char desc[]){
	unsigned int i;
	lenW=strlen(entity);
	lenD=strlen(desc);
	for(i=0;i<lenW;i++){
		ch=entity[i]+98;
		bufferEntity[i]=ch;
	}
	bufferEntity[i]='\0';
	for(i=0;i<lenD;i++){
		ch=desc[i]+98;
		bufferDesc[i]=ch;
	}
	bufferDesc[i]='\0';
	return 0;
}

FileOperate::writeFile(){
	ofstream fileOut;
	checkFile();
	strcpy(data.entity,bufferEntity);
	strcpy(data.desc,bufferDesc);
	if(flagDb>=1){
		setDecrypt(dbName);
		fileOut.open(buffer, ios::app);
		fileOut.write((char *)&data,sizeof(data));
		cout<<"\n\n Saved !\n";
	}
	else
		cout<<"\n\n\t Db not set !\n Data Discarded ! \n";
	fileOut.close();
	return 0;
}

FileOperate::loadFile(int open){
	ifstream fileIn;
	checkFile();
	if(flagDb>=1){
		if(flagDb==2){
			setDecrypt(dbName);
			fileIn.open(buffer);
			if(open==0){	/* beg to end*/
				fileIn.seekg(1*sizeof(data)); /* skip header*/
				while(fileIn){
					fileIn.read((char *)&data,sizeof(data));
					if(fileIn.eof())
						break;
					deText(data.entity,data.desc);
					cout<<"\n Entity : "<<bufferEntity;
					cout<<"\n Description : "<<bufferDesc;
				}
				cout<<"\n\n ..done\n ";
				fileIn.close();
			}
			else if(open==1){	/* Selected index */
				unsigned int index=0;
				unsigned int records=fileSize();
				if(fileIn){
					while(true){
						cout<<"\n Enter Index number : ";
						cin>>index;
						if(cin.fail()){
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							cout<<"\n Enter valid integer value !";
						}
						if(index<records)
							break;
						else
							cout<<"\n Records 0 - "<<(records);
					}
					fileIn.seekg(index*sizeof(data));
					fileIn.read((char *)&data,sizeof(data));
					deText(data.entity,data.desc);
					cout<<"\n Entity : "<<bufferEntity;
					cout<<"\n Description : "<<bufferDesc;
				}
				cout<<"\n\n ..done\n ";
				fileIn.close();
			}
		}else
			cout<<"\n\n Db file not found !";
	}else
		cout<<"\n\n\tDb not set !\n";
	return 0;
}

FileOperate::deText(char entity[],char desc[]){
	unsigned int i;
	lenW=strlen(entity);
	lenD=strlen(desc);
	for(i=0;i<lenW;i++){
		ch=entity[i]-98;
		bufferEntity[i]=ch;
	}
	bufferEntity[i]='\0';
	for(i=0;i<lenD;i++){
		ch=desc[i]-98;
		bufferDesc[i]=ch;
	}
	bufferDesc[i]='\0';
	return 0;
}

FileOperate::fileSize(){
	unsigned int index=0;
	ifstream fileIn;
	checkFile();
	dbSize=0;
	if(flagDb>=1){
		if(flagDb==2){
			setDecrypt(dbName);
			fileIn.open(buffer);
			fileIn.seekg(0,fileIn.end);
			dbSize=fileIn.tellg();
			fileIn.close();
			fileIn.open(buffer);
			while(!fileIn.eof()){
				fileIn.seekg(index*sizeof(data));
				fileIn.read((char *)&data,sizeof(data));
				if(fileIn.eof())
					break;
				index++;
			}
			fileIn.close();
		}
	}
	return index;
}

FileOperate::currentDb(){
	struct dbheader{
		char notify[64];
		char dbKey[64];
		char exInfo[384];
	}head;
	ifstream fileIn;
	checkFile();
	if(flagDb>=1){
		setDecrypt(dbName);
		cout<<"\n Current DB : "<<buffer<<endl;
		if(flagDb==2){
			fileIn.open(buffer);
			fileIn.read((char *)&head,sizeof(head));
			setDecrypt(head.dbKey);
			cout<<"\n DB Hash : "<<buffer;
			setDecrypt(head.exInfo);
			cout<<"\n Info : "<<buffer;
		}
		if(flagDb==2){
			cout<<"\n DB Record : "<<fileSize()<<" Records";
			cout<<"\n DB Size : "<<dbSize<<" Bytes\n";
		}
		else
			cout<<"\n\n DB file not found !\n";
	}
	else
		cout<<"\n\n\t Db not set !\n";
	return 0;
}

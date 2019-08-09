#include "head.h"
#include <cstring>

FileOperate::createDb(){
	changeDb();
	ofstream fileOut;
	fileOut.open(filename);
	if(fileOut){
		cout<<"\n New Database file created : "<<filename;
	}else{
		cout<<"\n Failed to create database file ";
	}
	fileOut.close();
	return 0;
}

FileOperate::loadFile(){
	return 0;
}

FileOperate::enText(char word[],char desc[]){
	unsigned int i;
	lenW=strlen(word);
	lenD=strlen(desc);
	for(i=0;i<lenW;i++){
		ch=word[i]+98;
		encryptWord[i]=ch;
	}
	for(i=0;i<lenD;i++){
		ch=desc[i]+98;
		encryptDesc[i]=ch;
	}
	cout<<"\n ";
	for(i=0;i<lenW;i++){
		cout<<encryptWord[i];
	}
	cout<<"\n ";
	for(i=0;i<lenD;i++){
		cout<<encryptDesc[i];
	}
	return 0;
}

FileOperate::deText(){
	unsigned int i;
	cout<<"\n ";
	for(i=0;i<lenW;i++){
		ch=encryptWord[i]-98;
		cout<<ch;
	}
	cout<<"\n ";
	for(i=0;i<lenD;i++){
		ch=encryptDesc[i]-98;
		cout<<ch;
	}
	return 0;
}

#include "head.h"
#include "hash/md5.h"
#include <cstdio>

ChooseSet::checkFile(){
	ifstream fileIn;
	ofstream fileOut;
	unsigned int count=0;
	flagPass=0;
	flagDb=0;
	fileIn.open("setApp.conf");
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
				}else if(count==2&&cSetV<=0){
					flagDb = 0; //db not set
				}
			}
		}
		fileIn.close();
	}else{
		/*Create a new config file, nothing assigned*/
		fileOut.open("setApp.conf");
		fileOut<<"<key>"<<";\n";
		fileOut<<"<sel_file>"<<";\n";
		fileOut.close();
		cout<<" Creating a new setApp.conf file \n";
	}
	return 0;
}

ChooseSet::changeDb(){
	ifstream fileIn;
	ofstream fileOut;
	checkFile();
	/*create a new config file, if pass not assigned, pass is reset*/
	if(flagPass==1){	
		fileOut.open("setApp.conf");
		fileOut<<"<key>"<<passValue<<";\n";
	}else{
		fileOut.open("setApp.conf");
		fileOut<<"<key>"<<";\n";	
	}
	cout<<"\n Enter new Database name (Syntax: filename.ext) : ";
	cin>>filename;
	fileIn.open(filename); /*check db file*/
	if(fileIn){
		fileOut<<"<sel_file>"<<filename<<";\n"; /*db assigned to config file*/
		cout<<" Database set to "<<filename<<endl;
	}else{
		cout<<"\n Database file not found";
		fileOut<<"<sel_file>"<<";\n"; //DB is reset
	}
	fileOut.close();
	fileIn.close();
	return 0;
}
ChooseSet::currentDb(){
	checkFile();
	if(flagDb==1)
		cout<<"\n Current DB : "<<dbName<<endl;
	else
		cout<<"\n Db not set";
	return 0;
}
	
ChooseSet::changePass(){
	ofstream fileOut;
	checkFile();
	/*Remove current config file*/
	if (remove("setApp.conf")==0){
			fileOut.open("setApp.conf");
			cout<<" Enter new pass : ";
			cin>>shash;
			fileOut<<"<key>"<<md5(shash)<<";\n";
			cout<<" Pass Changed : "<<shash<<endl;
	}else{
		cout<<" Failed to change pass";
	}
	/* if db not assigned, db is reset*/
	if(flagDb==1){
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
	checkFile();
	/*if pass assigned*/
	if(flagPass==1){
		while(true){
			cout<<"\n Enter pass : ";
			cin>>pcompare;
			string str=md5(pcompare);
			int n = str.length(); 
			char arr[n+1];
			for (i = 0; i < sizeof(arr); i++) { 
				arr[i] = str[i]; 
			}
			if(strcmp(passValue,arr)==0){
				cout<<" Okay !!";
				return 0;
			}else
				cout<<" Try Again ! ";
		}
	}else{
		/*if pass not set, or removed manually*/
		if (remove("setApp.conf")==0){
			fileOut.open("setApp.conf");
			cout<<" Enter new pass : ";
			cin>>shash;
			fileOut<<"<key>"<<md5(shash)<<";\n";
			/*pass not found, DB is reset*/
			fileOut<<"<sel_file>"<<";\n";
			fileOut.close();
			cout<<" Pass Changed : "<<shash<<endl;
		}else{
			cout<<" Failed to change pass";
		}	
	}
	return 0;
}


	
	
	
	

#include "head.h"
#include "hash/md5.h"
#include <cstdio>

ChooseSet::setFile(){
	ifstream fileIn;
	ofstream fileOut;
	unsigned int count=0;
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
						}else if(count==1&&cSetV<=0){
							//if pass not found
						}
						if(count==2&&cSetV>0){
							for (i = 0; i < cSetV; i++)
								dbName[i] = setValue[i]; 
							dbName[i]='\0';
						}else if(count==2&&cSetV<=0){
							cout<<" DB not set "<<endl;
							fileOut.open("setApp.conf");
							fileOut<<"<key>"<<passValue<<";\n";
							cout<<"\n Enter new Database name (Syntax: filename.ext) : ";
							cin>>filename;
							fileOut<<"<sel_file>"<<filename<<";\n";
							fileOut.close();
							cout<<"Database Changed to "<<filename<<endl;
						}
					}
				}
			fileIn.close();
		}else{
			fileOut.open("setApp.conf");
			cout<<" Creating a new setApp.conf file \n";
			cout<<" Enter new pass : ";
			gets(shash);
			fileOut<<"<key>"<<md5(shash)<<";\n";
			cout<<" Enter new Database name (Syntax: filename.ext) : ";
			gets(filename);
			fileOut<<"<sel_file>"<<filename<<";\n";
			fileOut.close();
			cout<<" New Pass : "<<shash<<endl;
			cout<<" New DB Name : "<<filename<<endl;
		}
		return 0;
	}
	
ChooseSet::changePass(){
	ifstream fileIn;
	ofstream fileOut;
	unsigned int count=0;
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
					if(count==2&&cSetV>0){
						for (i = 0; i < cSetV; i++)
							dbName[i] = setValue[i]; 
						dbName[i]='\0';
					}
				}
			}
		fileIn.close();
	}
	if (remove("setApp.conf")==0){
		fileOut.open("setApp.conf");
		cout<<" Enter new pass : ";
		cin>>shash;
		fileOut<<"<key>"<<md5(shash)<<";\n";
		fileOut<<"<sel_file>"<<dbName<<";\n";
		fileOut.close();
		cout<<" Pass Changed : "<<shash<<endl;
	}else{
		cout<<" Failed to change pass";
	}
	return 0;
}

ChooseSet::verify(){
	char pcompare[64];
	unsigned int count=0;
	ifstream fileIn;
	ofstream fileOut;
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
						for (i = 0; i < cSetV; i++){
							passValue[i] = setValue[i];
						}
						passValue[i]='\0';
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
					}else if(count==1&&cSetV<=0){
						//if pass not found
						break;
					}
				}
			}
			fileIn.close();
			if(count==1&&cSetV<=0){
				if (remove("setApp.conf")==0){
				fileOut.open("setApp.conf");
				cout<<" Enter new pass : ";
				cin>>shash;
				fileOut<<"<key>"<<md5(shash)<<";\n";
				//if pass not found, DB is reset
				fileOut<<"<sel_file>"<<";\n";
				fileOut.close();
				cout<<" Pass Changed : "<<shash<<endl;
				}else{
					cout<<" Failed to change pass";
				}	
			}
		}else
			cout<<" Error :  setApp.conf not found \n";
	return 0;
}


	
	
	
	
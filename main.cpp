#include <filesystem>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <ctime>
#include <cstdio>

using namespace std;
using namespace std::filesystem;

void reach_directory(vector<string>directory_path);
vector<string> manipulate_path_string(string p_string);
bool go_back();
void print_options();
void choiceD();
void choiceF();
void choiceN();
void choiceC();
void choiceM();

string cache;

int main(){
	
	cout << current_path() << "\n";
	while(go_back());
	
	char user_choice = '\0';
	
	do{
		print_options();
		cout << "\n> ";
		cin >> user_choice;
		user_choice = toupper(user_choice);
		switch(user_choice){
			case 'D':
				choiceD();
				break;
			case 'F':
				choiceF();
				break;
			case 'N':
				choiceN();
				break;
			case 'C':
				choiceC();
				break;
			case 'M':
				choiceM();
				break;
			default:
				break;
		}
		
	}while(user_choice != 'Q');
	
	
	return 0;
}

void reach_directory(vector<string>directory_path){
	string full_path = "/";
	for(auto each_path: directory_path){
		full_path += each_path + "/";
		if(!exists(each_path)){
			char user_input = '\0';
			cout << "\nDirectory (" << each_path << ") not found at (" << current_path() << ").\n";
			cout << "Create new directory? (Y)es    (N)o.\n";
			cout << ">";
			cin >> user_input;
			user_input = toupper(user_input);
			if(user_input == 'Y'){
				create_directory(each_path);
				cout << "Directory Created: '" << full_path << "'.\n";
			}else{
				return;
			}
		}
		current_path(each_path);
	}
}

vector<string> manipulate_path_string(string p_string){
	string directory_name = "";
	vector<string>vec;
	for(auto c: p_string){
		if(c != 92){
			if(c == '/'){
				if(!directory_name.empty()){ vec.push_back(directory_name); }
				directory_name = "";
			}else{
				directory_name += c;
			}
		}
	}
	vec.push_back(directory_name);
	return vec;
}

bool go_back(){
	if(current_path() != path("/")){
		current_path("..");
		return true;
	}else{
		cout << "\nDirectory reset to base.\n\n";
		return false;
	}
}

void print_options(){
	system("clear");
	cout << "===============================================================================\n";
	cout << "                                 F!LE  MANAG3R                                 \n";
	cout << "===============================================================================\n\n";
	cout << "Current Path: -> " << current_path() << "\n\n";
	system("ls");
	cout << "\n\n";
	cout << "(D)   Change Directory.\n";
	cout << "(N)   Create New File.\n";
	cout << "(F)   Create New Folder.\n";
	cout << "(C)   Copy File.\n";
	cout << "(M)   Move File.\n";
}

void choiceD(){
	char option = '\0';
	cout << "\n           ---------------   Change  Directory   ---------------\n\n";
	do{
		cout << "Current Directory -> " << current_path() << "\n\n";
		cout << "1- Enter Directory.\n";
		cout << "2- Go to Parent Directory.\n";
		cout << "3- Reset to Base Directory.\n";
		cout << "4- Back.\n";
		cout << "\n> ";
		cin >> option;
		getline(cin, cache);
		if(option == '1'){
			cout << "\nchanging directory...\n";
			string input_dir_path;
			cout << "\nEnter Destination: ";
			getline(cin,input_dir_path);
			vector<string>vec = manipulate_path_string(input_dir_path);
			reach_directory(vec);
			return;
		}else if(option == '2'){
			go_back();
		}else if(option == '3'){
			while(go_back());
		}else if(option == '4'){
			return;
		}
	}while(option == '2');
}

void choiceF(){
	cout << "\n           ---------------   Create New Folder   ---------------\n\n";
	cout << "\ncreating new folder...\n";
	string folder_name;
	path destination;
	getline(cin, cache);
	do{
		cout << "\nEnter new folder name: ";
		getline(cin,folder_name);
		cout << "\n";
		destination = current_path() / folder_name;
		if(folder_name != "*quit"){
			if(exists(destination)){
				cout << "Folder with name (" << folder_name << ") already exists.\n";
			}else{
				create_directory(folder_name);
				current_path(folder_name);
				cout << "Directory Created: '" << current_path() << "'.\n";
				return;
			}
		}
	}while(exists(destination) && folder_name != "*quit");
}

void choiceN(){
	cout << "\n           ---------------   Create New File   ---------------\n\n";
	cout << "\ncreating new file...\n";
	string file_name;
	path destination;
	getline(cin, cache);
	do{
		cout << "\nEnter new file name: ";
		getline(cin,file_name);
		cout << "\n";
		destination = current_path() / file_name;
		if(file_name != "*quit"){
			if(exists(destination)){
				cout << "File with name (" << file_name << ") already exists.\n";
			}else{
				path file_path = current_path() / file_name;
				ofstream file(file_path);
				if(file.is_open()){
					file.close();
					cout << "File Created: '" << file_name << " - " << current_path() << "'.\n";
					return;
				}else{
					cout << "Failed Creating File: " << file_path << "\n";
				}
			}
		}
	}while(exists(destination) && file_name != "*quit");
}

void choiceC(){
	
	cout << "\n           ---------------   Copying  File   ---------------\n\n";
	cout << "\ncopying file...\n\n";
	system("ls");
	getline(cin, cache);
	cout << "\n";
	bool f = 0;
	string file_name;
	string file_path;
	string to_path = "";
	
	do{
		if(to_path != "" && f == 0){
			system("clear");
			cout << "\ncopying files in progress...\n\n";
			cout << "~ from: " << current_path() << "\n";
			cout << "~ to: " << to_path << "\n\n";
			system("ls");
			cout << "\n";
		}
		
		if(f == 1){
			cout << "\nfile copied successfully.\n\n";
		}
		
		cout << "\nEnter file name to copy: ";
		getline(cin, file_name);
		
		file_path = current_path().string() + "/" + file_name;
		
		if(!exists(path(file_path))){
			cout << "\n\ncan't find file in this directory.\n";
			f = 0;
		}else{
			if(to_path == ""){
				do{
					cout << "\nEnter destination to copy to: ";
					getline(cin, to_path);
					if(!exists(path(to_path))){
						cout << "\n\npath not found!.\n";
						f = 0;
					}
				}while(!exists(path(to_path)) && to_path != "*quit");
				if(to_path == "*quit"){
					return;
				}
			}
			string source_string = current_path().string() + "/" + file_name;
			string destination_string = to_path;
			string copy_name;
			string extension;
			string copy_path = destination_string + "/" + copy_name;
			int ext_pos;
			for(int i=file_name.size()-1;  i>=0; i--){
				ext_pos = i;
			}
			if(ext_pos != file_name.size()){
				for(int i=0; i<ext_pos; i++){
					copy_name += file_name[i];
				}
				for(int i=ext_pos; i<file_name.size(); i++){
					extension += file_name[i];
				}
			}else{
				copy_name = file_name;
			}
			int i = 0;
			copy_path = destination_string + "/" + copy_name + extension;
			while(exists(path(copy_path))){
				if(i == 0){
					copy_name += '1';
					ext_pos++;
				}else if(i % 9 == 0){
					copy_name[copy_name.size()-1] = '1';
					copy_name += '1';
					ext_pos++;
				}else{
					copy_name[copy_name.size()-1]++;
				}
				i++;
				copy_path = destination_string + "/" + copy_name + extension;
			}
			ifstream from (source_string, ios::binary);
			ofstream to (copy_path, ios::binary);
			
			to << from.rdbuf();
			
			from.close();
			to.close();
			f = 1;
		}
	}while(file_name != "*quit");
}

void choiceM(){
	cout << "\n           ---------------   Moving  File   ---------------\n\n";
	cout << "\nmoving file...\n\n";
	system("ls");
	getline(cin, cache);
	cout << "\n";
	bool f = 0;
	string file_name;
	string file_path;
	string to_path = "";
	
	do{
		if(to_path != "" && f == 0){
			system("clear");
			cout << "\nmoving files in progress...\n\n";
			cout << "~ from: " << current_path() << "\n";
			cout << "~ to: " << to_path << "\n\n";
			system("ls");
			cout << "\n";
			f = 1;
		}
		
		if(f == 1){
			cout << "\nfile moved successfully.\n\n";
		}
		
		cout << "\nEnter file name to move: ";
		getline(cin, file_name);
		
		file_path = current_path().string() + "/" + file_name;
		
		if(!exists(path(file_path))){
			cout << "\n\ncan't find file in this directory.\n";
		}else{
			if(to_path == ""){
				do{
					cout << "\nEnter destination to move to: ";
					getline(cin, to_path);
					if(!exists(path(to_path))){
						cout << "\n\npath not found!.\n";
					}
				}while(!exists(path(to_path)) && to_path != "*quit");
				if(to_path == "*quit"){
					return;
				}
			}
			string source_string = current_path().string() + "/" + file_name;
			string destination_string = to_path;
			string copy_name;
			string extension;
			string copy_path = destination_string + "/" + copy_name;
			int ext_pos;
			for(int i=file_name.size()-1; file_name[i+1] != '.' && i>=0; i--){
				ext_pos = i;
			}
			for(int i=0; i<ext_pos; i++){
				copy_name += file_name[i];
			}
			for(int i=ext_pos; i<file_name.size(); i++){
				extension += file_name[i];
			}
			int i = 0;
			copy_path = destination_string + "/" + copy_name + extension;
			while(exists(path(copy_path))){
				if(i == 0){
					copy_name += '1';
					ext_pos++;
				}else if(i % 9 == 0){
					copy_name[copy_name.size()-1] = '1';
					copy_name += '1';
					ext_pos++;
				}else{
					copy_name[copy_name.size()-1]++;
				}
				i++;
				copy_path = destination_string + "/" + copy_name + extension;
			}
			ifstream from (source_string, ios::binary);
			ofstream to (copy_path, ios::binary);
			
			to << from.rdbuf();
			
			from.close();
			to.close();
			int status = remove(source_string);
			if(!status){
				cout << "\n\nerror removing file.\n\n";
			}
		}
	}while(file_name != "*quit");
}

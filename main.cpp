#include <filesystem>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <unistd.h>

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
	
	
}

void choiceM(){
	
	
}

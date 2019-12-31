/*Future - Collect Timetables of all branches, ask in start & change name of recallfile accordingly*/
/*Future- Add special_notes for particular 'dates'*/
//SUGGESTION - Set 'day' in daylist, using today's day, from the parent, ie. timetable, since, that will require only 1 refresh of time, and will set the day for all 5 daylists [or ndays]
//The below FUTURE suggestions are from the inside of the Experimental.cpp file
//Better give list of available timetables
				/*
				FUTURE -> system("ls ./timetables");
						  system("dir ./timetables");
				*/
/*
	I left original FUTURE comment of this in timetable::fill() there only, since that makes more sense there... see them
FUTURE - "Any Special notes for this day (1 or 0)? ";*/
		/*For the above, add 'string spec_notes' in daylist*/


/*
	CAUTION - IF YOU CHANGE 'ORDER' of elements, in timetable, or daylist, do so in the save functions and save functions also... so as to make sense
*/

/*Program - TimeTable Manager
 *Programmer - Aditya Gupta (aka. Techy15)
 *Language - C++
 *Purpose - Actually a part of Attendance_Register Program*/

//Actual parent of this MERGED file, is Experimental.cpp, which is the actually working, and 'done' TimeTable_Manager file, and not the others with the TimeTable_Manager Name, they got the name, bcz they were my first implementations, but I started out BY CHANGING SOME OF THE MAIN INTITAL IDEAS, and created this 'Experimental.cpp' which is now actually not Experimental, but is the actual 'TimeTable_Manager' :D :D !!!!
//It is the one that gave me hope that i will implement it further, and i set out to complete it... Will do best and complete it in time
//BTW, the main() is from main_frontend.cpp

#include <iostream>
/*The header file std::iostream contains these...
#include <bits/c++config.h>	//Not in fstream, but included in string... SO ALL std::iosTREAM IS DEFINED BY FSTREAM
#include <ostream>
#include <istream>
*/
#include <fstream>
/* 	The header file fstream contains these lines...
#include <istream>
#include <ostream>
#include <bits/codecvt.h>
#include <cstdio>             // For BUFSIZ
#include <bits/basic_file.h>  // For __basic_file, __c_lock
#if __cplusplus >= 201103L
#include <string>             // For string overloads.
*/
#include <string>
#include <ctime>
#include <cstdlib>		//For using system("clear") only once
#include <limits>	//for std::numeric_limits
//#include <ios>	//for <std::streamsize>, both these used in std::cin.ignore()

#ifdef _WIN32	//Macro defined by MSVC (Microsoft Visual C++) compiler (not g++)
	#include <windows.h>
#elif __linux__
	#include <sys/ioctl.h>
	#include <unistd.h>		//Since it defines 'STDOUT_FILENO', which is used for getting Dimensions in Linux
							//Also used to scroll "Records Updated" on linux
#elif __MINGW32__	//MinGW (g++)
	#include <windows.h>
#elif __CYGWIN__	//CygWin (g++)
	#include <windows.h>
#endif

using namespace std;

tm time_now;
string big[26][8]={{"---------","|  ---  |","|  | |  |","|  ---  |","|  | |  |","|  | |  |","|  | |  |","---- ----"},{"--------\\","|  ---  |","|  | |  |","|  ---  /","|  ---  \\","|  | |  |","|  ---  |","--------/"},{"--------\\","|       |","|  -----/","|  |     ","|  |     ","|  -----\\","|       |","--------/"},{"--------\\","|  ---\\ |","|  |  | |","|  |  | |","|  |  | |","|  |  | |","|  ---/ |","--------/"},{"---------","|       |","|  ------","|  --\\   ","|  --/   ","|  ------","|       |","---------"},{"---------","|       |","|  ------","|  |     ","|  ====  ","|  |     ","|  |     ","----     "},{"--------\\","|       |","|  -----/","|  |     ","|  \\=====","|    |  |","|    |  |","-----/  |"},{"---   ---","| |   | |","| |   | |","| ----- |","| ----- |","| |   | |","| |   | |","---   ---"},{"---------","|--- ---|","   | |   ","   | |   ","   | |   ","   | |   ","|--- ---|","---------"},{"---------","|--- ---|","   | |   ","   | |   ","   | |   ","   | |   ","/--- -   ","|----/   "},{"---   ---","| |  / / ","| | / /  ","| /  /   ","| \\  \\   ","| | \\ \\  ","| |  \\ \\ ","---   ---"},{"---      ","| |      ","| |      ","| |      ","| |      ","| |      ","|--- ---|","\\-------|"},{"---   ---","|  \\ /  |","|       |","|  \\ /  |","|  | |  |","|  | |  |","|  | |  |","---- ----"},{"---   ---","|\\\\   | |","| \\\\  | |","| |\\\\ | |","| | \\\\| |","| |  \\\\ |","| |   \\\\|","---   ---"},{"---------","| ----- |","| |   | |","| |   | |","| |   | |","| |   | |","| ----- |","---------"},{"---------","| ----- |","| |   | |","| -----/ ","| |      ","| |      ","| |      ","---      "},{"---------","| ----- |","| |   | |","| |   | |","| |   | |","| =======","| ======|","---------"},{"---------","| ----- |","| |   | |","| ----- /","| |\\  \\  ","| | \\  \\ ","| |  \\  \\","---   ---"},{"---------","| |      ","| |      "," \\ --- \\ ","      | |","      | |","|--- ---|","\\-------|"},{"---------","---| |---","   | |   ","   | |   ","   | |   ","   | |   ","   | |   ","   ---   "},{"---   ---","| |   | |","| |   | |","| |   | |","| |   | |","| |   | |","\\ ----- /"," ------- "},{"---   ---","| |   | |","| |   | |","| |   | |","| |   | |","\\ \\   / /"," \\  -  / ","  -----  "},{"--     --","||     ||","||     ||","||     ||","||     ||","\\\\  |  //"," \\\\/ \\// ","  -   -  "},{"--     --"," \\\\   // ","  \\\\ //  ","   \\ /   ","   / \\   ","  // \\\\  "," //   \\\\ ","--     --"},{"---   ---","\\ \\   / /"," \\ \\ / / ","  \\   /  ","   | |   ","   | |   ","   | |   ","   ---   "},{"---------","-------/ ","     //  ","    //   ","   //    ","  //     "," /-------","---------"}};
string small[26][4]={{"----","|  |","|--|","|  |"},{"----","|__|","|  |","----"},{"----","|   ","|   ","----"},{"---\\","|  |","|  |","---/"},{"----","|__ ","|   ","----"},{"----","|__ ","|   ","|   "},{"----","|   ","| -|","---|"},{"|  |","|__|","|  |","|  |"},{"----"," || "," || ","----"},{" ---","   |","   |","---/"},{"|  /","|/  ","|\\  ","|  \\"},{"|   ","|   ","|   ","----"},{"|  |","|\\/|","|  |","|  |"},{"|  |","|\\ |","| \\|","|  \\"},{"/--\\","|  |","|  |","\\--/"},{"/--\\","|__|","|   ","|   "},{"|--|","|  |","| \\|","|--\\"},{"/--\\","|__|","|\\  ","| \\ "},{"/--\\","|__","   |","\\--/"},{"----"," || "," || "," || "},{"|  |","|  |","|  |","|__|"},{"|  |","|  |","\\  /"," \\/ "},{"\\  /"," \\/ "," /\\ ","/  \\"},{"\\  /"," \\/ "," /\\ ","/  \\"},{"\\  /"," \\/ "," /  ","/   "},{"/---","  / "," /  ","---/"}};
string name = "Aditya Gupta";	//Will be taken from the records class
int terminal_width = 169, terminal_height = 39;		// [DONE] FUTURE - Set this using some function

typedef unsigned int positive;

/*NOTE - Change std::cin in settings() to respective getline() so that it may take spaces also*/

/*Note - This might be bad at error handling... since i dont check in every function, whether data is valid or not
		 But, I made sure that the data which are modifying the data, don't allow any invalid data to be fed in
		 This was just to make program a bit faster (...maybe)... but i may later update it to have those checks
*/

/*[5/12/2019 16:57] A drastic shift - In original idea, we actually demanded user to enter start and end time, for all intervals, 
					But I replaced it by having the program ask only for coursecode, and leave the time interval if empty
					This may increase convinience on user side, but DECREASES THE ABILITY TO HAVE CUSTOM TIME RANGES
					Change - Removed fillbox() from timeboxn class, and implemented the above said in parent daylist class*/

/*Improvements IMPLEMENTED [Some of them may have been lost, ya maine sirf mann me sochha tha, and didn't write it here, and such improvements might have been implemented in a day or so]*/
//[DONE]FUTURE - Range changes according to the Height of Terminal Window

//main_frontend.cpp function declarations START
void prt_t_header(void);
void greeting(string);		//CAUTION - Don't take address, since it will be modified later in magnify()
void refresh_time(void);	//refreshes global variable time

void magnify(string,string*,string*);	// int is for spaces to print before that
void capitallize(string*);
void clearscr(void);
void set_h_w(void);    //Set terminal height & width
//main_frontend.cpp function declarations END

//Added on 26th December 2019
void magnify(string, string*);
void smaller_magnify(string, string*);
int numspaces(string);
void vibrate(string);	//vibrates the given string at middle, with amplitude = 1.5 * length of string

//ONLY for timetable::set_total_courses()
struct strnode{
		string s;
		strnode* next= NULL ;
};

class string_list{
public:
	strnode *front, *rear;	//For now, LET THEM PUBLIC... required in listbox::initiate()
	bool is_in_list(string);	//true IF found
	void add_in_list(string);
	void destruct_list();
	string_list(){
		front = NULL;
		rear = NULL;
	}
	~string_list(){
		destruct_list();
	}
};
//string Class Functions START
bool string_list::is_in_list(string s){
	strnode* tmp = front;
	while(tmp->next){
		if(tmp->s == s){
			destruct_list();
			return true;
		}
	}
	destruct_list();
	return false;
}

void string_list::add_in_list(string str){
	strnode *newnode = new strnode;
	newnode->s = str;
	if(front == NULL){
		front = newnode;
		rear= newnode;	//newnode->next is already NULL
	}
	else {
		newnode->next = front;
		front = newnode;
	}
}

void string_list::destruct_list(){
	strnode *temp = front;
	while(front){
		temp=front;
		front = temp->next;
		delete temp;
	}
}
//string Class Functions END

class timeboxn{
	string coursecode;
//	irecbox *recbox;
	public:
		string sub;	//parent fills the times, and sub
        float starttime,endtime;  //store 9:30 as 9.5 & 1:30 pm as 13.5... ie. in 24-HOUR FORMAT
					//Auto assume am for any time (6,12), and for all others 'pm'
    	timeboxn *next,*prev;
		
    	timeboxn();
//        void fillbox();	//have this fillbox in its parent, and there dont ask user to enter time also, just keep taking input for different intervals, let user leave it blank, if empty period
        string* get_coursecode();
        void change_coursecode(string*);
//Added on 25 December 2019
        void change_coursecode(char*);	//Used ONLY in daylist::load_from_binary()...
        								//CAN BE REMOVED ONCE daylist::append_box() is utilized
};

class daylist{

			/*PROPOSED CHANGES - Utilize append_box() in load_from_binary... first check if it is LAB course or not, then call append_box()
			*/
	string day;	//let the parent fill this, and in capitals
	timeboxn *front,*rear;
	public:
	    timeboxn *tpoints[8]={ NULL };	//WARNING - If wanting to dynamically allocate, change timetable::set_total_courses().. No need to dynamically allocate though
		int numbox;

		void set_tpoints();
		void make_tlist();
		void append_box(string*,int);	//By Default, appends to end
		timeboxn* traverseto(int);	//Will traverse like array (ie. 0 means 1st box)
//Added on 25 DECEMBER 2019, after >7 days try
		void load_from_binary(std::ifstream*); //also calls set_tpoints() at end
		void save_to_binary(std::ofstream*);
		void set_Day(string);	//25 Aug 2019 - Made 'day' private
//Suggested on 26 DECEMBER 2019
//		bool isLabCourse(string);
		void update_box(int);	//Takes the number of box... then utilize tpoints[8]
		daylist();
		~daylist();                   
};

class timetable{
	bool state;		//'state' data member tells if it has been entered or not
	string savefile,txtfile,recallfile;	//Change these to department name + gp name, after user changes dept or grp
	string dept,grp;
	daylist *day;
	public:		/*Future - Add functionality for 'n' temp-timetables (each for 1 day)... These will store Day,Date,Sub,time */
		int ndays;	//For the basic part, don't change 'ndays'
					//Made it public, so that a_register::update_num_courses() can access it
		int total_courses;	/*DONT RECOVER FROM CONFIG... let the functions auto-set this*/
		daylist* ret_day(int);		//int from 0 to 6 (or ndays)
		string** contoarray(void);	//Deprecated... using tpointers to get values
//Added29th December, but all my work of 29th December was gone! So rewrote on 30th
		string_list distinct_courses;	//Use set_total_courses()
//[Replaced]        void save(void);
		void savetxt(void);
		void display(void);	//can utilize the display(int) function
//[Replaced]		void loadfrom_file(void);
		void fill(void);
		void settings(void);
//27 December 2019... made mainmenu() take a parameter mainmenu_retval, which when 0, signals all previous mainmenu() to exit
        int mainmenu(bool = true);
        void set_total_courses(void);	//traverses 'whole' timetable
        			//30December2019 -> also sets the distinct_courses
//Added on 25 December 2019, after >7 days of trying (ie. debugging the code, since it was giving SEG_FAULT everytime, finally resolved using 'gdb')
 		void save_to_binary();
		void load_from_binary();	//Since, we can't use data member, for default arguments, since they aren't declared at the instant, nor does 'this' work here
        void display_day(int);	//Suggested on 25Aug2019
//Suggested on 26 DECEMBER 2019
        /*[INITIAL SETUP]Have option and elements to take in time of start of the day, and if same for all days left, press y... and in time of end of the day, and if same for all days left to enter
        And also the time of recess, and if same for all*/
        timetable();
		~timetable();
};

//RECORDS.CPP classes START
class irecbox
{
//	bool today;	//Stores whether it is today or not
//	int order;	//FUTURE... Curently using just the indices of the 'irecbox **todayarray'
	string coursecode;
//Added on 28th December 2019
//	timeboxn *course;	//Pointer to the course box
public:
	int npresent, nabsent, nbunk;/*, n_not_entered;	//Practically not that important*/
	irecbox* next,*prev;
	string get_coursecode() const;
	void change_coursecode(string);
	irecbox(){
//		order = 0;
		coursecode = "";
		npresent = nabsent = nbunk =0;
	}
/*~irecbox();
*/	
};

string irecbox::get_coursecode() const{
	return coursecode;
}

void irecbox::change_coursecode(string s){
	coursecode = s;
}


class a_register
{
	bool setup_complete;
public:
	timetable table;	//links with table selected during initial setup
	//Read from the config file, and the table file (that too read from config file), and then load the table with that file name, then link with this
	int today_num_courses;
	void update_num_courses();	//Both today and total
//	void get_initstatus();	//sets setup_complete
	void RECOVERconfig();	//IT MAY BE MADE A GLOBAL FUNCTION
						//recovers from Attendance_Register.conf file...
						//	It will store : setup_complete, table_name, timetable::total_courses (not of today; that will be set by function),
						//					listbox data (of irecboxes)

//	void settings();	//FUTURE
	a_register();
/*	~a_register();
*/};

void a_register::RECOVERconfig(){
	//TRIAL
	setup_complete = true;
}

class listbox : public a_register 	//Made public, only to access table with dot_operator, from main() 'through' listbox object
{
	irecbox* front,*rear;	//A LIST
		//Put this array of pointers in this class, since it needs to access the listbox class list, but it can't from within a_register
    irecbox **todaylist;	//Make 'array of pointers' using a_register::(*table).total_courses
	int numbox;	//lenght of list
public:
	void totaldisplay();
	void idisplay(string*);	//Displays records for a particular records only
	//FUTURE - Display when the particular coursecode takes place also... preferably, link it with it's lab course also
	void parseinput(string);	//Updates the records with the given input
								//trear as yynny, or YNN, or YnnNy, or Y10nn1... ie. check each digit individualy == 'y' || 'Y' || '1'
	void initiate();	//parent calls it, after initiating timetable
	void set_today_array();	//this can't be used to set today_courses, since it needs it beforehand
	irecbox* find_irecbox(string*);
	listbox();
	~listbox();
};

int main(int argc, char const *argv[]){

	std::ios_base::sync_with_stdio(false);	//disables sync between C and C++ standard streams

	int i;
	string icommand;
	#ifdef __linux__
		system("clear");
	#else
		system("cls");
	#endif

	set_h_w();
	
//	a_register register_object;
	listbox all_records;
	all_records.table.mainmenu();
	//register_object.check_initstatus();	//Checks whether initial setup complete or not

	prt_t_header();
	greeting(name);
	if(terminal_width<115){
		std::cout<<'\n';
	}
	else std::cout<<"\n\n";
	for(i=0;i<(terminal_width/2 - 3); i++) std::cout<<' ';
	getline( std::cin, icommand );
	if(icommand[0] == ':' ){
		if ( icommand == ":exit" )
			return 0;
		//have conditions to check for commands
		/*
			Available Commands-
				:exit or :q or :quit
				:settings
				:tt     //display current tt
				:ttadv	//tt manager
				:records //overall
				:irecords //list coursecodes... select among them for individual records
				:irecord:CS1401 //Case-INsensitive //Directly displays individual records of CS1401
				:l or :list //lists all courses today
		*/
	}
	else {
		try{
			//all_records.parseinput(&icommand);
		}
		catch(char *s){
			std::cout<<s;
		}
	/*ONLY AFTER SUCCESS of ParseInput()*/
		//vibrate("Records Updated!");
		system("clear");
		prt_t_header();
		greeting(name);
		if(terminal_width<115){
			std::cout<<'\n';
		}
		else std::cout<<"\n\n";
		vibrate("Records Updated!");
	}
}

//main_frontend.cpp funtions START
void prt_t_header(void){	//FUTURE - Modify to get width of terminal, to print sufficient spaces
	int monlength=0, i=0, day_len=1;
	refresh_time();
	set_h_w();
	std::cout<<"\n    "<<time_now.tm_mday<<' ';
	if(time_now.tm_mday>9) day_len=2;
	switch(time_now.tm_mon){
		case 0: std::cout<<"January "; monlength=8;  break;
		case 1: std::cout<<"February "; monlength=8; break;
		case 2: std::cout<<"March "; monlength=5; break;
		case 3: std::cout<<"April "; monlength=5; break;
		case 4: std::cout<<"May "; monlength=3; break;
		case 5: std::cout<<"June "; monlength=4; break;
		case 6: std::cout<<"July "; monlength=4; break;
		case 7: std::cout<<"August "; monlength=6; break;
		case 8: std::cout<<"September "; monlength=9; break;
		case 9: std::cout<<"October "; monlength=7; break;
		case 10: std::cout<<"November "; monlength=8; break;
		case 11: std::cout<<"December "; monlength=8; break;
	}
	std::cout<<1900 + time_now.tm_year;
	int space = terminal_width - day_len - monlength - 42; //19 for 'Attendance Register'
	for(i=0; i<space/2; i++ ) std::cout<<' ';
	std::cout<<"Attendance Register";
	for(i=0; i<space - space/2; i++ ) std::cout<<' ';
	if(time_now.tm_hour > 9)
		std::cout<<time_now.tm_hour;
	else 
		std::cout<<'0'<<time_now.tm_hour;
	std::cout<<':';
	if(time_now.tm_min > 9)
		std::cout<<time_now.tm_min<<std::endl;
	else 
		std::cout<<'0'<<time_now.tm_min<<std::endl;
	for(i=0; i<terminal_width; i++) std::cout<<'-';
	std::cout<<std::endl;
}

void greeting(string name){	//IMPROVE - Give it in Hindi words... eg. Shubh Ratri, ya jo bhi us samay kaha jata ho 
	int i;
	for(i =0;name[i]!=' ' && i<name.size();i++);	//Extracting first_name from name
	name.resize(i);

	string msg = "Good ";
	refresh_time();
	if( time_now.tm_hour < 12 )
		msg.append("Morning");
	else if( time_now.tm_hour < 17 )
		msg.append("Afternoon");
	else if( time_now.tm_hour < 22 )
		msg.append("Evening");
	else msg.append("Night");

	if( terminal_width >( 5*msg.size() - 1*1 + 10*name.size() + 2 ))
    	for(i=0;i<(terminal_height/2 - 9);i++) std::cout<<'\n';	//-9 = -1 for height of header (time), and -8 for greeting
  	else
  		for(i=0;i<(terminal_height/2 - 5);i++) std::cout<<'\n';	//-9 = -1 for height of header (time), and -8 for greeting

	magnify("mid",&msg,&name);	//+6 for 1 space... since, space took 4columns, while if it had been a character, it would have taken 10
}

void refresh_time(){
	time_t t=time(0);
	time_now = *localtime(&t);
}

void set_h_w(){ //USE MORE ADVANCED
    #ifdef __linux__
        winsize w;  //struct winsize
        ioctl (STDOUT_FILENO, TIOCGWINSZ, &w);
        terminal_height = w.ws_row;
        terminal_width = w.ws_col;
    #else
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &csbi );
        terminal_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        terminal_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    #endif
//    terminal_width = 169;       //80 in small window
//    terminal_height = 39;       //24 in small window
}

void capitallize(string *s){
    for(int i=0; i<(s->size()) ; i++)
        (*s)[i] =  toupper((*s)[i]);
}

void magnify(string pos, string *small_str, string *big_str){	//FUTURE - pos maybe "start","mid","end"
	capitallize(small_str);
	capitallize(big_str);
	int spac, msglen = 5*(small_str->size()) - 1*1 + 2;	//no_of_spaces is 1, 2 for space b/w small and big 
    int i,j,k;
//    if( pos == "mid")	//FUTURE
    if( terminal_width >( msglen + 10*(big_str->size()) )){
    	spac=(terminal_width - msglen - 10*(big_str->size()))/2;
    	for(i=0;i<4;i++){
        	for(j=0;j<spac+msglen-1;j++) std::cout<<" ";
        	for(k=0;k<big_str->size();k++){
            	if((*big_str)[k]==' ') std::cout<<"   ";
            	else std::cout<<big[(int)((*big_str)[k])-65][i];
            	std::cout<<" ";
        	}
        	std::cout<<'\n';   
    	}

    	for(i=4;i<8;i++){
        	for(j=0;j<spac;j++) std::cout<<" ";
        	for(k=0;k<small_str->size();k++){
            	if((*small_str)[k]==' ') std::cout<<' ';
            	else std::cout<<small[(int)((*small_str)[k])-65][i-4];
            	std::cout<<' ';
        	}
        	std::cout<<"   ";
        	for(k=0;k<big_str->size();k++){
            	if((*big_str)[k]==' ') std::cout<<"   ";
            	else std::cout<<big[(int)((*big_str)[k])-65][i];
            	std::cout<<' ';
        	}
        	std::cout<<'\n';   
    	}
    }
    else{
   		spac=(terminal_width - msglen - 5*(big_str->size()))/2;
   		for(i=0;i<4;i++){
        	for(j=0;j<spac;j++) std::cout<<" ";
        	for(k=0;k<small_str->size();k++){
            	if((*small_str)[k]==' ') std::cout<<' ';
            	else std::cout<<small[(int)((*small_str)[k])-65][i];
            	std::cout<<' ';
        	}
        	std::cout<<"   ";
        	for(k=0;k<big_str->size();k++){
            	if((*big_str)[k]==' ') std::cout<<"   ";
            	else std::cout<<small[(int)((*big_str)[k])-65][i];
            	std::cout<<' ';
        	}
        	std::cout<<'\n';   
    	}
    } 
    std::cout<<'\n';
}

void magnify(string pos, string *big_str){	//FUTURE - pos maybe "start","mid","end"
	capitallize(big_str);
	int spac, msglen = 10*(big_str->size()) - 1*1 + 3*numspaces(*big_str);	//no_of_spaces is 1, 2 for space b/w small and big 
    int i,j,k;
//    if( pos == "mid")	//FUTURE
	for(i=0;i<8;i++){
		spac = (terminal_width - msglen)/2;
		for(j =0 ; j<spac ;j++) std::cout<<' ';
    	for(k=0;k<big_str->size();k++){
        	if((*big_str)[k]==' ') std::cout<<"   ";
        	else std::cout<<big[(int)((*big_str)[k])-65][i];
        	std::cout<<" ";
    	}
    	std::cout<<'\n';   
	}
}

void smaller_magnify(string pos, string *small_str){	//For understanding the reasons of these numbers, refer magnify()
	capitallize(small_str);
	int spac, msglen = 5*(small_str->size()) - 1*1 + 2*numspaces(*small_str);
    int i,j,k;
//    if( pos == "mid")	//FUTURE
	spac=(terminal_width - msglen)/2;
	
	for(i=0;i<4;i++){
		for(j=0;j<spac;j++) std::cout<<" ";
		for(k=0;(*small_str)[k]!='\0';k++){
	    	if((*small_str)[k]==' ') std::cout<<' ';
	    	else std::cout<<small[(int)((*small_str)[k])-65][i];
	    	std::cout<<' ';
		}
		std::cout<<'\n';
	}
}

int numspaces(string s){
    short i=s.size(),j=0;
    while(i--){
        if(s[i]==' ') ++j;
    }
    return j;
}

void clearscr(){
    for(int i=0 ; i<terminal_height; i++)
        std::cout<<'\n';
}
//main_frontend.cpp functions END

void vibrate(string msg){	//Doesn't actually vibrate, as visulaization expected
	int space = terminal_width/2 - 5*msg.size()/4, amp_diff = msg.size()/4, amp_space =0;
	bool dir=true;	//towards right is true, and left is false
	
	//for(int i=0;i<(5*msg.size());++i){
	while(amp_diff != 0){
		for(int i=0;i<2*amp_diff + msg.size() -1;++i){
			system("clear");
			prt_t_header();
			greeting(name);
/*			std::cout<<amp_diff;
			for(int i=0;i<terminal_width/2-1;i++) std::cout<<' ';
			std::cout<<'|'<<std::endl;
*/			if(terminal_width<115){
				std::cout<<'\n';
			}
			else std::cout<<"\n\n";

			
			for(int j=0;j<space;j++) std::cout<<' ';	//the vibrations start here
			std::cout<<msg;
			std::cout<<std::endl;
			usleep(30000); //0.07 sec
			if(dir){
				space++;
				if((space - terminal_width/2) == 1*msg.size()/4 - amp_diff)
					dir = !dir;	//basically 'false'
				if(space == terminal_width/2 - msg.size())
					--amp_diff;
			}
			else{
				space--;
				if((terminal_width/2) - space == 5*msg.size()/4 - amp_diff)
					dir = !dir; //basically 'true'
			if(space == terminal_width/2)
					--amp_diff;
			}
		}
	}
}

//RECORDS.CPP functions START

//RECORDS.CPP functions END

timetable::timetable(){
			state=false;
			ndays=5;
			total_courses=0;
			day = new daylist[ndays];	//FUTURE - This helps to have option for more days
			string dayname;
			for(int i=0;i<ndays;i++){
				switch(i){
					case 0: dayname = "Monday";
					case 1: dayname = "Tuesday";
					case 2: dayname = "Wednesday";
					case 3: dayname = "Thursday";
					case 4: dayname = "Friday";
					case 5: dayname = "Saturday";
					case 6: dayname = "Sunday";
				}
				day[i].set_Day(dayname);
			}
			savefile = "BinaryTimeTable.dat";
			txtfile = "TimeTable.txt";
			recallfile = "BinaryTimeTable.dat";
}

timetable::~timetable(){
	for(int i=0; i<ndays; i++)
		day[i].~daylist();
	delete[] day;
}

int timetable::mainmenu(bool mainmenu_retval){
	if(!mainmenu_retval){
		return 0;
	}

	time_t t = time(0);
	time_now = *localtime(&t);

	int i=0;
	positive ch;
	do{
		system("clear");
		/*Printing Intro*/
		prt_t_header();
		set_h_w();
		string msg = "TimeTable Manager";

		/*magnify() can't be used here for now... this is a slightly bigger font*/
		for (i = 0; i < terminal_height/7; ++i)
			std::cout<<std::endl;
		int space = (terminal_width - 97)/2;
	for(i=0;i<space;i++) std::cout<<' ';
		std::cout<<"----- ----- \\   / ----- ----- /---\\ |---\\ |     -----   \\   / /---\\ \\   | /---\\ |---- ----- |---\\\n";
	for(i=0;i<space;i++) std::cout<<' ';
		std::cout<<"  |     |   |\\ /| |       |   |   | |   / |     |       |\\ /| |   | |\\  | |   | |     |     |   |\n";
    for(i=0;i<space;i++) std::cout<<' ';
		std::cout<<"  |     |   | - | |--     |   |---| |---  |     |--     | - | |---| | \\ | |---| |  -| |--   |---/\n";
    for(i=0;i<space;i++) std::cout<<' ';
		std::cout<<"  |     |   |   | |       |   |   | |   \\ |     |       |   | |   | |  \\| |   | |   | |     |  \\ \n";
    for(i=0;i<space;i++) std::cout<<' ';
		std::cout<<"  |   ----- |   | -----   |   |   | |---/ |---- -----   |   | |   | |   \\ |   | |---| ----- |   \\\n\n";
	for(i=0;i<space-1;i++) std::cout<<' ';
		std::cout<<"===================================================================================================\n";
		std::cout<<"The Manager that actually works.. and is FAST... bcz it \"JUST\" works ;)\n"
		    <<"Programmer - Aditya Gupta (aka. Techy15)"
		    <<"\n\nMain Menu\n---------"
		    <<"\n1. Enter Timetable"	
		    <<"\n2. Load from Memory"
		    <<"\n3. Save to Memory"
		    <<"\n4. Display"	//Displays Current
		    <<"\n5. Save to text file"
		    <<"\n6. Advanced Settings"
		    <<"\n7. Exit \n";
		std::cin>>ch;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max() , '\n');	//WILL NOT BE NEEDED, if sync b/w the streams is turned on
	}while(ch>7);
	switch(ch){
		case 1: fill(); break;
		case 2: load_from_binary(); break;
		case 3: save_to_binary(); break;
		case 4: display();
				return 0; break;	//return 0, since both of these give option to go back to mainmenu()
		case 5: savetxt();
				std::cout<<"\nSaved to the file : "<<txtfile; break;
		case 6: settings();
				return 0; break;
		case 7:	/*delete this;	//Throws "Segmentation Fault"
				exit(0); break;*/
				mainmenu(false);	//will cause all previous mainmenu() to exit!!
								//kind of a chain-initiation
				return 0;
	}
	mainmenu();
	return 0;
}

void timetable::settings(){
	positive ch = 1;
	while(ch<6){
		system("clear");
		std::cout<<"\nSETTINGS\n---------\n"
		    <<"\n1. Change name of save_file"
		    <<"\n2. Change name of save_txtfile"
		    <<"\n3. Change name of loadfrom_file"
		    <<"\n4. Change number of days to store"
		    <<"\n5. Change department/group name"
		    <<"\n6. Go to Main Menu"
		    <<"\nWhat do you want to (1-6)? ";
		std::cin>>ch;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max() , '\n');
		std::cout<<"\n\n";
		switch(ch){
			case 1: std::cout<<"Enter name of save_file : \n";
				getline (std::cin, savefile);
				std::cout<<"DONE!";
				break;
			case 2: std::cout<<"Enter name of txt_file:\n";
				getline (std::cin, txtfile);
				std::cout<<"DONE!";
				break;
			case 3: std::cout<<"Enter name of loadfrom_file (Source) : \n";

				getline (std::cin, recallfile);
				std::cout<<"DONE!";
				break;
			case 4: std::cout<<"Enter Number of Days to store in Timetable : ";
				std::cin>>ndays;
				std::cout<<"DONE!";
				break;
			case 5: std::cout<<"Department : \nCurrent - "<<dept<<"\nNew - ";
				getline (std::cin, dept);
				std::cout<<"\nGroup : ";
				getline (std::cin, grp);
				std::cout<<"DONE!";
				break;
			case 6: mainmenu();
					return; break;	/*QUESTION - This won't EVER return control to here... is it OK?*/
			}
			std::cout<<"\nEnter any key to chose different action...";
			std::cin.ignore();
	}
}

void timetable::fill(){
	int i=0;
	std::cout<<"TIP : Leave Blank, if nothing ; and 'y' or 'Y' for same as previous one\n";
	while(i<ndays){
		switch(i){
			case 0: std::cout<<"Monday\n------\n"; break;
			case 1: std::cout<<"Tuesday\n-------\n"; break;
			case 2: std::cout<<"Wednesday\n---------\n"; break;
			case 3: std::cout<<"Thursday\n-------\n"; break;
			case 4: std::cout<<"Friday\n------\n"; break;
			case 5: std::cout<<"Saturday\n--------\n"; break;
			case 6: std::cout<<"Sunday\n------\n"; break;
		}
		day[i].make_tlist();
		i++;

		/*FUTURE - std::cout<<"\nAny Special notes for this day (1 or 0)? "; */
		/*For the above, add 'string spec_notes' in daylist*/
	}
	state = true;
//	set_total_courses();
}

void timetable::set_total_courses(){
	for(int i=0;i<ndays;i++){
		for(int j=0;j<8;j++){
			if(day[i].tpoints[j] == NULL) continue;
			const string* sptr = day[i].tpoints[j]->get_coursecode();
			if(!distinct_courses.is_in_list( *sptr )){
				distinct_courses.add_in_list(*sptr);
				++total_courses;
			}
		}
	}
}


void timetable::display(){	//WHOLLY REVAMPED DISPLAY() Function... from Scratch!!
							//Previous one used array, now working directly with the pointers

/**FUTURE - a) With graphics use, highlight timetable of current day
	 * 	OR  b) After the timetable, show strip of timetable of today, again, separately*/

	//FUTURE- Show current 'day' using time of system... like this above the table
/*
 * 	Current_Day								      Current_Year
 *	eg. Tuesday                                                                   eg. 2019	
*/
	/*Future - If timetable available for Sat & Sun also, print them also*/
	/*FUTURE - To be able to have Sat & Sun also...
	 * 	    better will be that contoarray provides other ways to tell us if it has passed a [6][8] or [7][8] array...
	 * 	    maybe by uupdating data member in the class, named ndays*/

	refresh_time();
	system("clear");
	int i=0, j=0, k=0;
	//[DONE]Display time and day here, course code etc

	std::cout<<"Date Printed : "<<time_now.tm_mday<<'-'<<time_now.tm_mon+1<<'-'<<time_now.tm_year + 1900;
	std::cout<<'\n';
	std::cout<<"Department : "<<dept;
	for(i=0;i<114-dept.size()- grp.size() - 21;i++ )	//-13 for "Department : " and -8 for "Group : "
		std::cout<<' ';
	std::cout<<"Group : "<<grp<<'\n';
	for( i=0 ; i<114 ; ++i)
		std::cout<<'/';
	std::cout<<std::endl;
	for( i=0 ; i<114 ; ++i)
		std::cout<<'/';
	std::cout<<std::endl;
	std::cout<<"||    Day    |";
	for( i=0 ; i<9 ; ++i ){
		if( i < 2 ) std::cout<<8+i<<":30      |";
		else if( i < 5 ) std::cout<<8+i<<":30     |";
		else std::cout<<i-4<<":30      |";
	}
	std::cout<<"|\n||           |";
	for( i=0 ; i<9 ; ++i ){
		if( i < 1 ) std::cout<<"      "<<9+i<<":30|";
		else if( i < 4 ) std::cout<<"     "<<9+i<<":30|";
		else std::cout<<"      "<<i-3<<":30|";
	}
	std::cout<<"|\n||";
	for( i=0 ; i<110 ; ++i)
		std::cout<<'-';
	std::cout<<"||\n";

	for( i=0 ; i<5 ;i++ )	//for block prints shedule of a compelete day
	{	
		std::cout<<"||";
		switch(i){			//switch block  prints the day name
			case 0: std::cout<<"Monday     "; break;
			case 1: std::cout<<"Tuesday    "; break;
			case 2: std::cout<<"Wednesday  "; break;
			case 3: std::cout<<"Thursday   "; break;
			case 4: std::cout<<"Friday     "; break;
		}
		std::cout<<'|';
		int len=0;
		for( j=0 ; j<4 ; ++j ){
			if( ret_day(i)->tpoints[j] != NULL ){
//				len = d[i].tpoints[j]->get_coursecode()->size();	//Display CourseCode
				len = ret_day(i)->tpoints[j]->get_coursecode()->size();
				for( k=0 ; k < 5 -len/2 ; ++k ) std::cout<<' ';
//				std::cout<<*(d[i].tpoints[j]->get_coursecode());
				std::cout<<*(ret_day(i)->tpoints[j]->get_coursecode());
				for( k=0 ; k < 5 -len + len/2 ; ++k ) std::cout<<' ';
			}
			else{
				for( k=0 ; k < 10 ; ++k ) std::cout<<' ';
				}
			std::cout<<'|'; 
		}
		std::cout<<"     ";
		switch(i){
			case 0 : std::cout<<'B'; break;
			case 1 : std::cout<<'R'; break;
			case 2 : std::cout<<'E'; break;
			case 3 : std::cout<<'A'; break;
			case 4 : std::cout<<'K'; break;
		}
		std::cout<<"    |";
		for( j=4 ; j<8 ; ++j ){
			if( ret_day(i)->tpoints[j] != NULL ){
//				len = d[i].tpoints[j]->get_coursecode()->size();	//Display CourseCode
				len = ret_day(i)->tpoints[j]->get_coursecode()->size();
				for( k=0 ; k < 5 -len/2 ; ++k ) std::cout<<' ';
//				std::cout<<*(d[i].tpoints[j]->get_coursecode());
				std::cout<<*(ret_day(i)->tpoints[j]->get_coursecode());
				for( k=0 ; k < 5 -len + len/2 ; ++k ) std::cout<<' ';
			}
			else{
				for( k=0 ; k < 10 ; ++k ) std::cout<<' ';
				}
			std::cout<<'|'; 
		}

		std::cout<<"|\n";
		std::cout<<"|| ";
		for( k=0 ; k<10;k++ ) std::cout<<"          |";
		std::cout<<"|\n";
	}
	for( i=0 ; i<116 ; ++i)
		std::cout<<'-';
	std::cout<<std::endl;
	for( i=0 ; i<116 ; ++i)
		std::cout<<'-';
	std::cout<<"\n\nTimeTable Printed!!\n";
	int ch;
	do{
		std::cout<<"\nWhat Next?\n1. Save to text file\n2. Go back to main menu\n";
		std::cin>>ch;
	}while(ch!=1 && ch!=2);

	if(ch==1)	savetxt();
	else{	//This will surely be ch=2... since all other numbers have been managed by do-while loop
		mainmenu();
	}
	return;	//To Continue the chain reaction that ends up closing mainmenu() whenever it returns false;
}	//End of Display Function

void timetable::save_to_binary(){
	std::ofstream fsave;
	fsave.open( savefile , std::ios::binary|std::ios::out);
	fsave.write((char*)&state,sizeof(state));	//state is lesser bytes than char, but the &state and char* will be same size, and for the bytes saved in file, it will save 1 byte, due to that sizeof()	
	fsave.write((char*)&ndays,sizeof(ndays));
	size_t len = savefile.size() +1;
	fsave.write((char*)&len,sizeof(len));
	fsave.write(savefile.c_str(),len*sizeof(char));
	len = txtfile.size() +1;
	fsave.write((char*)&len,sizeof(len));
	fsave.write(txtfile.c_str(),len*sizeof(char));
	len = recallfile.size() +1;
	fsave.write((char*)&len,sizeof(len));
	fsave.write(recallfile.c_str(),len*sizeof(char));
	len = dept.size() +1;
	fsave.write((char*)&(len),sizeof(len));
	fsave.write(dept.c_str(),len*sizeof(char));
	len = grp.size() +1;
	fsave.write((char*)&len,sizeof(len));
	fsave.write(grp.c_str(),len*sizeof(char));
	fsave.write((char*)&total_courses,sizeof(total_courses));
	for(int i=0;i<ndays;++i)
		day[i].save_to_binary(&fsave);
	std::cout<<"End of timetable save!\n";
	fsave.close();
}

void timetable::load_from_binary(){
	std::ifstream f_recall;
	f_recall.open( recallfile ,std::ios::binary|std::ios::in);
	f_recall.read((char*)&state, sizeof(state));
	f_recall.read((char*)&ndays,sizeof(ndays));
	//instead of auto, replastd::cing with size_t
	char *cstr;	//This is just a pointer to a random block of 1 byte (but for now, even that block isn't reserved)
	size_t len;	//May Cause a Bug, since when saving, it used 'auto' to determine the type
	f_recall.read((char*)&len,sizeof(len));	//len was random here... as big as hell, and also 0
	cstr = new char[len];
	f_recall.read(cstr,len*sizeof(char));	//it couldn't read cstr
	savefile = cstr;
	delete[] cstr;
	f_recall.read((char*)&len,sizeof(len));
	cstr = new char[len];
	f_recall.read(cstr,len*sizeof(char));
	txtfile = cstr;
	delete[] cstr;
	f_recall.read((char*)&len,sizeof(len));
	cstr = new char[len];
	f_recall.read(cstr,len*sizeof(char));
	recallfile = cstr;
	delete[] cstr;
	f_recall.read((char*)&(len),sizeof(len));
	cstr = new char[len];
	f_recall.read(cstr,len*sizeof(char));
	dept = cstr;
	delete[] cstr;
	f_recall.read((char*)&len,sizeof(len));
	cstr = new char[len];
	f_recall.read(cstr,len*sizeof(char));
	grp = cstr;
	delete[] cstr;
	f_recall.read((char*)&total_courses,sizeof(total_courses));
	for(int i=0;i<ndays;++i)
		day[i].load_from_binary(&f_recall);
	std::cout<<"End of timetable LOAD!\n";
	f_recall.close();
}

void timetable::savetxt(){
	std::ofstream fout;
	fout.open( txtfile , std::ios::out|std::ios::trunc );
	int i=0, j=0, k=0;
	refresh_time();
	//[DONE]Display time and day here, course code etc
	fout.seekp(0);
	fout<<"Date Printed : "<<time_now.tm_mday<<'-'<<time_now.tm_mon+1<<'-'<<time_now.tm_year + 1900;
	fout<<'\n';
	fout<<"Department : "<<dept;
	for(i=0;i<114-dept.size()- grp.size() - 21;i++ )	//-13 for "Department : " and -8 for "Group : "
		fout<<' ';
	fout<<"Group : "<<grp<<'\n';
	for( i=0 ; i<114 ; ++i)
		fout<<'/';
	fout<<std::endl;
	for( i=0 ; i<114 ; ++i)
		fout<<'/';
	fout<<std::endl;
	fout<<"||    Day    |";
	for( i=0 ; i<9 ; ++i ){
		if( i < 2 ) fout<<8+i<<":30      |";
		else if( i < 5 ) fout<<8+i<<":30     |";
		else fout<<i-4<<":30      |";
	}
	fout<<"|\n||           |";
	for( i=0 ; i<9 ; ++i ){
		if( i < 1 ) fout<<"      "<<9+i<<":30|";
		else if( i < 4 ) fout<<"     "<<9+i<<":30|";
		else fout<<"      "<<i-3<<":30|";
	}
	fout<<"|\n||";
	for( i=0 ; i<110 ; ++i)
		fout<<'-';
	fout<<"||\n";

	for( i=0 ; i<5 ;i++ )	//for block prints shedule of a compelete day
	{	
		fout<<"||";
		switch(i){			//switch block  prints the day name
			case 0: fout<<"Monday     "; break;
			case 1: fout<<"Tuesday    "; break;
			case 2: fout<<"Wednesday  "; break;
			case 3: fout<<"Thursday   "; break;
			case 4: fout<<"Friday     "; break;
		}
		fout<<'|';
		int len=0;
		for( j=0 ; j<4 ; ++j ){
			if( ret_day(i)->tpoints[j] != NULL ){
//				len = d[i].tpoints[j]->get_coursecode()->size();	//Display CourseCode
				len = ret_day(i)->tpoints[j]->get_coursecode()->size();
				for( k=0 ; k < 5 -len/2 ; ++k ) fout<<' ';
//				fout<<*(d[i].tpoints[j]->get_coursecode());
				fout<<*(ret_day(i)->tpoints[j]->get_coursecode());
				for( k=0 ; k < 5 -len + len/2 ; ++k ) fout<<' ';
			}
			else{
				for( k=0 ; k < 10 ; ++k ) fout<<' ';
				}
			fout<<'|'; 
		}
		fout<<"     ";
		switch(i){
			case 0 : fout<<'B'; break;
			case 1 : fout<<'R'; break;
			case 2 : fout<<'E'; break;
			case 3 : fout<<'A'; break;
			case 4 : fout<<'K'; break;
		}
		fout<<"    |";
		for( j=4 ; j<8 ; ++j ){
			if( ret_day(i)->tpoints[j] != NULL ){
//				len = d[i].tpoints[j]->get_coursecode()->size();	//Display CourseCode
				len = ret_day(i)->tpoints[j]->get_coursecode()->size();
				for( k=0 ; k < 5 -len/2 ; ++k ) fout<<' ';
//				fout<<*(d[i].tpoints[j]->get_coursecode());
				fout<<*(ret_day(i)->tpoints[j]->get_coursecode());
				for( k=0 ; k < 5 -len + len/2 ; ++k ) fout<<' ';
			}
			else{
				for( k=0 ; k < 10 ; ++k ) fout<<' ';
				}
			fout<<'|'; 
		}

		fout<<"|\n";
		fout<<"|| ";
		for( k=0 ; k<10;k++ ) fout<<"          |";
		fout<<"|\n";
	}
	for( i=0 ; i<116 ; ++i)
		fout<<'-';
	fout<<std::endl;
	for( i=0 ; i<116 ; ++i)
		fout<<'-';
	fout.close();
}

string** timetable::contoarray(){	//Returning 2D array... MAY FAIL
	string** retarr;
	retarr=(string**)(new string[ndays][8]);	//IMPORTANT - DON'T FORGET TO DELETE
	for(int i=0;i<ndays;i++)
		for(int j=0;j<8;j++){
            if(day[i].tpoints[j])
			    retarr[i][j]=*(day[i].tpoints[j]->get_coursecode());
            else retarr[i][j]="NULL"; }
	return retarr;
}

daylist* timetable::ret_day(int dayn){
	if ( dayn < 0 || dayn >= ndays){
		
		//My error handling... since if NULL is returned, and accessed it may cause Segmentation Fault
		std::cout<<"Invalid Input Passed... Destructing Nodes, to prevent memory leak...";
		for(int i=0; i<ndays; i++)
			day[i].~daylist();
		std::cout<<"Exiting...";
		//~timetable();		//Couldn't Call Destructor... no match for 'operator~'
		delete this;
		exit(0);
		//All destructed... seems safe, but IMPROVE IT (maybe using try, throw and catch)
		return NULL;
	}
	else return &day[dayn];
}

daylist::daylist(){
			front=rear=NULL;
			numbox=0;
}

daylist::~daylist(){
				//IMP - In these destructors, remember to use 'delete' data allocated using 'new'
	timeboxn *tmp = front;
    while(numbox && !(front)){
        tmp=front;
        front=tmp->next;
        delete tmp;
}
}

void daylist::make_tlist(){
	bool tbox_extend_flag = true;	//tells if, to just extend endtime of previous box by 1, or to create a new box altogether... in case 'y' is entered
	int i=8;
	string s;
	for(i=8;i<17;i++){
		if( i < 11){
			std::cout<<'\t'<<i<<":30am-"<<i+1<<":30am ";
			if( i ==8 ) std::cout<<"  ";
			else if ( i==9 ) std::cout<<' ';
			std::cout<<"- ";
		}
		else 	if( i == 11 )
					std::cout<<"\t11:30am-"<<"12:30pm - ";
				else if ( i ==12 ) continue;
					 else
						std::cout<<'\t'<<i-12<<":30pm-"<<i-11<<":30pm - ";

		getline ( std::cin, s );
		if( s == "" ){	//in case there's an empty box (a gap), we can't simply increase endtime, by a simple 1, nor 2 nor others
			tbox_extend_flag = false;	//tells not to extend endtime, of previous box, instead create a new box altogether
			continue;
		}
		else{	if ( s == "y" || s=="Y" ){
					if(tbox_extend_flag){	//if it's true, extend endtime
						float *endt = &(traverseto(numbox-1)->endtime);
						if( *endt < 11 || *endt > 12 )
							*endt +=1;
						else *endt +=2;
					}
					else{
						append_box( traverseto(numbox-1)->get_coursecode() , i );
						tbox_extend_flag = true;	//resetting this flag, since there's no gap
					}
				}
				else
					append_box( &s , i );
		}
	}
	set_tpoints();
}

timeboxn::timeboxn(){

	next=NULL;
	prev=NULL;
//	recbox = NULL;
	coursecode = "NULL";
}

string* timeboxn::get_coursecode(){
	return &coursecode;
}

void timeboxn::change_coursecode(string* sptr){
	coursecode = *sptr;
}

void timeboxn::change_coursecode(char* sptr){
	coursecode = *sptr;
}

void daylist::append_box(string* s, int stime){
	timeboxn *node = new timeboxn;
	node->change_coursecode(s);
	//Loop to set 'sub'
	string tmpstr = *s;
	int i=0,j=0,k=0;
	for ( i=0 ; i<tmpstr.size() ; i++ ){
		k=i;
		while(tmpstr[k] >= 48 && tmpstr[k] <= 57 && k!=tmpstr.size())
			k++;
		for(j=0; j< tmpstr.size() - k +1 ;j++){
			tmpstr[j+i] = tmpstr[j+k];
		}
		tmpstr.resize(j+i-1);
	}
	node->sub = tmpstr;
	//Loop end

	node->starttime = stime + 0.5;
	node->endtime = stime + 1.5;
	if( front ){
		node->prev = rear;
		rear->next = node;
		node->next = NULL;
		rear = node;
	}
	else{
		node->next = NULL;
		node->prev = NULL;
		front = node;
		rear = node;
	}
	++numbox;
}

void daylist::set_tpoints(){
	int i=0;
	float st=8.5, et=8.5;
	timeboxn* tptr;		
	for(i=0;i<numbox;++i){
		tptr = traverseto(i);
		st = tptr->starttime;
		et = tptr->endtime;
		if( st < 13 )		//FUTURE - May make these loops, a bit faster
			tpoints[int(st-8.5)] = tptr;
		else
			tpoints[int(st-9.5)] = tptr;
		for(int j=st+1; j<et; j++){
			if( j < 13 )
				tpoints[int(j-8.5)] = tptr;
			else
				tpoints[int(j-9.5)] = tptr;
		}
	}

}

timeboxn* daylist::traverseto(int loc){
	if(loc < 0) return NULL;
	else if(loc >= numbox){
		std::cout<<"\nEnough Entries Not Available";
		return NULL;
	}

	static timeboxn* retptr;	//made static, so that no other memory can alter the location stored in pointer
	retptr=front;	//don't merge with above, since it's static
	for(int i=0;i<loc;i++)
		retptr=retptr->next;
	return retptr;

}

void daylist::save_to_binary(std::ofstream* fsave){
	size_t len = day.size() + 1;
	fsave->write((char*)&len,sizeof(len));
	fsave->write(day.c_str(),(len*sizeof(char)));	
	fsave->write((char*)&numbox,sizeof(numbox));
	timeboxn *temp;
	temp = front;
	for(int i=0;i<numbox;i++){	//while(temp != NULL)
		len = temp->get_coursecode()->size() + 1;
		fsave->write((char*)&len,sizeof(len));	//Actually sizeof() returns auto, which is 8bytes, but still...
		fsave->write(temp->get_coursecode()->c_str(),len*sizeof(char));
		len = sizeof(temp->sub);
		fsave->write((char*)&len,sizeof(len));
		fsave->write(temp->sub.c_str(),len*sizeof(char));
		fsave->write((char*)&temp->starttime,sizeof(temp->starttime));
		fsave->write((char*)&temp->endtime,sizeof(temp->endtime));
		temp = temp->next;
	}
}

void daylist::load_from_binary(std::ifstream* f_recall){
	size_t len;
	char *cstr;
	string str;
	f_recall->read((char*)&len, sizeof(len));
	cstr = new char[len];
	f_recall->read(cstr,len*sizeof(char));	
	day = cstr;
	delete[] cstr;
	f_recall->read((char*)&numbox,sizeof(numbox));
	front = NULL;
	timeboxn *tmp = front;
	timeboxn *box;	//will be alloted by 'new'
	for(int i=0;i<numbox;i++){	//while(temp != NULL)
		box = new timeboxn;
		
		if(i == 0){	//For setting *front
			front = box;
			
		}
		else{
			box->prev = tmp;
			box->prev->next = box;
		}

		f_recall->read((char*)&len,sizeof(len));
		cstr = new char[len];
		f_recall->read(cstr,len*sizeof(char));
		box->change_coursecode(cstr);
		delete[] cstr;

		f_recall->read((char*)&len,sizeof(len));	//Actually sizeof() returns auto, which is 8bytes, but still...
		cstr = new char[len];
		f_recall->read(cstr,len*sizeof(char));
		box->sub = cstr;
		delete[] cstr;
		f_recall->read((char*)&box->starttime,sizeof(box->starttime));
		f_recall->read((char*)&box->endtime,sizeof(box->endtime));
		box->next = NULL;
		rear = box;
		tmp = box;
	}
	set_tpoints();
}

void daylist::set_Day(string daystr){
	day = daystr;
}

a_register::a_register(){
//	get_initstatus();
	today_num_courses = 0;
}

void listbox::parseinput(string s){
//	update_num_courses();	//already called, by set_today_array(), which itself called by the constructor
	for(int i=0;i<today_num_courses;++i){
		if(s[i] == 'y' || s[i] == 'Y' || s[i] == '1' )
			++(todaylist[i]->npresent);
		else if(s[i] == 'n' || s[i] == 'N' || s[i] == '0' )
			++(todaylist[i]->nabsent);
		else if(s[i] == 'b' || s[i] == 'B' || s[i] == '2' ) 
			++(todaylist[i]->nbunk);
		else {
			std::cout<<"\nWe couldn't interpret "<<s[i]<<"\nReverting all updates of today... Try Again :)";
			for(int j=i-1;j>=0;--j){
				if(s[j] == 'y' || s[j] == 'Y' || s[j] == '1' )
					--(todaylist[j]->npresent);
				else if(s[j] == 'n' || s[j] == 'N' || s[j] == '0' )
					--(todaylist[j]->nabsent);
				else --(todaylist[j]->nbunk);	//It can only be one among these 3
			}
		}
	}
}

void a_register::update_num_courses(){
	daylist *today;
	if((time_now.tm_wday + 6)%7 <= table.ndays)
		today = table.ret_day((time_now.tm_wday + 6)%7);
	else {
		today_num_courses=0;
		return;
	}
	string_list tmplist;
	for(int j=0;j<8;j++){
		const string* sptr = today->tpoints[j]->get_coursecode();
		if(!tmplist.is_in_list( *sptr )){
			tmplist.add_in_list(*sptr);
			++today_num_courses;
		}
	}
	table.set_total_courses();
}

void listbox::totaldisplay(){
	irecbox *tmp = front;
	for(int i=0, j=0; i<numbox; i++){
		cout<<tmp->get_coursecode()<<'\n';
		for(j=0;j<tmp->get_coursecode().size(); ++j)
			cout<<'-';
		cout<<"\nPresent = "<<tmp->npresent
			<<"\nAbsent = "<<tmp->nabsent
			<<"\nBunks = "<<tmp->nbunk;
		cout<<"\n\n";		
	}
}

irecbox* listbox::find_irecbox(string *search_code){
	irecbox *tmp_ptr = front;

	for(int i=0; i<numbox; ++i){
		if(*search_code == tmp_ptr->get_coursecode())
			return tmp_ptr;
//WARNING - Returning local pointer...
	//Q. BUT IS IT PROBLEMATIC, SINCE I HAVE PASSED THE ADDRESS VALUE OF A NODE, WHICH STILL EXISTS ??
		tmp_ptr = tmp_ptr->next;
	}
	return NULL;
}

void listbox::set_today_array(){
	int tmp_num = 0;
	irecbox *tmpbox;
	todaylist = new irecbox*[a_register::today_num_courses];
	refresh_time();
	if(time_now.tm_wday < a_register::table.ndays){
		//tm_wday is 0 for Sunday... so, for Friday, it's 5...
		// ret_day(int) takes input from 0(Monday) to Sunday(6)so only problem is to make Sunday as 6
		string_list tmp_daylist;
		//The below 'const' caused the error: passing 'const timeboxn' as 'this' argument discards qualifiers [-fperissive]
		/*const */timeboxn *temp = a_register::table.ret_day((time_now.tm_wday + 6)%7)->traverseto(0);
		//WARNING - The above can lead to HACKING of the system... since, even though *front is private, by using public function traverseto(0) returns the *front pointer!!	And same goes, for functions that are returning modifiable pointers to the private data members
		while(temp!=NULL){
			if(tmp_daylist.is_in_list(*(temp->get_coursecode())))
				continue;
			else{
				tmp_daylist.add_in_list(*(temp->get_coursecode()));
				todaylist[tmp_num] = find_irecbox(temp->get_coursecode());
					//The above line may cause SEGMENTATION FAULT
				++tmp_num;
			}
		}
//		if(tmp_num - 1 != a_register::today_num_courses ) //THEN IT's !!!!BAD!!!!
//		if(todaylist[i] == NULL)... it's a critical problem, and may cause Segmentation Fault
		//CONSIDERING OK FOR NOW!
	}
	else{
		cerr<<"Today's TimeTable can't be loaded, or it hasn't been entered for ";
		switch(time_now.tm_wday){
			case 0: cerr<<"Sunday"; break;
			case 1: cerr<<"Monday"; break;
			case 2: cerr<<"Tuesday"; break;
			case 3: cerr<<"Wednesday"; break;
			case 4: cerr<<"Thursday"; break;
			case 5: cerr<<"Friday"; break;
			case 6: cerr<<"Saturday"; break;
		}
		cerr<<'\n';
	}
}

listbox::listbox(){
	a_register::update_num_courses();
	front = rear = NULL;
	numbox = 0;
	initiate();
}

void listbox::initiate(){
	int length = a_register::table.total_courses;
	strnode *iter = a_register::table.distinct_courses.front;	//iterates through whole list
	irecbox *rbox;
	for(int i=0; i< length; ++i){
		rbox = new irecbox;
		rbox->change_coursecode(iter->s);
		iter = iter->next;
	}
	numbox = length;
}

listbox::~listbox(){
	irecbox *tmp= front;
	delete[] todaylist;
	for(int i=0; i<numbox; ++i){	//or, while(front != NULL)
		tmp = front;
		front = front->next;
		delete tmp;
	}
}

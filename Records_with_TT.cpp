//TODO - Read all FUTURE and NOTE comments

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
#include <cstdlib>		//For using system("clear")
#include <limits>	//for std::numeric_limits
//#include <ios>	//for <std::streamsize>, both these used in std::cin.ignore()
#include<vector>
#include<list>
#include<cmath>
#include<algorithm>
/*
#if __cplusplus >= 201402	//Actually it should be 201703L, but some earlier versions of G++ using C++17 didnt change __cplusplus, like mine
							//LEARNT - 201402 vs 201402L -> The 'L' at end signifies long, thats it
	#include<filesystem>	//after C++17, std::filesystem
#else
	#include<boost/filesystem.hpp>	//before C++17, boost::filesystem
#endif
*/
#include<experimental/filesystem>

#define testMode true

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

/*



*/

tm time_now;
//the 27th character is '?'
string bigChar[27][8]={{"---------","|  ---  |","|  | |  |","|  ---  |","|  | |  |","|  | |  |","|  | |  |","---- ----"},{"--------\\","|  ---  |","|  | |  |","|  ---  /","|  ---  \\","|  | |  |","|  ---  |","--------/"},{"--------\\","|       |","|  -----/","|  |     ","|  |     ","|  -----\\","|       |","--------/"},{"--------\\","|  ---\\ |","|  |  | |","|  |  | |","|  |  | |","|  |  | |","|  ---/ |","--------/"},{"---------","|       |","|  ------","|  --\\   ","|  --/   ","|  ------","|       |","---------"},{"---------","|       |","|  ------","|  |     ","|  ====  ","|  |     ","|  |     ","----     "},{"--------\\","|       |","|  -----/","|  |     ","|  \\=====","|    |  |","|    |  |","-----/  |"},{"---   ---","| |   | |","| |   | |","| ----- |","| ----- |","| |   | |","| |   | |","---   ---"},{"---------","|--- ---|","   | |   ","   | |   ","   | |   ","   | |   ","|--- ---|","---------"},{"---------","|--- ---|","   | |   ","   | |   ","   | |   ","   | |   ","/--- -   ","|----/   "},{"---   ---","| |  / / ","| | / /  ","| /  /   ","| \\  \\   ","| | \\ \\  ","| |  \\ \\ ","---   ---"},{"---      ","| |      ","| |      ","| |      ","| |      ","| |      ","|--- ---|","\\-------|"},{"---   ---","|  \\ /  |","|       |","|  \\ /  |","|  | |  |","|  | |  |","|  | |  |","---- ----"},{"---   ---","|\\\\   | |","| \\\\  | |","| |\\\\ | |","| | \\\\| |","| |  \\\\ |","| |   \\\\|","---   ---"},{"---------","| ----- |","| |   | |","| |   | |","| |   | |","| |   | |","| ----- |","---------"},{"---------","| ----- |","| |   | |","| -----/ ","| |      ","| |      ","| |      ","---      "},{"---------","| ----- |","| |   | |","| |   | |","| |   | |","| =======","| ======|","---------"},{"---------","| ----- |","| |   | |","| ----- /","| |\\  \\  ","| | \\  \\ ","| |  \\  \\","---   ---"},{"---------","| |      ","| |      "," \\ --- \\ ","      | |","      | |","|--- ---|","\\-------|"},{"---------","---| |---","   | |   ","   | |   ","   | |   ","   | |   ","   | |   ","   ---   "},{"---   ---","| |   | |","| |   | |","| |   | |","| |   | |","| |   | |","\\ ----- /"," ------- "},{"---   ---","| |   | |","| |   | |","| |   | |","| |   | |","\\ \\   / /"," \\  -  / ","  -----  "},{"--     --","||     ||","||     ||","||     ||","||     ||","\\\\  |  //"," \\\\/ \\// ","  -   -  "},{"--     --"," \\\\   // ","  \\\\ //  ","   \\ /   ","   / \\   ","  // \\\\  "," //   \\\\ ","--     --"},{"---   ---","\\ \\   / /"," \\ \\ / / ","  \\   /  ","   | |   ","   | |   ","   | |   ","   ---   "},{"---------","-------/ ","     //  ","    //   ","   //    ","  //     "," /-------","---------"},{"         ","         ","  /---\\  ","  |   |  ","     /   ","    /    ","    |    ","    O    "}};
string smallChar[27][4]={{"----","|  |","|--|","|  |"},{"----","|__|","|  |","----"},{"----","|   ","|   ","----"},{"---\\","|  |","|  |","---/"},{"----","|__ ","|   ","----"},{"----","|__ ","|   ","|   "},{"----","|   ","| -|","---|"},{"|  |","|__|","|  |","|  |"},{"----"," || "," || ","----"},{" ---","   |","   |","---/"},{"|  /","|/  ","|\\  ","|  \\"},{"|   ","|   ","|   ","----"},{"|  |","|\\/|","|  |","|  |"},{"|  |","|\\ |","| \\|","|  \\"},{"/--\\","|  |","|  |","\\--/"},{"/--\\","|__|","|   ","|   "},{"|--|","|  |","| \\|","|--\\"},{"/--\\","|__|","|\\  ","| \\ "},{"/--\\","|__","   |","\\--/"},{"----"," || "," || "," || "},{"|  |","|  |","|  |","|__|"},{"|  |","|  |","\\  /"," \\/ "},{"\\  /"," \\/ "," /\\ ","/  \\"},{"\\  /"," \\/ "," /\\ ","/  \\"},{"\\  /"," \\/ "," /  ","/   "},{"/---","  / "," /  ","---/"},{"/---","\\  |","  / ","  o "}};
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
					Change - Removed fillbox() from timebox class, and implemented the above said in parent daylist class*/

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

class timebox{
	string coursecode;
//	irecbox *recbox;
	public:
		bool box_type;	//false for recess, true for class(default)
		string sub;
        float starttime,endtime;  //store 9:30 as 9.5 & 1:30 pm as 13.5... ie. in 24-HOUR FORMAT
					//Auto assume am for any time (6,12), and for all others 'pm'
//    	timebox *next,*prev;
		
    	timebox();
//        void fillbox();	//have this fillbox in its parent, and there dont ask user to enter time also, just keep taking input for different intervals, let user leave it blank, if empty period
        /*const */string get_coursecode(void) const;
        void change_coursecode(string);
//Added on 25 December 2019
        void change_coursecode(const char*);	//Used ONLY in daylist::load_from_binary()...
        								//CAN BE REMOVED ONCE daylist::append_box() is utilized
		void set_sub(void);
};

class daylist{

			/*PROPOSED CHANGES - Utilize append_box() in load_from_binary... first check if it is LAB course or not, then call append_box()
			*/
	string day;	//let the parent fill this, and in capitals
	std::vector<timebox> timelist;	//the day's list
	public:
	/*static*/ float class_start, class_end, class_length, recess_start, recess_end;	//class_length seems more connected to timetable class
		int numBox;	//basically size of timelist, NOT_REQUIRED
	    vector</*const */timebox*> tpoints;	//IMP_NOTE - THE CONST IS HIGHLY PROBLEMATIC HERE!
//DECIDED_COMMENT - //WARNING - If wanting to dynamically allocate tpoints, change timetable::set_total_courses().. No need to dynamically allocate though
		void set_tpoints();
		void show_tpoints();	//FOR DEBUG PURPOSES
		void make_tlist();
		void set_Testmode_tlist(void);
//Added on 25 DECEMBER 2019, after >7 days try
		void load_from_binary(std::ifstream*); //also calls set_tpoints() at end
		void save_to_binary(std::ofstream*);
		void set_Day(string);	//25 Aug 2019 - Made 'day' private
//Suggested on 26 DECEMBER 2019
//		bool isLabCourse(string);
		void reset_records(void);	//to be used before loading from file
		void DEBUG_show_timelist(void);	//to see difference between tpoints and the timelist
		int getmaxCCLen(void);
		const string get_Day(void) const;
		daylist();
		~daylist();                   
};

const string daylist::get_Day(void) const{
	return day;
}

int daylist::getmaxCCLen(){
	int maxCCLen = 0;
	for(timebox &t : timelist){	//this line prevents this method from being const
		if(t.get_coursecode().size() > maxCCLen)
			maxCCLen = t.get_coursecode().size();
	}
	return maxCCLen;
}

void daylist::DEBUG_show_timelist(){
	for(int i=0; i<timelist.size(); ++i){
		std::cout<<timelist[i].starttime<<" - "<<timelist[i].endtime<<" == "<<timelist[i].get_coursecode()<<std::endl;
	}
}

void daylist::reset_records(){
	day.clear();
	timelist.clear();
	numBox = 0;
	tpoints.clear();
	class_start = 8,5;
	class_end = 17.5;
	class_length = 1;
	recess_start = 12.5;
	recess_end = 13.5;
}

void daylist::show_tpoints(){
	for( const timebox* box : tpoints){
		if(box == NULL){
			std::cout<<"NULL"<<std::endl;
			continue;
		}
		std::cout<<box->starttime<<" - "<<box->endtime<<" == "<<box->get_coursecode();
		std::cout<<std::endl;
	}
}

class timetable{	//TODO - Add Check in all methods of timetable, where it asks for choices.... IT IS NOT WORKING IN DISPLAY() CHECK IT
	bool state;		//'state' data member tells if it has been entered or not
	string save_TTFile,txtfile;	//Change these to department name + gp name, after user changes dept or grp
	string dept,grp;
	vector<daylist> days;	//UPDATE_NOTE - Using vectors makes it easier to accomodate Saturdays and Sundays
	public:		/*Future - Add functionality for 'n' temp-timetables (each for 1 day)... These will store Day,Date,Sub,time */
		int ndays;	//For the basic part, don't change 'ndays'
					//Made it public, so that a_register::update_num_courses() can access it
		int total_courses;	/*DONT RECOVER FROM CONFIG... let the functions auto-set this*/
		daylist* ret_day(int);		//int from 0 to 6 (or ndays)
		vector<vector<string>> contoarray(void);	//Deprecated... using tpointers to get values
//Added29th December, but all my work of 29th December was gone! So rewrote on 30th
		vector<string> distinct_courses;	//Use set_total_courses()
//[Replaced]        void save(void);
		void saveTXT(void);
		void display(void);	//change due to generalization
//[Replaced]		void loadfrom_file(void);
		void fill(void);
		void tt_Testmode(void);
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
		bool isFilled(void) const;
        timetable();
		~timetable();
					//UPDATE_FUTURE - Instead of using set_Day() in constructor, give fill() ability to take custom number of days, and call set_Day() in it
};

bool timetable::isFilled() const{
	return state;
}

void timetable::tt_Testmode(){
	ndays = 6;
	if(ndays != days.size()){
		if(ndays > days.size()){
			daylist new_day;
			for(int i=ndays - days.size(); i>0; i--){
				days.emplace_back(new_day);
			}
		}
		else{	//ie. day.size() is already more than ndays
			days.resize(ndays);
		}
	}

	string dayname;
	for(int i=0;i<ndays;i++){
		switch(i){
			case 0: dayname = "Monday"; break;
			case 1: dayname = "Tuesday"; break;
			case 2: dayname = "Wednesday"; break;
			case 3: dayname = "Thursday"; break;
			case 4: dayname = "Friday"; break;
			case 5: dayname = "Saturday"; break;
			case 6: dayname = "Sunday"; break;
		}
		days[i].set_Day(dayname);
	}

	for (int i = 0; i < ndays; i++)
	{
		days[i].set_Testmode_tlist();
	}

	set_total_courses();

	state = true;
	save_TTFile = "BinaryTimeTable.dat";
	txtfile = "TimeTable.txt";
	dept = "CSE";
	grp = "A1";

}

//RECORDS.CPP classes START
class irecbox
{
//	bool today;	//Stores whether it is today or not
//	int order;	//FUTURE... Curently using just the indices of the 'irecbox **todayarray'
	string coursecode;
//Added on 28th December 2019
//	timebox *course;	//Pointer to the course box
public:
	int npresent, nabsent, nbunk;/*, n_not_entered;	//Practically not that important*/
	string get_coursecode() const;
	void change_coursecode(string);
	irecbox(){
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


class a_register{
		//FUTURE_TODO - Have functions to convert the '.config', '.record', '.table' file to JSON
	//[DONE]FUTURE - Have username also in this class
	bool setup_complete;
	string last_savedTTFile;	//TODO - After recovering this, try to restore the TT from that file, if it exists
	string last_savedRecords;	//After recovering this, do same as above
			//NOTE - the '.record' file will have name of the table file it used
			//		iT WOuLD bE GooD FOr EAcH TT tO hAVE A UNiQue iD, to which the records will check whether its the same timetable, that was used to create it
					//FUTURE_NOTE - When we load the 'records_list' using the RECOVERconfig(), have a temporary copy, then change only those irecboxes that have the courcesoce present, in the records_list set by set_total_today_array()
	string user_name;
	vector<irecbox> records_list;	//total list
		//Put this array of pointers in this class, since it needs to access the a_register class list, but it can't from within a_register
//    irecbox **todaylist;	//Make 'array of pointers' using a_register::(*table).total_courses
	vector<irecbox*> todaylist;	//its elements aren't 'irecbox' but only pointers, since it can just point to records_list elements
public:
	int num_SavedTimetables;
	timetable table;	//links with table selected during initial setup
	//Read from the config file, and the table file (that too read from config file), and then load the table with that file name, then link with this
//	void get_initstatus();	//sets setup_complete
	bool RECOVERconfig(void);	//IT MAY BE MADE A GLOBAL FUNCTION
						//recovers from Attendance_Register.conf file...
						//	It will store : setup_complete, table_name, timetable::total_courses (not of today; that will be set by function),
						//					a_register data (of irecboxes)
						// If config file not found, OR even after RECOVER, the setup_complete bool is false, then ensureInitStatus() will be called

//	void settings();	//FUTURE
	void totaldisplay(void);
	void idisplay(string);	//Displays records for a particular records only
	//FUTURE - Display when the particular coursecode takes place also... preferably, link it with it's lab course also
	void parseInput(string);	//Updates the records with the given input
								//trear as yynny, or YNN, or YnnNy, or Y10nn1... ie. check each digit individualy == 'y' || 'Y' || '1'
	void set_total_today_array(void);
	irecbox* find_irecbox(string);	//finds in records_list
	bool already_present_in_todaylist(string);
	bool already_present_in_recordslist(string);
	void ensure_InitStatus(void);	//Checks whether initial setup complete or not
	void newWelcome(void);	//For first time use (ie. table not set)
	void set_num_SavedTimetables(void);	//Sees how many '.table' files are available in 'Timetables' folder
	void listTimetables(void);	//this can and will set the num_SavedTimetables integer, but still setter method for that is also required
//	void WelcomeScreen(void);	//asks for attendance, then calls parseString
	void set_up_TestMode(void);
	void parseStringScreen(void);	//NOTE - May have to make as the mainmenu() function
	void testModeScreen(void);
	a_register();
	~a_register();
};

void a_register::testModeScreen(){
	set_up_TestMode();
	table.display();
	parseStringScreen();
}

void a_register::set_up_TestMode(){
	table.tt_Testmode();
	setup_complete = true;
	set_total_today_array();//cAUSING SEGFAULT
	set_num_SavedTimetables();
}

void a_register::listTimetables(){
/*	namespace fs = std::filesystem;
	int count = 0;
	string path_to_directory = "./tables";
	for(const auto &entry : fs::directory_iterator(path_to_directory)){
		if(!entry.is_directory()){
			++count;
			std::cout<<count<<". "<<entry.path().filename().string()<<std::endl;	//type of entry 'should' (check in linux, the return type) be of type directory_entry
												//check what these path(), filename(), string() return (in Linux)
		}
	}
	num_SavedTimetables = count;
*/}

void a_register::set_num_SavedTimetables(){
/*	#if __cplusplus >= 201402
		std::filesystem;
	#else
		boost::filesystem;
	#endif
*/
/*	num_SavedTimetables = 0;
	string path_to_tables_dir = "./tables";
	for(const auto &entry : std::filesystem::directory_iterator(path_to_tables_dir)){
		if(!entry.is_directory()){
			++num_SavedTimetables;
		}
	}
*/}

void a_register::newWelcome(){
	
	if(setup_complete)
		return;

	string icommand;
	#ifdef __linux__
		system("clear");
	#else
		system("cls");
	#endif

	set_h_w();

	prt_t_header();
	
	int i;
	string msg = "Hello", name = "Kaun?";
	if( terminal_width >( 25 - 1*1 + 50 + 2 ))	//5*5 for "Hello", and 10*4 for "Kaun ?"
    	for(i=0;i<(terminal_height/2 - 9);i++) std::cout<<'\n';	//-9 = -1 for height of header (time), and -8 for greeting
  	else
  		for(i=0;i<(terminal_height/2 - 5);i++) std::cout<<'\n';	//-9 = -1 for height of header (time), and -8 for greeting

	magnify("mid",&msg,&name);	//+6 for 1 space... since, space took 4columns, while if it had been a character, it would have taken 10

	string icommand;
	#ifdef __linux__
		system("clear");
	#else
		system("cls");
	#endif

	string welcome_msg;
	welcome_msg = "Welcome to the attendance register, first enter/chose the timetable :-)";

	if(terminal_width<115){
		std::cout<<'\n';
	}
	else std::cout<<"\n\n";
	if(terminal_width > 71){
		for(i=0;i<(terminal_width/2 - 3 - 35); i++) std::cout<<' ';
		std::cout<<welcome_msg;
	}
	else{
		int i = welcome_msg.size()/terminal_width;
		while(i--){
			int j = terminal_width;
			while(j--)	std::cout<<welcome_msg[terminal_width-i];
			std::cout<<std::endl;
		}

		i = terminal_width * int(welcome_msg.size()/terminal_width);
		for(int j=0; j<(welcome_msg.size() - i)/2;)	std::cout<<' ';
		while(i++ < welcome_msg.size())
			std::cout<<welcome_msg[i];
	}
	set_num_SavedTimetables();
	if(num_SavedTimetables == 0){
		std::cout<<"No saved timetables found! Press any key to proceed to filling the timetable...  ";
		char ignoreChar;
		std::cin>>std::noskipws>>ignoreChar;
		table.fill();
		set_total_today_array();


	}
	else{
		std::cout<<"Press any key to proceed to Timetable Selection, or Entering it...  ";
		char ignoreChar;
		std::cin>>std::noskipws>>ignoreChar;
	}

	//After completion
	setup_complete = true;
}

void a_register::ensure_InitStatus(){
	RECOVERconfig();
	if(table.isFilled() == false){
		newWelcome();
	}
}

void a_register::parseStringScreen(){
	string icommand;
	bool alreadyParsed = false;

	#ifdef __linux__
		system("clear");
	#else
		system("cls");
	#endif

	set_h_w();
	
	int i;
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
			return;
		else if( icommand == ":test" ){	//USER can get to test mode from here also, other than editing the sourcecode to change the macro 'testMode'
				testModeScreen();
				alreadyParsed = true;
		}
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
		if(!alreadyParsed){
			try{
				parseInput(icommand);
			}
			catch(char *s){
				std::cout<<s;
			}
		}
		else{
			return;
		}
	/*ONLY AFTER SUCCESS of ParseInput()*/
//		vibrate("Records Updated!");
		std::cout<<"\nPress any key to continue...  ";
		std::cout<<std::endl;
		char ignoreChar;
		std::cin>>std::noskipws>>ignoreChar;
	}
}

int main(int argc, char const *argv[]){

	std::ios_base::sync_with_stdio(false);	//disables sync between C and C++ standard streams

	int i;
	string icommand;

	/*Before this line itself, the debugger shows us that there are 3 threads
	[New Thread 7008.0x1db0]
	[New Thread 7008.0xcdc]
	[New Thread 7008.0x1010]

	And after i chose exit in the timetable::mainmenu() in the 1st run of that function itself, it shows these :
	[New Thread 7008.0x1c48]
	[New Thread 7008.0x25e0]
	[New Thread 7008.0x114c]
	[New Thread 7008.0x500]
	[New Thread 7008.0x145c]
	[Inferior 1(process 7008) exited normally]

	//QUESTION - But what does this mean anyway? Is it multi-threading ?
	*/
	#ifdef __linux__
		system("clear");
	#else
		system("cls");
	#endif

	set_h_w();
	
	a_register all_records;

	if(testMode == true){
		all_records.testModeScreen();
		return 0;
	}

	all_records.RECOVERconfig();
	all_records.ensure_InitStatus();

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
		else if( icommand == ":test" ){
				all_records.testModeScreen();
		}
	}
	else {
		try{
			all_records.parseInput(icommand);
		}
		catch(char *s){
			std::cout<<s;
		}
		std::cout<<"\nPress any key to continue...  ";
		std::cout<<std::endl;
		char ignoreChar;
		std::cin>>std::noskipws>>ignoreChar;
	}
	return 0;
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
				else if((*big_str)[k] == '?')	std::cout<<bigChar[26][i];
            	else std::cout<<bigChar[(int)((*big_str)[k])-65][i];
            	std::cout<<" ";
        	}
        	std::cout<<'\n';   
    	}

    	for(i=4;i<8;i++){
        	for(j=0;j<spac;j++) std::cout<<" ";
        	for(k=0;k<small_str->size();k++){
            	if((*small_str)[k]==' ') std::cout<<' ';
				else if((*small_str)[k] == '?')	std::cout<<smallChar[26][i];
            	else std::cout<<smallChar[(int)((*small_str)[k])-65][i-4];
            	std::cout<<' ';
        	}
        	std::cout<<"   ";
        	for(k=0;k<big_str->size();k++){
            	if((*big_str)[k]==' ') std::cout<<"   ";
				else if((*big_str)[k] == '?')	std::cout<<bigChar[26][i];
            	else std::cout<<bigChar[(int)((*big_str)[k])-65][i];
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
				else if((*small_str)[k] == '?')	std::cout<<smallChar[26][i];
            	else std::cout<<smallChar[(int)((*small_str)[k])-65][i];
            	std::cout<<' ';
        	}
        	std::cout<<"   ";
        	for(k=0;k<big_str->size();k++){
            	if((*big_str)[k]==' ') std::cout<<"   ";
				else if((*big_str)[k] == '?')	std::cout<<smallChar[26][i];
            	else std::cout<<smallChar[(int)((*big_str)[k])-65][i];
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
			else if((*big_str)[k] == '?')	std::cout<<bigChar[26][i];
        	else std::cout<<bigChar[(int)((*big_str)[k])-65][i];
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
			else if((*small_str)[k] == '?')	std::cout<<smallChar[26][i];
	    	else std::cout<<smallChar[(int)((*small_str)[k])-65][i];
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

/*			#ifdef __linux__
				system("clear");
			#else
				system("cls");
			#endif
*/
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
			
			#ifdef __linux__
				usleep(300000);
			#else
				Sleep(300000);
			#endif

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
			daylist new_day;
			int i=ndays;
			while(i--){
				days.emplace_back(new_day);
			}
			total_courses=0;
			string dayname;
			for(int i=0;i<ndays;i++){
				switch(i){
					case 0: dayname = "Monday"; break;
					case 1: dayname = "Tuesday"; break;
					case 2: dayname = "Wednesday"; break;
					case 3: dayname = "Thursday"; break;
					case 4: dayname = "Friday"; break;
					case 5: dayname = "Saturday"; break;
					case 6: dayname = "Sunday"; break;
				}
				days[i].set_Day(dayname);
			}
			save_TTFile = "BinaryTimeTable.dat";
			txtfile = "TimeTable.txt";
}

timetable::~timetable(){
	for(int i=0; i<ndays; i++)
		days[i].~daylist();
}

int timetable::mainmenu(bool mainmenu_retval){
	if(!mainmenu_retval){
		return 0;
	}

	refresh_time();

	int i=0;
	positive ch;
	do{
		#ifdef __linux__
			system("clear");
		#else
			system("cls");
		#endif

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
		if(ch == 0){	//NOTE - Protection from user entering a string, character etc, instead of integer, the value given to the integer is 0
			ch = 10;
		}
	}while(ch>7);
	switch(ch){
		case 1: fill(); break;
		case 2: load_from_binary(); break;
		case 3: save_to_binary(); break;
		case 4: display();
				return 0; break;	//return 0, since both of these give option to go back to mainmenu()
		case 5: saveTXT();
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

		#ifdef __linux__
			system("clear");
		#else
			system("cls");
		#endif
		
		std::cout<<"\nSETTINGS\n---------\n"
		    <<"\n1. Change name of save_file"
		    <<"\n2. Change name of save_txtfile"
		    <<"\n3. Change number of days to store"
		    <<"\n4. Change department/group name"
		    <<"\n5. Go to Main Menu"
		    <<"\nWhat do you want to (1-5)? ";
		std::cin>>ch;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max() , '\n');
		std::cout<<"\n\n";
		switch(ch){
			case 1: std::cout<<"Enter name of save_file : \n";
				getline (std::cin, save_TTFile);
				std::cout<<"DONE!";
				break;
			case 2: std::cout<<"Enter name of txt_file:\n";
				getline (std::cin, txtfile);
				std::cout<<"DONE!";
				break;
			case 3: std::cout<<"Enter Number of Days to store in Timetable : ";
				std::cin>>ndays;
				std::cout<<"DONE!";
				break;
			case 4: std::cout<<"Department : \nCurrent - "<<dept<<"\nNew - ";
				getline (std::cin, dept);
				std::cout<<"\nGroup : ";
				getline (std::cin, grp);
				std::cout<<"DONE!";
				break;
			case 5: mainmenu();
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
		days[i].make_tlist();
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
			if(days[i].tpoints[j] == NULL) continue;
			const string sptr = days[i].tpoints[j]->get_coursecode();
			if(find( distinct_courses.begin(), distinct_courses.end(), sptr ) == distinct_courses.end()){	//will be true if not found
				distinct_courses.push_back(sptr);
				++total_courses;
			}
		}
	}
}

void timetable::display(){
	refresh_time();

	int box_length, maxStrLen = 0;
	int i, j;

	#ifdef __linux__
		system("clear")
	#else
		system("cls");
	#endif

	prt_t_header();
	std::cout<<"\n\n";

	if( days.size() == 0){
		set_h_w();

		std::cout<<' ';
		for(i=0; i<terminal_width-2; ++i)	std::cout<<'-';

		std::cout<<'|';
		for(i=0; i<(terminal_width - 5)/2; ++i)	std::cout<<' ';
		std::cout<<"EMPTY";
		for(i=0; i<terminal_width - (terminal_width - 5)/2; ++i)	std::cout<<' ';
		std::cout<<'|';

		for(i=0; i<terminal_width-2; ++i)	std::cout<<'-';
	}

	else{	//This block prints the table
		for(i=0; i<ndays; i++){
			if( ret_day(i)->getmaxCCLen() > maxStrLen ){
				maxStrLen = ret_day(i)->getmaxCCLen();
			}
		}

		box_length = 2*(int)ret_day(0)->class_length + maxStrLen + 2*int(maxStrLen/3) + 1;

		for(i=0; i<(14 + (int)((ret_day(0)->recess_start - ret_day(0)->class_start)/ret_day(0)->class_length)*box_length + 11 + (int)((ret_day(0)->class_end - ret_day(0)->recess_end)/ret_day(0)->class_length)*box_length + 1); ++i){
			std::cout<<'\\';			
		}
		std::cout<<std::endl;
		for(i=0; i<(14 + (int)((ret_day(0)->recess_start - ret_day(0)->class_start)/ret_day(0)->class_length)*box_length + 11 + (int)((ret_day(0)->class_end - ret_day(0)->recess_end)/ret_day(0)->class_length)*box_length + 1); ++i){
			std::cout<<'\\';			
		}
		std::cout<<std::endl;

		//1st line
		std::cout<<"||    Day    |";
		float tmp_time = ret_day(0)->class_start;
		//for time before recess
		for(i=0; i<(ret_day(0)->recess_start - ret_day(0)->class_start)/ret_day(0)->class_length; ++i){
			std::cout<<int(tmp_time)<<':';	if(int((fmod(tmp_time,1)*60))>9)	std::cout<<int((fmod(tmp_time,1)*60));
										else	std::cout<<'0'<<int((fmod(tmp_time,1)*60));
			for(j=0; j<(box_length - 6); ++j)	std::cout<<' ';
			if(int(tmp_time)<10)	std::cout<<" |";
			else
			{
				std::cout<<'|';
			}
			tmp_time += ret_day(0)->class_length;
		}

		//recess_block
		std::cout<<int(ret_day(0)->recess_start)<<':';	if(int(fmod(ret_day(0)->recess_start, 1)*60) > 9)	std::cout<<int(fmod(ret_day(0)->recess_start, 1)*60);
													else
													{
														std::cout<<'0'<<int(fmod(ret_day(0)->recess_start, 1)*60);
													}
		for(j=0; j<5; ++j)	std::cout<<' ';
		if(int(ret_day(0)->recess_start)<10)	std::cout<<' ';
		std::cout<<'|';

		//for time after recess
		tmp_time = ret_day(0)->recess_end;
		for(i=0; i<(ret_day(0)->class_end - ret_day(0)->recess_end)/ret_day(0)->class_length; ++i){
			std::cout<<int(tmp_time)<<':';	if(int((fmod(tmp_time,1)*60))>9)	std::cout<<int((fmod(tmp_time,1)*60));
										else	std::cout<<'0'<<int((fmod(tmp_time,1)*60));
			for(j=0; j<(box_length - 6); ++j)	std::cout<<' ';
			if(int(tmp_time)<10)	std::cout<<" |";
			else
			{
				std::cout<<'|';
			}
			tmp_time += ret_day(0)->class_length;
		}
		std::cout<<'|'<<std::endl;

		/*2nd Line*/
		std::cout<<"||           |";
		tmp_time = ret_day(0)->class_start + ret_day(0)->class_length;
		//for time before recess
		for(i=0; i<(ret_day(0)->recess_start - ret_day(0)->class_start)/ret_day(0)->class_length; ++i){
			if(int(tmp_time)<10)	std::cout<<' ';
			for(j=0; j<(box_length - 6); ++j)	std::cout<<' ';
			std::cout<<int(tmp_time)<<':';	if(int((fmod(tmp_time,1)*60))>9)	std::cout<<int((fmod(tmp_time,1)*60));
										else	std::cout<<'0'<<int((fmod(tmp_time,1)*60));
			std::cout<<'|';
			tmp_time += ret_day(0)->class_length;
		}

		//recess_block
		if(int(ret_day(0)->recess_end)<10)	std::cout<<' ';
		for(j=0; j<5; ++j)	std::cout<<' ';
		std::cout<<int(ret_day(0)->recess_end)<<':';	if(int(fmod(ret_day(0)->recess_end, 1)*60) > 9)	std::cout<<int(fmod(ret_day(0)->recess_end, 1)*60);
													else
													{
														std::cout<<'0'<<int(fmod(ret_day(0)->recess_end, 1)*60);
													}
		std::cout<<'|';

		//for time after recess
		tmp_time = ret_day(0)->recess_end + ret_day(0)->class_length;
		for(i=0; i<(ret_day(0)->class_end - ret_day(0)->recess_end)/ret_day(0)->class_length; ++i){
			if(int(tmp_time)<10)	std::cout<<' ';
			for(j=0; j<(box_length - 6); ++j)	std::cout<<' ';
			std::cout<<int(tmp_time)<<':';	if(int((fmod(tmp_time,1)*60))>9)	std::cout<<int((fmod(tmp_time,1)*60));
										else	std::cout<<'0'<<int((fmod(tmp_time,1)*60));
			std::cout<<'|';
			tmp_time += ret_day(0)->class_length;
		}
		std::cout<<'|'<<std::endl<<"||";
		for(i=0; i<(14 + (int)((ret_day(0)->recess_start - ret_day(0)->class_start)/ret_day(0)->class_length)*box_length + 11 + (int)((ret_day(0)->class_end - ret_day(0)->recess_end)/ret_day(0)->class_length)*box_length - 3); ++i){
			std::cout<<'-';			
		}
		std::cout<<"||"<<std::endl;
		
		/*Setting value of recess, and calling set_tpoints*/	//NOTE_NOT_NEEDED - Calling set_tpoints() may not be needed here
		vector<string> v;
		v.reserve(6);
		if( days.size() == 5 ){
			v.push_back("B");
			v.push_back("R");
			v.push_back("E");
			v.push_back("A");
			v.push_back("K");

			for(i=0; i<5; ++i){
				ret_day(i)->set_tpoints();
				ret_day(i)->tpoints[(ret_day(i)->recess_start - ret_day(i)->class_start)/ret_day(i)->class_length]->change_coursecode(v[i]);
			}
		}
		else if( days.size() == 6){
			v.clear();
			v.push_back("R");
			v.push_back("E");
			v.push_back("C");
			v.push_back("E");
			v.push_back("S");
			v.push_back("S");

			for(i=0; i<6; ++i){
				ret_day(i)->set_tpoints();
				ret_day(i)->tpoints[(ret_day(i)->recess_start - ret_day(i)->class_start)/ret_day(i)->class_length]->change_coursecode(v[i]);
			}

		}
		else{
			for(i=0; i<days.size(); ++i){
				ret_day(i)->set_tpoints();
				ret_day(i)->tpoints[(ret_day(i)->recess_start - ret_day(i)->class_start)/ret_day(i)->class_length]->change_coursecode("-");
			}
		}

		for(i=0; i<days.size(); ++i){	//Now printing daywise	[It is too much short :-)]
			std::cout<<"||";
			std::cout<<days[i].get_Day();
			for(j=0; j<(11 - days[i].get_Day().size()); ++j)	std::cout<<' ';
			std::cout<<'|';

			//The courses
			for(timebox* box : days[i].tpoints){
				if(box->box_type == true){
					for(j=0; j<(box_length - box->get_coursecode().size() - 1)/2; ++j)	std::cout<<' ';
					std::cout<<box->get_coursecode();
					for(j=0; j<(box_length - box->get_coursecode().size() - 1) - (box_length - box->get_coursecode().size() - 1)/2; ++j)	std::cout<<' ';
					std::cout<<'|';
				}
				else{
					std::cout<<"     "<<box->get_coursecode()<<"    |";
				}
			}
			std::cout<<'|'<<std::endl<<"||           |";
			for(j=0; j<(ret_day(0)->recess_start - ret_day(0)->class_start)/ret_day(0)->class_length; ++j){
				int k=0;
				for(k=0; k<box_length-1; ++k)	std::cout<<' ';
				std::cout<<'|';
			}

			std::cout<<"          |";

			for(j=0; j<(ret_day(0)->class_end - ret_day(0)->recess_end)/ret_day(0)->class_length; ++j){
				int k=0;
				for(k=0; k<box_length-1; ++k)	std::cout<<' ';
				std::cout<<'|';
			}
			std::cout<<'|'<<std::endl;			
		}		

		for(i=0; i<(14 + (int)((ret_day(0)->recess_start - ret_day(0)->class_start)/ret_day(0)->class_length)*box_length + 11 + (int)((ret_day(0)->class_end - ret_day(0)->recess_end)/ret_day(0)->class_length)*box_length + 1); ++i){
			std::cout<<'\\';			
		}
		std::cout<<std::endl;
		for(i=0; i<(14 + (int)((ret_day(0)->recess_start - ret_day(0)->class_start)/ret_day(0)->class_length)*box_length + 11 + (int)((ret_day(0)->class_end - ret_day(0)->recess_end)/ret_day(0)->class_length)*box_length + 1); ++i){
			std::cout<<'\\';			
		}
		std::cout<<std::endl;

	}

	std::cout<<"\n\nTimeTable Printed!!\n\n";

	char ignoreChar;
	if( testMode == true ){
		std::cout<<"Press 'Enter' to continue to the parseStringScreen... ";
		std::cin>>std::noskipws>>ignoreChar;
		return;
	}
	else{
		int choice;
		do{
			std::cout<<"\nWhat Next?\n1. Save to text file\n2. Go back to Main Menu\n";
			std::cin>>choice;
		}while(choice !=1 && choice != 2);

		if(choice == 1){
			saveTXT();
			std::cout<<"Saved to "<<txtfile;
		}
		else{
			mainmenu();
		}
	}
}

//void timetable::display(){	//WHOLLY REVAMPED DISPLAY() Function... from Scratch!!
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

/*	refresh_time();
	
	#ifdef __linux__
		system("clear");
	#else
		system("cls");
	#endif

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

	for( i=0 ; i<ndays ;i++ )	//for block prints shedule of a compelete day
	{	
		std::cout<<"||";
		switch(i){			//switch block  prints the day name
			case 0: std::cout<<"Monday     "; break;
			case 1: std::cout<<"Tuesday    "; break;
			case 2: std::cout<<"Wednesdayas"; break;
			case 3: std::cout<<"Thursday   "; break;
			case 4: std::cout<<"Friday     "; break;
			case 5: std::cout<<"Saturday   "; break;
		}
		std::cout<<'|';
		int len=0;
		for( j=0 ; j<4 ; ++j ){	//first half
			if( ret_day(i)->tpoints[j] != NULL ){
//				len = d[i].tpoints[j]->get_coursecode()->size();	//Display CourseCode
				len = ret_day(i)->tpoints[j]->get_coursecode().size();
				for( k=0 ; k < 5 -len/2 ; ++k ) std::cout<<' ';
//				std::cout<<*(d[i].tpoints[j]->get_coursecode());
				std::cout<<ret_day(i)->tpoints[j]->get_coursecode();
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
			case 5 : std::cout<<' '; break;
		}
		std::cout<<"    |";
		for( j=5 ; j<9 ; ++j ){	//Changed limits after making the tpoints to have the recess box also
			if( ret_day(i)->tpoints[j] != NULL ){
//				len = d[i].tpoints[j]->get_coursecode().size();	//Display CourseCode
				len = ret_day(i)->tpoints[j]->get_coursecode().size();
				for( k=0 ; k < 5 -len/2 ; ++k ) std::cout<<' ';
//				std::cout<<d[i].tpoints[j]->get_coursecode();
				std::cout<<ret_day(i)->tpoints[j]->get_coursecode();
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

	if(testMode == true){
		return;
	}

	do{
		std::cout<<"\nWhat Next?\n1. Save to text file\n2. Go back to main menu\n";
		std::cin>>ch;
		if(ch == 0){	//NOTE - Protection from user entering a string, character etc, instead of integer, the value given to the integer is 0
			ch = 10;
		}
	}while(ch!=1 && ch!=2);

	if(ch==1)	saveTXT();
	else{	//This will surely be ch=2... since all other numbers have been managed by do-while loop
		mainmenu();
	}
	//To Continue the chain reaction that ends up closing mainmenu() whenever it returns false;
}	//End of Display Function
*/
void timetable::save_to_binary(){
	std::ofstream fsave;
	fsave.open( save_TTFile , std::ios::binary|std::ios::out);
	fsave.write((char*)&state,sizeof(state));	//state is lesser bytes than char, but the &state and char* will be same size, and for the bytes saved in file, it will save 1 byte, due to that sizeof()	
	fsave.write((char*)&ndays,sizeof(ndays));
	size_t len = save_TTFile.size() +1;
	fsave.write((char*)&len,sizeof(len));
	fsave.write(save_TTFile.c_str(),len*sizeof(char));
	len = txtfile.size() +1;
	fsave.write((char*)&len,sizeof(len));
	fsave.write(txtfile.c_str(),len*sizeof(char));
	len = dept.size() +1;
	fsave.write((char*)&(len),sizeof(len));
	fsave.write(dept.c_str(),len*sizeof(char));
	len = grp.size() +1;
	fsave.write((char*)&len,sizeof(len));
	fsave.write(grp.c_str(),len*sizeof(char));
	fsave.write((char*)&total_courses,sizeof(total_courses));
	for(int i=0;i<ndays;++i)
		days[i].save_to_binary(&fsave);
	std::cout<<"End of timetable save!\n";
	fsave.close();
}

void timetable::load_from_binary(){
	std::ifstream f_recall;

	if( save_TTFile == "" )
		return;

	f_recall.open( save_TTFile ,std::ios::binary|std::ios::in);
	f_recall.read((char*)&state, sizeof(state));
	f_recall.read((char*)&ndays,sizeof(ndays));
	//instead of auto, replastd::cing with size_t
	char *cstr;	//This is just a pointer to a random block of 1 byte (but for now, even that block isn't reserved)
	size_t len;	//May Cause a Bug, since when saving, it used 'auto' to determine the type
	f_recall.read((char*)&len,sizeof(len));	//len was random here... as big as hell, and also 0
	cstr = new char[len];
	f_recall.read(cstr,len*sizeof(char));	//it couldn't read cstr
	save_TTFile = cstr;
	delete[] cstr;
	f_recall.read((char*)&len,sizeof(len));
	cstr = new char[len];
	f_recall.read(cstr,len*sizeof(char));
	txtfile = cstr;
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
		days[i].load_from_binary(&f_recall);
	std::cout<<"End of timetable LOAD!\n";
	f_recall.close();

	state = true;
}

void timetable::saveTXT(){
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
				len = ret_day(i)->tpoints[j]->get_coursecode().size();
				for( k=0 ; k < 5 -len/2 ; ++k ) fout<<' ';
//				fout<<*(d[i].tpoints[j]->get_coursecode());
				fout<<ret_day(i)->tpoints[j]->get_coursecode();
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
//				len = d[i].tpoints[j]->get_coursecode().size();	//Display CourseCode
				len = ret_day(i)->tpoints[j]->get_coursecode().size();
				for( k=0 ; k < 5 -len/2 ; ++k ) fout<<' ';
//				fout<<d[i].tpoints[j]->get_coursecode();
				fout<<ret_day(i)->tpoints[j]->get_coursecode();
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

vector<vector<string>> timetable::contoarray(){	//Returning 2D array... MAY FAIL
	vector<vector<string>> retarr;	//UPDATE_NOTE - This is basically a ndays*8 2D matrix, which may not always be the case
	retarr.reserve(ndays);	//IMPORTANT - DON'T FORGET TO DELETE
	for (int i = 0; i < ndays; i++)
	{
		retarr[i].reserve(8);
	}
	
	for(int i=0;i<ndays;i++)
		for(int j=0;j<8;j++){
            if(days[i].tpoints[j])
			    retarr[i][j]=days[i].tpoints[j]->get_coursecode();
            else retarr[i][j]="NULL"; }
	return retarr;
}

daylist* timetable::ret_day(int dayn){
	if ( dayn < 0 || dayn >= ndays){
		
		//My error handling... since if NULL is returned, and accessed it may cause Segmentation Fault
		std::cout<<"Invalid Input Passed... Destructing Nodes, to prevent memory leak...";
		for(int i=0; i<ndays; i++)
			days[i].~daylist();
		std::cout<<"Exiting...";
		//~timetable();		//Couldn't Call Destructor... no match for 'operator~'
		delete this;
		exit(0);
		//All destructed... seems safe, but IMPROVE IT (maybe using try, throw and catch)
		return NULL;
	}
	else return &days[dayn];
}

daylist::daylist(){
	numBox = 0;
	class_start = 8.5;
	class_end = 17.5;
	recess_start = 12.5;
	recess_end = 13.5;
	class_length = 1;
}

daylist::~daylist(){
				//IMP - In these destructors, remember to use 'delete' data allocated using 'new'
}

timebox::timebox(){

//	next=NULL;
//	prev=NULL;
//	recbox = NULL;
	box_type = true;
	coursecode = "NULL";
}

/*const */string timebox::get_coursecode() const{
	return coursecode;
}

void timebox::change_coursecode(string sptr){
	coursecode = sptr;
}

void timebox::change_coursecode(const char* sptr){
	coursecode = *sptr;
}

void timebox::set_sub(){
	int i=0;
	while(i<coursecode.size()){
		if((coursecode[i] >= 65 && coursecode[i] <= 90)||(coursecode[i] >= 97 && coursecode[i] <= 122))
			break;
		else sub.push_back(coursecode[i]);
		++i;
	}
}

void daylist::set_tpoints(){	//NOTE - only used by display function, else no hinderance to supporting CUSTOM Boxes, BUT it does change class_end and recess_start
//	int org_recess_start = recess_start, org_class_end = class_end ;

	tpoints.clear();

	if(ceil((recess_start - class_start)/class_length) != int((recess_start - class_start)/class_length)){
		recess_start -= fmod(recess_start - class_start,class_length);
	}
	if(ceil((class_end - recess_end)/class_length) != int((class_end - recess_end)/class_length)){
		class_end -= fmod(class_end - recess_end,class_length);
	}
	int class_boxes = int((recess_start - class_start)/class_length) + 1 + int((class_end - recess_end)/class_length);
	
	int i=0, j=0, k=0;
	timebox *box_ptr = NULL;
	for (i = 0; i < class_boxes; i++)
	{
		tpoints.push_back(box_ptr);
	}
	for (i = 0; i < timelist.size(); i++)
	{
		j=0;
		if(timelist[i].starttime < recess_start ){	//due to the way they are assigned, endtime will also be <= recess_start
			j=(timelist[i].endtime - timelist[i].starttime)/class_length;
			for(k=0; k<j; ++k)
				tpoints[int((timelist[i].starttime - class_start)/class_length) + k] = &timelist[i];
		}
		else{
			//after recess
			j = (timelist[i].endtime - timelist[i].starttime)/class_length;
			for(k=0; k<j; ++k){
				tpoints[int((timelist[i].starttime - recess_end + recess_start - class_start)/class_length) + k + 1] = &timelist[i];	//[DEBUG] Check if the '+1' I added is consistent with other cases too, like length 2 hours etc???
				if(tpoints.size() < int((timelist[i].starttime - recess_end + recess_start - class_start)/class_length) + k){
					std::cout<<"Size is smaller";
					std::cout<<std::endl;
				}
			}
		}
	}
}

void daylist::make_tlist(){
	int i=class_start;
	bool tbox_extend_flag;
	string s;
    short mins_start, mins_end;
    bool am_pm_start, am_pm_end;
	for(i=class_start;i<class_end;i+=class_length){
		if( i+class_length < recess_start){
			mins_start = (i/10)*6/10;	mins_end = ((i+class_length)/10)*6/10;
			am_pm_start = i<12 ? true:false;	am_pm_end = (i+class_length<12) ? true:false;
			std::cout<<'\t'<<int(i)<<":"<<mins_start;
			am_pm_start ? std::cout<<"am" : std::cout<<"pm" ;
			std::cout<<'-'<<int(i+class_length)<<":"<<mins_end;
			am_pm_end ? std::cout<<"am" : std::cout<<"pm" ;
			std::cout<<' ';
			if( int(i + class_length) < 10 ) std::cout<<"  ";
			else if ( int(i + class_length) >= 10 ) std::cout<<' ';
			std::cout<<"- ";
		}
		else{
			timebox recess_box;
			recess_box.box_type = false;
			timelist.push_back(recess_box);

			i = recess_end;
			continue;
		}

		getline ( std::cin, s );
		if( s == "" ){	//in case there's an empty box (a gap), we can't simply increase endtime, by a simple 1, nor 2 nor others
			continue;
		}
		else{	if ( s == "y" || s=="Y" ){
					if(timelist.size() == 0)	continue;
					if(timelist.back().endtime + class_length > recess_start && timelist.back().starttime < recess_start){
							i = recess_end;	//this will create a void in between sometimes, and is deliberate, for eg. class till 11:00 then recess from 12:00 and 13:00, then 11 to 12 is void, since class_length is 2
							timebox new_box;
							new_box.change_coursecode(timelist.back().get_coursecode());
							new_box.starttime = i;
							new_box.endtime = i + class_length;
							new_box.set_sub();				
							timelist.push_back(new_box);
					}
					else{
							timelist.back().endtime += class_length;
					}
				}
				else{
					timebox new_box;
					new_box.change_coursecode(s);
					new_box.starttime = i;
					new_box.endtime = i + class_length;
					new_box.set_sub();				
					timelist.push_back(new_box);
				}
		}
	}
	numBox = timelist.size();
	set_tpoints();
}

void daylist::set_Testmode_tlist(){
	timelist.clear();
	float i=class_start;
	bool tbox_extend_flag;
	string s;
    short mins_start, mins_end;
    bool am_pm_start, am_pm_end;
	for(i=class_start;i<class_end;i+=class_length){
		if( (i+class_length > recess_start) && (i+class_length <= recess_end) ){
			timebox recess_box;
			recess_box.box_type = false;
			recess_box.starttime = recess_start;
			recess_box.endtime = recess_end;
			recess_box.change_coursecode("---");
			timelist.push_back(recess_box);

			i = recess_end - class_length;
			continue;
		}
		else{
			int j;
			string s;

			s = "CS2401";
/*			refresh_time();
			j = (time_now.tm_sec)%26;
			s.push_back(65 + j);
			for(j=0; j<4; ++j){
				refresh_time();
				j = (time_now.tm_sec)%26;
				s.push_back(97 + j);
			}
*/			
			timebox new_box;
			new_box.change_coursecode(s);
			new_box.starttime = i;
			new_box.endtime = i + class_length;
			new_box.set_sub();				
			timelist.push_back(new_box);
		}
	}
	numBox = timelist.size();
	set_tpoints();
}

void daylist::save_to_binary(std::ofstream* fsave){
	size_t len = day.size() + 1;
	fsave->write((char*)&len,sizeof(len));
	fsave->write(day.c_str(),(len*sizeof(char)));	
	fsave->write((char*)&class_start, sizeof(class_start));
	fsave->write((char*)&class_end, sizeof(class_end));
	fsave->write((char*)&class_length, sizeof(class_length));
	fsave->write((char*)&recess_start, sizeof(recess_start));
	fsave->write((char*)&recess_end, sizeof(recess_end));
	for(int i=0;i<timelist.size();i++){	//while(temp != NULL)
		bool box_type;
		len = timelist[i].get_coursecode().size() + 1;
		fsave->write((char*)&len,sizeof(len));	//Actually sizeof() returns auto, which is 8bytes, but still...
		fsave->write(timelist[i].get_coursecode().c_str(),len*sizeof(char));
			//No need to save sub, that will be autoset by set_sub()
		fsave->write((char*)&timelist[i].box_type,sizeof(box_type));
		fsave->write((char*)&timelist[i].starttime,sizeof(timelist[i].starttime));
		fsave->write((char*)&timelist[i].endtime,sizeof(timelist[i].endtime));
	}
}

void daylist::load_from_binary(std::ifstream* f_recall){
	reset_records();

	size_t len = 0;
	char *cstr;
	f_recall->read((char*)&len,sizeof(len));
	cstr = new char[len];
	f_recall->read(cstr,len*sizeof(char));	
	day = cstr;
	delete[] cstr;
	f_recall->read((char*)&class_start, sizeof(class_start));
	f_recall->read((char*)&class_end, sizeof(class_end));
	f_recall->read((char*)&class_length, sizeof(class_length));
	f_recall->read((char*)&recess_start, sizeof(recess_start));
	f_recall->read((char*)&recess_end, sizeof(recess_end));
	for(int i=0;i<timelist.size();i++){	//while(temp != NULL)
		timebox new_box;
		float st_end_time;
		bool box_type;
		len = 0;
		f_recall->read((char*)&len,sizeof(len));	//Actually sizeof() returns auto, which is 8bytes, but still...
		cstr = new char[len];
		f_recall->read(cstr,len*sizeof(char));
		new_box.change_coursecode(cstr);
		f_recall->read((char*)&st_end_time,sizeof(st_end_time));
		new_box.starttime = st_end_time;
		f_recall->read((char*)&st_end_time,sizeof(st_end_time));
		new_box.endtime = st_end_time;
		f_recall->read((char*)&box_type, sizeof(box_type));
		new_box.box_type = box_type;
		
		new_box.set_sub();

		timelist.push_back(new_box);
	}

	numBox = timelist.size();
	set_tpoints();
}

void daylist::set_Day(string daystr){
	day = daystr;
}

void a_register::parseInput(string parseString){
	set_total_today_array();
	if(parseString.size() > todaylist.size()){	//to ignore additional characters
		parseString.erase(todaylist.size(), parseString.size() -1);
	}
	for(int i=0; i<parseString.size(); ++i){
		if(parseString[i] == 'y' || parseString[i] == 'Y' || parseString[i] == '1' )
			++(todaylist[i]->npresent);
		else if(parseString[i] == 'n' || parseString[i] == 'N' || parseString[i] == '0' )
			++(todaylist[i]->nabsent);
		else if(parseString[i] == 'b' || parseString[i] == 'B' || parseString[i] == '2' ) 
			++(todaylist[i]->nbunk);
		else {
			std::cerr<<"\nWe couldn't interpret "<<parseString[i]<<"\nReverting all updates of today... Try Again :)";
			for(int j=i-1;j>=0;--j){
				if(parseString[j] == 'y' || parseString[j] == 'Y' || parseString[j] == '1' )
					--(todaylist[j]->npresent);
				else if(parseString[j] == 'n' || parseString[j] == 'N' || parseString[j] == '0' )
					--(todaylist[j]->nabsent);
				else --(todaylist[j]->nbunk);	//It can only be one among these 3
			}
		}
	}

}

void a_register::totaldisplay(){
	for(int i=0; i<records_list.size(); ++i){
		idisplay(records_list[i].get_coursecode());
	}
}

void a_register::idisplay(string display_cc){	//CourseCode

	int i=0;
	irecbox *display_rec_box = find_irecbox(display_cc);

	if(display_rec_box == NULL)	return;

	set_h_w();
	if(terminal_width > 12){
		i=12;
		while(i--)	std::cout<<'-';
		i=12;
		std::cout<<std::endl;
		while(i--)	std::cout<<'-';
	}
	else{
		i=terminal_width;
		while(i--)	std::cout<<'-';
		i=terminal_width;
		std::cout<<std::endl;
		while(i--)	std::cout<<'-';
	}
	std::cout<<std::endl;
	std::cout<<display_cc;
	std::cout<<std::endl;

	if(terminal_width > 12){
		i=12;
		while(i--)	std::cout<<'_';
	}
	else{
		i=terminal_width;
		while(i--)	std::cout<<'_';
	}
	std::cout<<std::endl;
	std::cout<<"Present -> "<<display_rec_box->npresent<<std::endl;
	std::cout<<"Absent -> "<<display_rec_box->nabsent<<std::endl;
	std::cout<<"Bunk -> "<<display_rec_box->nbunk<<std::endl<<std::endl;
}

bool a_register::already_present_in_todaylist(string query_str){
	for(int i=0; i<todaylist.size(); ++i){
		if(todaylist[i]->get_coursecode() == query_str)
			return true;
	}
	return false;
}

bool a_register::already_present_in_recordslist(string query_str){
	for(int i=0; i<records_list.size(); ++i){
		if(records_list[i].get_coursecode() == query_str)
			return true;
	}
	return false;
}


irecbox* a_register::find_irecbox(string search_str){
	for(int i=0; i<records_list.size(); ++i){
		if(records_list[i].get_coursecode() == search_str){
			return &records_list[i];
		}
	}
	return NULL;
}

void a_register::set_total_today_array(){

	daylist *the_day;
	int i=0, j=0;
	for(i=0; i<table.ndays; ++i){
		the_day = table.ret_day(i);
		for(j=0; j<the_day->tpoints.size(); ++j){
			if(the_day->tpoints[j] != NULL){
				if(the_day->tpoints[j]->box_type == false)
					continue;
				if( !already_present_in_recordslist( the_day->tpoints[j]->get_coursecode() )){	//ie. not found
					irecbox new_rec_box;
					new_rec_box.change_coursecode(the_day->tpoints[j]->get_coursecode());
					records_list.push_back(new_rec_box);
//					std::cout<<"[DEBUG]Size of Records_List - "<<records_list.size()<<std::endl;
				}
			}
		}
	}
	refresh_time();
	the_day = table.ret_day((time_now.tm_wday + 1)%6);	//It is days since Sunday (ie. 0-6), and i converted to days since Monday
	if(the_day == NULL){
		return;
	}
	else{
		for(j=0; j<the_day->tpoints.size(); ++j){
			if(the_day->tpoints[j] != NULL){
				if( the_day->tpoints[j]->box_type == false )
					continue;
				if( !already_present_in_todaylist( the_day->tpoints[j]->get_coursecode() )){
//					std::cout<<"[DEBUG]Reached inside for the coursecode - "<<the_day->tpoints[j]->get_coursecode()<<std::endl;
					irecbox *rec_box_ptr = NULL;
					rec_box_ptr = find_irecbox( the_day->tpoints[j]->get_coursecode());
					if(rec_box_ptr != NULL){
						todaylist.push_back(rec_box_ptr);
					}
					else{
//						std::cout<<"[DEBUG]rec_box is NULL for "<<the_day->tpoints[j]->get_coursecode()<<std::endl;
					}
				}
			}
		}
	}

}

a_register::a_register(){
	setup_complete = false;
	num_SavedTimetables = 0;
	last_savedRecords = "";
	last_savedTTFile = "";
	user_name = "Kaun";

	if(RECOVERconfig() == true){
		setup_complete = true;
	}
	else{
		newWelcome();
	}
}

a_register::~a_register(){
}

bool a_register::RECOVERconfig(){	//NOTE - It returns true if it finds a username, and a linked timetable, thats it!
									//		For the records file, it will try to find it, but if need be, will just create a new file, and use the methods of a_register
	//TRIAL
	return false;
}
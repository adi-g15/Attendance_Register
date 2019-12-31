# 29 "Records_with_TT.cpp"
/*Comments have been removed from this file, to see the actual code with 'all', see the other Records_TT.cpp 
And due to removing comments, their are many newlines
*/
#include <iostream>

#include <fstream>
# 45 "Records_with_TT.cpp"
#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>


#ifdef _WIN32
 #include <windows.h>
#elif __linux__
 #include <sys/ioctl.h>
 #include <unistd.h>

#elif __MINGW32__
 #include <windows.h>
#elif __CYGWIN__
 #include <windows.h>
#endif

using namespace std;

tm time_now;
string big[26][8]={{"---------","|  ---  |","|  | |  |","|  ---  |","|  | |  |","|  | |  |","|  | |  |","---- ----"},{"--------\\","|  ---  |","|  | |  |","|  ---  /","|  ---  \\","|  | |  |","|  ---  |","--------/"},{"--------\\","|       |","|  -----/","|  |     ","|  |     ","|  -----\\","|       |","--------/"},{"--------\\","|  ---\\ |","|  |  | |","|  |  | |","|  |  | |","|  |  | |","|  ---/ |","--------/"},{"---------","|       |","|  ------","|  --\\   ","|  --/   ","|  ------","|       |","---------"},{"---------","|       |","|  ------","|  |     ","|  ====  ","|  |     ","|  |     ","----     "},{"--------\\","|       |","|  -----/","|  |     ","|  \\=====","|    |  |","|    |  |","-----/  |"},{"---   ---","| |   | |","| |   | |","| ----- |","| ----- |","| |   | |","| |   | |","---   ---"},{"---------","|--- ---|","   | |   ","   | |   ","   | |   ","   | |   ","|--- ---|","---------"},{"---------","|--- ---|","   | |   ","   | |   ","   | |   ","   | |   ","/--- -   ","|----/   "},{"---   ---","| |  / / ","| | / /  ","| /  /   ","| \\  \\   ","| | \\ \\  ","| |  \\ \\ ","---   ---"},{"---      ","| |      ","| |      ","| |      ","| |      ","| |      ","|--- ---|","\\-------|"},{"---   ---","|  \\ /  |","|       |","|  \\ /  |","|  | |  |","|  | |  |","|  | |  |","---- ----"},{"---   ---","|\\\\   | |","| \\\\  | |","| |\\\\ | |","| | \\\\| |","| |  \\\\ |","| |   \\\\|","---   ---"},{"---------","| ----- |","| |   | |","| |   | |","| |   | |","| |   | |","| ----- |","---------"},{"---------","| ----- |","| |   | |","| -----/ ","| |      ","| |      ","| |      ","---      "},{"---------","| ----- |","| |   | |","| |   | |","| |   | |","| =======","| ======|","---------"},{"---------","| ----- |","| |   | |","| ----- /","| |\\  \\  ","| | \\  \\ ","| |  \\  \\","---   ---"},{"---------","| |      ","| |      "," \\ --- \\ ","      | |","      | |","|--- ---|","\\-------|"},{"---------","---| |---","   | |   ","   | |   ","   | |   ","   | |   ","   | |   ","   ---   "},{"---   ---","| |   | |","| |   | |","| |   | |","| |   | |","| |   | |","\\ ----- /"," ------- "},{"---   ---","| |   | |","| |   | |","| |   | |","| |   | |","\\ \\   / /"," \\  -  / ","  -----  "},{"--     --","||     ||","||     ||","||     ||","||     ||","\\\\  |  //"," \\\\/ \\// ","  -   -  "},{"--     --"," \\\\   // ","  \\\\ //  ","   \\ /   ","   / \\   ","  // \\\\  "," //   \\\\ ","--     --"},{"---   ---","\\ \\   / /"," \\ \\ / / ","  \\   /  ","   | |   ","   | |   ","   | |   ","   ---   "},{"---------","-------/ ","     //  ","    //   ","   //    ","  //     "," /-------","---------"}};
string small[26][4]={{"----","|  |","|--|","|  |"},{"----","|__|","|  |","----"},{"----","|   ","|   ","----"},{"---\\","|  |","|  |","---/"},{"----","|__ ","|   ","----"},{"----","|__ ","|   ","|   "},{"----","|   ","| -|","---|"},{"|  |","|__|","|  |","|  |"},{"----"," || "," || ","----"},{" ---","   |","   |","---/"},{"|  /","|/  ","|\\  ","|  \\"},{"|   ","|   ","|   ","----"},{"|  |","|\\/|","|  |","|  |"},{"|  |","|\\ |","| \\|","|  \\"},{"/--\\","|  |","|  |","\\--/"},{"/--\\","|__|","|   ","|   "},{"|--|","|  |","| \\|","|--\\"},{"/--\\","|__|","|\\  ","| \\ "},{"/--\\","|__","   |","\\--/"},{"----"," || "," || "," || "},{"|  |","|  |","|  |","|__|"},{"|  |","|  |","\\  /"," \\/ "},{"\\  /"," \\/ "," /\\ ","/  \\"},{"\\  /"," \\/ "," /\\ ","/  \\"},{"\\  /"," \\/ "," /  ","/   "},{"/---","  / "," /  ","---/"}};
string name = "Aditya Gupta";
int terminal_width = 169, terminal_height = 39;

typedef unsigned int positive;
# 89 "Records_with_TT.cpp"
void prt_t_header(void);
void greeting(string);
void refresh_time(void);

void magnify(string,string*,string*);
void capitallize(string*);
void clearscr(void);
void set_h_w(void);



void magnify(string, string*);
void smaller_magnify(string, string*);
int numspaces(string);
void vibrate(string);


struct strnode{
  string s;
  strnode* next= NULL ;
};

class string_list{
public:
 strnode *front, *rear;
 bool is_in_list(string);
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
  rear= newnode;
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


class timeboxn{
 string coursecode;

 public:
  string sub;
        float starttime,endtime;

     timeboxn *next,*prev;

     timeboxn();

        string* get_coursecode();
        void change_coursecode(string*);

        void change_coursecode(char*);

};

class daylist{



 string day;
 timeboxn *front,*rear;
 public:
     timeboxn *tpoints[8]={ NULL };
  int numbox;

  void set_tpoints();
  void make_tlist();
  void append_box(string*,int);
  timeboxn* traverseto(int);

  void load_from_binary(std::ifstream*);
  void save_to_binary(std::ofstream*);
  void set_Day(string);


  void update_box(int);
  daylist();
  ~daylist();
};

class timetable{
 bool state;
 string savefile,txtfile,recallfile;
 string dept,grp;
 daylist *day;
 public:
  int ndays;

  int total_courses;
  daylist* ret_day(int);
  string** contoarray(void);

  string_list distinct_courses;

  void savetxt(void);
  void display(void);

  void fill(void);
  void settings(void);

        int mainmenu(bool = true);
        void set_total_courses(void);


   void save_to_binary();
  void load_from_binary();
        void display_day(int);



        timetable();
  ~timetable();
};


class irecbox
{


 string coursecode;


public:
 int npresent, nabsent, nbunk;
 irecbox* next,*prev;
 string get_coursecode() const;
 void change_coursecode(string);
 irecbox(){

  coursecode = "";
  npresent = nabsent = nbunk =0;
 }


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
 timetable table;

 int today_num_courses;
 void update_num_courses();

 void RECOVERconfig();





 a_register();

  };

void a_register::RECOVERconfig(){

 setup_complete = true;
}

class listbox : public a_register
{
 irecbox* front,*rear;

    irecbox **todaylist;
 int numbox;
public:
 void totaldisplay();
 void idisplay(string*);

 void parseinput(string);

 void initiate();
 void set_today_array();
 irecbox* find_irecbox(string*);
 listbox();
 ~listbox();
};

int main(int argc, char const *argv[]){

 std::ios_base::sync_with_stdio(false);

 int i;
 string icommand;
 #ifdef __linux__
  system("clear");
 #else
  system("cls");
 #endif

 set_h_w();


 listbox all_records;
 all_records.table.mainmenu();

}


void prt_t_header(void){
 int monlength=0, i=0, day_len=1;
 refresh_time();
 set_h_w();
 std::cout<<"\n    "<<time_now.tm_mday<<' ';
 if(time_now.tm_mday>9) day_len=2;
 switch(time_now.tm_mon){
  case 0: std::cout<<"January "; monlength=8; break;
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
 int space = terminal_width - day_len - monlength - 42;
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

void greeting(string name){
 int i;
 for(i =0;name[i]!=' ' && i<name.size();i++);
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
     for(i=0;i<(terminal_height/2 - 9);i++) std::cout<<'\n';
   else
    for(i=0;i<(terminal_height/2 - 5);i++) std::cout<<'\n';

 magnify("mid",&msg,&name);
}

void refresh_time(){
 time_t t=time(0);
 time_now = *localtime(&t);
}

void set_h_w(){
    #ifdef __linux__
        winsize w;
        ioctl (STDOUT_FILENO, TIOCGWINSZ, &w);
        terminal_height = w.ws_row;
        terminal_width = w.ws_col;
    #else
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &csbi );
        terminal_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        terminal_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    #endif


}

void capitallize(string *s){
    for(int i=0; i<(s->size()) ; i++)
        (*s)[i] = toupper((*s)[i]);
}

void magnify(string pos, string *small_str, string *big_str){
 capitallize(small_str);
 capitallize(big_str);
 int spac, msglen = 5*(small_str->size()) - 1*1 + 2;
    int i,j,k;

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

void magnify(string pos, string *big_str){
 capitallize(big_str);
 int spac, msglen = 10*(big_str->size()) - 1*1 + 3*numspaces(*big_str);
    int i,j,k;

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

void smaller_magnify(string pos, string *small_str){
 capitallize(small_str);
 int spac, msglen = 5*(small_str->size()) - 1*1 + 2*numspaces(*small_str);
    int i,j,k;

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


void vibrate(string msg){
 int space = terminal_width/2 - 5*msg.size()/4, amp_diff = msg.size()/4, amp_space =0;
 bool dir=true;


 while(amp_diff != 0){
  for(int i=0;i<2*amp_diff + msg.size() -1;++i){
   system("clear");
   prt_t_header();
   greeting(name);



     if(terminal_width<115){
    std::cout<<'\n';
   }
   else std::cout<<"\n\n";


   for(int j=0;j<space;j++) std::cout<<' ';
   std::cout<<msg;
   std::cout<<std::endl;
   usleep(30000);
   if(dir){
    space++;
    if((space - terminal_width/2) == 1*msg.size()/4 - amp_diff)
     dir = !dir;
    if(space == terminal_width/2 - msg.size())
     --amp_diff;
   }
   else{
    space--;
    if((terminal_width/2) - space == 5*msg.size()/4 - amp_diff)
     dir = !dir;
   if(space == terminal_width/2)
     --amp_diff;
   }
  }
 }
}





timetable::timetable(){
   state=false;
   ndays=5;
   total_courses=0;
   day = new daylist[ndays];
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

  prt_t_header();
  set_h_w();
  string msg = "TimeTable Manager";


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
      <<"\n4. Display"
      <<"\n5. Save to text file"
      <<"\n6. Advanced Settings"
      <<"\n7. Exit \n";
  std::cin>>ch;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max() , '\n');
 }while(ch>7);
 switch(ch){
  case 1: fill(); break;
  case 2: load_from_binary(); break;
  case 3: save_to_binary(); break;
  case 4: display();
    return 0; break;
  case 5: savetxt();
    std::cout<<"\nSaved to the file : "<<txtfile; break;
  case 6: settings();
    return 0; break;
  case 7:

    mainmenu(false);

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
     return; break;
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



 }
 state = true;

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


void timetable::display(){
# 807 "Records_with_TT.cpp"
 refresh_time();
 system("clear");
 int i=0, j=0, k=0;


 std::cout<<"Date Printed : "<<time_now.tm_mday<<'-'<<time_now.tm_mon+1<<'-'<<time_now.tm_year + 1900;
 std::cout<<'\n';
 std::cout<<"Department : "<<dept;
 for(i=0;i<114-dept.size()- grp.size() - 21;i++ )
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

 for( i=0 ; i<5 ;i++ )
 {
  std::cout<<"||";
  switch(i){
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

    len = ret_day(i)->tpoints[j]->get_coursecode()->size();
    for( k=0 ; k < 5 -len/2 ; ++k ) std::cout<<' ';

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

    len = ret_day(i)->tpoints[j]->get_coursecode()->size();
    for( k=0 ; k < 5 -len/2 ; ++k ) std::cout<<' ';

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

 if(ch==1) savetxt();
 else{
  mainmenu();
 }
 return;
}

void timetable::save_to_binary(){
 std::ofstream fsave;
 fsave.open( savefile , std::ios::binary|std::ios::out);
 fsave.write((char*)&state,sizeof(state));
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

 char *cstr;
 size_t len;
 f_recall.read((char*)&len,sizeof(len));
 cstr = new char[len];
 f_recall.read(cstr,len*sizeof(char));
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

 fout.seekp(0);
 fout<<"Date Printed : "<<time_now.tm_mday<<'-'<<time_now.tm_mon+1<<'-'<<time_now.tm_year + 1900;
 fout<<'\n';
 fout<<"Department : "<<dept;
 for(i=0;i<114-dept.size()- grp.size() - 21;i++ )
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

 for( i=0 ; i<5 ;i++ )
 {
  fout<<"||";
  switch(i){
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

    len = ret_day(i)->tpoints[j]->get_coursecode()->size();
    for( k=0 ; k < 5 -len/2 ; ++k ) fout<<' ';

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

    len = ret_day(i)->tpoints[j]->get_coursecode()->size();
    for( k=0 ; k < 5 -len/2 ; ++k ) fout<<' ';

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

string** timetable::contoarray(){
 string** retarr;
 retarr=(string**)(new string[ndays][8]);
 for(int i=0;i<ndays;i++)
  for(int j=0;j<8;j++){
            if(day[i].tpoints[j])
       retarr[i][j]=*(day[i].tpoints[j]->get_coursecode());
            else retarr[i][j]="NULL"; }
 return retarr;
}

daylist* timetable::ret_day(int dayn){
 if ( dayn < 0 || dayn >= ndays){


  std::cout<<"Invalid Input Passed... Destructing Nodes, to prevent memory leak...";
  for(int i=0; i<ndays; i++)
   day[i].~daylist();
  std::cout<<"Exiting...";

  delete this;
  exit(0);

  return NULL;
 }
 else return &day[dayn];
}

daylist::daylist(){
   front=rear=NULL;
   numbox=0;
}

daylist::~daylist(){

 timeboxn *tmp = front;
    while(numbox && !(front)){
        tmp=front;
        front=tmp->next;
        delete tmp;
}
}

void daylist::make_tlist(){
 bool tbox_extend_flag = true;
 int i=8;
 string s;
 for(i=8;i<17;i++){
  if( i < 11){
   std::cout<<'\t'<<i<<":30am-"<<i+1<<":30am ";
   if( i ==8 ) std::cout<<"  ";
   else if ( i==9 ) std::cout<<' ';
   std::cout<<"- ";
  }
  else if( i == 11 )
     std::cout<<"\t11:30am-"<<"12:30pm - ";
    else if ( i ==12 ) continue;
      else
      std::cout<<'\t'<<i-12<<":30pm-"<<i-11<<":30pm - ";

  getline ( std::cin, s );
  if( s == "" ){
   tbox_extend_flag = false;
   continue;
  }
  else{ if ( s == "y" || s=="Y" ){
     if(tbox_extend_flag){
      float *endt = &(traverseto(numbox-1)->endtime);
      if( *endt < 11 || *endt > 12 )
       *endt +=1;
      else *endt +=2;
     }
     else{
      append_box( traverseto(numbox-1)->get_coursecode() , i );
      tbox_extend_flag = true;
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
  if( st < 13 )
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

 static timeboxn* retptr;
 retptr=front;
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
 for(int i=0;i<numbox;i++){
  len = temp->get_coursecode()->size() + 1;
  fsave->write((char*)&len,sizeof(len));
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
 timeboxn *box;
 for(int i=0;i<numbox;i++){
  box = new timeboxn;

  if(i == 0){
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

  f_recall->read((char*)&len,sizeof(len));
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

 today_num_courses = 0;
}

void listbox::parseinput(string s){

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
    else --(todaylist[j]->nbunk);
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


  string_list tmp_daylist;

            timeboxn *temp = a_register::table.ret_day((time_now.tm_wday + 6)%7)->traverseto(0);

  while(temp!=NULL){
   if(tmp_daylist.is_in_list(*(temp->get_coursecode())))
    continue;
   else{
    tmp_daylist.add_in_list(*(temp->get_coursecode()));
    todaylist[tmp_num] = find_irecbox(temp->get_coursecode());

    ++tmp_num;
   }
  }



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
 strnode *iter = a_register::table.distinct_courses.front;
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
 for(int i=0; i<numbox; ++i){
  tmp = front;
  front = front->next;
  delete tmp;
 }
}

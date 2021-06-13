#include <iostream>
#include <string>
#include <ctime>
#include <array>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <sstream>


#define SHOWS_PER_DAY   3
#define ROWS    10
#define COLS    10

using namespace std;

static int totUsers=0;

char rowNames[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

struct Seat  // Do we rerally require a struct for this?
{
    int row;
    int col;
    int bookedBy; // vacant seats will have value -1
};

struct Show
{
    string movie;
    time_t startTime; 
    time_t endTime; 
};

struct Cinema
{
    string name = "Pak Cinema"; 
    Show shows[SHOWS_PER_DAY]; // Movie shows per day  
};


// Utility functions
time_t setTime(time_t tt, unsigned int hr, unsigned int min)
{
    if (hr > 23)
        hr = 0;
    if (min > 59)
        min = 0;
    tm *t = localtime(&tt);
    t->tm_hour = hr;
    t->tm_min = min;
    return mktime(t);
}

time_t addDays(time_t tt, int days)
{
    tt = tt + (days * 86400); // 86400 seconds in a day
    return tt;
}

time_t addHours(time_t tt, int hrs)
{
    tt = tt + (hrs * 3600); // 3600 seconds per hour
    return tt;
}

string getDate(time_t tt)
{
    char s[51];
 
    tm *t = localtime(&tt);

    strftime(s, 50, "%d/%m/%Y", t);
    string tdate = s;
    return tdate;
}

string getTime(time_t tt)
{
    char s[51];
 
    tm *t = localtime(&tt);

    strftime(s, 50, "%R", t);
    string ttime = s;
    return ttime;
}


// ----------------------------------- Utility functions end

Cinema cinema;

int seats[ROWS][COLS];

void init()
{
    time_t tt = time(0);  // current time
    tt = setTime(tt, 0, 0); // set it to start of the day
    cinema.shows[0].startTime = addHours(tt, 10); // 10:00 am -> Ist show time
    cinema.shows[0].endTime = addHours(cinema.shows[0].startTime, 3); // 3-hour show
    cinema.shows[1].startTime = addHours(tt, 14); // 02:00 pm -> 2nd show time
    cinema.shows[1].endTime = addHours(cinema.shows[1].startTime, 3); // 3-hour show
    cinema.shows[2].startTime = addHours(tt, 18); // 06:00 pm -> 3rd show time
    cinema.shows[2].endTime = addHours(cinema.shows[2].startTime, 3); // 3-hour show

    int numLines = 0;
    ifstream inFile("users.dat");
    std::string unused;
    while ( getline(inFile, unused) )
        ++totUsers;
    //cinema.shows[0].startTime = 
}

void resetSeats()
{
    //fill(begin(seats), end(seats), Seat{0, 0, -1});
    std::fill(&seats[0][0], &seats[0][0]+sizeof(seats)/sizeof(int), -1);
}


void readShowData()
{
   ifstream inFile;
   inFile.open("show.dat");
   int idx, r, c, u;
   inFile >> idx;
   cout << "Index: " << idx << endl;
   getline(inFile, cinema.shows[0].movie);
   cout << "Movie: "<< cinema.shows[0].movie << endl;
    // reset data for next show
    resetSeats();
    cout << "Reading show data" << endl;
    while (inFile >> r >> c >> u)
    {
        cout << r << " " << c << " " << u << endl;
        if ( r>0 && r<=10 && c>0 && c<=10 && u>0 && u<=totUsers)
        {
            seats[r-1][c-1] = u;
        }  
    }
}

int bookSeat(int userId, int row, int col)
{
    if (seats[row][col] == -1) 
    {
        seats[row][col] = userId;
        return userId;
    }
    return -1;
}

bool isBooked (int row, int col)
{
    if (seats[row][col] == -1) 
        return 0;
    return 1;
}


void printSeats()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << rowNames[i] << to_string(j+1);
            
            if (seats[i][j] == -1)
                cout << ":  " ;
            else
                cout << ":" << setfill(' ') << setw(2) << seats[i][j];
            if (j < 9)
                cout << "  ";
        }
        cout << endl;
    }

}

int main()
{

    string uname, username, passwd, password;
    ifstream inFile;

    init();
    readShowData();
    printSeats();
    time_t tm= time(0);
    tm = addDays(tm, 5);
    string newDate = getDate(tm);   
    cout << newDate << endl;
 
    //std::fill(&st[0][0], &st[0][0]+sizeof(st)/sizeof(Seat), Seat{0, 0, -1});
    resetSeats();

    std::cout << __cplusplus << std::endl;

    exit(0);

    cout << "Please enter you name " ;
    cin >>uname;

    cout << " Please enter you Password " ;
    cin >>passwd;

    int userOk = 0;
    inFile.open("users.dat");
    while (inFile >> username >> password)
    {
        if ( uname == username)
        {
            if (password == passwd)
            {
                userOk = 1;
            }
        }  
    }
    if (userOk)
    {
        cout << "Welcome! " << endl;
    }
    else
    {
        cout << "Sorry, I do not know you." << endl;
    }
    exit(0);

/*
    cout << "\tUsername : " << username << endl;
    cout << "\tPassword :" << password << endl;
    
    Cinema a2 ;
    a2.setName("PakCinema");
    a2.setMovie("Wild Life in Asia");
    a2.initSeats();

    cout << "Cinema:" << endl;
    cout << "\tCinema = " << a2.getName()  << endl;
    cout << "\tMovie = " << a2.getMovie()  << endl;
    a2.showSeats();

    string selectedSeat;
    cout << " Please enter you Seat Number " ;
    cin >>selectedSeat;

    cout << "\tSeat Number : " << selectedSeat << endl;
*/
    return 1;
}
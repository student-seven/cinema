#include <iostream>
#include <string>

using namespace std;

char rowNames[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
                  'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
// Seat Status
#define BOOKED  1
#define VACANT  0

// Categories
#define VIP 3
#define BUSINESS    2
#define ECONOMY 1 

class Seat
{
private:
    bool status;   // two values; yes/no, true/false, available/NotAvailable; booked/vacant etc
    int category;
    string seatNumber;
    int bookedBy=-1;

public:
    void setCategory(int cat)
    {
        category= cat;
    }
    int getCategory()
    {
        return category;
    }
    int userBooked()
    {
        return bookedBy;
    }
    bool book(int userId)
    {
        status= BOOKED;
        bookedBy= userId;
        return status;
    }

    bool isBooked()
    {
        return status;
    } 

    void setSeatNumber(string sNum)
    {
        seatNumber = sNum;
    }

    string getSeatNumber()
    {
        return seatNumber;
    }
    
};

class Cinema
{
private:
    string name;  // will contain name. Max length = 49 characters
    string movie; // movie played in cinema. Max length = 49 characters
    int rows = 10;
    int cols = 10;
    Seat seats[10][10]; // The cinema will have 100 seat objects
    

public:
     
    void setName(string cname)
    {
        name= cname;
    }
 
    string getName()
    {
        return name;
    }

    void setMovie(string mov)
    {
        movie= mov;
    }
    string getMovie()
    {
        return movie;
    }

    void initSeats()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                seats[i][j].setSeatNumber (rowNames[i] + to_string(j+1));
            }
        }
    }
    void showSeats ()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << seats[i][j].getSeatNumber() << "  ";
                //cout << "z ";
            }
            cout << endl;
        }
    }
};
 
class person;

    char name[30];
    char paswd[10];


int main()
{
    cout << "Please enter you name " ;
    cin >>name;

    cout << " Please enter you Password " ;
    cin >>paswd;

    cout << "\tUsername : " << name << endl;
    cout << "\tPassword :" << paswd << endl;
    
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

    return 1;
}
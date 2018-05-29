/*
By Heber Cooke 5/27/18
REMEMBER to : Make infile file name, Name the file after the stock! Change CONST FILE_SIZE to correct settings for file size !
A program to take stock data
display the open price and date, display the end close price and date.
display the average move per day amount, display the total move per file.
display how many days closing higer, how many days closing lower.
display average volume and volume different from last day.
display a buy or sell signal depending on the average moving direction.
A decision to make a file with all the data to email or print
to a file named -- stock data .
*/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>
using namespace std;

const string F = "EEM.txt";  //change input file name here
const int FILE_SIZE = 20;  //change input file size here



void makeFile(int num, double expectedMove);
void Color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
} // end  void color function 
string  dateFix1(string date); // to switch date order to mm/dd/yy
//string  dateFix2(string date);  // from yy/dd/mm


int main(int argc, char *argv[])
{

	// file variables
	string date = "";    // date
	double open = 0.0; // open
	double high = 0.0; // high
	double low = 0.0; // low 
	double close = 0.0; // close 
	double adjClose = 0.0; // adjclose 
	int volume = 0;  // volume 
	 // calculation variables 
	double averageMove = 0.0; // open to close average moves
	char choice = ' ';
	int count = 0;
	double totalMove = 0.0;
	int totalVolume = 0;  // volume average
	int volumeDiff = 0;
	int  daysUp = 0;
	int  daysDown = 0;
	string  sign = "";  // sign BUY or SELL
	string ticker = "";  //  stock name 
	ticker = F.substr(0, 4);  //stock name 
	int num = 0;   // how many days into the future
	double expectedMove = 0.0; // expected move into the future

	ifstream infile;    // starting file 
	infile.open(F);  // opening file 
	if (infile.is_open())
	{
		cout << "---file open---" << endl;

		getline(infile, date, ',');
		infile >> open;
		infile.ignore(1);
		infile >> high;
		infile.ignore(1);
		infile >> low;
		infile.ignore(1);
		infile >> close;
		infile.ignore(1);
		infile >> adjClose;
		infile.ignore(1);
		infile >> volume;

		cout << fixed << setprecision(2);
		cout << ticker << "    " << "stock " << endl;
		cout << "Open price $" << open << endl << "on " << dateFix1(date) << endl << endl; // print out start of file
		averageMove = close - open;
		totalMove = open;
		totalVolume += volume;  // volume average 
		count = 1;

		while (!infile.eof())
		{
			getline(infile, date, ',');
			infile >> open;
			infile.ignore(1);
			infile >> high;
			infile.ignore(1);
			infile >> low;
			infile.ignore(1);
			infile >> close;
			infile.ignore(1);
			infile >> adjClose;
			infile.ignore(1);
			infile >> volume;
			averageMove += close - open;

			count += 1;
			totalVolume += volume;  // volume average 
			if (open > close)     // quantity days up or down
			{
				daysUp += 1;
			}// end if 
			else  daysDown += 1;

			if (count == FILE_SIZE)  // choosing last row in the file 
			{
				cout << "Close  price $" << close << endl << "on " << dateFix1(date) << endl << endl; // print out end of file 
				cout << "Average move per day is  $";
				if (averageMove < 0)
				{
					Color(4);
					cout << averageMove / FILE_SIZE << endl;
				}
				else
				{
					Color(2);
					cout << averageMove / FILE_SIZE << endl;
				}
				Color(7);
				totalMove = close - totalMove; // calculating the total move
				volumeDiff = volume - totalVolume / FILE_SIZE;
			} // enf if 
		}// end while file is open 
		cout << endl << "Total move is  $";
		if (totalMove < 0)
		{
			Color(4);
			cout << totalMove << endl;
		}
		else
		{
			Color(2);
			cout << totalMove << endl;
		}
		Color(2);
		cout << daysUp;
		Color(7);
		cout << " Days moving up" << endl;
		Color(4);
		cout << daysDown;
		Color(7);
		cout << " Days moving  down" << endl << endl;
		cout << "Volume average ";
		Color(1);
		cout << totalVolume / FILE_SIZE << endl;
		Color(7);
		cout << "Change from last day  ";
		Color(1);
		cout << volumeDiff << endl << endl;
		Color(7);
		if (averageMove < 0)   // sign BUY or SELL
		{
			Color(4);
			sign = "---SELL--- ";
		}
		else
		{
			Color(2);
			sign = "---BUY--- ";
		}
		cout << sign << endl;   // sign BUY or SELL
		Color(7);
	}//end if 

	else cout << "file not found " << endl;
	infile.close();
	cout << "The program calculates the average movement into the future" << endl;
	cout << "Enter how many days you want to see :";
	cin >> num ;
	expectedMove = num * averageMove / FILE_SIZE;
	cout << "The expected move for " << num << " days is " << expectedMove <<endl;
	cout << "price target would be " << expectedMove + close << endl;


	cout << endl;
	cout << "Do you want a file with all the information (Y/N)? ";
	cin >> choice;
	

	if (choice == 'Y' || choice == 'y')   // creating a file to print or email 
	{

		makeFile(num,expectedMove);

	}// if choice
	if (choice == 'N' || choice == 'n')
	{
		cout << "THANK YOU " << endl;
		cout << "for using the stock analysis program "<< endl;
	}//end if 

	system("pause");
	return 0;

}// end main -------------------------------------------------------------------------------

string  dateFix1(string date)
{
	string newDate = "";

	newDate = date.substr(6, 5) + date.substr(5, 1) + date.substr(1, 4);

	return newDate;
}// end dateFix ----------------------------------------------------------------------------

void makeFile(int num, double expectedMove)
{
	// file variables
	string date = "";    // date
	double open = 0.0; // open
	double high = 0.0; // high
	double low = 0.0; // low 
	double close = 0.0; // close 
	double adjClose = 0.0; // adjclose 
	int volume = 0;  // volume 
					 // calculation variables 
	double averageMove = 0.0; // open to close average moves
	char choice = ' ';
	int count = 0;
	double totalMove = 0.0;
	int totalVolume = 0;  // volume average
	int volumeDiff = 0;
	int  daysUp = 0;
	int  daysDown = 0;
	string  sign = "";  // sign BUY or SELL
	string ticker = "";  //  stock name 
	ticker = F.substr(0, 4);

	ofstream outFile;
	outFile.open("stock data ");
	if (outFile.is_open())
	{
		cout << "---file created successful---" << endl;
		ifstream infile;
		infile.open(F);  // opening file 
		if (infile.is_open())
		{

			getline(infile, date, ',');
			infile >> open;
			infile.ignore(1);
			infile >> high;
			infile.ignore(1);
			infile >> low;
			infile.ignore(1);
			infile >> close;
			infile.ignore(1);
			infile >> adjClose;
			infile.ignore(1);
			infile >> volume;

			outFile << fixed << setprecision(2);
			outFile << ticker << "    " << "stock " << endl;
			outFile << "Open price $" << open << endl << "on " << dateFix1(date) << endl << endl; // print out start of file
			averageMove = close - open;
			totalMove = open;
			totalVolume += volume;  // volume average 
			count = 1;

			while (!infile.eof())
			{
				getline(infile, date, ',');
				infile >> open;
				infile.ignore(1);
				infile >> high;
				infile.ignore(1);
				infile >> low;
				infile.ignore(1);
				infile >> close;
				infile.ignore(1);
				infile >> adjClose;
				infile.ignore(1);
				infile >> volume;
				averageMove += close - open;

				count += 1;
				totalVolume += volume;  // volume average 
				if (open > close)     // quantity days up or down
				{
					daysUp += 1;
				}// end if 
				else  daysDown += 1;

				if (count == FILE_SIZE)  // choosing last row in the file 
				{
					outFile << "Close  price $" << close << endl << "on " << dateFix1(date) << endl << endl; // print out end of file 
					outFile << "Average move per day is  $" << averageMove / FILE_SIZE << endl;
					totalMove = close - totalMove; // calculating the total move
					volumeDiff = volume - totalVolume / FILE_SIZE;
				} // enf if 
			}// end while file is open 
			outFile << endl << "Total move is  $" << totalMove << endl;
			outFile << daysUp << " Days moving up" << endl;
			outFile << daysDown << " Days moving  down" << endl << endl;
			outFile << "Volume average " << totalVolume / FILE_SIZE << endl;
			outFile << "Change from last day  " << volumeDiff << endl << endl;
			if (averageMove < 0)   // sign BUY or SELL
			{
				sign = "---SELL--- ";
			}
			else
			{
				sign = "---BUY ---";
			}
			outFile << sign << endl;   // sign BUY or SELL
			outFile << "The expected move for " << num << " days is " << expectedMove << endl;
			outFile << "price target would be " << expectedMove + close << endl;
		}//end if 
	}// end if open 
	outFile.close();
}// end make  file  --------------------------------------------------------------------------





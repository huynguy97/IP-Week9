/*                                                                    
                                             
           
                                                                                                    
                                 
                                      
                                                           
                                                                    
                                                        
                                                                     
                                                                     */
#define NDEBUG
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

//                       
/*                                                                    
                                                      
                                                                     */
struct Length
{
	int minutes;							//                
	int seconds;							//                  
};
struct Track
{
	string artist;                          //                             
	string cd;                              //             
	int    year;                            //                 
	int    track;							//                 
	string title;                           //                
	string tags;                            //               
	Length time;							//                 
	string country;                         //                 
};

int operator_number = 0;
//                                                                                       
typedef Track El ;
typedef vector <Track> MuziekDB;
//                                                                                        
MuziekDB liedjes;

/*                                                                       
                                
                                                              
                                                             
                                                                       */
bool operator< (const Length& a, const Length& b)
{
    operator_number++;
    if (a.minutes < b.minutes){
        return true;

        if (a.minutes == b.minutes){
            if (a.seconds < b.seconds){
                return true;
            }
        }
    }
    return false;
}

bool operator== (const Length& a, const Length& b)
{
    operator_number++;
    if (a.minutes == b.minutes){
        if (a.seconds == b.seconds){
            return true;
        }
    }
    return false;
}

bool operator<(const Track& a, const Track& b)
/* 
                              
                          
                                  
                                         
             
                                   
         
                           
     
                               
 */
{
    if (a.time == b.time){
        if (a.artist == b.artist){
            if (a.title == b.title){
                return a.cd < b.cd;
            }
            return a.title < b.title;
        }
        return a.artist <b.artist;
    }
    return a.time < b.time;
}

bool operator==(const Track& a, const Track& b)
/* 
                              
                          
                                  
                                         
             
         
     
 */

{
    if (a.time == b.time){
        if (a.artist == b.artist){
            if (a.title == b.title){
                return a.cd == b.cd;
            }
        }
    }
}

//	                                      
bool operator>(const Track& a, const Track& b)
{
	return b < a ;
}

bool operator<=(const Track& a, const Track& b)
{
	return !(b < a) ;
}

bool operator>=(const Track& a, const Track& b)
{
	return b <= a ;
}

/*                                                                       
                                    
                                                                       */
istream& operator>> (istream& in, Length& lengte)
{//             
    assert (true) ;
/*               
                                                                                         
*/
    char colon ;
    in >> lengte.minutes >> colon >> lengte.seconds ;
    return in ;
}

ostream& operator<< (ostream& out, const Length lengte)
{
    out << lengte.minutes << ':' ;
    if (lengte.seconds < 10)
        out << '0' ;
    out << lengte.seconds ;
    return out ;
}

istream& operator>> (istream& infile, Track& track)
{
    string dummy;
    getline(infile,track.artist);       //       
    getline(infile,track.cd);           //   
    infile >> track.year ;              //     
    getline(infile, dummy) ;            //                      
    infile >> track.track ;             //         
    getline(infile, dummy) ;            //                      
    getline(infile,track.title);        //            
    getline(infile,track.tags);         //           
    infile >> track.time ;              //           
    getline(infile, dummy) ;            //                      
    getline(infile,track.country);      //        
    getline(infile, dummy) ;            //                      
    return infile ;
}

ostream& operator<< (ostream& out, const Track track)
{
    out << track.artist << " " << track.cd << " [" << track.track << "] (" << track.time << ")" ;
    return out ;
}

//                                                                     
int lees_liedjes(ifstream& infile, MuziekDB& liedjes)
{
    do {
        Track volgende ;
        infile >> volgende ;
        if (infile)
            liedjes.push_back(volgende);
    }
    while (infile);
    return liedjes.size();
}

int lees_bestand (string bestandnaam)
{
    ifstream nummersDBS (bestandnaam.c_str());
    if (!nummersDBS)
    {
        cout << "Kon '" << bestandnaam << "' niet openen." << endl;
        return -1;
    }
    cout << "Lees '" << bestandnaam << "' in." << endl;
	int aantal = lees_liedjes (nummersDBS, liedjes);
	nummersDBS.close();
	return aantal;
}

void toon_MuziekDB (MuziekDB liedjes)
{
    for (int i = 0 ; i < liedjes.size(); i++)
        cout << i+1 << ". " << liedjes[i] << endl ;
}

/*                                                                       
                                                         
                                                                       */
struct Slice
{
	int from ; 	//             
	int to ; 	//           
} ;

Slice mkSlice (int from, int to)
{
//	              
	assert (0 <= from && from <= to);
	Slice s = { from, to } ;
	return s ;
}

bool valid_slice (Slice s)
{
	return 0 <= s.from && s.from <= s.to ;
}

/*                                                                       
                                                         
                                                                       */

bool is_sorted (MuziekDB& array, Slice s)
{
//	              
	assert (valid_slice(s)) ;	//                            
//	               
//	                 	                                  
//						                                  
//						   
//						                              
	bool sorted = true ;
	for (int i = s.from; i < s.to && sorted; i++)
		if (array[i] > array[i+1])
			sorted = false ;
	return sorted ;
}

int find_position ( MuziekDB& array, Slice s, El y )
{
//	              
	assert (valid_slice(s) && is_sorted(array,s)) ;    //                            
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= array [i] )
			return i ;
	return s.to+1;
}

void shift_right ( MuziekDB& array, Slice s )
{
//	              
	assert (valid_slice (s)) ;	//                                
//	                                	  	                 
//			    	                	  	                   
//						   
//			    	              		  	               
	for ( int i = s.to+1 ; i > s.from ; i-- )
		array [i]  = array [i-1] ;
}

void insert ( MuziekDB& array, int& length, El y )
{
	const int pos = find_position (array, mkSlice (0, length-1), y) ;
	if (pos < length)
		shift_right ( array, mkSlice (pos, length-1) ) ;
	array [pos] = y ;
	length++;
}

void swap (MuziekDB& array, int  i, int  j )
{
//	              
	assert ( i >= 0 && j >= 0 ) ;	//                          
						            //                          
//                                                                    
	const El help = array [i];
	array [i] = array [j] ;
	array [j] = help;
}

//	                           
void insertion_sort ( MuziekDB& array, int length )
{
	int sorted = 1 ;
    while ( sorted < length )
    {   insert ( array, sorted, array[sorted] ) ;
    }
}

//	                           
int smallest_value_at ( MuziekDB& array, Slice s )
{
//	              
	assert (valid_slice (s)) ;	//                        
//	                                                             
//	                                                 
	int  smallest_at = s.from ;
	for ( int index = s.from+1 ; index <= s.to ; index++ )
		if ( array [index] < array [smallest_at] )
			smallest_at = index ;
	return smallest_at ;
}

void selection_sort ( MuziekDB& array, int length )
{	for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
	{   const int k = smallest_value_at (array, mkSlice (unsorted, length-1));
	    swap ( array, unsorted, k ) ;
	}
}

//	                        
bool bubble ( MuziekDB& array, Slice s )
{
//	              
	assert (valid_slice(s));	//                           
//	               
//	                                                       
//	                                         
	bool is_sorted = true ;
	for ( int i = s.from ; i < s.to ; i++)
	    if ( array [i] > array [i+1])
		{	swap ( array, i, i+1 ) ;
			is_sorted = false ;
		}
	return is_sorted ;
}

void bubble_sort ( MuziekDB& array, int length )
{
    while ( !bubble ( array, mkSlice (0, length-1 ) ) )
        length-- ;
}

/*                                                                       
                                        
                         
                                                                           
                                                           
                                                        
                                                                       */
enum Sorteermethode {Insertion,Selection,Bubble,AantalMethoden};
string sorteermethode [] = {"insertion", "selection", "bubble"} ;

Sorteermethode selecteer ()
{
    cout << "Kies een sorteermethode: " << endl ;
    for (int m = 0; m < AantalMethoden; m++)
        cout << m+1 << ": " << sorteermethode[m] << " sort" << endl ;
    int keuze ;
    cin >> keuze ;
    return static_cast<Sorteermethode>(keuze-1) ;
}

int main()
{
	int aantalLiedjes = lees_bestand ("Nummers.txt");
	if (aantalLiedjes < 0)
	{
        cout << "Bestand inlezen mislukt. Programma termineert." << endl;
	    return aantalLiedjes;
    }
    Sorteermethode m = selecteer () ;
    cout << "Sorteren bestand met " << sorteermethode[m] << " sort" << endl;
    switch (m)
    {
        case Insertion: insertion_sort(liedjes,aantalLiedjes) ; break ;
        case Selection: selection_sort(liedjes,aantalLiedjes) ; break ;
        case Bubble:    bubble_sort   (liedjes,aantalLiedjes) ; break ;
        default:        cout << "Huh?" << endl ;
    }
    cout << "Bestand gesorteerd." << endl;
    //                         
    cout << "Het aantal operaties is" << " " << operator_number << " " << "keer" << endl;

    int j = 0;

    while (operator_number >= 100000){
        operator_number = operator_number - 100000;
        j++;

        while (j > 0){
            cout << "*";
            j--;
        }
    }
    if (operator_number > 0){
        cout << "." << endl;
    }

	return 0;
}


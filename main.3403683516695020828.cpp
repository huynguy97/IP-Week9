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

/*                                                                    
                         
                            
                                                                    */

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

const int MAX_AANTAL_LIEDJES = 6000;        //                                         
vector<Track> liedjes;                      //                                          
vector<Track> oud;
int size(vector<Track>& v)
{   return static_cast<int> (v.size());
}
int global;

/*                                                                       
                                
                                                              
                                                             
                                                                       */
//                            

bool operator==(const Length& a, const Length& b){
//              
    assert ( a.seconds >= 0 && b.seconds >= 0 && a.seconds < 60 && b.seconds < 60 );
    return (a.minutes == b.minutes && a.seconds == b.seconds);
}

//                             
bool operator<(const Length& a, const Length& b){
//              
    assert ( a.seconds >= 0 && b.seconds >= 0 && a.seconds < 60 && b.seconds < 60 );

    bool a_is_smaller = true;
    if(a.minutes > b.minutes)
        a_is_smaller = false;
    else if(a.minutes == b.minutes && a.seconds >= b.seconds)
        a_is_smaller = false;

    return a_is_smaller;
}

/*
                         
                                              
 
             
                             
                         
                                 
                                         
             
                                        
         
                                
     
                                    
 
*/

//                             
bool operator<(const Track& a, const Track& b)
{
    global++;
    if(a.time == b.time){
        if(a.artist == b.artist){
            if(a.title == b.title){
                return a.cd < b.cd;
            }
            else return a.title < b.title;
        }
        else return a.artist < b.artist;
    }
    else return a.time < b.time;
}

/*
                         
                                               
 
             
                                                                                                                                                      
 
*/

//                  
bool operator==(const Track& a, const Track& b)
{
    global++;
    return (a.time == b.time && a.artist == b.artist && a.title== b.title && a.cd == b.cd); //                                                       
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
int lees_liedjes(ifstream& infile, vector<Track>& liedjes)
{
    int aantal_ingelezen_liedjes = 0 ;
    do {
        Track volgende ;
        infile >> volgende ;
        liedjes.push_back(volgende);
        oud.push_back(volgende);
        aantal_ingelezen_liedjes++;
    }
    while (infile);
    return aantal_ingelezen_liedjes ;
}

int lees_bestand (string bestandnaam)
{
    ifstream nummersDBS (bestandnaam.c_str());
    if (!nummersDBS)
    {
        cout << "Kon '" << bestandnaam << "' niet openen." << endl;
        return -1;
    }
    //                                                   
	int aantal = lees_liedjes (nummersDBS, liedjes);
	nummersDBS.close();
	return aantal;
}

void toon_MuziekDB (vector<Track>(liedjes), int aantalLiedjes)
{
    cout << aantalLiedjes << endl;
    for (int i = 0 ; i < aantalLiedjes; i++)
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
typedef Track El ;                //                                                                     

bool is_sorted (El array [], Slice s)
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

bool is_sorted2 (vector<El>&(track) , Slice s)
{
//	              
	assert (valid_slice(s)) ;
//	               
//	                 	                                    
//						                                    
//						   
//						                                
	bool sorted = true ;
	for (int i = s.from; i < s.to && sorted; i++)
		if (track[i] > track[i+1])
			sorted = false ;
	return sorted ;
}

int find_position ( El array [], Slice s, El y )
{
//	              
	assert (valid_slice(s) && is_sorted(array,s)) ;    //                            
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= array [i] )
			return i ;
	return s.to+1;
}

int find_position2 ( vector<El>& track, Slice s, El y )
{
//	              
	assert (valid_slice(s) && is_sorted2(track,s)) ;    //                             
//	                                          
    int count_stars = 0;
	for ( int i = s.from ; i <= s.to ; i++ )
    {
		if ( y <= track [i] )
            return i;
    }
	return s.to+1;
}

void shift_right ( El array [], Slice s )
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

void shift_right2 ( vector<El>& track, Slice s )
{
//	              
	assert (valid_slice (s)) ;
//	                                                      
	for ( int i = s.to+1 ; i > s.from ; i-- )
		track [i]  = track [i-1] ;
}

void insert ( El array [], int& length, El y )
{
	const int pos = find_position (array, mkSlice (0, length-1), y) ;
	if (pos < length)
		shift_right ( array, mkSlice (pos, length-1) ) ;
	array [pos] = y ;
	length++;
}

void insert2 (vector<El>& track, int& length, El y)
{
    const int pos = find_position2 (track, mkSlice (0, length-1), y) ;
	if (pos < length)
		shift_right2 ( track, mkSlice (pos, length-1) ) ;
	track [pos] = y ;
	length++;
}

void swap (El array [], int  i, int  j )
{
//	              
	assert ( i >= 0 && j >= 0 ) ;	//                          
						            //                          
//                                                                    
	const El help = array [i];
	array [i] = array [j] ;
	array [j] = help;
}

void swap2 (vector<El>&(track), int  i, int  j )
{
//	              
	assert ( i >= 0 && j >= 0 ) ;	//                           
						            //                           
//                                                                        
	const El help = track [i];
	track [i] = track [j] ;
	track [j] = help;
}

//	                           
void insertion_sort ( El array [], int length )
{
	int sorted = 1 ;
    while ( sorted < length )
    {   insert ( array, sorted, array[sorted] ) ;
    }
}

void insertion_sort2 (vector<El>&(track), int length)
{
    int sorted = 1;
    while (sorted < length)
    {
        insert2 (track, sorted, track[sorted]);
    }
}

//	                           
int smallest_value_at ( El array [], Slice s )
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

int smallest_value_at2 ( vector<El>&(track), Slice s )
{
//	              
	assert (valid_slice (s)) ;	//                        
//	                                                              
//	                                                   
	int  smallest_at = s.from ;
	for ( int index = s.from+1 ; index <= s.to ; index++ )
		if ( track [index] < track [smallest_at] )
			smallest_at = index ;
	return smallest_at ;
}

void selection_sort ( El array [], int length )
{	for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
	{   const int k = smallest_value_at (array, mkSlice (unsorted, length-1));
	    swap ( array, unsorted, k ) ;
	}
}

void selection_sort2 ( vector<El>&(track), int length )
{	for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
	{   const int k = smallest_value_at2 (track, mkSlice (unsorted, length-1));
	    swap2 ( track, unsorted, k ) ;
	}
}

//	                        
bool bubble ( El array [], Slice s )
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

bool bubble2 ( vector<El>&(track), Slice s )
{
//	              
	assert (valid_slice(s));	//                            
//	               
//	                                                          
//	                                          
	bool is_sorted = true ;
	for ( int i = s.from ; i < s.to ; i++)
	    if ( track [i] > track [i+1])
		{	swap2 ( track, i, i+1 ) ;
			is_sorted = false ;
		}
	return is_sorted ;
}

void bubble_sort ( El array [], int length )
{
    while ( !bubble ( array, mkSlice (0, length-1 ) ) )
        length-- ;
}

void bubble_sort2 ( vector<El>&(track), int length )
{
    while ( !bubble2 ( track, mkSlice (0, length-1 ) ) )
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
    int starcount = 0;
	int aantalLiedjes = lees_bestand ("Tracks.txt");
	if (aantalLiedjes < 0)
	{
        cout << "Bestand inlezen mislukt. Programma termineert." << endl;
	    return aantalLiedjes;
    }
    Sorteermethode m = selecteer () ;
    cout << "Sorteren bestand met " << sorteermethode[m] << " sort" << endl;
    //                                                       
    /*
              
     
                       
                                        
             
                           
                                                        
                                              
                                         
                 
                                                                          
                 
                    
                 
                                                                                 
                 
                              
             

                   
                       
                                        
             
                           
                                                        
                                              
                                         
                 
                                                                          
                 
                    
                 
                                                                                 
                 
                              
             
                   
                    
                                        
             
                           
                                                    
                                              
                                         
                 
                                                                          
                 
                    
                 
                                                                                 
                 

                              
             
                   
                                                
     
    */
    //                                                         
    switch(m){
        case Insertion: insertion_sort2(liedjes, aantalLiedjes);
        case Selection: selection_sort2(liedjes, aantalLiedjes);
        case Bubble: bubble_sort2(liedjes, aantalLiedjes);
    }
    cout << "Bestand gesorteerd." << endl;
    toon_MuziekDB (liedjes,aantalLiedjes);
    cout << "Comparisons made: " << global << endl;
	return 0;
}

/*                                                                                                                            
                                                                                                              
                                
*/

/*                                                                                                    
                                                                                                              
                                                                  
                                                        
*/


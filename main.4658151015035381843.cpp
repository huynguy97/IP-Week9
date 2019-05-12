//             
//                          

/*                                                                    
                                              
            
                                                                                                            
                                  
                              
                                                           
                                                                    
                                                          
                                                               
                                                                     */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <math.h>

#define NDEBUG

using namespace std;

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
	string year;                            //                   
	string track_no;						//             
	string title;                           //            
	string tags;                            //                            
	Length time;							//             
	string country;                         //                                         
};

vector<Track> songs;              //                                     

int cC = 0; //                 
/*                                                                       
                                
                                                               
                                                                         
                                                                       */
int stringToInt(string s)
{
    double value = 0;
    for(int i = 0; i < s.length(); i++)
    {
        int digit = s[i] - '0';
        value += (digit * pow(10, s.length() - i - 1));
    }
    return (int)value;
}

bool operator<(const Length& a, const Length& b)
{
    int aLengthSec = 60 * a.minutes + a.seconds;
    int bLengthSec = 60 * b.minutes + b.seconds;
    return aLengthSec < bLengthSec;
}

bool operator>(const Length& a, const Length& b)
{
    return b < a;
}

bool operator==(const Length& a, const Length& b)
{
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

bool operator!=(const Length& a, const Length& b)
{
    return !(a == b);
}

bool operator<(const Track& a, const Track& b)
{
    cC++;
    if(a.artist < b.artist) return true;
    if(a.artist > b.artist) return false;
    if(a.cd < b.cd) return true;
    if(a.cd > b.cd) return false;
    if(stringToInt(a.year) < stringToInt(b.year)) return true;
    if(stringToInt(a.year) > stringToInt(b.year)) return false;
    if(stringToInt(a.track_no) < stringToInt(b.track_no)) return true;
    return false;
}

/*
                                              
 
         
                                    
                                     
                                        
                                         
                                      
                 
 
*/
bool operator==(const Track& a, const Track& b)
{
    bool equality = true;
    if(a.artist != b.artist) equality = false;
    if(a.cd != b.cd) equality = false;
    if(a.year != b.year) equality = false;
    if(a.track_no != b.track_no) equality = false;
    return equality ;   /*                                                 */
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
istream& operator>> (istream& in, Length& length)
{//               
    assert (true) ;
/*                 
                                                                                                      
*/
    char colon ;
    in >> length.minutes >> colon >> length.seconds ;
    return in ;
}

ostream& operator<< (ostream& out, const Length length)
{//               
    assert (true) ;
/*                 
                                                                       
*/
    out << length.minutes << ':';
	if (length.seconds < 10)
		out << '0';
	out << length.seconds;
	return out ;
}

void skip_to_next_newline (istream& infile)
{//               
    assert (true) ;
/*                 
                                                                        
*/
    string remains ;
    getline (infile, remains) ;
}

istream& operator>> (istream& infile, Track& track)
{//               
    assert (true) ;
/*                 
                                                                                                                   
                                      
*/
    getline(infile,track.artist);       //       
    getline(infile,track.cd);           //   
    infile >> track.year ;              //     
    skip_to_next_newline(infile) ;
    infile >> track.track_no ;          //             
    skip_to_next_newline(infile) ;
    getline(infile,track.title);        //            
    getline(infile,track.tags);         //           
    infile >> track.time ;              //           
    skip_to_next_newline(infile) ;
    getline(infile,track.country);      //        
    skip_to_next_newline(infile) ;
    return infile ;
}

//                                                                                                        
ostream& operator<< (ostream& out, const Track track)
{//               
    assert (true) ;
/*                 
                                                                                
*/
    out << track.artist   << endl ;
    out << track.cd       << endl ;
    out << track.year     << endl ;
    out << track.track_no << endl ;
    out << track.title    << endl ;
    out << track.tags     << endl ;
    out << track.time     << endl ;
    out << track.country  << endl ;
    out << endl ;
    return out ;
}

int read_songs (ifstream& infile, vector<Track>& db)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    do
    {
        Track song ;
        infile >> song ;
        if (infile)

            db.push_back(song);
    }
    while (infile);
    return db.size() ;
}

int read_songs (ifstream& infile, vector<Track>& db, int maxSongs)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int readSongs = 0;

    do
    {
        Track song ;
        infile >> song ;
        if (infile)
        {
           db.push_back(song);
           readSongs++;
        }
    }
    while (infile && readSongs < maxSongs);
    return db.size() ;
}

int read_file (string filename)
{//               
    assert (songs.size() == 0) ;
/*                 
                                                                              
                                                                                             
                                        
*/
    ifstream songsDBS (filename.c_str());
    if (!songsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
	const int NO_OF_SONGS = read_songs (songsDBS, songs);
	songsDBS.close();
	cout << " Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

int read_file (string filename, int maxSongs)
{//               
    assert (songs.size() == 0) ;
/*                 
                                                                              
                                                                                             
                                        
*/
    ifstream songsDBS (filename.c_str());
    if (!songsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
	const int NO_OF_SONGS = read_songs (songsDBS, songs, maxSongs);
	songsDBS.close();
	return NO_OF_SONGS;
}

void show_all_tracks (vector<Track> songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < songs.size(); i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

/*                                                                       
                                                         
                                                                       */
struct Slice
{
	int from ; 	//             
	int to ; 	//           
} ;

Slice mkSlice (int from, int to)
{//	              
	assert (0 <= from && from <= to);
/*                 
                                              
*/	Slice s = { from, to } ;
	return s ;
}

bool valid_slice (Slice s)
{//               
    assert (true) ;
/*                 
                                                                                      
*/
	return 0 <= s.from && s.from <= s.to ;
}

bool is_sorted (vector<Track>& data, Slice s)
{//	              
	assert (valid_slice(s)) ;	//                           
//	               
//	                 	                                
//						                                
//						   
//						                            
	bool sorted = true ;
	for (int i = s.from; i < s.to && sorted; i++)
		if (data[i] > data[i+1])
			sorted = false ;
	return sorted ;
}

int find_position (vector<Track>& data, Slice s, Track y )
{//	              
	assert (valid_slice(s) && is_sorted(data,s)) ;    //                           
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= data [i] )
			return i ;
	return s.to+1;
}

void shift_right ( vector<Track>& data, Slice s )
{//	              
	assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
	for ( int i = s.to+1 ; i > s.from ; i-- )
		data [i]  = data [i-1] ;
}

void insert (vector<Track>& data, int& length, Track y )
{//               
    Slice s = mkSlice(0,length-1) ;
    assert (length >= 0 && is_sorted (data, s)) ;
/*                 
                                                                                     
                                   
*/
	const int POS = find_position (data, mkSlice (0, length-1), y) ;
	if (POS < length)
		shift_right ( data, mkSlice (POS, length-1) ) ;
	data [POS] = y ;
	length++;
}

void swap (vector<Track>& data, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const Track HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

//	                           
void insertion_sort (vector<Track>& data)
{
	int sorted = 1 ;
    while ( sorted < data.size() )
    {   insert ( data, sorted, data[sorted] ) ;
    }
}

//	                           
int smallest_value_at (vector<Track>& data, Slice s )
{//	              
	assert (valid_slice (s)) ;	//                        
//	                                                            
//	                                               
	int smallest_at = s.from ;
	for ( int index = s.from+1 ; index <= s.to ; index++ )
		if ( data [index] < data [smallest_at] )
			smallest_at = index ;
	return smallest_at ;
}

void selection_sort (vector<Track>& data)
{	for ( int unsorted = 0 ; unsorted < data.size() ; unsorted++ )
	{   const int k = smallest_value_at (data, mkSlice (unsorted, data.size()-1));
	    swap ( data, unsorted, k ) ;
	}
}

//	                        
bool bubble (vector<Track>& data, Slice s )
{//	              
	assert (valid_slice(s));	//                          
//	               
//	                                                    
//	                                        
	bool is_sorted = true ;
	for ( int i = s.from ; i < s.to ; i++)
	    if ( data [i] > data [i+1])
		{	swap ( data, i, i+1 ) ;
			is_sorted = false ;
		}
	return is_sorted ;
}

void bubble_sort (vector<Track>& data)
{
    int length = data.size();
    while ( !bubble ( data, mkSlice (0, length-1 ) ) )
        length-- ;
}

int maximum(const int& a, const int& b)
{
    if(a > b) return a;
    else return b;
}

int minimum(const int& a, const int& b)
{
    if(a < b) return a;
    else return b;
}
/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */
enum SortingMethod {InsertionSort,SelectionSort,BubbleSort,NoOfSortingMethods};
string methods [] = {"insertion", "selection", "bubble"} ;

SortingMethod get_sorting_method ()
{
    cout << "What sorting method do you want to use? " << endl ;
    for (int m = 0; m < NoOfSortingMethods; m++)
        cout << m+1 << ": " << methods[m] << " sort" << endl ;
    int choice ;
    cin >> choice ;
    choice = maximum (1, minimum (choice, NoOfSortingMethods)) ;
    return static_cast<SortingMethod>(choice-1) ;
}

int exercise_1_to_4() //          
{
	const int NO_OF_SONGS = read_file ("Tracks.txt");
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }
    SortingMethod m = get_sorting_method () ;
    cout << "Sorting tracks with " << methods[m] << " sort" << endl;
    switch (m)
    {
        case InsertionSort: insertion_sort(songs) ; break ;
        case SelectionSort: selection_sort(songs) ; break ;
        case BubbleSort:    bubble_sort   (songs) ; break ;
        default:        cout << "Huh?" << endl ;
    }
    cout << "Tracks sorted." << endl;
    show_all_tracks (songs) ;
    cout << "It took " << cC << " comparisons!" << endl;
	return 0;
}

void emptyVector(vector<Track>& a)
{
    while(a.size() > 0)
    {
        a.pop_back();
    }
}

void visualizeNumber(int& a)
{
    while(a > 0)
    {
        if(a > 100000)
        {
            cout << "*";
            a -= 100000;
        }
        else
        {
            cout << ".";
            a = 0;
        }
    }
    cout << endl;
}

void insertion_sort_analysis(vector<Track>& songs, const int& maxSlice)
{
    emptyVector(songs);
    for(int i = 1; i*100 < maxSlice; i++)
    {
        read_file("Tracks.txt", i*100);
        insertion_sort(songs);
        emptyVector(songs);
        visualizeNumber(cC);
    }
}

void selection_sort_analysis(vector<Track>& songs, const int& maxSlice)
{
    emptyVector(songs);
    for(int i = 1; i*100 < maxSlice; i++)
    {
        read_file("Tracks.txt", i*100);
        selection_sort(songs);
        emptyVector(songs);
        visualizeNumber(cC);
    }
}

void bubble_sort_analysis(vector<Track>& songs, const int& maxSlice)
{
    emptyVector(songs);
    for(int i = 1; i*100 < maxSlice; i++)
    {
        read_file("Tracks.txt", i*100);
        bubble_sort(songs);
        emptyVector(songs);
        visualizeNumber(cC);
    }
}

int exercise_5() //      
{
    const int NO_OF_SONGS = read_file ("Tracks.txt");
    SortingMethod m = get_sorting_method () ;
    cout << "Sorting tracks with " << methods[m] << " sort" << endl;
    switch (m)
    {
        case InsertionSort: insertion_sort_analysis(songs, NO_OF_SONGS) ; break ;
        case SelectionSort: selection_sort_analysis(songs, NO_OF_SONGS) ; break ;
        case BubbleSort:    bubble_sort_analysis(songs, NO_OF_SONGS) ; break ;
        default:        cout << "Huh?" << endl ;
    }
	return 0;
}

int main()
{
    cout << "To check program for exercises 1 - 4 enter 'a'"
         << endl << "to check program for exercise 5 enter anything else!"
         << endl;

    char a;
    cin >> a;
    if(a == 'a') return exercise_1_to_4();
    else return exercise_5();

}

/*
          
 
                                                     
                                                 
             
 
*/
/*
                                                                                                    
                      

                      

               
                  	        
                  	        
               		      

            
                  	        
                  	        
               		        

                                                                                                                     
                                                                                                  

                                                                                                                                                                                   
                                                                                                                   

                                                                                                       

                                                                                                                                                                                                                                         

                                                                                                    
                      

                                                                                                                                                                                                                                                                       
                                                          
                                                                                                                                                                       
                                                                                      
                                                                                                  
*/


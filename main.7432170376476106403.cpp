/*                                                                    
                                              
            
                                                                                                            
                                  
                              
                                                           
                                                                    
                                                          
                                                               
                                                                     */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

#include<typeinfo>

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
	int    track_no;						//             
	string title;                           //            
	string tags;                            //                            
	Length time;							//             
	string country;                         //                                         
};

typedef Track El;
typedef vector<Track> Songs;              //                                     
Songs songs;
int global_counter = 0;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator<(const Length& a, const Length& b)
{
    if (a.minutes*60+a.seconds < b.minutes*60+b.seconds)
        return true;
    return false;
}

bool operator==(const Length& a, const Length& b)
{
    return (a.minutes == b.minutes && a.seconds == b.seconds);
}

bool operator<(const Track& a, const Track& b)
{
    global_counter++;
    if (!(a.time == b.time))
        return a.time < b.time;
    if (a.artist != b.artist)
        return a.artist < b.artist;
    if (a.cd != b.cd)
        return a.cd < b.cd;
    if (a.year != b.year)
        return a.year < b.year;
    if (a.track_no != b.track_no)
        return a.track_no < b.track_no;
    return false;
}

bool operator==(const Track& a, const Track& b)
{
    global_counter++;
    return (a.time == b.time &&
            a.artist == b.artist &&
            a.cd == b.cd &&
            a.year == b.year &&
            a.track_no == b.track_no);
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

//                                                                           
int read_songs (ifstream& infile, Songs& songs)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int NO_OF_SONGS = 0;
	Track song;
    do {
        infile >> song ;
        songs.push_back(song);
        NO_OF_SONGS++;
    }
    while (infile);
    return NO_OF_SONGS;
}

int read_file (string filename)
{//               
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
	cout << "Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

//                                                                           
void show_all_tracks (Songs& songs, int NO_OF_SONGS)
{//               
    assert (true);
/*                 
                                                                  
*/
    for (int i = 0 ; i < NO_OF_SONGS; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

/*                                                                       
                                                         
                                                                       */
void visualize_growth (int nr_of_operations)
{
    while (nr_of_operations >= 100000) {
        nr_of_operations -= 100000;
        cout << '*';
    }
    if (nr_of_operations > 0)
        cout << '.' << endl;
}

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

                //                                                       

bool is_sorted (Songs& songs, Slice s)
{//	              
	assert (valid_slice(s)) ;	//                           
//	               
//	                 	                                
//						                                
//						   
//						                            
	bool sorted = true ;
	for (int i = s.from; i < s.to && sorted; i++)
		if (songs[i] > songs[i+1])
			sorted = false ;
	return sorted ;
}

int find_position (Songs& songs, Slice s, El y)
{//	              
	assert (valid_slice(s) && is_sorted(songs, s)) ;    //                           
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= songs[i] )
			return i ;
	return s.to+1;
}

void shift_right (Songs& songs, Slice s)
{//	              
	assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
	for (int i = s.to+1 ; i > s.from ; i--)
		songs[i]  = songs[i-1] ;
}

void insert (Songs& songs, int& length, El y)
{//               
    //                               
    //                                              
/*                 
                                                                                     
                                   
*/
	const int POS = find_position (songs, mkSlice (0, length-1), y) ;
	if (POS < length)
		shift_right (songs, mkSlice (POS, length-1) ) ;
	songs[POS] = y ;
	length++;
}

void swap (Songs& songs, int i, int j)
{//	              
	assert (i >= 0 && j >= 0) ;	//                         
						            //                         
//                                                                
	const El HELP = songs[i];
	songs[i] = songs[j] ;
	songs[j] = HELP;
}

//	                           
void insertion_sort (Songs& songs, int length)
{
	int sorted = 1 ;
    while (sorted < length) {
        insert (songs, sorted, songs[sorted]);
        if ((sorted-99)%100 == 0)
            visualize_growth(global_counter);
    }
}

//	                           
int smallest_value_at (Songs& songs, Slice s)
{//	              
	assert (valid_slice (s)) ;	//                        
//	                                                            
//	                                               
	int smallest_at = s.from ;
	for ( int index = s.from+1 ; index <= s.to ; index++ )
		if ( songs [index] < songs [smallest_at] )
			smallest_at = index ;
	return smallest_at ;
}

void selection_sort (Songs& songs, int length)
{	for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
	{   const int k = smallest_value_at (songs, mkSlice (unsorted, length-1));
	    swap ( songs, unsorted, k ) ;
	    if ((unsorted-100)%100 == 0)
            visualize_growth(global_counter);
	}
}

//	                        
bool bubble (Songs& songs, Slice s )
{//	              
	assert (valid_slice(s));	//                          
//	               
//	                                                    
//	                                        
	bool is_sorted = true ;
	for ( int i = s.from ; i < s.to ; i++)
	    if ( songs [i] > songs [i+1])
		{	swap ( songs, i, i+1 ) ;
			is_sorted = false ;
		}
    if ((s.to-99)%100 == 0)
        visualize_growth(global_counter);
	return is_sorted ;
}

void bubble_sort (Songs& songs, int length )
{
    while ( !bubble ( songs, mkSlice (0, length-1 ) ) ) {
        length-- ;
    }
}

/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */
enum SortingMethod {InsertionSort,SelectionSort,BubbleSort,NoOfSortingMethods};
string methods [] = {"insertion", "selection", "bubble"} ;

int maximum (int first, int second)
{
    if (first >= second)
        return first;
    return second;
}

int minimum (int first, int second)
{
    if (first <= second)
        return first;
    return second;
}

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

int main()
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
        case InsertionSort: insertion_sort(songs, NO_OF_SONGS) ; break ;
        case SelectionSort: selection_sort(songs, NO_OF_SONGS) ; break ;
        case BubbleSort:    bubble_sort   (songs, NO_OF_SONGS) ; break ;
        default:        cout << "Huh?" << endl ;
    }
    cout << "Tracks sorted." << endl;
    //                                      
	return 0;
}

/*
                                    
                                
                                
                                

                                        
                                
                                
                                

                                                                      
                                                                        
                                                                        
                                                                       
                                                                         
                                                                      
                                                                       
                                                                      
                                                                          
                                       

*/


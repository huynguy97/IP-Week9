/*                                                                    
                                              
            
                                                                                                            
                                  
                              
                                                           
                                                                    
                                                          
                                                               
                                                                     */

/*
                                                      
                                                                                                           
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
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
	int    year;                            //                   
	int    track_no;						//             
	string title;                           //            
	string tags;                            //                            
	Length time;							//             
	string country;                         //                                         
};

const int MAX_NO_OF_SONGS = 6000;           //                                
vector<Track> songsvector = {};

int counter = 0;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator<(const Track& a, const Track& b)
{
    counter++;

    if (a.artist == b.artist)
    {
        if (a.cd == b.cd)
        {
            if (a.year == b.year)
            {
                return a.track_no < b.track_no;
            }
            else
                return a.year < b.year;
        }
        else
            return a.cd < b.cd;
    }
    else
        return a.artist < b.artist;
}

bool operator==(const Track& a, const Track& b)
{
    counter++;

    return a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no ;
}

//	                                 
bool operator>(const Track& a, const Track& b)
{
	counter++;

	return b < a ;
}

bool operator<=(const Track& a, const Track& b)
{
	counter++;

	return !(b < a) ;
}

bool operator>=(const Track& a, const Track& b)
{
	counter++;

	return b <= a ;
}

bool operator<(const Length& a, const Length& b)
{
    counter++;

    if (a.minutes != b.minutes)
    {
        return a.minutes < b.minutes;
    }
    else
    {
        return a.seconds < b.seconds;
    }
}

bool operator>(const Length& a, const Length& b)
{
    counter++;

    return b < a;
}

bool operator<=(const Length& a, const Length& b)
{
	counter++;

	return !(b < a) ;
}

bool operator==(const Length& a, const Length& b)
{
    counter++;

    return a.minutes == b.minutes && a.seconds == b.seconds;
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
int read_songs (ifstream& infile, vector<Track>& songsvector)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0 ;
    do {
        Track song ;
        infile >> song ;
        if (infile)
        {
            songsvector.push_back(song);
        }
    }
    while (infile && no_of_read_songs < MAX_NO_OF_SONGS);
    return songsvector.size();
}

int size (vector<Track>& songsvector)
{
    return songsvector.size();
}

int read_file (string filename)
{//               
    assert (size (songsvector) == 0) ;
/*                 
                                                                              
                                                                                             
                                        
*/
    ifstream songsDBS (filename.c_str());
    if (!songsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
	const int NO_OF_SONGS = read_songs (songsDBS, songsvector);
	songsDBS.close();
	cout << " Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

//                                                                           
void show_all_tracks (vector<Track>& songsvector, int no_of_songs)
{//               
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songsvector[i] << endl ;
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

bool is_sorted (vector<Track>& vect, Slice s)
{//	              
	assert (valid_slice(s)) ;	//                           
//	               
//	                 	                                
//						                                
//						   
//						                            
	bool sorted = true ;
	for (int i = s.from; i < s.to && sorted; i++)
		if (vect[i].time > vect[i+1].time)
			sorted = false ;
	return sorted ;
}

int find_position (vector<Track>& vect, Slice s, Track y )
{//	              
	assert (valid_slice(s) && is_sorted(vect,s)) ;    //                           
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y.time <= vect[i].time )
			return i ;
	return s.to+1;
}

void shift_right (vector<Track>& vect, Slice s )
{//	              
	assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
	for ( int i = s.to+1 ; i > s.from ; i-- )
		vect[i]  = vect[i-1] ;
}

void insert (vector<Track>& vect, int& length, Track y )
{//               
    Slice s = mkSlice(0,length-1) ;
    assert (length >= 0 && is_sorted (vect, s)) ;
/*                 
                                                                                     
                                   
*/
	const int POS = find_position (vect, mkSlice (0, length-1), y) ;
	if (POS < length)
		shift_right (vect, mkSlice (POS, length-1)) ;
	vect[POS] = y ;
	length++;
}

void swap (vector<Track>& vect, int  i, int  j)
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const Track HELP = vect [i];
	vect [i] = vect [j];
	vect [j] = HELP;
}

//	                           
void insertion_sort (vector<Track>& vect, int length)
{
	int sorted = 1 ;
    while ( sorted < length )
    {
        insert (vect, sorted, vect[sorted]);
    }
}

//	                           
int smallest_value_at (vector<Track>& vect, Slice s )
{//	              
	assert (valid_slice (s)) ;	//                        
//	                                                            
//	                                               
	int smallest_at = s.from ;
	for ( int index = s.from+1 ; index <= s.to ; index++ )
		if ( vect[index].time < vect[smallest_at].time )
			smallest_at = index ;
	return smallest_at ;
}

void selection_sort (vector<Track>& vect, int length )
{	for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
	{   const int k = smallest_value_at (vect, mkSlice (unsorted, length-1));
	    swap ( vect, unsorted, k ) ;
	}
}

//	                        
bool bubble (vector<Track>& vect, Slice s )
{//	              
	assert (valid_slice(s));	//                          
//	               
//	                                                    
//	                                        
	bool is_sorted = true ;
	for ( int i = s.from ; i < s.to ; i++)
	    if ( vect[i].time > vect[i+1].time)
		{	swap ( vect, i, i+1 ) ;
			is_sorted = false ;
		}
	return is_sorted ;
}

void bubble_sort (vector<Track>& vect, int length )
{
    while ( !bubble ( vect, mkSlice (0, length-1 ) ) )
        length-- ;
}

/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */
enum SortingMethod {InsertionSort,SelectionSort,BubbleSort,NoOfSortingMethods};
string methods [] = {"insertion", "selection", "bubble"} ;

int minimum (int a, int b)
{
    if (a <= b)
        return a;
    else
        return b;
}

int maximum (int a, int b)
{
    if (a >= b)
        return a;
    else
        return b;
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

void print_stars (int counter)
{
    int large = counter / 100000;
    int small = counter % 100000;

    for (int i = 0; i < large; i++)
    {
        cout << "*";
    }
    if (small > 0)
        cout << ".";
    cout << endl << endl;
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
        case InsertionSort: insertion_sort(songsvector,NO_OF_SONGS) ; break ;
        case SelectionSort: selection_sort(songsvector,NO_OF_SONGS) ; break ;
        case BubbleSort:    bubble_sort   (songsvector,NO_OF_SONGS) ; break ;
        default:        cout << "Huh?" << endl ;
    }
    cout << "Tracks sorted." << endl;
    show_all_tracks (songsvector,NO_OF_SONGS) ;

    /*           

                    
     
                                                   
                                          
                                          
                                       
                             
                    
                     
     */

	return 0;
}

/*
                                             
                                             
                                          

                                                                                                       
                                                                                                                       
                                       
*/


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
#include <algorithm>
#include <sstream>
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
Track songs [MAX_NO_OF_SONGS];              //                                     

int number_of_operators;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
/*                                                
 
                            
     
                        
         
                                
             
                                            
                 
                                 
                 
                    
                 
                                                   
                 
             
                
             
                                       
             
         
            
         
                               
         
     
        
     
                                    
     
 
*/
/*
                                               
 
                                                                                                
 */
bool operator<(const Track& a, const Track& b)
{
    number_of_operators++;
    if(a.time.minutes == b.time.minutes)
    {
        if(a.time.seconds == b.time.seconds)
        {
            if(a.artist == b.artist)
            {
                if(a.title == b.title)
                {
                    if(a.cd == b.cd)
                    {
                        return false;
                    }
                    else
                    {
                        return a.cd < b.cd;
                    }
                }
                else
                {
                    return a.title < b.title;
                }
            }
            else
            {
                return a.artist < b.artist;
            }
        }
        else
        {
            return a.time.seconds < b.time.seconds;
        }
    }
    else
    {
        return a.time.minutes < b.time.minutes ;
    }
}

bool operator==(const Track& a, const Track& b)
{
    number_of_operators++;
    return a.time.minutes == b.time.minutes && a.time.seconds == b.time.seconds && a.artist == b.artist && a.title == b.title && a.cd == b.cd;
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

istream& operator>> (istream& in, Track& track)
{//               
    assert (true) ;
/*                 
                                                                                                                   
                                      
*/
    string linebreak;
    getline(in, linebreak);
    if (linebreak.empty()) {
        getline(in, track.artist);
        if (track.artist.empty()) {
            return in;
        }
    } else {
        track.artist = linebreak;
    }
    getline(in, track.cd);
    string yearstring;
    getline(in, yearstring);
    track.year = stoi(yearstring);
    string tracknumstring;
    getline(in, tracknumstring);
    track.title = stoi(tracknumstring);
    getline(in, track.title);
    getline(in, track.tags);
    Length length;
    string l;
    stringstream ss;
    getline(in, l);
    ss << l;
    ss >> length;
    track.time = length;
    getline(in, track.country);
    return in;
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
int read_songs (ifstream& infile, vector<Track>&songs)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    Track track;
    int count = 0;
    while (infile >> track) {
        count++;
        songs.push_back(track);
    }
    return count;
}

int read_file (string filename, vector<Track>&songs)
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

//                                                                           
void show_all_tracks (vector <Track>& track_vector, int no_of_songs)
{//               
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << track_vector[i] << endl ;
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

typedef int El ;                //                                                       

bool is_sorted (vector <Track>& track_vector, Slice s)
{//	              
	assert (valid_slice(s)) ;	//                           
//	               
//	                 	                                
//						                                
//						   
//						                            
	bool sorted = true ;
	for (int i = s.from; i < s.to && sorted; i++)
		if (track_vector[i] > track_vector[i+1])
			sorted = false ;
	return sorted ;
}

int find_position ( vector <Track>& track_vector, Slice s, Track y )
{//	              
	assert (valid_slice(s) && is_sorted(track_vector,s)) ;    //                           
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= track_vector [i] )
			return i ;
	return s.to+1;
}

void shift_right ( vector <Track>& track_vector, Slice s )
{//	              
	assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
	for ( int i = s.to+1 ; i > s.from ; i-- )
		track_vector [i]  = track_vector [i-1] ;
}

void insert ( vector <Track>& total_songs, int& length, Track y )

{//               

    Slice s = mkSlice(0,length-1) ;

    assert (length >= 0 && is_sorted (total_songs, s)) ;
/*                 
                                                                                     
                                   
*/
    const int POS = find_position (total_songs, mkSlice (0, length-1), y) ;
    if (POS < length)
        shift_right ( total_songs, mkSlice (POS, length-1) ) ;
    total_songs [POS] = y ;
    length++;

}

void swap (vector <Track>& track_vector, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const Track HELP = track_vector [i];
	track_vector [i] = track_vector [j] ;
	track_vector [j] = HELP;
}

//	                           
void insertion_sort (vector<Track>& track_vector, int length )
{
	int sorted = 1 ;
    while ( sorted < length )
    {   insert ( track_vector, sorted, track_vector[sorted] ) ;
    }
}

//	                           
int smallest_value_at ( vector<Track>& track_vector, Slice s )
{//	              
	assert (valid_slice (s)) ;	//                        
//	                                                            
//	                                               
	int smallest_at = s.from ;
	for ( int index = s.from+1 ; index <= s.to ; index++ )
		if ( track_vector [index] < track_vector [smallest_at] )
			smallest_at = index ;
	return smallest_at ;
}

void selection_sort ( vector <Track>& track_vector, int length )
{	for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
	{   const int k = smallest_value_at (track_vector, mkSlice (unsorted, length-1));
	    swap ( track_vector, unsorted, k ) ;
	}
}

//	                        
bool bubble ( vector<Track>& track_vector, Slice s )
{//	              
	assert (valid_slice(s));	//                          
//	               
//	                                                    
//	                                        
	bool is_sorted = true ;
	for ( int i = s.from ; i < s.to ; i++)
	    if ( track_vector [i] > track_vector [i+1])
		{	swap ( track_vector, i, i+1 ) ;
			is_sorted = false ;
		}
	return is_sorted ;
}

void bubble_sort ( vector<Track>& track_vector, int length )
{
    while ( !bubble ( track_vector, mkSlice (0, length-1 ) ) )
        length-- ;
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
    choice = max (1, min (choice, static_cast<int>(NoOfSortingMethods))) ;
    return static_cast<SortingMethod>(choice-1) ;
}

void visualize_comparisions(vector<Track>& track_vector)
{
    ofstream output_file;
    output_file.open("results.txt");

    for(int i = 100; i < 5800; i = i + 100)
    {
        number_of_operators = 0;
        insertion_sort(track_vector, i);
        while (number_of_operators - 100000 >= 0)
        {
            output_file << "*";
            number_of_operators = number_of_operators - 100000;
        }
        if (number_of_operators !=0)
        output_file << "." << endl;
    }
    output_file.close();
}

int main()
{
    number_of_operators = 0;
    vector<Track> track_vector;
	const int NO_OF_SONGS = read_file ("Tracks.txt", track_vector);

	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }

    SortingMethod m = get_sorting_method () ;
    cout << "Sorting tracks with " << methods[m] << " sort" << endl;
    switch (m)
    {
        case InsertionSort: insertion_sort(track_vector,NO_OF_SONGS) ; break ;
        case SelectionSort: selection_sort(track_vector,NO_OF_SONGS) ; break ;
        case BubbleSort:    bubble_sort   (track_vector,NO_OF_SONGS) ; break ;
        default:        cout << "Huh?" << endl ;
    }
    //                                            
    cout << "Tracks sorted." << endl;
    cout << "Number of operators used: " << number_of_operators << endl;
    visualize_comparisions(track_vector);
	return 0;
}
/*
                                                           
                                                           
                                                        
                                                                                                                                      
*/


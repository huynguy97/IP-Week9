//                              
//                                

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

//                                                                               
//                                                                                    
vector<Track> songs;
int comparisons_count = 0;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */

bool operator< (const Length& a, const Length& b)
{
//                                                                                     
//                                                                                
    return a.minutes * 60 + a.seconds < b.minutes * 60 + b.seconds;
}

bool operator== (const Length&a, const Length& b)
{
    return a.minutes * 60 + a.seconds == b.minutes * 60 + b.seconds;
}

bool operator<(const Track& a, const Track& b)
{
    comparisons_count++;
    if (a.time < b.time)
        return true;
    else if (a.time == b.time)
    {
        if (a.artist < b.artist)
            return true;
        else if (a.artist == b.artist)
        {
            if (a.cd < b.cd)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

bool operator==(const Track& a, const Track& b)
{
    comparisons_count++;
    return a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no;   //                                                
}

/*       
                                              
 
                        
                            
                    
                                  
     
                        
                        
                              
         
                                
                            
                                      
             
                                            
                                
                    
                                 
             
                
                             
         
            
                         
     
        
                     
 

                                               
 
                        
                                                                                                                                                     
 
*/

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

int size (vector<Track>& v)
{
    return static_cast<int> (v.size());
}

//                                                                           
int read_songs (ifstream& infile, vector<Track>& songs)
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
            songs.push_back(song);
            no_of_read_songs++;
        }
    }
    while (infile);
    return no_of_read_songs ;
}

int read_file (string filename)
{//               
    assert (size (songs) == 0) ;
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
void show_all_tracks (vector<Track>& songs, int no_of_songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
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

//                                                                                          

bool is_sorted (vector<Track>& songs, Slice s)
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

int find_position (vector<Track>& songs, Slice s, Track y )
{//	              
	assert (valid_slice(s) && is_sorted(songs,s)) ;    //                           
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= songs [i] )
			return i ;
	return s.to+1;
}

void shift_right (vector<Track>& songs, Slice s )
{//	              
	assert (valid_slice (s)) ;	//                               
//	                                	  	                 
//			    	                	  	                   
//						   
//			    	              		  	               
	for ( int i = s.to+1 ; i > s.from ; i-- )
		songs [i]  = songs [i-1] ;
}

void insert (vector<Track>& songs, int& length, Track y )
{//               
    Slice s = mkSlice(0,length-1) ;
    assert (length >= 0 && is_sorted (songs, s)) ;
/*                 
                                                                                       
                                   
*/
	const int POS = find_position (songs, mkSlice (0, length-1), y) ;
	if (POS < length)
		shift_right ( songs, mkSlice (POS, length-1) ) ;
	songs [POS] = y ;
	length++;
}

void swap (vector<Track>& songs, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                    
	const Track HELP = songs [i];
	songs [i] = songs [j] ;
	songs [j] = HELP;
}

//	                           
void insertion_sort (vector<Track>& songs, int length )
{
	int sorted = 1 ;
    while ( sorted < length )
    {   insert ( songs, sorted, songs[sorted] ) ;
    }
}

//	                           
int smallest_value_at (vector<Track>& songs, Slice s )
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

void selection_sort (vector<Track>& songs, int length )
{
    for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
	{   const int k = smallest_value_at (songs, mkSlice (unsorted, length-1));
	    swap ( songs, unsorted, k ) ;
	}
}

//	                        
bool bubble (vector<Track>& songs, Slice s )
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
	return is_sorted ;
}

void bubble_sort (vector<Track>& songs, int length )
{
    while ( !bubble ( songs, mkSlice (0, length-1 ) ) )
    {
        length-- ;
    }
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
    choice = max (1, min (choice, static_cast<int>(NoOfSortingMethods)));
    return static_cast<SortingMethod>(choice-1) ;
}

//       
void show_comparisons (SortingMethod m)
{
    //                
    assert(true);

    vector<Track> test = songs;

    //                 
    //
    for (int i = 99; i < 5800; i += 100)
    {
        switch (m)
        {
            case InsertionSort: insertion_sort(test,i) ; break ;
            case SelectionSort: selection_sort(test,i) ; break ;
            case BubbleSort:    bubble_sort   (test,i) ; break ;
            default:        cout << "Huh?" << endl ;
        }

        //                      
        while (comparisons_count > 100000)
        {
            cout << "*";
            comparisons_count -= 100000;
        }
        if (comparisons_count > 0)
            cout << "." << endl;

        comparisons_count = 0;
    }
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

    /*
      
              
     
                                                                       
                                                                       
                                                                       
                                                
     
                                     
                                            
                                                                   

     */

    show_comparisons(m);
	return 0;
}

/*
            
          
                                                                                                        
                                                                                                                                                                                                              
  
                                                                                                                                 
  
          
  
 */


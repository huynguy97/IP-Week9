#define NDEBUG
/*                                                                    
                                              
            
                                                                                                            
                                  
                              
                                                           
                                                                    
                                                          
                                                               
                                                                     */
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

const int MAX_NO_OF_SONGS = 6000;           //                                
//                                                                                          
vector<Track> songs;

int size (vector<Track> vec) { return vec.size(); }

int less_count = 0;
int equal_count = 0;

void reset_counters()
{//              
    assert(true);
/*                
                        */
    less_count = 0;
    equal_count = 0;
}

void show_counters ()
{//              
    assert(true);
/*                
                                                      */
    cout << "counters: less:" << less_count << "\tequal:" << equal_count << endl;
}

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator==(const Length& a, const Length& b)
{//              
    assert(true);
/*                
                                                              */
    bool are_equal = false;
    if (a.minutes == b.minutes)
        if (a.seconds == b.seconds)
            are_equal = true;
    return are_equal;
}

bool operator<(const Length& a, const Length& b)
{//              
    assert(true);
/*                
                                       */
    if (a.minutes == b.minutes)
        return a.seconds < b.seconds;
    return a.minutes < b.minutes;
}

bool operator<(const Track& a, const Track& b)
{//              
    assert(true);
/*                
                                                                   */
    less_count++;
    if (a.artist == b.artist) {
        if (a.cd == b.cd) {
            if((int)a.year == (int)b.year) {
                if( (int) a.track_no == (int) b.track_no) {
                    if (a.title == b.title) {
                        if (a.tags == b.tags) {
                            if (a.time == b.time) {
                                return a.country < b.country;
                            }
                            return a.time < b.time;
                        }
                        return a.tags < b.tags;
                    }
                    return a.title < b.title;
                }
                return (int) a.track_no < (int) b.track_no;
            }
            return (int) a.year < (int) b.year;
        }
        return a.cd < b.cd;
    }
    return a.artist < b.artist ;    /*                                                 */
}

bool operator==(const Track& a, const Track& b)
{//              
    assert(true);
/*                
                                                                 */
    equal_count++;
    bool are_equal = false;
    if (a.artist == b.artist)
        if (a.cd == b.cd)
            if((int)a.year == (int)b.year)
                if( (int) a.track_no == (int) b.track_no)
                    if (a.title == b.title)
                        if (a.tags == b.tags)
                            if (a.time == b.time)
                                if (a.country == b.country)
                                    are_equal = true;
    return are_equal ;   /*                                                 */
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
int read_songs (ifstream& infile, vector<Track>& songs )
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    do {
        Track song ;
        infile >> song ;
        if (infile)
            songs.push_back(song) ;
    }
    while (infile && songs.size() < MAX_NO_OF_SONGS);
    return songs.size() ;
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
    //                                                
	const int NO_OF_SONGS = read_songs (songsDBS, songs);
	songsDBS.close();
	//                                                      
	return NO_OF_SONGS;
}

//                                                                                   
void show_all_tracks (vector<Track> songs)
{//               
    assert (songs.size() < MAX_NO_OF_SONGS) ;
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

typedef Track El ;                //                                                       

bool is_sorted ( vector<El>& data , Slice s)
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

int find_position ( vector<El>& data, Slice s, El y )
{//	              
	assert (valid_slice(s) && is_sorted(data,s)) ;    //                           
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= data [i] )
			return i ;
	return s.to+1;
}

void shift_right ( vector<El>& data, Slice s )
{//	              
	assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
	for ( int i = s.to+1 ; i > s.from ; i-- )
		data [i]  = data [i-1] ;
}

void insert ( vector<El>& data, int& length, El y )
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

void swap ( vector<El>& data, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const El HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

//	                            
void insertion_sort ( vector<El>& data, int length )
{
    reset_counters();
	int sorted = 1 ;
    while ( sorted < length )
    {   insert ( data, sorted, data[sorted] ) ;
    }
}

//	                            
int smallest_value_at ( vector<El>& data, Slice s )
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

void selection_sort ( vector<El>& data, int length )
{
    reset_counters();
    for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
	{   const int k = smallest_value_at (data, mkSlice (unsorted, length-1));
	    swap ( data, unsorted, k ) ;
	}
}

//	                        
bool bubble ( vector<El> &data, Slice s )
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

void bubble_sort ( vector<El> &data, int length )
{
    reset_counters();
    while ( !bubble ( data, mkSlice (0, length-1 ) ) )
        length-- ;
}

/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */
enum SortingMethod {InsertionSort,SelectionSort,BubbleSort,NoOfSortingMethods};
string methods [] = {"insertion", "selection", "bubble"} ;

//             
int minimum (int a, int b)
{ //              
    assert(true);
  //              
  /*                                                           */
    if (a <= b)
        return a;
    return b;
}
int maximum (int a, int b)
{ //              
    assert(true);
  //              
  /*                                                           */
    if(a < b)
        return b;
    return a;
}
//             

SortingMethod get_sorting_method ()
{
    cout << "What sorting method do you want to use? " << endl ;
    for (int m = 0; m < NoOfSortingMethods; m++)
        cout << m+1 << ": " << methods[m] << " sort" << endl ;
    int choice ;
    cin >> choice ;
    choice = maximum (1, minimum (choice, NoOfSortingMethods)) ; //                                                               
    return static_cast<SortingMethod>(choice-1) ;
}

void count_slice (vector<El> &data, SortingMethod m, int length)
{//              
    assert(length >= 0 && data.size() >= length);
/*                
                                                                                                                      */
    switch (m)
    {
        case InsertionSort: insertion_sort(songs,length) ; break ;
        case SelectionSort: selection_sort(songs,length) ; break ;
        case BubbleSort:    bubble_sort   (songs,length) ; break ;
    }

    cout << "total count:" << less_count + equal_count << " length:" << length << endl;
    for (int i = less_count + equal_count; i >= 100000; i-= 100000)
        cout << '*';
    if (less_count + equal_count % 100000 != 0)
        cout << '.';
    cout << endl;
    reset_counters();
}

void part5()
{//              
    assert(true);
/*                
                                                                                     */
    for(int i = 0; i<NoOfSortingMethods; i++)
    {
        SortingMethod method = static_cast<SortingMethod>(i);
        cout << "Method: " << methods[i] << endl;
        for(int i = 100; i <= 5800; i+= 100)
        {
            read_file("Tracks.txt");
            count_slice(songs, method, i-1);
        }
    }
}

int main()
{
    part5();
    /*
                 
	                                                 
	                    
	 
                                                                   
	                       
     
                                             
                                                                    
              
     
                                                                       
                                                                       
                                                                       
                                                
     
                                     
                    
                    
                                  
	         
 

  
                                                                                               
                                                                                                                               
                                             
                                             
                                           

         
                                                      
                                                      
                                                                           

           
                 
                          
 
                            
 
                            
 
                            
 
                             
  
                             
  
                             
   
                             
    
                             
     
                             
     
                              
       
                              
        
                              
         
                              
          
                               
            
                               
             
                               
               
                               
                 
                               
                   
                               
                    
                               
                       
                               
                         
                               
                           
                               
                             
                               
                                
                               
                                  
                               
                                     
                               
                                        
                               
                                           
                               
                                             
                               
                                                 
                               
                                                    
                               
                                                       
                               
                                                          
                               
                                                              
                               
                                                                 
                               
                                                                     
                               
                                                                         
                               
                                                                            
                               
                                                                                
                               
                                                                                    
                               
                                                                                         
                               
                                                                                             
                               
                                                                                                 
                                
                                                                                                      
                                
                                                                                                          
                                
                                                                                                               
                                
                                                                                                                    
                                
                                                                                                                        
                                
                                                                                                                             
                                
                                                                                                                                  
                                
                                                                                                                                        
                                
                                                                                                                                             
                                
                                                                                                                                                  
                                
                                                                                                                                                        
                                
                                                                                                                                                             
                                
                                                                                                                                                                   
                                
                                                                                                                                                                         
                 
                          
 
                            
 
                            
 
                            
 
                             
  
                             
  
                             
   
                             
    
                             
     
                             
     
                              
       
                              
        
                              
         
                              
          
                               
            
                               
             
                               
               
                               
                 
                               
                   
                               
                    
                               
                       
                               
                         
                               
                           
                               
                             
                               
                                
                               
                                  
                               
                                     
                               
                                        
                               
                                           
                               
                                             
                               
                                                 
                               
                                                    
                               
                                                       
                               
                                                          
                               
                                                              
                               
                                                                 
                               
                                                                     
                               
                                                                         
                               
                                                                            
                               
                                                                                
                               
                                                                                    
                               
                                                                                         
                               
                                                                                             
                               
                                                                                                 
                                
                                                                                                      
                                
                                                                                                          
                                
                                                                                                               
                                
                                                                                                                    
                                
                                                                                                                        
                                
                                                                                                                             
                                
                                                                                                                                  
                                
                                                                                                                                        
                                
                                                                                                                                             
                                
                                                                                                                                                  
                                
                                                                                                                                                        
                                
                                                                                                                                                             
                                
                                                                                                                                                                   
                                
                                                                                                                                                                         
              
                        
 
                          
 
                          
 
                          
 
                          
 
                          
 
                          
 
                          
 
                          
 
                          
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
                            
 
*/


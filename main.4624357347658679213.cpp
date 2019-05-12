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

/* 
                             
                             
 */

using namespace std;
int cmp_count = 0;

/*                                                                    
                                            
                                                                     */
struct Length
{
	int minutes;							//               
	int seconds;
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

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
operator < (const Length& lhs, const Length& rhs){
    //              
    assert(true);
    //               
    //                                                                                     
    return
        lhs.minutes < rhs.minutes ? true  :(
        lhs.minutes > rhs.minutes ? false :(
        lhs.seconds < rhs.seconds ));
}
operator > (const Length& lhs, const Length& rhs){
    //              
    assert(true);
    //               
    //                                                                                     
    return rhs < lhs;
}

operator == (const Length& lhs, const Length& rhs){
    //               
        assert(true);
    //                                       
    return !(lhs < rhs || rhs < lhs);
}
bool operator<(const Track& a, const Track& b)
{
    //               
        assert(true);
    //                                      
    cmp_count++;
    return
       a.artist   < b.artist   ? true  :(
       a.artist   > b.artist   ? false :(
       a.cd       < b.cd       ? true  :(
       a.cd       > b.cd       ? false :(
       a.year     < b.year     ? true  :(
       a.year     > b.year     ? false :(
       a.track_no < b.track_no ? true  :(
       a.track_no > b.track_no ? false :(
       a.title    < b.title    ? true  :(
       a.title    > b.title    ? false :(
       a.tags     < b.tags     ? true  :(
       a.tags     > b.tags     ? false :(
       a.time     < b.time     ? true  :(
       a.time     > b.time     ? false :(
       a.country  < b.country  ))))))))))))));
}

bool operator==(const Track& a, const Track& b)
{
    //               
        assert(true);
    //                                                                             
    cmp_count++;
    return a.artist   == b.artist   &&
           a.cd       == b.cd       &&
           a.year     == b.year     &&
           a.track_no == b.track_no &&
           a.title    == b.title    &&
           a.tags     == b.tags     &&
           a.time     == b.time     &&
           a.country  == b.country  ;
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
int read_songs (ifstream& infile, Track songs [MAX_NO_OF_SONGS])
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0 ;
    do {
        Track song ;
        infile >> song ;
        if (infile)
            songs[no_of_read_songs++] = song ;
    }
    while (infile && no_of_read_songs < MAX_NO_OF_SONGS);
    return no_of_read_songs ;
}

int read_file (string filename)
{//               
//                                
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
void show_all_tracks (Track songs [MAX_NO_OF_SONGS], int no_of_songs)
{//               
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
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

typedef Track El ;                //                                                       

bool is_sorted (El data [], Slice s)
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

int find_position ( El data [], Slice s, El y )
{//	              
	assert (valid_slice(s) && is_sorted(data,s)) ;    //                           
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= data [i] )
			return i ;
	return s.to+1;
}

void shift_right ( El data [], Slice s )
{//	              
	assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
	for ( int i = s.to+1 ; i > s.from ; i-- )
		data [i]  = data [i-1] ;
}

void insert ( El data [], int& length, El y )
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

void swap (El data [], int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const El HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

//	                           
void insertion_sort ( El data [], int length )
{
    cmp_count = 0;
	int sorted = 1 ;
    while ( sorted < length )
    {
        insert ( data, sorted, data[sorted] ) ;
    }
}

//	                           
int smallest_value_at ( El data [], Slice s )
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

void selection_sort ( El data [], int length )
{
    cmp_count = 0;
    for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
	{   const int k = smallest_value_at (data, mkSlice (unsorted, length-1));
	    swap ( data, unsorted, k ) ;
	}
}

//	                        
bool bubble ( El data [], Slice s )
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

void bubble_sort ( El data [], int length )
{
    cmp_count = 0;
    while ( !bubble ( data, mkSlice (0, length-1 ) ) )
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
    //                                                            
    choice = choice < 1 ? 1 : choice;
    choice = choice >= NoOfSortingMethods  ? NoOfSortingMethods - 1 : choice;
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
        case InsertionSort:
            for(int i = 99; i < 5800; i+= 100){
                insertion_sort(songs, i);
                int star_count = cmp_count / 100000;
                int remainder = cmp_count % 100000;
                for(int i = 0; i < star_count; i++)
                    cout << '*';
                if(remainder)
                    cout << '.';
                cout << endl;
            }
            break ;
        case SelectionSort:
            for(int i = 99; i < 5800; i+= 100){
                selection_sort(songs, i) ;
                int star_count = cmp_count / 100000;
                int remainder = cmp_count % 100000;
                for(int i = 0; i < star_count; i++)
                    cout << '*';
                if(remainder)
                    cout << '.';
                cout << endl;
            }
            break ;
        case BubbleSort:
            for(int i = 99; i < 5800; i+= 100){
                bubble_sort(songs, i) ;
                int star_count = cmp_count / 100000;
                int remainder = cmp_count % 100000;
                for(int i = 0; i < star_count; i++)
                    cout << '*';
                if(remainder)
                    cout << '.';
                cout << endl;
            }
            break ;
        default:        cout << "Huh?" << endl ;
    }
    cout << "Tracks sorted." << endl;
    //                                     

	return 0;
}


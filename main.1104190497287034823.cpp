/*                                                                    
                                              
            
                                                                                                            
                                  
                              
                                                           
                                                                    
                                                          
                                                               
                                                                     */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

//                                                     

using namespace std;
int total_performed = 0;
int previous_performed = 0;

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

const int MAX_NO_OF_SONGS = 5891;           //                                

vector <Track> songs;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator< (const Length& a, const Length& b)
{
    total_performed++;
    return ((a.minutes * 60)+ a.seconds) < ((b.minutes * 60) + b.seconds);
}

bool operator== (const Length& a, const Length& b)
{
    total_performed++;
    return (a.minutes == b.minutes &&
            a.seconds == b.seconds
           );
}

//      
/*
                                              
 
                      
                            
                        
                                
                                                
                
                                        
            
                                
        
                                    
 
*/

//       

bool operator<(const Track& a, const Track& b)
{
    total_performed++;
    if(a.time == b.time)
        if(a.artist == b.artist)
            if(a.title == b.title)
               return a.cd == b.cd ;
           else return a.title < b.title ;
        else return a.artist < b.artist ;
    else return a.time < b.time ;
}

bool operator==(const Track& a, const Track& b)
{
    total_performed++;
    return (a.artist == b.artist &&
            a.cd == b.cd &&
            a.year == b.year);
}

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
{
    //               
    assert (true) ;
    /*                 
                                                                                                          
    */
    char colon ;
    in >> length.minutes >> colon >> length.seconds ;
    return in ;
}

ostream& operator<< (ostream& out, const Length length)
{
    //               
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
{
    //               
    assert (true) ;
    /*                 
                                                                            
    */
    string remains ;
    getline (infile, remains) ;
}

istream& operator>> (istream& infile, Track& track)
{
    //               
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
{
    //               
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
int read_songs (ifstream& in)
{
    //               
    assert (in.is_open ()) ;
    /*                 
                                                                                  
                                                               
    */
    int no_of_read_songs = 0 ;
    while(in)
    {
        Track track = {};
        in >> track;
        songs.push_back(track);
        no_of_read_songs ++;
    }

    songs.pop_back();
    no_of_read_songs--;

    return no_of_read_songs ;
}

int read_file (string filename)
{
    //               
    assert (true) ;
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
    const int NO_OF_SONGS = read_songs (songsDBS);
    songsDBS.close();
    cout << " Read " << NO_OF_SONGS << " tracks." << endl;
    return NO_OF_SONGS;
}

//                                                                           
void show_all_tracks (int no_of_songs)
{
    //               
    assert (true) ;
    /*                 
                                                                      
    */
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

/*                                                                       
                                                         
                                                                       */
void visualize ()
{
    //            
    assert(true);
    //             
    //                                                            
    previous_performed += total_performed;

    while ((total_performed + previous_performed) >= 100000)
    {
        total_performed -= 100000;
        cout << "*"  ;
    }
    cout << "." << endl;
    total_performed = 0;
}

struct Slice
{
    int from ; 	//             
    int to ; 	//           
} ;

Slice mkSlice (int from, int to)
{
    //	              
    assert (0 <= from && from <= to);
    /*                 
                                                  
    */	Slice s = { from, to } ;

    return s ;
}

bool valid_slice (Slice s)
{
    //               
    assert (true) ;
    /*                 
                                                                                          
    */
    return 0 <= s.from && s.from <= s.to ;
}

typedef Track El;                //                                                       

bool is_sorted (Slice s)
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
        if (songs[i] > songs[i+1])
            sorted = false ;
    return sorted ;
}

int find_position (Slice s, El y )
{
    //	              
    assert (valid_slice(s) && is_sorted(s)) ;    //                           
//	                                          
    for ( int i = s.from ; i <= s.to ; i++ )
        if ( y <= songs[i] )
            return i ;
    return s.to+1;
}

void shift_right (Slice s )
{
    //	              
    assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
    for ( int i = s.to+1 ; i > s.from ; i-- )
        songs [i]  = songs [i-1] ;
}

void insert (int& length, El y )
{
    //               
    Slice s = mkSlice(0,length-1) ;
    assert (length >= 0 && is_sorted (s)) ;
    /*                 
                                                                                         
                                       
    */
    const int POS = find_position (mkSlice (0, length-1), y) ;
    if (POS < length)
        shift_right (mkSlice (POS, length-1) ) ;
    songs [POS]= y ;
    if (length%100 == 0)
        visualize();
    length++;
}

void swap (int  i, int  j )
{
    //	              
    assert ( i >= 0 && j >= 0 ) ;	//                         
    //                         
//                                                                
    const El HELP = songs [i];
    songs [i] = songs [j] ;
    songs [j] = HELP;
}

//	                           
void insertion_sort (int length )
{
    int sorted = 1 ;
    while ( sorted < length )
    {
        insert (sorted, songs[sorted] );
    }
}

//	                           
int smallest_value_at (Slice s )
{
    //	              
    assert (valid_slice (s)) ;	//                        
//	                                                            
//	                                               
    int smallest_at = s.from ;
    for ( int index = s.from+1 ; index <= s.to ; index++ )
        if ( songs [index] < songs [smallest_at] )
            smallest_at = index ;
    return smallest_at ;
}

void selection_sort (int length )
{
    for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
    {
        const int k = smallest_value_at (mkSlice (unsorted, length-1));
        swap (unsorted, k ) ;
        if (unsorted%100 == 0)
            visualize();
    }
}

//	                        
bool bubble (Slice s )
{
    //	              
    assert (valid_slice(s));	//                          
//	               
//	                                                    
//	                                        
    bool is_sorted = true ;
    for ( int i = s.from ; i < s.to ; i++)
    {
        if ( songs [i] > songs [i+1])
        {
            swap ( i, i+1 ) ;
            is_sorted = false ;
        }

        if ((MAX_NO_OF_SONGS - s.to)%100 == 0)
        {
            visualize();
        }
    }
    return is_sorted ;
}

void bubble_sort (int length )
{
    while ( !bubble (mkSlice (0, length-1 ) ) )
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
//                                                               
    return static_cast<SortingMethod>(choice-1) ;
}

int main()
{
    string infile;
    cout << "Please enter a file (.txt): ";
    getline (cin, infile);
    int NO_OF_SONGS = read_file (infile);

//                                                    
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
        insertion_sort(NO_OF_SONGS) ;
        break ;
    case SelectionSort:
        selection_sort(NO_OF_SONGS) ;
        break ;
    case BubbleSort:
        bubble_sort   (NO_OF_SONGS) ;
        break ;
    default:
        cout << "Huh?" << endl ;
    }
    cout << "Tracks sorted." << endl;
//                                  
    return 0;
}

/*
                                                          
                         
                         
                   
                                                             
                                                                          

                                                    
                          
                         
                      
                                                                                          
                         
*/


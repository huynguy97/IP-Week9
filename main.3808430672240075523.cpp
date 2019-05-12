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

vector<Track> vdata;
const int MAX_NO_OF_SONGS = 6000;
/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator<(const Track& a, const Track& b)
{

    if
    (a.artist == b.artist)
    {
        if (a.cd == b.cd)
        {
            if (a.year == b.year)
            {
                return a.track_no < b.track_no ;
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
    if
    (a.artist == b.artist)
    {
        if (a.cd == b.cd)
        {
            if (a.year == b.year)
            {
                return a.track_no == b.track_no ;
            }
            else
                return a.year == b.year;
        }
        else
            return a.cd == b.cd;

    }
    return a.artist == b.artist ;   /*                                                 */
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
int read_songs (ifstream& infile, vector<Track>& vdata)
{
    //               
    assert (infile.is_open ()) ;
    /*                 
                                                                                  
                                                               
    */
    int no_of_read_songs = 0 ;
    do
    {
        Track song ;
        infile >> song ;
        if (infile)
            vdata.push_back(song);
            no_of_read_songs++;
    }
    while (infile);
    return no_of_read_songs ;
}

int read_file (string filename)
{
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
    const int NO_OF_SONGS = read_songs (songsDBS, vdata );
    songsDBS.close();
    cout << " Read " << NO_OF_SONGS << " tracks." << endl;
    return NO_OF_SONGS;
}

//                                                                           
void show_all_tracks (vector<Track>& vdata, int no_of_songs)
{
    //               
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
    /*                 
                                                                      
    */
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << vdata[i] << endl ;
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

typedef int El ;                //                                                       

bool is_sorted (vector<Track>& vdata, Slice s)
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
        if (vdata[i]  > vdata[i+1])
            sorted = false ;
    return sorted ;
}

int find_position (vector<Track>& vdata, Slice s, Track x)
{
    //	              
    assert (valid_slice(s) && is_sorted(vdata,s)) ;    //                           
//	                                          
    for ( int i = s.from ; i <= s.to ; i++ )
        if ( x <= vdata[i] )
            return i ;
    return s.to+1;
}

void shift_right (vector<Track>& vdata, Slice s )
{
    //	              
    assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
cout << "yes3";
    for ( int i = s.to+1 ; i > s.from ; i-- )
        vdata [i]  = vdata [i-1] ;
}

void insert (vector<Track>& vdata, int& length, Track x)
{
    //               
    Slice s = mkSlice(0,length-1) ;
    cout << "yes2";
    assert (length >= 0 && is_sorted (vdata, s)) ;
    /*                 
                                                                                         
                                       
    */
    cout << "yes1";
    const int POS = find_position (vdata, mkSlice (0, length-1), x) ;
    if (POS < length)
        shift_right (vdata, mkSlice (POS, length-1) ) ;
    vdata [POS] = x ;
    length++;
}

void swap (vector<Track>& vdata, int  i, int  j )
{
    //	              
    assert ( i >= 0 && j >= 0 ) ;	//                         
    //                         
//                                                                
    const Track HELP = vdata [i];
    vdata [i] = vdata [j] ;
    vdata [j] = HELP;
}

//	                           
void insertion_sort (vector<Track>& vdata, int length )
{
    int sorted = 1 ;

    cout << sorted << endl;
    cout << length << endl;
    while ( sorted < length )
    {
        cout << "yes4" << endl;
        cout << vdata [sorted] << endl;
        insert ( vdata, sorted, vdata[sorted] ) ;
    }
}

//	                           
int smallest_value_at (vector<Track> vdata, Slice s )
{
    //	              
    assert (valid_slice (s)) ;	//                        
//	                                                            
//	                                               
    int smallest_at = s.from ;
    for ( int index = s.from+1 ; index <= s.to ; index++ )
        if ( vdata [index] < vdata [smallest_at] )
            smallest_at = index ;
    return smallest_at ;
}

void selection_sort (vector<Track> vdata, int length )
{
    for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
    {
        const int k = smallest_value_at (vdata, mkSlice (unsorted, length-1));
        swap ( vdata, unsorted, k ) ;
    }
}

//	                        
bool bubble (vector<Track> vdata, Slice s )
{
    //	              
    assert (valid_slice(s));	//                          
//	               
//	                                                    
//	                                        
    bool is_sorted = true ;
    for ( int i = s.from ; i < s.to ; i++)
        if ( vdata [i] > vdata [i+1])
        {
            swap ( vdata, i, i+1 ) ;
            is_sorted = false ;
        }
    return is_sorted ;
}

void bubble_sort (vector<Track> vdata, int length )
{
    while ( !bubble ( vdata, mkSlice (0, length-1 ) ) )
        length-- ;
}

int maximum (int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

int minimum (int a, int b)
{
    if (a > b)
    {
        return b;
    }
    return a;
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
        insertion_sort(vdata,NO_OF_SONGS) ;
        break ;
    case SelectionSort:
        selection_sort(vdata,NO_OF_SONGS) ;
        break ;
    case BubbleSort:
        bubble_sort   (vdata,NO_OF_SONGS) ;
        break ;
    default:
        cout << "Huh?" << endl ;
    }
    cout << "Tracks sorted." << endl;
    show_all_tracks (vdata, NO_OF_SONGS) ;
    return 0;
}


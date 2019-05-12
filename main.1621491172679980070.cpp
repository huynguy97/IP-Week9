/*                                                                    
                                              
            
                                                                                                            
                                  
                              
                                                           
                                                                    
                                                          
                                                               
                                                                     */
//              
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

int comparisons;
bool sortByLength = true;

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
vector<Track> songs;              //                                     

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator < (const Length& a, const Length& b)
{
    return ((b.minutes * 60 + b.seconds) > (a.minutes * 60 + a.seconds));
}

bool operator == (const Length& a, const Length& b)
{
    return ((a.minutes * 60 + a.seconds) == (b.minutes * 60 + b.seconds));
}

bool operator<(const Track& a, const Track& b)
{
    comparisons ++;
    if (sortByLength)
    {
        if (a.time == b.time)
        {
            if (a.artist == b.artist)
            {
                if (a.title == b.title)
                {
                    return ( a.cd < b.cd );
                }
                return a.title < b.title;
            }
            return a.artist < b.artist;
        }
        return a.time < b.time;
    }
    else
    {
        /*
                                                                                                          
                                                                                                                   
                                                                                                                          
                                                                                                                                   
                                                                                                                                         
        */
        if (a.artist == b.artist)
        {
            if (a.year == b.year )
            {
                if ( a.cd == b.cd )
                {
                    //                                                                                                                 
                    return (a.track_no < b.track_no);
                }
                return (a.cd < b.cd);
            }
            return (a.year < b.year);
        }
        return a.artist < b.artist;
    }
}

bool operator==(const Track& a, const Track& b)
{
    comparisons ++;
    return (a.artist == b.artist && a.cd == b.cd && a.track_no == b.track_no && a.year == b.year) ;   /*                                                 */
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
int read_songs (ifstream& infile, vector<Track>& songs)
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
            songs.push_back(song) ;
    }
    while (infile);
    return songs.size() ;
}

int read_file (string filename)
{
    //               
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
    cout << "Read " << NO_OF_SONGS << " tracks." << endl;
    return NO_OF_SONGS;
}

//                                                                           
void show_all_tracks (vector<Track>& songs, int no_of_songs)
{
    //               
    assert (no_of_songs <= songs.size()) ;
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
{
    //	              
    assert (0 <= from);
    assert( from <= to);
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

typedef Track El ;                //                                                       

bool is_sorted (vector<Track>& data, Slice s)
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
        if (data[i] > data[i+1])
            sorted = false ;
    return sorted ;
}

int find_position ( vector<Track>& data, Slice s, El y )
{
    //	              
    assert (valid_slice(s) && is_sorted(data,s)) ;    //                           
//	                                          
    for ( int i = s.from ; i <= s.to ; i++ )
        if ( y <= data [i] )
            return i ;
    return s.to+1;
}

void shift_right ( vector<Track>& data, Slice s )
{
    //	              
    assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
    for ( int i = s.to+1 ; i > s.from ; i-- )
        data [i]  = data [i-1] ;
}

void insert ( vector<Track>& data, int& length, El y )
{
    //               
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
{
    //	              
    assert ( i >= 0 && j >= 0 ) ;	//                         
    //                         
//                                                                
    const El HELP = data [i];
    data [i] = data [j] ;
    data [j] = HELP;
}

//	                           
void insertion_sort ( vector<Track>& data, int length )
{
    int sorted = 1 ;
    while ( sorted < length )
    {
        insert ( data, sorted, data[sorted] ) ;
    }
}

//	                           
int smallest_value_at ( vector<Track>& data, Slice s )
{
    //	              
    assert (valid_slice (s)) ;	//                        
//	                                                            
//	                                               
    int smallest_at = s.from ;
    for ( int index = s.from+1 ; index <= s.to ; index++ )
        if ( data [index] < data [smallest_at] )
            smallest_at = index ;
    return smallest_at ;
}

void selection_sort ( vector<Track>& data, int length )
{
    for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
    {
        const int k = smallest_value_at (data, mkSlice (unsorted, length-1));
        swap ( data, unsorted, k ) ;
    }
}

//	                        
bool bubble ( vector<Track>& data, Slice s )
{
    //	              
    assert (valid_slice(s));	//                          
//	               
//	                                                    
//	                                        
    bool is_sorted = true ;
    for ( int i = s.from ; i < s.to ; i++)
        if ( data [i] > data [i+1])
        {
            swap ( data, i, i+1 ) ;
            is_sorted = false ;
        }
    return is_sorted ;
}

void bubble_sort ( vector<Track>& data, int length )
{
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
    if ( choice > NoOfSortingMethods )
        choice = NoOfSortingMethods;
    else if ( choice < 1)
        choice = 1;
    return static_cast<SortingMethod>(choice-1) ;
}

void writeFile(vector<Track> data, string filename, int no_of_songs)
{
    //               
    assert (no_of_songs <= songs.size()) ;
    /*                 
                                                                          
    */
    ofstream file;
    file.open(filename.c_str());
    if (file)
    {
        for (int i = 0 ; i < no_of_songs; i++)
            file << i+1 << ". " << songs[i] << endl ;
    }
    file.close();
}

void printProgress() {
    //               
    assert (true);
    //                                                                           
    for (int i = 0; i < comparisons / 100000; i ++ ) {
            cout << "*";
        }
        if (comparisons % 100000 > 0) {
            cout << ".";
        }
        cout << endl;
}

void sortBySlices (vector<Track>& data, SortingMethod m) {
    //              
    assert(true);
    //                                                                                    
    comparisons = 0;
  for ( int i = 100; i < data.size() + 100; i += 100){
        if (i > data.size()) { i = data.size();}
        switch (m){
        case InsertionSort:
            insertion_sort(data,i); break;
        case SelectionSort:
            selection_sort(data,i); break;
        case BubbleSort:
            bubble_sort(data,i); break;
        }
        cout << "Comparisons for slice 0 - " << i << ": " << comparisons << endl;
        printProgress();
    }
    cout << "Number of comparison  operations: " << comparisons << endl;
    cout << "Tracks sorted." << endl;
}

int main()
{
    const int NO_OF_SONGS = read_file ("Tracks.txt");
    if (NO_OF_SONGS < 0)
    {
        cout << "Reading file failed. Program terminates." << endl;
        return NO_OF_SONGS;
    }
    cout << "What do you want to sort?\n1: artist \n2: length" << endl;
    int choice;
    cin >> choice;
    if ( choice >= 2)
    {
        sortByLength = true;
    }
    else
    {
        sortByLength = false;
    }
    SortingMethod m = get_sorting_method () ;
    cout << "Sorting tracks with " << methods[m] << " sort" << endl;
    sortBySlices(songs,m);
    //                                     
    return 0;

}

/*
                  
                     
                     
                 

                  
                     
                    
               

                                                                                                                                   
                                                                                                                                                          
                                                                                                         

*/


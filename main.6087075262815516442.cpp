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
int minutes;       //               
int seconds;       //                 
};
struct Track
{
string artist;                          //            
string cd;                              //         
int    year;                            //                   
int    track_no;      //             
string title;                           //            
string tags;                            //                            
Length time;       //             
string country;                         //                                         
};

const int MAX_NO_OF_SONGS = 6000;           //                                
vector<Track> songs;              //                                     
int count_comparisons = 0;
int slice_counter;
vector<int> slices;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator<(const Length& a, const Length& b)
{
    if(a.minutes < b.minutes)
    {
        return true;
    }
    else if(a.minutes == b.minutes)
    {
        if(a.seconds < b.seconds)
        {
            return true;
        }
        return false;
    }
    return false;
}
bool operator==(const Length& a, const Length& b)
{
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

//                                                                    
//                                                                                               
bool operator<(const Track& a, const Track& b)
{
    count_comparisons++;
    if(a.artist < b.artist)
    {
        return true;
    }
    else if(a.artist == b.artist)
    {
        if(a.cd < b.cd)
        {
            return true;
        }
        else if(a.cd == b.cd)
        {
            if(a.year < b.year)
            {
                return true;
            }
            else if(a.year == b.year)
            {
                if(a.track_no < b.track_no)
                {
                    return true;
                }
                else if(a.track_no == b.track_no)
                {
                    if(operator<(a.time,b.time))
                    {
                        return true;
                    }
                    else if(operator==(a.time,b.time))
                    {
                        return true;
                        //                                                                             
                    }
                    return false;
                }
                return false;
            }
            return false;
        }
        return false;
    }
    return false;
}

bool operator==(const Track& a, const Track& b)
{
    count_comparisons++;
    return a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no;
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
    while (infile && no_of_read_songs < MAX_NO_OF_SONGS);
    return no_of_read_songs ;
}

int read_file (string filename)
{//               
    assert(true) ;
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
int from ;  //             
int to ;  //           
} ;

Slice mkSlice (int from, int to)
{//               
assert (0 <= from && from <= to);
/*                 
                                              
*/ Slice s = { from, to } ;
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

bool is_sorted (vector<Track>& data, Slice s)
{//               
    assert (valid_slice(s)) ; //                           
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

void shift_right (vector<Track>& data, Slice s )
{//               
assert (valid_slice (s)) ; //                               
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
    assert ( i >= 0 && j >= 0 ) ; //                         
    //                         

    const Track HELP = data [i];
    data [i] = data [j] ;
    data [j] = HELP;
}

//                            
void insertion_sort (vector<Track>& data, int length )
{
    int sorted = 1 ;
    slice_counter = 1;
    while ( sorted < length )
    {
        insert ( data, sorted, data[sorted] ) ;
        slice_counter++;
        if(slice_counter%100 == 0)
        {
            slices.push_back(count_comparisons);
        }
    }
}

//                            
int smallest_value_at (vector<Track>& data, Slice s )
{//               
    assert (valid_slice (s)) ; //                        
    //                                                             
    //                                                
    int smallest_at = s.from ;
    for ( int index = s.from+1 ; index <= s.to ; index++ )
    if ( data [index] < data [smallest_at] )
    smallest_at = index ;
    return smallest_at ;
}

void selection_sort (vector<Track>& data, int length )
{ for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
    {   const int k = smallest_value_at (data, mkSlice (unsorted, length-1));
        swap ( data, unsorted, k ) ;
        slice_counter = unsorted; //             
        if(slice_counter%100 == 0)
        {
            slices.push_back(count_comparisons);
        }
    }
}

//                         
bool bubble (vector<Track>& data, Slice s )
{//               
    assert (valid_slice(s)); //                          
    //                
    //                                                     
    //                                         
    bool is_sorted = true ;
    for ( int i = s.from ; i < s.to ; i++)
        if ( data [i] > data [i+1])
     { swap ( data, i, i+1 ) ;
      is_sorted = false ;
     }
    return is_sorted ;
}

void bubble_sort (vector<Track>& data, int length )
{
    while ( !bubble ( data, mkSlice (0, length-1 ) ) )
    {
        length-- ;
        slice_counter = data.size() - length + 1;
        if(slice_counter%100 == 0)
        {
            slices.push_back(count_comparisons);
        }
    }
}

/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */
enum SortingMethod {InsertionSort,SelectionSort,BubbleSort,NoOfSortingMethods};
string methods [] = {"insertion", "selection", "bubble"} ;

int minimum(int a, int b)
{
    if(a<b)
    {
        return a;
    }
    else{
        return b;
    }
}

int maximum(int a, int b)
{
    if(a>b)
    {
        return a;
    }
    else{
        return b;
    }
}

SortingMethod get_sorting_method ()
{
    cout << "What sorting method do you want to use? " << endl ;
    for (int m = 0; m < NoOfSortingMethods; m++)
        cout << m+1 << ": " << methods[m] << " sort" << endl ;
    int choice ;
    cin >> choice ;
    choice = maximum (1, minimum(choice, NoOfSortingMethods)) ;
    return static_cast<SortingMethod>(choice-1) ;
}

void number_to_stars(int a)
{
    for(int i = 1; i<=a/100000;i++)
    {
        if(i*100000 <= a)
        {
            cout << "*";
        }
    }
    int j = a%100000;
    if(j != 0)
    {
        cout << ".\n";
    }
    else{
        cout << "\n";
    }
}

int main()
{
    const int NO_OF_SONGS = read_file("Tracks.txt");
    if (NO_OF_SONGS < 0)
    {
        cout << "Reading file failed. Program terminates." << endl;
        return NO_OF_SONGS;
    }
    SortingMethod m = get_sorting_method () ;
    cout << "Sorting tracks with " << methods[m] << " sort" << endl;
    switch (m)
    {
        case InsertionSort: insertion_sort(songs,NO_OF_SONGS) ; break ;
        case SelectionSort: selection_sort(songs,NO_OF_SONGS) ; break ;
        case BubbleSort:    bubble_sort   (songs,NO_OF_SONGS) ; break ;
        default:        cout << "Huh?" << endl ;
    }
    cout << "Tracks sorted." << endl;
    show_all_tracks (songs,NO_OF_SONGS) ;
    cout << "The amount of comparisons is: " << count_comparisons << endl;
    for(int i = 0;i<slices.size();i++)
    {
        number_to_stars(slices[i]);
    }
    return 0;
    //                                                                                             
    //                                                                                                                                   
}


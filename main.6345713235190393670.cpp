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
#include <cmath>

using namespace std;

/*                                                                    
             
                                             
                                                                     */

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
vector<Track> songs;              //                                     
int size (vector<Track>& songs)
{

    return static_cast<int>(songs.size());

};

int counter_comparisons = 0;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */

//                             
bool operator<(const Track& a, const Track& b)
{
    //                                                                                                         
    counter_comparisons++;
    if (a.artist < b.artist)    return true;
    else if (a.artist == b.artist)
    {
        if(a.cd < b.cd) return true;
        else if(a.cd == b.cd)
        {
            if(a.year < b.year) return true;
            else if (a.year == b.year)
            {
                if(a.track_no < b.track_no) return true;
            }
        }
    }
    return false;
}

//           

bool operator<(const Length& a, const Length& b)
{
    if (a.minutes < b.minutes)
        return true;
    else if (a.minutes == b.minutes)
    {
        if(a.seconds < b.seconds)
            return true;
        else
            return false;
    }
    else
    {
        return false;
    }
}

bool operator==(const Length& a, const Length& b)
{
    if (a.minutes == b.minutes && a.seconds == b.seconds)
        return true;
    return false;
}
/*                                                  
                               

                                              
 
                                                                                                          
                          
                      
                    
                              
     
                               
                        
                                     
         
                           
                            
                                  
             
                                     
                                
             
         
     
                 
 
                                                  */

bool operator==(const Track& a, const Track& b)
{
    counter_comparisons++;
    if(a.artist == b.artist && a.cd == b.cd && a.country==b.country && a.tags==b.tags&&a.time==b.time && a.title==b.title && a.track_no == b.track_no && a.year == b.year)
        return true;
    return false;
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

//	                                  
/*
                                                
 
	              
 

                                                 
 
	                 
 

                                                 
 
	               
 
*/

int maximum(int a, int b)
{
    //            
    assert(true);
    //                                                                             
    if(a>b)
        return a;
    else
        return b;
}

int minimum(int a, int b)
{
    //            
    assert(true);
    //                                                                             
    if(a<b)
        return a;
    else
        return b;
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
    //              
    int no_of_read_songs = 0 ;
    songs.clear();
    do
    {
        Track song ;
        infile >> song ;
        if (infile)
        {
            songs.push_back(song) ;
            no_of_read_songs++;
        }
    }
    while (infile && no_of_read_songs < MAX_NO_OF_SONGS);
    return no_of_read_songs ;
}

int read_file (string filename)
{
    //               
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
void show_all_tracks (vector<Track>& songs, int no_of_songs)
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

typedef Track El;

bool is_sorted (vector<El> data, Slice s)
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
        if (data[i+1] < data[i])
            sorted = false ;
    return sorted ;
}

int find_position ( vector<El>& data, Slice s, El y )
{
    //	              
    assert (valid_slice(s) && is_sorted(data,s)) ;    //                           
//	                                          
    for ( int i = s.from ; i <= s.to ; i++ )
        if ( y <= data [i] )
            return i ;
    return s.to+1;
}

int find_position_2 ( vector<El>& data, Slice s, El y )
{
    //	              
    assert (valid_slice(s) && is_sorted(data,s)) ;    //                           
//	                                          
    for ( int i = s.to ; i >= s.from ; i-- )
    {
        if ( y >= data [i-1] )
            return i ;
    }

    return s.from;
}

void shift_right ( vector<El>& data, Slice s )
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

void insert ( vector<El>& data, int& length, El y, bool on_front)
{
    //               
    Slice s = mkSlice(0,length-1) ;
    assert (length >= 0 && is_sorted (data, s)) ;
    /*                 
                                                                                         
                                       
    */

    if (on_front)
    {
        const int POS = find_position (data, mkSlice (0, length-1), y) ;
        if (POS < length)
            shift_right ( data, mkSlice (POS, length-1) ) ;
        data [POS] = y ;
        length++;
    }
    else
    {

        const int POS = find_position_2 (data, mkSlice (0, length), y) ;
        if (POS < length)
            shift_right ( data, mkSlice (POS, length-1) ) ;
        data [POS] = y ;
        length++;

    }

}

void insertion_sort (vector <El>& data, int length, bool on_front )
{
    int sorted = 1 ;
    while ( sorted < length )
    {
        insert ( data, sorted, data[sorted], on_front) ;
    }
}

void swap (vector<El>& data, int  i, int  j )
{
    //	              
    assert ( i >= 0 && j >= 0 ) ;	//                         
    //                         
//                                                                
    const El HELP = data [i];
    data [i] = data [j] ;
    data [j] = HELP;
}

int smallest_value_at ( vector<El>& data, Slice s )
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

void selection_sort (vector<El>& data, int length )
{
    for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
    {
        const int k = smallest_value_at (data, mkSlice (unsorted, length-1));
        swap ( data, unsorted, k ) ;
    }
}

bool bubble (vector<El>& data, Slice s )
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

void bubble_sort (vector<El>& data, int length )
{
    while ( !bubble ( data, mkSlice (0, length-1 ) ) )
        length-- ;
}

/*                                                                       
              
                                                                       */

void write_counter_down()
{
    //            
    assert (counter_comparisons >= 0);
    //                                                                                                                                                     
    int stars = counter_comparisons/100000;
    bool dot = false;
    if (counter_comparisons%100000 > 0)
        dot = true;
    if (stars > 0)
    {
        for (int i=0; i < stars; i++)
        {
            cout << "*";
        }
    }

    if (dot)
        cout << ".";
}

/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */
enum SortingMethod {InsertionSort,SelectionSort,BubbleSort, InsertionSort2, NoOfSortingMethods};
string methods [] = {"insertion", "selection", "bubble", "insertion2"} ;

SortingMethod get_sorting_method ()
{
    //            
    assert (true);
    //                                                                                                               
    cout << "What sorting method do you want to use? " << endl ;
    for (int m = 0; m < NoOfSortingMethods; m++)
        cout << m+1 << ": " << methods[m] << " sort" << endl ;
    int choice ;
    cin >> choice ;
    choice = maximum (1, minimum (choice, NoOfSortingMethods)) ;
    return static_cast<SortingMethod>(choice-1) ;
}

void give_visual_representation(int length, SortingMethod m)
{
    //            
    assert (true);
    //                                                                                                                                                 
    //                                                                                                                 
    //                                                                                        
    counter_comparisons = 0 ;
    for(int i = 99; i < length; i=i+100)
    {
        const int NO_OF_SONGS = read_file ("Tracks.txt");
        counter_comparisons = 0;
        switch (m)
        {
        case InsertionSort:
            insertion_sort(songs,i, true) ;
            break ;
        case SelectionSort:
            selection_sort(songs,i) ;
            break ;
        case BubbleSort:
            bubble_sort   (songs,i) ;
            break ;
        case InsertionSort2:
            insertion_sort(songs, i, false);
            break;
        default:
            cout << "Huh?" << endl ;
        }
        write_counter_down();
        cout << endl;
    }
    cout << counter_comparisons << endl;
}

void do_visual(int NO_OF_SONGS)
{
    //              
    songs.clear();
    //                                                                                                                                                                                                            
   for (int i = 0; i < 4; i++)
    {
        cout << "Sorting tracks with " << methods[i] << " sort" << endl;
        give_visual_representation(NO_OF_SONGS, static_cast<SortingMethod>(i));
    }
    //                                           
    //                                   
    cout << "Tracks sorted." << endl;

}

enum way {visualize = 1, sorted = 2};

int main()
{
    //            
    assert(true);
    //                                                                                                                 
    const int NO_OF_SONGS = read_file ("Tracks.txt");
    if (NO_OF_SONGS < 0)
    {
        cout << "Reading file failed. Program terminates." << endl;
        return NO_OF_SONGS;
    }
    cout << "Want to visualize the sorting methods, type 1, if you want to see a sorted list, type 2" << endl;
    int choice;
    cin >> choice;
    switch(choice)
    {
        case visualize: do_visual(NO_OF_SONGS);
            break;
        case sorted: char input;
    while (input != 's')
    {
        SortingMethod m = get_sorting_method () ;
        cout << "Sorting tracks with " << methods[m] << " sort" << endl;
        switch (m)
        {
        case InsertionSort:
            insertion_sort(songs,NO_OF_SONGS, true) ;
            break ;
        case SelectionSort:
            selection_sort(songs,NO_OF_SONGS) ;
            break ;
        case BubbleSort:
            bubble_sort   (songs,NO_OF_SONGS) ;
            break ;
        case InsertionSort2:
            insertion_sort(songs, NO_OF_SONGS, false);
            break;
        default:
            cout << "Huh?" << endl ;
        }
        cout << "Tracks sorted." << endl;
        cout << "You can start again with g, you can stop with s" << endl;
        cin >> input;
    }

    show_all_tracks (songs,NO_OF_SONGS) ;
    break;
    default: cout << "huh?";
    }
    return 0;
}

/*                                                            
               
                                                                                                                
                                                                                                                                                     
                                                                                                                                                 
                                                                                                  

             
                                                                                                    
                                                                                                            
                                         
                                                                             
                                                                                                                                                
               

              
                                                                                                                                                
       
                                                                                                                                                    
                                                             */


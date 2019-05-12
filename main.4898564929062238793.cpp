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

int comparisons = 0;

/*
                        
                  

                     
                  
*/

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

vector<Track> songs;              //                                     

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator<(const Length& a, const Length& b)
{
    //               
    assert(true);
    //                
    //                                              
    return (a.seconds + a.minutes*60) < (b.seconds + b.minutes*60);
}

bool operator>=(const Length& a, const Length& b)
{
    return !(a < b);
}

bool operator==(const Length& a, const Length &b)
{
    //               
    assert(true);
    //                
    //                                            
    return a.seconds == b.seconds && a.minutes == b.minutes;
}

bool operator<(const Track& a, const Track& b)
{
    //               
    assert(true);
    //                
    //                                                                                      
    comparisons++;
    if(a.time >= b.time) return false;
    else if(a.artist >= b.artist) return false;
    else if (a.title >= b.title) return false;
    else if (a.cd >= b.cd) return false;
    else return true;
}

bool operator==(const Track& a, const Track& b)
{
    //               
    assert(true);
    //                
    //                                                                              
    comparisons++;
    return a.time == b.time && a.artist == b.artist && a.title == b.title && a.cd == b.cd;
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

int minimum(int a, int b) {
    //               
    assert(true);
    //                
    //                                                      
    if(a < b)
        return a;
    else
        return b;
}

int maximum(int a, int b) {
    //               
    assert(true);
    //                
    //                                     
    if(a > b)
        return a;
    else
        return b;
}

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
            songs.insert(songs.begin()+no_of_read_songs++, song);
    } while (infile);
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

void swap (vector<Track> &data, int i, int j)
{
    //               
    assert(i >= 0 && j >= 0);
    //                                                                
    const Track HELP = data[i];
    data[i] = data[j];
    data[j] = HELP;
}

//                             
void insertion_sort ( vector<Track>& data) {
    int sorted = 1;
    int j = 0;
    while (sorted < data.size())
    {
        j = sorted;
        while(j > 0 && data[j-1] > data[sorted]) {
            swap(data, j, j-1);
            j--;
        }
        sorted++;
    }
}

int smallest_value_at (vector<Track>& songs, Slice s)
{
    //               
    assert(valid_slice(s));
    //                                                              
    //                                                  
    int smallest_at = s.from;
    for(int index = s.from+1; index <= s.to; index++)
        if(songs[index] < songs[smallest_at])
            smallest_at = index;
    return smallest_at;
}

void selection_sort(vector<Track>& songs)
{
    for (int unsorted = 0; unsorted < songs.size(); unsorted++)
    {   const int k = smallest_value_at(songs, mkSlice(unsorted, songs.size()-1));
        swap(songs, unsorted, k);
    }
}

bool bubble(vector<Track>& songs, Slice s)
{
    //               
    assert(valid_slice(s));
    //                
    //                                                        
    //                                             
    bool is_sorted = true;
    for (int i = s.from; i < s.to; i++)
    {
        if (songs[i] > songs[i+1])
        {   swap(songs, i, i+1);
            is_sorted = false;
        }
    }
    return is_sorted;
}

void bubble_sort(vector<Track>& songs)
{
    int length = songs.size();
    while ( !bubble(songs, mkSlice(0, length-1)))
        length--;
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

void show_all_tracks(vector<Track>& songs) {
    for(int i = 0; i < songs.size(); i++)
        cout << songs[i];
}

void show_comparisons()
{
    for(int i = 0; i < (comparisons / 100000); i++)
        cout << '*';
    if(comparisons % 100000 > 0)
        cout << '.';
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
        case InsertionSort: insertion_sort(songs) ; break ;
        case SelectionSort: selection_sort(songs) ; break ;
        case BubbleSort:    bubble_sort   (songs) ; break ;
        default:        cout << "Huh?" << endl ;
    }
    cout << "Tracks sorted." << endl;
    show_all_tracks (songs) ;
	return 0;
}


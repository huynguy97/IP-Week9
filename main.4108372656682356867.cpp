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
//                                                        

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
vector<Track> songs;         //                                     
bool time_sort = true;
int counter_equal;
int counter_difference;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator<(const Length& a, const Length& b)
{
    if(a.minutes != b.minutes)
        return a.minutes < b.minutes;
    if(a.seconds != b.seconds)
        return a.seconds < b.seconds;
    return false;
}

bool operator==(const Length& a, const Length& b)
{
    if(a.minutes != b.minutes || a.seconds != b.seconds)
        return false;
    return true;
}

bool operator<(const Track& a, const Track& b)
{
    counter_difference++;
    if(time_sort)
    {
        if(a.time == b.time)
        {
            if(a.artist.compare(b.artist) != 0)
                return a.artist.compare(b.artist) < 0;
            if(a.cd.compare(b.cd) != 0)
                return a.cd.compare(b.cd) < 0;
            if(a.year != b.year)
                return a.year < b.year;
            if(a.track_no != b.track_no)
                return a.track_no < b.track_no;
            return false;
        }
        return a.time < b.time;
    }
    if(a.artist.compare(b.artist) != 0)
        return a.artist.compare(b.artist) < 0;
    if(a.cd.compare(b.cd) != 0)
        return a.cd.compare(b.cd) < 0;
    if(a.year != b.year)
        return a.year < b.year;
    if(a.track_no != b.track_no)
        return a.track_no < b.track_no;
    return false;
}

bool operator==(const Track& a, const Track& b)
{
    counter_equal++;
    if((a.artist.compare(b.artist) != 0 || a.cd.compare(b.cd) != 0 || a.year != b.year || a.track_no != b.track_no) && a.time == b.time)
        return false;
    return true;
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
    string remains;
    getline (infile, remains);
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
int read_songs (ifstream& infile, vector<Track>& songs, int slice_size)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0 ;
    do {
        Track song ;
        songs.push_back(song);
        infile >> song ;
        if (infile)
            songs[no_of_read_songs++] = song ;
    }
    while (infile && no_of_read_songs < slice_size);
    return no_of_read_songs ;
}

int read_file (string filename, int slice_size)
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
    //                                                
	const int NO_OF_SONGS = read_songs (songsDBS, songs, slice_size);
	songsDBS.close();
	//                                                      
	return NO_OF_SONGS;
}

//                                                                           
void show_all_tracks (vector<Track>& songs, int slice_size)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < slice_size; i++)
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

typedef int El ;                //                                                       

bool is_sorted (vector<Track>& data, Slice s)
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

int find_position (vector<Track>& data, Slice s, Track y )
{//	              
	assert (valid_slice(s) && is_sorted(data,s) && s.to < data.size()) ;    //                           
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= data [i] )
			return i ;
	return s.to+1;
}

void shift_right (vector<Track>& data, Slice s )
{//	              
	assert (valid_slice (s)&& s.to < data.size() - 1) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
	for ( int i = s.to+1 ; i > s.from ; i-- )
		data [i]  = data [i-1] ;
}

void insert ( vector<Track>& data, int& length, Track y )
{//               
    Slice s = mkSlice(0,length-1);
    assert (is_sorted (data, s));
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
	assert ( i >= 0 && j >= 0 && i <= data.size() && j<= data.size()) ;
//                                                                
	const Track HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

//	                           
void insertion_sort ( vector<Track>& data, int length)
{
	int sorted = 1 ;
    while ( sorted < length)
    {   insert ( data, sorted, data[sorted] ) ;
    }
}

//	                           
int smallest_value_at ( vector<Track>& data, Slice s )
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

void selection_sort ( vector<Track>& data, int length)
{	for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
	{   const int k = smallest_value_at (data, mkSlice (unsorted, length-1));
	    swap ( data, unsorted, k ) ;
	}
}

//	                        
bool bubble ( vector<Track>& data, Slice s )
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

void bubble_sort ( vector<Track>& data, int length)
{
    while ( !bubble ( data, mkSlice (0, length-1 ) ) )
        length--;

}

/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */
enum SortingMethod {InsertionSort,SelectionSort,BubbleSort,NoOfSortingMethods};
enum Timesorting {yes,no};
string methods [] = {"insertion", "selection", "bubble"} ;

SortingMethod get_sorting_method ()
{
    cout << "What sorting method do you want to use? " << endl ;
    for (int m = 0; m < NoOfSortingMethods; m++)
        cout << m+1 << ": " << methods[m] << " sort" << endl ;
    int choice ;
    cin >> choice ;
    choice = max(1, min(static_cast<int>(choice), static_cast<int>(NoOfSortingMethods))) ;
    cout << "Do you want to sort the tracks on runtime? (y/n)" << endl;
    string choice1;
    cin >> choice1;
    if(choice1 == "y")
        time_sort = true;
    else if(choice1 == "n")
        time_sort = false;
    else
    {
        time_sort = false;
        cout << "Something went wrong, the sorting will not be done time-wise" << endl;
    }

    return static_cast<SortingMethod>(choice-1) ;
}

int main()
{
    int i = 99;
    int ophoger = 100;
    const int N = 100000;
    do {
        if(songs.size() != 0 )
            songs.clear();
        int no_of_songs = read_file ("Tracks.txt", i);
        counter_difference = 0;
        counter_equal = 0;
        if (no_of_songs < 0)
        {
            cout << "Reading file failed. Program terminates." << endl;
            return no_of_songs;
        }
        //                                                                                                                         
        cout << "Sorting tracks with slice size : " << i << " sorting on tracktime" << endl;
        for (int m = 0; m < 3 ; m++)
        {
            time_sort = true;
            counter_difference = 0;
            counter_equal = 0;
            switch (static_cast<SortingMethod>(m))
            {
                case InsertionSort: insertion_sort(songs,no_of_songs) ; break ;
                case SelectionSort: selection_sort(songs,no_of_songs) ; break ;
                case BubbleSort:    bubble_sort   (songs,no_of_songs) ; break ;
                default:        cout << "Huh?" << endl ;
            }
            cout << methods[static_cast<SortingMethod>(m)] << " sort: " << '\t';
            for(int l = 0; l < (counter_equal + counter_difference) / N ; l++)
                cout << '*';
            if((counter_equal + counter_difference) % N != 0 )
                cout << '.';
            cout << endl;
            songs.clear();
            no_of_songs = read_file ("Tracks.txt", i);
        }
        cout << "Sorting tracks with slice size : " << i << " not sorting on tracktime" << endl;
        for (int k = 0; k < 3 ; k++)
        {
            time_sort = false;
            counter_difference = 0;
            counter_equal = 0;

            switch (static_cast<SortingMethod>(k))
            {
                case InsertionSort: insertion_sort(songs,no_of_songs) ; break ;
                case SelectionSort: selection_sort(songs,no_of_songs) ; break ;
                case BubbleSort:    bubble_sort   (songs,no_of_songs) ; break ;
                default:        cout << "Huh?" << endl ;
            }
            cout << methods[static_cast<SortingMethod>(k)] << " sort: " << '\t';
            for(int g = 0; g < (counter_equal + counter_difference) / N ; g++)
                cout << '*';
            if((counter_equal + counter_difference) % N != 0 )
                cout << '.';
            cout << endl;
            songs.clear();
            if (k != 2)
                no_of_songs = read_file ("Tracks.txt", i);
        }
        //                                 
        i = i + ophoger;
    }
    while(i < 5892);
    //                         
	return 0;
}

/*
                          
                                             
                                             
                                           
                                                                                                                                                                 
                                                                                                                                                                                                                                 
*/
/*
                                                                                                                                           
                                                                                                                                                                                                                                   
                                                                                                                                               
                                                                                                                                                                                                             
*/


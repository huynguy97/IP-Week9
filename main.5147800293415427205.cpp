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
#define NDEBUG

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
int number_of_comparisons = 0;
/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator< (const Length& a, const Length& b)
{//              
    assert (0 <= a.minutes && 0 <= a.seconds && a.seconds < 60 && 0 <= b.minutes && 0 <= b.seconds && b.seconds < 60) ;
/*                
     
*/
    if (a.minutes == b.minutes) return a.seconds < b.seconds;
    else return a.minutes < b.minutes;
}
bool operator== (const Length& a, const Length& b)
{//              
    assert (0 <= a.minutes && 0 <= a.seconds && a.seconds < 60 && 0 <= b.minutes && 0 <= b.seconds && b.seconds < 60) ;
/*                
     
*/
    return (a.minutes == b.minutes)  && (a.seconds == b.seconds);
}

/*                                                                                                                      
                                                                                                                      
                                                                                   */

/*                                              
                  
                   
                   
                                                                
                              
                             
                         
                                
                                             
                                           
                                             
                                                                               
                                                        
                                                    
                                                  
                                                    
                                        
                                
                                     
 */

 /*                
                                                                                                                                                                             
                                                                                                                                           
                                                                                  
 */

bool operator<(const Track& a, const Track& b)
{//               
    assert (true) ;
/*                 
                                                               */
    number_of_comparisons++;
    if (a.time == b.time)
        if (a.artist == b.artist)
            if (a.cd == b.cd)
                if(a.year == b.year)
                    if (a.track_no == b.track_no)
                        if (a.title == b.title)
                            if (a.tags == b.tags)
                                return a.country < b.country;
                            else return a.tags < b.tags;
                        else return a.title < b.title;
                    else return a.track_no < b.track_no;
                else return a.year < b.year;
            else return a.cd < b.cd;
        else return a.artist < b.artist ;
    else return a.time < b.time;
}

bool operator==(const Track& a, const Track& b)
{//               
    assert (true) ;
/*                 
                                                                                              
*/
    number_of_comparisons++;
    return  a.artist == b.artist &&
            a.cd == b.cd && a.year &&
            a.year == b.year &&
            a.track_no == b.track_no &&
            a.title == b.title &&
            a.tags == b.tags &&
            a.time == b.time &&
            a.country == b.country;
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
    out << "Artist:  " << track.artist   << endl ;
    out << "CD:      " << track.cd       << endl ;
    out << "Year:    " << track.year     << endl ;
    out << "No:      " << track.track_no << endl ;
    out << "Title:   " << track.title    << endl ;
    out << "Tags:    " << track.tags     << endl ;
    out << "Time:    " << track.time     << endl ;
    out << "Country: " << track.country  << endl ;
    out << endl ;
    return out ;
}

//                                                                           
int read_songs (ifstream& infile, vector<Track> &songs )
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    songs.clear();
    do {
        Track song ;
        infile >> song ;
        if (infile)
            songs.push_back(song) ;
    }
    while (infile);
    return songs.size();
}

int read_file (string filename)
{//               
    assert (true) ;
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
int print_to_file(string filename, vector<Track> songs)
{//               
    assert (true) ;
/*                 
                                                                          */
    ofstream songsDBS(filename.c_str());
    if (!songsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    for (int i = 0 ; i < songs.size(); i++)
        songsDBS << i+1 << ". " << songs[i] << endl ;
    songsDBS.close();

}
//                                                                           
void show_all_tracks (vector<Track> songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    cout << " showing all tracks " << songs.size() << endl;
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

void print_comparisons_growth(Slice s)
{//	              
	assert (true) ;
//	               
//	                                                                              
//						                                                                                     
    //                                                                                     
    if (0 == s.to%100)
    {
        int number_of_stars = number_of_comparisons/100000;
        for (int i=0; i< number_of_stars; i++)
            cout << "*";
        if (number_of_comparisons%100000 > 0)
            cout << ".";
        cout << endl;
    }

    //                                                                       
    if (0 == s.from%100 && s.from > 0)
    {
        int number_of_stars = number_of_comparisons/100000;
        for (int i=0; i< number_of_stars; i++)
            cout << "*";
        if (number_of_comparisons%100000 > 0)
            cout << ".";
        cout << endl;
    }
}
bool is_sorted (vector<El>& data , Slice s)
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
//	                  
	if (POS < length)
		shift_right ( data, mkSlice (POS, length-1) ) ;
	data [POS] = y ;
	length++;
	print_comparisons_growth(s);
}

void swap (vector<El>& data, int  i, int  j )
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
	print_comparisons_growth(s);
	return smallest_at ;
}

void selection_sort ( vector<El>& data, int length )
{
    for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
	{   const int k = smallest_value_at (data, mkSlice (unsorted, length-1));
	    swap ( data, unsorted, k ) ;
	}
}

//	                        
bool bubble ( vector<El>& data, Slice s )
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
    print_comparisons_growth(s);
	return is_sorted ;
}

void bubble_sort ( vector<El>& data, int length )
{
    while ( !bubble ( data, mkSlice (0, length-1 ) ) )
        length-- ;
}

/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */
/*
                                                                                                                                           
                                                                               
                                                          

                                   
 
                                                                
                                                
                                                              
                
                   
                                                         
                                                 
 
*/
int main()
{
    //                                                   
	int no_of_songs = read_file ("Tracks.txt");
	if (no_of_songs < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return no_of_songs;
    }
    number_of_comparisons = 0;

    //                                                                                                                                                      
    cout << "starting sorting - insertion method" << endl;
    insertion_sort(songs,no_of_songs);
    cout << " insertion sort ended. Total number_of_comparisons is " << number_of_comparisons << endl;
    //                                                                     
    print_to_file("part3 - insertion_sorted_tracks.txt",songs);

    //                                                                                            
    no_of_songs = read_file ("Tracks.txt");
	if (no_of_songs < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return no_of_songs;
    }
    number_of_comparisons = 0;
    //                                                                                                                         
    //                                                                                
    cout << "starting sorting - selection method" << endl;
    selection_sort(songs,no_of_songs);
    cout << "selection sort ended. Total number_of_comparisons is " << number_of_comparisons << endl;
    //                                                                     
    print_to_file("part3 - selection_sorted_tracks.txt",songs);

    no_of_songs = read_file ("Tracks.txt");
	if (no_of_songs < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return no_of_songs;
    }
    number_of_comparisons = 0;
    //                                                                                                                            
    //                                                                                                                      

    cout << "starting sorting - bubble method" << endl;
    bubble_sort(songs,no_of_songs);
    cout << "Bubble sort ended. Total number_of_comparisons is " << number_of_comparisons << endl;
    //                                                                     
    print_to_file("part3 - bubble_sorted_tracks.txt",songs);

/*
                           
                                                                                                                                                                     
                              
                                                                                                                                                                                                 
                                                                                                                                            

*/
	return 0;
}


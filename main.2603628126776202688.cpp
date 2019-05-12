/*                                                                     
                        
                        
                                                                     */

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

int counter = 0;

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
Track songs [MAX_NO_OF_SONGS];              //                                     

/*                                                                       
                                            
                                                                       */
vector<Track> music ;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
/*                               */
bool operator<(const Length& a, const Length& b)
{
    if (a.minutes  ==   b.minutes)
            return (a.seconds   <   b.seconds);
    else    return (a.minutes    <  b.minutes);

}

bool operator==(const Length& a, const Length& b)
{
    if (a.minutes  ==   b.minutes)
            return (a.seconds   !=   b.seconds);
    else    return (a.minutes    !=  b.minutes);
}

//	                                  
bool operator>(const Length& a, const Length& b)
{
	return b < a ;
}

bool operator<=(const Length& a, const Length& b)
{
	return !(b < a) ;
}

bool operator>=(const Length& a, const Length& b)
{
	return b <= a ;
}

bool operator!=(const Length& a, const Length& b)
{
	return a.minutes != b.minutes || a.seconds != b.seconds;
}

/*                              */
bool operator<(const Track& a, const Track& b)
{
    if (a.time != b.time)
    {
        return a.time < b.time;
    }
    if (a.artist != b.artist)
    {
         return a.artist < b.artist;
    }
    else if (a.cd != b.cd)
    {
         return a.cd < b.cd;
    }
    else if (a.year != b.year)
    {
        return a.year < b.year;
    }
    else if (a.track_no != b.track_no)
    {
        return a.track_no < b.track_no;
    }
}

bool operator==(const Track& a, const Track& b)
{
    return a.time == b.time && a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no;
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

/*                                                                       
                                                       
                                                                       */
int read_songs (ifstream& infile, vector<Track>& music)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0 ;
    do {
        Track song ;
        infile >> song ;
//                                                
        if (infile)
        {
//                                                                                 
            music.push_back(song);
            no_of_read_songs++ ;
        }
    }
    while (infile);  //                                                     
    return no_of_read_songs ;
}

int read_file (string filename)
{//               
    assert (music.size() == 0) ;
/*                 
                                                                              
                                                                                             
                                        
*/
    ifstream songsDBS (filename.c_str());
    if (!songsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
	const int NO_OF_SONGS = read_songs (songsDBS, music);
	songsDBS.close();
	cout << " Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

void show_all_tracks (vector<Track>& music, int no_of_songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << music[i] << endl ;
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

/*                                                                       
                                       
                                                                       */
typedef int El ;                //                                                       

bool is_sorted (vector<Track>& music, Slice s, int& counter)
{//	              
	assert (valid_slice(s)) ;	//                            
//	               
//	                 	                                  
//						                                  
//						   
//						                              
	bool sorted = true ;
	for (int i = s.from; i < s.to && sorted; i++)
		if (music[i] > music[i+1])
        {
            counter ++;
            sorted = false ;
        }
	return sorted ;
}

int find_position ( vector<Track>& music, Slice s, Track track, int& counter)
{//	              
	assert (valid_slice(s) && is_sorted(music,s, counter)) ;    //                            
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
        if ( track <= music [i] )
        {
            counter++;
            return i ;
        }
	return s.to+1;
}

void shift_right (vector<Track>& music, Slice s)
{//	              
	assert (valid_slice (s)) ;	//                                
//	                                	  	                 
//			    	                	  	                   
//						   
//			    	              		  	               
	for ( int i = s.to+1 ; i > s.from ; i-- )
		music[i] = music[i-1] ;
}

void insert (vector<Track>& music, int& length, Track track )
{//               
    Slice s = mkSlice(0,length-1) ;
    assert (length >= 0 && is_sorted (music, s, counter)) ;
/*                 
                                                                                       
                                   
*/
	const int POS = find_position (music, mkSlice (0, length-1), track, counter);
	if (POS < length)
		shift_right ( music, mkSlice (POS, length-1) ) ;
	music[POS] = track ;
	length++;
}

void swap (vector<Track>& music, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                          
						            //                          
//                                                                    
    vector<Track> help(1);
    help[0] = music[i];
	music [i] = music [j] ;
	music [j] = help[0];
}

/*                                                                       
                                                 
                                                                       */
//	                            
void insertion_sort ( vector<Track>& music, int length)
{   /*                */ assert (length > 0);
    //                                                                                 
	int sorted = 1 ;
    while ( sorted < length )
    {   insert ( music, sorted, music[sorted] ) ;
    }
}

//	                            
int smallest_value_at ( vector<Track>& music, Slice s, int& counter )
{//	              
	assert (valid_slice (s)) ;	//                        
//	                                                            
//	                                               
	int smallest_at = s.from ;
	for ( int index = s.from+1 ; index <= s.to ; index++ )
    {
        if ( music [index] < music [smallest_at] )
        {
            counter++;
            smallest_at = index ;
        }
    }
	return smallest_at ;
}

void selection_sort (vector<Track>& music, int length )
{
    /*               */ assert(length > 0);
    //                                                                                 
    for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
	{
	    const int k = smallest_value_at (music, mkSlice (unsorted, length-1), counter);
	    swap ( music, unsorted, k ) ;
	}
}

//	                         
bool bubble ( vector<Track>& music, Slice s, int& counter )
{//	              
	assert (valid_slice(s));	//                          
//	               
//	                                                    
//	                                        
	bool is_sorted = true ;
	for ( int i = s.from ; i < s.to ; i++)
	    if ( music [i] > music [i+1])
		{
		    counter++;
		    swap ( music, i, i+1 ) ;
			is_sorted = false ;
		}
	return is_sorted ;
}

void bubble_sort (vector<Track>& music, int length )
{
    /*               */ assert(length > 0);
    //                                                                                 
    while ( !bubble (music, mkSlice (0, length-1 ), counter ) )
        length-- ;
}

/*                                                                       
                                                    
                                                                       */
enum SortingMethod {InsertionSort,SelectionSort,BubbleSort,NoOfSortingMethods};
string methods [] = {"insertion", "selection", "bubble"} ;

int minimum (int x, int y)
{
    /*               */ assert(true);
    //                                                         
        if(x < 0)
        {
            cout << "Input too low, changing it to 1." << endl;
            return x = 1;
        }
    return x;
}

int maximum (int z, int a)
{
    /*               */ assert(true);
    //                                                         
    assert (a >= z);
    if (a > 3)
    {
            cout << "Input too high, changing it to 3." << endl;
            return a = 3;
    }
}

SortingMethod get_sorting_method ()
{
    /*               */ assert(true);
    //                                                    
    cout << "What sorting method do you want to use? " << endl ;
    for (int m = 0; m < NoOfSortingMethods; m++)
        cout << m+1 << ": " << methods[m] << " sort" << endl ;
    int choice ;
    cout << "Choose 1, 2, or 3: ";
    cin >> choice ;
    choice = maximum (1, minimum (choice, NoOfSortingMethods)) ; \
    return static_cast<SortingMethod>(choice-1) ;
}

/*                                                                       
                                            
                                           
                                                                       */

void visualization (int counter)
//                                                                              
{
    /*               */ assert(counter >= 0);
    //                                                                                                                                           
    cout << "Number of comparisons:" << counter << endl;
    for (counter; counter>100000 ; (counter = counter-100000))
    {
        cout << "*";
    }

    if (counter != 0)
        cout << ".";
    cout << "\n" ;
}

/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */

int main()
{
	const int NO_OF_SONGS = read_file ("Tracks.txt");
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }

//                                                  
//     
//                                                         
//                            
//         
//                                                                       
//                               
//         
//                    
//                                                         
//         
//                      
//             
//                                                                  
//                                                                  
//                                                                  
//                                                    
//             
//                                                        
//                                                 
//                                   
//         
//     

    SortingMethod m = get_sorting_method () ;
    cout << "Sorting tracks with " << methods[m] << " sort" << endl;
    switch (m)
    {
        case InsertionSort: insertion_sort(music,NO_OF_SONGS) ; break ;
        case SelectionSort: selection_sort(music,NO_OF_SONGS) ; break ;
        case BubbleSort:    bubble_sort   (music,NO_OF_SONGS) ; break ;
        default:        cout << "Huh?" << endl ;
    }
    cout << "Tracks sorted." << endl;
    show_all_tracks (music,NO_OF_SONGS) ;
    visualization(counter);
	return 0;
}

//                              
/*
                  
                                   
                                             
                  
                                    
                                             
               
                                      
                                              

                 
                                                                                                                                                                     
                                                                                                                                                                                           
                                                                                                                
                                                                                                                                      
                                                                                                                                                                                    
                                                                                              

     */


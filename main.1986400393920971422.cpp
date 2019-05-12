/*
                                             
*/
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

vector<Track> songs ;              //                                     
int comparisons = 0; //                                                       
const bool cd_length = true; //                                                            

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator< (const Length& a, const Length& b) {
    if (a.minutes != b.minutes) return a.minutes < b.minutes;
    if (a.seconds != b.seconds) return a.seconds < b.seconds;
    return false;
}

bool operator== (const Length& a, const Length& b) {
    return a.minutes == b.minutes && a.seconds == b.seconds;
}

//	                                  
bool operator!= (const Length& a, const Length& b) {
    return !(a == b);
}

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

//                            
//                                                                   
//                                                    

bool operator<(const Track& a, const Track& b)
{
    //               
    assert(true);
    //                                                                                                     
    //                               
    comparisons++;
    if (cd_length){
        if (a.time != b.time) return a.time < b.time;
        switch((a.artist).compare(b.artist)){
            case -1:    return true; break;
            case 1:     return false; break;
            default:    break;
        }
        switch((a.title).compare(b.title)){
            case -1:    return true; break;
            case 1:     return false; break;
            default:    break;
        }
        switch((a.cd).compare(b.cd)){
            case -1:    return true; break;
            case 1:     return false; break;
            default:    break;
        }
    } else {
        switch((a.artist).compare(b.artist)){
            case -1:    return true; break;
            case 1:     return false; break;
            default:    break;
        }
        switch((a.cd).compare(b.cd)){
            case -1:    return true; break;
            case 1:     return false; break;
            default:    break;
        }
        if (a.year != b.year) return a.year < b.year;
        if (a.track_no != b.track_no) return a.track_no < b.track_no;
    }
    return false;
}

bool operator==(const Track& a, const Track& b)
{
    //               
    assert(true);
    //                                                           
    //                               
    comparisons++;
    if (cd_length) {
        return (a.artist == b.artist && a.cd == b.cd && a.title == b.title
                && a.time.minutes == b.time.minutes && a.time.seconds == b.time.seconds);
    } else {
        return (a.artist == b.artist && a.cd == b.cd
                && a.year == b.year && a.track_no == b.track_no);
    }
}

//	                                 
bool operator!=(const Track& a, const Track& b)
{
	return !(a == b) ;
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

int read_songs (ifstream& infile, vector<Track>& songs)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0 ;
    do {
        Track song ;
        infile >> song ;
        if (infile) {
            no_of_read_songs++;
            songs.push_back(song);
        }
    } while (infile);
    return no_of_read_songs ;
}

int read_file (string filename, vector<Track>& songs)
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
    cout << "Reading '" << filename << "'." << endl;
	const int NO_OF_SONGS = read_songs (songsDBS, songs);
	songsDBS.close();
	cout << " Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

void show_all_tracks (vector<Track>& songs)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    for (unsigned int i = 0 ; i < songs.size(); i++)
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

bool valid_slice (Slice s, vector<Track>& data)
{//               
    assert (true) ;
/*                 
                                                  
                                       
                                          
*/
	return 0 <= s.from && s.from <= s.to && s.to < static_cast<int>(data.size()) ;
}

bool is_sorted ( vector<Track>& data, Slice s)
{//	              
	assert (valid_slice(s, data)) ;	//                           
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

int find_position ( vector<Track>& data, Slice s, Track y )
{//	              
	assert (valid_slice(s, data) && is_sorted(data,s)) ;
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= data [i] )
			return i ;
	return s.to+1;
}

void shift_right ( vector<Track>& data, Slice s )
{//	              
	assert (valid_slice (s, data) && s.to < data.size() - 1) ;
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
	for ( int i = s.to+1 ; i > s.from ; i-- )
		data [i]  = data [i-1] ;
}

void insert ( vector<Track>& data, int& length, Track y )
{//               
    assert (length >= 0 && is_sorted (data, mkSlice(0,length-1))) ;
/*                 
                                                                                     
                                   
*/
	const int POS = find_position (data, mkSlice (0, length-1), y) ;
	if (POS < length)
		shift_right ( data, mkSlice (POS, length-1) ) ;
	data [POS] = y ;
	length++;
}

void swap (vector<Track>& data, unsigned int  i, unsigned int  j )
{//	              
	assert ( i >= 0 && j >= 0 && i < data.size() && j < data.size()) ;
//                                                                
	const Track HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

//	                            
void insertion_sort ( vector<Track>& data) {
	int sorted = 1 ;
	int length = static_cast<int>(data.size());
    while ( sorted < length )
    {   insert ( data, sorted, data[sorted] ) ;
    }
}

//	                            
int smallest_value_at ( vector<Track>& data, Slice s )
{//	              
	assert (valid_slice (s, data)) ;	//                        
//	                                                            
//	                                               
	int smallest_at = s.from ;
	for ( int index = s.from+1 ; index <= s.to ; index++ )
		if ( data [index] < data [smallest_at] )
			smallest_at = index ;
	return smallest_at ;
}

void selection_sort ( vector<Track>& data ){
    int length = static_cast<int>(data.size());
    for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
	{   const int k = smallest_value_at (data, mkSlice (unsorted, length-1));
	    swap ( data, unsorted, k ) ;
	}
}

//	                         
bool bubble ( vector<Track>& data, Slice s )
{//	              
	assert (valid_slice(s, data));
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

void bubble_sort ( vector<Track>& data) {
    int length = static_cast<int>(data.size());
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
    choice = max (1, min (choice, static_cast<int>(NoOfSortingMethods))) ;
    return static_cast<SortingMethod>(choice-1) ;
}

int main()
{
    vector<Track> songs;
	const int NO_OF_SONGS = read_file ("Tracks.txt", songs);
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }

    SortingMethod m = get_sorting_method () ;
    cout << "Sorting tracks with " << methods[m] << " sort" << endl;
    for (int i = 99; i < NO_OF_SONGS; i += 100){
        comparisons = 0;
        vector<Track> songs_check = vector<Track>(songs.begin(), songs.begin()+i);
        switch (m)
        {
            case InsertionSort: insertion_sort(songs_check) ; break ;
            case SelectionSort: selection_sort(songs_check) ; break ;
            case BubbleSort:    bubble_sort   (songs_check) ; break ;
            default:        cout << "Huh?" << endl ;
        }
        cout << i << '\t';
        while (comparisons/100000 > 0){
            cout << "*";
            comparisons -= 100000;
        }
        if (comparisons > 0) cout << "." << endl;
    }
    comparisons = 0;
    switch (m)
        {
            case InsertionSort: insertion_sort(songs) ; break ;
            case SelectionSort: selection_sort(songs) ; break ;
            case BubbleSort:    bubble_sort   (songs) ; break ;
            default:        cout << "Huh?" << endl ;
        }
    cout << "Tracks sorted." << endl;
    show_all_tracks (songs) ;
    cout << endl << comparisons << " comparisons were computed." << endl;
	return 0;
}

/*
                                                           

         

                    
                    
                    

                                                                            

             

                    
                    
                    

                                                                             

       

                                                
                                                                                                                            
                                                                                                                              

                                         
                                                                                                             
                                                                                                                              

        

              
          
         
         
         
         
          
          
           
            
             
             
               
                
                 
                  
                    
                     
                       
                         
                          
                            
                              
                                 
                                   
                                     
                                        
                                          
                                             
                                                
                                                  
                                                     
                                                        
                                                            
                                                               
                                                                  
                                                                      
                                                                         
                                                                             
                                                                                 
                                                                                    
                                                                                        
                                                                                            
                                                                                                 
                                                                                                     
                                                                                                         
                                                                                                              
                                                                                                                  
                                                                                                                       
                                                                                                                           
                                                                                                                                
                                                                                                                                     
                                                                                                                                          
                                                                                                                                               
                                                                                                                                                     
                                                                                                                                                          
                                                                                                                                                                
                                                                                                                                                                     
                                                                                                                                                                           
                                                                                                                                                                                
          
         
         
         
         
          
          
           
            
             
             
               
                
                 
                  
                    
                     
                       
                         
                           
                            
                               
                                 
                                   
                                     
                                        
                                          
                                             
                                                
                                                   
                                                     
                                                         
                                                            
                                                               
                                                                  
                                                                      
                                                                         
                                                                             
                                                                                 
                                                                                    
                                                                                        
                                                                                            
                                                                                                 
                                                                                                     
                                                                                                         
                                                                                                              
                                                                                                                  
                                                                                                                       
                                                                                                                            
                                                                                                                                
                                                                                                                                     
                                                                                                                                          
                                                                                                                                                
                                                                                                                                                     
                                                                                                                                                          
                                                                                                                                                                
                                                                                                                                                                     
                                                                                                                                                                           
                                                                                                                                                                                 
       
         
         
         
         
         
         
         
         
         
         
         
         
         
         
          
          
          
          
          
          
          
          
          
          
          
             
             
              
              
              
              
              
               
               
               
               
               
                
                
                
                
                
                
                 
                 
                 
                 
                 
                  
                  
                  
                  
                  
                   
                   
                   
                   
                   

                  
          
         
         
         
         
         
         
          
          
          
           
           
            
            
             
              
               
                
                 
                  
                  
                   
                     
                      
                       
                        
                          
                           
                             
                              
                               
                                 
                                   
                                    
                                      
                                       
                                         
                                           
                                             
                                               
                                                 
                                                   
                                                     
                                                       
                                                         
                                                           
                                                              
                                                                
                                                                  
                                                                     
                                                                        
                                                                           
                                                                             
                                                                               
                                                                                 
                                                                                    
                                                                                       
                                                                                         
                                                                                             
          
         
         
         
         
          
          
           
            
             
             
               
                
                 
                  
                    
                     
                       
                         
                           
                            
                               
                                 
                                   
                                     
                                        
                                          
                                             
                                                
                                                   
                                                     
                                                         
                                                            
                                                               
                                                                  
                                                                      
                                                                         
                                                                             
                                                                                 
                                                                                    
                                                                                        
                                                                                            
                                                                                                 
                                                                                                     
                                                                                                         
                                                                                                              
                                                                                                                  
                                                                                                                       
                                                                                                                            
                                                                                                                                
                                                                                                                                     
                                                                                                                                          
                                                                                                                                                
                                                                                                                                                     
                                                                                                                                                          
                                                                                                                                                                
                                                                                                                                                                     
                                                                                                                                                                           
                                                                                                                                                                                 
       
         
         
         
         
          
          
           
            
             
             
               
                
                 
                  
                    
                     
                       
                         
                          
                            
                               
                                 
                                   
                                     
                                        
                                          
                                             
                                                
                                                   
                                                     
                                                        
                                                            
                                                               
                                                                  
                                                                      
                                                                         
                                                                             
                                                                                 
                                                                                    
                                                                                        
                                                                                            
                                                                                                 
                                                                                                     
                                                                                                         
                                                                                                              
                                                                                                                  
                                                                                                                       
                                                                                                                            
                                                                                                                                
                                                                                                                                     
                                                                                                                                          
                                                                                                                                               
                                                                                                                                                     
                                                                                                                                                          
                                                                                                                                                                
                                                                                                                                                                     
                                                                                                                                                                           
                                                                                                                                                                                 
*/


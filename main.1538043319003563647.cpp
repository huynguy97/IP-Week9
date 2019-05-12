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

int counter;

const int MAX_NO_OF_SONGS = 6000;           //                                
vector <Track> songs;              //                                     

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator< (const Length& a, const Length& b){
    return a.minutes < b.minutes || (a.minutes == b.minutes && a.seconds < b.seconds);
}

bool operator== (const Length& a, const Length& b){
    return (a.minutes == b.minutes && a.seconds == b.seconds);
}

bool operator<(const Track& a, const Track& b)
{
//              
//               
//                                 
//                                                 
//                                                                     
//                                                                                                

//                
    counter ++;
    return a.time < b.time ||
           (a.time == b.time && a.artist < b.artist)||
           (a.time == b.time && a.artist == b.artist && a.title < b.title)||
           (a.time == b.time && a.artist == b.artist && a.title == b.title && a.cd < b.cd);

}

bool operator==(const Track& a, const Track& b)
{
    counter ++;
    return a.artist == b.artist &&
           a.cd == b.cd &&
           a.year == b.year &&
           a.track_no == b.track_no;
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
int read_songs (ifstream& infile, vector <Track>& songs)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0 ;
    do {
        Track song ;
        infile >> song ;
        if (infile){
            //                                  
            songs.push_back(song);
            no_of_read_songs ++;
        }
    }
    while (infile/*                                      */);
    return no_of_read_songs ;
}

int alt_read_songs(ifstream& infile, vector<Track>& songs ,int measure){
    //               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0 ;
    do {
        Track song ;
        infile >> song ;
        if (infile){
            //                                  
            songs.push_back(song);
            no_of_read_songs ++;
        }
    }
    while (no_of_read_songs < measure/*                                      */);
    return no_of_read_songs ;
}

int size(vector<Track>& v){
    return static_cast<int> (v.size());
}

int read_file (string filename, int measure)
{//               
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
	const int NO_OF_SONGS = alt_read_songs (songsDBS, songs, measure);
	songsDBS.close();
	//                                                     
	return NO_OF_SONGS;
}

//                                                                           
void show_all_tracks (vector <Track>& songs, int no_of_songs)
{//               
    assert (/*                             */ true) ;
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

int find_position (vector<El>& data , Slice s, El y )
{//	              
	assert (valid_slice(s) && is_sorted(data,s)) ;    //                           
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= data [i] )
			return i ;
	return s.to+1;
}

void shift_right (vector<El>& data , Slice s )
{//	              
	assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
	for ( int i = s.to+1 ; i > s.from ; i-- )
		data [i]  = data [i-1] ;
}

void insertv(vector<Track>& v, int i, Track e){
    assert(0 <= i && i <= size(v));

    v.push_back(e);
    if(i < size(v) - 1){
        for(int j = size(v) - 1; j > i; j--){
            v[j] = v[j-1];
        }
        v[i] = e;
    }
}

void insert (vector<El>& data , int& length, El y )
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

void swap (vector<El>& data , int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                
	const El HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

//	                           
void insertion_sort (vector<El>& data , int length )
{
    counter = 0;
	int sorted = 1 ;
    while ( sorted < length )
    {   insert ( data, sorted, data[sorted] ) ;
    }
}

//	                           
int smallest_value_at (vector<El>& data , Slice s )
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

void selection_sort (vector<El>& data , int length )
{
    counter = 0;
    for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
	{   const int k = smallest_value_at (data, mkSlice (unsorted, length-1));
	    swap ( data, unsorted, k ) ;
	}
}

//	                        
bool bubble (vector<El>& data , Slice s )
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

void bubble_sort (vector<El>& data , int length )
{
    counter = 0;
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
    //                                                            
    return static_cast<SortingMethod>(choice-1) ;
}

void print_visualisation(int counter, SortingMethod m, int measure){
    //                                                    

    while(counter >= 100000){
        cout << "*";
        counter -= 100000;
    }
    if(counter > 0){
        cout << "." << endl;
    }
}

int main()
{
    /*
                                                                                                                               
                                                                                                                                                               
                                                                                     
                                                                                                                                             
    */
    int measure = 99;
    SortingMethod m = get_sorting_method ();
    while(measure < 5799){
            const int NO_OF_SONGS = read_file ("Tracks.txt", measure);
            if (NO_OF_SONGS < 0)
            {
                cout << "Reading file failed. Program terminates." << endl;
                return NO_OF_SONGS;
            }
            //                                         
            //                                                                
            switch (m)
            {
                case InsertionSort: insertion_sort(songs,NO_OF_SONGS) ; break ;
                case SelectionSort: selection_sort(songs,NO_OF_SONGS) ; break ;
                case BubbleSort:    bubble_sort   (songs,NO_OF_SONGS) ; break ;
                default:        cout << "Huh?" << endl ;
            }
            //                                 
            //                                     
            //                                                    
            print_visualisation(counter, m, measure);
        measure += 100;
    }

	return 0;
}
/*
          

                                                                      
                                                                      
                                                                      

                       
                                                                                                    
                                                                                                 
                                                                                                   

                    
                                                                                                 
                                                                                                 
                                                                                                   

                                                                                                                                                      
                                                                                               

                                                                                                                                                 
                                                                                              

                                                                                                                                    
                                                                                       
                                                                                                 

          

                              
     
     
     
     
      
      
      
       
        
         
          
           
             
              
                
                
                  
                    
                      
                        
                          
                           
                              
                                
                                   
                                      
                                         
                                           
                                            
                                                
                                                   
                                                       
                                                          
                                                              
                                                                  
                                                                     
                                                                      
                                                                          
                                                                               
                                                                                   
                                                                                        
                                                                                            
                                                                                                 
                                                                                                     
                                                                                                         
                                                                                                          
                                                                                                                
                                                                                                                     
                                                                                                                           
                                                                                                                                
                                                                                                                                      
                                                                                                                                           
                                                                                                                                                 
                                                                                                                                                      
                                                                                                                                                           
                                                                                                                                                            
                                                                                                                                                                   
                           
     
     
     
     
      
      
       
       
        
         
          
           
            
              
               
                 
                  
                    
                      
                       
                         
                            
                              
                                
                                  
                                     
                                       
                                          
                                             
                                                
                                                   
                                                      
                                                         
                                                            
                                                                
                                                                   
                                                                       
                                                                           
                                                                              
                                                                                  
                                                                                      
                                                                                          
                                                                                               
                                                                                                   
                                                                                                       
                                                                                                            
                                                                                                                 
                                                                                                                     
                                                                                                                          
                                                                                                                               
                                                                                                                                   
                                                                                                                                         
                                                                                                                                              
                                                                                                                                                   
                                                                                                                                                         
                                                                                                                                                               
                                                                                                                                                                    
                              
     
     
     
     
      
      
       
        
         
         
           
            
             
              
                
                 
                   
                     
                       
                        
                           
                             
                               
                                 
                                    
                                      
                                         
                                            
                                               
                                                 
                                                     
                                                        
                                                           
                                                              
                                                                  
                                                                     
                                                                         
                                                                             
                                                                                
                                                                                    
                                                                                        
                                                                                             
                                                                                                 
                                                                                                     
                                                                                                          
                                                                                                              
                                                                                                                   
                                                                                                                        
                                                                                                                            
                                                                                                                                 
                                                                                                                                      
                                                                                                                                            
                                                                                                                                                 
                                                                                                                                                      
                                                                                                                                                            
                                                                                                                                                                 
                                                                                                                                                                       
                           
     
     
     
     
      
      
       
        
         
         
           
            
             
              
                
                 
                   
                     
                       
                        
                           
                             
                               
                                 
                                    
                                      
                                         
                                            
                                               
                                                 
                                                     
                                                        
                                                           
                                                              
                                                                  
                                                                     
                                                                         
                                                                             
                                                                                
                                                                                    
                                                                                        
                                                                                             
                                                                                                 
                                                                                                     
                                                                                                          
                                                                                                              
                                                                                                                   
                                                                                                                        
                                                                                                                            
                                                                                                                                 
                                                                                                                                      
                                                                                                                                            
                                                                                                                                                 
                                                                                                                                                      
                                                                                                                                                            
                                                                                                                                                                 
                                                                                                                                                                       
                           
     
     
     
     
     
      
       
       
     
         
          
          
        
      
                
                 
                 
             
          
       
                           
                             
                            
                       
                 
             
         
                                            
                                              
                                             
                                       
                               
                        
                 
        
                                                                     
                                                                         
                                                                       
                                                               
                                                     
                                          
                                
                 
         
                                                                                                          
                                                                                                              
                                                                                                            
                                                                                                  
                                                                                    
                                                                      
                                                        
                                 
                   
         
                                                                                                                                                            
                                                                                                                                                                 
                                                                                                                                                               
                        
     
     
     
     
      
      
       
        
         
         
           
            
             
              
                
                 
                   
                     
                       
                        
                           
                             
                               
                                 
                                    
                                      
                                         
                                           
                                              
                                                 
                                                    
                                                        
                                                           
                                                              
                                                                 
                                                                     
                                                                         
                                                                             
                                                                                
                                                                                    
                                                                                        
                                                                                             
                                                                                                
                                                                                                     
                                                                                                          
                                                                                                              
                                                                                                                   
                                                                                                                        
                                                                                                                            
                                                                                                                                 
                                                                                                                                      
                                                                                                                                           
                                                                                                                                                 
                                                                                                                                                      
                                                                                                                                                           
                                                                                                                                                                 
                                                                                                                                                                      

                                                                                                                                                 
                                                                                    
                                                                                                                                               

                                                                                                                                                                         
                                                                                                         
                                                                                                                         
*/


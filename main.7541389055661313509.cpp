#define NDEBUG
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
//            
//                                                             
//                
//                                                             
//                                       
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

vector<Track> songs;
int part4_counter=0;
/*        */
#ifndef TIME
bool operator<(const Track& a, const Track& b)
{
    part4_counter++;
    if (a.artist==b.artist){
        if (a.cd==b.cd){
            if (a.year==b.year){
                return a.track_no<b.track_no;
            }else{
                return a.year<b.year;
            }
        }else{
            return a.cd<b.cd;
        }
    }else{
        return a.artist<b.artist;
    }
}

bool operator==(const Track& a, const Track& b)
{
    part4_counter++;
    return a.artist==b.artist&&a.cd==b.cd&&a.year==b.year&&a.track_no==b.track_no;
}
#endif
//                                  
#ifdef TIME
bool operator<(const Length& a, const Length& b)
{
    if (a.minutes==b.minutes){
        return a.seconds<b.seconds;
    }else{
        return a.minutes<b.minutes;
    }
}

bool operator==(const Length& a, const Length& b)
{
    return a.minutes==b.minutes&&a.seconds==b.seconds;
}

bool operator<(const Track& a, const Track& b)
{
    part4_counter++;
    if (a.time==b.time){
        if (a.artist==b.artist){
            if (a.title==b.title){
                return a.cd<b.cd;
            }else{
                return a.title<b.title;
            }
        }else{
            return a.artist<b.artist;
        }
    }else{
        return a.time<b.time;
    }
}

bool operator==(const Track& a, const Track& b)
{
    part4_counter++;
    return a.artist==b.artist&&a.cd==b.cd&&a.title==b.title&&a.time==b.time;
}
#endif
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

int size(vector<Track>& v){
    return static_cast<int>(v.size());
}

int read_songs (ifstream& infile, vector<Track>& songs)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    do {
        Track song ;
        infile >> song ;
        if (infile)
            songs.push_back(song);
    }
    while (infile);
    return size(songs) ;
}

int read_file (string filename)
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
    for (int i = 0 ; i < size(songs); i++)
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

bool is_sorted (vector<Track>& data, Slice s)
{//	              
	assert (valid_slice(s)&&s.to<size(data));
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
	assert (valid_slice(s) && s.to<size(data) && is_sorted(data,s));
//	                                          
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= data [i] )
			return i ;
	return s.to+1;
}

void shift_right (vector<Track>& data, Slice s )
{//	              
	assert (valid_slice (s)&&s.to<size(data));
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
    assert (length >= 0);
    if(!is_sorted(data,s)){
        show_all_tracks(data);
        cout<<length-1;
    }
    assert(is_sorted (data, s));
/*                 
                                                                                     
                                   
*/
	const int POS = find_position (data, mkSlice (0, length-1), y) ;
	if (POS < length){
		shift_right(data, mkSlice(POS, length-1)) ;
    }
	data [POS] = y ;
	length++;
}

void swap (vector<Track>& data, int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 && i<size(data) && j<size(data));
//                                                                
	const Track HELP = data [i];
	data [i] = data [j] ;
	data [j] = HELP;
}

//	                           
void insertion_sort (vector<Track>& data, int length )
{
	int sorted = 1 ;
    while ( sorted < length ){
       insert ( data, sorted, data[sorted] ) ;
    }
}

//	                           
int smallest_value_at (vector<Track>& data, Slice s )
{//	              
	assert (valid_slice(s)&&s.to<size(data));
//	                                                            
//	                                               
	int smallest_at = s.from ;
	for ( int index = s.from+1 ; index <= s.to ; index++ )
		if ( data [index] < data [smallest_at] )
			smallest_at = index ;
	return smallest_at ;
}

void selection_sort (vector<Track>& data, int length )
{	for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
	{   const int k = smallest_value_at (data, mkSlice (unsorted, length-1));
	    swap ( data, unsorted, k ) ;
	}
}

//	                        
bool bubble (vector<Track>& data, Slice s )
{//	              
	assert (valid_slice(s)&&s.to<size(data));
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

void bubble_sort (vector<Track>& data, int length )
{
    while ( !bubble ( data, mkSlice (0, length-1 ) ) )
        length-- ;
}

vector<Track> subslice(vector<Track>& data, Slice s){
    //	              
	assert (valid_slice(s)&&s.to<size(data));
    //               
    //                                                
    vector<Track> ret;
    for(int i = s.from; i < s.to; i++){
        ret.push_back(data[i]);
    }
    return ret;
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
    choice = max(1, min(choice,(int) NoOfSortingMethods)) ;
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
    #ifdef ANALASIS
    cout<<"Insertion sort:"<<endl;
    for(int i=99;i/100<=size(songs)/100;i+=100){
        part4_counter=0;
        Slice s={0,min(i,size(songs))};
        vector<Track> sub=subslice(songs,s);
        insertion_sort(sub,min(i,size(songs)));
        for(int j=0;j<part4_counter/100000;j++){
            cout<<'*';
        }
        if(part4_counter%100000>0){
            cout<<'.';
        }
        cout<<"\n";
    }
    cout<<"Selection sort:"<<endl;
    for(int i=99;i/100<=size(songs)/100;i+=100){
        part4_counter=0;
        Slice s={0,min(i,size(songs))};
        vector<Track> sub=subslice(songs,s);
        selection_sort(sub,min(i,size(songs)));
        for(int j=0;j<part4_counter/100000;j++){
            cout<<'*';
        }
        if(part4_counter%100000>0){
            cout<<'.';
        }
        cout<<"\n";
    }
    cout<<"Bubble sort:"<<endl;
    for(int i=99;i/100<=size(songs)/100;i+=100){
        part4_counter=0;
        Slice s={0,min(i,size(songs))};
        vector<Track> sub=subslice(songs,s);
        bubble_sort(sub,min(i,size(songs)));
        for(int j=0;j<part4_counter/100000;j++){
            cout<<'*';
        }
        if(part4_counter%100000>0){
            cout<<'.';
        }
        cout<<"\n";
    }
    #endif
    #ifndef ANALASIS
    SortingMethod m = get_sorting_method () ;
    cout << "Sorting tracks with " << methods[m] << " sort" << endl;
    part4_counter=0;
    switch (m)
    {
        case InsertionSort: insertion_sort(songs,NO_OF_SONGS) ; break ;
        case SelectionSort: selection_sort(songs,NO_OF_SONGS) ; break ;
        case BubbleSort:    bubble_sort   (songs,NO_OF_SONGS) ; break ;
        default:        cout << "Huh?" << endl ;
    }
    cout << "Tracks sorted." << endl;
    show_all_tracks (songs) ;
    //                    
    #endif
	return 0;
}
/*                          
                   
                                      
                                      
                                      
                                      
                                      
                                      
                                                              

                                                                             
                                                                    
                                                                                                       

                                                                   
                                                                                                 
                                                                                 
                                                                              
                                                         
                          */

/*                          
                   
                                                        
                                                          
                                                                                              
                                                                                                           

                                                                                                              
                          */


/*                                                                                  
                                                                                                */

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
vector<Track> tracklist;
int operatorcount=0;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
/*                           
                                              
 
                                                      
                            
     
                        
         
                                
                                               
                
                                       
         
            
                               
     
        
                                 
 

                                               
 
                                                      
                                                            
                                                
        
                     
 
*/
//                       

bool operator<(const Length& a, const Length& b)
{
    if(a.minutes<b.minutes)
        return true;
    else if(a.minutes==b.minutes && a.seconds<b.seconds)
        return true;
    else
        return false;
}

bool operator==(const Length& a, const Length& b)
{
    if(a.minutes==b.minutes && a.seconds==b.seconds)
        return true;
    else
        return false;
}
bool operator<(const Track& a, const Track& b)
{
    operatorcount++;
    if(a.time == b.time)
    {
        if(a.artist == b.artist)
        {
            if(a.title == b.title)
                return a.cd < b.cd;
            else
                return a.title < b.title;
        }
        else
            return a.artist < b.artist;
    }
    else
        return a.time<b.time;
}

bool operator==(const Track& a, const Track& b)
{
    operatorcount++;
    //                                                
    if(a.time == b.time && a.artist==b.artist && a.title==b.title)
                return a.cd == b.cd;
    else
        return false;
}
//

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

void fill_tracklist()
{
    int i=0;
    while(songs[i].artist[0]!=NULL)
    {
        tracklist.push_back(songs[i]);
        i++;
    }
}

void show_tracklist()
{
    for(int i=0; i<tracklist.size(); i++)
    {
        cout << tracklist[i] << endl;
    }
}

//                                                                           
int read_songs (ifstream& infile)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0 ;
    do {
        Track song ;
        infile >> song ;
        if (infile)
            tracklist.push_back(song);
    }
    while (infile && no_of_read_songs < MAX_NO_OF_SONGS);
    return tracklist.size() ;
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
	const int NO_OF_SONGS = read_songs (songsDBS);
	songsDBS.close();
	//                                                      
	return NO_OF_SONGS;
}

//                                                                           
void show_all_tracks (Track songs [MAX_NO_OF_SONGS], int no_of_songs)
{//               
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << i+1 << ". " << songs[i] << endl ;
}

/*                                                                       
                                                         
                                                                       */
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
//                 
//                                            
	Slice s = { from, to } ;
	return s ;
}

bool valid_slice (Slice s)
{//               
    assert (true) ;
//                 
//                                                                                    

	return 0 <= s.from && s.from <= s.to ;
}

bool is_sorted(Slice s)
{
    assert(valid_slice(s));

    bool sorted=true;
    for(int i=s.from; i<s.to&&sorted; i++)
        if(tracklist[i]>tracklist[i+1])
            sorted=false;
    return sorted;
}

int find_position(Slice s, Track track)
{
    assert(valid_slice(s) && is_sorted(s));
    for(int i=s.from; i<=s.to; i++)
        if(track<=tracklist[i]){
            return i;}
    return s.to+1;
}

void shift_right (Slice s)
{//	              
	assert (valid_slice (s)) ;	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
	for ( int i = s.to; i > s.from ; i-- )
		tracklist[i]  = tracklist[i-1];
}

void insert(Track track, int& sorted)
{
    Slice s = mkSlice(0, sorted-1);
    assert(tracklist.size()>0 && is_sorted(s));

    const int POS = find_position(mkSlice(0, sorted-1), track);
    if(POS<sorted){
        shift_right(mkSlice(POS, sorted));}
    tracklist[POS]=track;
    sorted++;
}

void swap (int  i, int  j )
{//	              
	assert ( i >= 0 && j >= 0 ) ;	//                         
						            //                         
//                                                                

	const Track HELP = tracklist[i];
	tracklist[i] = tracklist[j] ;
	tracklist[j] = HELP;
}

//	                           
void insertion_sort (int amnt)
{
	int sorted = 1 ;
    while ( sorted < amnt )
    {
        insert ( tracklist[sorted], sorted ) ;
    }
}

//	                           
int smallest_value_at ( Slice s )
{//	              
	assert (valid_slice (s)) ;	//                        
//	                                                            
//	                                               
	int smallest_at = s.from ;
	for ( int index = s.from+1 ; index <= s.to ; index++ )
		if ( tracklist[index] < tracklist[smallest_at] )
			smallest_at = index ;
	return smallest_at ;
}

void selection_sort (int amnt)
{	for ( int unsorted = 0 ; unsorted < amnt ; unsorted++ )
	{   const int k = smallest_value_at (mkSlice (unsorted, amnt-1));
	    swap ( unsorted, k ) ;
	}
}

//	                        
bool bubble ( Slice s )
{//	              
	assert (valid_slice(s));	//                          
//	               
//	                                                    
//	                                        
	bool is_sorted = true ;
	for ( int i = s.from ; i < s.to ; i++)
	    if ( tracklist[i] > tracklist[i+1])
		{	swap ( i, i+1 ) ;
			is_sorted = false ;
		}
	return is_sorted ;
}

void bubble_sort (int amnt)
{
    int i=amnt;
    while ( !bubble ( mkSlice (0, i)))
        i--;
}

/*                                                                       
                                      
                   
                                                                      
                                    
                                          
                                                                       */
enum SortingMethod {InsertionSort,SelectionSort,BubbleSort,NoOfSortingMethods};
string methods [] = {"insertion", "selection", "bubble"} ;

int maximum(int a, int b)
{
    if(a>b)
        return a;
    return b;
}
int minimum(int a, int b)
{
    if(a<b)
        return a;
    return b;
}

SortingMethod get_sorting_method ()
{
    cout << "What sorting method do you want to use? " << endl ;
    for (int m = 0; m < NoOfSortingMethods; m++)
        cout << m+1 << ": " << methods[m] << " sort" << endl ;
    int choice ;
    cin >> choice ;
    choice = maximum (1, minimum (choice, NoOfSortingMethods)) ;
    return static_cast<SortingMethod>(choice-1) ;
}

void visualize(int i, ofstream& outfile)
{
    int counter=0;
    while(i>100000)
    {
        outfile.put('*');
        i=i-100000;
        counter++;
    }
    cout << i << endl;
    if(i>0)
    {
        outfile.put('.');
    }
}

int main()
{
//                                             
/*
	                                                 
	                    
	 
                                                                   
	                       
     
                                              
                                                                    
                    
              
     
                                                                      
                                                                      
                                                                   
                                                
     
                                     
                                           
                       
                            
                                                                                         
	         
*/
//                             
    const int NO_OF_SONGS = read_file ("Tracks.txt");
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }
    std::ofstream outfile("Output.txt");
    int counter=99;
    string output="";
    while(counter!=5899)

    {
        operatorcount=0;
        read_file("Tracks.txt");
        insertion_sort(counter);
        cout << "Insertion from tracks 0 to " << counter << endl;

        outfile << "Insertion from tracks 0 to " << counter << " used " << '\n'; visualize(operatorcount, outfile); outfile << '\n';

        operatorcount=0;
        read_file("Tracks.txt");
        selection_sort(counter);
        cout << "Selection sort from tracks 0 to " << counter << endl;

        outfile << "Selection from tracks 0 to " << counter << " used " << '\n'; visualize(operatorcount, outfile); outfile << '\n';

        operatorcount=0;
        read_file("Tracks.txt");
        bubble_sort(counter);
        cout << "Bubble sort from tracks 0 to " << counter << endl;

        outfile << "Bubble from tracks 0 to " << counter << " used " << '\n'; visualize(operatorcount, outfile); outfile << '\n';

        counter=counter+100;
    }
}


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
#include <algorithm>

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

vector<Track> tracklist;                    //                                   

int counter;                                //                           

/*                                                                       
                                        
                                                                       */
//                      
bool operator<(const Length& a, const Length& b)
{
    int timea = a.minutes*60 + a.seconds,
        timeb = b.minutes*60 + b.seconds;

    if (timea < timeb)
        return true;

    return false;
}

bool operator==(const Length& a, const Length& b)
{
    int timea = a.minutes*60 + a.seconds,
        timeb = b.minutes*60 + b.seconds;

    if (timea == timeb)
        return true;

    return false;
}

//                      
bool operator==(const Track& a, const Track& b)
{
    counter++;
    if (a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no)   //                                                  
    //                                                                                                               
        return true;

    return false;
}

bool operator<(const Track& a, const Track& b)
{
    counter++;
    if (a.artist <= b.artist && a.cd <= b.cd && a.year <= b.year && a.track_no < b.track_no)    //                                                  
    //                                                                                                               
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
    getline(infile, track.artist);       //       
    getline(infile, track.cd);           //   
    infile >> track. year ;              //     
    skip_to_next_newline(infile) ;
    infile >> track. track_no ;          //             
    skip_to_next_newline(infile) ;
    getline(infile, track.title);        //            
    getline(infile, track.tags);         //           
    infile >> track.time ;               //           
    skip_to_next_newline(infile) ;
    getline(infile, track.country);      //        
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
    int tracks = 0;
    Track temptrack;
    while (infile >> temptrack)
    {
        tracklist.push_back(temptrack);
        tracks++;
    }
    return tracks;
}

int read_file (string filename)
{//               
    assert (tracklist.size() == 0) ;
/*                 
                                                                              
                                                                                             
                                        
*/
    ifstream songsDBS (filename.c_str());
    if (!songsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
	const int NO_OF_SONGS = read_songs(songsDBS, tracklist);
	songsDBS.close();
	cout << "Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

//                                                                           
void show_all_tracks (vector<Track>& songs)
{//               
    assert (tracklist.size() > 0) ;
/*                 
                                                                  
*/
    for (int i = 0; i < tracklist.size(); i++)
        cout << tracklist[i] << endl;
}

/*                                                                       
                                                         
                                                                       */

void swap_elements (Track& a, Track& b)
{
//               
    assert(true);
//                                  
    Track temp1 = a,
          temp2 = b;

    a = temp2;
    b = temp1;
}

void insertionsort(vector<Track>& tracklist)
{
//               
    assert(tracklist.size() > 1);
//                                                                                         
    counter = 0;
    int j;
    Track temptrack;

    for (int i = 0; i < tracklist.size(); i++)
    {
        j = i;
        temptrack = tracklist[i];
        while (j>0 && temptrack < tracklist[j-1])
        {
            tracklist[j] = tracklist[j-1];
            j--;
        }
        tracklist[j] = temptrack;
    }
}

void selectionsort(vector<Track>& tracklist)
{
//               
    assert(tracklist.size() > 1);
//                                                                                         
    counter = 0;
    int j, least;

    for (int i = 0; i < tracklist.size(); i++)
    {
        least = i;
        for (int j = i; j < tracklist.size(); j++)
        {
            if (tracklist[j] < tracklist[least])
                least = j;
        }
        swap_elements(tracklist[i], tracklist[least]);
    }
}

void bubblesort(vector<Track>& tracklist)
{
//               
    assert(tracklist.size() > 1);
//                                                                                         
    counter = 0;
    for (int i = 0; i < tracklist.size(); i++)
    {
        for (int j = 0; j < tracklist.size()-1; j++)
            if (tracklist[i] < tracklist[j])
                swap_elements(tracklist[i], tracklist[j]);
    }
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
    int choice, NoOfSM = NoOfSortingMethods ;
    cin >> choice ;
    choice = max(1, min(choice, NoOfSM)) ;
    return static_cast<SortingMethod>(choice-1) ;
}

int main()
{
/*
	                                
	                                   
	 
	                                                                                           
	                                                                                                                    
	                                              
                           
                               
	 
	                
*/
    const int NO_OF_SONGS = read_file("Tracks.txt");
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;     //                                  
	    return NO_OF_SONGS;
    }
    SortingMethod m = get_sorting_method () ;
    cout << "Sorting tracks with " << methods[m] << " sort" << endl;
    switch (m)
    {
        case InsertionSort: insertionsort(tracklist); break;
        case SelectionSort: selectionsort(tracklist); break;
        case BubbleSort:    bubblesort(tracklist); break;
        default:        cout << "Choose 1, 2 or 3." << endl;
    }
    cout << endl
         << "Tracks sorted by Artist, CD, Year and Track# respectively." << endl
         << "It took this algorithm " << counter << " steps." << endl
         << endl;

    string answer;
    cout << "Show track-list? (y/n)" << endl;
    cin >> answer;
    if (answer == "y")
        show_all_tracks(tracklist);

	return 0;
}

/*
            

                                                                                      
                                                                           
                                                                            
                                                                            

                                                                                                                                    
                                                                                                              
                                                                                                                                                             
                                                                                                                                                
                                                                                                                          
                                                                                                                               

                                                                                            
                                                                                                                                                                             
                                                                                                                                                                                           
                                                                                                  
                                                                                                  
                                                                                                 
         
         
         
         
         
         
         
         
         
         
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
           
           
           
           
           
           
           
           
           
           
           
           
           
           
           
           
           
            
            
            
            
            
            
            
            
            
            

                                                                                                                                  
                                                                                                     
                                                                                                                          
                                                                                                                                                                 
*/


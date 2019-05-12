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

const int MAX_NO_OF_SONGS = 6000;           //                                                             
vector<Track> songs;                        //                                 
int operatorUse = 0;                        //                                                                                       
                                            //                         

/*                                                                       
                                
                                                               
                                                                         
                                                                       */
bool operator< (const Length& a, const Length& b)
{
//               
    assert (true);
/*                
                                                                             
*/
    return (a.minutes*60 + a.seconds < b.minutes*60 + b.seconds);
}

bool operator== (const Length& a, const Length& b)
{
//               
    assert (true);
/*                
                                                                               
*/
    return (a.minutes*60 + a.seconds == b.minutes*60 + b.seconds);
}

//	                                  
bool operator> (const Length& a, const Length& b)
{
//               
    assert (true);
/*                
                                                                             
*/
	return b < a;
}

bool operator<= (const Length& a, const Length& b)
{
//               
    assert (true);
/*                
                                                                              
*/
	return !(b < a);
}

bool operator>= (const Length& a, const Length& b)
{
//               
    assert (true);
/*                
                                                                              
*/
	return b <= a;
}

bool operator< (const Track& a, const Track& b)
{
//               
    assert (true);
/*                
                                                                                                                                                 
                                                                                                                   
                                
*/
    if (a.artist < b.artist)
        return true;
    else if (a.artist == b.artist)
    {
        if (a.cd < b.cd)
            return true;
        else if (a.cd == b.cd)
        {
            if (a.year < b.year)
                return true;
            else if (a.year == b.year)
            {
                if (a.track_no < b.track_no)
                    return true;
                else if (a.track_no == b.track_no)
                {
                    if (a.title < b.title)
                        return true;
                    else if (a.title == b.title)
                    {
                        if (a.tags < b.tags)
                            return true;
                        else if (a.tags == b.tags)
                        {
                            if (a.time < b.time)
                                return true;
                            else if (a.time == b.time)
                            {
                                if (a.country < b.country)
                                    return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool operator== (const Track& a, const Track& b)
{
//               
    assert (true);
/*                
                                                                                     
*/
    return (a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no && a.title == b.title && a.tags == b.tags &&
    a.time == b.time && a.country == b.country);
}

//	                                 
bool operator> (const Track& a, const Track& b)
{
//               
    assert (true);
/*                
                              
*/
	return b < a;
}

bool operator<= (const Track& a, const Track& b)
{
//               
    assert (true);
/*                
                              
*/
	return !(b < a);
}

bool operator>= (const Track& a, const Track& b)
{
//               
    assert (true);
/*                
                              
*/
	return b <= a;
}

/*                                                                       
                            
                                                                       */
istream& operator>> (istream& in, Length& length)
{//               
    assert (true);
/*                 
                                                                                                      
*/
    char colon;
    in >> length.minutes >> colon >> length.seconds;
    return in;
}

ostream& operator<< (ostream& out, const Length length)
{//               
    assert (true);
/*                 
                                                                       
*/
    out << length.minutes << ':';
	if (length.seconds < 10)
		out << '0';
	out << length.seconds;
	return out;
}

void skip_to_next_newline (istream& infile)
{//               
    assert (true);
/*                 
                                                                        
*/
    string remains;
    getline (infile, remains);
}

istream& operator>> (istream& infile, Track& track)
{//               
    assert (true);
/*                 
                                                                                                                   
                                      
*/
    getline(infile,track.artist);       //       
    getline(infile,track.cd);           //   
    infile >> track.year;               //     
    skip_to_next_newline(infile);
    infile >> track.track_no;           //             
    skip_to_next_newline(infile);
    getline(infile,track.title);        //            
    getline(infile,track.tags);         //           
    infile >> track.time;               //           
    skip_to_next_newline(infile);
    getline(infile,track.country);      //        
    skip_to_next_newline(infile);
    return infile;
}

//                                                                                                        
ostream& operator<< (ostream& out, const Track track)
{//               
    assert (true);
/*                 
                                                                                
*/
    out << track.artist   << endl;
    out << track.cd       << endl;
    out << track.year     << endl;
    out << track.track_no << endl;
    out << track.title    << endl;
    out << track.tags     << endl;
    out << track.time     << endl;
    out << track.country  << endl;
    out << endl;
    return out;
}

//                                                  
int read_songs (ifstream& infile, vector<Track>& songs)
{//               
    assert (infile.is_open ());
/*                 
                                                                              
                                                           
*/
    int no_of_read_songs = 0;
    do
    {
        Track song;
        infile >> song;
        if (infile)
        {
            songs.push_back(song);
            no_of_read_songs++;
        }
    }
    while (infile && no_of_read_songs < MAX_NO_OF_SONGS);
    return no_of_read_songs;
}

int read_file (string filename)
{//               
    assert (songs.size() == 0);
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

//                                                  
void show_all_tracks (vector<Track>& songs, int no_of_songs)
{//               
    assert (no_of_songs < MAX_NO_OF_SONGS);
/*                 
                                                                  
*/
    for (int i = 0 ; i < no_of_songs; i++)
        cout << songs[i] << endl;
}

/*                                                                                                      
                                                                                                        
                                                                                                      */
struct Slice
{
	int from; 	//             
	int to; 	//           
};

Slice makeSlice (int from, int to)
{//	              
	assert (0 <= from && from <= to);
/*                 
                                              
*/	Slice s = {from, to};
	return s;
}

bool valid_slice (Slice s)
{//               
    assert (true);
/*                 
                                                                                      
*/
	return 0 <= s.from && s.from <= s.to;
}

bool is_sorted(vector<Track> data, Slice s, bool trackLength)
{//	              
	assert (valid_slice(s));	//                           
//	               
//	                 	                                
//						                                
//						   
//						                            
	for (int i = s.from; i < s.to; i++)
    {
        operatorUse++;
        if (operatorUse % 100000 == 0)
            cout << "*"; //                                                                                      
        if (!trackLength)
        {
            if (data[i] > data[i+1])
                return false;
        }
        else
            if (data[i].time > data[i+1].time)
                return false;
    }
	return true;
}

int find_position (vector<Track> data, Slice s, Track y, bool trackLength)
{//	              
	assert (valid_slice(s) && is_sorted(data, s, trackLength));    //                           
//	                                          
	for (int i = s.from; i <= s.to; i++)
    {
        operatorUse++;
        if (operatorUse % 100000 == 0)
            cout << "*"; //                                                                                      
        if (!trackLength)
        {
            if (y <= data[i])
                return i;
        }
        else if (y.time <= data[i].time)
            {
                return i;
            }
    }
	return s.to+1;
}

void shift_right (vector<Track>& data, Slice s)
{//	              
	assert (valid_slice(s));	//                               
//	                               	  	                
//			    	               	  	                  
//						   
//			    	             		  	              
	for (int i = s.to+1; i > s.from; i--)
		data[i] = data[i-1];
}

void insert (vector<Track>& data, int& length, Track y, bool trackLength)
{//               
    Slice s = makeSlice(0, length-1);
    assert (length > 0 && is_sorted(data, s, trackLength));
/*                 
                                                                                     
                                   
*/
	const int POS = find_position(data, makeSlice(0, length-1), y, trackLength);
	if (POS < length)
		shift_right(data, makeSlice(POS, length-1));
	data[POS] = y;
	length++;
}

//	                           
void insertion_sort (vector<Track>& data, int length, bool trackLength)
{
//               
    assert (length > 0);
/*                
                                                                
*/
	int sorted = 1;
    while (sorted < length)
        insert (data, sorted, data[sorted], trackLength);
    cout << ".\n"; //                                                                                      
}

//	                           
int smallest_value_at (vector<Track> data, Slice s, bool trackLength)
{//	              
	assert (valid_slice(s));	//                        
//	                                                            
//	                                               
	int smallest_at = s.from;
	for (int index = s.from+1; index <= s.to; index++)
    {
        if (!trackLength)
        {
            if (data[index] < data[smallest_at])
                smallest_at = index;
        }
        else
            if (data[index].time < data[smallest_at].time)
                smallest_at = index;
        operatorUse++;
        if (operatorUse % 100000 == 0)
            cout << "*"; //                                                                                      
    }
	return smallest_at;
}

void swap (vector<Track>& data, int  i, int  j)
{//	              
	assert (i >= 0 && j >= 0 && i < data.size() && j < data.size());
//                                                                 
	const Track HELP = data[i];
	data[i] = data[j];
	data[j] = HELP;
}

void selection_sort (vector<Track>& data, int length, bool trackLength)
{
//               
    assert (length > 0);
/*                
                              
*/
    for (int unsorted = 0; unsorted < length; unsorted++)
	{
	    const int k = smallest_value_at(data, makeSlice(unsorted, length-1), trackLength);
	    swap(data, unsorted, k);
	}
	cout << ".\n"; //                                                                                      
}

//	                         
bool bubble (vector<Track>& data, Slice s, bool trackLength)
{//	              
	assert (valid_slice(s));	//                          
//	               
//	                                                    
//	                                       
	bool sorted = true;
	for (int i = s.from; i < s.to; i++)
    {
        operatorUse++;
        if (operatorUse % 100000 == 0)
            cout << "*"; //                                                                                      
        if (!trackLength)
        {
            if (data[i] > data[i+1])
            {
                swap(data, i, i+1);
                sorted = false;
            }
        }
        else
            if (data[i].time > data[i+1].time)
            {
                swap(data, i, i+1);
                sorted = false;
            }
    }
	return sorted;
}

void bubble_sort (vector<Track>& data, int length, bool trackLength)
{
//               
    assert (length > 0);
/*                
                              
*/
    while (!bubble(data, makeSlice(0, length-1), trackLength))
        length--;
    cout << ".\n"; //                                                                                      
}

/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */
enum SortingMethod {InsertionSort, SelectionSort, BubbleSort, NoOfSortingMethods};
string methods [] = {"insertion", "selection", "bubble"};

SortingMethod get_sorting_method ()
{
//                               
//                                                                           
    cout << "What sorting method do you want to use? " << endl;
    for (int m = 0; m < NoOfSortingMethods; m++)
        cout << m+1 << ": " << methods[m] << " sort" << endl;
    int choice;
    cin >> choice;
    choice = max(1, min(choice, (int)NoOfSortingMethods));
    return static_cast<SortingMethod>(choice-1);
}

bool SortByTrackLength ()
{
//               
    assert (true);
/*                
                                                                                                    
                                                                                   
*/
    string choice;
    do
    {
    cout << "Would you like to sort by track length instead of alphabetically? (y/n) " << endl;
    cin >> choice;
    } while(choice != "y" && choice != "n");
    return choice == "y";
}

int main()
{
	const int NO_OF_SONGS = read_file("Tracks.txt");
	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }
    SortingMethod m = get_sorting_method();
    cout << "Sorting tracks with " << methods[m] << " sort." << endl;
    bool trackLength = SortByTrackLength();
    switch(m)
    {
        case InsertionSort: insertion_sort(songs, NO_OF_SONGS, trackLength); break;
        case SelectionSort: selection_sort(songs, NO_OF_SONGS, trackLength); break;
        case BubbleSort:    bubble_sort   (songs, NO_OF_SONGS, trackLength); break;
        default:        cout << "Huh?" << endl;
    }
    cout << "Tracks sorted with " << methods[m] << " sort." << endl << "Number of comparison operations used: " << operatorUse << endl;
//                                                                                                                                      
                                          //                                                                                              
                                          //                                                                         
	return 0;
}

/*                                                                                                                                           
                                                      
                                                                                                                                                
                                                                                                                                                 
                                                                                                                                             
                                                                                     
                                                                                                                                                    
                                                                                                                                                   
                          
                                                                                                                                                
                                                                                                                                                  
                                                                                                                                                 
                                                                                                                                               
                    */


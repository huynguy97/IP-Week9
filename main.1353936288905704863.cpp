//                                                 
//                                            

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

vector<Track> songs;
int counter;

/*                                                                       
                                
                                                               
                                                                         
                                                                       */

bool operator<(const Length& a, const Length& b)
{
    //              
    assert (true);
    //               
    //                                                                                 
    //                                                                

    if (a.minutes == b.minutes)
        return a.seconds < b.seconds;
    else
        return a.minutes < b.minutes;
}

bool operator==(const Length& a, const Length& b)
{
    //              
    assert (true);
    //               
    //                                                                                        
    //                                                              

    return (a.minutes == b.minutes && a.seconds == b.seconds);
}

bool operator<(const Track& a, const Track& b)
{
    //              
    assert (true);
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

    counter++;

    if (a.time == b.time)
    {
        if (a.artist == b.artist)
        {
            if (a.title == b.title)
                return a.cd < b.cd;
            else
                return a.title < b.title;
        }
        else
            return a.artist < b.artist;
    }
    else
        return a.time < b.time;
}

bool operator==(const Track& a, const Track& b)
{
    //              
    assert (true);
    //               
    //                                                                                                                               
    //                                                                                                             
    //                                                                                                                               
    //                                                                                          

    //                                                                                              

    counter++;
    return (a.time == b.time && a.artist == b.artist && a.title == b.title && a.cd == b.cd);
}

//	                                 
bool operator>(const Track& a, const Track& b)
{
    //              
    assert (true);
    //               
    //                                                                

	return b < a ;
}

bool operator<=(const Track& a, const Track& b)
{
    //              
    assert (true);
    //               
    //                                                                                                    

	return !(b < a) ;
}

bool operator>=(const Track& a, const Track& b)
{
    //              
    assert (true);
    //               
    //                                                                       

	return b <= a ;
}

/*                                                                       
                            
                                                                       */
istream& operator>> (istream& in, Length& length)
{
    //              
    assert (true) ;
    //               
    //                                                                                                   

    char colon ;
    in >> length.minutes >> colon >> length.seconds ;
    return in ;
}

ostream& operator<< (ostream& out, const Length length)
{
    //              
    assert (true) ;
    //               
    //                                                                     

    out << length.minutes << ':';
	if (length.seconds < 10)
		out << '0';
	out << length.seconds;
	return out ;
}

void skip_to_next_newline (istream& infile)
{
    //              
    assert (true) ;
    //               
    //                                                                     

    string remains ;
    getline (infile, remains) ;
}

istream& operator>> (istream& infile, Track& track)
{
    //              
    assert (true) ;
    //               
    //                                                                                                                
    //                                   

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
{
    //              
    assert (true) ;
    //               
    //                                                                             

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

int read_songs (ifstream& infile)
{
    //              
    assert (infile.is_open ());
    //               
    //                                                                           
    //                                                        

    int no_of_read_songs = 0;
    Track song;

    while (!infile.eof())
    {
        infile >> song;
        songs.push_back(song);
        no_of_read_songs++;
    }

    return no_of_read_songs;
}

int read_file (string filename)
{
    //              
    assert (songs.size() == 0) ;
    //               
    //                                                                           
    //                                                                                          
    //                                     

    ifstream songsDBS(filename.c_str());

    if (!songsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }

    cout << "Reading '" << filename << "'." << endl;
	const int NO_OF_SONGS = read_songs (songsDBS);
	songsDBS.close();
	cout << "Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

void show_all_tracks (vector<Track>& songs)
{
    //              
    assert (true) ;
    //               
    //                                        

    for (int i = 0; i < songs.size(); i++)
        cout << songs[i] << endl;
}

/*                                                                       
                                                         
                                                                       */
struct Slice
{
	int from; 	//             
	int to; 	//           
} ;

Slice mkSlice (int from, int to)
{
    //              
	assert (0 <= from && from <= to);
    //               
    //                                           

	Slice s = {from, to};
	return s;
}

bool valid_slice (Slice s)
{
    //              
    assert (true);
    //               
    //                                                                                   

	return 0 <= s.from && s.from <= s.to;
}

typedef Track El;

bool is_sorted (vector<El>& data, Slice s)
{
    //              
	assert (valid_slice(s) && s.to < data.size());
    //               
    //                  	                                
	//	  				                                    
	//					       
	//					                                

	bool sorted = true;

	for (int i = s.from; i < s.to && sorted; i++)
		if (data[i] > data[i+1])
			sorted = false;

	return sorted;
}

int find_position (vector<El>& data, Slice s, El y)
{
    //              
	assert (valid_slice(s) && is_sorted(data,s) && s.to < data.size());
	//               
	//                           

	for (int i = s.from; i <= s.to; i++)
		if (y <= data[i])
			return i;

	return s.to+1;
}

void shift_right (vector<El>& data, Slice s)
{
    //              
	assert (valid_slice (s) && s.to < data.size()-1);
	//                                	  	                
	//		    	                  	  	                  
	// 					   
	//		    	                		  	              

	for (int i = s.to+1; i > s.from; i--)
		data[i] = data[i-1];
}

void insert (vector<El>& data, int& length, El y)
{
    //              
    Slice s = mkSlice(0,length-1);
    assert (length >= 0);
    assert(is_sorted (data, s));
    //               
    //                                                                                  
    //                                

	const int POS = find_position(data, mkSlice(0, length-1), y);

	if (POS < length)
		shift_right(data, mkSlice(POS, length-1));

	data[POS] = y;
	length++;
}

void swap (vector<El>& data, int  i, int  j)
{
    //              
	assert (i >= 0 && j >= 0 && i < data.size() && j < data.size());
    //               
    //                                                

	const El HELP = data[i];
	data[i] = data[j];
	data[j] = HELP;
}

void insertion_sort (vector<El>& data, int length)
{
    //              
    assert(true);
    //               
    //                                                        

	int sorted = 1;

    while (sorted < length)
        insert(data, sorted, data[sorted]);
}

int smallest_value_at (vector<El>& data, Slice s)
{
    //              
	assert (valid_slice (s) && s.to < data.size());
    //               
    //                                                                                             

	int smallest_at = s.from;

	for (int index = s.from+1; index <= s.to; index++)
		if (data[index] < data[smallest_at])
			smallest_at = index;

	return smallest_at;
}

void selection_sort (vector<El>& data, int length)
{
    //              
    assert(true);
    //               
    //                                                        

    for (int unsorted = 0; unsorted < length; unsorted++)
	{
	    const int k = smallest_value_at(data, mkSlice(unsorted, length-1));
	    swap(data, unsorted, k);
	}
}

bool bubble (vector<El>& data, Slice s)
{
    //              
	assert (valid_slice(s) && s.to < data.size());
	//               
    //                                                                                            

	bool is_sorted = true;

	for (int i = s.from; i < s.to; i++)
	    if (data[i] > data[i+1])
		{
		    swap (data, i, i+1);
			is_sorted = false;
		}

	return is_sorted;
}

void bubble_sort (vector<El>& data, int length)
{
    //              
    assert(true);
    //               
    //                                                     

    while (!bubble(data, mkSlice(0, length-1)))
        length--;
}

/*                                                                       
                                 
                                                                       */

int maximum(int a, int b)
{
    //              
    assert(true);
    //               
    //                                        

    if (a > b)
        return a;
    else
        return b;
}

int minimum(int a, int b)
{
    //              
    assert(true);
    //               
    //                                         

    if (a < b)
        return a;
    else
        return b;
}

/*                                                                       
                                      
                   
                                                                      
                                           
                                          
                                                                       */
enum SortingMethod {InsertionSort,SelectionSort,BubbleSort,NoOfSortingMethods};
string methods[] = {"insertion", "selection", "bubble"};

SortingMethod get_sorting_method()
{
    cout << "\nWhat sorting method do you want to use? " << endl;
    for (int m = 0; m < NoOfSortingMethods; m++)
        cout << m+1 << ": " << methods[m] << " sort" << endl;
    int choice;
    cin >> choice;
    choice = maximum(1, minimum(choice, static_cast<int>(NoOfSortingMethods)));
    return static_cast<SortingMethod>(choice-1);
}

bool open_output_file (ofstream& outfile)
{
//                
    assert (true);

//                 
//                               
//                                           

    cout << "Please enter a file name. The file names may not contain layout symbols." <<endl;
    cout <<"Enter name of output file: ";
    string file;
    cin >> file;

    outfile.open (file.c_str());

    if (outfile.is_open())
    {
        cout << "File opened" << endl;
        return true;
    }
    else
    {
        cout << "Error.";
        return false;
    }
}

void tally_stars(SortingMethod m, ofstream& outfile)
{
    //              
    assert(true);
    //               
    //                                                                                            
    //                                                                          
    //                                        
    //                                                                        

    open_output_file(outfile);
    outfile << "Sorting tracks with " << methods[m] << " sort" << endl;
    for (int i = 100; i <= 5800; i = i+100)
    {
        vector<El> copy;
        copy = songs;

        switch (m)
        {
            case InsertionSort: insertion_sort(copy, i); break;
            case SelectionSort: selection_sort(copy, i); break;
            case BubbleSort:    bubble_sort   (copy, i); break;
            default:            cout << "Huh?" << endl;
        }

        outfile << "Slice 0-" << i-1 << ": \t";
        while (counter != 0)
        {
            if (counter >= 100000)
            {
                outfile << "*";
                counter = counter - 100000;
            }
            else
            {
                outfile << ".";
                counter = 0;
            }
        }
        outfile << endl;
    }
}

int main()
{
	const int NO_OF_SONGS = read_file ("Tracks.txt");

	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }

    SortingMethod m = get_sorting_method();
    ofstream outfile;
    counter = 0;
    tally_stars(m, outfile);

    cout << "Sorting tracks with " << methods[m] << " sort" << endl;

    switch (m)
    {
        case InsertionSort: insertion_sort(songs,songs.size()); break;
        case SelectionSort: selection_sort(songs,songs.size()); break;
        case BubbleSort:    bubble_sort   (songs,songs.size()); break;
        default:            cout << "Huh?" << endl;
    }

    cout << "Tracks sorted." << endl;
    show_all_tracks (songs);
    cout << "Number of comparison operations: " << counter << endl;
	return 0;
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


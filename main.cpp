#include <iostream>
#include <vector>
#include <math.h>
#include <sstream>
#include <string>
#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>
using namespace std;

vector<double>
input_numbers( istream& in,size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}

vector<double>
make_histogram(Input data)
{
    double min,max;
    find_minmax(data.numbers,min,max);
    vector<double> bins(data.bin_count,0);
    double bin_size = (max - min) / data.bin_count;
    for(size_t i=0; i<data.numbers.size(); i++)
    {
        bool found=false;
        for(size_t j=0; j<(data.bin_count-1) && !found; j++)
        {
            auto lo = min + j*bin_size;
            auto hi = min + (j + 1)*bin_size;
            if((lo <= data.numbers[i]) && (data.numbers[i]<hi))
            {
                bins[j]++;
                found =true;
            }
        }
        if(!found)
        {
            bins[data.bin_count-1]++;
        }
    }
    return bins;
}

Input
read_input(istream& in,bool prompt) {
    Input data;
    if(prompt)
    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    if(prompt)
    cerr << "Enter numbers: ";
    data.numbers = input_numbers(cin,number_count);

    if(prompt)
    cerr <<"Enter bin count:";
    in >> data.bin_count;




    return data;
}


void
show_histogram_text(const vector<double>bins)
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

    size_t max_bin = bins[0];
    for(size_t bin:bins)
    {
        if(max_bin<bin)
        {
            max_bin=bin;
        }
    }


    for(size_t bin:bins)
    {
        size_t height = bin;

        if (height > MAX_ASTERISK)
        {
            height = MAX_ASTERISK * (static_cast<double>(bin) /max_bin);
        }
        if(bin<100)
            for(size_t i=0; i<(MAX_ASTERISK-bin); i++)
            {
                cout<<" ";
            }
        for(size_t i=0; i< height; i++)
        {
            cout<<"*";

        }

        cout <<"|" << bin;
        cout << endl;
    }
}


int main(int argc, char* argv[])
{
    if(argc>1)
    {
        cerr <<"kolvo: "<< argc<<endl;
        for(int i=0;i<argc; i++)
        {
            cerr<<"argv["<<i<<"]="<<argv[i]<<endl;
        }
        return 0;
    }
    curl_global_init(CURL_GLOBAL_ALL);
    Input input;
    input = read_input(cin,true);
    const auto bins = make_histogram(input);
    show_histogram_svg(bins);

    return 0;
}

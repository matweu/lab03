#include <iostream>
#include <vector>
using namespace std;

vector<double>
input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}
void
find_minmax(const vector<double> &numbers,double &min,double &max)
{
    min=numbers[0];
    max=numbers[0];
    for (double number : numbers )
    {
        if(min>number)
        {
            min=number;
        }
        if (max<number)
        {
            max=number;
        }
    }

}
vector<double>
make_histogram(const vector<double> numbers,size_t bin_count,double max,double min,size_t number_count)
{
    vector<double> bins(bin_count,0);
    double bin_size = (max - min) / bin_count;
    for(size_t i=0; i<number_count; i++)
    {
        bool found=false;
        for(size_t j=0; j<(bin_count-1) && !found; j++)
        {
            auto lo = min + j*bin_size;
            auto hi = min + (j + 1)*bin_size;
            if((lo <= numbers[i]) && (numbers[i]<hi))
            {
                bins[j]++;
                found =true;
            }
        }
        if(!found)
        {
            bins[bin_count-1]++;
        }
    }
    return bins;
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
void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() {
    cout << "</svg>\n";
}
void
svg_text(double left, double baseline, string text)
{
    //cout << "<text x='" << left << "' y='35'>anything you want</text>";
    cout << "<text x='" << left << "' y='"<< baseline << "'>"<< text <<"</text>" <<endl;
}
void svg_rect(double x, double y, double width, double height,string stroke, string fill){
    //cout<<"<rect x='0' y='0' width='100' height='200' />";
    //cout<<"<rect x='50' y='0' width='30' height='30' stroke='red' fill='#ffeeee'/>";
    cout<<"<rect x='" << x <<"' y='"<< y <<"' width='"<< width <<"' height='"<< height <<"' stroke='"<<stroke<<"' fill='"<<fill<<"' />" <<endl;
}
void
show_histogram_svg(const vector<double>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const string stroke = "black";
    const string fill = "#3CB371";

    svg_begin(400, 300);
    double top = 0;
    for (size_t bin : bins)
    {
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,"blue", "#3CB371");
        top += BIN_HEIGHT;
    }
    /*svg_rect(50, 0, bins[0] * 10, 30);
    svg_text(20, 20, to_string(bins[0]));*/
    svg_end();
}
int main()
{
    size_t number_count;
    cerr <<"Enter number count:";
    cin >> number_count;
    const auto numbers = input_numbers(number_count);
    size_t bin_count;
    cerr <<"Enter bin count:";
    cin >> bin_count;
    double min,max;
    find_minmax(numbers,min,max);
    const auto bins = make_histogram(numbers, bin_count,max,min,number_count);
    show_histogram_svg(bins);

    return 0;
}
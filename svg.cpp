#include "histogram.h"

void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_text(double left, double baseline, string text)
{
    //cout << "<text x='" << left << "' y='35'>anything you want</text>";
    cout << "<text x='" << left << "' y='"<< baseline << "'>"<< text <<"</text>" <<endl;
}

void svg_rect(double x, double y, double width, double height,string stroke, string fill){
    //cout<<"<rect x='0' y='0' width='100' height='200' />";
    //cout<<"<rect x='50' y='0' width='30' height='30' stroke='red' fill='#ffeeee'/>";
    cout<<"<rect x='" << x <<"' y='"<< y <<"' width='"<< width <<"' height='"<< height <<"' stroke='"<<stroke<<"' fill='"<<fill<<"' />" <<endl;
}

void svg_end() {
    cout << "</svg>\n";
}


void show_histogram_svg(const vector<double>& bins) {


    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 370;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 0;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const string stroke = "black";
    const string fill = "#3CB371";
    const auto MAX_ASTERISK = IMAGE_WIDTH - TEXT_WIDTH;
    size_t max_count = 0;
    for (size_t bin : bins)
    {
        if (bin * BLOCK_WIDTH > max_count)
        {
            max_count = bin * BLOCK_WIDTH;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;
    svg_begin(IMAGE_WIDTH,IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins)
    {
        size_t bin_scale = bin;
        if (scaling_needed)
        {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            bin_scale = (size_t)(bin * scaling_factor);
        }
        if (bin<100){
        const double bin_width = BLOCK_WIDTH * bin_scale;
        const double text_wid= IMAGE_WIDTH-bin_width-30;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(text_wid, top, bin_width, BIN_HEIGHT,"black", "#3CB371");
        top += BIN_HEIGHT;
        }
        else{
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, 370, BIN_HEIGHT,"black", "#3CB371");
        top += BIN_HEIGHT;
        }
    }
    svg_end();
}

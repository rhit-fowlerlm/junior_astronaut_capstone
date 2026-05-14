#include "SevenSegments.h"


SevenSegment::SevenSegment(){

}


void SevenSegment::begin(){
    seven_segment1.begin(&Wire, 0xE0);
    seven_segment2.begin(&Wire, 0xE2);
}


void SevenSegment::print_chars1(char c1, char c2, char c3, char c4, char c5, char c6, char c7, char c8){
    this->seven_segment1.print(c1, c2, c3, c4, c5, c6, c7, c8);
}

void SevenSegment::print_chars2(char c1, char c2, char c3, char c4, char c5, char c6, char c7, char c8){
    this->seven_segment2.print(c1, c2, c3, c4, c5, c6, c7, c8);
}
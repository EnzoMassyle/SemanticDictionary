#ifndef SEMANTIC_WINDOW_GUARD
#define SEMANTIC_WINDOW_GUARD
 
#include "Simple_window.h"
#include "GUI.h"
#include "SemanticDictionary.h"

struct SemanticWindow : Graph_lib::Window  // Lines_window inherits from Window
{
    SemanticWindow(Point xy, int w, int h, const string& title); // declare constructor
private:
    //data:
    SemanticDictionary sd;
    string dictionaryFileName = "SemanticDictionary.txt";
    

    //widgets:
    Button quit_button; // end program
    Button write_button; //write to SemanticDictionary.txt
    Button process_button; //Process text file
    Button read_button; //read from SemanticDictionary.txt
    Button solve_button;
    Button next_button;
    Button next_process_button;
    Button return_from_solve_button;
    Button return_from_process_button;
    Out_box general_output_box; // output box for general use
    In_box target_word;
    In_box correct_answer;
    In_box guess_one;
    In_box guess_two;
    In_box guess_three;
    In_box file_name;


    //Actions invoked by callbacks:

    void process_pressed();
    void next_process_pressed();
    void read_pressed();
    void write_pressed();  // what to do when next_button is pushed
    void solve_pressed();
    void quit_pressed();  // what to do when quit_botton is pushed
    void next_pressed();
    void return_from_solve_pressed();
    void return_from_process_pressed();

    //calback functions:
    static void cb_read(Address, Address);
    static void cb_write(Address, Address);
    static void cb_process(Address, Address);
    static void cb_solve(Address, Address);
    static void cb_quit(Address, Address);  // callback for quit_button
    static void cb_next(Address, Address);
    static void cb_next_process(Address, Address);
    static void cb_return_from_solve(Address, Address);
    static void cb_return_from_process(Address, Address);
}; 



#endif
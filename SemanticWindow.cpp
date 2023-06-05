#include "SemanticWindow.h"



SemanticWindow::SemanticWindow(Point xy, int w, int h, const string& title)
    :Window(xy, w, h, title),
    quit_button{Point{225,90}, 150, 20, "Quit", cb_quit}, // quit button
    write_button{Point{225, 120}, 150, 20, "Write", cb_write}, //write button
    process_button{Point{225, 150}, 150, 20, "Process", cb_process},
    read_button{Point{225, 180}, 150, 20, "Read", cb_read},
    solve_button{Point{225, 210}, 150, 20, "Solve", cb_solve},
    next_button{Point{250, 300}, 70, 20, "Next", cb_next},
    next_process_button{Point{250, 350}, 70, 20, "Next", cb_next_process},
    return_from_solve_button{Point{0, y_max()-20}, 70, 20, "Return", cb_return_from_solve},
    return_from_process_button{Point{0, y_max()-20}, 70, 20, "Return", cb_return_from_process},
    general_output_box{Point{75, 0}, 500, 80, "Message: "},
    target_word{Point{50, 250}, 70, 20, "Word: "},
    correct_answer{Point{200, 250}, 70, 20, "Answer: "},
    guess_one{Point{300, 250}, 70, 20, "G1:"},
    guess_two{Point{420, 250}, 70, 20, "G2: "},
    guess_three{Point{530, 250}, 70, 20, "G3: "},
    file_name{Point{250, 300}, 100, 20, "File name: "}
    
{

    //Attach the buttons...
    attach(quit_button);
    attach(write_button);
    attach(process_button);
    attach(read_button);
    attach(solve_button);
    attach(general_output_box);

    //start with welcome message
    general_output_box.put("Welcome to the similarity checker! Select from below...");

    redraw();
}

void SemanticWindow::quit_pressed()
{
    hide(); // get rid of window
}
void SemanticWindow::cb_quit(Address, Address pw)
{
    reference_to<SemanticWindow>(pw).quit_pressed();
}

void SemanticWindow::read_pressed()
{
            ifstream dictionary(dictionaryFileName);
            //if failed
            if(dictionary.fail())
            {
                //error message
                cout << "Oops! could not open " << dictionaryFileName << endl;
            }
            else
            {
                //extract from ifstream object into your dictionary object
                dictionary >> sd;
                //output that you are done reading
                 general_output_box.put("Data successfully read from SemanticDictionary.txt");
                 redraw();
            }
}
void SemanticWindow::cb_read(Address, Address pw)
{
    reference_to<SemanticWindow>(pw).read_pressed();
}

void SemanticWindow::write_pressed()
{
    //declare and open ofstream object
    ofstream outFile(dictionaryFileName);
    //insert from the dictionary object into the ofstream object
    outFile << sd;
    //output that you are done writing
    general_output_box.put("Data successfuly written into SemanticDictionary.txt");
}
void SemanticWindow::cb_write(Address, Address pw)
{
    reference_to<SemanticWindow>(pw).write_pressed();
}

void SemanticWindow::process_pressed()
{

    attach(file_name);
    attach(next_process_button);
    attach(return_from_process_button);
    redraw();
}
void SemanticWindow::cb_process(Address, Address pw)
{
    reference_to<SemanticWindow>(pw).process_pressed();
}

void SemanticWindow::next_process_pressed()
{

    stringstream ss;
    //declare variable for file name
    string fileName;
    //prompt and input file name

    fileName = file_name.get_string();
    //construct ifstream object and open the file

    ifstream newFile(fileName);

    //if failed
    if(newFile.fail())
    {
        //error message
        ss << "Oops! could not open file" << endl;
    }
    //else
    else
    {
        //output that you are processing the file
        ss << "Processing file..." << endl;
        auto start = chrono::high_resolution_clock::now(); //code to record time elapsed
        //declare a variable to hold all of the text
        string textHolder = "";
        //declare a variable to hold a singlar word
        string singleWord;
        //loop to read every word in the file.  Concatenate each word onto text, separated by " "
        while(newFile >> singleWord)
        {
            textHolder += (singleWord + " ");
        }

        //pass text into getSentenceLists.  (This is a copy paste from the last project)
        vector<vector<string>> sentenceLists = getSentenceLists(textHolder);

        //Create a double for loop to loop through each word of each sentenceList in sentenceLists and 
        //    process the target word.  (This is also a copy paste from the last project)
        for(vector<string> sentenceList : sentenceLists)
            for(string targetWord : sentenceList) sd.processTargetWord(targetWord, sentenceList);

        auto stop = chrono::high_resolution_clock::now();  //code to record time elapsed
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        ss << "Done.  Time elapsed: " << duration.count() << " milliseconds" << endl;
    }

    general_output_box.put(ss.str());
    redraw();
}
void SemanticWindow::cb_next_process(Address, Address pw)
{
    reference_to<SemanticWindow>(pw).next_process_pressed();
}

void SemanticWindow::solve_pressed()
{

    attach(target_word);
    attach(correct_answer);
    attach(guess_one);
    attach(guess_two);
    attach(guess_three);
    attach(next_button);
    attach(return_from_solve_button);
    redraw();
}

void SemanticWindow::cb_solve(Address, Address pw)
{
    reference_to<SemanticWindow>(pw).solve_pressed();
}

void SemanticWindow::next_pressed()
{
    stringstream ss;
    string word, answer, choice1, choice2, choice3;
    word = target_word.get_string();
    answer = correct_answer.get_string();
    choice1 = guess_one.get_string();
    choice2 = guess_two.get_string();
    choice3 = guess_three.get_string();

    try
    {
        string s = sd.mostSimilarWord(word, vector<string>{choice1, choice2, choice3});
        ss << "Most similar: " << s << endl;
        ss << "Index: " << sd.getSimilarity(word, s) << endl;
        if(s == answer) ss << "Correct answer." << endl;
        else ss << "Incorrect answer." << endl;
    }
    catch(runtime_error& e)
    {
        ss << e.what() << endl;
    }

    general_output_box.put(ss.str());

    redraw();
}
void SemanticWindow::cb_next(Address, Address pw)
{
    reference_to<SemanticWindow>(pw).next_pressed();
}

void SemanticWindow::return_from_solve_pressed()
{
    next_button.hide();
    target_word.hide();
    correct_answer.hide();
    guess_one.hide();
    guess_two.hide();
    guess_three.hide();
    return_from_solve_button.hide();

    redraw();
}
void SemanticWindow::cb_return_from_solve(Address, Address pw)
{
    reference_to<SemanticWindow>(pw).return_from_solve_pressed();
}

void SemanticWindow::return_from_process_pressed()
{
    file_name.hide();
    next_process_button.hide();
    return_from_process_button.hide();
    redraw();
}
void SemanticWindow::cb_return_from_process(Address, Address pw)
{
    reference_to<SemanticWindow>(pw).return_from_process_pressed();
}

#include"SemanticWindow.h"

int main()
{

    try 
    {
        SemanticWindow win(Point{100,100}, 600, 400, "SemanticWindow");
        return gui_main();
    }
    catch(exception& e)
    {
        cerr << "exception: " << e.what() << '\n';
        return 1;
    }
    catch(...)
    {
        cerr << "Some exception\n";
        return 2;
    }


}
#include <windows.h>
using namespace std;

int main() {
    constexpr auto text = "I'm simple console program.  Press OK to quit.";
    MessageBox(GetConsoleWindow(), text, "Demo", MB_OK);
    return 0;
}

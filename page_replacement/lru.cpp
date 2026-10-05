#include <iostream>
using namespace std;

int main() {
    int n, frames;

    cout << "Enter number of pages: ";
    cin >> n;

    int pages[n];

    cout << "Enter reference string: ";
    for (int i = 0; i < n; i++)
        cin >> pages[i];

    cout << "Enter number of frames: ";
    cin >> frames;

    int frame[frames];
    int recent[frames];

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        recent[i] = -1;
    }

    int pageFault = 0;
    int pageHit = 0;

    cout << "\nPage\tFrames\n";

    for (int i = 0; i < n; i++) {

        bool found = false;

        // Check page in frame
        for (int j = 0; j < frames; j++) {

            if (frame[j] == pages[i]) {

                found = true;
                recent[j] = i;

                break;
            }
        }

        // Page Hit
        if (found) {

            pageHit++;
        }

        // Page Fault
        else {

            int pos = -1;

            // Find empty frame
            for (int j = 0; j < frames; j++) {

                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If no empty frame
            if (pos == -1) {

                pos = 0;

                for (int j = 1; j < frames; j++) {

                    if (recent[j] < recent[pos])
                        pos = j;
                }
            }

            frame[pos] = pages[i];
            recent[pos] = i;

            pageFault++;
        }

        cout << pages[i] << "\t";

        for (int j = 0; j < frames; j++) {

            if (frame[j] == -1)
                cout << "- ";
            else
                cout << frame[j] << " ";
        }

        cout << endl;
    }

    cout << "\nPage Fault = " << pageFault << endl;
    cout << "Page Hit = " << pageHit << endl;

    return 0;
}

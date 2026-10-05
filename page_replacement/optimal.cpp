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

    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    int pageFault = 0;
    int pageHit = 0;

    cout << "\nPage\tFrames\n";

    for (int i = 0; i < n; i++) {

        bool found = false;

        // Check page in frame
        for (int j = 0; j < frames; j++) {

            if (frame[j] == pages[i]) {
                found = true;
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

                int farthest = i;

                for (int j = 0; j < frames; j++) {

                    int k;

                    for (k = i + 1; k < n; k++) {

                        if (frame[j] == pages[k])
                            break;
                    }

                    // Page is never used again
                    if (k == n) {
                        pos = j;
                        break;
                    }

                    // Find page used farthest in future
                    if (k > farthest) {
                        farthest = k;
                        pos = j;
                    }
                }
            }

            frame[pos] = pages[i];

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

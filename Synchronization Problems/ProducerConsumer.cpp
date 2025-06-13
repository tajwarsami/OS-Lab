#include <iostream>
#include <vector>
using namespace std;

const int MAX_CAPACITY = 5;
vector<int> sharedBuffer;  // Shared data buffer
int prodIDCounter = 0;     // Producer ID generator
int consIDCounter = 0;     // Consumer ID generator
vector<int> activeProducersList; // Active producers record
vector<int> activeConsumersList; // Active consumers record

void displayOptions() {
    cout << "\nChoose an action:\n";
    cout << "1 - Add product (Produce)\n";
    cout << "2 - Remove product (Consume)\n";
    cout << "0 - Exit program\n";
    cout << "Your choice: ";
}

void produceItem() {
    if (sharedBuffer.size() >= MAX_CAPACITY) {
        cout << "[Producer] Buffer is full! Cannot add more items.\n";
        return;
    }

    prodIDCounter++;
    activeProducersList.push_back(prodIDCounter);

    int item = prodIDCounter * 100;  // Unique item per producer
    sharedBuffer.push_back(item);

    cout << ">> [Producer " << prodIDCounter << "] produced item: " << item << "\n";
}

void consumeItem() {
    if (sharedBuffer.empty()) {
        cout << "[Consumer] Buffer empty! No items to consume.\n";
        return;
    }

    consIDCounter++;
    activeConsumersList.push_back(consIDCounter);

    int item = sharedBuffer.front();
    sharedBuffer.erase(sharedBuffer.begin());

    cout << ">> [Consumer " << consIDCounter << "] consumed item: " << item << "\n";
}

int main() {
    int userChoice;

    // Pre-fill buffer with initial products
    sharedBuffer.push_back(100);
    sharedBuffer.push_back(200);
    sharedBuffer.push_back(300);
    cout << "Initial buffer contents: 100, 200, 300\n";

    while (true) {
        displayOptions();
        cin >> userChoice;

        switch (userChoice) {
            case 1:
                produceItem();
                break;
            case 2:
                consumeItem();
                break;
            case 0:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid input. Please try again.\n";
        }
    }
}

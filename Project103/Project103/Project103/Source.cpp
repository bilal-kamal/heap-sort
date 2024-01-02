#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to construct a heap using the bottom-up algorithm
void buildHeap(vector<int>& H) {
    int n = H.size() - 1;

    for (int i = n / 2; i >= 1; --i) {
        int k = i;
        int v = H[k];
        bool heap = false;

        while (!heap && 2 * k <= n) {
            int j = 2 * k;

            if (j < n && H[j] < H[j + 1]) {
                j = j + 1;
            }

            if (v >= H[j]) {
                heap = true;
            }
            else {
                H[k] = H[j];
                k = j;
            }
        }

        H[k] = v;
    }
}

// Function to calculate the height of the tree
int calculateTreeHeight(int size) {
    return static_cast<int>(log2(size)) + 1;
}

// Function to display the heap as a tree
void displayTree(const vector<int>& H) {
    int size = H.size() - 1;
    int height = calculateTreeHeight(size);
    int index = 1;

    for (int level = 0; level < height; ++level) {
        int nodesInLevel = min(static_cast<int>(pow(2, level)), size - index + 1);
        int spaces = (1 << (height - level)) - 1;

        // Print leading spaces
        for (int i = 0; i < spaces; ++i) {
            cout << " ";
        }

        // Print nodes in the current level
        for (int i = 0; i < nodesInLevel; ++i) {
            cout << H[index++] << " ";

            // Print spaces between nodes
            if (i < nodesInLevel - 1) {
                for (int j = 0; j < 2 * (spaces + 1); ++j) {
                    cout << " ";
                }
            }
        }

        cout << endl;
    }
}

// Function to insert a new element into the heap
void insertElement(vector<int>& H, int element) {
    H.push_back(element);
    int k = H.size() - 1;
    int v = H[k];

    // Heapify-up to restore the heap property
    while (k > 1 && v > H[k / 2]) {
        H[k] = H[k / 2];
        k = k / 2;
    }

    H[k] = v;
}

// Function to remove the maximum element from the heap
void removeMax(vector<int>& H) {
    if (H.size() <= 1) {
        cout << "Heap is empty. Cannot remove maximum element.\n";
        return;
    }

    int n = H.size() - 1;
    swap(H[1], H[n]);
    H.pop_back();
    int k = 1;
    int v = H[k];

    // Heapify-down to restore the heap property
    while (2 * k <= n) {
        int j = 2 * k;

        if (j < n && H[j] < H[j + 1]) {
            j = j + 1;
        }

        if (v >= H[j]) {
            break;
        }
        else {
            H[k] = H[j];
            k = j;
        }
    }

    H[k] = v;
}

int main() {
    int size;

    cout << "Enter the size of the array: ";
    cin >> size;

    vector<int> heapArray;

    cout << "Enter the elements of the array:\n";
    for (int i = 0; i < size; ++i) {
        int element;
        cin >> element;
        heapArray.push_back(element);
    }

    cout << "Original array: ";
    for (int i = 0; i < heapArray.size(); ++i) {
        cout << heapArray[i] << " ";
    }
    cout << endl;

    // Construct the heap
    buildHeap(heapArray);

    cout << "Heapified array:\n";
    displayTree(heapArray);

    // Insert a new element
    int newElement;
    cout << "Enter a new element to insert: ";
    cin >> newElement;
    insertElement(heapArray, newElement);

    cout << "Heap after insertion:\n";
    displayTree(heapArray);

    // Remove the maximum element
    removeMax(heapArray);

    cout << "Heap after removing maximum element:\n";
    displayTree(heapArray);

    return 0;
}

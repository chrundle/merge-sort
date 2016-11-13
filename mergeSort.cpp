#include <algorithm>
#include <cstdlib>
#include <iostream>


/* --------------------------- merge --------------------------- */
/*  Given an array, its length, a starting index, and subarray
    width w, merge combines the two sorted subarrays 
                    arr[index : index + w - 1] 
    and 
                arr[index + w : index + 2 * w - 1]
    so that the subarray arr[index: index + 2 * w] is sorted in
    nondecreasing order.
    
    Input variables:
        arr   : array of integers to be sorted
        temp  : array of same length as arr used in sorting
                procedure
        length: length of arrays arr and temp
        index : index of first entry in first subarray
        w     : width of each subarray

    Features: This implementation has time complexity O(length)
    and requires O(1) additional memory.                        */

void merge(int *arr, int *temp, int length, int index, int w) {
    int i, j, i_end, j_end, k;
    i = index;      // first index of first sorted subarray
    j = index + w;  // first index of second sorted subarray
    k = index;      // running index of merged & sorted subarray

    /* i_end and j_end are the last index of the subarrays with
       starting index i and j, respectively. 
       The min function is used to ensure the last index of each
       subarray does not exceed the last index of the array arr. */
    i_end = std::min(index + w, length);
    j_end = std::min(index + 2 * w, length);

    /* while both subarrays are not empty, merge the subarrays */
    while(i < i_end && j < j_end) {
        if(arr[i] <= arr[j]) {// store entry from first subarray in temp
            temp[k++] = arr[i++];
        }
        else {// store entry from second subarray in temp
            temp[k++] = arr[j++];
        }
    }
    /* at this point, either the first or second subarray has 
       been merged into the temp array. */

    /* store remaining elements of first subarray in temp */
    while(i < i_end) {
        temp[k++] = arr[i++];
    }
    /* store remaining elements of second subarray in temp */
    while(j < j_end) {
        temp[j] = arr[j++];
    }
}


/* ------------------ mergeSort (bottom up) ------------------ */
/*  Given an array the mergeSort algorithm returns a pointer 
    to a sorted array containing the entries of the original
    array.
    
    Input variables:
        arr   : pointer to array of integers to be sorted
        temp  : pointer to array of same length as arr used 
                in sorting procedure
        length: length of arrays arr and temp

    Output variable:
        temp  : pointer to sorted copy of arr

    Features: This implementation has time complexity 
    O(length lg(length)) and requires O(length) additional
    memory (this memory is for the array temp which is
    allocated in main). Additionally, this sorting algorithm 
    is stable.                                                */

int * mergeSort (int *arr, int *temp, int length) {
    int i, w;    

    /* double width until it exceeds length of arr */
    for(w = 1; w < length; w *= 2) {
        /* i is index of subarray of length 2*w to be sorted */
        for(i = 0; i < length; i += 2 * w) {
            merge(arr, temp, length, i, w); // execute merge
        }

        std::swap(arr, temp);   // swap pointers for arr and temp
    }

    std::swap(arr, temp);       // swap pointers for arr and temp
    return temp;                // end mergeSort
}


/* ----------------------- arrayPrint ----------------------- */
/*  Given an array and its length this function prints the 
    elements of the array.                                    */

void arrayPrint(int *arr, int length) {
    int i;

    for(i = 0; i < length; i++) {
        std::cout << " " << arr[i]; // print ith entry in array
    }

    std::cout << std::endl;         // end line after all entries printed
}


/* -------------------------- main -------------------------- */
/*  Main routine for experimenting with mergeSort. Try it 
    with n = one billion for fun.                             */

int main () {
    int i, n;

    std::cout << "Enter the size of the array you would like to sort: ";
    std::cin >> n;

    int *arr = new int[n];  // create array of size n
    int *temp = new int[n]; // create temp array of size n

    for(i = 0; i < n; i++) {
        arr[i] = rand() % 1000 + 1; // store random number arr[i]
    }

    /* print elements in arr before applying mergeSort */
    std::cout << "Array prior to merge sort: " << std::endl;
    arrayPrint(arr, n);
    std::cout << std::endl;

    arr = mergeSort(arr, temp, n);  // execute mergeSort

    /* print elements in arr after applying mergeSort */
    std::cout << "Array after merge sort: " << std::endl;
    arrayPrint(arr, n);

    delete[] arr, temp;             // free memory
    return 0;                       // end main
}

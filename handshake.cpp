#include <iostream>
// include additional necessary headers
#include <thread>
#include <unistd.h>
#include <mutex>
#include <string>

using namespace std;

void query(int num/*add necessary parameters*/) {
    // Should print: the print number (starting from 0), "SYN", and the three dots "..."
    printf("[%d] SYN ... ", num);
}

void response(/*add necessary parameters*/) {
    // Should print "ACK"
    printf("ACK\n");
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: ./handshake <count>\n");
        exit(1);
    }
    int count = 0;
    
    /**
     * Steps to follow:
     * 1. Get the "count" from cmd args
     * 2. Create necessary synchronization primitive(s)
     * 3. Create two threads, one for "SYN" and the other for "ACK"
     * 4. Provide the threads with necessary args
     * 5. Update the "query" and "response" functions to synchronize the output
    */

    // getopt to read count
    int opt;
    while ((opt = getopt(argc, argv, "c:")) != -1) {
        switch (opt) {
            case 'c':
                count = atoi(optarg);
                break;
        }
    }

    mutex m;

    for (int i = 0; i < count ; ++i)
    {
        m.lock();
        thread first(query, i);
        m.unlock();
        thread second(response);
    
        first.join();
        second.join();
        
    }
    
    return 0;
}
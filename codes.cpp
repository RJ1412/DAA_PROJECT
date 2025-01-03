#include <bits/stdc++.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <climits>
using namespace std;


const int ROWS = 5;  // Example parking row size
const int COLS = 5;  // Example parking column size
int car_parking[ROWS][COLS], bikes_parking[ROWS][COLS];
int krusgal_count=0;
// Structure to represent a person
struct Person {
    string name;
    int licenseNumber;
    string carNumber;
    float fine;
    bool isFinePending;
};

// Node for the linked list
struct Nod {
    Person data;
    Nod* next;
};

struct PD {
    string location;
    string ps;    // Petrol Station name
    float dist;      // Distance to the petrol station
};

PD save_petrol[100]; // Assuming a maximum of 100 petrol stations

// Define type alias for node pointer for clarity
using nod = Nod*;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

struct Node {
    int vehicle_number;
    int price;
    string vehicle_type;
    Node* next;

    Node() : vehicle_number(0), price(0), vehicle_type(""), next(nullptr) {}
};

// Road quality structure
struct RoadQuality {
    string source;
    string destination;
    int quality_rating;
    int traffic_rating;
    int max_speed;
    int safety_rating;
    int road_id;
};
    //   RoadQuality(string src, string dest, int q, int t, int max, int safety, int rid) 
    //     : source(src), destination(dest), quality_rating(q), traffic_rating(t), 
    //       max_speed(max), safety_rating(safety), road_id(rid) {}


int quality_count = 0;
struct nodee
{
    int u;
    int v;
    int w;
};

// Global variables
const int MAX_EDGES = 100;
nodee edge[MAX_EDGES];
// Global variables
vector<RoadQuality> quality_list;

// Function prototypes
Node* getnode();
Node* insert_rear(Node* head);
Node* insert_front(Node* head);
Node* insert_pos(int pos, Node* head);
Node* delete_rear(Node* head);
Node* delete_front(Node* head);
void display_list(Node* head);
void load_from_file_quality();
void heapify(vector<RoadQuality>& arr, int n, int i);
void heap_sort_quality(vector<RoadQuality>& arr);
void selection_sort_traffic(vector<RoadQuality>& arr);
void insertion_sort_safety(vector<RoadQuality>& arr);



struct WeatherInfo {
    string place;
    string weather;
};

struct TransportInfo {
    string source;
    string destination;
    string hours;
};

const int MAX_PARKING_SPOTS = 100; // Maximum number of parking spots

// Structure to represent a parking spot
struct ParkingSpot {
    int spotNumber;
    int priority;
    string carPlate;
};


PD search_list[300];
WeatherInfo weather_list[300];
TransportInfo transport_list[300];
int petrol_count = 0, count_petrol = 0, weather_count = 0, transport_count = 0;

int cost_matrix[150][150];
int dist[150], visited[150] = {0}, path[150];

void welcome_transport()
{
    for (int i = 0; i < 80; i++)
        cout << "*";
    cout << "\n\n\t\t\t\tIII TRANSPORT SCHEDULE III\n\n\n";
    for (int i = 0; i < 80; i++)
        cout << "*";
    cout << "\n\n";
}

void welcome()
{
    int i = 0;

    // Print a line of asterisks for formatting
    for (i = 0; i < 80; i++) cout<<"*";

    // Print a generic welcome title
    printf("\n\n\t\t\t\tIII WELCOME III\n\n\n");

    // Print another line of asterisks for formatting
    for (i = 0; i < 80; i++) cout<<"*";

    // Print additional newlines for spacing
    cout<<endl<<endl;
}

void welcome_weather()
{
    for (int i = 0; i < 80; i++)
        cout << "*";
    cout << "\n\n\t\t\t\tIII SEARCH BUS STOP INFORMATION III\n\n\n";
    for (int i = 0; i < 80; i++)
        cout << "*";
    cout << "\n\n";
}

void welcome_petrol()
{
    for (int i = 0; i < 80; i++)
        cout << "*";
    cout << "\n\n\t\t\t\tIII SEARCH PETROL STATIONS NEARBY III\n\n\n";
    for (int i = 0; i < 80; i++)
        cout << "*";
    cout << "\n\n";
}

int BruteForceStringMatch(const string& t, const string& p)
{
    int n = t.length();
    int m = p.length();
    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && p[j] == t[i + j])
            j++;
        if (j == m)
            return i;
    }
    return -1;
}

void load_from_file()
{
    ifstream file("petrol.txt");
    if (!file.is_open()) {
        cout << "File Not Found\n";
        return;
    }
    while (file >> search_list[petrol_count].location >> search_list[petrol_count].ps >> search_list[petrol_count].dist) {
        cout << search_list[petrol_count].location << "\t" << search_list[petrol_count].ps << "\t" << search_list[petrol_count].dist << "\n";
        petrol_count++;
    }
    file.close();
}

void load_from_file_weather()
{
    ifstream file("weather.txt");
    if (!file.is_open()) {
        cout << "File Not Found\n";
        return;
    }
    weather_count = 0;
    while (file >> weather_list[weather_count].place >> weather_list[weather_count].weather) {
        cout << weather_list[weather_count].place  << "\t" << weather_list[weather_count].weather << "\n";
        weather_count++;
    }
    file.close();
}

void load_from_file_transport()
{
    ifstream file("transport.txt");
    if (!file.is_open()) {
        cout << "File Not Found\n";
        return;
    }
    while (file >> transport_list[transport_count].source >> transport_list[transport_count].destination >> transport_list[transport_count].hours) {
        // cout << transport_list[transport_count].source << "\t" << transport_list[transport_count].destination << "\t" << transport_list[transport_count].hours << "\n";
        transport_count++;
    }
    file.close();
}

void petrol_nearby()
{
    load_from_file();
    string a;
    cin >> a;
    cout << "\nSearching petrol station near : " << a << "\n";
    int searched_count = 0;
    for (int i = 0; i < petrol_count; i++) {
        int index = BruteForceStringMatch(search_list[i].location, a);
        if (index != -1) {
            cout << search_list[i].location << "\t" << search_list[i].ps << "\t" << search_list[i].dist << "\n";
            save_petrol[searched_count] = search_list[i];
            searched_count++;
            count_petrol++;
        }
    }
}

void merge(PD b[], int p, PD c[], int q, PD A[]) {
    int i = 0, j = 0, k = 0;

    // Merge the two arrays into a single sorted array
    while (i < p && j < q) {
        if (b[i].dist <= c[j].dist) {
            A[k] = b[i];
            i++;
        } else {
            A[k] = c[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements from array b
    while (i < p) {
        A[k] = b[i];
        i++;
        k++;
    }

    // Copy the remaining elements from array c
    while (j < q) {
        A[k] = c[j];
        j++;
        k++;
    }
}

// Function to perform mergesort on an array of petrol_data structures
void mergesortt(PD A[], int n) {
    if (n > 1) {
        int p = n / 2;

        // Create two temporary arrays to store the halves of the original array
        PD b[p], c[n - p];
        for (int i = 0; i < p; i++) {
            b[i] = A[i];
        }
        for (int i = p; i < n; i++) {
            c[i - p] = A[i];
        }

        // Recursively apply mergesort on the two halves
        mergesortt(b, p);
        mergesortt(c, n - p);

        // Merge the sorted halves back into the original array
        merge(b, p, c, n - p, A);
    }
}

// Function to sort the saved petrol stations using mergesort
void sort_petroll() {
    mergesortt(save_petrol, count_petrol);
}

// Function to print the sorted petrol stations
void print_sorted_petrol() {
    cout << "\nSorted Petrol Stations:\n";
    for (int i = 0; i < count_petrol; i++) {
        cout << save_petrol[i].location << "\t" << save_petrol[i].ps << "\t" << save_petrol[i].dist << endl;
    }
}

void weather_info()
{
    load_from_file_weather();
    string a ;
    cout << "Enter location to search nearest bus stand: ";
    cin >> a;
    cout << "\nSearching nearest bus stand from: " << a << "\n";
    int searched_count = 0;
    for (int i = 0; i < weather_count; i++) {
        int index = BruteForceStringMatch(weather_list[i].place, a);
        if (index != -1) {
            cout << weather_list[i].place << "\t" << weather_list[i].weather << "\n";
            searched_count++;
        }
    }
}

void search_transport()
{
    load_from_file_transport();
    string src , src1;
    cout << "Enter your source: ";
    cin >> src;
    cout << "Enter Destination: ";
    cin >> src1;
    int searched_count = 0;
    for (int i = 0; i < transport_count; i++) {
        if (transport_list[i].source == src && transport_list[i].destination == src1) {
            cout <<"Prefered Bus Route:"<<"\t\t"<< transport_list[i].hours << "\n";
            searched_count++;
        }
    }
}

void matrix()
{
    int counter = 1;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cost_matrix[i][j] = counter++;
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i == j)
                cost_matrix[i][j] = 0;
        }
    }
}

void dijikstra()
{
    matrix();
    int v = 10;
    int src;
    cout << "Enter source: ";
    cin >> src;

    for (int i = 0; i < v; i++) {
        dist[i] = cost_matrix[src][i];
        path[i] = src;
    }
    visited[src] = 1;

    for (int j = 0; j < v - 1; j++) {
        int min = INT_MAX, u = -1;
        for (int i = 0; i < v; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        if (u == -1) {
            cout << "No reachable nodes\n";
            break;
        }

        int distn = dist[u];
        visited[u] = 1;

        for (int i = 0; i < v; i++) {
            if (!visited[i] && dist[i] > distn + cost_matrix[u][i]) {
                dist[i] = distn + cost_matrix[u][i];
                path[i] = u;
            }
        }
    }

    cout << "Distances: ";
    for (int i = 0; i < v; i++) {
        cout << dist[i] << "\t";
    }
}


Node* getnode() {
    Node* newNode = new Node();
    if (!newNode) {
        cout << "Memory allocation failed" << endl;
        exit(0);
    }
    return newNode;
}

// Function to display the elements of the linked list
void display_list(Node* head) {
    if (!head) {
        cout << "Empty List" << endl;
        return;
    }
    cout << "Elements are:" << endl;
    Node* cur = head;
    while (cur) {
        cout << cur->vehicle_number << "\t"
             << cur->price << "\t"
             << cur->vehicle_type << "\t" << endl;
        cur = cur->next;
    }
}

// Function to read details and return a new node
Node* read_details() {
    Node* temp = getnode();
    cout << "Enter the data:" << endl;
    cout << "Enter vehicle number: ";
    cin >> temp->vehicle_number;
    cout << "Enter amount paid: ";
    cin >> temp->price;
    cout << "Enter vehicle type: ";
    cin >> temp->vehicle_type;
    return temp;
}

// Function to insert a new node at the rear of the linked list
Node* insert_rear(Node* head) {
    Node* newNode = read_details();
    if (!head)
        return newNode;
    Node* cur = head;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = newNode;
    return head;
}

// Function to insert a new node at the front of the linked list
Node* insert_front(Node* head) {
    Node* newNode = read_details();
    newNode->next = head;
    return newNode;
}

// Function to delete the node at the front of the linked list
Node* delete_front(Node* head) {
    if (!head) {
        cout << "List empty" << endl;
        return nullptr;
    }
    Node* cur = head;
    head = head->next;
    cout << "Deleted: " << cur->vehicle_number << "\t"
         << cur->price << "\t"
         << cur->vehicle_type << endl;
    delete cur;
    return head;
}

// Function to delete the node at the rear of the linked list
Node* delete_rear(Node* head) {
    if (!head) {
        cout << "List empty" << endl;
        return nullptr;
    }
    if (!head->next) {
        cout << "Deleted: " << head->vehicle_number << "\t"
             << head->price << "\t"
             << head->vehicle_type << endl;
        delete head;
        return nullptr;
    }
    Node* cur = head;
    Node* prev = nullptr;
    while (cur->next) {
        prev = cur;
        cur = cur->next;
    }
    cout << "Deleted: " << cur->vehicle_number << "\t"
         << cur->price << "\t"
         << cur->vehicle_type << endl;
    delete cur;
    prev->next = nullptr;
    return head;
}

// Function to insert a new node at a specified position in the linked list
Node* insert_pos(int pos, Node* head) {
    Node* newNode = read_details();
    if (pos == 1) {
        newNode->next = head;
        return newNode;
    }
    Node* cur = head;
    Node* prev = nullptr;
    int count = 1;
    while (cur && count < pos) {
        prev = cur;
        cur = cur->next;
        count++;
    }
    if (count == pos) {
        prev->next = newNode;
        newNode->next = cur;
    } else {
        cout << "Invalid position" << endl;
        delete newNode;
    }
    return head;
}

// Function to delete the node at a specified position in the linked list
Node* delete_pos(int pos, Node* head) {
    if (!head) {
        cout << "List empty" << endl;
        return nullptr;
    }
    if (pos == 1) {
        Node* cur = head;
        head = head->next;
        cout << "Deleted: " << cur->vehicle_number << "\t"
             << cur->price << "\t"
             << cur->vehicle_type << endl;
        delete cur;
        return head;
    }
    Node* cur = head;
    Node* prev = nullptr;
    int count = 1;
    while (cur && count < pos) {
        prev = cur;
        cur = cur->next;
        count++;
    }
    if (cur) {
        prev->next = cur->next;
        cout << "Deleted: " << cur->vehicle_number << "\t"
             << cur->price << "\t"
             << cur->vehicle_type << endl;
        delete cur;
    } else {
        cout << "Invalid position specified" << endl;
    }
    return head;
}


// Function for toll management menu
void tollmanagement() {
    Node* head = nullptr;
    int choice, pos;

    while (true) {
        cout << "1-Insert Rear\n2-Display\n3-Insert Front\n4-Insert Position\n5-Delete Rear\n6-Delete Front\n9-Exit\n";
        cin >> choice;

        switch (choice) {
            case 1:
                // Insert a node at the rear
                head = insert_rear(head);
                break;
            case 2:
                // Display the linked list
                cout << "Display List Inserted\n";
                display_list(head);
                break;
            case 3:
                // Insert a node at the front
                head = insert_front(head);
                break;
            case 4:
                // Insert a node at a specified position
                cout << "Enter the position to be inserted: ";
                cin >> pos;
                head = insert_pos(pos, head);
                break;
            case 5:
                // Delete the node at the rear
                head = delete_rear(head);
                break;
            case 6:
                // Delete the node at the front
                head = delete_front(head);
                break;
            default:
                // Exit the program
                return;
        }
    }
}

void load_from_file_quality() {
    ifstream file("map.txt");
    if (!file.is_open()) {
        cout << "File not found" << endl;
        return;
    }

    RoadQuality rq;
    while (file >> rq.source >> rq.destination >> rq.quality_rating >> rq.traffic_rating >> rq.max_speed >> rq.safety_rating >> rq.road_id) {
        quality_list.push_back(rq);
    }

    file.close();

    for (const auto& rq : quality_list) {
        cout << rq.source << "\t" << rq.destination << "\t" << rq.quality_rating << "\t"
             << rq.traffic_rating << "\t" << rq.max_speed << "\t" << rq.safety_rating << endl;
    }
}

void heapify(vector<RoadQuality>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].quality_rating > arr[largest].quality_rating)
        largest = left;

    if (right < n && arr[right].quality_rating > arr[largest].quality_rating)
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort_quality(vector<RoadQuality>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void selection_sort_traffic(vector<RoadQuality>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_index = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j].traffic_rating < arr[min_index].traffic_rating)
                min_index = j;
        }
        swap(arr[i], arr[min_index]);
    }
}

void insertion_sort_safety(vector<RoadQuality>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        RoadQuality key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].safety_rating > key.safety_rating) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

TreeNode* insert_into_bst(TreeNode* root, int data) {
    if (!root) {
        return new TreeNode(data);
    }

    if (data < root->data) {
        root->left = insert_into_bst(root->left, data);
    } else {
        root->right = insert_into_bst(root->right, data);
    }

    return root;
}

// In-order traversal of the BST
void inorder(TreeNode* root) {
    if (root) {
        inorder(root->left);
        cout << root->data << "\t";
        inorder(root->right);
    }
}

// Pre-order traversal of the BST
void preorder(TreeNode* root) {
    if (root) {
        cout << root->data << "\t";
        preorder(root->left);
        preorder(root->right);
    }
}

// Post-order traversal of the BST
void postorder(TreeNode* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << "\t";
    }
}

// Function to delete a node from the BST
TreeNode* delete_from_bst(TreeNode* root, int data) {
    if (!root) {
        cout << "Empty tree\n";
        return nullptr;
    }

    if (data < root->data) {
        root->left = delete_from_bst(root->left, data);
    } else if (data > root->data) {
        root->right = delete_from_bst(root->right, data);
    } else {
        if (!root->left) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        } else {
            TreeNode* succParent = root;
            TreeNode* succ = root->right;

            while (succ->left) {
                succParent = succ;
                succ = succ->left;
            }

            if (succParent != root) {
                succParent->left = succ->right;
            } else {
                succParent->right = succ->right;
            }

            root->data = succ->data;
            delete succ;
        }
    }

    return root;
}

// Function to load road quality data from a file


// Heap sort based on quality rating


// Selection sort based on traffic rating

// Insertion sort based on safety rating

// Function to sort and display roads based on user choice
void sorttt() {
    int choice;

    // Load road details from file into the BST
    load_from_file_quality();

    do {
        cout << "\nOperations:\n";
        cout << "1. Display Roads (sorted by Quality Rating)\n";
        cout << "2. Display Roads (sorted by Traffic Rating)\n";
        cout << "3. Display Roads (sorted by Safety Rating)\n";
        cout << "4. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Sort based on Quality Rating using Heap Sort
                heap_sort_quality(quality_list);
                cout << "Roads sorted by Quality Rating:\n";
                for (const auto& road : quality_list) {
                    cout << road.road_id << " " << road.source << " " << road.destination << " " 
                         << road.quality_rating << " " << road.traffic_rating << " " 
                         << road.max_speed << " " << road.safety_rating << "\n";
                }
                break;

            case 2:
                // Sort based on Traffic Rating using Selection Sort
                selection_sort_traffic(quality_list);
                cout << "Roads sorted by Traffic Rating:\n";
                for (const auto& road : quality_list) {
                    cout << road.road_id << " " << road.source << " " << road.destination << " " 
                         << road.quality_rating << " " << road.traffic_rating << " " 
                         << road.max_speed << " " << road.safety_rating << "\n";
                }
                break;

            case 3:
                // Sort based on Safety Rating using Insertion Sort
                insertion_sort_safety(quality_list);
                cout << "Roads sorted by Safety Rating:\n";
                for (const auto& road : quality_list) {
                    cout << road.road_id << " " << road.source << " " << road.destination << " " 
                         << road.quality_rating << " " << road.traffic_rating << " " 
                         << road.max_speed << " " << road.safety_rating << "\n";
                }
                break;

            case 4:
                cout << "Exiting the program.\n";
                break;

            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }

    } while (choice != 4);
}

void bstttt() {
    load_from_file_quality(); // Load the quality data from file

    TreeNode* root = nullptr;
    for (int i = 0; i < quality_count; i++) {
        root = insert_into_bst(root, quality_list[i].road_id);
    }

    int choice, data;

    do {
        cout << "\nBinary Search Tree Operations:\n";
        cout << "1. Insert (BST based on road ID)\n";
        cout << "2. Delete\n";
        cout << "3. Inorder Traversal\n";
        cout << "4. Preorder Traversal\n";
        cout << "5. Postorder Traversal\n";
        cout << "6. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the road ID to insert: ";
                cin >> data;
                root = insert_into_bst(root, data);
                break;

            case 2:
                cout << "Enter the element to delete: ";
                cin >> data;
                root = delete_from_bst(root, data);
                break;

            case 3:
                cout << "Inorder Traversal: ";
                inorder(root);
                cout << endl;
                break;

            case 4:
                cout << "Preorder Traversal: ";
                preorder(root);
                cout << endl;
                break;

            case 5:
                cout << "Postorder Traversal: ";
                postorder(root);
                cout << endl;
                break;

            case 6:
                cout << "Exiting the program.\n";
                break;

            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }

    } while (choice != 6);
}

// Function to initialize the parking arrays
void initialize_parking() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            car_parking[i][j] = 0;
            bikes_parking[i][j] = 0;
        }
    }
}

// Function to display parking status (either car or bike parking)
void display_parking_status(int parking[][COLS]) {
    cout << "Parking Status:\n";
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << parking[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to park a vehicle
void park_vehicle(int parking[][COLS], char vehicle_type) {
    int row, col;
    cout << "Enter the row and column to park the " << vehicle_type << " (0-indexed): ";
    cin >> row >> col;

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
        if (parking[row][col] == 0) {
            parking[row][col] = 1;
            cout << vehicle_type << " parked successfully in slot (" << row << ", " << col << ").\n";
        } else {
            cout << "Slot (" << row << ", " << col << ") is already occupied.\n";
        }
    } else {
        cout << "Invalid parking slot. Please enter valid row and column.\n";
    }
}

// Main parking function
void parking() {
    initialize_parking();
    while (true) {
        char choice;
        cout << "Enter 'B' to park a bike, 'C' to park a car, or 'Q' to quit: ";
        cin >> choice;

        switch (choice) {
            case 'Q':
            case 'q':
                return;

            case 'B':
            case 'b':
                display_parking_status(bikes_parking);
                park_vehicle(bikes_parking, 'B');
                break;

            case 'C':
            case 'c':
                display_parking_status(car_parking);
                park_vehicle(car_parking, 'C');
                break;

            default:
                cout << "Invalid choice. Please enter 'B', 'C', or 'Q'.\n";
        }
    }
}

// Function to create a new node with a given person's data
nod getnod(const Person& person) {
    nod t = new Nod;
    if (t == nullptr) {
        cout << "Memory allocation failed\n";
        exit(0);
    }
    t->data = person;
    t->next = nullptr;
    return t;
}

// Function to enqueue a person into the linked list
void enqueue(const Person& person, nod& front, nod& rear) {
    nod t = getnod(person);
    if (rear == nullptr) {
        front = rear = t;
    } else {
        rear->next = t;
        rear = t;
    }
}

// Function to dequeue a person from the linked list
Person dequeue(nod& front, nod& rear) {
    Person person = {"", -1, "", 0.0f, false};  // Initialize with invalid values

    if (front == nullptr) {
        cout << "Queue is empty\n";
        return person;
    }

    nod t = front;
    person = t->data;
    front = t->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete t;
    return person;
}

// Function to display all persons in the linked list
void display_queue(nod front) {
    if (front == nullptr) {
        cout << "Queue is empty\n";
        return;
    }

    while (front != nullptr) {
        cout << "Name: " << front->data.name << ", License Number: " << front->data.licenseNumber
             << ", Car Number: " << front->data.carNumber << ", Fine: " << front->data.fine
             << ", Fine Pending: " << (front->data.isFinePending ? "Yes" : "No") << endl;
        front = front->next;
    }

    cout << endl;
}

// Function to display persons with pending fines in the linked list
void display_pending_fines(nod front) {
    if (front == nullptr) {
        cout << "Queue is empty\n";
        return;
    }

    while (front != nullptr) {
        if (front->data.isFinePending) {
            cout << "Name: " << front->data.name << ", License Number: " << front->data.licenseNumber
                 << ", Car Number: " << front->data.carNumber << ", Fine: " << front->data.fine << endl;
        }
        front = front->next;
    }

    cout << endl;
}

// Main function for the queue system
void queue_main() {
    nod front = nullptr, rear = nullptr;
    int choice;
    Person person;

    while (true) {
        cout << "1-Enqueue\n2-Dequeue\n3-Display\n4-Display Pending Fines\n5-Exit\n";
        cin >> choice;

        switch (choice) {
            case 1:
                // Enqueue a new person
                cout << "Enter person details:\n";
                cout << "Name: ";
                cin >> person.name;
                cout << "License Number: ";
                cin >> person.licenseNumber;
                cout << "Car Number: ";
                cin >> person.carNumber;
                cout << "Fine in Rupees: ";
                cin >> person.fine;
                cout << "Is Fine Pending (1 for Yes, 0 for No): ";
                cin >> person.isFinePending;
                enqueue(person, front, rear);
                break;
            case 2:
                // Dequeue a person
                person = dequeue(front, rear);
                if (front != nullptr)
                    cout << "Dequeued person: " << person.name << ", License Number: " << person.licenseNumber << endl;
                break;
            case 3:
                // Display all persons
                cout << "Queue elements:\n";
                display_queue(front);
                break;
            case 4:
                // Display persons with pending fines
                cout << "People with Pending Fines:\n";
                display_pending_fines(front);
                break;
            case 5:
                // Exit the program
                exit(0);
            default:
                // Invalid choice
                cout << "Invalid choice\n";
        }
    }
}

// Function to implement bubble sort for Kruskal's algorithm
void bubblesort_krusgal(nodee edge[], int e) {
    nodee temp;
    for (int i = 0; i < e - 2; i++) {
        for (int j = 0; j < e - 2 - 1; j++) {
            if (edge[j + 1].w < edge[j].w) {
                temp = edge[j + 1];
                edge[j + 1] = edge[j];
                edge[j] = temp;
            }
        }
    }
}


int kmpSearch(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();

    vector<int> lps(m);
    int j = 0;

    // Build the LPS (Longest Prefix Suffix) array
    for (int i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = lps[j - 1];
        }

        if (pattern[i] == pattern[j]) {
            j++;
        }

        lps[i] = j;
    }

    j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = lps[j - 1];
        }

        if (text[i] == pattern[j]) {
            j++;
        }

        if (j == m) {
            return i - j + 1; // Pattern found, return the starting index
        }
    }

    return -1; // Pattern not found
}

// Function to load parking data from file
void loadParkingData(vector<ParkingSpot>& parkingSpots, int& numParkingSpots) {
    ifstream file("app_9.txt");
    if (!file) {
        cerr << "Error opening the file" << endl;
        exit(EXIT_FAILURE);
    }

    while (file >> parkingSpots[numParkingSpots].spotNumber
                 >> parkingSpots[numParkingSpots].priority
                 >> parkingSpots[numParkingSpots].carPlate) {
        numParkingSpots++;
    }

    file.close();
}

// Function to perform insertion sort on parking data based on priority
void insertionSort(vector<ParkingSpot>& arr, int n) {
    for (int i = 1; i < n; i++) {
        ParkingSpot key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j].priority > key.priority) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}

// Dijkstra's algorithm for finding the shortest distance
int dijkstra(const vector<vector<int>>& graph, int numVertices, int source, int destination) {
    vector<int> distance(numVertices, INT_MAX);
    vector<bool> visited(numVertices, false);

    distance[source] = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = -1;
        for (int i = 0; i < numVertices; i++) {
            if (!visited[i] && (u == -1 || distance[i] < distance[u])) {
                u = i;
            }
        }

        visited[u] = true;

        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && graph[u][v] != INT_MAX && distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
            }
        }
    }

    return distance[destination];
}

void search_veh() {
    vector<ParkingSpot> parkingSpots(MAX_PARKING_SPOTS);
    int numParkingSpots = 0;
    int choice;

    while (true) {
        cout << "Enter choice (1: Load and Sort, 2: Search, 3: Exit): ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Load parking data from file
                loadParkingData(parkingSpots, numParkingSpots);

                // Sort parking data using insertion sort based on priority
                insertionSort(parkingSpots, numParkingSpots);
                break;

            case 2:
                // Search for car plate using Knuth-Morris-Pratt algorithm
                {
                    string searchPlate;
                    cout << "Enter a car plate to search: ";
                    cin >> searchPlate;

                    for (int i = 0; i < numParkingSpots; i++) {
                        if (kmpSearch(parkingSpots[i].carPlate, searchPlate) != -1) {
                            cout << "Car plate found at spot " << parkingSpots[i].spotNumber
                                 << " with priority " << parkingSpots[i].priority << endl;
                            break;
                        }
                    }
                }
                break;

            case 3:
                // Exit the program
                return;

            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;
        }

        // Create a graph for Dijkstra's algorithm
        vector<vector<int>> graph(numParkingSpots, vector<int>(numParkingSpots, INT_MAX));
        for (int i = 0; i < numParkingSpots; i++) {
            for (int j = 0; j < numParkingSpots; j++) {
                if (i == j) graph[i][j] = 0;
            }
        }

        // Assume there is an edge between adjacent parking spots
        for (int i = 0; i < numParkingSpots - 1; i++) {
            graph[i][i + 1] = graph[i + 1][i] = 1;
        }

        // Find and print the shortest distance using Dijkstra's algorithm
        int shortestDistance = dijkstra(graph, numParkingSpots, 0, numParkingSpots - 1);
        cout << "Shortest distance from the entrance to the last spot: " << shortestDistance << endl;
    }
}

void displayNumberGuessing() {
    cout << "\nNumber Guessing Game:\n";
    cout << "I have selected a number between 1 and 100.\n";
    cout << "Try to guess the number!\n\n";
}

// Function to display Rock-Paper-Scissors game
void displayRockPaperScissors() {
    cout << "\nRock-Paper-Scissors Game:\n";
    cout << "You are playing against the computer.\n";
    cout << "Enter 'r' for rock, 'p' for paper, or 's' for scissors.\n\n";
}

void game() {
    char stuckInTraffic;
    int trafficTime;

    // Ask the user if they are stuck in traffic
    cout << "Are you stuck in traffic? (y/n): ";
    cin >> stuckInTraffic;

    if (stuckInTraffic == 'y' || stuckInTraffic == 'Y') {
        // If yes, ask for estimated traffic time
        cout << "Enter estimated traffic time (in minutes): ";
        cin >> trafficTime;

        if (trafficTime > 15) {
            // If traffic time is greater than 15 minutes, prompt user to choose a game
            cout << "You have more than 15 minutes of traffic time.\n";

            int gameChoice;

            // Ask the user to choose a game
            cout << "Choose a game:\n";
            cout << "1. Rock-Paper-Scissors\n";
            cout << "2. Number Guessing\n";
            cout << "3. Watch Instagram Reels\n";
            cout << "Enter your choice (1, 2, or 3): ";
            cin >> gameChoice;

            if (gameChoice == 1) {
                // Rock-Paper-Scissors game
                displayRockPaperScissors();

                char userChoice;
                char computerChoice;

                do {
                    // Get user's choice
                    cout << "Enter your choice (r/p/s): ";
                    cin >> userChoice;

                    // Validate user's choice
                    if (userChoice != 'r' && userChoice != 'p' && userChoice != 's') {
                        cout << "Invalid choice. Please enter 'r', 'p', or 's'.\n";
                        continue;
                    }

                    // Get computer's choice
                    srand(time(0));
                    int randomChoice = rand() % 3;
                    switch (randomChoice) {
                        case 0: computerChoice = 'r'; break;
                        case 1: computerChoice = 'p'; break;
                        case 2: computerChoice = 's'; break;
                    }

                    // Display choices
                    cout << "Your choice: " << userChoice << endl;
                    cout << "Computer's choice: " << computerChoice << endl;

                    // Determine the winner
                    if (userChoice == computerChoice) {
                        cout << "It's a tie!\n";
                    } else if ((userChoice == 'r' && computerChoice == 's') ||
                               (userChoice == 'p' && computerChoice == 'r') ||
                               (userChoice == 's' && computerChoice == 'p')) {
                        cout << "You win!\n";
                    } else {
                        cout << "Computer wins!\n";
                    }

                    // Ask if the user wants to play again
                    cout << "Do you want to play again? (y/n): ";
                    cin >> userChoice;

                } while (userChoice == 'y' || userChoice == 'Y');
            } else if (gameChoice == 2) {
                // Number Guessing game
                displayNumberGuessing();

                // Generate a random number between 1 and 100
                srand(time(0));
                int targetNumber = rand() % 100 + 1;

                int userGuess;
                int attempts = 0;

                do {
                    // Get user's guess
                    cout << "Enter your guess: ";
                    cin >> userGuess;

                    // Check if the guess is correct
                    if (userGuess == targetNumber) {
                        cout << "Congratulations! You guessed the correct number in " << attempts + 1 << " attempts.\n";
                        break;
                    } else if (userGuess < targetNumber) {
                        cout << "Try a higher number.\n";
                    } else {
                        cout << "Try a lower number.\n";
                    }

                    attempts++;

                } while (true);
            } else if (gameChoice == 3) {
                // Watch Instagram Reels
                cout << "You chose to watch Instagram Reels. YOU ARE AN INSTAGRAM ADDICT\n";
            } else {
                // Invalid choice
                cout << "Invalid choice. Exiting...\n";
            }
        } else {
            // If traffic time is less than or equal to 15 minutes
            cout << "You have less than or equal to 15 minutes of traffic time. Keep waiting!\n";
        }
    } else {
        // If not stuck in traffic
        cout << "Great! No traffic. Keep moving!\n";
    }
}

// Function to load data for Kruskal's algorithm from a file
void load_from_file_krusgal() {
    ifstream file("abc.txt");

    if (!file) {
        cout << "File Not found\n";
        return;
    }

    while (file >> edge[krusgal_count].u >> edge[krusgal_count].v >> edge[krusgal_count].w) {
        krusgal_count++;
    }

    file.close();
}

// Function to check if two elements are in the same set (for Kruskal's algorithm)
int find(int arr[], int u, int v) {
    if (arr[u] == arr[v]) {
        return 1;
    } else {
        return 0;
    }
}

// Function to perform the union operation by merging two sets (for Kruskal's algorithm)
void union1(int arr[], int u, int v, int n) {
    int temp = arr[u];
    for (int i = 0; i < n; i++) {
        if (arr[i] == temp) {
            arr[i] = arr[v];
        }
    }
}

// Function to implement Kruskal's algorithm for finding the minimum spanning tree
void krusgal() {
    int e = 31; // Number of edges (hardcoded for this example)
    int sum = 0;

    load_from_file_krusgal();
    // Assuming bubblesort_krusgal is implemented elsewhere
    // bubblesort_krusgal(edge, e);

    int ver;
    cout << "Enter number of places you want to visit:";
    cin >> ver;

    int arr[ver];
    for (int i = 0; i < ver; i++) {
        arr[i] = i;
    }

    int findee;
    for (int i = 0; i < e - 1; i++) {
        findee = find(arr, edge[i].u, edge[i].v);
        if (findee == 0) {
            union1(arr, edge[i].u, edge[i].v, ver);
            sum += edge[i].w;
        }
    }

    cout << "Minimum_Time_Required: " << sum << " min" <<endl;
}

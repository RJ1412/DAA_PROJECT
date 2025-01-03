#ifndef HEADERR_H_INCLUDED
#define HEADERR_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>

#define ALPHABET_SIZE 26

// Variable to hold the inventory data containing the
// keywords and properties
char ***headerr;


// Variable to capture the time details
time_t mytime;


// Keeps a log of activity. Any errors can be checked in this file
FILE *flog;

struct petrol_data
{
    int dist;
    char location[150];
    char ps[150];
};
typedef struct petrol_data PD;
PD search_list[300];
PD save_petrol[300];

struct weather_data
{
    int time;
    char place[150];
    char weather[150];
};
typedef struct weather_data WD;
WD weather_list[300];

struct transportdata
{
    char source;
    char destination;
    int hours;
};
typedef struct transportdata td;
td transport_list[300];

int petrol_count = 0;
int weather_count = 0;

int transport_count = 0;
int count_petrol = 0;
int cost_matrix[150][150];
int visited[150], dist[150], path[150];
struct NODE
{
	int vehicle_number;
    int price;
    char vehicle_type[100];
	struct NODE *next;
};
	typedef struct NODE  *node;

struct road_quality
{
    char source[100];
    char destination[100];
    int quality_rating;
    int traffic_rating;
    int max_speed;
    int safety_rating;
    int road_id;
};

typedef struct road_quality rq;

rq quality_list[300];

int quality_count = 0;

struct tree
{
    int data;
    struct tree *left;
    struct tree *right;
};
typedef struct tree TREE;

#define ALPHABET_SIZE 26

#define ROWS 5
#define COLS 5


int car_parking[ROWS][COLS];
int bikes_parking[ROWS][COLS];

struct Person {
    char name[50];
    int licenseNumber;
    char carNumber[20];
    float fine;
    int isFinePending; // 1 if fine is pending, 0 otherwise
    // Add other relevant information
};

// Node structure for a linked list
struct Nod {
    struct Person data;
    struct Nod* next;
};

typedef struct Nod* nod;

struct nodee
{
    int u;
    int v;
    int w;
};
typedef struct nodee nodee;
nodee edge[40];
int krusgal_count=0;

#define MAX_PARKING_SPOTS 50
#define MAX_CAR_PLATE_LEN 10
char searchPlate[MAX_CAR_PLATE_LEN];

// Structure to represent parking spots
typedef struct {
    int spotNumber;
    int priority;
    char carPlate[MAX_CAR_PLATE_LEN];
} ParkingSpot;




void welcome_transport();

void welcome_weather();

void welcome_petrol();

void welcome();

int BruteForceStringMatch(char t[], char p[]);

void load_from_file();

void load_from_file_weather();

void load_from_file_transport();

void petrol_nearby();

void merge(PD b[], int p, PD c[], int q, PD A[]);

void mergesortt(PD A[], int n);

void sort_petroll();

void print_sorted_petrol();

void weather_info();

void search_transport();

void matrix();

void dijikstra();

node insert_rear(node head);

node insert_front(node head);

node getnode();

node read_details();

void display_list(node head);

node insert_pos(int pos,node head);

node delete_rear(node head);

node delete_front(node head);

void tollmanagement();

void load_from_file_quality();

void heapify(rq arr[], int n, int i);

void heap_sort_quality(rq arr[], int n);

void selection_sort_traffic(rq arr[], int n);

void insertion_sort_safety(rq arr[], int n);

TREE *insert_into_bst(TREE *root, int data);

void inorder(TREE *root);

void preorder(TREE *root);

void postorder(TREE *root);

TREE *delete_from_bst(TREE *root, int data);

TREE *insert_into_bst_by_road_id(TREE *root, int road_id);

void sorttt();

void bstttt();

void insert(struct TrieNode* root, const char* city);

int search(struct TrieNode* root, const char* city);

void freeTrie(struct TrieNode* root);

void triee();

#define ROWS 5

#define COLS 5


void initialize_parking();

void display_parking_status(int parking[][COLS]);

void park_vehicle(int parking[][COLS], char vehicle_type);

void parking();

nod getnod(struct Person person);

void enqueue(struct Person person, nod* front, nod* rear);

struct Person dequeue(nod* front, nod* rear);

void display_queue(nod front);

void display_pending_fines(nod front);

void queue_main();

void bubblesort_krusgal(nodee edge[],int e);
void load_from_file_krusgal();

int find(int arr[10], int u,int v);

void union1(int arr[10], int u,int v,int n);

void krusgal();

#define MAX_PARKING_SPOTS 50

#define MAX_CAR_PLATE_LEN 10

char searchPlate[MAX_CAR_PLATE_LEN];

void loadParkingData(ParkingSpot parkingSpots[], int *numParkingSpots);

void insertionSort(ParkingSpot arr[], int n);

int kmpSearch(char *text, char *pattern);

int dijkstra(int graph[MAX_PARKING_SPOTS][MAX_PARKING_SPOTS], int numVertices, int source, int destination);

void search_veh();







#endif // HEADERR_H_INCLUDED

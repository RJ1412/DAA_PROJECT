#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<limits.h>
#include <time.h>
#include "headerr.h"
// Function to print a welcome message for the transport schedule
void welcome_transport()
{
    int i = 0;

    // Print a line of asterisks for formatting
    for (i = 0; i < 80; i++)
        printf("*");

    // Print the title for the transport schedule section
    printf("\n\n\t\t\t\tIII TRANSPORT SCHEDULE III\n\n\n");

    // Print another line of asterisks for formatting
    for (i = 0; i < 80; i++)
        printf("*");

    // Print additional newlines for spacing
    printf("\n\n");
}

// Function to print a welcome message for searching weather information
void welcome_weather()
{
    int i = 0;

    // Print a line of asterisks for formatting
    for (i = 0; i < 80; i++)
        printf("*");

    // Print the title for the weather information search section
    printf("\n\n\t\t\t\tIII SEARCH WEATHER INFORMATION III\n\n\n");

    // Print another line of asterisks for formatting
    for (i = 0; i < 80; i++)
        printf("*");

    // Print additional newlines for spacing
    printf("\n\n");
}

// Function to print a welcome message for searching petrol stations nearby
void welcome_petrol()
{
    int i = 0;

    // Print a line of asterisks for formatting
    for (i = 0; i < 80; i++)
        printf("*");

    // Print the title for the petrol station search section
    printf("\n\n\t\t\t\tIII SEARCH PETROL STATIONS NEARBY III\n\n\n");

    // Print another line of asterisks for formatting
    for (i = 0; i < 80; i++)
        printf("*");

    // Print additional newlines for spacing
    printf("\n\n");
}

// Function to print a generic welcome message
void welcome()
{
    int i = 0;

    // Print a line of asterisks for formatting
    for (i = 0; i < 80; i++)
        printf("*");

    // Print a generic welcome title
    printf("\n\n\t\t\t\tIII WELCOME III\n\n\n");

    // Print another line of asterisks for formatting
    for (i = 0; i < 80; i++)
        printf("*");

    // Print additional newlines for spacing
    printf("\n\n");
}

// Function to perform brute-force string matching
// Returns the index of the first occurrence of the pattern in the text, or -1 if not found
int BruteForceStringMatch(char t[], char p[])
{
    int n, m;
    n = strlen(t);
    m = strlen(p);
    int j;

    for (int i = 0; i <= n - m; i++)
    {
        j = 0;
        // Check if characters in the pattern match corresponding characters in the text
        while (j < m && p[j] == t[i + j])
        {
            j = j + 1;
        }
        // If all characters match, return the starting index of the match
        if (j == m)
        {
            return i;
        }
    }

    // Return -1 if the pattern is not found in the text
    return -1;
}

// Function to load petrol data from a file
void load_from_file()
{
    FILE *fp;

    // Open the file for reading
    fp = fopen("petrol.txt", "r");

    // Check if the file exists
    if (fp == NULL)
    {
        printf("File Not found\n");
        return;
    }

    // Read data from the file into the search_list array
    while (fscanf(fp, "%s\t%s\t%d", search_list[petrol_count].location, search_list[petrol_count].ps, &search_list[petrol_count].dist) == 3)
    {
        // Print the loaded data (for demonstration purposes)
        printf("%s\t%s\t%d\n", search_list[petrol_count].location, search_list[petrol_count].ps, search_list[petrol_count].dist);
        petrol_count++;
    }

    // Close the file
    fclose(fp);
}

// Function to load weather data from a file
void load_from_file_weather()
{
    FILE *fp;

    // Open the file for reading
    fp = fopen("weather.txt", "r");

    // Check if the file exists
    if (fp == NULL)
    {
        printf("File Not found\n");
        return;
    }

    weather_count = 0;

    // Read data from the file into the weather_list array
    while (fscanf(fp, "%s\t%d\t%s", weather_list[weather_count].place, &weather_list[weather_count].time, weather_list[weather_count].weather) == 3)
    {
        // Print the loaded data (for demonstration purposes)
        printf("%s\t%d\t%s\n", weather_list[weather_count].place, weather_list[weather_count].time, weather_list[weather_count].weather);
        weather_count++;
    }

    // Close the file
    fclose(fp);
}

// Function to load transport data from a file
void load_from_file_transport() {
    FILE *fp;

    // Open the file for reading
    fp = fopen("transport.txt", "r");

    // Check if the file exists
    if (fp == NULL) {
        printf("File Not found\n");
        return;
    }

    // Read data from the file into the transport_list array
    while (fscanf(fp, " %c\t%c\t%d", &transport_list[transport_count].source,
                  &transport_list[transport_count].destination,
                  &transport_list[transport_count].hours) == 3) {
        // Print the loaded data (for demonstration purposes)
        printf("%c\t%c\t%d\n", transport_list[transport_count].source,
               transport_list[transport_count].destination,
               transport_list[transport_count].hours);
        transport_count++;
    }
       fclose(fp);
}
// while (!feof(fp) && transport_count < 300)



// Function to search for petrol stations nearby
void petrol_nearby()
{
    // Load petrol data from the file
    load_from_file();

    char a[1024];
    // Input the location to search for nearby petrol stations
    scanf("%s", a);

    printf("\nSearching petrol station near : %s\n", a);
    int searched_count = 0;

    // Iterate through the petrol stations and find matches based on the location
    for (int i = 0; i < petrol_count; i++)
    {
        // Use BruteForceStringMatch to check if the input location matches any petrol station location
        int index = BruteForceStringMatch(search_list[i].location, a);
        if (index != -1)
        {
            // Print the details of the matched petrol station
            printf("%s\t%s\t%d\n", search_list[i].location, search_list[i].ps, search_list[i].dist);
            // Save the matched petrol station data to another array
            save_petrol[searched_count] = search_list[i];
            searched_count++;
            count_petrol++;  // Increment the count of matched petrol stations
        }
    }
}

// Function to merge two sorted arrays
void merge(PD b[], int p, PD c[], int q, PD A[])
{
    int i = 0, j = 0, k = 0;

    // Merge the two arrays into a single sorted array
    while (i < p && j < q)
    {
        if (b[i].dist <= c[j].dist)
        {
            A[k] = b[i];
            i++;
        }
        else
        {
            A[k] = c[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements from array b
    while (i < p)
    {
        A[k] = b[i];
        i++;
        k++;
    }

    // Copy the remaining elements from array c
    while (j < q)
    {
        A[k] = c[j];
        j++;
        k++;
    }
}

// Function to perform mergesort on an array of petrol_data structures
void mergesortt(PD A[], int n)
{
    if (n > 1)
    {
        int p = n / 2;

        // Create two temporary arrays to store the halves of the original array
        PD b[p], c[n - p];
        for (int i = 0; i < p; i++)
        {
            b[i] = A[i];
        }
        for (int i = p; i < n; i++)
        {
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
void sort_petroll()
{
    mergesortt(save_petrol, count_petrol);
}

// Function to print the sorted petrol stations
void print_sorted_petrol()
{
    printf("\nSorted Petrol Stations:\n");
    for (int i = 0; i < count_petrol; i++)
    {
        printf("%s\t%s\t%d\n", save_petrol[i].location, save_petrol[i].ps, save_petrol[i].dist);
    }
}

// Function to search for weather information at a particular location
void weather_info()
{
    // Load weather data from the file
    load_from_file_weather();

    char a[1024];
    // Input the location to search for weather information
    scanf("%s", a);

    printf("\nsearch weather at a particular location : %s\n", a);
    int searched_count = 0;

    // Iterate through the weather data and find matches based on the location
    for (int i = 0; i < weather_count; i++)
    {
        // Use BruteForceStringMatch to check if the input location matches any weather data location
        int index = BruteForceStringMatch(weather_list[i].place, a);
        if (index != -1)
        {
            // Print the weather information for the matched location
            printf("%s\t%s\t%d\n", weather_list[i].place, weather_list[i].weather, weather_list[i].time);
            searched_count++;
        }
    }
}

// Function to search for available public transport between two locations
void search_transport() {
    char src;
    printf("Enter the pickup location: ");
    scanf(" %c", &src);
    printf("Enter the drop location\n");
    // load_from_file_transport();  // Commented to avoid reading the file multiple times

    int searched_count = 0;

    // Iterate through the transport data and find matches based on the location
    for (int i = 0; i < transport_count; i++) {
        int index = BruteForceStringMatch(&transport_list[i].source, &src);
        if (index != -1) {
            // Print the transport information for the matched location
            printf("%c\t%c\t%d\n", transport_list[i].source, transport_list[i].destination, transport_list[i].hours);
            searched_count++;
        }
    }
}



// Function to initialize the cost_matrix with values and set diagonal elements to 0
void matrix() {
    int counter = 1;

    // Fill the cost_matrix with sequential values
    for (int i = 0; i < 150; i++) {
        for (int j = 0; j < 150; j++) {
            cost_matrix[i][j] = counter++;
        }
    }

    // Set diagonal elements to 0
    for (int i = 0; i < 150; i++) {
        for (int j = 0; j < 150; j++) {
            if (i == j)
                cost_matrix[i][j] = 0;
        }
    }
}

// Function to perform Dijkstra's algorithm on the cost_matrix
void dijikstra()
{
    // Initialize the cost_matrix
    matrix();

    // Variables to store the number of vertices and edges
    int v = 150;
    int e = 11175;

    // Arrays to store distance, visited nodes, and path information
    int distn;
    int src;
    printf("enter source: ");
    scanf("%d", &src);

    // Initialize distance and path arrays with values from the cost_matrix
    for (int i = 0; i < v; i++) {
        dist[i] = cost_matrix[src][i];
        path[i] = src;
    }

    // Mark the source node as visited
    visited[src] = 1;

    // Perform Dijkstra's algorithm
    for (int j = 0; j < v - 1; j++) {
        int min = INT_MAX;
        int u = -1; // Initialize u and distn

        // Find the minimum distance vertex from the set of vertices not yet processed
        for (int i = 0; i < v; i++) {
            if (visited[i] != 1) {
                if (dist[i] < min) {
                    min = dist[i];
                    u = i;
                }
            }
        }

        // Check if there are no reachable nodes left
        if (u == -1) {
            printf("No reachable nodes\n");
            break;
        }

        // Update distn and mark the selected vertex as visited
        distn = dist[u];
        visited[u] = 1;

        // Update distance and path values for adjacent vertices
        for (int i = 0; i < v; i++) {
            if (visited[i] != 1) {
                if (dist[i] > (distn + cost_matrix[u][i])) {
                    dist[i] = distn + cost_matrix[u][i];
                    path[i] = u;
                }
            }
        }
    }

    // Print the minimum distance and distances to each vertex
    printf("Minimum Distance: %d\n", distn);
    printf("Distances: ");
    for (int i = 0; i < v; i++) {
        printf("%d\t", dist[i]);
    }
}




// Function to create a new node and return its address
node getnode()
{
    node new;
    new = (node)malloc(sizeof(struct NODE));
    if (new == NULL)
    {
        printf("Memory allocation failed\n");
        exit(0);
    }
    new->next = NULL;
    return new;
}

// Function to display the elements of the linked list
void display_list(node head)
{
    node cur;
    if (head == NULL)
    {

        printf("Empty List\n");
        return;

    }
    printf("Elements are:\n");
    cur = head;
    while (cur != NULL)
    {

        printf("%d\t", cur->vehicle_number);
        printf("%d\t", cur->price);
        printf("%s\t", cur->vehicle_type);
        cur = cur->next;

    }
    printf("\n");


}

// Function to insert a new node at the rear of the linked list
node insert_rear(node head)
{
    node new, cur;
    new = read_details();
    new->next = NULL;
    if (head == NULL)
        return new;
    cur = head;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = new;
    return head;

}

// Function to read details and return a new node
node read_details()
{
    node temp;
    temp = getnode();
    printf("Enter the data\n");
    printf("enter vehicle number");
    scanf("%d", &temp->vehicle_number);
    printf("enter amount paid");
    scanf("%d", &temp->price);
    printf("enter vehivle type");
    scanf("%s", temp->vehicle_type);
    return temp;

}

// Function to insert a new node at the front of the linked list
node insert_front(node head)
{

    node new;
    new = read_details();
    new->next = NULL;
    if (head == NULL)
        return new;
    new->next = head;
    head = new;
    return head;


}

// Function to delete the node at the front of the linked list
node delete_front(node head)
{
    node cur;
    if (head == NULL)
    {

        printf("List empty\n");
        return head;

    }
    cur = head;
    head = head->next;
    printf("Deleted: %d\t", cur->vehicle_number);
    printf("Deleted: %d\t", cur->price);
    printf("Deleted: %s\t", cur->vehicle_type);
    free(cur);
    return head;

}

// Function to insert a new node at a specified position in the linked list
node insert_pos(int pos, node head)
{
    node new, prev, cur;
    int count;
    new = read_details();
    new->next = NULL;
    if (head == NULL && pos == 1)
        return new;
    if (head == NULL)
    {
        printf("Invalid position\n");
        return head;
    }
    if (pos == 1)
    {

        new->next = head;
        return new;

    }
    count = 1;
    prev = NULL;
    cur = head;
    while (cur != NULL && count != pos)
    {
        prev = cur;
        cur = cur->next;
        count++;
    }
    if (count == pos)
    {

        prev->next = new;
        new->next = cur;
        return head;

    }
    else
        printf("Invalid position\n");
    return head;
}

// Function to delete the node at the rear of the linked list
node delete_rear(node head)
{
    node prev, cur;
    if (head == NULL)
    {
        printf("List empty\n");
        return head;

    }
    if (head->next == NULL)
    {

        cur = head;
        printf("Deleted: %d\t", cur->vehicle_number);
        printf("Deleted: %d\t", cur->price);
        printf("Deleted: %s\t", cur->vehicle_type);
        free(head);
        return NULL;

    }
    prev = NULL;
    cur = head;
    while (cur->next != NULL)
    {

        prev = cur;
        cur = cur->next;

    }
    printf("Deleted: %d\t", cur->vehicle_number);
    printf("Deleted: %d\t", cur->price);
    printf("Deleted: %s\t", cur->vehicle_type);
    free(cur);
    prev->next = NULL;
    return head;

}

// Function to delete the node at a specified position in the linked list
node delete_pos(int pos, node head)
{
    node cur, prev;
    int count;

    if (head == NULL)
    {
        printf("List empty\n");
        return NULL;
    }
    if (pos == 1)
    {

        cur = head;
        head = head->next;
        printf("Deleted: %d\t", cur->vehicle_number);
        printf("Deleted: %d\t", cur->price);
        printf("Deleted: %s\t", cur->vehicle_type);
        free(cur);
        return head;

    }
    prev = NULL;
    cur = head;
    count = 1;
    while (cur != NULL && count != pos)
    {
        prev = cur;
        cur = cur->next;
        count++;
    }
    if (cur == NULL)
    {
        printf("Invalid position specified\n");
        return head;
    }
    prev->next = cur->next;
    printf("Deleted: %d\t", cur->vehicle_number);

    printf("Deleted: %d\t", cur->price);

    printf("Deleted: %s\t", cur->vehicle_type);
    free(cur);

    return head;
}

// Function to manage toll operations using a linked list
void tollmanagement()
{
    // Initialize the linked list
    node head = NULL;

    int choice, pos;

    for (;;)
    {
        // Display menu for toll management operations
        printf("1-Insert Rear\n2-Display\n3-Insert Front \n4-Insert Position\n5-Delete Rear\n6-Delete Front\n9:Exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // Insert a node at the rear
            printf("Enter value for data field\n");
            head = insert_rear(head);
            break;

        case 2:
            // Display the linked list
            printf("Display List Inserted\n");
            display_list(head);
            break;

        case 3:
            // Insert a node at the front
            printf("Enter item to be inserted\n");
            head = insert_front(head);
            break;

        case 4:
            // Insert a node at a specified position
            printf("Enter the position to be inserted\n");
            scanf("%d", &pos);
            head = insert_pos(pos, head);
            break;

        case 5:
            // Delete the node at the rear
            printf("Rear element delete\n");
            head = delete_rear(head);
            break;

        case 6:
            // Delete the node at the front
            printf("Front element delete\n");
            head = delete_front(head);
            break;

        default:
            // Exit the program
            return;
        }
    }
}

void load_from_file_quality()
{
    FILE *fp;

    fp = fopen("map.txt", "r");  // Assuming the file is named "map.txt"

    if (fp == NULL)
    {
        printf("File Not found\n");
        return;
    }

    while (fscanf(fp, "%s\t%s\t%d\t%d\t%d\t%d\t%d", quality_list[quality_count].source, quality_list[quality_count].destination, &quality_list[quality_count].quality_rating, &quality_list[quality_count].traffic_rating, &quality_list[quality_count].max_speed, &quality_list[quality_count].safety_rating, &quality_list[quality_count].road_id) == 7)
    {
        printf("%s\t%s\t%d\t%d\t%d\t%d\n", quality_list[quality_count].source, quality_list[quality_count].destination, quality_list[quality_count].quality_rating, quality_list[quality_count].traffic_rating, quality_list[quality_count].max_speed, quality_list[quality_count].safety_rating);
        quality_count++;
    }

    fclose(fp);
}

// Function to maintain the heap property for a subtree rooted at node i
void heapify(rq arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].quality_rating > arr[largest].quality_rating)
    {
        largest = left;
    }

    if (right < n && arr[right].quality_rating > arr[largest].quality_rating)
    {
        largest = right;
    }

    if (largest != i)
    {
        // Swap arr[i] and arr[largest]
        rq temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

// Function to perform heap sort on an array of road quality data
void heap_sort_quality(rq arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        // Swap arr[0] and arr[i]
        rq temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}


// Function to perform selection sort on an array of road quality data based on traffic rating
void selection_sort_traffic(rq arr[], int n)
{
    int i, j, min_index;
    rq temp;
    for (i = 0; i < n - 1; i++)
    {
        min_index = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j].traffic_rating < arr[min_index].traffic_rating)
            {
                min_index = j;
            }
        }
        temp = arr[min_index];
        arr[min_index] = arr[i];
        arr[i] = temp;
    }
}


// Function to perform insertion sort on an array of road quality data based on safety rating
void insertion_sort_safety(rq arr[], int n)
{
    int i, j;
    rq key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j].safety_rating > key.safety_rating)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}



TREE *insert_into_bst(TREE *root, int data)
{
    TREE *newnode;
    newnode = (TREE *)malloc(sizeof(TREE));
    if (newnode == NULL)
    {
        printf("memory allocation error");
        return root;
    }
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    if (root == NULL)
    {
        printf("root is created");
        root = newnode;
        return root;
    }

    TREE *cur, *parent;
    cur = root;
    parent = NULL;
    while (cur != NULL)
    {
        parent = cur;
        if (newnode->data < cur->data)
        {
            cur = cur->left;
        }
        else
        {
            cur = cur->right;
        }
    }
    if (newnode->data < parent->data)
    {
        parent->left = newnode;
    }
    else
    {
        parent->right = newnode;
    }
    return root;
}
void inorder(TREE *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d\t", root->data);
        inorder(root->right);
    }
}

void preorder(TREE *root)
{
    if (root != NULL)
    {
        printf("%d\t", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(TREE *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d\t", root->data);
    }
}

TREE *delete_from_bst(TREE *root, int data)
{
    TREE *cur, *parent, *p, *succ;
    if (root == NULL)
    {
        printf("empty tree\n");
        return root;
    }
    cur = root;
    parent = NULL;
    while (cur != NULL && cur->data != data)
    {
        parent = cur;
        if (data < cur->data)
        {
            cur = cur->left;
        }
        else
        {
            cur = cur->right;
        }
    }

    if (cur == NULL)
    {
        printf("item not found in tree\n");
        return root;
    }
    if (cur->left == NULL)
    {
        p = cur->right;
    }
    else if (cur->right == NULL)
    {
        p = cur->left;
    }
    else
    {
        succ = cur->right;
        while (succ->left != NULL)
        {
            succ = succ->left;
        }
        succ->left = cur->left;
        p = cur->right;
    }
    if (parent == NULL)
    {
        free(cur);
        return p;
    }
    if (cur == parent->left)
    {
        parent->left = p;
    }
    else
        parent->right = p;

    free(cur);
    return root;
}

// Function to insert into BST based on road ID
TREE *insert_into_bst_by_road_id(TREE *root, int road_id)
{
    int data = road_id;
    return insert_into_bst(root, data);
}
void sorttt()
{
   int choice;

    // Load road details from file into the BST
    load_from_file_quality();

    do
    {
        printf("\nOperations:\n");
        printf("1. Display Roads (sorted by Quality Rating)\n");
        printf("2. Display Roads (sorted by Traffic Rating)\n");
        printf("3. Display Roads (sorted by Safety Rating)\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // Sort based on Quality Rating using Heap Sort
            heap_sort_quality(quality_list, quality_count);
            printf("Roads sorted by Quality Rating:\n");
            for (int i = 0; i < quality_count; i++)
            {
                printf("%d %s %s %d %d %d %d\n", quality_list[i].road_id, quality_list[i].source, quality_list[i].destination, quality_list[i].quality_rating, quality_list[i].traffic_rating, quality_list[i].max_speed, quality_list[i].safety_rating);

            }

            break;

        case 2:
            // Sort based on Traffic Rating using Selection Sort
            selection_sort_traffic(quality_list, quality_count);
            printf("Roads sorted by Traffic Rating:\n");
            for (int i = 0; i < quality_count; i++)
            {

                printf("%d %s %s %d %d %d %d\n", quality_list[i].road_id, quality_list[i].source, quality_list[i].destination, quality_list[i].quality_rating, quality_list[i].traffic_rating, quality_list[i].max_speed, quality_list[i].safety_rating);

            }
            break;


        case 3:
            // Sort based on Safety Rating using Insertion Sort
            insertion_sort_safety(quality_list, quality_count);
            printf("Roads sorted by Safety Rating:\n");
            for (int i = 0; i < quality_count; i++)
            {
                printf("%d %s %s %d %d %d %d\n", quality_list[i].road_id, quality_list[i].source, quality_list[i].destination, quality_list[i].quality_rating, quality_list[i].traffic_rating, quality_list[i].max_speed, quality_list[i].safety_rating);
            }
            break;

        case 4:
            printf("Exiting the program.\n");
            break;

        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 4);



}

void bstttt()
{
    load_from_file_quality();
    TREE *root = NULL;
    for(int i=0;i<quality_count;i++)
    {
        root = insert_into_bst_by_road_id(root, quality_list[i].road_id);
    }
    int choice, data;

    do
    {
        printf("\nBinary Search Tree Operations:\n");
        printf("1. Insert (BST based on road ID)\n");
        printf("2. Delete\n");
        printf("3. Inorder Traversal\n");
        printf("4. Preorder Traversal\n");
        printf("5. Postorder Traversal\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the road ID to insert: ");
            scanf("%d", &data);
            root = insert_into_bst_by_road_id(root, data);
            break;

        case 2:
            printf("Enter the element to delete: ");
            scanf("%d", &data);
            root = delete_from_bst(root, data);
            break;

        case 3:
            printf("Inorder Traversal: ");
            inorder(root);
            printf("\n");
            break;

        case 4:
            printf("Preorder Traversal: ");
            preorder(root);
            printf("\n");
            break;

        case 5:
            printf("Postorder Traversal: ");
            postorder(root);
            printf("\n");
            break;

        case 6:
            printf("Exiting the program.\n");
            break;

        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 6);
}




void initialize_parking() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            car_parking[i][j] = 0;
            bikes_parking[i][j] = 0;
        }
    }
}

void display_parking_status(int parking[][COLS]) {
    printf("Parking Status:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", parking[i][j]);
        }
        printf("\n");
    }
}

void park_vehicle(int parking[][COLS], char vehicle_type) {
    int row, col;
    printf("Enter the row and column to park the %c (0-indexed): ", vehicle_type);
    scanf("%d %d", &row, &col);

    switch (vehicle_type) {
        case 'B':
        case 'b':
            if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
                if (parking[row][col] == 0) {
                    parking[row][col] = 1;
                    printf("%c parked successfully in slot (%d, %d).\n", vehicle_type, row, col);
                } else {
                    printf("Slot (%d, %d) is already occupied.\n", row, col);
                }
            } else {
                printf("Invalid parking slot. Please enter valid row and column.\n");
            }
            break;

        case 'C':
        case 'c':
            if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
                if (parking[row][col] == 0) {
                    parking[row][col] = 1;
                    printf("%c parked successfully in slot (%d, %d).\n", vehicle_type, row, col);
                } else {
                    printf("Slot (%d, %d) is already occupied.\n", row, col);
                }
            } else {
                printf("Invalid parking slot. Please enter valid row and column.\n");
            }
            break;
            break;

        default:
            printf("Invalid vehicle type.\n");
    }
}
void parking()
{
      initialize_parking();

    while (1) {
        char choice;
        printf("Enter 'B' to park a bike, 'C' to park a car, or 'Q' to quit: ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'Q':
            case 'q':
                return ;

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
                printf("Invalid choice. Please enter 'B', 'C', or 'Q'.\n");
        }
    }
}
// Structure to represent a person


// Function to create a new node with a given person's data
nod getnod(struct Person person) {
    nod t = (nod)malloc(sizeof(struct Nod));
    if (t == NULL) {
        printf("Memory allocation failed\n");
        exit(0);
    }
    t->data = person;
    t->next = NULL;
    return t;
}

// Function to enqueue a person into the linked list
void enqueue(struct Person person, nod* front, nod* rear) {
    nod t = getnod(person);
    if (*rear == NULL) {
        *front = *rear = t;
    } else {
        (*rear)->next = t;
        *rear = t;
    }
}

// Function to dequeue a person from the linked list
struct Person dequeue(nod* front, nod* rear) {
    struct Person person;
    person.licenseNumber = -1; // Initialize with an invalid value

    if (*front == NULL) {
        printf("Queue is empty\n");
        return person;
    }

    nod t = *front;
    person = t->data;
    *front = t->next;

    if (*front == NULL) {
        *rear = NULL;
    }

    free(t);
    return person;
}

// Function to display all persons in the linked list
void display_queue(nod front) {
    if (front == NULL) {
        printf("Queue is empty\n");
        return;
    }

    while (front != NULL) {
        printf("Name: %s, License Number: %d, Car Number: %s, Fine: %.2f, Fine Pending: %s\n",
               front->data.name, front->data.licenseNumber, front->data.carNumber,
               front->data.fine, (front->data.isFinePending ? "Yes" : "No"));
        front = front->next;
    }

    printf("\n");
}

// Function to display persons with pending fines in the linked list
void display_pending_fines(nod front) {
    if (front == NULL) {
        printf("Queue is empty\n");
        return;
    }

    while (front != NULL) {
        if (front->data.isFinePending) {
            printf("Name: %s, License Number: %d, Car Number: %s, Fine: %.2f\n",
                   front->data.name, front->data.licenseNumber, front->data.carNumber, front->data.fine);
        }
        front = front->next;
    }

    printf("\n");
}

void queue_main()
{
    nod front = NULL, rear = NULL;
    int choice;
    struct Person person;

    for (;;) {
        printf("1-Enqueue\n2-Dequeue\n3-Display\n4-Display Pending Fines\n5-Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Enqueue a new person
                printf("Enter person details:\n");
                printf("Name: ");
                scanf("%s", person.name);
                printf("License Number: ");
                scanf("%d", &person.licenseNumber);
                printf("Car Number: ");
                scanf("%s", person.carNumber);
                printf("Fine in Rupees: ");
                scanf("%f", &person.fine);
                printf("Is Fine Pending (1 for Yes, 0 for No): ");
                scanf("%d", &person.isFinePending);
                enqueue(person, &front, &rear);
                break;
            case 2:
                // Dequeue a person
                person = dequeue(&front, &rear);
                if (front != NULL)
                    printf("Dequeued person: %s, License Number: %d\n", person.name, person.licenseNumber);
                break;
            case 3:
                // Display all persons
                printf("Queue elements:\n");
                display_queue(front);
                break;
            case 4:
                // Display persons with pending fines
                printf("People with Pending Fines:\n");
                display_pending_fines(front);
                break;
            case 5:
                // Exit the program
                exit(0);
            default:
                // Invalid choice
                printf("Invalid choice\n");
        }
    }

}

void bubblesort_krusgal(nodee edge[],int e)
{
    nodee temp;
    for(int i=0;i<e-2;i++)
    {
        for(int j=0;j<e-2-1;j++)
        {
            if(edge[j+1].w<edge[j].w)
            {
                temp=edge[j+1];
                edge[j+1]=edge[j];
                edge[j]=temp;
            }
        }
    }
}

// Structure to represent parking spots


// Function prototypes

// Function to load parking data from a file
void loadParkingData(ParkingSpot parkingSpots[], int *numParkingSpots)
{
    FILE *file = fopen("app_9.txt", "r");
    if (file == NULL) {
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%d\t%d\t%s", &parkingSpots[*numParkingSpots].spotNumber, &parkingSpots[*numParkingSpots].priority, parkingSpots[*numParkingSpots].carPlate) == 3) {
        (*numParkingSpots)++;
    }

    fclose(file);
}

// Function to perform insertion sort on parking data based on priority
void insertionSort(ParkingSpot arr[], int n) {
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

// Knuth-Morris-Pratt algorithm for string searching
int kmpSearch(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    int *lps = (int *)malloc(sizeof(int) * m);
    int j = 0;

    // Build the LPS (Longest Proper Prefix which is also Suffix) array
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
            free(lps);
            return i - j + 1; // Pattern found, return the starting index
        }
    }

    free(lps);
    return -1; // Pattern not found
}

// Dijkstra's algorithm for finding the shortest distance
int dijkstra(int graph[MAX_PARKING_SPOTS][MAX_PARKING_SPOTS], int numVertices, int source, int destination) {
    int distance[MAX_PARKING_SPOTS];
    int visited[MAX_PARKING_SPOTS];

    for (int i = 0; i < numVertices; i++) {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }

    distance[source] = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = -1;
        for (int i = 0; i < numVertices; i++) {
            if (!visited[i] && (u == -1 || distance[i] < distance[u])) {
                u = i;
            }
        }

        visited[u] = 1;

        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && graph[u][v] != INT_MAX && distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
            }
        }
    }

    return distance[destination];
}
void search_veh()
{
     ParkingSpot parkingSpots[MAX_PARKING_SPOTS];
    int choice;
    int numParkingSpots = 0;

    while (1) {
        printf("Enter choice (1: Load and Sort, 2: Search, 3: Exit): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Load parking data from file
                loadParkingData(parkingSpots, &numParkingSpots);

                // Sort parking data using insertion sort based on priority
                insertionSort(parkingSpots, numParkingSpots);
                break;

            case 2:
                // Search for car plate using Knuth-Morris-Pratt algorithm


                printf("Enter a car plate to search: ");
                scanf("%s", searchPlate);

                for (int i = 0; i < numParkingSpots; i++) {
                    if (kmpSearch(parkingSpots[i].carPlate, searchPlate) != -1) {
                        printf("Car plate found at spot %d with priority %d\n", parkingSpots[i].spotNumber, parkingSpots[i].priority);
                        break;
                    }
                }
                break;

            case 3:
                // Exit the program
                return;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }

        // Create a graph for Dijkstra's algorithm
        int graph[MAX_PARKING_SPOTS][MAX_PARKING_SPOTS];
        for (int i = 0; i < numParkingSpots; i++) {
            for (int j = 0; j < numParkingSpots; j++) {
                graph[i][j] = (i == j) ? 0 : INT_MAX;
            }
        }

        // Assume there is an edge between adjacent parking spots

        for (int i = 0; i < numParkingSpots - 1; i++) {
            graph[i][i + 1] = graph[i + 1][i] = 1;
        }

        // Find and print the shortest distance using Dijkstra's algorithm
        int shortestDistance = dijkstra(graph, numParkingSpots, 0, numParkingSpots - 1);
        printf("Shortest distance from the entrance to the last spot: %d\n", shortestDistance);
    }
}


void displayNumberGuessing() {
    printf("\nNumber Guessing Game:\n");
    printf("I have selected a number between 1 and 100.\n");
    printf("Try to guess the number!\n\n");
}

// Function to display Rock-Paper-Scissors game
void displayRockPaperScissors() {
    printf("\nRock-Paper-Scissors Game:\n");
    printf("You are playing against the computer.\n");
    printf("Enter 'r' for rock, 'p' for paper, or 's' for scissors.\n\n");
}
void game()
{
    char stuckInTraffic;
    int trafficTime;

    // Ask the user if they are stuck in traffic
    printf("Are you stuck in traffic? (y/n): ");
    scanf(" %c", &stuckInTraffic);

    if (stuckInTraffic == 'y' || stuckInTraffic == 'Y') {
        // If yes, ask for estimated traffic time
        printf("Enter estimated traffic time (in minutes): ");
        scanf("%d", &trafficTime);

        if (trafficTime > 15) {
            // If traffic time is greater than 15 minutes, prompt user to choose a game
            printf("You have more than 15 minutes of traffic time.\n");

            int gameChoice;

            // Ask the user to choose a game
            printf("Choose a game:\n");
            printf("1. Rock-Paper-Scissors\n");
            printf("2. Number Guessing\n");
            printf("3. Watch Instagram Reels\n");
            printf("Enter your choice (1, 2, or 3): ");
            scanf("%d", &gameChoice);

            if (gameChoice == 1) {
                // Rock-Paper-Scissors game
                displayRockPaperScissors();

                char userChoice;
                char computerChoice;

                do {
                    // Get user's choice
                    printf("Enter your choice (r/p/s): ");
                    scanf(" %c", &userChoice);

                    // Validate user's choice
                    if (userChoice != 'r' && userChoice != 'p' && userChoice != 's') {
                        printf("Invalid choice. Please enter 'r', 'p', or 's'.\n");
                        continue;
                    }

                    // Get computer's choice
                    srand(time(NULL));
                    int randomChoice = rand() % 3;
                    switch (randomChoice) {
                        case 0:
                            computerChoice = 'r';
                            break;
                        case 1:
                            computerChoice = 'p';
                            break;
                        case 2:
                            computerChoice = 's';
                            break;
                    }

                    // Display choices
                    printf("Your choice: %c\n", userChoice);
                    printf("Computer's choice: %c\n", computerChoice);

                    // Determine the winner
                    if (userChoice == computerChoice) {
                        printf("It's a tie!\n");
                    } else if ((userChoice == 'r' && computerChoice == 's') ||
                               (userChoice == 'p' && computerChoice == 'r') ||
                               (userChoice == 's' && computerChoice == 'p')) {
                        printf("You win!\n");
                    } else {
                        printf("Computer wins!\n");
                    }

                    // Ask if the user wants to play again
                    printf("Do you want to play again? (y/n): ");
                    scanf(" %c", &userChoice);

                } while (userChoice == 'y' || userChoice == 'Y');
            } else if (gameChoice == 2) {
                // Number Guessing game
                displayNumberGuessing();

                // Generate a random number between 1 and 100
                srand(time(NULL));
                int targetNumber = rand() % 100 + 1;

                int userGuess;
                int attempts = 0;

                do {
                    // Get user's guess
                    printf("Enter your guess: ");
                    scanf("%d", &userGuess);

                    // Check if the guess is correct
                    if (userGuess == targetNumber) {
                        printf("Congratulations! You guessed the correct number in %d attempts.\n", attempts + 1);
                        break;
                    } else if (userGuess < targetNumber) {
                        printf("Try a higher number.\n");
                    } else {
                        printf("Try a lower number.\n");
                    }

                    attempts++;

                } while (1);
            } else if (gameChoice == 3) {
                // Watch Instagram Reels
                printf("You chose to watch Instagram Reels. YOU ARE AN INSTAGRAM ADDICT\n");
            } else {
                // Invalid choice
                printf("Invalid choice. Exiting...\n");
            }
        } else {
            // If traffic time is less than or equal to 15 minutes
            printf("You have less than or equal to 15 minutes of traffic time. Keep waiting!\n");
        }
    } else {
        // If not stuck in traffic
        printf("Great! No traffic. Keep moving!\n");
    }
}
void load_from_file_krusgal()
{
    FILE *fp;

    fp = fopen("abc.txt", "r");
    if (fp == NULL)
    {
        printf("File Not found\n");
        return;
    }

    while (fscanf(fp, "%d\t%d\t%d", &edge[ krusgal_count].u, &edge[ krusgal_count].v, &edge[ krusgal_count].w) == 3)
    {

         krusgal_count++;
    }

    fclose(fp);
}

// Function to check if two elements in the array have the same representative (are in the same set)
int find(int arr[10], int u, int v)
{
    // If the representatives of elements 'u' and 'v' are the same, they are in the same set
    if (arr[u] == arr[v])
    {
        // Return 1 to indicate that 'u' and 'v' are in the same set
        return 1;
    }
    else
    {
        // Return 0 to indicate that 'u' and 'v' are not in the same set
        return 0;
    }
}

// Function to perform the union operation by merging the sets of 'u' and 'v'
void union1(int arr[10], int u, int v, int n)
{
    // Store the representative of 'u' in a temporary variable
    int temp = arr[u];
    int i;

    // Iterate through the array to update the representatives of elements in the set of 'u'
    for (i = 0; i < n; i++)
    {
        // If the representative of the current element is the same as that of 'u', update it to the representative of 'v'
        if (arr[i] == temp)
        {
            arr[i] = arr[v];
        }
    }
}

// Function to implement Kruskal's algorithm for finding the minimum spanning tree of a graph
void krusgal()
{

    int e;
    int sum=0;
    e=31;
   load_from_file_krusgal();
    bubblesort_krusgal(edge,e);
    int ver;
    printf("enter no of vertices\n");
    scanf("%d",&ver);
    int arr[ver];
    for(int i=0;i<ver;i++)
    {
     arr[i]=i;
    }
    int findee;
    for(int i=0;i<e-1;i++)
    {
      findee= find(arr, edge[i].u,edge[i].v);
      if(findee==0)
      {
         union1( arr,  edge[i].u, edge[i].v, ver);
         sum=sum+ edge[i].w;

      }
    }
    printf("%d \n",sum);
}



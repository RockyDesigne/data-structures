//
// Created by HORIA on 29.11.2023.
//

#ifndef DATA_STRUCTURES_GRAPH_WITH_ADJACENCY_MATRIX_H
#define DATA_STRUCTURES_GRAPH_WITH_ADJACENCY_MATRIX_H

//
// Created by HORIA on 16.11.2023.
//
#include <iostream>
#include <cstring>
#include <string>

#define NR_NODES_INIT 2
#define OFFSET 1

int CURR_NR_NODES {};

char** alloc_info(int size) {
    char** info {new char*[size]};
    for (int i {0}; i < size; ++i) {
        info[i] = new char[1];
        info[i][0] = '\0';
    }
    return info;
}

void zero_mat_adj(int** m, int M_SIZE) {
    for (int i {0}; i < M_SIZE; ++i) {
        for (int j {0}; j < M_SIZE; ++j) {
            m[i][j] = 0;
        }
    }
}

//int matrice_adj[NR_NODES_INIT+1][NR_NODES_INIT+1] = {0};
int** matrice_adj {};
int MATRICE_ADJ_SIZE {NR_NODES_INIT+OFFSET};

//zona de memorie alocata stocarii informatiei din noduri
char** INFO {};
int INFO_SIZE {NR_NODES_INIT+OFFSET};

void delete_mat_adj() {
    //delete old matrix
    for (int i {0}; i < MATRICE_ADJ_SIZE; ++i) {
        delete []matrice_adj[i];
    }
    delete []matrice_adj;
}

void delete_info() {
    //delete old info
    for (int i {0}; i < INFO_SIZE; ++i) {
        delete []INFO[i];
    }
    delete []INFO;
}

/*
void update_adj_mat() {
    for (int i {1}; i <= CURR_NR_NODES; ++i) {
        std::cout << "Are nodul: " << CURR_NR_NODES << " muchie cu nodul: "
                  << i << " ?(y/n)";
        char ans;
        std::cin >> ans;
        if (ans == 'y') {
            matrice_adj[CURR_NR_NODES][i] = 1;
        }
        std::cout << "Are nodul: " << i << " muchie cu nodul " << CURR_NR_NODES << " ?(y/n)";
        ans = ' ';
        std::cin >> ans;
        if (ans == 'y') {
            matrice_adj[i][CURR_NR_NODES] = 1;
        }
    }
}
*/

int** alloc_mat_adj(int size) {
    int** mat {new int*[size]};
    for (int i {0}; i < size; ++i) {
        mat[i] = new int[size];
    }
    return mat;
}

void add_col_add_line() {
    int** temp_adj = alloc_mat_adj(MATRICE_ADJ_SIZE*2);
    zero_mat_adj(temp_adj, MATRICE_ADJ_SIZE*2);

    //copy over old matrix
    for (int i {0}; i < MATRICE_ADJ_SIZE; ++i) {
        for (int j = 0; j < MATRICE_ADJ_SIZE; ++j) {
            temp_adj[i][j] = matrice_adj[i][j];
        }
    }
    delete_mat_adj();
    matrice_adj = temp_adj;
    MATRICE_ADJ_SIZE*=2;
}

void increase_info_arr() {
    char** temp_info {alloc_info(INFO_SIZE*2)};
    for (int i {0}; i < INFO_SIZE; ++i) {
        temp_info[i] = new char[std::strlen(INFO[i]) + 1];
        std::strcpy(temp_info[i], INFO[i]);
    }

    delete_info();
    INFO = temp_info;
    INFO_SIZE*=2;
}

std::string get_info() {
    std::cout << "Enter name: ";
    std::string nume {};
    std::getline(std::cin, nume);
    std::getline(std::cin, nume);
    return nume;
}

void add_node() {
    ++CURR_NR_NODES;// step 1
    if (CURR_NR_NODES == MATRICE_ADJ_SIZE-1) //step2
        add_col_add_line();
    if (CURR_NR_NODES == INFO_SIZE-1) //step 3
        increase_info_arr();
    //update_adj_mat(); //step 4
    //step 5
    std::string nume {get_info()};
    INFO[CURR_NR_NODES] = new char[std::strlen(&nume[0]) + 1];
    std::strcpy(INFO[CURR_NR_NODES], &nume[0]);
}

void print(int** mat) {
    for (int i{1}; i <= CURR_NR_NODES; ++i) {
        for (int j{1}; j <= CURR_NR_NODES; ++j) {
            std::cout << mat[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void sterge_din_info(int nrNod) {
    char* tmp {INFO[nrNod]};
    for (int i {nrNod}; i < INFO_SIZE-1; ++i) {
        INFO[i]=INFO[i+1];
    }
    --INFO_SIZE;
    delete []tmp;
}

void sterge_din_mat_adj(int nrNod) {
    //sterge coloana
    for (int i {0}; i < MATRICE_ADJ_SIZE; ++i) {
        for (int j {nrNod}; j < MATRICE_ADJ_SIZE-1;++j) {
            matrice_adj[i][j]=matrice_adj[i][j+1];
        }
    }
    //sterge linia
    for (int i {nrNod}; i < MATRICE_ADJ_SIZE-1; ++i) {
        for (int j {0}; j < MATRICE_ADJ_SIZE; ++j) {
            matrice_adj[i][j]=matrice_adj[i+1][j];
        }
    }
    --MATRICE_ADJ_SIZE;
}

void sterge_nod(int nrNod) {
    if (nrNod < 1 || nrNod > CURR_NR_NODES) {
        std::cout << "Person doesn't exist!\n";
        return;
    }
    if (!CURR_NR_NODES) {
        std::cout << "The nr. of persons is 0\n";
        return;
    }
    //stergem din info
    sterge_din_info(nrNod); // pas1
    sterge_din_mat_adj(nrNod); //pas2
    --CURR_NR_NODES;//pas3
}

void add_edge(int nod1, int nod2) {
    if (nod1 < 1 || nod1 > CURR_NR_NODES) {
        std::cout << "Person 1 doesn't exist!\n";
        return;
    }
    if (nod2 < 1 || nod2 > CURR_NR_NODES) {
        std::cout << "Person 2 doesn't exist!\n";
        return;
    }
    matrice_adj[nod1][nod2]=1;
}
void remove_edge(int nod1, int nod2) {
    if (nod1 < 1 || nod1 > CURR_NR_NODES) {
        std::cout << "Person 1 doesn't exist!\n";
        return;
    }
    if (nod2 < 1 || nod2 > CURR_NR_NODES) {
        std::cout << "Person 2 doesn't exist!\n";
        return;
    }
    matrice_adj[nod1][nod2]=0;
}

void print_node_info(int nrNod) {
    if (nrNod < 1 || nrNod > CURR_NR_NODES) {
        printf("The person doesn't exist!\n");
        return;
    }
    printf("%s", INFO[nrNod]);
}

int get_nr_nodes() {
    return CURR_NR_NODES;
}

void print_info() {
    for (int i {1}; i <= CURR_NR_NODES; ++i) {
        printf("ID: %i. Name: %s\n", i, INFO[i]);
    }
}

void list_friends(int nrNode) {
    if (nrNode < 1 || nrNode > CURR_NR_NODES) {
        printf("Person doesn't exist!\n");
        return;
    }
    for (int j {1}; j <= CURR_NR_NODES; ++j) {
        if (matrice_adj[nrNode][j]) {
            print_node_info(j);
            std::cout << ',';
        }
    }
}

int get_nr_of_friends(int nrNode) {
    if (nrNode < 1 || nrNode > CURR_NR_NODES) {
        printf("Person doesn't exist!\n");
        return -1;
    }
    int nrFriends {};
    for (int j {1}; j <= CURR_NR_NODES; ++j) {
        if (matrice_adj[nrNode][j]) {
            ++nrFriends;
        }
    }
    return nrFriends;
}

bool is_valid_id(int n) {
    return (n >= 1 && n <= CURR_NR_NODES);
}

/* Example program written for my DSA class 29.11.2023
 * int main() {
    INFO = alloc_info(NR_NODES_INIT+OFFSET);
    matrice_adj = alloc_mat_adj(NR_NODES_INIT+OFFSET);
    zero_mat_adj(matrice_adj, MATRICE_ADJ_SIZE);
    bool on {true};
    while (on) {
        std::cout << "------------------------------------------------------------------------------\n"
                     "1. Print a list of all the people\n"
                     "2. Add person\n"
                     "3. Show a person's friends\n"
                     "4. Add a person 2 as a friend to person 1\n"
                     "5. Remove the friendship between person 1 and person 2\n"
                     "6. Remove a person from the list\n"
                     "7. Print the total number of persons\n"
                     "8. Print the adjacency matrix which represents the connections between people\n"
                     "9. Any other option terminates the program gracefully\n";
        std::cout << "Type in option(1-8): ";
        int optiune;
        std::cin>>optiune;
        switch (optiune) {
            case 1: {
                print_info();
                break;
            }
            case 2: {
                add_node();
                break;
            }
            case 3: {
                std::cout << "Type in the person's ID: ";
                char p;
                std::cin >> p;
                if (!is_valid_id(p-'0')) {
                    std::cout << "ERROR: WRONG ID!\n";
                    continue;
                }
                print_node_info(p-'0');
                std::cout << " numbers " << get_nr_of_friends(p-'0') << " friends: ";
                list_friends(p-'0');
                std::cout << '\n';
                break;
            }
            case 4: {
                std::cout << "Enter the id of person 1: ";
                char p1;
                std::cin >> p1;
                if (!is_valid_id(p1-'0')) {
                    std::cout << "ERROR: ID OF PERSON 1 IS NOT VALID!\n";
                    continue;
                }
                std::cout << "Enter the id of person 2: ";
                char p2;
                std::cin >> p2;
                if (!is_valid_id(p2-'0')) {
                    std::cout << "ERROR: ID OF PERSON 2 IS NOT VALID!\n";
                    continue;
                }
                add_edge(p1-'0', p2-'0');
                break;
            }
            case 5: {
                std::cout << "Enter the id of person 1: ";
                char p1;
                std::cin >> p1;
                if (!is_valid_id(p1-'0')) {
                    std::cout << "ERROR: ID OF PERSON 1 IS NOT VALID!\n";
                    continue;
                }
                std::cout << "Enter the id of person 2: ";
                char p2;
                std::cin >> p2;
                if (!is_valid_id(p2-'0')) {
                    std::cout << "ERROR: ID OF PERSON 2 IS NOT VALID!\n";
                    continue;
                }
                remove_edge(p1-'0', p2-'0');
                break;
            }
            case 6: {
                std::cout << "Enter the id of the person you wish to remove: ";
                char p;
                std::cin>>p;
                if (!is_valid_id(p-'0')) {
                    std::cout << "ERROR: ID OF PERSON IS NOT VALID!\n";
                    continue;
                }
                sterge_nod(p-'0');
                break;
            }
            case 7: {
                std::cout << "There are " << get_nr_nodes() << " persons.\n";
                break;
            }
            case 8: {
                std::cout << "The adjacency matrix: \n";
                print(matrice_adj);
                break;
            }
            default: {
                on = false;
                break;
            }
        }
    }
    delete_info();
    delete_mat_adj();
    return 0;
}
 */

#endif //DATA_STRUCTURES_GRAPH_WITH_ADJACENCY_MATRIX_H

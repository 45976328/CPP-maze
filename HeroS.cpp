#include "HeroS.h"
#include <stack>
#include <utility>

using namespace std;


HeroS::HeroS(const int rows, const int cols) : character('S'){
        this->rows = rows;
        this->cols = cols;
        visited = new bool*[rows];
        for (int i = 0; i < rows; ++i){
                visited[i] = new bool[cols]();
        }

}

HeroS::~HeroS() {
    for (int i = 0; i < rows; ++i)
        delete[] visited[i];
    delete[] visited;
}


void HeroS::move(char** map){
        if(dfs_stack.empty()){// Αν είναι η πρώτη φορά που καλείται move(), ξεκινάμε από την τρέχουσα θέση του ήρωα
                dfs_stack.push(make_pair(y,x));// Βάλε την αρχική θέση στη στοίβα
        }

        while(!dfs_stack.empty()){// Όσο υπάρχει κάτι στη στοίβα (υπάρχει "μονοπάτι" να εξερευνήσουμε)
                pair<int,int> pos = dfs_stack.top(); // Πάρε την κορυφή της στοίβας
                dfs_stack.pop(); // Και αφαίρεσέ την
                int cy = pos.first; // Τρέχουσα γραμμή (y)
                int cx = pos.second; // Τρέχουσα στήλη (x)

                if(cy <0 || cx <0 || cy >= rows || cx >= cols){ continue;} // Αν είναι εκτός ορίων χάρτη, αγνόησέ το

                if(map[cy][cx] == '*' || visited[cy][cx]){continue;} // Αν είναι τοίχος ή έχει ήδη επισκεφθεί, αγνόησέ το

                visited[cy][cx] = true; // Μαρκάρισμα ως επισκέφθηκε
                y = cy;// Ενημέρωσε τις συντεταγμένες του ήρωα με τη νέα θέση
                x = cx;

                // Προσθήκη γειτόνων (η σειρά έχει σημασία!)
                dfs_stack.push(std::make_pair(cy + 1, cx));  // κάτω
                dfs_stack.push(std::make_pair(cy - 1, cx));  // πάνω
                dfs_stack.push(std::make_pair(cy, cx + 1));  // δεξιά
                dfs_stack.push(std::make_pair(cy, cx - 1));  // αριστερά

                break;  // σταμάτα στο πρώτο αποδεκτό βήμα
        }
}

void HeroS::moveToL(int ladderY, int ladderX) {
    if (y < ladderY) {
        y++;  
    } else if (y > ladderY) {
        y--;  
    }

    if (x < ladderX) {
        x++;  
    } else if (x > ladderX) {
        x--;  
    }
}


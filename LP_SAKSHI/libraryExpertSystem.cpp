#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Book structure
struct Book {
    string title;
    string author;
    string domain;
};

// Sample library books
vector<Book> library = {
    {"Artificial Intelligence: A Modern Approach", "Stuart Russell & Peter Norvig", "AI"},
    {"Deep Learning", "Ian Goodfellow", "AI"},
    {"Python Machine Learning", "Sebastian Raschka", "AI"},
    {"Database System Concepts", "Silberschatz, Korth", "DBMS"},
    {"Fundamentals of Database Systems", "Elmasri & Navathe", "DBMS"},
    {"NoSQL Distilled", "Pramod J. Sadalage", "DBMS"},
    {"Computer Networking: A Top-Down Approach", "Kurose & Ross", "Networking"},
    {"Data and Computer Communications", "William Stallings", "Networking"},
    {"Cybersecurity for Beginners", "Raef Meeuwisse", "Cybersecurity"},
    {"The Web Application Hacker's Handbook", "Dafydd Stuttard", "Cybersecurity"},
    {"HTML & CSS: Design and Build Websites", "Jon Duckett", "Web Development"},
    {"Eloquent JavaScript", "Marijn Haverbeke", "Web Development"}
};

// Convert string to lowercase
string to_lowercase(const string &s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Book recommendation logic
void recommend_books(const string &domain_input) {
    string domain = to_lowercase(domain_input);
    bool found = false;

    cout << "\n📚 Recommended books for domain: " << domain_input << "\n" << endl;

    for (const auto &book : library) {
        if (to_lowercase(book.domain) == domain) {
            cout << "🔹 " << book.title << " by " << book.author << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "❌ No books found for the selected domain. Please try a valid one." << endl;
    }
}

int main() {
    cout << "\n--- Library Expert System: Book Recommender ---\n" << endl;
    cout << "Available Domains: AI, DBMS, Networking, Web Development, Cybersecurity" << endl;

    string domain_choice;
    cout << "Enter your project domain: ";
    getline(cin, domain_choice); // Accept input with spaces

    recommend_books(domain_choice);

    return 0;
}

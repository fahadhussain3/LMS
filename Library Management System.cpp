#include <iostream>
#include <cstring>
using namespace std;

struct Book
{
    char title[50];
    char author[50];
    int number_of_copies;
};

Book **initializeLibrary(int &numCategories, int *&numBooksInCategory, int *&freeIndexInCategory)
{
    cout << "Enter number of categories: ";
    cin >> numCategories;
    numBooksInCategory = new int[numCategories];
    freeIndexInCategory = new int[numCategories];
    Book **library = new Book *[numCategories];
    for (int i = 0; i < numCategories; i++)
    {
        cout << "Enter the number of books for category " << i + 1 << ": ";
        cin >> numBooksInCategory[i];
        library[i] = new Book[numBooksInCategory[i]];
        freeIndexInCategory[i] = 0;
    }
    return library;
}

void addBook(Book **library, int numCategories, int *numBooksInCategory, int *freeIndexInCategory)
{
    int catNum;
    cout << "Enter category number to add a book (1 to " << numCategories << " ): ";
    cin >> catNum;
    catNum--;
    if (freeIndexInCategory[catNum] == numBooksInCategory[catNum])
    {
        cout << "No more Books can be added as category is full" << endl;
        return;
    }
    int &colNum = freeIndexInCategory[catNum];
    cin.ignore(500, '\n');
    cout << "Enter Book Title: ";
    cin.getline(library[catNum][colNum].title, 50);

    cout << "Enter Author : ";
    cin.getline(library[catNum][colNum].author, 50);

    cout << "Enter Number of Copies: ";
    cin >> library[catNum][colNum].number_of_copies;
    colNum++;
    cout << "Book added sucessfully!" << endl;
}

Book *searchBook(Book **library, int numCategories, int *numBooksInCategory, int *freeIndexInCategory)
{
    char bookTitle[50];
    cin.ignore(500, '\n');
    cout << "Enter book title to search: ";
    cin.getline(bookTitle, sizeof(bookTitle));
    for (int i = 0; i < numCategories; i++)
    {
        for (int j = 0; j < freeIndexInCategory[i]; j++)
        {
            if (strcmp(library[i][j].title, bookTitle) == 0)
            {
                cout << "Found in category " << i + 1 << endl;
                cout << "Title: " << library[i][j].title << endl;
                cout << "Author: " << library[i][j].author << endl;
                cout << "Copies: " << library[i][j].number_of_copies << endl;
                return &(library[i][j]);
            }
        }
    }
    cout << " No Book Found with this title " << endl;
    return nullptr;
}

void updateCopies(Book **library, int numCategories, int *numBooksInCategory, int *freeIndexInCategory)
{
    Book *ref = searchBook(library, numCategories, numBooksInCategory, freeIndexInCategory);
    if (ref == nullptr)
    {
        cout << "No book found with this title " << endl;
        return;
    }
    int number;
    cout << "Enter new number of copies: ";
    cin >> number;
    ref->number_of_copies = number;
    cout << "Number of Copies Updated Successfully! " << endl;
}

void printAllBooks(Book **library, int numCategories, int *numBooksInCategory, int *freeIndexInCategory)
{
    for (int i = 0; i < numCategories; i++)
    {
        cout << "Category " << i + 1 << ": " << endl;
        for (int j = 0; j < freeIndexInCategory[i]; j++)
        {
            cout << "\t\t\t";
            cout << "Title: " << library[i][j].title << ", ";
            cout << "Author: " << library[i][j].author << ", ";
            cout << "Copies:" << library[i][j].number_of_copies;
            cout << endl;
        }
    }
}

void releaseMemory(Book **library, int numCategories, int *numBooksInCategory, int *freeIndexInCategory)
{
    for (int i = 0; i < numCategories; i++)
    {
        delete[] library[i];
    }
    delete[] library;
    delete[] numBooksInCategory;
    delete[] freeIndexInCategory;
}

int main()
{
    int numCategories = 0;
    int *numBooksInCategory = nullptr;
    int *freeIndexInCategory = nullptr;
    Book **library = initializeLibrary(numCategories, numBooksInCategory, freeIndexInCategory);
    int choice = 0;
    while (choice != 5)
    {
        cout << "\nMenu:\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book\n";
        cout << "3. Update Number of Copies\n";
        cout << "4. Print All Books\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            addBook(library, numCategories, numBooksInCategory, freeIndexInCategory);
            break;
        case 2:
            searchBook(library, numCategories, numBooksInCategory, freeIndexInCategory);
            break;
        case 3:
            updateCopies(library, numCategories, numBooksInCategory, freeIndexInCategory);
            break;
        case 4:
            printAllBooks(library, numCategories, numBooksInCategory, freeIndexInCategory);
            break;
        case 5:
            cout << "Exiting the program..." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }
    releaseMemory(library, numCategories, numBooksInCategory, freeIndexInCategory);
    return 0;
}

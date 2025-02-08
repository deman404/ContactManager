#include <windows.h>
#include <stdio.h>
#include <string.h>

#define MAX_CONTACTS 100
#define FILE_NAME "contacts.txt"

typedef struct
{
    char name[50];
    char phone[15];
    char email[50];
} Contact;

Contact contacts[MAX_CONTACTS];
int contactCount = 0;
HWND hName, hPhone, hEmail, hOutput, hRemoveIndex;

void LoadContactsFromFile()
{
    FILE *file = fopen(FILE_NAME, "r");
    if (file != NULL)
    {
        while (fscanf(file, "%49[^,],%14[^,],%49[^\n]\n", contacts[contactCount].name, contacts[contactCount].phone, contacts[contactCount].email) == 3)
        {
            contactCount++;
            if (contactCount >= MAX_CONTACTS)
                break;
        }
        fclose(file);
    }
}

void SaveContactsToFile()
{
    FILE *file = fopen(FILE_NAME, "w");
    if (file != NULL)
    {
        for (int i = 0; i < contactCount; i++)
        {
            fprintf(file, "%s,%s,%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
        }
        fclose(file);
    }
}

void AddContact()
{
    char name[50] = {0};
    char phone[15] = {0};
    char email[50] = {0};
    GetWindowText(hName, name, sizeof(name));
    GetWindowText(hPhone, phone, sizeof(phone));
    GetWindowText(hEmail, email, sizeof(email));

    // Prevent adding empty data
    if (strlen(name) == 0 || strlen(phone) == 0 || strlen(email) == 0)
    {
        SetWindowText(hOutput, "Tous les champs doivent être remplis !");
        return;
    }

    if (contactCount < MAX_CONTACTS)
    {
        strncpy(contacts[contactCount].name, name, sizeof(contacts[contactCount].name) - 1);
        strncpy(contacts[contactCount].phone, phone, sizeof(contacts[contactCount].phone) - 1);
        strncpy(contacts[contactCount].email, email, sizeof(contacts[contactCount].email) - 1);
        contactCount++;
        SaveContactsToFile();
        SetWindowText(hOutput, "Contact ajouté !");
    }
    else
    {
        SetWindowText(hOutput, "Liste de contacts pleine !");
    }
}

void RemoveContact()
{
    char removeIndexStr[10];
    GetWindowText(hRemoveIndex, removeIndexStr, sizeof(removeIndexStr));
    int removeIndex = atoi(removeIndexStr) - 1;

    if (removeIndex >= 0 && removeIndex < contactCount)
    {
        for (int i = removeIndex; i < contactCount - 1; i++)
        {
            contacts[i] = contacts[i + 1];
        }
        contactCount--;
        SaveContactsToFile();
        SetWindowText(hOutput, "Contact supprimé !");
    }
    else
    {
        SetWindowText(hOutput, "Numéro de contact invalide !");
    }
}

void DisplayContacts()
{
    char buffer[2048] = "Contacts:\n";
    for (int i = 0; i < contactCount; i++)
    {
        char temp[128];
        snprintf(temp, sizeof(temp), "%d. %s - %s - %s\n", i + 1, contacts[i].name, contacts[i].phone, contacts[i].email);
        strncat(buffer, temp, sizeof(buffer) - strlen(buffer) - 1);
    }
    SetWindowText(hOutput, buffer);
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_COMMAND:
        if (LOWORD(wp) == 1) // Add Contact
            AddContact();
        if (LOWORD(wp) == 2) // Show Contacts
            DisplayContacts();
        if (LOWORD(wp) == 3) // Remove Contact
            RemoveContact();
        break;
    case WM_CREATE:
        SetWindowPos(hwnd, NULL, 100, 100, 500, 400, SWP_NOZORDER | SWP_NOACTIVATE);

        // Title: Contact Information
        CreateWindow("STATIC", "Nom:", WS_VISIBLE | WS_CHILD, 20, 20, 80, 30, hwnd, NULL, NULL, NULL);
        hName = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 110, 20, 250, 30, hwnd, NULL, NULL, NULL);

        CreateWindow("STATIC", "Telephone:", WS_VISIBLE | WS_CHILD, 20, 60, 80, 30, hwnd, NULL, NULL, NULL);
        hPhone = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 110, 60, 250, 30, hwnd, NULL, NULL, NULL);

        CreateWindow("STATIC", "E-mail:", WS_VISIBLE | WS_CHILD, 20, 100, 80, 30, hwnd, NULL, NULL, NULL);
        hEmail = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 110, 100, 250, 30, hwnd, NULL, NULL, NULL);

        HWND hAddBtn = CreateWindow("BUTTON", "Ajouter un contact", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 140, 150, 40, hwnd, (HMENU)1, NULL, NULL);
        HWND hShowBtn = CreateWindow("BUTTON", "Afficher les contacts", WS_VISIBLE | WS_CHILD | WS_BORDER, 190, 140, 150, 40, hwnd, (HMENU)2, NULL, NULL);

        // New field to remove contact
        CreateWindow("STATIC", "Supprimer l'index:", WS_VISIBLE | WS_CHILD, 20, 200, 120, 30, hwnd, NULL, NULL, NULL);
        hRemoveIndex = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 200, 60, 30, hwnd, NULL, NULL, NULL);

        HWND hRemoveBtn = CreateWindow("BUTTON", "Supprimer le contact", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 200, 150, 40, hwnd, (HMENU)3, NULL, NULL);

        // Output Area (Scrollable area)
        hOutput = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY, 20, 250, 400, 100, hwnd, NULL, NULL, NULL);

        LoadContactsFromFile();
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProcedure;
    wc.hInstance = hInstance;
    wc.lpszClassName = "ContactApp";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);
    HWND hwnd = CreateWindow("ContactApp", "Gestionnaire de contacts", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 400, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
